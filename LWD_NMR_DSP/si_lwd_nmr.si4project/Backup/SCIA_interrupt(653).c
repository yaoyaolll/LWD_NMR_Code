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

unsigned int SciaTx_Ready(void)   //׼����������ʱΪ1������Ϊ0
{
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
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
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 0xAA55;
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA����Ϊ����״̬
}

/****************************************************************************
*
*��    �ƣ�SciaRx_Ready()
*׼����������ʱΪ1������Ϊ0*/
unsigned int SciaRx_Ready(void)   
{
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
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
		if(BufferSciaDataAll==0x1328||DownTableFlag==1)              //���ر���������
		{
			DownloadTable(BufferSciaDataAll);
		}
		else if(BufferSciaDataAll==0x1428)     //�ϴ�����������
		{
			SendTableFlag = SET;
		}
		else if(BufferSciaDataAll==0x0328)         //����ģʽ
		{
//			while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9910;     //�ظ�

			SciaSendData(0x9910);           //�ظ�   ������

	   		WorkMode = *(Uint16 *)0x8001;           //��ȡ�����۲�ģʽѡ��Ĵ���
			CheckWorkMode();
			switch(WorkMode)
			{
				case 0x0001: SingleModeFlag	= SET;break;
				case 0x0002: PPModeFlag		= SET;break;
				case 0x0003: PPDIFModeFlag	= SET;break;
				case 0x0004: PPT1ModeFlag	= SET;break;
				case 0x0005: PPOFTWModeFlag	= SET;break;
				case 0x0006: PPShortModeFlag= SET;break;
				//case 0x0007: 	= SET;break;
				case 0x0008: ScanModeFlag	= SET;break;
				case 0x0009: ScaleModeFlag	= SET;break;
				case 0x000A: HoleModeFlag	= SET;break;
				case 0x000B: PulseAcqFlag	= SET;break;
				default: break;
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

