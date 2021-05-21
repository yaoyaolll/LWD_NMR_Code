/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"
//Uint16 temp[100];
//Uint16 itemp;

interrupt void MRINTA_ISR1(void)
{    
	McbspRcvBuf	= McbspaRegs.DRR1.all;   //��ȡ���͹���������   
//	temp[itemp]=McbspRcvBuf;
//	itemp++;
	if(McbspRcvBuf==0x9931||DownTableFlag==1)              //���ر���������
	{
		DownloadTable(McbspRcvBuf); 
	}   
	else if(McbspRcvBuf==0x9921)     //�ϴ�����������
	{    
      SendTableFlag = SET; 
	}
	else if(McbspRcvBuf==0x9910)         //����ģʽ
	{   
		while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{ ; }
		McbspaRegs.DXR1.all=0x9910;     //�ظ�
   		WorkMode = *(Uint16 *)0x8001;           //��ȡ�����۲�ģʽѡ��Ĵ��� 
		CheckWorkMode();
		switch(WorkMode)
		{
			case 0x0001: SingleModeFlag	= SET;break;
			case 0x0002: flag_pp3		= SET;break;
			case 0x0003: PP6ModeFlag	= SET;break;
			case 0x0004: Oil3ModeFlag	= SET;break;
			case 0x0005: PPHOIL6FFlag	= SET;break;
			case 0x0006: FBW2FFlag		= SET;break;
			case 0x0007: Gas6ModeFlag	= SET;break;
			case 0x0008: Gas6_2ModeFlag	= SET;break;
			case 0x0009: ScanModeFlag	= SET;break;
			case 0x000A: ScaleModeFlag	= SET;break;
			case 0x000B: HoleModeFlag	= SET;break;
			case 0x000C: PulseAcqFlag	= SET;break;
			case 0x000D: PPLOIL6FFlag	= SET;break;
			case 0x000E: HRT1T22FFlag	= SET;break;
			case 0x000F: PPHOIL6F_2Flag	= SET;break;
			case 0x0011: P3D6FFlag		= SET;break;
			case 0x0010: ST2DFlag		= SET;break;
			case 0x0020: DT2DFlag		= SET;break;
			case 0x0030: MT2DFlag		= SET;break;
			case 0x0040: ST1T2Flag		= SET;break;			
			case 0x0060: ST12DFlag		= SET;break;
			case 0x0070: DFT1T2DFlag	= SET;break;
			default: break;
		}
	}
	else if(McbspRcvBuf==0x9922)              //���ܶ̽�����
	{
		K1_EN = USER_ENABLE;     //K1�պϣ�����ߣ�
		K2_EN = USER_ENABLE;     //K2�պ�  
		HVState = HV_ON;  //������ͨ״̬       
		while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{ ; }
		McbspaRegs.DXR1.all=0x9922;     //�ظ�
	}   
	else if(McbspRcvBuf==0x9923)              //���ܶ̽ڶϿ�
	{
	    K1_DIS = USER_DISABLE;
	    K2_DIS = USER_DISABLE;
	    HVState = HV_OFF;
        while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{ ; }
		McbspaRegs.DXR1.all=0x9923;     //�ظ�
	}
	else if(McbspRcvBuf==0x9924)              //���ܶ̽��ж�
	{
		while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{;  }
		McbspaRegs.DXR1.all=0x9924;     //�ظ�ͷ
		while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{ ; }
		McbspaRegs.DXR1.all=HVState;     //�ظ�״̬ 
		while(McbspaRegs.SPCR2.bit.XRDY==0)         
		{ ; }
		McbspaRegs.DXR1.all=0xAA55;     //�ظ�״̬ 
	}  
	else if(McbspRcvBuf==0x9901)              //ϵͳ�Լ��
	{
		TIMER_DATA = 1;   //1������Ϊ   
		TIMER_START = 0x1;
		Delay(60);
		if(GpioDataRegs.GPADAT.bit.GPIOA9==1)
		{
			while(McbspaRegs.SPCR2.bit.XRDY==0)         
			{ ; }
			McbspaRegs.DXR1.all=0x0;   
		}
		else
		{			
			while(McbspaRegs.SPCR2.bit.XRDY==0)         
			{ ; }
			McbspaRegs.DXR1.all=0x0020;    
		} 
		TIMER_STOP = 0x2;     
	}
	else
	{
		ChangeTableBuf	= McbspRcvBuf&0xfff0;
		if(ChangeTableBuf==0x9950||ChgTable995Flag==SET)
		{
			ChangeTable995(McbspRcvBuf);
		}
		else if(ChangeTableBuf==0x9960||ChgTable996Flag==SET)
		{
			ChangeTable996(McbspRcvBuf);
		}
		else if(ChangeTableBuf==0x9990||ChgTable999Flag==SET)
		{
			ChangeTable999(McbspRcvBuf);
		}
		else if(ChangeTableBuf==0x99A0||ChgTable99AFlag==SET)
		{
			ChangeTable99A(McbspRcvBuf);
		}
	}

	PieCtrlRegs.PIEACK.bit.ACK6 = 1;
	IER|=M_INT6;
	EINT;
	return;
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  
