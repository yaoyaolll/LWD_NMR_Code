/*
 * PP3FreqTop.c
 *
 *  Created on: 2020-5-5
 *      Author: PJX
 */
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(freq3PP_top,"Datatable");

void freq3PP_top(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 5+PP3FNRept1C;
	DataTotalNum	= 2*(PP3FNe1A+PP3FNe1C*PP3FNRept1C+4*PP3FNe23DE);

//3频pp__1A
	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP3FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 * PP3FTe1A23DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PP3FNe1A;
	Pulse90StoreAddr	= PP3TABLE_START+(Uint32)DataTotalNum+40;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PP3TABLE_START+(Uint32)3;
	DCWorkOnce(PP3FreqSelAry[1]);

//3频pp__1C
	StartS1msModule(PP3FTw1C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PP3FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100 * PP3FTe1C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PP3FNe1C;
	EchoStorAddr += 2*PP3FNe1A;
	for(PP3FCnt=0;PP3FCnt<PP3FNRept1C;PP3FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PP3FreqSelAry[1]);
		EchoStorAddr += 2*PP3FNe1C;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(PP3FCnt<PP3FNRept1C-1)
		{
			StartS1msModule(PP3FTw1C*FPGA_BC);	//1个计数为
		}
	}

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//3频pp__2D
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[2]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP3FreqSelAry[2]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * PP3FTe1A23DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PP3FNe23DE;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PP3FreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//3频pp__3D
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[3]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP3FreqSelAry[3]],MINITABLE_START+58,MINITABLE_START+49);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP3FNe23DE;
	DCWorkOnce(PP3FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//3频pp__2E
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[2]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP3FreqSelAry[2]],MINITABLE_START+46,MINITABLE_START+37);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP3FNe23DE;
	DCWorkOnce(PP3FreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//3频pp__3E
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[3]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP3FreqSelAry[3]],MINITABLE_START+70,MINITABLE_START+61);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP3FNe23DE;
	DCWorkOnce(PP3FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PP3FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//相关存储
	SaveNTempPt	= (int *)PP3TABLE_START;
	*SaveNTempPt= 0x9902;
	SaveNTempPt++;
	*SaveNTempPt= PP3FreqSel;
	SaveNTempPt++;
	SavePhaseWord();
	SaveNTempPt	= (int *)(PP3TABLE_START+DataTotalNum+30);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
	SaveSTempPt	= (Uint16 *)(PP3TABLE_START+DataTotalNum+3);
	StoreMiniAryPt	= &PP3FMiniNumAry[0];
	StoreMini(3,SaveNTempPt,SaveSTempPt); ////计算某一工作频率9个mini扫频点的平均值、噪声均值的平均值、噪声标准偏差的平均值
	//上传数据
	McbspSendData(PP3TABLE_START,DataTotalNum+3*EchoNum+40);
	ChangePhase();
	return;
}
