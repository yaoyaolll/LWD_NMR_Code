/*
 * PPHOIL6FModeTop.c
 *
 *  Created on: 2020-5-6
 *      Author: PJX
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPHOIL6FModeTop,"Datatable");

void PPHOIL6FModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 21+4*PPHOIL6FNRept1234C+PPHOIL6FNRept5C+PPHOIL6FNRept6C;
	DataTotalNum	= 2*(6*PPHOIL6FNe1B+4*PPHOIL6FNe12345C*PPHOIL6FNRept1234C+3*PPHOIL6FNe246A+2*PPHOIL6FNe2B+6*PPHOIL6FNe3B+PPHOIL6FNe4B+2*PPHOIL6FNe5B+PPHOIL6FNe6B+PPHOIL6FNe6C*PPHOIL6FNRept6C+PPHOIL6FNe12345C*PPHOIL6FNRept5C);

	//PPHOIL6F__1B
	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	Pulse90StoreAddr	= PPHOIL6FTABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPHOIL6FTABLE_START+(Uint32)4;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__2A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100*PPHOIL6F_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe246A;
	EchoStorAddr += 2*PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	EchoStorAddr += 2*PPHOIL6FNe246A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	//PPHOIL6F__3C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe12345C;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept1234C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[3]);
		EchoStorAddr += 2*PPHOIL6FNe12345C;

		if(PPHOIL6FCnt<PPHOIL6FNRept1234C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	//PPHOIL6F__1C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe12345C;
	EchoStorAddr += 2*PPHOIL6FNe1B;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept1234C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[1]);
		EchoStorAddr += 2*PPHOIL6FNe12345C;

		if(PPHOIL6FCnt<PPHOIL6FNRept1234C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+166,MINITABLE_START+157);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__2B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[2]],MINITABLE_START+106,MINITABLE_START+97);

	Tes	= (Uint32)100*PPHOIL6F_TE_2B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe2B;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[2]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__4A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[4]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[4]],MINITABLE_START+226,MINITABLE_START+217);

	Tes	= (Uint32)100*PPHOIL6F_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe246A;
	EchoStorAddr += 2*PPHOIL6FNe2B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[4]);

	//PPHOIL6F__4C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[4]],MINITABLE_START+238,MINITABLE_START+229);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe12345C;
	EchoStorAddr += 2*PPHOIL6FNe246A;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept1234C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[4]);
		EchoStorAddr += 2*PPHOIL6FNe12345C;

		if(PPHOIL6FCnt<PPHOIL6FNRept1234C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+178,MINITABLE_START+169);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__5B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[5]],MINITABLE_START+262,MINITABLE_START+253);

	Tes	= (Uint32)100 *PPHOIL6F_TE_5B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe5B;
	EchoStorAddr += 2*PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[5]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__2B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[2]],MINITABLE_START+118,MINITABLE_START+109);

	Tes	= (Uint32)100*PPHOIL6F_TE_2B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe2B;
	EchoStorAddr += 2*PPHOIL6FNe5B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[2]);

	//PPHOIL6F__2C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[2]],MINITABLE_START+130,MINITABLE_START+121);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe12345C;
	EchoStorAddr += 2*PPHOIL6FNe2B;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept1234C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[2]);
		EchoStorAddr += 2*PPHOIL6FNe12345C;

		if(PPHOIL6FCnt<PPHOIL6FNRept1234C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+190,MINITABLE_START+181);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__4B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[4]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[4]],MINITABLE_START+250,MINITABLE_START+241);

	Tes	= (Uint32)100*PPHOIL6F_TE_4B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe4B;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[4]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+58,MINITABLE_START+49);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	EchoStorAddr += 2*PPHOIL6FNe4B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__5B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[5]],MINITABLE_START+274,MINITABLE_START+265);

	Tes	= (Uint32)100 *PPHOIL6F_TE_5B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe5B;
	EchoStorAddr += 2*PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[5]);

	//PPHOIL6F__5C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[5]],MINITABLE_START+286,MINITABLE_START+277);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe12345C;
	EchoStorAddr += 2*PPHOIL6FNe5B;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept5C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[5]);
		EchoStorAddr += 2*PPHOIL6FNe12345C;

		if(PPHOIL6FCnt<PPHOIL6FNRept5C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+202,MINITABLE_START+193);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__6A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[6]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[6]],MINITABLE_START+298,MINITABLE_START+289);

	Tes	= (Uint32)100*PPHOIL6F_TE_246A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe246A;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[6]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+70,MINITABLE_START+61);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	EchoStorAddr += 2*PPHOIL6FNe246A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[3]],MINITABLE_START+214,MINITABLE_START+205);

	Tes	= (Uint32)100*PPHOIL6F_TE_3B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe3B;
	EchoStorAddr += 2*PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[3]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__6B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[6]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[6]],MINITABLE_START+310,MINITABLE_START+301);

	Tes	= (Uint32)100*PPHOIL6F_TE_6B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe6B;
	EchoStorAddr += 2*PPHOIL6FNe3B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[6]);

	//PPHOIL6F__6C
	StartS1msModule(PPHOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[6]],MINITABLE_START+322,MINITABLE_START+313);

	Tes	= (Uint32)100 * PPHOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe6C;
	EchoStorAddr += 2*PPHOIL6FNe6B;
	for(PPHOIL6FCnt=0;PPHOIL6FCnt<PPHOIL6FNRept6C;PPHOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPHOIL6FFreqSelAry[6]);
		EchoStorAddr += 2*PPHOIL6FNe6C;

		if(PPHOIL6FCnt<PPHOIL6FNRept6C-1)
		{
			StartS1msModule(PPHOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPHOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPHOIL6FFreqSelAry[1]],MINITABLE_START+82,MINITABLE_START+73);

	Tes	= (Uint32)100 *PPHOIL6F_TE_1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPHOIL6FNe1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPHOIL6FFreqSelAry[1]);

	RELAY_ON_CLOSE = RelayAry[PPHOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//相关存储
	SaveNTempPt	= (int *)PPHOIL6FTABLE_START;
	*SaveNTempPt= 0x9905;
	SaveNTempPt++;
	*SaveNTempPt= PPHOIL6FFreqSelLow;
	SaveNTempPt++;
	*SaveNTempPt= PPHOIL6FFreqSelHi;
	SaveNTempPt++;
	SavePhaseWord();
	SaveNTempPt	= (int *)(PPHOIL6FTABLE_START+DataTotalNum+58);
	*SaveNTempPt= 0x294;
	SaveNTempPt	= (int *)(PPHOIL6FTABLE_START+DataTotalNum+59);
	SaveSTempPt	= (Uint16 *)(PPHOIL6FTABLE_START+DataTotalNum+4);
	StoreMiniAryPt	= &PPHOIL6FMiniNumAry[0];
	StoreMini(6,SaveNTempPt,SaveSTempPt);
	McbspSendData(PPHOIL6FTABLE_START,DataTotalNum+3*EchoNum+77);
	ChangePhase();
	return;
}




