/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop,"Datatable");

//�̶�������
void ScaleHoleModeTop(void)
{          
	if(ScaleModeFlag==SET)//���̶�
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}     
	Tes	= (Uint32)100 * ScaleTe * FPGA_COUNT;
	Tel	= Tes;  //��TEת��Ϊ10ns��λ��FPGA����ֵ
	Ne	= ScaleNe;
	ScaleMn	= 1;
	ScaleM	= 0;   
	for (ZeroOne=0;ZeroOne<2;ZeroOne++)
	{	
		for (ScaleCnt=1;ScaleCnt<9;ScaleCnt+=2)
		{     
			BandCnt	= ScaleCnt + ZeroOne;
			if(BandCnt==2)//��ʱ
			{
				StartS1msModule(25000);
			}
			else
			{
				StartS1msModule(1000);
			}
			
			RELAY_ON_CLOSE	= RelayAry[BandCnt];   //Ƶ��1�̵����պ�
			Delay(120);                       
			RELAY_ON_CLOSE	= 0x0000;
	
			ToMSFreq		= FreqAry[BandCnt];
			if(ScaleModeFlag==SET)//���̶�
			{
				ToMSNoiseAddr	= SCALETABLE_START+16*Ne+3*BandCnt+73;
				ToMSSignalAddr	= SCALETABLE_START+16*Ne+9*BandCnt-6;
			}
			else//��϶�ȿ̶�
			{
				ToMSNoiseAddr	= HOLETABLE_START+16*Ne+3*BandCnt+80;
				ToMSSignalAddr	= HOLETABLE_START+16*Ne+9*BandCnt+1;
			}		                                                                              
			MiniScan(ToMSFreq,ToMSNoiseAddr,ToMSSignalAddr);//miniɨƵ

			if(ScaleModeFlag==SET)//���̶�
			{
				Pulse90StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+99;
				PulseF180StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+107;
				PulseL180StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+115;
				EchoStorAddr		= SCALETABLE_START+2*Ne*(BandCnt-1)+3;
			}
			else
			{
				Pulse90StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+106;
				PulseF180StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+114;
				PulseL180StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+122;
				EchoStorAddr		= HOLETABLE_START+2*Ne*(BandCnt-1)+10;
			}
			DCWorkOnce(BandCnt); //�̶�
      
			RELAY_ON_CLOSE = RelayAry[BandCnt]<<8;   //Ƶ��1�̵����Ͽ�
			Delay(120);            
			RELAY_ON_CLOSE = 0x0000;
		} 
	}                  
//�洢
	if(ScaleModeFlag==SET)   //�̶�
	{    
		SaveNTempPt	= (int *)(SCALETABLE_START);
		*SaveNTempPt= 0x990A;
		SaveNTempPt++;
		*SaveNTempPt= NintyWidthAry[1]; //����F1����Ƶ���µ�90��������
		SaveNTempPt++;
		if(PhaseFlag==POSITIVE)
		{
			*SaveNTempPt	= 0x0; 
		}
		else
		{
			*SaveNTempPt	= 0x1111; 
		}
		SaveNTempPt	= (int *)(SCALETABLE_START+16*Ne+75);
		*SaveNTempPt= 0x294;//����ο��̶��źŷ�ֵ
		McbspSendData(SCALETABLE_START,16*Ne+124);//�ϴ��̶Ƚ��
	}     
	else//��϶��
	{
		SaveNTempPt	= (int *)(HOLETABLE_START);
		*SaveNTempPt= 0x990B;
		SaveNTempPt++;
		for(SaveCnt=1;SaveCnt<9;SaveCnt++)//�ֱ�洢F1~F8����Ƶ����90��������
		{
			*SaveNTempPt= NintyWidthAry[SaveCnt];
			SaveNTempPt++;		
		}   
		if(PhaseFlag==SET)
		{
			*SaveNTempPt	= 0x0; 
		}
		else
		{
			*SaveNTempPt	= 0x1111; 
		}
		SaveNTempPt	= (int *)(HOLETABLE_START+16*Ne+82);
		*SaveNTempPt = 0x294;//����ο��̶��źŷ�ֵ
	    McbspSendData(HOLETABLE_START,16*Ne+131);//�ϴ��̶Ƚ��
	}             
	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  



