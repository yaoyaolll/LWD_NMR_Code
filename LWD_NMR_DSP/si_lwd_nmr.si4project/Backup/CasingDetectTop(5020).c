/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

Uint16 CasingMiniNumAry = 5;


void CasingDetectTop()
{
	
}

void CasingDetectOnce()
{
	// 五次Mini扫频
	int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	SaveNTempPt	= (int *)(PPShort_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(PPShort_TABLE_START+7);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);
	
}
