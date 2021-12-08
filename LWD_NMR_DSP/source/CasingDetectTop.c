/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-04-26 14:28:14
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-14 14:49:39
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

Uint16 CasingMiniNumAry = 5;
Uint16 center_fre;	   	// 由插值得到的中心频率，需要与工作频率区分开来
Uint16 center_fre_amp; 	// 中心频率幅值

#define CASING_DATA_LEN 33

Uint16 getCenterFreq()
{
	return center_fre;
}

Uint16 getCenterFreqAmp()
{
	return center_fre_amp;
}

void CasingDetectTop()
{
	Uint16 Q_value; 			// Q值
	
	// 五次Mini扫频
    int cnt = 0;
    // 继电器控制
    RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 11);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// 五次Mini扫频
	RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 8);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 20);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// 计算Q值
	Q_value = CalQValue(TransmitFre, CASING_TABLE_START + 20);
	// 计算中心频率和赋值
	CalFreAndAmp(&center_fre, &center_fre_amp);

	// 存储数据
	SaveNTempPt = (int *)CASING_TABLE_START;
	*SaveNTempPt++ = REPLY_CASING_F;    // 数据头部
	*SaveNTempPt++ = CASING_DATA_LEN;   // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;    // 从机标识
	*SaveNTempPt++ = 0x0008;		    // 工作模式存储为主扫频模式
	*SaveNTempPt = TransmitFre;	    // 工作频率，下发和上传的中心频率单位是0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 29);
	*SaveNTempPt++ = Q_value;			// Q值
	*SaveNTempPt++ = 0x294;		   	    // 参考幅值
	*SaveNTempPt++ = center_fre;  	    // 中心频率
	*SaveNTempPt = center_fre_amp; 	    // 中心频率幅值

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(CASING_TABLE_START);
	int i = 0;
	for (; i < CASING_DATA_LEN; ++i) // CheckSum计算前面的数据时，除去CheckSum本身
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = CASING_DATA_LEN + 1;
}

// 启动测井模式之前需要通过扫频来判断仪器是否处于套管中，暂未使用
int CasingDetectOnce()
{
	// 五次Mini扫频
    int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
	    // 继电器控制
	    RelayOpen(RelayCtrlCode);
		MiniScan(TransmitFre, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
		RelayClose(RelayCtrlCode);
	}
	// 暂时将测量结果存放在此处
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// 插值计算中心频率及其幅值
	MiniFreq = TransmitFre;
	MiniFreq -= ScanDeltaFreq*4;
	for (cnt=0;cnt<9;cnt++)
	{
	    x[cnt] = MiniFreq + ScanDeltaFreq*cnt;
	    y[cnt] = *SaveSTempPt++;
	}

	// 计算中心频率及其幅值
	// 高斯拟合公式为 y=a*e(-((x-b)/c)^2)
	// b为拟合出的中心点
	GaussFit(x, y, &a, &b, &c);

	// 计算中心频率和幅值
	center_fre = (Uint16)b;
	center_fre_amp = (Uint16)CublicSplineInterpolation(x, y, b);	// 强制类型转换

	/*
	// 计算Q值
	Q_value = (Uint16)(c*Q_FACTOR);
    */

//    if (center_fre_amp <= ParamOrderData.data.AutoAmpThd)   // 幅值异常
//        return 0;

	// TODO: 根据中心频率及其幅值进行频率优选

    return 1;
}

// 为了方便使用，将两个函数拆开来写
// 计算Q值
Uint16 CalQValue(Uint16 CenterFre, Uint32 AmpAddr)
{
    // 初始化
    int cnt = 0;
    MiniFreq = CenterFre;
    MiniFreq -= ScanDeltaFreq * 4;
    SaveSTempPt = (Uint16 *)AmpAddr;
    for (cnt = 0; cnt < 9; cnt++)
    {
        x[cnt] = MiniFreq + ScanDeltaFreq * cnt;
        y[cnt] = *SaveSTempPt++;
    }
    // 计算中心频率及其幅值
    // 高斯拟合公式为 y=a*e(-((x-b)/c)^2)
    // b为拟合出的中心点，a为幅值
    GaussFit(x, y, &a, &b, &c);
    return (Uint16)(c*Q_FACTOR/b);
}

// 计算中心频率和幅值
void CalFreAndAmp(Uint16 *fre, Uint16* amp)
{
    *fre = (Uint16)b;
    *amp = (Uint16)CublicSplineInterpolation(x, y, b);
}
