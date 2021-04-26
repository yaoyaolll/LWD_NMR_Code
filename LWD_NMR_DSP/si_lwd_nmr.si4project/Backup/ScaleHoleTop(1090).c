/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop,"Datatable");


//�̶�������
void ScaleHoleModeTop(void)
{
	// 20201016���δ˴�����
	/*if(ScaleModeFlag==SET)//���̶�
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}*/
	// ���̶�ʱTEĬ��Ϊ10����϶�ȿ̶�ʱĬ��Ϊ6
	// ���̶�ʱNEĬ��Ϊ60����϶�ȿ̶�ʱĬ��Ϊ150
	Tes	= (Uint32)100 * Calib_TE * FPGA_COUNT;
	Tel	= Tes;  //��TEת��Ϊ10ns��λ��FPGA����ֵ
	Ne	= Calib_NE;
	ScaleMn	= 1;
	ScaleM	= 0;

	ToMSNoiseAddr	= SCALETABLE_START + 4;
	ToMSSignalAddr	= SCALETABLE_START + 7;
	EchoStorAddr		= SCALETABLE_START+20;
	Pulse90StoreAddr	= SCALETABLE_START+2*Ne+20;
	PulseF180StoreAddr	= SCALETABLE_START+2*Ne+21;
	PulseL180StoreAddr	= SCALETABLE_START+2*Ne+22;

	
	RELAY_ON_CLOSE	= RelayAry[1];   //Ƶ��1�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE	= 0x0000;

	StartS1msModule(25000);
	MiniScan(CenterFreq, ToMSNoiseAddr, ToMSSignalAddr);//miniɨƵ

	FreqAry[1] = CenterFreq;
	DCWorkOnce(1); //�̶�

	RELAY_ON_CLOSE = RelayAry[1]<<8;   //Ƶ��1�̵����Ͽ�
	Delay(120);            
	RELAY_ON_CLOSE = 0x0000;


	//�洢
	if(ScaleModeFlag==SET)   //���̶�ģʽ
	{    
		SaveNTempPt	= (int *)(SCALETABLE_START);
		*SaveNTempPt++ = 0x9995;    		// ����ͷ
		*SaveNTempPt++ = 0x0009;   			// ����ģʽ
		*SaveNTempPt++ = 2*Ne+23;			// ����
		*SaveNTempPt = CenterFreq * 10; 	// ����Ƶ��

		SaveNTempPt = (int *)(SCALETABLE_START + 16);
		*SaveNTempPt++ = 0;          		// Qֵ
		*SaveNTempPt++ = 0x294;				// �ο���ֵ
		*SaveNTempPt++ = Width90Pulse;      // 90��������
		SavePhaseWord();

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(SCALETABLE_START);
		int i=0;
		for (;i<2*Ne+23;++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		SciaSendDataNWords(SCALETABLE_START, 2*Ne+24);    //�ϴ��̶Ƚ��
	}     
	else    // ��϶�ȿ̶���У��ģʽ
	{
		SaveNTempPt	= (int *)(HOLETABLE_START);
		*SaveNTempPt++ = 0x9995;    		// ����ͷ
		*SaveNTempPt++ = 0x000A;   			// ����ģʽ
		*SaveNTempPt++ = 2*Ne+23;			// ����
		*SaveNTempPt = CenterFreq * 10; 	// ����Ƶ��

		SaveNTempPt = (int *)(HOLETABLE_START + 16);
		*SaveNTempPt++ = 0;          		// Qֵ
		*SaveNTempPt++ = 0x294;				// �ο���ֵ
		*SaveNTempPt++ = Width90Pulse;      // 90��������
		SavePhaseWord();       // �洢��λ

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(HOLETABLE_START);
		int i=0;
		for (;i<2*Ne+23;++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		SciaSendDataNWords(HOLETABLE_START, 2*Ne+24);    //�ϴ��̶Ƚ��
	}             
	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  



