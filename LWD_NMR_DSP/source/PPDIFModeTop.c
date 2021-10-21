/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-21 15:39:20
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 15:55:31
 */
/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#ifdef DEBUG
#pragma CODE_SECTION(PPDIFModeTop, "secureRamFuncs");
#endif

Uint16 PPDIFMiniNumAry = 4;

void PPDIFModeTop(void)
{
	ScaleMn = 1;
	ScaleM = 0; //�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = PPDIF_Nrept_1C * 2 + 2;										   // 1A 1B�ظ�һ�Σ�1C�ظ�64*2�Σ���130������
	DataTotalNum = 2 * (PPDIF_NE_1A1B * 2 + PPDIF_NE_1C * PPDIF_Nrept_1C * 2); // ��8400���ز���

	// ��ʱ���ü̵����˿�Ϊ1
	// DCFreqSel = 1;
	// FreqAry[DCFreqSel]  = TransmitFre;

	RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(TransmitFre, MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPDIF_TE_1A1B * FPGA_COUNT;
	Tel = Tes;
	Ne = PPDIF_NE_1A1B;
	Pulse90StoreAddr = PPDIF_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPDIF_TABLE_START + (Uint32)21;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPDIF_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 34, MINITABLE_START + 25);

	Tes = (Uint32)100 * PPDIF_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPDIF_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPDIF_NE_1A1B;
	DCWorkOnce(TransmitFre);
	int i = 0;
	for (; i < PPDIF_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPDIF_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPDIF_NE_1C;
		DCWorkOnce(TransmitFre);
	}

	// 1B
	StartS1msModule(PPDIF_TW_1B);

	MiniScan(TransmitFre, MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPDIF_TE_1A1B * FPGA_COUNT;
	Tel = Tes;
	Ne = PPDIF_NE_1A1B;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPDIF_NE_1C;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPDIF_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 46, MINITABLE_START + 37);

	Tes = (Uint32)100 * PPDIF_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPDIF_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPDIF_NE_1A1B;
	DCWorkOnce(TransmitFre);

	for (i = 0; i < PPDIF_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPDIF_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPDIF_NE_1C;
		DCWorkOnce(TransmitFre);
	}

	RelayClose(RelayCtrlCode);

	//ģʽ���ݴ洢
	SaveNTempPt = (int *)PPDIF_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // ����ͷ
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;				  // �ӻ���ʶ
	*SaveNTempPt++ = 0x0003;						  // ����ģʽ
	*SaveNTempPt++ = TransmitFre;				  // ����Ƶ��

	SaveNTempPt = (int *)(PPDIF_TABLE_START + 17);
	*SaveNTempPt++ = CalQValue(TransmitFre, PPDIF_TABLE_START + 8);			   // Qֵ
	*SaveNTempPt++ = 0x294;		   // �ο���ֵ
	*SaveNTempPt++ = Width90Pulse; // 90��������
	SavePhaseWord();

	SaveNTempPt = (int *)(PPM_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = (Uint16)b;  // ����Ƶ��
	*SaveNTempPt = (Uint16)CublicSplineInterpolation(x, y, b); // ����Ƶ�ʷ�ֵ

	SaveNTempPt = (int *)(PPDIF_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(PPDIF_TABLE_START + 8);
	StoreMiniAryPt = &PPDIFMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPDIF_TABLE_START);
	for (i = 0; i < 3 * EchoNum + DataTotalNum + 23; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3 * EchoNum + DataTotalNum + 24;

	//SciaSendDataNWords(PPDIF_TABLE_START, 3*EchoNum+DataTotalNum+21);

	// PAPS���ݴ洢
	PAPSEntry.current_well_mode = 0x0003;
	PAPSEntry.echo_1A_num = PPDIF_NE_1A1B;
	PAPSEntry.echo_1A_addr = PPDIF_TABLE_START + 21;
	PAPSEntry.echo_1C_num = PPDIF_NE_1C;
	PAPSEntry.echo_1C_addr1 = PPDIF_TABLE_START + 21 + 2 * PPDIF_NE_1A1B;	
	PAPSEntry.echo_1C_addr2 = PPDIF_TABLE_START + 21 + 4 * PPDIF_NE_1A1B + 2 * (PPDIF_Nrept_1C*PPDIF_NE_1C);
	PAPSEntry.echo_1C_nrept = PPDIF_Nrept_1C;
	StorgePAPSToFIFO(&PAPSEntry);
	
	ChangePhase();

	return;
}
