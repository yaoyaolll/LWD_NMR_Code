/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// SCIA_interrupt.c
Uint16 SciaDataEven;
Uint16 BufferSciaDataH;
Uint16 BufferSciaDataL;
Uint16 BufferSciaDataAll;
Uint16 SciaRecFlag = 0;

// ׼����������ʱΪ1������Ϊ0
unsigned int SciaTx_Ready(void)   
{
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
		return(1);
	else
		return(0);
}

//׼����������ʱΪ1������Ϊ0
unsigned int SciaRx_Ready(void)   
{
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
		return(1);
	else
		return(0);
}

// �̶�/�⾮ģʽ���ݻظ�֡
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
	SendTempPt = (Uint16*)(startAddr);
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	for (SendCnt=0;SaveCnt<dataLen;SendCnt++)
	{
		while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = *SendTempPt++;
	}
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ��ѯ״ָ̬��Ļظ�֡
void ReplyStateFrame(Uint16 state)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = REPLY_STATE_F >> 8;

	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = state;      		// ����״̬
	
	CheckSum += REPLY_STATE_F;
	CheckSum += 3;
	CheckSum += state;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // ����CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA����Ϊ����״̬
}

// ����������ָ��Ļظ�֡
void ReplyDownTableFrame(Uint16 lastCheckSum)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = REPLY_DOWN_TABLE_F;            
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = lastCheckSum;      		// ָ���CheckSum
	
	CheckSum += REPLY_STATE_F;
	CheckSum += 3;
	CheckSum += lastCheckSum;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // ����CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA����Ϊ����״̬
}

// �������ϴ�ָ��Ļظ�֡
void ReplyUpTableFrame(Uint16 tableID)
{
	Uint16* addr;
	Uint16 len = 0;
	Uint16 CheckSum = 0;
	int i = 0;
	if (tableID == 2)		// �̶�ģʽ������
	{
		addr = (Uint16*)0x8002;
	}
	else if (tableID == 3) 	// �⾮ģʽ������
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

// �׹ܼ����������ʱ�Ļظ�֡
void ReplyCasingFrame()
{

}

// �׹ܼ�������쳣ʱ�Ļظ�֡
void ReplyCasingErrFrame()
{
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = 0x9996;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ���������Ļظ�֡�������ڴ��ܶ̽��жϺ�ϵͳ�Լ��ָ����
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = frameHead;            
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = var;      			// ����״̬
	
	CheckSum += frameHead;
	CheckSum += 3;
	CheckSum += var;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // ����CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA����Ϊ����״̬
}

void SciaSendOneWord(Uint16 data)
{
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = data;              // ��������
	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;    // SCIA����Ϊ����״̬
}

interrupt void SCIRXINTA_ISR(void)     // SCI-A�����жϺ���
{
	//BufferSciaDate=SciaRegs.SCIRXBUF.all;	//��8λ����
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
		BufferSciaDataAll = (BufferSciaDataH<<8) | BufferSciaDataL;   	// ��ȡ���ذ巢�͹�����16λ����
		SciaRecFlag = 1;    											// ���յ�16λ���ı�־
	}

	// ���յ�16λ����
	if (SciaRecFlag)
	{
		if	(BufferSciaDataAll==DATA_DOWN_TABLE_F || DownTableFlag==SET)           //���ز���������
		{
			DownloadTable(BufferSciaDataAll);
		}
		
		else if	(BufferSciaDataAll==DATA_UP_TABLE_F || RecSendTableFlag==SET)     //�ϴ�����������
		{
		    RecUpTableCommand(BufferSciaDataAll);
		}
		
		else if (BufferSciaDataAll == DATA_INQUIRE_F)			// ��ѯ״ָ̬��
		{
			ReplyStateFrame(EventBoardState);
		}
		
		else if	(BufferSciaDataAll == DATA_OPERATION_F)         // ��������ָ��
		{
			if (EventBoardState == IDLE_STAT)
			{
				// �¶ȼ�������Ƶ��
				
				
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
			ReplyStateFrame(EventBoardState);		// �ظ�֡
		}
		
		else if (BufferSciaDataAll == DATA_CASING_F)		// �׹ܼ��ָ��
		{
			if (EventBoardState == IDLE_STAT)
			{
				_caseingDetectFlag = SET;
				EventBoardState = CASING_DETECT_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_OPERATION_F)		// ��������ָ��
		{
			if (EventBoardState == IDLE_STAT)
			{
				_operationFlag = SET;
				EventBoardState = OPERATION_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_UP_MODE_F)		// �ϴ�ģʽ����ָ������׹ܼ�����ݺͲ⾮ģʽ����
		{
			if (EventBoardState == ACQ_FIN_STAT)
			{
				_modeDataSendFlag = SET;		// �ϴ�����
			}
		}
		
		else if (BufferSciaDataAll == DATA_MODE_CONFIRM_F)	// ģʽ����ȷ��ָ��
		{
			if (EventBoardState == ACQ_FIN_STAT)
			{
				EventBoardState = IDLE_STAT;
			}
			ReplyStateFrame(EventBoardState);
		}
		
		else if (BufferSciaDataAll == DATA_K1K2_EN_F)		// ���ܶ̽�����ָ��
		{
			K1_EN = USER_ENABLE;	// K1�պϣ�����ߣ�
			K2_EN = USER_ENABLE;	// K2�պ�
			HVState = HV_ON;		// ������ͨ״̬
			SciaSendData(DATA_K1K2_EN_F);
		}
		
		else if (BufferSciaDataAll == DATA_K1K2_DIS_F)		// ���ܶ̽ڶϿ�ָ��
		{
		    K1_DIS = USER_DISABLE;
		    K2_DIS = USER_DISABLE;
		    HVState = HV_OFF;
			SciaSendData(DATA_K1K2_DIS_F);
		}
		
		else if (BufferSciaDataAll == DATA_HVState_F)		// ���ܶ̽�״̬�ж�ָ��
		{
			ReplySingleVarFrame(DATA_HVState_F, HVState);
		}
		
		else if (BufferSciaDataAll == DATA_SysCheck_F)		// ϵͳ�Լ��ָ��
		{
			Uint16 retData = 0;
			TIMER_DATA = 1;   //1������λ
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
//		SciaRegs.SCICTL1.bit.SLEEP = 1;			//������ɣ����� 485 ������ ��ַ
	return;
}

