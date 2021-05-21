/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

Uint16 CasingMiniNumAry = 5;


void CasingDetectTop()
{
	// 五次Mini扫频
	int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// 五次Mini扫频
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	SaveNTempPt	= (int *)(CASING_TABLE_START+7);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+19);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);
	
	// 插值计算中心频率及其幅值
	
	
	// 存储数据
	SaveNTempPt 	= (int *)CASING_TABLE_START;
	*SaveNTempPt++	= REPLY_CASING_F;   // 数据头部
	*SaveNTempPt++	= 32;				// 长度
	*SaveNTempPt++	= 0x0008;        	// 工作模式
	*SaveNTempPt	= CenterFreq * 10;  // 工作频率，下发和上传的中心频率单位是0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 28);
	*SaveNTempPt++ = 0;          		// Q值
	*SaveNTempPt++ = 0x294;				// 参考幅值
	*SaveNTempPt++ = 0;					// 中心频率
	*SaveNTempPt   = 0;					// 中心频率幅值
	
	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(CASING_TABLE_START);
	int i=0;
	for (;i<32;++i)  // CheckSum计算前面的数据时，除去CheckSum本身
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 33;
}

// 启动测井模式之前需要通过扫频来判断仪器是否处于套管中
void CasingDetectOnce()
{
	// 五次Mini扫频
	int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	// 暂时将测量结果存放在此处
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// 插值计算中心频率及其幅值

	
}

