/*
 * @Descripttion: 下发单个指令（不带数据）的处理函数
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-05-31 15:53:25
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-05-31 17:25:18
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// 计算CheckSum是否正确
Uint16 CheckSumCal()
{
    Uint16 checkSum = 0;
    checkSum += SingleOrderData.frameHead;
    checkSum += SingleOrderData.len;
    checkSum += SingleOrderData.slaveID;

    if (checkSum == SingleOrderData.checkSum)
        return 1;
    return 0;
}

// SingleOrderAryChoice = 0
void EmptyDeal()
{
    return;
}

// SingleOrderAryChoice = 1，查询状态指令
void InquireDeal()
{
    if (CheckSumCal())
        ReplyStateFrame(EventBoardState);
}

// SingleOrderAryChoice = 2，启动工作指令
void OperationDeal()
{
    if (CheckSumCal())
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
}

// SingleOrderAryChoice = 3，套管检测指令
void CasingDeal()
{
    if (CheckSumCal())
    {
        if (EventBoardState == IDLE_STAT)
        {
            _caseingDetectFlag = SET;
            EventBoardState = CASING_DETECT_STAT;
        }
        ReplyStateFrame(EventBoardState);
    }
}

// SingleOrderAryChoice = 4，上传模式数据指令，包括套管检测数据和测井模式数据
void DataUpDeal()
{
    if (CheckSumCal())
    {
        if (EventBoardState == ACQ_FIN_STAT)
        {
            _modeDataSendFlag = SET; // 上传数据
        }
    }
}

// SingleOrderAryChoice = 5，模式数据确认指令
void ModeConfirmDeal()
{
    if (CheckSumCal())
    {
        if (EventBoardState == ACQ_FIN_STAT)
        {
            EventBoardState = IDLE_STAT;
        }
        ReplyStateFrame(EventBoardState);
    }
}

// SingleOrderAryChoice = 6，储能短节连接指令
void K1K2EnDeal()
{
    if (CheckSumCal())
    {
        K1_EN = USER_ENABLE; // K1闭合（输出高）
        K2_EN = USER_ENABLE; // K2闭合
        HVState = HV_ON;     // 表明开通状态
        ReplyNoVarFrame(DATA_K1K2_EN_F);
    }
}

// SingleOrderAryChoice = 7，储能短节断开指令
void K1K2DisDeal()
{
    if (CheckSumCal())
    {
        K1_DIS = USER_DISABLE;
        K2_DIS = USER_DISABLE;
        HVState = HV_OFF;
        ReplyNoVarFrame(DATA_K1K2_DIS_F);
    }
}

// SingleOrderAryChoice = 8，储能短节状态判断指令
void HVStateDeal()
{
    if (CheckSumCal())
    {
        ReplySingleVarFrame(DATA_HVState_F, HVState);
    }
}

// SingleOrderAryChoice = 9，系统自检测指令
void SysCheckDeal()
{
    if (CheckSumCal())
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
}

// SingleOrderAryChoice = 10，启动测试指令
void TestDeal()
{
    if (CheckSumCal())
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
            EventBoardState = TEST_STAT;
        }
        ReplyStateFrame(EventBoardState); // 回复帧
    }
}

// SingleOrderAryChoice = 11，启动刻度指令
void ScaleDeal()
{
    if (CheckSumCal())
    {
        if (EventBoardState == IDLE_STAT)
        {
            CheckWorkMode();
            switch (WorkMode)
            {
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
            default:                // 默认为扫频模式
                ScanModeFlag = SET;
                break;
            }
            EventBoardState = SCALE_STAT;
        }
        ReplyStateFrame(EventBoardState); // 回复帧
    }
}
