/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

/*
// �¼���״̬��
enum EB_STATE EventBoardState;
// ״̬ת���¼�
enum FSM_EVENTS EventBoardEvents;
// ״̬���ṹ��
struct FSM EventBoardFSM[STATE_NUM][EVENTS_NUM];
*/
int main()
{
	DINT;
	InitAll();   //��ʼ��

	while (1)
	{
		
	}
}

Uint16 IdleStateCtl(void)
{
	int ret = 0;
	// �ϴ����ݱ�
	if (SendTableFlag == SET)
	{
		CheckReadTable();
		ReplyUpTableFrame(SendTableID);
		SendTableFlag = CLEAR;
	}	
	return ret;
}

Uint16 OperaStateCtl(void)
{
	int ret = 0;
	/*
	*(Uint16*)0x8000 = 3;   // Table ID
	*(Uint16 *)0x8001 = 6;  // WorkMode
	PPShortModeFlag = SET;
	*/

	// STWTEģʽ��ģʽ��0x0001
	if (SingleModeFlag == SET)
	{
		CheckReadTable();
		DeCpmgTop();
		SingleModeFlag	= CLEAR;
	}

	// PPMODEģʽ��ģʽ��0x0002
	else if (PPModeFlag == SET)
	{
		CheckReadTable();
		PPModeTop();
		PPModeFlag = CLEAR;
	}

	// PPDIFģʽ��ģʽ��0x0003
	else if (PPDIFModeFlag == SET)
	{
		CheckReadTable();
		PPDIFModeTop();
		PPDIFModeFlag = CLEAR;
	}

	// PPT1ģʽ��ģʽ��0x0004
	else if (PPT1ModeFlag == SET)
	{
		CheckReadTable();
		PPT1ModeTop();
		PPT1ModeFlag = CLEAR;
	}

	// PPOFTWģʽ��ģʽ��0x0005
	else if (PPOFTWModeFlag == SET)
	{
		CheckReadTable();
		PPOFTWModeTop();
		PPOFTWModeFlag = CLEAR;
	}

	// PPShortģʽ��ģʽ��0x0006
	else if (PPShortModeFlag == SET)
	{
		CheckReadTable();
		PPShortModeTop();
		PPShortModeFlag = CLEAR;
	}

	// �ų�ɨƵģʽ��ģʽ��0x0007

	// ����ɨƵģʽ��ģʽ��0x0008
	else if(ScanModeFlag==SET)
	{
		CheckReadTable();
		ScanModeTop();
		ScanModeFlag	=CLEAR;
	}

	// ���̶�ģʽ���϶�ȿ̶�ģʽ��ģʽ��0x0009|0x000A 
	else if((ScaleModeFlag||HoleModeFlag)==SET)
	{
		CheckReadTable();
		ScaleHoleModeTop();     //�̶�������
		ScaleModeFlag	= CLEAR;
		HoleModeFlag	= CLEAR;
	}

	// ������ģʽ��ģʽ��0x000B
	else if(PulseAcqFlag==SET)
	{
		CheckReadTable();
		PulseTop();       //���μ��������
		PulseAcqFlag	= CLEAR;
	}
	return ret;
}

Uint16 CasDctStateCtl(void)
{
	Uint16 ret = 0;
	return ret;
}

Uint16 AcqFinStateCtl(void)
{
	Uint16 ret = 0;
	return ret;
}
