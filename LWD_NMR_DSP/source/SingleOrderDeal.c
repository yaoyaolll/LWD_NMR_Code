/*
 * @Descripttion: �·�����ָ��������ݣ��Ĵ�����
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-05-31 15:53:25
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-17 00:24:48
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// single_ord_ary_idx = 0
void EmptyDeal()
{
    return;
}

// single_ord_ary_idx = 1����ѯ״ָ̬��
void InquireDeal()
{
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 2����������ָ��
void OperationDeal()
{
    if (EventBoardState == IDLE_STAT)
    {
        CheckWorkMode();
        switch (WorkMode)
        {
        case 0x0001:
            SingleModeFlag = SET;
            break;
        case 0x0002:
            PPModeFlag = SET;
            break;
        case 0x0003:
            PPDIFModeFlag = SET;
            break;
        case 0x0004:
            PPT1ModeFlag = SET;
            break;
        case 0x0005:
            PPOFTWModeFlag = SET;
            break;
        case 0x0006:
            PPShortModeFlag = SET;
            break;
        case 0x0007:
            TuningModeFlag = SET;
        case 0x0008:
            ScanModeFlag = SET;
            break;
        case 0x0009:
            ScaleModeFlag = SET;
            break;
        case 0x000A:
            HoleModeFlag = SET;
            break;
        case 0x000B:
            PulseAcqFlag = SET;
            break;
        default:
            break;
        }
        _operationFlag = SET;
        EventBoardState = OPERATION_STAT;
    }
    ReplyStateFrame(EventBoardState); // �ظ�֡
}

// single_ord_ary_idx = 3���׹ܼ��ָ��
void CasingDeal()
{
    if (EventBoardState == IDLE_STAT)
    {
        _caseingDetectFlag = SET;
        EventBoardState = CASING_DETECT_STAT;
    }
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 4���ϴ�ģʽ����ָ������׹ܼ�����ݺͲ⾮ģʽ����
void DataUpDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        _modeDataSendFlag = SET; // �ϴ�����
    }
}

// single_ord_ary_idx = 5��ģʽ����ȷ��ָ��
void ModeConfirmDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        EventBoardState = IDLE_STAT;
    }
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 6�����ܶ̽�����ָ���ʱδ��
void K1K2EnDeal()
{
    K1_EN = USER_ENABLE; // K1�պϣ�����ߣ�
    K2_EN = USER_ENABLE; // K2�պ�
    HVState = HV_ON;     // ������ͨ״̬
    ReplyNoVarFrame(DATA_K1K2_EN_F);
}

// TODO
// single_ord_ary_idx = 7�����ܶ̽ڶϿ�ָ���ʱδ��
void K1K2DisDeal()
{
    K1_DIS = USER_DISABLE;
    K2_DIS = USER_DISABLE;
    HVState = HV_OFF;
    ReplyNoVarFrame(DATA_K1K2_DIS_F);
}

// single_ord_ary_idx = 8�����ܶ̽�״̬�ж�ָ��
void HVStateDeal()
{
    ReplySingleVarFrame(DATA_HVState_F, HVState);
}

// single_ord_ary_idx = 9��ϵͳ�Լ��ָ��
void SysCheckDeal()
{
    Uint16 retData = 0;
    TIMER_DATA = 1; //1������λ
    TIMER_START = 0x1;
    Delay(100);

    if (GpioDataRegs.GPADAT.bit.GPIOA9 != 1)
        retData = 0x20;
    TIMER_STOP = 0x2;

    ReplySingleVarFrame(DATA_SysCheck_F, retData);
}

// single_ord_ary_idx = 10��PAPS�����ϴ�ָ��
void PAPSDataUpDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        _PAPSUpDataFlag = SET;
    }
}
