/*
 * @Descripttion: ״̬����
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-01 09:25:44
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-07 10:36:18
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(IdleStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(CasDctStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(OperaStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(TestStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(ScaleStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(AcqFinStateCtl, "secureRamFuncs");

void IdleStateCtl(void)
{
	// �ϴ����ݱ�
	if (SendTableFlag == SET)
	{
		CheckReadTable();
		ReplyUpTableFrame(SendTableID);
		SendTableFlag = CLEAR;
	}		
}

void CasDctStateCtl(void)
{
	if (_caseingDetectFlag == SET)
	{
		_casingOrOperaFlag = SET;
		CasingDetectTop();
		
		_caseingDetectFlag = CLEAR;
		EventBoardState = ACQ_FIN_STAT;
	}
}

void OperaStateCtl(void)
{
    // ʹ���·��¶ȼ��㷢��Ƶ�ʺͼ̵��������룬��ģʽ����֮ǰһ��Ҫȷ���¶��·����
	// ����ģʽ�²�ʹ���¶ȼ�����ķ���Ƶ�ʺͼ̵���������
	// �̵����������Ƶ����һһ��Ӧ��

    FreqAry[1] = TransmitFre;

	if (_operationFlag == SET)
	{
		_casingOrOperaFlag = CLEAR;
		
		if (CasingDetectOnce())
		{
			_casingDetectErrFlag = CLEAR;

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

			// ��г�̶�ģʽ��ģʽ��0x0007
			else if (TuningModeFlag == SET)
			{
				CheckReadTable();
				TuningModeTop();
				TuningModeFlag = CLEAR;
			}
			// ����ɨƵģʽ��ģʽ��0x0008
			else if(ScanModeFlag==SET)
			{
				CheckReadTable();
 				ScanModeTop();
				ScanModeFlag	= CLEAR;
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
		else
			_casingDetectErrFlag = SET;			// �׹ܼ���쳣
		
		_operationFlag = CLEAR;
		EventBoardState = ACQ_FIN_STAT;
	}
}

void TestStateCtl(void)
{
    _casingOrOperaFlag = SET;

    CheckReadTable();

    // ����̵���������
	// �̵����������ӿ̶Ȳ��������õ�
    FreqAry[1] = CenterFreq;
    RelayCtrlCode_f = RELAY_f_k * CenterFreq + RELAY_f_b;
    // �޷���0-1023
    if (RelayCtrlCode_f < 0)
        RelayCtrlCode = 0;
    else if (RelayCtrlCode_f > 1023)
        RelayCtrlCode = 1023;
    else
        RelayCtrlCode = (Uint16)RelayCtrlCode_f;  // ǿ������ת��

    // STWTEģʽ��ģʽ��0x0001
    if (SingleModeFlag == SET)
    {
        DeCpmgTop();
        SingleModeFlag  = CLEAR;
    }

    // PPMODEģʽ��ģʽ��0x0002
    else if (PPModeFlag == SET)
    {
        PPModeTop();
        PPModeFlag = CLEAR;
    }

    // PPDIFģʽ��ģʽ��0x0003
    else if (PPDIFModeFlag == SET)
    {
        PPDIFModeTop();
        PPDIFModeFlag = CLEAR;
    }

    // PPT1ģʽ��ģʽ��0x0004
    else if (PPT1ModeFlag == SET)
    {
        PPT1ModeTop();
        PPT1ModeFlag = CLEAR;
    }

    // PPOFTWģʽ��ģʽ��0x0005
    else if (PPOFTWModeFlag == SET)
    {
        PPOFTWModeTop();
        PPOFTWModeFlag = CLEAR;
    }

    // PPShortģʽ��ģʽ��0x0006
    else if (PPShortModeFlag == SET)
    {
        PPShortModeTop();
        PPShortModeFlag = CLEAR;
    }

    // �ų�ɨƵģʽ��ģʽ��0x0007

    // ����ɨƵģʽ��ģʽ��0x0008
    else if(ScanModeFlag==SET)
    {
        ScanModeTop();
        ScanModeFlag    =CLEAR;
    }

    // ���̶�ģʽ���϶�ȿ̶�ģʽ��ģʽ��0x0009|0x000A
    else if((ScaleModeFlag||HoleModeFlag)==SET)
    {
        ScaleHoleModeTop();     //�̶�������
        ScaleModeFlag   = CLEAR;
        HoleModeFlag    = CLEAR;
    }

    // ������ģʽ��ģʽ��0x000B
    else if(PulseAcqFlag==SET)
    {
        PulseTop();       //���μ��������
        PulseAcqFlag    = CLEAR;
    }

    EventBoardState = ACQ_FIN_STAT;
}

void ScaleStateCtl(void)
{
    _casingOrOperaFlag = SET;

    CheckReadTable();   // ����CenterFreq

    // ����̵���������
    FreqAry[1] = CenterFreq;
    RelayCtrlCode_f = RELAY_f_k * CenterFreq + RELAY_f_b;
    // �޷���0-1023
    if (RelayCtrlCode_f < 0)
        RelayCtrlCode = 0;
    else if (RelayCtrlCode_f > 1023)
        RelayCtrlCode = 1023;
    else
        RelayCtrlCode = (Uint16)RelayCtrlCode_f;  // ǿ������ת��

    // ����ɨƵģʽ��ģʽ��0x0008
    if(ScanModeFlag==SET)
    {
        ScanModeTop();
        ScanModeFlag    =CLEAR;
    }

    // ���̶�ģʽ���϶�ȿ̶�ģʽ��ģʽ��0x0009|0x000A
    else if((ScaleModeFlag||HoleModeFlag)==SET)
    {
        ScaleHoleModeTop();     //�̶�������
        ScaleModeFlag   = CLEAR;
        HoleModeFlag    = CLEAR;
    }

    // ������ģʽ��ģʽ��0x000B
    else if(PulseAcqFlag==SET)
    {
        PulseTop();       //���μ��������
        PulseAcqFlag    = CLEAR;
    }

    EventBoardState = ACQ_FIN_STAT;
}


void AcqFinStateCtl(void)
{
	if (_modeDataSendFlag == SET)
	{
		if (_casingOrOperaFlag == SET)		// CASING_DETECTģʽ/TEST_STAT/CAL_STAT
		{
			ReplyModeDataFrame(SCANTABLE_START, modeDataSendLen);
		}
		else								// OPERATIONģʽ
		{
			if (_casingDetectErrFlag == SET)	// �׹ܼ���쳣
				ReplyCasingErrFrame();
			else								// �׹ܼ������
				ReplyModeDataFrame(SCANTABLE_START, modeDataSendLen);
		}

		_modeDataSendFlag = CLEAR;
	}
}
