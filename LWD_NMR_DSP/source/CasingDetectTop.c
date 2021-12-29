/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-04-26 14:28:14
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-27 10:04:08
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#define CASING_DATA_LEN 36

Uint16 CasingMiniNumAry = 5;

void CasingDetectTop()
{
	Uint16 Q_value1; 			// Q值1
	Uint16 center_fre1;	   		// 由插值得到的中心频率1
	Uint16 center_fre_amp1; 	// 中心频率幅值1
	
	Uint16 Q_value2;			// Q值2
	Uint16 center_fre2;			// 由插值得到的中心频率2
	Uint16 center_fre_amp2;		// 中心频率幅值2
    int cnt = 0;

	// 五次Mini扫频1
    RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 8);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// 计算Q值1，中心频率1以及中心频率幅值1
	Q_value1 =  CalQValue(TransmitFre, CASING_TABLE_START + 8);
	CalFreAndAmp(&center_fre1, &center_fre_amp1);

	// 五次Mini扫频2
	RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 20);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 23);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// 计算Q值
	Q_value2 = CalQValue(TransmitFre, CASING_TABLE_START + 23);
	// 计算中心频率和赋值
	CalFreAndAmp(&center_fre2, &center_fre_amp2);

	// 存储数据
	SaveNTempPt = (int *)CASING_TABLE_START;
	*SaveNTempPt++ = REPLY_CASING_F;    // 数据头部
	*SaveNTempPt++ = CASING_DATA_LEN;   // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;    // 从机标识
	*SaveNTempPt++ = 0x0008;		    // 工作模式存储为主扫频模式
	*SaveNTempPt = TransmitFre;	    	// 工作频率，下发和上传的中心频率单位是0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 17);
	*SaveNTempPt++ = Q_value1;			// Q值1
	*SaveNTempPt++ = center_fre1;  	    // 中心频率1
	*SaveNTempPt = center_fre_amp1; 	// 中心频率幅值1

	SaveNTempPt = (int *)(CASING_TABLE_START + 32);
	*SaveNTempPt++ = Q_value2;    		// Q值2
	*SaveNTempPt++ = center_fre2;		// 中心频率2
	*SaveNTempPt++ = center_fre_amp2;	// 中心频率幅值2
	*SaveNTempPt = 0x294;				// 参考幅值

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

// 为了方便使用，将两个函数拆开来写
// 计算Q值
Uint16 CalQValue(Uint16 CenterFre, Uint32 AmpAddr)
{
    // 初始化
    int cnt = 0;
	float res = 0;
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
	res = c*Q_FACTOR/b;
    return (Uint16)res;
}

// 计算中心频率和幅值
void CalFreAndAmp(Uint16 *fre, Uint16* amp)
{
    *fre = (Uint16)b;
    *amp = (Uint16)CublicSplineInterpolation(x, y, b);
}
