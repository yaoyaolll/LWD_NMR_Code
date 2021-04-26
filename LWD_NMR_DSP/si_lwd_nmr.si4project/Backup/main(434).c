/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

/*
// �¼���״̬��
enum EB_STATE EventBoardState;
*/
int main()
{	
	DINT;
	InitAll();   //��ʼ��

	while (1)
	{
		(*(eventFunc[EventBoardState]))();
	}
}

void IdleStateCtl(void)
{
	// �ϴ����ݱ�
	if (SendTableFlag == SET)
	{
		CheckReadTable();
		ReplyUpTableFrame(SendTableID);
		SendTableFlag = CLEAR;
	}	

	// �����׹ܼ��״̬
	
	// ������������״̬
	
}

void OperaStateCtl(void)
{
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
}

void CasDctStateCtl(void)
{
}

void AcqFinStateCtl(void)
{

}
