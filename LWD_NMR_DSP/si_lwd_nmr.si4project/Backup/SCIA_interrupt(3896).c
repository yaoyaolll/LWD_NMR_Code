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

// ���ذ��·�����֡֡ͷ���壬F means Frame
#define DATA_INQUIRE_F		0x999A	// ��ѯ״ָ̬��
#define DATA_DOWN_TABLE_F	0x1328	// ����������ָ��
#define DATA_UP_TABLE_F		0x1428	// �������ϴ�ָ��
#define DATA_OPERATION_F	0x999B	// ��������ָ��
#define	DATA_CASING_F		0x999C	// �׹ܼ��ָ��
#define	DATA_UP_MODE_F		0x999D	// ģʽ�����ϴ�ָ��
#define	DATA_MODE_CONFIRM_F	0x999E	// ģʽ����ȷ��ָ��

// �¼���ظ�֡֡ͷ���壬F means Frame
#define REPLY_STATE_F		0x9991	// ��ѯ״ָ̬��ظ�
#define REPLY_DOWN_TABLE_F 	0x9992	// ����������ָ��ظ�
#define	REPLY_UP_TABLE_F	0x9993	// �������ϴ�ָ��ظ�
#define REPLY_CASING_F		0x9994	// �׹ܼ������
#define REPLY_MODE_DATA_F	0x9995	// �̶Ȳ⾮ģʽ���ݻظ�
#define REPLY_CASING_ERR_F	0x9996	// �׹ܼ���쳣֡

unsigned int SciaTx_Ready(void)   //׼����������ʱΪ1������Ϊ0
{
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
		return(1);
	else
		return(0);
}

// ��ѯ״ָ̬��Ļظ�֡
void ReplyStateFrame(Uint16 state)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA����Ϊ����״̬
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = REPLY_STATE_F;            
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 3;              

	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = state;      		// ����״̬
	
	CheckSum += REPLY_STATE_F;
	CheckSum += 3;
	CheckSum += state;
	
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = CheckSum;          // ����CheckSum
	
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
}

// ����������ָ��Ļظ�֡
void ReplyDownTableFrame(Uint16 lastCheckSum)
{
	Uint16 CheckSum = 0;
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA����Ϊ����״̬
	
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
	
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
}

// �������ϴ�ָ��Ļظ�֡
void ReplyUpTableFrame(Uint16 tableID)
{
	Uin16* addr = NULL;
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

}

void SciaSendData(Uint16 data)
{
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA����Ϊ����״̬
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = data;              // ��������
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
}

void SciaSendDataNWords(Uint32 StartAddr,Uint32 DataNum)
{
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA����Ϊ����״̬
	SendTempPt = (Uint16 *)(StartAddr);
	for (SendCnt=0; SendCnt<DataNum; SendCnt++)
	{
		while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = *SendTempPt++;
	}
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
}

/*׼����������ʱΪ1������Ϊ0*/
unsigned int SciaRx_Ready(void)   
{
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
		return(1);
	else
		return(0);
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
		BufferSciaDataAll = (BufferSciaDataH<<8)|BufferSciaDataL;   //��ȡ���ذ巢�͹�����16λ����
		SciaRecFlag = 1;    							//���յ�16λ���ı�־
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
			RecSendTableCommand(BufferSciaDataAll);
		}
		else if (BufferSciaDataAll == DATA_INQUIRE_F)			// ��ѯ״ָ̬��
		{
			ReplyStateFrame(EventBoardState);
		}
		else if	(BufferSciaDataAll == DATA_OPERATION_F)         // ��������ָ��
		{
			if (EventBoardState == IDLE_STAT)
			{
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
				EventBoardState = OPERATION_STAT;
				EventBoardEvents = OPERATION_ORD_EVENT;
			}

			// �ظ�֡
			ReplyStateFrame(EventBoardState);
		}
		else if (BufferSciaDataAll == DATA_CASING_F)		// �׹ܼ��ָ��
		{
			if (EventBoardState == IDLE_STAT)
			{
				
				EventBoardState = CASING_DETECT_STAT;
			}
		}

		




		
		else if(BufferSciaDataAll==0x5028)              //���ܶ̽�����
		{
			K1_EN = USER_ENABLE;     //K1�պϣ�����ߣ�
			K2_EN = USER_ENABLE;     //K2�պ�
			HVState = HV_ON;  //������ͨ״̬

			SciaSendData(0x9922);

//			while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9922;     //�ظ�
		}
		else if(BufferSciaDataAll==0x9923)              //���ܶ̽ڶϿ�
		{
		    K1_DIS = USER_DISABLE;
		    K2_DIS = USER_DISABLE;
		    HVState = HV_OFF;

		    SciaSendData(0x9923);

//	        while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9923;     //�ظ�
		}
		else if(BufferSciaDataAll==0x9924)              //���ܶ̽��ж�
		{
			GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA����Ϊ����״̬
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0x9924;              // ��������
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = HVState;              // ��������
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0xAA55;              // ��������
			GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
		}
		else if(BufferSciaDataAll==0x9901)              //ϵͳ�Լ��
		{
			TIMER_DATA = 1;   //1������Ϊ
			TIMER_START = 0x1;
			Delay(60);

			if(GpioDataRegs.GPADAT.bit.GPIOA9==1)
			{
//				while(McbspaRegs.SPCR2.bit.XRDY==0)
//				{ ; }
//				McbspaRegs.DXR1.all=0x0;
				SciaSendData(0);
			}
			else
			{
//				while(McbspaRegs.SPCR2.bit.XRDY==0)
//				{ ; }
//				McbspaRegs.DXR1.all=0x0020;
				SciaSendData(0x0020);
			}
			TIMER_STOP = 0x2;
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

