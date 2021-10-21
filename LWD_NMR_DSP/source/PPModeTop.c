/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-21 15:37:14
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 15:54:48
 */
/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"


Uint16 PPModeMiniNumAry = 2;

void PPModeTop(void)
{
	ScaleMn = 1;
	ScaleM = 0; //�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	EchoNum = PPM_Nrept_1C + 1; // 1A�ظ�һ�Σ�1C�ظ�128��
	DataTotalNum = 2 * (PPM_NE_1A + PPM_Nrept_1C * PPM_NE_1C);

	// ��ʱ���ü̵����˿�Ϊ1
	// DCFreqSel = 1;
	// FreqAry[DCFreqSel] = TransmitFre;

	RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(TransmitFre, MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPM_TE_1A * FPGA_COUNT;
	Tel = Tes;
	Ne = PPM_NE_1A;
	Pulse90StoreAddr = PPM_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPM_TABLE_START + (Uint32)21;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPM_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPM_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPM_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPM_NE_1A;
	DCWorkOnce(TransmitFre);

	int i = 0;
	for (; i < PPM_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPM_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPM_NE_1C;
		DCWorkOnce(TransmitFre);
	}

	RelayClose(RelayCtrlCode);

	//ģʽ���ݴ洢
	SaveNTempPt = (int *)PPM_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // ����ͷ
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;				  // �ӻ���ʶ
	*SaveNTempPt++ = 0x0002;						  // ����ģʽ
	*SaveNTempPt = TransmitFre; 					  // ����Ƶ��

	SaveNTempPt = (int *)(PPM_TABLE_START + 17);
	*SaveNTempPt++ = CalQValue(TransmitFre, PPM_TABLE_START + 8);			   // Qֵ
	*SaveNTempPt++ = 0x294;		   // �ο���ֵ
	*SaveNTempPt++ = Width90Pulse; // 90��������
	SavePhaseWord();			   //�洢����������λ

	SaveNTempPt = (int *)(PPM_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = (Uint16)b;  // ����Ƶ��
	*SaveNTempPt = (Uint16)CublicSplineInterpolation(x, y, b); // ����Ƶ�ʷ�ֵ

	SaveNTempPt = (int *)(PPM_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(PPM_TABLE_START + 8);
	StoreMiniAryPt = &PPModeMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPM_TABLE_START);
	for (i = 0; i < 3 * EchoNum + DataTotalNum + 23; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3 * EchoNum + DataTotalNum + 24;

	//SciaSendDataNWords(PPM_TABLE_START, 3*EchoNum+DataTotalNum+21);

	// PAPS���ݴ洢
	PAPSEntry.current_well_mode = 0x0002;
	PAPSEntry.echo_1A_num = PPM_NE_1A;
	PAPSEntry.echo_1A_addr = PPM_TABLE_START + 21;
	PAPSEntry.echo_1C_num = PPM_NE_1C;
	PAPSEntry.echo_1C_addr1 = PPM_TABLE_START + 21 + 2 * PPM_NE_1A;
	PAPSEntry.echo_1C_nrept = PPM_Nrept_1C;
	StorgePAPSToFIFO(&PAPSEntry);

	ChangePhase();
	
	return;
}
