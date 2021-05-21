/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// SCIA_interrupt.c
Uint16 SciaDataEven;
Uint16 BufferSciaDataH;
Uint16 BufferSciaDataL;
Uint16 BufferSciaDataAll;
Uint16 SciaRecFlag = 0;

// 准备发送数据时为1，否则为0
unsigned int SciaTx_Ready(void)   
{
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
		return(1);
	else
		return(0);
}

//准备接收数据时为1，否则为0
unsigned int SciaRx_Ready(void)   
{
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
		return(1);
	else
		return(0);
}

// 刻度/测井模式数据回复帧
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
	SendTempPt = (Uint16*)(startAddr);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	for (SendCnt=0;SaveCnt<dataLen;SendCnt++)
	{
		while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = *SendTempPt++;
	}
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 查询状态指令的回复帧
void ReplyStateFrame(Uint16 state)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = REPLY_STATE_F >> 8;

	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = state;      		// 发送状态
	
	CheckSum += REPLY_STATE_F;
	CheckSum += 3;
	CheckSum += state;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // 发送CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA设置为接收状态
}

// 参数表下载指令的回复帧
void ReplyDownTableFrame(Uint16 lastCheckSum)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = REPLY_DOWN_TABLE_F;            
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = lastCheckSum;      		// 指令的CheckSum
	
	CheckSum += REPLY_STATE_F;
	CheckSum += 3;
	CheckSum += lastCheckSum;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // 发送CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA设置为接收状态
}

// 参数表上传指令的回复帧
void ReplyUpTableFrame(Uint16 tableID)
{
	Uint16* addr;
	Uint16 len = 0;
	Uint16 CheckSum = 0;
	int i = 0;
	if (tableID == 2)		// 刻度模式参数表
	{
		addr = (Uint16*)0x8002;
	}
	else if (tableID == 3) 	// 测井模式参数表
	{
		addr = (Uint16*)0x8017;
	}
	len = *addr;

	while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = REPLY_UP_TABLE_F;
	for (i=0;i<len-1;++i)
	{
		while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = *addr;
		CheckSum += *addr;
		addr++;
	}
	while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = CheckSum;
	*addr = CheckSum;
}

// 套管检测数据正常时的回复帧
void ReplyCasingFrame()
{

}

// 套管检测数据异常时的回复帧
void ReplyCasingErrFrame()
{
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = 0x9996;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 单个变量的回复帧，可用于储能短节判断和系统自检测指令中
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = frameHead;            
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = var;      			// 发送状态
	
	CheckSum += frameHead;
	CheckSum += 3;
	CheckSum += var;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // 发送CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA设置为接收状态
}

void SciaSendOneWord(Uint16 data)
{
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = data;              // 发送数据
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA设置为接收状态
}

