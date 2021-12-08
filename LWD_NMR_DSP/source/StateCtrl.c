/*
 * @Descripttion: 状态控制
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-01 09:25:44
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 11:51:13
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(IdleStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(CasDctStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(OperaStateCtl, "secureRamFuncs");
#pragma CODE_SECTION(AcqFinStateCtl, "secureRamFuncs");

void IdleStateCtl(void)
{
	// 上传数据表
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
		CheckReadTable();
		CasingDetectTop();
		
		_caseingDetectFlag = CLEAR;
		EventBoardState = ACQ_FIN_STAT;
	}
}

void OperaStateCtl(void)
{
    // 使用下发温度计算发射频率和继电器控制码，在模式工作之前一定要确保温度下发完成
	// 其他模式下不使用温度计算出的发射频率和继电器控制码
	// 继电器控制码和频率是一一对应的

	if (_operationFlag == SET)
	{
//		_casingOrOperaFlag = CLEAR;
		
		// if (CasingDetectOnce())
		// {
//			_casingDetectErrFlag = CLEAR;

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

			// 调谐刻度模式，模式字0x0007
			else if (TuningModeFlag == SET)
			{
				CheckReadTable();
				TuningModeTop();
				TuningModeFlag = CLEAR;
			}
			// 仪器扫频模式，模式字0x0008
			else if(ScanModeFlag==SET)
			{
				CheckReadTable();
 				ScanModeTop();
				ScanModeFlag	= CLEAR;
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
		// }
		// else
		// 	_casingDetectErrFlag = SET;			// 套管检测异常
		
		_operationFlag = CLEAR;
		EventBoardState = ACQ_FIN_STAT;
	}
}

void AcqFinStateCtl(void)
{
	// 模式数据上传
	if (_modeDataSendFlag == SET)
	{
//	    TODO: 频率优选和套管检测之后的判断在主控板做，事件板仅仅采集数据
//		if (_casingOrOperaFlag == SET)		    // CASING_DETECT模式
//		{
//			ReplyModeDataFrame(SCANTABLE_START, modeDataSendLen);
//		}
//		else								    // OPERATION模式
//		{
//			if (_casingDetectErrFlag == SET)	// 套管检测异常
//				ReplyCasingErrFrame();
//			else								// 套管检测正常
//				ReplyModeDataFrame(SCANTABLE_START, modeDataSendLen);
//		}
	    ReplyModeDataFrame(SCANTABLE_START, modeDataSendLen);
		_modeDataSendFlag = CLEAR;
	}

	// PAPS数据上传
	if (_PAPSUpDataFlag == SET)
	{
	    Uint16* PAPS_data_frame_pt = (Uint16*)(PAPSTABLE_START);
	    Uint16 dataSendLen;
		PAPSTop();
		// 从地址获取数据发送长度
		dataSendLen = *(PAPS_data_frame_pt + 1) + 1;
		ReplyModeDataFrame(PAPSTABLE_START, dataSendLen);
		_PAPSUpDataFlag = CLEAR;
	}
}
