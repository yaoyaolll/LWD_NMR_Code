/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPShortModeTop,"Datatable");

Uint16 PPShortMiniNumAry = 2;

void PPShortModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = 1 + PPShort_Nrept_1C;        // 1A 1C ��101������
	//  �������ǻز���������2
	DataTotalNum = 2*(PPShort_NE_1A + PPShort_NE_1C*PPShort_Nrept_1C);  // ��6000���ز���

	// ��ʱ���ü̵����˿�Ϊ1
	DCFreqSel = 1;
	FreqAry[DCFreqSel]  = CenterFreq;

	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	// 1A
	StartS1msModule(1800);      // 1800+ms
	MiniScan(CenterFreq, MINITABLE_START+10, MINITABLE_START+1);

	Tes	= (Uint32)100 *PPShort_TE_1A *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPShort_NE_1A;
	Pulse90StoreAddr	= PPShort_TABLE_START+(Uint32)DataTotalNum+19;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPShort_TABLE_START+(Uint32)19;
	DCWorkOnce(DCFreqSel);

	// 1C
	StartS1msModule(PPShort_TW_1C);

	MiniScan(CenterFreq, MINITABLE_START+22, MINITABLE_START+13);

	Tes	= (Uint32)100 * PPShort_TE_1C *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPShort_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPShort_NE_1A;
	DCWorkOnce(DCFreqSel);
	int i=0;
	for (;i<PPShort_Nrept_1C-1;i++)
	{
		StartS1msModule(PPShort_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2*PPShort_NE_1C;
		DCWorkOnce(DCFreqSel);
	}

	InverseTurnFlag = SET;              // -90������

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//��ش洢
	SaveNTempPt	= (int *)PPShort_TABLE_START;
	*SaveNTempPt++ = 0x9995;       		// ����ͷ
	*SaveNTempPt++ = 0x0006;       		// ����ģʽ
	*SaveNTempPt = CenterFreq * 10;   	// ����Ƶ��

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 15);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt++ = Width90Pulse;      // 90��������
	SavePhaseWord();

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPShort_TABLE_START);
	for (i=0;i<DataTotalNum+322;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	SaveNTempPt	= (int *)(PPShort_TABLE_START+3);
	SaveSTempPt	= (Uint16 *)(PPShort_TABLE_START+6);
	StoreMiniAryPt	= &PPShortMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);
	
	SciaSendDataNWords(PPShort_TABLE_START, DataTotalNum+323);
	ChangePhase();
	return;
}
