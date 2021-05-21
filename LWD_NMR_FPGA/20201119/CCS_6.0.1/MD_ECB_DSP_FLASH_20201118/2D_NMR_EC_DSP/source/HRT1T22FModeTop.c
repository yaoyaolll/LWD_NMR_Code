/*
 * HRT1T22FModeTop.c
 *
 *  Created on: 2020-5-13
 *      Author: PJX
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(HRT1T22FModeTop,"Datatable");

void PulseAddrIncrementOne(void);

/*HRT1T22F模式*/
void HRT1T22FModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零

	/*******************20201022修改*******************/
	// NREPT B3 B4 B5 B6: 2 2 2 4
    //EchoNum = 2 + HRT1T22FMode_NREPT_B2 + 2 + 2 + 2 + 4 + HRT1T22FMode_NREPT_B7; // 53个回波串
    //DataTotalNum = 2*(HRT1T22FMode_NE_A1 + HRT1T22FMode_NE_B1 + HRT1T22FMode_NE_B2 * HRT1T22FMode_NREPT_B2 + HRT1T22FMode_NE_B3 * 2 + HRT1T22FMode_NE_B4 * 2 +
                   //HRT1T22FMode_NE_B5 * 2 + HRT1T22FMode_NE_B6 * 4 + HRT1T22FMode_NE_B7 * HRT1T22FMode_NREPT_B7);
    EchoNum = 2 + HRT1T22FMode_NREPT_B2 + 2 + 2 + 2 + 4 + HRT1T22FMode_NREPT_B7; // 53个回波串
    DataTotalNum = 2*(HRT1T22FMode_NE_A1 + HRT1T22FMode_NE_B1 + HRT1T22FMode_NE_B2 * HRT1T22FMode_NREPT_B2 + HRT1T22FMode_NE_B3 * 2 + HRT1T22FMode_NE_B4 * 2 +
                   HRT1T22FMode_NE_B5 * 2 + HRT1T22FMode_NE_B6 * 4 + HRT1T22FMode_NE_B7 * HRT1T22FMode_NREPT_B7);


    // DataTotalNum其实是总回波个数

    // A1/B1/B2前面需要增加采集噪声和迷你扫频
    // A1
    // 继电器操作
    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[1]];   // 继电器闭合
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    MiniScan(FreqAry[HRT1T22FFreqSelAry[1]], MINITABLE_START + 10, MINITABLE_START + 1); // 默认F8，储存9个频率幅值，3个噪声参数

    Tes = (Uint32)100 * HRT1T22FMode_TE_A1 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_A1;
    Pulse90StoreAddr = HRT1T22FTABLE_START + (Uint32)DataTotalNum  + 28; // 90度脉冲幅值存储地址
    PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;                        // 第一个180脉冲幅值
    PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;                      // 最后一个180脉冲幅值
    EchoStorAddr = HRT1T22FTABLE_START + (Uint32)3;
    DCWorkOnce(HRT1T22FFreqSelAry[1]); // 默认F8

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[1]]<<8;   // 继电器断开
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B1
    // StartS1msModule(200);
    StartS1msModule(1000-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[2]];   // 继电器闭合
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 22, MINITABLE_START + 13);

    Tes = (Uint32)100 * HRT1T22FMode_TE_B1 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_B1;
    PulseAddrIncrementOne();
    EchoStorAddr += (2 * HRT1T22FMode_NE_A1);
    DCWorkOnce(HRT1T22FFreqSelAry[2]); // 默认F5

    // B2
	StartS1msModule(HRT1T22FMode_TW_B2*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 34, MINITABLE_START + 25);

	Tes	= (Uint32)100 * HRT1T22FMode_TE_B2 * FPGA_COUNT;
	Tel	= Tes;
	Ne	= HRT1T22FMode_NE_B2;
	EchoStorAddr += 2*HRT1T22FMode_NE_B1;
	for(HRT1T22FCnt=0;HRT1T22FCnt<HRT1T22FMode_NREPT_B2;HRT1T22FCnt++)
	{
		PulseAddrIncrementOne();
		DCWorkOnce(HRT1T22FFreqSelAry[2]);
		EchoStorAddr += 2*HRT1T22FMode_NE_B2;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(HRT1T22FCnt<HRT1T22FMode_NREPT_B2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B2*FPGA_BC);	//1个计数为
		}
	}

    // B3 B4 B5 B6 B7的第一个回波串前面增加采集噪声和迷你扫频
    // B3
	StartS1msModule(HRT1T22FMode_TW_B3*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 46, MINITABLE_START + 37);

	Tes	= (Uint32)100 * HRT1T22FMode_TE_B3 * FPGA_COUNT;
	Tel	= Tes;
	Ne	= HRT1T22FMode_NE_B3;
