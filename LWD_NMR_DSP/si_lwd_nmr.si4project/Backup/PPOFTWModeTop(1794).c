/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPOFTWModeTop,"Datatable");

#define PPOFTW_NE_1ADEFGH 1000
#define PPOFTW_NE_1C      50

Uint16 PPOFTWMiniNumAry = 7;

void PPOFTWModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = 6 + PPOFTW_Nrept_1C;        // 1A 1C 1D 1E 1F 1G 1H��106������
	//  �������ǻز���������2
	DataTotalNum = 2*(PPOFTW_NE_1ADEFGH*6 + PPOFTW_NE_1C*PPOFTW_Nrept_1C);  // ��11000���ز���

	// ��ʱ���ü̵����˿�Ϊ1
	DCFreqSel = 1;
	FreqAry[DCFreqSel]  = CenterFreq;

	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	// 1A
	//StartS1msModule(15000);      // 15000+ms
	MiniScan(CenterFreq, MINITABLE_START+10, MINITABLE_START+1);

	Tes	= (Uint32)100 *PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	Pulse90StoreAddr	= PPOFTW_TABLE_START+(Uint32)DataTotalNum+20;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPOFTW_TABLE_START+(Uint32)20;
	DCWorkOnce(DCFreqSel);

	// 1C
	StartS1msModule(PPOFTW_TW_1C);

	MiniScan(CenterFreq, MINITABLE_START+22, MINITABLE_START+13);

	Tes	= (Uint32)100 * PPOFTW_TE_1C *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPOFTW_NE_1ADEFGH;
	DCWorkOnce(DCFreqSel);
	int i=0;
	for (;i<PPOFTW_Nrept_1C-1;i++)
	{
		StartS1msModule(PPOFTW_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2*PPOFTW_NE_1C;
		DCWorkOnce(DCFreqSel);
	}

	// 1D
	StartS1msModule(PPOFTW_TW_1D);

	MiniScan(CenterFreq, MINITABLE_START+34, MINITABLE_START+25);

	Tes	= (Uint32)100 * PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2*PPOFTW_NE_1C;
	DCWorkOnce(DCFreqSel);

	// 1E
	StartS1msModule(PPOFTW_TW_1E);

	MiniScan(CenterFreq, MINITABLE_START+46, MINITABLE_START+37);

	Tes	= (Uint32)100 *PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2*PPOFTW_NE_1ADEFGH;
	DCWorkOnce(DCFreqSel);

	// 1F
	StartS1msModule(PPOFTW_TW_1F);

	MiniScan(CenterFreq, MINITABLE_START+58, MINITABLE_START+49);

	Tes	= (Uint32)100 *PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2* PPOFTW_NE_1ADEFGH;
	DCWorkOnce(DCFreqSel);

	// 1G
	StartS1msModule(PPOFTW_TW_1G);

	MiniScan(CenterFreq, MINITABLE_START+70, MINITABLE_START+61);

	Tes	= (Uint32)100 *PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2* PPOFTW_NE_1ADEFGH;
	DCWorkOnce(DCFreqSel);

	//1H
	StartS1msModule(PPOFTW_TW_1H);

	MiniScan(CenterFreq, MINITABLE_START+82, MINITABLE_START+73);

	Tes	= (Uint32)100 *PPOFTW_TE_1ADEFGH *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPOFTW_NE_1ADEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2* PPOFTW_NE_1ADEFGH;
	DCWorkOnce(DCFreqSel);

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//��ش洢
	SaveNTempPt	= (int *)PPOFTW_TABLE_START;
	*SaveNTempPt++ = 0x9995;       						// ����ͷ
	*SaveNTempPt++ = 3*EchoNum + DataTotalNum + 20;		// ����
	*SaveNTempPt++ = 0x0005;       						// ����ģʽ
	*SaveNTempPt = CenterFreq*10;   					// ����Ƶ��

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 16);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt++ = Width90Pulse;      // 90��������
	SavePhaseWord();

	SaveNTempPt	= (int *)(PPOFTW_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(PPOFTW_TABLE_START+7);
	StoreMiniAryPt	= &PPOFTWMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPOFTW_TABLE_START);
	for (i=0;i<3*EchoNum+DataTotalNum+20;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;
	
	SciaSendDataNWords(PPOFTW_TABLE_START, 3*EchoNum+DataTotalNum+21);
	ChangePhase();
	return;
}
