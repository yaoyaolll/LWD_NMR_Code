/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-21 15:40:17
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 15:53:43
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"


#define PPT1_Nrept_1F 4
#define PPT1_Nrept_1G 8
#define PPT1_Nrept_1H 16

Uint16 PPT1MiniNumAry = 7;

void PPT1ModeTop(void)
{
	ScaleMn = 1;
	ScaleM = 0; //在此模式中，ScaleM参数一直都为零

	EchoNum = 1 + PPT1_Nrept_1C + 1 + 1 + PPT1_Nrept_1F + PPT1_Nrept_1G + PPT1_Nrept_1H; // 1A 1C 1D 1E 1F 1G 1H共131个脉冲序列
	//  数据量是回波点数乘以2
	DataTotalNum = 2 * (PPT1_NE_1A + PPT1_NE_1C * PPT1_Nrept_1C + PPT1_NE_1DEFGH * (2 + PPT1_Nrept_1F + PPT1_Nrept_1G + PPT1_Nrept_1H)); // 共6480个回波点

	// 暂时设置继电器端口为1
	// DCFreqSel = 1;
	// FreqAry[DCFreqSel] = TransmitFre;

	RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(TransmitFre, MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPT1_TE_1A * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1A;
	Pulse90StoreAddr = PPT1_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPT1_TABLE_START + (Uint32)21;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPT1_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1A;
	DCWorkOnce(TransmitFre);
	int i = 0;
	for (; i < PPT1_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPT1_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1C;
		DCWorkOnce(TransmitFre);
	}

	// 1D
	StartS1msModule(PPT1_TW_1D);

	MiniScan(TransmitFre, MINITABLE_START + 34, MINITABLE_START + 25);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1C;
	DCWorkOnce(TransmitFre);

	// 1E
	StartS1msModule(PPT1_TW_1E);

	MiniScan(TransmitFre, MINITABLE_START + 46, MINITABLE_START + 37);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(TransmitFre);

	// 1F
	StartS1msModule(PPT1_TW_1F);

	MiniScan(TransmitFre, MINITABLE_START + 58, MINITABLE_START + 49);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(TransmitFre);
	for (i = 0; i < PPT1_Nrept_1F - 1; i++)
	{
		StartS1msModule(PPT1_TW_1F);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(TransmitFre);
	}

	// 1G
	StartS1msModule(PPT1_TW_1G);

	MiniScan(TransmitFre, MINITABLE_START + 70, MINITABLE_START + 61);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(TransmitFre);

	for (i = 0; i < PPT1_Nrept_1G - 1; i++)
	{
		StartS1msModule(PPT1_TW_1G);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(TransmitFre);
	}

	//1H
	StartS1msModule(PPT1_TW_1H);

	MiniScan(TransmitFre, MINITABLE_START + 82, MINITABLE_START + 73);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(TransmitFre);

	for (i = 0; i < PPT1_Nrept_1H - 1; i++)
	{
		StartS1msModule(PPT1_TW_1G);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(TransmitFre);
	}

	RelayClose(RelayCtrlCode);

	//模式数据存储
	SaveNTempPt = (int *)PPT1_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // 数据头
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;
	*SaveNTempPt++ = 0x0004;		    // 工作模式
	*SaveNTempPt++ = TransmitFre;       // 工作频率

	SaveNTempPt = (int *)(PPT1_TABLE_START + 17);
	*SaveNTempPt++ = CalQValue(TransmitFre, PPT1_TABLE_START + 8);			   // Q值
	*SaveNTempPt++ = 0x294;		   // 参考幅值
	*SaveNTempPt++ = Width90Pulse; // 90度脉冲宽度
	SavePhaseWord();

	SaveNTempPt = (int *)(PPT1_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = (Uint16)b;  // 中心频率
	*SaveNTempPt = (Uint16)CublicSplineInterpolation(x, y, b); // 中心频率幅值

	SaveNTempPt = (int *)(PPT1_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(PPT1_TABLE_START + 8);
	StoreMiniAryPt = &PPT1MiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPT1_TABLE_START);
	for (i = 0; i < 3 * EchoNum + DataTotalNum + 23; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3 * EchoNum + DataTotalNum + 24;

	//SciaSendDataNWords(PPT1_TABLE_START, 3*EchoNum+DataTotalNum+21);

	// PAPS数据存储
	PAPSEntry.current_well_mode = 0x0004;
	PAPSEntry.echo_1A_num = PPT1_NE_1A;
	PAPSEntry.echo_1A_addr = PPT1_TABLE_START + 21;
	PAPSEntry.echo_1C_num = PPT1_NE_1C;
	PAPSEntry.echo_1C_addr1 = PPT1_TABLE_START + 21 + 2 * PPT1_NE_1A;	
	PAPSEntry.echo_1C_nrept = PPT1_Nrept_1C;
	StorgePAPSToFIFO(&PAPSEntry);
	
	ChangePhase();

	return;
}
