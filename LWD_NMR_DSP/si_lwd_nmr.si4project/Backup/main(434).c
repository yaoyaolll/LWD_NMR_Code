/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

/*
// 事件板状态字
enum EB_STATE EventBoardState;
*/
int main()
{	
	DINT;
	InitAll();   //初始化

	while (1)
	{
		(*(eventFunc[EventBoardState]))();
	}
}

void IdleStateCtl(void)
{
	// 上传数据表
	if (SendTableFlag == SET)
	{
		CheckReadTable();
		ReplyUpTableFrame(SendTableID);
		SendTableFlag = CLEAR;
	}	

	// 进入套管检测状态
	
	// 进入正常工作状态
	
}

void OperaStateCtl(void)
{
	/*
	*(Uint16*)0x8000 = 3;   // Table ID
	*(Uint16 *)0x8001 = 6;  // WorkMode
	PPShortModeFlag = SET;
	*/

	// STWTE模式，模式字0x0001
	if (SingleModeFlag == SET)
	{
		CheckReadTable();
		DeCpmgTop();
		SingleModeFlag	= CLEAR;
	}

	// PPMODE模式，模式字0x0002
	else if (PPModeFlag == SET)
	{
		CheckReadTable();
		PPModeTop();
		PPModeFlag = CLEAR;
	}

	// PPDIF模式，模式字0x0003
	else if (PPDIFModeFlag == SET)
	{
		CheckReadTable();
		PPDIFModeTop();
		PPDIFModeFlag = CLEAR;
	}

	// PPT1模式，模式字0x0004
	else if (PPT1ModeFlag == SET)
	{
		CheckReadTable();
		PPT1ModeTop();
		PPT1ModeFlag = CLEAR;
	}

	// PPOFTW模式，模式字0x0005
	else if (PPOFTWModeFlag == SET)
	{
		CheckReadTable();
		PPOFTWModeTop();
		PPOFTWModeFlag = CLEAR;
	}

	// PPShort模式，模式字0x0006
	else if (PPShortModeFlag == SET)
	{
		CheckReadTable();
		PPShortModeTop();
		PPShortModeFlag = CLEAR;
	}

	// 磁场扫频模式，模式字0x0007

	// 仪器扫频模式，模式字0x0008
	else if(ScanModeFlag==SET)
	{
		CheckReadTable();
		ScanModeTop();
		ScanModeFlag	=CLEAR;
	}

	// 主刻度模式或孔隙度刻度模式，模式字0x0009|0x000A 
	else if((ScaleModeFlag||HoleModeFlag)==SET)
	{
		CheckReadTable();
		ScaleHoleModeTop();     //刻度主函数
		ScaleModeFlag	= CLEAR;
		HoleModeFlag	= CLEAR;
	}

	// 脉冲检测模式，模式字0x000B
	else if(PulseAcqFlag==SET)
	{
		CheckReadTable();
		PulseTop();       //波形检测主函数
		PulseAcqFlag	= CLEAR;
	}
}

void CasDctStateCtl(void)
{
}

void AcqFinStateCtl(void)
{

}
