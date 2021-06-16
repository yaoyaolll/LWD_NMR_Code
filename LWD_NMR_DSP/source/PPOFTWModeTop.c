/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-28 10:19:18
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-06-06 23:06:47
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

	// ��ʱ���ü̵����˿�Ϊ1
	// DCFreqSel = 1;
	// FreqAry[DCFreqSel] = CenterFreq;

    RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(15000);      // 15000+ms
	MiniScan(FreqAry[1], MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	Pulse90StoreAddr = PPOFTW_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPOFTW_TABLE_START + (Uint32)21;
	DCWorkOnce(1);

	// 1C
	StartS1msModule(PPOFTW_TW_1C);

	MiniScan(FreqAry[1], MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPOFTW_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(1);
	int i = 0;
	for (; i < PPOFTW_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPOFTW_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPOFTW_NE_1C;
		DCWorkOnce(1);
	}

	// 1D
	StartS1msModule(PPOFTW_TW_1D);

	MiniScan(FreqAry[1], MINITABLE_START + 34, MINITABLE_START + 25);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1C;
	DCWorkOnce(1);

	// 1E
	StartS1msModule(PPOFTW_TW_1E);

	MiniScan(FreqAry[1], MINITABLE_START + 46, MINITABLE_START + 37);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(1);

	// 1F
	StartS1msModule(PPOFTW_TW_1F);

	MiniScan(FreqAry[1], MINITABLE_START + 58, MINITABLE_START + 49);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(1);

	// 1G
	StartS1msModule(PPOFTW_TW_1G);

	MiniScan(FreqAry[1], MINITABLE_START + 70, MINITABLE_START + 61);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(1);

	//1H
	StartS1msModule(PPOFTW_TW_1H);

	MiniScan(FreqAry[1], MINITABLE_START + 82, MINITABLE_START + 73);

	Tes = (Uint32)100 * PPOFTW_TE_1ADEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(1);

    RelayClose(RelayCtrlCode);

	//��ش洢
	SaveNTempPt = (int *)PPOFTW_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // ����ͷ
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;				  // �ӻ���ʶ
	*SaveNTempPt++ = 0x0005;						  // ����ģʽ
	*SaveNTempPt = FreqAry[1] * 10;					  // ����Ƶ��

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 17);
	*SaveNTempPt++ = 0;			   // Qֵ
	*SaveNTempPt++ = 0x294;		   // �ο���ֵ
	*SaveNTempPt++ = Width90Pulse; // 90��������
	SavePhaseWord();

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = getCenterFreq();  // ����Ƶ��
	*SaveNTempPt = getCenterFreqAmp(); // ����Ƶ�ʷ�ֵ

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
	ChangePhase();
	return;
}
