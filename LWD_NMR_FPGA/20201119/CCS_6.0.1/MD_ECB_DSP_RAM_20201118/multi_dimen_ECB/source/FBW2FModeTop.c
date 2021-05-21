/*
 * FBW2FModeTop.c
 *
 *  Created on: 2020-5-5
 *      Author: PJX
 */
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(FBW2FModeTop,"Datatable");

void FBW2FModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��
	EchoNum	= 2+2*FBW2FNRept12C;
	DataTotalNum	= 4*(FBW2FNe12B+FBW2FNe12C*FBW2FNRept12C);

	//FBW2F_1B
	RELAY_ON_CLOSE = RelayAry[FBW2FFreqSelAry[1]];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[FBW2FFreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 * FBW2FTe12B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= FBW2FNe12B;
	Pulse90StoreAddr	= FBW2FTABLE_START+(Uint32)DataTotalNum+28;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= FBW2FTABLE_START+(Uint32)3;
	DCWorkOnce(FBW2FFreqSelAry[1]);

	//FBW2F__1C
	StartS1msModule(FBW2FTw12C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[FBW2FFreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100 * FBW2FTe12C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= FBW2FNe12C;
	EchoStorAddr += 2*FBW2FNe12B;
	for(FBW2FCnt=0;FBW2FCnt<FBW2FNRept12C;FBW2FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(FBW2FFreqSelAry[1]);
		EchoStorAddr += 2*FBW2FNe12C;

		//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(FBW2FCnt<FBW2FNRept12C-1)
		{
			StartS1msModule(FBW2FTw12C*FPGA_BC);	//1������Ϊ
		}
	}

	RELAY_ON_CLOSE = RelayAry[FBW2FFreqSelAry[1]]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//FBW2F_2B
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[FBW2FFreqSelAry[2]];   //�̵����պ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[FBW2FFreqSelAry[2]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * FBW2FTe12B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= FBW2FNe12B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(FBW2FFreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[FBW2FFreqSelAry[2]]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//FBW2F__2C
	StartS1msModule(FBW2FTw12C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[FBW2FFreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

	Tes	= (Uint32)100 * FBW2FTe12C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= FBW2FNe12C;
	EchoStorAddr += 2*FBW2FNe12B;
	for(FBW2FCnt=0;FBW2FCnt<FBW2FNRept12C;FBW2FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(FBW2FFreqSelAry[2]);
		EchoStorAddr += 2*FBW2FNe12C;

		//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(FBW2FCnt<FBW2FNRept12C-1)
		{
			StartS1msModule(FBW2FTw12C*FPGA_BC);	//1������Ϊ
		}
	}

	RELAY_ON_CLOSE = RelayAry[FBW2FFreqSelAry[2]]<<8;   //�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//��ش洢
	SaveNTempPt	= (int *)FBW2FTABLE_START;
	*SaveNTempPt= 0x9906;
	SaveNTempPt++;
	*SaveNTempPt= FBW2FFreqSel;
	SaveNTempPt++;
	SavePhaseWord();
	SaveNTempPt	= (int *)(FBW2FTABLE_START+DataTotalNum+21);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
	SaveSTempPt	= (Uint16 *)(FBW2FTABLE_START+DataTotalNum+3);
	StoreMiniAryPt	= &FBW2FMiniNumAry[0];
	StoreMini(2,SaveNTempPt,SaveSTempPt); ////����ĳһ����Ƶ��9��miniɨƵ���ƽ��ֵ��������ֵ��ƽ��ֵ��������׼ƫ���ƽ��ֵ
	//�ϴ�����
	McbspSendData(FBW2FTABLE_START,DataTotalNum+3*EchoNum+28);
	ChangePhase();
	return;
}



