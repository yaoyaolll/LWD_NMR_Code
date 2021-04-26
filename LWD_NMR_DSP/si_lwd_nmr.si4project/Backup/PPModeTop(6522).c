/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPModeTop,"Datatable");

Uint16 PPModeMiniNumAry = 2;

void PPModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = PPM_Nrept_1C + 1;         // 1A�ظ�һ�Σ�1C�ظ�128��
	DataTotalNum = 2*(PPM_NE_1A + PPM_Nrept_1C*PPM_NE_1C);

	// ��ʱ���ü̵����˿�Ϊ1
	DCFreqSel = 1;

	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;


	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(CenterFreq, MINITABLE_START+10, MINITABLE_START+1);

	Tes	= (Uint32)100 *PPM_TE_1A *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPM_NE_1A;
	Pulse90StoreAddr	= PPM_TABLE_START+(Uint32)DataTotalNum+20;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPM_TABLE_START+(Uint32)20;
	DCWorkOnce(DCFreqSel);

	// 1C
	StartS1msModule(PPM_TW_1C);

	MiniScan(CenterFreq, MINITABLE_START+22, MINITABLE_START+13);

	Tes	= (Uint32)100 *PPM_TE_1C *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPM_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2* PPM_NE_1A;
	DCWorkOnce(DCFreqSel);

	int i=0;
	for (;i<PPM_Nrept_1C-1;i++)
	{
		StartS1msModule(PPM_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2*PPM_NE_1C;
		DCWorkOnce(DCFreqSel);
	}

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//��ش洢
	SaveNTempPt	= (int *)PPM_TABLE_START;
	*SaveNTempPt++ = 0x9995;       						// ����ͷ
	*SaveNTempPt++ = 3*EchoNum + DataTotalNum + 20;  	// ����
	*SaveNTempPt++ = 0x0002;       						// ����ģʽ
	*SaveNTempPt   = CenterFreq*10;   						// ����Ƶ��

	SaveNTempPt = (int *)(PPM_TABLE_START + 16);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt++ = Width90Pulse;      // 90��������
	SavePhaseWord();					//�洢����������λ

	SaveNTempPt	= (int *)(PPM_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(PPM_TABLE_START+7);
	StoreMiniAryPt	= &PPModeMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPM_TABLE_START);
	for (i=0;i<3*EchoNum+DataTotalNum+20;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;
	
	SciaSendDataNWords(PPM_TABLE_START, 3*EchoNum+DataTotalNum+21);
	ChangePhase();
	return;
}