//	EchoStorAddr += 2*HRT1T22FMode_NE_B2;
	for(HRT1T22FCnt=0;HRT1T22FCnt<2;HRT1T22FCnt++)
	{
		PulseAddrIncrementOne();
		DCWorkOnce(HRT1T22FFreqSelAry[2]);
		EchoStorAddr += 2*HRT1T22FMode_NE_B3;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B3*FPGA_BC);	//1个计数为
		}
	}


    // B4
	StartS1msModule(HRT1T22FMode_TW_B4*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 58, MINITABLE_START + 49);

	Tes	= (Uint32)100 * HRT1T22FMode_TE_B4 * FPGA_COUNT;
	Tel	= Tes;
	Ne	= HRT1T22FMode_NE_B4;

	for(HRT1T22FCnt=0;HRT1T22FCnt<2;HRT1T22FCnt++)
	{
		PulseAddrIncrementOne();
		DCWorkOnce(HRT1T22FFreqSelAry[2]);
		EchoStorAddr += 2*HRT1T22FMode_NE_B4;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B4*FPGA_BC);	//1个计数为
		}
	}


    // B5
	StartS1msModule(HRT1T22FMode_TW_B5*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 70, MINITABLE_START + 61);

	Tes	= (Uint32)100 * HRT1T22FMode_TE_B5 * FPGA_COUNT;
	Tel	= Tes;
	Ne	= HRT1T22FMode_NE_B5;

	for(HRT1T22FCnt=0;HRT1T22FCnt<2;HRT1T22FCnt++)
	{
		PulseAddrIncrementOne();
		DCWorkOnce(HRT1T22FFreqSelAry[2]);
		EchoStorAddr += 2*HRT1T22FMode_NE_B5;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B5*FPGA_BC);	//1个计数为
		}
	}

    // B6
    StartS1msModule(HRT1T22FMode_TW_B6*FPGA_BC-MINI_TEST);

    MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 82, MINITABLE_START + 73);

    Tes = (Uint32)100 * HRT1T22FMode_TE_B6 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_B6;
    for (HRT1T22FCnt = 0; HRT1T22FCnt < 4; HRT1T22FCnt++)
    {
        PulseAddrIncrementOne();
        DCWorkOnce(HRT1T22FFreqSelAry[2]);
        EchoStorAddr += (2 * HRT1T22FMode_NE_B6);
        if (HRT1T22FCnt < 4 - 1)
        {
            StartS1msModule(HRT1T22FMode_TW_B6*FPGA_BC);
        }
    }

    // B7
    StartS1msModule(HRT1T22FMode_TW_B7*FPGA_BC-MINI_TEST);

    MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 94, MINITABLE_START + 85);

    Tes = (Uint32)100 * HRT1T22FMode_TE_B7 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_B7;
    for (HRT1T22FCnt = 0; HRT1T22FCnt < HRT1T22FMode_NREPT_B7; HRT1T22FCnt++)
    {
        PulseAddrIncrementOne();
        DCWorkOnce(HRT1T22FFreqSelAry[2]);

        if (HRT1T22FCnt < HRT1T22FMode_NREPT_B7 - 1)
        {
            EchoStorAddr += (2 * HRT1T22FMode_NE_B7);
            StartS1msModule(HRT1T22FMode_TW_B7*FPGA_BC);
        }
    }

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[2]]<<8;   // 继电器断开
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // 相关存储
    SaveNTempPt = (int *)HRT1T22FTABLE_START;
    *SaveNTempPt = 0x990E;
    SaveNTempPt++;
    *SaveNTempPt = HRT1T22FFreqSel;
    SaveNTempPt++;
    SavePhaseWord();
  	SaveNTempPt	= (int *)(HRT1T22FTABLE_START+DataTotalNum+21);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
  	SaveSTempPt	= (Uint16 *)(HRT1T22FTABLE_START+DataTotalNum+3);
	StoreMiniAryPt	= &HRT1T22FMiniNumAry[0];
	StoreMini(2,SaveNTempPt,SaveSTempPt); ////计算某一工作频率9个mini扫频点的平均值、噪声均值的平均值、噪声标准偏差的平均值
	/****************20201023修改**********************/
    //McbspSendData(MINITABLE_START, DataTotalNum+3*EchoNum+28);
	McbspSendData(HRT1T22FTABLE_START, DataTotalNum+3*EchoNum+28);
    ChangePhase();
    return;
}

void PulseAddrIncrementOne(void)
{
    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
}


