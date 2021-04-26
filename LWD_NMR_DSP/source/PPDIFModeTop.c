/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPDIFModeTop,"Datatable");

Uint16 PPDIFMiniNumAry = 4;

void PPDIFModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = PPDIF_Nrept_1C*2 + 2;         // 1A 1B�ظ�һ�Σ�1C�ظ�64*2�Σ���130������
	DataTotalNum = 2*(PPDIF_NE_1A1B*2 + PPDIF_NE_1C*PPDIF_Nrept_1C*2);   // ��8400���ز���

	// ��ʱ���ü̵����˿�Ϊ1
	DCFreqSel = 1;
	FreqAry[DCFreqSel]  = CenterFreq;

	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(CenterFreq, MINITABLE_START+10, MINITABLE_START+1);

	Tes	= (Uint32)100 *PPDIF_TE_1A1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPDIF_NE_1A1B;
	Pulse90StoreAddr	= PPDIF_TABLE_START+(Uint32)DataTotalNum+20;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPDIF_TABLE_START+(Uint32)20;
	DCWorkOnce(DCFreqSel);

	// 1C
	StartS1msModule(PPDIF_TW_1C);

	MiniScan(CenterFreq, MINITABLE_START+34, MINITABLE_START+25);

	Tes	= (Uint32)100 *PPDIF_TE_1C *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPDIF_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2* PPDIF_NE_1A1B;
	DCWorkOnce(DCFreqSel);
	int i=0;
	for (;i<PPDIF_Nrept_1C-1;i++)
	{
		StartS1msModule(PPDIF_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2*PPDIF_NE_1C;
		DCWorkOnce(DCFreqSel);
	}

	// 1B
	StartS1msModule(PPDIF_TW_1B);

	MiniScan(CenterFreq, MINITABLE_START+22, MINITABLE_START+13);

	Tes	= (Uint32)100 *PPDIF_TE_1A1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPDIF_NE_1A1B;
	PulseParamIncrement();
	EchoStorAddr += 2* PPDIF_NE_1C;
	DCWorkOnce(DCFreqSel);

	// 1C
	StartS1msModule(PPDIF_TW_1C);

	MiniScan(CenterFreq, MINITABLE_START+46, MINITABLE_START+37);

	Tes	= (Uint32)100 *PPDIF_TE_1C *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPDIF_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2* PPDIF_NE_1A1B;
	DCWorkOnce(DCFreqSel);

	for (i=0;i<PPDIF_Nrept_1C-1;i++)
	{
		StartS1msModule(PPDIF_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2*PPDIF_NE_1C;
		DCWorkOnce(DCFreqSel);
	}

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//��ش洢
	SaveNTempPt	= (int *)PPDIF_TABLE_START;
	*SaveNTempPt++ = 0x9995;       						// ����ͷ
	*SaveNTempPt++ = 3*EchoNum + DataTotalNum + 20;		// ����
	*SaveNTempPt++ = 0x0003;       						// ����ģʽ
	*SaveNTempPt++ = CenterFreq*10;   					// ����Ƶ��

	SaveNTempPt = (int *)(PPDIF_TABLE_START + 16);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt++ = Width90Pulse;      // 90��������
	SavePhaseWord();

	SaveNTempPt	= (int *)(PPDIF_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(PPDIF_TABLE_START+7);
	StoreMiniAryPt	= &PPDIFMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPDIF_TABLE_START);
	for (i=0;i<3*EchoNum+DataTotalNum+20;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3*EchoNum+DataTotalNum+21;
	
	//SciaSendDataNWords(PPDIF_TABLE_START, 3*EchoNum+DataTotalNum+21);
	ChangePhase();
	return;
}
