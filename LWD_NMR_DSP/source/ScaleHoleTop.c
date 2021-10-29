/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:31:40
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:11:20
 */
/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop, "secureRamFuncs");

//�̶�������
void ScaleHoleModeTop(void)
{
	// ��ģʽ�µļ̵���������·���Ƶ�ʼ���õ�
	RelayCode = CalRelayFromFre(CenterFreq);

    Uint16 QValue;
	// 20201016���δ˴�����
	/*if(ScaleModeFlag==SET)//���̶�
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}*/
	// ���̶�ʱTEĬ��Ϊ10����϶�ȿ̶�ʱĬ��Ϊ6
	// ���̶�ʱNEĬ��Ϊ60����϶�ȿ̶�ʱĬ��Ϊ150
	Tes = (Uint32)100 * Calib_TE * FPGA_COUNT;
	Tel = Tes; //��TEת��Ϊ10ns��λ��FPGA����ֵ
	Ne = Calib_NE;
	ScaleMn = 1;
	ScaleM = 0;

	ToMSNoiseAddr = SCALETABLE_START + 5;
	ToMSSignalAddr = SCALETABLE_START + 8;
	EchoStorAddr = SCALETABLE_START + 21;
	Pulse90StoreAddr = SCALETABLE_START + 2 * Ne + 21;
	PulseF180StoreAddr = SCALETABLE_START + 2 * Ne + 22;
	PulseL180StoreAddr = SCALETABLE_START + 2 * Ne + 23;

    RelayOpen(RelayCode);

	//StartS1msModule(25000);
	MiniScan(CenterFreq, ToMSNoiseAddr, ToMSSignalAddr); //miniɨƵ

	DCWorkOnce(CenterFreq); //�̶�

    RelayClose(RelayCode);


    // ����Qֵ
    QValue = CalQValue(CenterFreq, SCANTABLE_START + 8);

	//�洢
	if (ScaleModeFlag == SET) //���̶�ģʽ
	{
		SaveNTempPt = (int *)(SCALETABLE_START);
		*SaveNTempPt++ = REPLY_MODE_DATA_F; // ����ͷ
		*SaveNTempPt++ = 2 * Ne + 24;		// ����
		*SaveNTempPt++ = EVENT_BOARD_ID;	// �ӻ���ʶ
		*SaveNTempPt++ = 0x0009;			// ����ģʽ
		*SaveNTempPt = CenterFreq;  		// ����Ƶ��

		SaveNTempPt = (int *)(SCALETABLE_START + 17);
		*SaveNTempPt++ = QValue;			   // Qֵ
		*SaveNTempPt++ = 0x294;		   // �ο���ֵ
		*SaveNTempPt++ = Width90Pulse; // 90��������
		SavePhaseWord();

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(SCALETABLE_START);
		int i = 0;
		for (; i < 2 * Ne + 24; ++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		PAPSEntry.last_well_mode = 0x0009;

		//SciaSendDataNWords(SCALETABLE_START, 2*Ne+24);    //�ϴ��̶Ƚ��
	}
	else // ��϶�ȿ̶���У��ģʽ
	{
		SaveNTempPt = (int *)(HOLETABLE_START);
		*SaveNTempPt++ = REPLY_MODE_DATA_F; // ����ͷ
		*SaveNTempPt++ = 2 * Ne + 24;		// ����
		*SaveNTempPt++ = EVENT_BOARD_ID;	// �ӻ���ʶ
		*SaveNTempPt++ = 0x000A;			// ����ģʽ
		*SaveNTempPt = CenterFreq;  		// ����Ƶ��

		SaveNTempPt = (int *)(HOLETABLE_START + 17);
		*SaveNTempPt++ = QValue;			   // Qֵ
		*SaveNTempPt++ = 0x294;		   // �ο���ֵ
		*SaveNTempPt++ = Width90Pulse; // 90��������
		SavePhaseWord();			   // �洢��λ

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(HOLETABLE_START);
		int i = 0;
		for (; i < 2 * Ne + 24; ++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		PAPSEntry.last_well_mode = 0x000A;

		//SciaSendDataNWords(HOLETABLE_START, 2*Ne+24);    //�ϴ��̶Ƚ��
	}

	modeDataSendLen = 2 * Ne + 25;

	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/
/*-----------------------------------------------------------------------------------------*/
