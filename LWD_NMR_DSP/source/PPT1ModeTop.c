/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-21 15:40:17
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-06-06 23:01:04
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
	// FreqAry[DCFreqSel] = CenterFreq;

	RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(10000);      // 10000+ms
	MiniScan(FreqAry[1], MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPT1_TE_1A * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1A;
	Pulse90StoreAddr = PPT1_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPT1_TABLE_START + (Uint32)21;
	DCWorkOnce(1);

	// 1C
	StartS1msModule(PPT1_TW_1C);

	MiniScan(FreqAry[1], MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1A;
	DCWorkOnce(1);
	int i = 0;
	for (; i < PPT1_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPT1_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1C;
		DCWorkOnce(1);
	}

	// 1D
	StartS1msModule(PPT1_TW_1D);

	MiniScan(FreqAry[1], MINITABLE_START + 34, MINITABLE_START + 25);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1C;
	DCWorkOnce(1);

	// 1E
	StartS1msModule(PPT1_TW_1E);

	MiniScan(FreqAry[1], MINITABLE_START + 46, MINITABLE_START + 37);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(1);

	// 1F
	StartS1msModule(PPT1_TW_1F);

	MiniScan(FreqAry[1], MINITABLE_START + 58, MINITABLE_START + 49);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(1);
	for (i = 0; i < PPT1_Nrept_1F - 1; i++)
	{
		StartS1msModule(PPT1_TW_1F);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(1);
	}

	// 1G
	StartS1msModule(PPT1_TW_1G);

	MiniScan(FreqAry[1], MINITABLE_START + 70, MINITABLE_START + 61);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(1);

	for (i = 0; i < PPT1_Nrept_1G - 1; i++)
	{
		StartS1msModule(PPT1_TW_1G);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(1);
	}

	//1H
	StartS1msModule(PPT1_TW_1H);

	MiniScan(FreqAry[1], MINITABLE_START + 82, MINITABLE_START + 73);

	Tes = (Uint32)100 * PPT1_TE_1CDEFGH * FPGA_COUNT;
	Tel = Tes;
	Ne = PPT1_NE_1DEFGH;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPT1_NE_1DEFGH;
	DCWorkOnce(1);

	for (i = 0; i < PPT1_Nrept_1H - 1; i++)
	{
		StartS1msModule(PPT1_TW_1G);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPT1_NE_1DEFGH;
		DCWorkOnce(1);
	}

	RelayClose(RelayCtrlCode);

	//相关存储
	SaveNTempPt = (int *)PPT1_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // 数据头
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;
	*SaveNTempPt++ = 0x0004;		  // 工作模式
	*SaveNTempPt++ = FreqAry[1] * 10; // 工作频率

	SaveNTempPt = (int *)(PPT1_TABLE_START + 17);
	*SaveNTempPt++ = 0;			   // Q值
	*SaveNTempPt++ = 0x294;		   // 参考幅值
	*SaveNTempPt++ = Width90Pulse; // 90度脉冲宽度
	SavePhaseWord();

	SaveNTempPt = (int *)(PPT1_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = getCenterFreq();  // 中心频率
	*SaveNTempPt = getCenterFreqAmp(); // 中心频率幅值

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
	ChangePhase();
	return;
}
