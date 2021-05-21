/*
 * HRT1T22FModeTop.c
 *
 *  Created on: 2020-5-13
 *      Author: PJX
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(HRT1T22FModeTop,"Datatable");

void PulseAddrIncrementOne(void);

/*HRT1T22Fģʽ*/
void HRT1T22FModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��

	/*******************20201022�޸�*******************/
	// NREPT B3 B4 B5 B6: 2 2 2 4
    //EchoNum = 2 + HRT1T22FMode_NREPT_B2 + 2 + 2 + 2 + 4 + HRT1T22FMode_NREPT_B7; // 53���ز���
    //DataTotalNum = 2*(HRT1T22FMode_NE_A1 + HRT1T22FMode_NE_B1 + HRT1T22FMode_NE_B2 * HRT1T22FMode_NREPT_B2 + HRT1T22FMode_NE_B3 * 2 + HRT1T22FMode_NE_B4 * 2 +
                   //HRT1T22FMode_NE_B5 * 2 + HRT1T22FMode_NE_B6 * 4 + HRT1T22FMode_NE_B7 * HRT1T22FMode_NREPT_B7);
    EchoNum = 2 + HRT1T22FMode_NREPT_B2 + 2 + 2 + 2 + 4 + HRT1T22FMode_NREPT_B7; // 53���ز���
    DataTotalNum = 2*(HRT1T22FMode_NE_A1 + HRT1T22FMode_NE_B1 + HRT1T22FMode_NE_B2 * HRT1T22FMode_NREPT_B2 + HRT1T22FMode_NE_B3 * 2 + HRT1T22FMode_NE_B4 * 2 +
                   HRT1T22FMode_NE_B5 * 2 + HRT1T22FMode_NE_B6 * 4 + HRT1T22FMode_NE_B7 * HRT1T22FMode_NREPT_B7);


    // DataTotalNum��ʵ���ܻز�����

    // A1/B1/B2ǰ����Ҫ���Ӳɼ�����������ɨƵ
    // A1
    // �̵�������
    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[1]];   // �̵����պ�
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    MiniScan(FreqAry[HRT1T22FFreqSelAry[1]], MINITABLE_START + 10, MINITABLE_START + 1); // Ĭ��F8������9��Ƶ�ʷ�ֵ��3����������

    Tes = (Uint32)100 * HRT1T22FMode_TE_A1 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_A1;
    Pulse90StoreAddr = HRT1T22FTABLE_START + (Uint32)DataTotalNum  + 28; // 90�������ֵ�洢��ַ
    PulseF180StoreAddr = Pulse90StoreAddr + EchoNum;                        // ��һ��180�����ֵ
    PulseL180StoreAddr = PulseF180StoreAddr + EchoNum;                      // ���һ��180�����ֵ
    EchoStorAddr = HRT1T22FTABLE_START + (Uint32)3;
    DCWorkOnce(HRT1T22FFreqSelAry[1]); // Ĭ��F8

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[1]]<<8;   // �̵����Ͽ�
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // B1
    // StartS1msModule(200);
    StartS1msModule(1000-MINI_TEST);

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[2]];   // �̵����պ�
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    MiniScan(FreqAry[HRT1T22FFreqSelAry[2]], MINITABLE_START + 22, MINITABLE_START + 13);

    Tes = (Uint32)100 * HRT1T22FMode_TE_B1 * FPGA_COUNT;
    Tel = Tes;
    Ne = HRT1T22FMode_NE_B1;
    PulseAddrIncrementOne();
    EchoStorAddr += (2 * HRT1T22FMode_NE_A1);
    DCWorkOnce(HRT1T22FFreqSelAry[2]); // Ĭ��F5

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

			//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(HRT1T22FCnt<HRT1T22FMode_NREPT_B2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B2*FPGA_BC);	//1������Ϊ
		}
	}

    // B3 B4 B5 B6 B7�ĵ�һ���ز���ǰ�����Ӳɼ�����������ɨƵ
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

			//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B3*FPGA_BC);	//1������Ϊ
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

			//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B4*FPGA_BC);	//1������Ϊ
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

			//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(HRT1T22FCnt<2-1)
		{
			StartS1msModule(HRT1T22FMode_TW_B5*FPGA_BC);	//1������Ϊ
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

    RELAY_ON_CLOSE = RelayAry[HRT1T22FFreqSelAry[2]]<<8;   // �̵����Ͽ�
    Delay(120);
    RELAY_ON_CLOSE = 0x0000;

    // ��ش洢
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
	StoreMini(2,SaveNTempPt,SaveSTempPt); ////����ĳһ����Ƶ��9��miniɨƵ���ƽ��ֵ��������ֵ��ƽ��ֵ��������׼ƫ���ƽ��ֵ
	/****************20201023�޸�**********************/
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


