/*
 * @Descripttion: 下发单个指令（不带数据）的处理函数
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-05-31 15:53:25
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-17 00:24:48
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// single_ord_ary_idx = 0
void EmptyDeal()
{
    return;
}

// single_ord_ary_idx = 1，查询状态指令
void InquireDeal()
{
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 2，启动工作指令
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
    ReplyStateFrame(EventBoardState); // 回复帧
}

// single_ord_ary_idx = 3，套管检测指令
void CasingDeal()
{
    if (EventBoardState == IDLE_STAT)
    {
        _caseingDetectFlag = SET;
        EventBoardState = CASING_DETECT_STAT;
    }
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 4，上传模式数据指令，包括套管检测数据和测井模式数据
void DataUpDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        _modeDataSendFlag = SET; // 上传数据
    }
}

// single_ord_ary_idx = 5，模式数据确认指令
void ModeConfirmDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        EventBoardState = IDLE_STAT;
    }
    ReplyStateFrame(EventBoardState);
}

// single_ord_ary_idx = 6，储能短节连接指令，暂时未用
void K1K2EnDeal()
{
//    K1_EN = USER_ENABLE; // K1闭合（输出高）
//    K2_EN = USER_ENABLE; // K2闭合
//    HVState = HV_ON;     // 表明开通状态
//    ReplyNoVarFrame(DATA_K1K2_EN_F);
}

// TODO
// single_ord_ary_idx = 7，储能短节断开指令，暂时未用
void K1K2DisDeal()
{
//    K1_DIS = USER_DISABLE;
//    K2_DIS = USER_DISABLE;
//    HVState = HV_OFF;
//    ReplyNoVarFrame(DATA_K1K2_DIS_F);
}

// single_ord_ary_idx = 8，储能短节状态判断指令
void HVStateDeal()
{
    ReplySingleVarFrame(DATA_HVState_F, HVState);
}

// single_ord_ary_idx = 9，系统自检测指令
void SysCheckDeal()
{
    Uint16 retData = 0;
    TIMER_DATA = 1; //1个计数位
    TIMER_START = 0x1;
    Delay(100);

    if (GpioDataRegs.GPADAT.bit.GPIOA9 != 1)
        retData = 0x20;
    TIMER_STOP = 0x2;

    ReplySingleVarFrame(DATA_SysCheck_F, retData);
}

// single_ord_ary_idx = 10，PAPS数据上传指令
void PAPSDataUpDeal()
{
    if (EventBoardState == ACQ_FIN_STAT)
    {
        _PAPSUpDataFlag = SET;
    }
}
