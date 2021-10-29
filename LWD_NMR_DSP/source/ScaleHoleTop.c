/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:31:40
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:11:20
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop, "secureRamFuncs");

//刻度主函数
void ScaleHoleModeTop(void)
{
	// 此模式下的继电器码根据下发的频率计算得到
	RelayCode = CalRelayFromFre(CenterFreq);

    Uint16 QValue;
	// 20201016屏蔽此处代码
	/*if(ScaleModeFlag==SET)//主刻度
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}*/
	// 主刻度时TE默认为10，孔隙度刻度时默认为6
	// 主刻度时NE默认为60，孔隙度刻度时默认为150
	Tes = (Uint32)100 * Calib_TE * FPGA_COUNT;
	Tel = Tes; //将TE转换为10ns单位即FPGA计数值
	Ne = Calib_NE;
	ScaleMn = 1;
	ScaleM = 0;

	ToMSNoiseAddr = SCALETABLE_START + 5;
	ToMSSignalAddr = SCALETABLE_START + 8;
	EchoStorAddr = SCALETABLE_START + 21;
	Pulse90StoreAddr = SCALETABLE_START + 2 * Ne + 21;
	PulseF180StoreAddr = SCALETABLE_START + 2 * Ne + 22;
	PulseL180StoreAddr = SCALETABLE_START + 2 * Ne + 23;

    RelayOpen(RelayCode);

	//StartS1msModule(25000);
	MiniScan(CenterFreq, ToMSNoiseAddr, ToMSSignalAddr); //mini扫频

	DCWorkOnce(CenterFreq); //刻度

    RelayClose(RelayCode);


    // 计算Q值
    QValue = CalQValue(CenterFreq, SCANTABLE_START + 8);

	//存储
	if (ScaleModeFlag == SET) //主刻度模式
	{
		SaveNTempPt = (int *)(SCALETABLE_START);
		*SaveNTempPt++ = REPLY_MODE_DATA_F; // 参数头
		*SaveNTempPt++ = 2 * Ne + 24;		// 长度
		*SaveNTempPt++ = EVENT_BOARD_ID;	// 从机标识
		*SaveNTempPt++ = 0x0009;			// 工作模式
		*SaveNTempPt = CenterFreq;  		// 工作频率

		SaveNTempPt = (int *)(SCALETABLE_START + 17);
		*SaveNTempPt++ = QValue;			   // Q值
		*SaveNTempPt++ = 0x294;		   // 参考幅值
		*SaveNTempPt++ = Width90Pulse; // 90度脉冲宽度
		SavePhaseWord();

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(SCALETABLE_START);
		int i = 0;
		for (; i < 2 * Ne + 24; ++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		PAPSEntry.last_well_mode = 0x0009;

		//SciaSendDataNWords(SCALETABLE_START, 2*Ne+24);    //上传刻度结果
	}
	else // 孔隙度刻度与校验模式
	{
		SaveNTempPt = (int *)(HOLETABLE_START);
		*SaveNTempPt++ = REPLY_MODE_DATA_F; // 参数头
		*SaveNTempPt++ = 2 * Ne + 24;		// 长度
		*SaveNTempPt++ = EVENT_BOARD_ID;	// 从机标识
		*SaveNTempPt++ = 0x000A;			// 工作模式
		*SaveNTempPt = CenterFreq;  		// 中心频率

		SaveNTempPt = (int *)(HOLETABLE_START + 17);
		*SaveNTempPt++ = QValue;			   // Q值
		*SaveNTempPt++ = 0x294;		   // 参考幅值
		*SaveNTempPt++ = Width90Pulse; // 90度脉冲宽度
		SavePhaseWord();			   // 存储相位

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(HOLETABLE_START);
		int i = 0;
		for (; i < 2 * Ne + 24; ++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		PAPSEntry.last_well_mode = 0x000A;

		//SciaSendDataNWords(HOLETABLE_START, 2*Ne+24);    //上传刻度结果
	}

	modeDataSendLen = 2 * Ne + 25;

	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/
/*-----------------------------------------------------------------------------------------*/
