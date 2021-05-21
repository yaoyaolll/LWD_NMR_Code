/*
 * DFT1T2DModeTop.c
 *
 *  Created on: 2020-5-14
 *      Author: PJX
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(DFT1T2DModeTop,"Datatable");

/*双频T1-T2-D模式*/
// 本模式总计148个回波串。正负各算一个回波串。
void DFT1T2DModeTop(void)
{
    ScaleMn = 1;
    ScaleM = 0;
    EchoNum = 2 * (DFT1T2D_NREPT_CBW * 2 + 26); // 148个回波串
    //2n
    DataTotalNum = 4 * (DFT1T2D_NE_A1B1 * 2 + DFT1T2D_NE_A2B2 * 2 + DFT1T2D_NREPT_A8B8 * DFT1T2D_NE_A8B8 * 2 + DFT1T2D_NREPT_A9B9 * DFT1T2D_NE_A9B9 * 2 + DFT1T2D_NE_DE * 10 + DFT1T2D_NREPT_A10B10 * DFT1T2D_NE_A10B10 * 2 + DFT1T2D_NE_CBW * DFT1T2D_NREPT_CBW * 2);

    MiniStorAddr1 = MINITABLE_START + 1;
    MiniStorAddr2 = MiniStorAddr1 + 324;
    PhaseFlag = POSITIVE;
    // A1+ T2
    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A1B1;
    Pulse90StoreAddr = DFT1T2DTABLE_START + (Uint32)DataTotalNum + 36;
    PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;
    PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;
    EchoStorAddr = DFT1T2DTABLE_START + (Uint32)12;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
	MiniStorAddr1	+=12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    StartS1msModule(DFT1T2D_TW_A1B1*FPGA_BC-MINI_TEST);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
    EchoStorAddr += 2 * DFT1T2D_NE_A1B1;

    // A11+- CBW 24次
	PhaseFlag		= POSITIVE;
	Tes	= (Uint32)100 * DFT1T2D_TE_CBW *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= DFT1T2D_NE_CBW;

	for (DFT1T2D_cnt=0;DFT1T2D_cnt<2*DFT1T2D_NREPT_CBW;DFT1T2D_cnt++)
	{
		if (DFT1T2D_cnt==0)
		{
			StartS1msModule(DFT1T2D_TW_CBW*FPGA_BC-MINI_TEST);
			MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
			MiniStorAddr1	+=12;
		}
		else
		{
			StartS1msModule(DFT1T2D_TW_CBW*FPGA_BC);
		}

		DCWorkOnce(DFT1T2DFreqSelAry[1]);

		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (DFT1T2D_cnt==DFT1T2D_NREPT_CBW-1)
		{
			ChangePhase();
		}
	}

    RELAY_ON_CLOSE = RelayAry[T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B1+ T2
    StartS1msModule(7395-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT;
    Tel = Tes;
    Ne = DFT1T2D_NE_A1B1;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;

    EchoStorAddr += 2 * DFT1T2D_NE_A1B1;

    // B11+- CBW
	PhaseFlag		= POSITIVE;
	Tes	= (Uint32)100 * DFT1T2D_TE_CBW *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= DFT1T2D_NE_CBW;

	for (DFT1T2D_cnt=0;DFT1T2D_cnt<2*DFT1T2D_NREPT_CBW;DFT1T2D_cnt++)
	{
		if (DFT1T2D_cnt==0)
		{
			StartS1msModule(DFT1T2D_TW_CBW*FPGA_BC-MINI_TEST);
			MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
			MiniStorAddr2	+=12;
		}
		else
		{
			StartS1msModule(DFT1T2D_TW_CBW*FPGA_BC);
		}

		DCWorkOnce(DFT1T2DFreqSelAry[2]);

		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (DFT1T2D_cnt==DFT1T2D_NREPT_CBW-1)
		{
			ChangePhase();
		}
	}

    RELAY_ON_CLOSE = RelayAry[T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A1- T2
    StartS1msModule(920-MINI_TEST);

    PhaseFlag = NEGATIVE;
    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A1B1;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;
    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * DFT1T2D_NE_A1B1;

    // A10+- T1
    PhaseFlag		= POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A10B10;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
		StartS1msModule(DFT1T2D_TW_A10B10*FPGA_BC-MINI_TEST);
		MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
		MiniStorAddr1	+=12;

		DCWorkOnce(DFT1T2DFreqSelAry[1]);

		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
    }

    // A8+- T1
    PhaseFlag		= POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_A8B8*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
        MiniStorAddr1 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[1]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }

    // A9+ T1
    PhaseFlag		= POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // A10+- T1
    PhaseFlag		= POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A10B10;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
		StartS1msModule(DFT1T2D_TW_A10B10*FPGA_BC-MINI_TEST);
		MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
		MiniStorAddr1	+=12;

		DCWorkOnce(DFT1T2DFreqSelAry[1]);

		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
    }

    // A8+ T1
    PhaseFlag		= POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    StartS1msModule(DFT1T2D_TW_A8B8*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // A9-+ T1
    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
        MiniStorAddr1 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[1]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }

    // A8- T1
    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    StartS1msModule(DFT1T2D_TW_A8B8*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // A9- T1
    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // A2+ T2
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A2B2;

    StartS1msModule(DFT1T2D_TW_A2B2*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B1- T2
    StartS1msModule(638-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A1B1;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // B10+- T1
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A10B10;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_A10B10*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * DFT1T2D_NE_A10B10;
    }

    // B8+
    PhaseFlag = POSITIVE;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    StartS1msModule(DFT1T2D_TW_A8B8*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A2- T2 带负90度脉冲
    StartS1msModule(190-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; // -90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B8- T1
    StartS1msModule(259-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // B9+ T1
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // B10+- T1
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A10B10;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_A10B10*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }
    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A3+ DE -90脉冲
    StartS1msModule(204-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL1_DE;
    Ne = DFT1T2D_NE_DE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);
    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; // -90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B8+ T1
    StartS1msModule(242-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // B9-+ T1
    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }
    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A3- -90脉冲
    StartS1msModule(179-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL1_DE;
    Ne = DFT1T2D_NE_DE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; // -90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B8- T1
    StartS1msModule(267-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A8B8;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    // B9- T1
    PhaseFlag = NEGATIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A9B9;

    StartS1msModule(DFT1T2D_TW_A9B9*FPGA_BC-MINI_TEST);
    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A4+- DE -90脉冲
    StartS1msModule(340-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL2_DE;
    Ne = DFT1T2D_NE_DE;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
    	if(DFT1T2D_cnt==1)
    	{
            StartS1msModule(DFT1T2D_TW_DE*FPGA_BC-MINI_TEST);
    	}

        MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
        MiniStorAddr1 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[1]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B2+ T2
    StartS1msModule(403-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A2B2;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A5+- DE -90脉冲
    StartS1msModule(336-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL3_DE;
    Ne = DFT1T2D_NE_DE;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        if (DFT1T2D_cnt == 1)
        {
            StartS1msModule(DFT1T2D_TW_DE*FPGA_BC-MINI_TEST);
        }
        MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
        MiniStorAddr1 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[1]);

        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        EchoStorAddr += 2 * Ne;
    }

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B2- T2 -90脉冲
    StartS1msModule(403-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = Tes;
    Ne = DFT1T2D_NE_A2B2;

    PhaseFlag = NEGATIVE;
    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A6+ DE -90脉冲
    StartS1msModule(330-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL4_DE;
    Ne = DFT1T2D_NE_DE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);\
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B3+ DE -90脉冲
    StartS1msModule(400-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL1_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = POSITIVE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A6- DE -90脉冲
    StartS1msModule(330-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL4_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = NEGATIVE;
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B3- DE -90脉冲
    StartS1msModule(400-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL1_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = NEGATIVE;
    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);\
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A7+ DE -90脉冲
    StartS1msModule(322-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL5_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = POSITIVE;
    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B4+ DE -90脉冲
    StartS1msModule(398-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL2_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = POSITIVE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // A7- DE -90脉冲
    StartS1msModule(322-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL5_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = NEGATIVE;


    MiniScan(FreqAry[DFT1T2DFreqSelAry[1]], MiniStorAddr1 + 9, MiniStorAddr1);
    MiniStorAddr1 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[1]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[1]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B4- DE -90脉冲
    StartS1msModule(398-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]];
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL2_DE;
    Ne = DFT1T2D_NE_DE;

    PhaseFlag = NEGATIVE;

    MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
    MiniStorAddr2 += 12;

    DCWorkOnce(DFT1T2DFreqSelAry[2]);

    Pulse90StoreAddr++;
    PulseF180StoreAddr++;
    PulseL180StoreAddr++;
    InverseTurnFlag = SET; //-90脉冲
    EchoStorAddr += 2 * Ne;

    // B5+- DE -90脉冲
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL3_DE;
    Ne = DFT1T2D_NE_DE;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_DE*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        InverseTurnFlag = SET;
        EchoStorAddr += 2 * Ne;
    }

    // B6+- DE -90脉冲
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL4_DE;
    Ne = DFT1T2D_NE_DE;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_DE*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        InverseTurnFlag = SET;
        EchoStorAddr += 2 * Ne;
    }

    // B7+- DE -90脉冲
    PhaseFlag = POSITIVE;
    Tes = DFT1T2D_TES_DE_T2_T1 * (Uint32)100 * FPGA_COUNT; // 所有TES都是0.5ms
    Tel = DFT1T2D_TEL5_DE;
    Ne = DFT1T2D_NE_DE;

    for (DFT1T2D_cnt = 0; DFT1T2D_cnt < 2; DFT1T2D_cnt++)
    {
        StartS1msModule(DFT1T2D_TW_DE*FPGA_BC-MINI_TEST);
        MiniScan(FreqAry[DFT1T2DFreqSelAry[2]], MiniStorAddr2 + 9, MiniStorAddr2);
        MiniStorAddr2 += 12;

        DCWorkOnce(DFT1T2DFreqSelAry[2]);

        ChangePhase();
        Pulse90StoreAddr++;
        PulseF180StoreAddr++;
        PulseL180StoreAddr++;
        InverseTurnFlag = SET;
        EchoStorAddr += 2 * Ne;
    }

    RELAY_ON_CLOSE = RelayAry[DFT1T2DFreqSelAry[2]] << 8;
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    //相关参数存储
    SaveNTempPt = (int *)DFT1T2DTABLE_START;
    *SaveNTempPt = 0x9995;
	SaveNTempPt++;
	*SaveNTempPt	= 0x0070;
	SaveSixFreq();
	SaveNTempPt++;
	*SaveNTempPt	= DFT1T2DFreqSel;
	SaveNTempPt++;
	*SaveNTempPt	= 0x55AA;

	SaveNTempPt	= (int *)(DFT1T2DTABLE_START + DataTotalNum + 30);
	SaveSTempPt	= (Uint16 *)(DFT1T2DTABLE_START + DataTotalNum + 12);
	DFT1T2DMiniNumAry[0]=27;
	StoreMiniAryPt = &DFT1T2DMiniNumAry[0];
	 StoreMini(2, SaveNTempPt, SaveSTempPt);
    McbspSendData(DFT1T2DTABLE_START, DataTotalNum +3*EchoNum+36);
    return;
}


