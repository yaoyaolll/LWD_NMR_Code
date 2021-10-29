/*----------------------------ͷ�ļ�---------------------------------------------*/
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

// ׼����������ʱΪ1������Ϊ0
unsigned int SciaTx_Ready(void)
{
	if (SciaRegs.SCICTL2.bit.TXRDY == 1)
		return (1);
	else
		return (0);
}

//׼����������ʱΪ1������Ϊ0
unsigned int SciaRx_Ready(void)
{
	if (SciaRegs.SCIRXST.bit.RXRDY == 1)
		return (1);
	else
		return (0);
}

// �˺�����Ҫ��GPIOF11���ʹ��
void SciaSendOneWord(Uint16 data)
{
	while (SciaTx_Ready() == 0)
	{
	}
	SciaRegs.SCITXBUF = data >> 8; // ���͸�8λ
	while (SciaTx_Ready() == 0)
	{
	}
	SciaRegs.SCITXBUF = data; // ���͵�8λ
}

// �̶�/�⾮ģʽ���ݻظ�֡
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
	SendTempPt = (Uint16 *)(startAddr);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
	for (SendCnt = 0; SendCnt < dataLen; SendCnt++)
	{
		SciaSendOneWord(*SendTempPt);
		SendTempPt++;
	}
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ��ѯ״ָ̬��Ļظ�֡
void ReplyStateFrame(Uint16 state)
{
	Uint16 CheckSum = 0;

	CheckSum += REPLY_STATE_F;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += state;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
	SciaSendOneWord(REPLY_STATE_F);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(state);
	SciaSendOneWord(CheckSum);
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// ����������ָ��Ļظ�֡
void ReplyLastCheckFrame(Uint16 frameHead, Uint16 lastCheckSum)
{
	Uint16 CheckSum = 0;
	CheckSum += frameHead;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += lastCheckSum;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
	SciaSendOneWord(frameHead);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(lastCheckSum);
	SciaSendOneWord(CheckSum);
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// �������ϴ�ָ��Ļظ�֡
void ReplyUpTableFrame(Uint16 tableID)
{
	Uint16 *addr;
	Uint16 len = 0;
	Uint16 CheckSum = 0;
	int i = 0;
	if (tableID == 1)           // �̶Ȳ�����
	{
	    addr = (Uint16 *)0x8057;
	}
	else if (tableID == 2) 		    // �̶�ģʽ������
	{
		addr = (Uint16 *)0x8002;
	}
	else if (tableID == 3) 	    // �⾮ģʽ������
	{
		addr = (Uint16 *)0x8018;
	}
	else                        // ��ֹ��
	{
	    return;
	}

	len = *addr;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; 	// SCIA����Ϊ����״̬
	SciaSendOneWord(REPLY_UP_TABLE_F);	 	// ֡ͷ
	SciaSendOneWord(len + 1);
	SciaSendOneWord(EVENT_BOARD_ID); 		// �����ӻ���ʶ
	addr++;
	CheckSum = REPLY_UP_TABLE_F;
	CheckSum += (len + 1);
	CheckSum += EVENT_BOARD_ID;
	for (i = 0; i < len - 2; ++i) 			// �����������ͱ��ز�����ĩβ�洢��CheckSum
	{
		SciaSendOneWord(*addr);
		CheckSum += *addr;
		addr++;
	}

	SciaSendOneWord(CheckSum); 				// ���ݰ���CheckSum
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// �׹ܼ�������쳣ʱ�Ļظ�֡
void ReplyCasingErrFrame()
{
	Uint16 CheckSum = 0;
	CheckSum += REPLY_CASING_ERR_F;
	CheckSum += 3;
	CheckSum += EVENT_BOARD_ID;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
	SciaSendOneWord(REPLY_CASING_ERR_F);
	SciaSendOneWord(3);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(CheckSum);
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// �ظ��������ݵ�֡ͷ
void ReplyNoVarFrame(Uint16 frameHead)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(frameHead);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ���������Ļظ�֡�������ڴ��ܶ̽��жϺ�ϵͳ�Լ��ָ����
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
	Uint16 CheckSum = 0;

	CheckSum += frameHead;
	CheckSum += 4;
	CheckSum += EVENT_BOARD_ID;
	CheckSum += var;

	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
	SciaSendOneWord(frameHead);
	SciaSendOneWord(4);
	SciaSendOneWord(EVENT_BOARD_ID);
	SciaSendOneWord(var);
	SciaSendOneWord(CheckSum);
	// �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
	Delay(RS485_DELAY);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// RS485�жϴ�����
interrupt void SCIRXINTA_ISR(void) // SCI-A�����жϺ���
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
		BufferSciaDataAll = (BufferSciaDataH << 8) | BufferSciaDataL; // ��ȡ���ذ巢�͹�����16λ����
		SciaRecFlag = 1;											  // ���յ�16λ���ı�־
	}

	// ���յ�16λ����
	if (SciaRecFlag)
	{
		if (DownTableFlag == SET || BufferSciaDataAll == DATA_DOWN_TABLE_F) // ���ز���������
		{
			RecDownTableCommand(BufferSciaDataAll);
		}

		else if (RecSendTableFlag == SET || BufferSciaDataAll == DATA_UP_TABLE_F) // �ϴ�����������
		{
			RecUpTableCommand(BufferSciaDataAll);
		}

		else if (RecParamOrderFlag == SET || BufferSciaDataAll == DATA_Parameter_F) // ��Ҫ�����·�ָ��
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
	//		SciaRegs.SCICTL1.bit.SLEEP = 1;			//������ɣ����� 485 ������ ��ַ
	return;
}
