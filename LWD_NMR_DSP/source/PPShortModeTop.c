/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-21 15:42:09
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 15:55:52
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"


Uint16 PPShortMiniNumAry = 2;

void PPShortModeTop(void)
{
	ScaleMn = 1;
	ScaleM = 0; //在此模式中，ScaleM参数一直都为零

	EchoNum = 1 + PPShort_Nrept_1C; // 1A 1C 共101个序列
	//  数据量是回波点数乘以2
	DataTotalNum = 2 * (PPShort_NE_1A + PPShort_NE_1C * PPShort_Nrept_1C); // 共6000个回波点

	RelayOpen(RelayCtrlCode);

	// 1A
	//StartS1msModule(1800);      // 1800+ms
	MiniScan(TransmitFre, MINITABLE_START + 10, MINITABLE_START + 1);

	Tes = (Uint32)100 * PPShort_TE_1A * FPGA_COUNT;
	Tel = Tes;
	Ne = PPShort_NE_1A;
	Pulse90StoreAddr = PPShort_TABLE_START + (Uint32)DataTotalNum + 21;
	PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
	PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
	EchoStorAddr = PPShort_TABLE_START + (Uint32)21;
	DCWorkOnce(TransmitFre);

	// 1C
	StartS1msModule(PPShort_TW_1C);

	MiniScan(TransmitFre, MINITABLE_START + 22, MINITABLE_START + 13);

	Tes = (Uint32)100 * PPShort_TE_1C * FPGA_COUNT;
	Tel = Tes;
	Ne = PPShort_NE_1C;
	PulseParamIncrement();
	EchoStorAddr += 2 * PPShort_NE_1A;
	DCWorkOnce(TransmitFre);
	int i = 0;
	for (; i < PPShort_Nrept_1C - 1; i++)
	{
		StartS1msModule(PPShort_TW_1C);

		PulseParamIncrement();
		EchoStorAddr += 2 * PPShort_NE_1C;
		DCWorkOnce(TransmitFre);
	}

//	InverseTurnFlag = SET; // -90度脉冲

	RelayClose(RelayCtrlCode);

	// 模式数据存储
	SaveNTempPt = (int *)PPShort_TABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;				  // 数据头
	*SaveNTempPt++ = 3 * EchoNum + DataTotalNum + 23; // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;				  // 从机标识
	*SaveNTempPt++ = 0x0006;						  // 工作模式
	*SaveNTempPt = TransmitFre; 					  // 工作频率

	SaveNTempPt = (int *)(PPShort_TABLE_START + 17);
	*SaveNTempPt++ = CalQValue(TransmitFre, DECPMGTABLE_START + 8);			   // Q值
	*SaveNTempPt++ = 0x294;		   // 参考幅值
	*SaveNTempPt++ = Width90Pulse; // 90度脉冲宽度
	SavePhaseWord();

	SaveNTempPt = (int *)(PPOFTW_TABLE_START + 3 * EchoNum + DataTotalNum + 21);
	*SaveNTempPt++ = (Uint16)b;  // 中心频率
	*SaveNTempPt = (Uint16)CublicSplineInterpolation(x, y, b); // 中心频率幅值

	SaveNTempPt = (int *)(PPShort_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(PPShort_TABLE_START + 8);
	StoreMiniAryPt = &PPShortMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(PPShort_TABLE_START);
	for (i = 0; i < 3 * EchoNum + DataTotalNum + 23; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 3 * EchoNum + DataTotalNum + 24;

	//SciaSendDataNWords(PPShort_TABLE_START, 3*EchoNum+DataTotalNum+21);

	// PAPS数据存储
	PAPSEntry.current_well_mode = 0x0006;
	PAPSEntry.echo_1A_num = PPShort_NE_1A;
	PAPSEntry.echo_1A_addr = PPShort_TABLE_START + 21;
	PAPSEntry.echo_1C_num = PPShort_NE_1C;
	PAPSEntry.echo_1C_addr1 = PPOFTW_TABLE_START + 21 + 2 * PPShort_NE_1A;	
	PAPSEntry.echo_1C_nrept = PPShort_Nrept_1C;
	StorgePAPSToFIFO(&PAPSEntry);

	ChangePhase();
	
	return;
}
