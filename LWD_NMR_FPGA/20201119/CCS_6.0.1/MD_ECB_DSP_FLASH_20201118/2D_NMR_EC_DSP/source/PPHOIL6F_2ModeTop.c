/*
 * PPHOIL6F_2_2ModeTop.c
 *
 *  Created on: 2020-5-7
 *      Author: PJX
 */


/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPHOIL6F_2ModeTop,"Datatable");

void PPHOIL6F_2ModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 23+6*PPHOIL6F_2NRept123456C;
	DataTotalNum	= 2*(6*PPHOIL6F_2Ne1B+5*PPHOIL6F_2Ne12346C*PPHOIL6F_2NRept123456C+3*PPHOIL6F_2Ne246A+2*PPHOIL6F_2Ne2B+6*PPHOIL6F_2Ne3B+PPHOIL6F_2Ne4B+3*PPHOIL6F_2Ne5B+2*PPHOIL6F_2Ne6B+PPHOIL6F_2Ne5C*PPHOIL6F_2NRept123456C);

	//PPHOIL6F_2__1B1
	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	Pulse90StoreAddr	= PPHOIL6F_2TABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPHOIL6F_2TABLE_START+(Uint32)4;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__2A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne246A;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B1
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	EchoStorAddr += 2*PPHOIL6F_2Ne246A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	//PPHOIL6F_2__3C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne12346C;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);
		EchoStorAddr += 2*PPHOIL6F_2Ne12346C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__1B2
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	//PPHOIL6F_2__1C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne12346C;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);
		EchoStorAddr += 2*PPHOIL6F_2Ne12346C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__2B1
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[2]],MINITABLE_START+106,MINITABLE_START+97);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_2B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne2B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B2
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+166,MINITABLE_START+157);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	EchoStorAddr += 2*PPHOIL6F_2Ne2B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;


	//PPHOIL6F_2__4A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[4]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[4]],MINITABLE_START+226,MINITABLE_START+217);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne246A;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[4]);

	//PPHOIL6F_2__4C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[4]],MINITABLE_START+238,MINITABLE_START+229);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne12346C;
	EchoStorAddr += 2*PPHOIL6F_2Ne246A;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[4]);
		EchoStorAddr += 2*PPHOIL6F_2Ne12346C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B3
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+178,MINITABLE_START+169);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__1B3
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__5B1
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[5]],MINITABLE_START+262,MINITABLE_START+253);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_5B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne5B;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[5]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__2B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[2]],MINITABLE_START+118,MINITABLE_START+109);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_2B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne2B;
	EchoStorAddr += 2*PPHOIL6F_2Ne5B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[2]);

	//PPHOIL6F_2__2C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[2]],MINITABLE_START+130,MINITABLE_START+121);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne12346C;
	EchoStorAddr += 2*PPHOIL6F_2Ne2B;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[2]);
		EchoStorAddr += 2*PPHOIL6F_2Ne12346C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B4
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+190,MINITABLE_START+181);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__1B4
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+58,MINITABLE_START+49);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__6A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[6]],MINITABLE_START+310,MINITABLE_START+301);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne246A;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[6]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__4B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[4]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[4]],MINITABLE_START+250,MINITABLE_START+241);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_4B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne4B;
	EchoStorAddr += 2*PPHOIL6F_2Ne246A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[4]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;


	//PPHOIL6F_2__5B2
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[5]],MINITABLE_START+274,MINITABLE_START+265);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_5B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne5B;
	EchoStorAddr += 2*PPHOIL6F_2Ne4B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[5]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B5
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+202,MINITABLE_START+193);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	EchoStorAddr += 2*PPHOIL6F_2Ne5B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__1B5
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+70,MINITABLE_START+61);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__6B1
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[6]],MINITABLE_START+322,MINITABLE_START+313);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_6B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne6B;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[6]);

	//PPHOIL6F_2__6C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[6]],MINITABLE_START+334,MINITABLE_START+325);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne12346C;
	EchoStorAddr += 2*PPHOIL6F_2Ne6B;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[6]);
		EchoStorAddr += 2*PPHOIL6F_2Ne12346C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__3B6
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[3]],MINITABLE_START+214,MINITABLE_START+205);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__1B6
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[1]],MINITABLE_START+82,MINITABLE_START+73);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne1B;
	EchoStorAddr += 2*PPHOIL6F_2Ne3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F_2__5B3
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[5]],MINITABLE_START+286,MINITABLE_START+277);

	Tes	= (Uint32)100 *PPHOIL6F_2_TE_5B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne5B;
	EchoStorAddr += 2*PPHOIL6F_2Ne1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[5]);

	//PPHOIL6F_2__5C
	StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[5]],MINITABLE_START+298,MINITABLE_START+289);

	Tes	= (Uint32)100 * PPHOIL6F_2_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne5C;
	EchoStorAddr += 2*PPHOIL6F_2Ne5B;
	for(PPHOIL6F_2Cnt=0;PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C;PPHOIL6F_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6F_2FreqSelAry[5]);
		EchoStorAddr += 2*PPHOIL6F_2Ne5C;

		if(PPHOIL6F_2Cnt<PPHOIL6F_2NRept123456C-1)
		{
			StartS1msModule(PPHOIL6F_2Tw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;


	//PPHOIL6F_2__6B2
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6F_2FreqSelAry[6]],MINITABLE_START+346,MINITABLE_START+337);

	Tes	= (Uint32)100*PPHOIL6F_2_TE_6B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6F_2Ne6B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6F_2FreqSelAry[6]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6F_2FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;



	//相关存储
	SaveNTempPt	= (int *)PPHOIL6F_2TABLE_START;
	*SaveNTempPt= 0x990F;
	SaveNTempPt++;
	*SaveNTempPt= PPHOIL6F_2FreqSelLow;
	SaveNTempPt++;
	*SaveNTempPt= PPHOIL6F_2FreqSelHi;
	SaveNTempPt++;
	SavePhaseWord();
	SaveNTempPt	= (int *)(PPHOIL6F_2TABLE_START+DataTotalNum+58);
	*SaveNTempPt= 0x294;
	SaveNTempPt	= (int *)(PPHOIL6F_2TABLE_START+DataTotalNum+59);
	SaveSTempPt	= (Uint16 *)(PPHOIL6F_2TABLE_START+DataTotalNum+4);
	StoreMiniAryPt	= &PPHOIL6F_2MiniNumAry[0];
	StoreMini(6,SaveNTempPt,SaveSTempPt);
	McbspSendData(PPHOIL6F_2TABLE_START,DataTotalNum+3*EchoNum+77);
	ChangePhase();
	return;
}