interrupt void SCIRXINTA_ISR(void)     // SCI-A接收中断函数
{
	//BufferSciaDate=SciaRegs.SCIRXBUF.all;	//读8位数据
	if(SciaDataEven == 0)
	{
		SciaDataEven = 1;
		BufferSciaDataH = SciaRegs.SCIRXBUF.bit.RXDT;
		SciaRecFlag = 0;
	}
	else
	{
		SciaDataEven = 0;
		BufferSciaDataL = SciaRegs.SCIRXBUF.bit.RXDT;
		BufferSciaDataAll = (BufferSciaDataH<<8) | BufferSciaDataL;   	// 读取主控板发送过来的16位数据
		SciaRecFlag = 1;    											// 接收到16位数的标志
	}

	// 接收到16位数据
	if (SciaRecFlag)
	{
		if	(BufferSciaDataAll==DATA_DOWN_TABLE_F || DownTableFlag==SET)           //下载参数表命令
		{
			DownloadTable(BufferSciaDataAll);
		}
		
		else if	(BufferSciaDataAll==DATA_UP_TABLE_F || RecSendTableFlag==SET)     //上传参数表命令
		{
		    RecUpTableCommand(BufferSciaDataAll);
		}
		
		else if (BufferSciaDataAll == DATA_INQUIRE_F)			// 查询状态指令
		{
			ReplyStateFrame(EventBoardState);
		}
		
		else if	(BufferSciaDataAll == DATA_OPERATION_F)         // 启动工作指令
		{
			if (EventBoardState == IDLE_STAT)
			{
				// 温度计算中心频率
				
				
				CheckWorkMode();
				switch(WorkMode)
				{
					case 0x0001: SingleModeFlag	= SET;break;
					case 0x0002: PPModeFlag		= SET;break;
					case 0x0003: PPDIFModeFlag	= SET;break;
					case 0x0004: PPT1ModeFlag	= SET;break;
					case 0x0005: PPOFTWModeFlag	= SET;break;
					case 0x0006: PPShortModeFlag= SET;break;
					
					case 0x0008: ScanModeFlag	= SET;break;
					case 0x0009: ScaleModeFlag	= SET;break;
					case 0x000A: HoleModeFlag	= SET;break;
					case 0x000B: PulseAcqFlag	= SET;break;
					default: break;
				}
				_operationFlag = SET;
				EventBoardState = OPERATION_STAT;
			}
			ReplyStateFrame(EventBoardState);		// 回复帧
		}
		
		else if (BufferSciaDataAll == DATA_CASING_F)		// 套管检测指令
		{
			if (EventBoardState == IDLE_STAT)
			{
				_caseingDetectFlag = SET;
				EventBoardState = CASING_DETECT_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_OPERATION_F)		// 启动工作指令
		{
			if (EventBoardState == IDLE_STAT)
			{
				_operationFlag = SET;
				EventBoardState = OPERATION_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_UP_MODE_F)		// 上传模式数据指令，包括套管检测数据和测井模式数据
		{
			if (EventBoardState == ACQ_FIN_STAT)
			{
				_modeDataSendFlag = SET;		// 上传数据
			}
		}
		
		else if (BufferSciaDataAll == DATA_MODE_CONFIRM_F)	// 模式数据确认指令
		{
			if (EventBoardState == ACQ_FIN_STAT)
			{
				EventBoardState = IDLE_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_K1K2_EN_F)		// 储能短节连接指令
		{
			K1_EN = USER_ENABLE;	// K1闭合（输出高）
			K2_EN = USER_ENABLE;	// K2闭合
			HVState = HV_ON;		// 表明开通状态
			SciaSendData(DATA_K1K2_EN_F);
		}
		
		else if (BufferSciaDataAll == DATA_K1K2_DIS_F)		// 储能短节断开指令
		{
		    K1_DIS = USER_DISABLE;
		    K2_DIS = USER_DISABLE;
		    HVState = HV_OFF;
			SciaSendData(DATA_K1K2_DIS_F);
		}
		
		else if (BufferSciaDataAll == DATA_HVState_F)		// 储能短节状态判断指令
		{
			ReplySingleVarFrame(DATA_HVState_F, HVState);
		}
		
		else if (BufferSciaDataAll == DATA_SysCheck_F)		// 系统自检测指令
		{
			Uint16 retData = 0;
			TIMER_DATA = 1;   //1个计数位
			TIMER_START = 0x1;
			Delay(60);

			if(GpioDataRegs.GPADAT.bit.GPIOA9 != 1)
				retData = 0x20;
			TIMER_STOP = 0x2;
			
			ReplySingleVarFrame(DATA_SysCheck_F, retData);
		}
	}

    SciaRegs.SCIFFRX.bit.RXFIFORESET=0;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

//	GpioDataRegs.GPFDAT.bit.GPIOF11=1;
	EINT;
//		SciaRegs.SCICTL1.bit.SLEEP = 1;			//更改完成，结束 485 总线上 地址
	return;
}

