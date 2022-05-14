/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-28 10:19:18
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 15:46:39
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"


#define PPOFTW_NE_1ADEFGH 1000
#define PPOFTW_NE_1C 50

Uint16 PPOFTWMiniNumAry = 7;

void PPOFTWModeTop(void)
{
	ScaleMn = 1;
	ScaleM = 0; //�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = 6 + PPOFTW_Nrept_1C; // 1A 1C 1D 1E 1F 1G 1H��106������
	//  �������ǻز���������2
	DataTotalNum = 2 * (PPOFTW_NE_1ADEFGH * 6 + PPOFTW_NE_1C * PPOFTW_Nrept_1C); // ��11000���ز���

    RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(15000);
	MiniScan(TransmitFre, MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	Pulse90StoreAddr = PPOFTW_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPOFTW_TABLE_START + (Uint32)21;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPOFTW_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPOFTW_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(TransmitFre);
	int i = 0;
	for (; i < PPOFTW_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPOFTW_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPOFTW_NE_1C;
		DCWorkOnce(TransmitFre);
	}

	// 1D
	StartS1msModule(PPOFTW_TW_1D);

	MiniScan(TransmitFre, MINITABLE_START + 34, MINITABLE_START + 25);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1C;
	DCWorkOnce(TransmitFre);

	// 1E
	StartS1msModule(PPOFTW_TW_1E);

	MiniScan(TransmitFre, MINITABLE_START + 46, MINITABLE_START + 37);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(TransmitFre);

	// 1F
	StartS1msModule(PPOFTW_TW_1F);

	MiniScan(TransmitFre, MINITABLE_START + 58, MINITABLE_START + 49);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(TransmitFre);

	// 1G
	StartS1msModule(PPOFTW_TW_1G);

	MiniScan(TransmitFre, MINITABLE_START + 70, MINITABLE_START + 61);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(TransmitFre);

	//1H
	StartS1msModule(PPOFTW_TW_1H);

	MiniScan(TransmitFre, MINITABLE_START + 82, MINITABLE_START + 73);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(TransmitFre);

    RelayClose(RelayCtrlCode);

	//��ش洢
	SaveNTempPt = (int *)PPOFTW_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // ����ͷ
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;				  // �ӻ���ʶ
	*SaveNTempPt++ = 0x0005;						  // ����ģʽ
	*SaveNTempPt = TransmitFre; 					  // ����Ƶ��

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 17);
	*SaveNTempPt++ = CalQValue(TransmitFre, PPOFTW_TABLE_START + 8);			   // Qֵ
	*SaveNTempPt++ = 0x294;		   // �ο���ֵ
	*SaveNTempPt++ = Width90Pulse; // 90��������
	SavePhaseWord();

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = (Uint16)b;  // ����Ƶ��
	*SaveNTempPt = (Uint16)CublicSplineInterpolation(x, y, b); // ����Ƶ�ʷ�ֵ

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(PPOFTW_TABLE_START + 8);
	StoreMiniAryPt = &PPOFTWMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPOFTW_TABLE_START);
	for (i = 0; i < 3 * EchoNum + DataTotalNum + 23; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3 * EchoNum + DataTotalNum + 24;

	//SciaSendDataNWords(PPOFTW_TABLE_START, 3*EchoNum+DataTotalNum+21);
	
	// PAPS���ݴ洢
	PAPSEntry.current_well_mode = 0x0005;
	PAPSEntry.echo_1A_num = PPOFTW_NE_1ADEFGH;
	PAPSEntry.echo_1A_addr = PPOFTW_TABLE_START + 21;
	PAPSEntry.echo_1C_num = PPOFTW_NE_1C;
	PAPSEntry.echo_1C_addr1 = PPOFTW_TABLE_START + 21 + 2 * PPOFTW_NE_1ADEFGH;	
	PAPSEntry.echo_1C_nrept = PPOFTW_Nrept_1C;
	StorgePAPSToFIFO(&PAPSEntry);

	ChangePhase();

	return;
}
