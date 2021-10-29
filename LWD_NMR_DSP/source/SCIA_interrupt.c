/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(SciaTx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SciaRx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SCIRXINTA_ISR, "secureRamFuncs");

// SCIA_interrupt.c
Uint16 SciaDataEven = 0;
Uint16 BufferSciaDataH;
Uint16 BufferSciaDataL;
Uint16 BufferSciaDataAll;
Uint16 SciaRecFlag = 0;

// 准备发送数据时为1，否则为0
unsigned int SciaTx_Ready(void)
{
	if (SciaRegs.SCICTL2.bit.TXRDY == 1)
		return (1);
	else
		return (0);
}

//准备接收数据时为1，否则为0
unsigned int SciaRx_Ready(void)
{
	if (SciaRegs.SCIRXST.bit.RXRDY == 1)
		return (1);
	else
		return (0);
}

// 此函数需要与GPIOF11配合使用
void SciaSendOneWord(Uint16 data)
{
	while (SciaTx_Ready() == 0)
	{
	}
	SciaRegs.SCITXBUF = data >> 8; // 发送高8位
	while (SciaTx_Ready() == 0)
	{
	}
	SciaRegs.SCITXBUF = data; // 发送低8位
}

// 刻度/测井模式数据回复帧
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
	SendTempPt = (Uint16 *)(startAddr);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
	for (SendCnt = 0; SendCnt < dataLen; SendCnt++)
	{
		SciaSendOneWord(*SendTempPt);
		SendTempPt++;
	}
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 查询状态指令的回复帧
void ReplyStateFrame(Uint16 state)
{
	Uint16 CheckSum = 0;

	CheckSum += REPLY_STATE_F;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += state;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
	SciaSendOneWord(REPLY_STATE_F);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(state);
	SciaSendOneWord(CheckSum);
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 参数表下载指令的回复帧
void ReplyLastCheckFrame(Uint16 frameHead, Uint16 lastCheckSum)
{
	Uint16 CheckSum = 0;
	CheckSum += frameHead;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += lastCheckSum;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
	SciaSendOneWord(frameHead);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(lastCheckSum);
	SciaSendOneWord(CheckSum);
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 参数表上传指令的回复帧
void ReplyUpTableFrame(Uint16 tableID)
{
	Uint16 *addr;
	Uint16 len = 0;
	Uint16 CheckSum = 0;
	int i = 0;
	if (tableID == 1)           // 刻度参数表
	{
	    addr = (Uint16 *)0x8057;
	}
	else if (tableID == 2) 		    // 刻度模式参数表
	{
		addr = (Uint16 *)0x8002;
	}
	else if (tableID == 3) 	    // 测井模式参数表
	{
		addr = (Uint16 *)0x8018;
	}
	else                        // 防止误发
	{
	    return;
	}

	len = *addr;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; 	// SCIA设置为发送状态
	SciaSendOneWord(REPLY_UP_TABLE_F);	 	// 帧头
	SciaSendOneWord(len + 1);
	SciaSendOneWord(EVENT_BOARD_ID); 		// 新增从机标识
	addr++;
	CheckSum = REPLY_UP_TABLE_F;
	CheckSum += (len + 1);
	CheckSum += EVENT_BOARD_ID;
	for (i = 0; i < len - 2; ++i) 			// 参数表，不发送本地参数表末尾存储的CheckSum
	{
		SciaSendOneWord(*addr);
		CheckSum += *addr;
		addr++;
	}

	SciaSendOneWord(CheckSum); 				// 数据包的CheckSum
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 套管检测数据异常时的回复帧
void ReplyCasingErrFrame()
{
	Uint16 CheckSum = 0;
	CheckSum += REPLY_CASING_ERR_F;
	CheckSum += 3;
	CheckSum += EVENT_BOARD_ID;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
	SciaSendOneWord(REPLY_CASING_ERR_F);
	SciaSendOneWord(3);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(CheckSum);
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 回复不带内容的帧头
void ReplyNoVarFrame(Uint16 frameHead)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(frameHead);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 单个变量的回复帧，可用于储能短节判断和系统自检测指令中
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
	Uint16 CheckSum = 0;

	CheckSum += frameHead;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += var;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
	SciaSendOneWord(frameHead);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(var);
	SciaSendOneWord(CheckSum);
	// 此处要加一定延时避免最后一个数据发不出去
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// RS485中断处理函数
interrupt void SCIRXINTA_ISR(void) // SCI-A接收中断函数
{
	if (SciaDataEven == 0)
	{
		SciaDataEven = 1;
		BufferSciaDataH = SciaRegs.SCIRXBUF.bit.RXDT;
		SciaRecFlag = 0;
	}
	else
	{
		SciaDataEven = 0;
		BufferSciaDataL = SciaRegs.SCIRXBUF.bit.RXDT;
		BufferSciaDataAll = (BufferSciaDataH << 8) | BufferSciaDataL; // 读取主控板发送过来的16位数据
		SciaRecFlag = 1;											  // 接收到16位数的标志
	}

	// 接收到16位数据
	if (SciaRecFlag)
	{
		if (DownTableFlag == SET || BufferSciaDataAll == DATA_DOWN_TABLE_F) // 下载参数表命令
		{
			RecDownTableCommand(BufferSciaDataAll);
		}

		else if (RecSendTableFlag == SET || BufferSciaDataAll == DATA_UP_TABLE_F) // 上传参数表命令
		{
			RecUpTableCommand(BufferSciaDataAll);
		}

		else if (RecParamOrderFlag == SET || BufferSciaDataAll == DATA_Parameter_F) // 重要参数下发指令
		{
		    RecParameterCommand(BufferSciaDataAll);
		}

		else if (RecK1K2CtrlFlag == SET || BufferSciaDataAll == DATA_K1K2_EN_F)
		{
		    RecK1K2CtrlCommand(BufferSciaDataAll);       // 20211027, K1K2 control cmd add a K1K2 member.
		}

		else if (RecSingleOrderFlag == SET || (BufferSciaDataAll>=DATA_INQUIRE_F && BufferSciaDataAll<=DATA_PAPS_F))
		{
			RecSingleOrderCommand(BufferSciaDataAll);
		}
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

	EINT;
	//		SciaRegs.SCICTL1.bit.SLEEP = 1;			//更改完成，结束 485 总线上 地址
	return;
}
