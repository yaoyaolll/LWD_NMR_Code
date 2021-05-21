/*
 * PPLOIL6FModeTop.c
 *
 *  Created on: 2020-4-28
 *      Author: PJX
 */

 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PPLOIL6FModeTop,"Datatable");

//6频PP+Light Oil模式
void PPLOIL6FModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 10+10*PPLOIL6NRept123456C+2*PPLOIL6NRept24D+2*PPLOIL6NRept24E;//总回波个数，默认10+10*16+2*8+2*4=194
	DataTotalNum = 2*(4*PPLOIL6FNe156A1B+10*PPLOIL6FNe123456C*PPLOIL6NRept123456C+2*PPLOIL6FNe24DE*(PPLOIL6NRept24D+PPLOIL6NRept24E)+4*PPLOIL6FNe23AB+2*PPLOIL6FNe4AB);//总NE数
					// 默认值2*(4*1000+10*25*16+2*25*12+4*148+2*285)=2*9762=19524
	//PPLOIL6F__1A
	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 *PPLOIL6F_TE_156A1B *  FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe156A1B;
	Pulse90StoreAddr	= PPLOIL6FTABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPLOIL6FTABLE_START+(Uint32)4;    //0x120004
	DCWorkOnce(PPLOIL6FFreqSelAry[1]);

	//PPLOIL6F__1C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100*PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe156A1B;   // 0x1207D4  offset: 2004
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[1]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__2A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[2]];
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+58,MINITABLE_START+49);

	Tes	= (Uint32)100*PPLOIL6F_TE_23AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe23AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[2]);   // echo addr 0x120AF4, offset: 2804

	//PPLOIL6F__2C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+70,MINITABLE_START+61);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe23AB;    // 0x120C1C, offset: 3100
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[2]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[1]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100*PPLOIL6F_TE_156A1B *FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe156A1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[1]);   // echo addr: 0x120F3C, offset: 3900

	//PPLOIL6F__1C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

	Tes	= (Uint32)100*PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe156A1B;   // 0x12170C, offset: 5900
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[1]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__2B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[2]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+82,MINITABLE_START+73);

	Tes	= (Uint32)100*PPLOIL6F_TE_23AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe23AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[2]);   // echo addr: 0x121A2C, offset: 6700

	//PPLOIL6F__2C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe23AB;   // 0x121B54, offset: 6996
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[2]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}


	//PPLOIL6F__2D
	StartS1msModule(PPLOIL6FTw24D*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+106,MINITABLE_START+97);

	Tes	= (Uint32)100 * PPLOIL6F_TE_2DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe24DE;   // echo addr: 0x121E74, offset: 7796
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept24D;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[2]);
		EchoStorAddr += 2*PPLOIL6FNe24DE;

		if(PPLOIL6FCnt<PPLOIL6NRept24D-1)
		{
			StartS1msModule(PPLOIL6FTw24D*FPGA_BC);
		}
	}


	//PPLOIL6F__2E
	StartS1msModule(PPLOIL6FTw24E*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[2]],MINITABLE_START+118,MINITABLE_START+109);

	Tes	= (Uint32)100 * PPLOIL6F_TE_2DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe24DE;   // echo addr: 0x122004, offset: 8196
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept24E;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[2]);
		EchoStorAddr += 2*PPLOIL6FNe24DE;

		if(PPLOIL6FCnt<PPLOIL6NRept24E-1)
		{
			StartS1msModule(PPLOIL6FTw24E*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__3A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[3]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[3]],MINITABLE_START+130,MINITABLE_START+121);

	Tes	= (Uint32)100*PPLOIL6F_TE_23AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe23AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[3]);  // echo addr: 0x1220CC, offset: 8396

	//PPLOIL6F__3C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe23AB;   // 0x1221F4, offset: 8692
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[3]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__4A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[4]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+178,MINITABLE_START+169);

	Tes	= (Uint32)100*PPLOIL6F_TE_4AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe4AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[4]);   // echo addr:0x122514, offset: 9492

	//PPLOIL6F__4C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+190,MINITABLE_START+181);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe4AB;  // 0x12274E, offset: 10062
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[4]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__3B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[3]];   //继电器
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);

	Tes	= (Uint32)100*PPLOIL6F_TE_23AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe23AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[3]);   // echo addr: 0x122A6E, offset: 10862

	//PPLOIL6F__3C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[3]],MINITABLE_START+166,MINITABLE_START+157);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe23AB;   // 0x122B96, offset: 11158
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[3]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__4B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[4]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+202,MINITABLE_START+193);

	Tes	= (Uint32)100*PPLOIL6F_TE_4AB * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe4AB;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[4]);  // echo addr: 0x122EB6, offset: 11958

	//PPLOIL6F__4C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+214,MINITABLE_START+205);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe4AB;  // 0x1230F012528
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[4]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	//PPLOIL6F__4D
	StartS1msModule(PPLOIL6FTw24D*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+226,MINITABLE_START+217);

	Tes	= (Uint32)100 * PPLOIL6F_TE_4DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe24DE;   // echo addr: 0x123410, offset: 13328
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept24D;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[4]);
		EchoStorAddr += 2*PPLOIL6FNe24DE;

		if(PPLOIL6FCnt<PPLOIL6NRept24D-1)
		{
			StartS1msModule(PPLOIL6FTw24D*FPGA_BC);
		}
	}

	//PPLOIL6F__4E
	StartS1msModule(PPLOIL6FTw24E*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[4]],MINITABLE_START+238,MINITABLE_START+229);

	Tes	= (Uint32)100 * PPLOIL6F_TE_4DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe24DE;   // echo addr: 0x1235A0, offset: 13728
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept24E;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[4]);
		EchoStorAddr += 2*PPLOIL6FNe24DE;

		if(PPLOIL6FCnt<PPLOIL6NRept24E-1)
		{
			StartS1msModule(PPLOIL6FTw24E*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__5A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[5]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[5]],MINITABLE_START+250,MINITABLE_START+241);

	Tes	= (Uint32)100*PPLOIL6F_TE_156A1B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe156A1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[5]);  // echo addr: 0x123668, offset: 13928

	//PPLOIL6F__5C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[5]],MINITABLE_START+262,MINITABLE_START+253);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe156A1B;  // echo addr: 0x123E38, offset: 15928
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[5]);
		EchoStorAddr += 2*PPLOIL6FNe123456C;

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[5]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//PPLOIL6F__6A
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[6]];   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[6]],MINITABLE_START+274,MINITABLE_START+265);

	Tes	= (Uint32)100*PPLOIL6F_TE_156A1B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe156A1B;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PPLOIL6FFreqSelAry[6]);   // echo addr: 0x124158, offset: 16728

	//PPLOIL6F__6C
	StartS1msModule(PPLOIL6FTw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[PPLOIL6FFreqSelAry[6]],MINITABLE_START+286,MINITABLE_START+277);

	Tes	= (Uint32)100 * PPLOIL6F_TE_123456C * FPGA_COUNT;
	Tel	= Tes;
	Ne	= PPLOIL6FNe123456C;
	EchoStorAddr += 2*PPLOIL6FNe156A1B;   // 0x124928, offset: 18728
	for(PPLOIL6FCnt=0;PPLOIL6FCnt<PPLOIL6NRept123456C;PPLOIL6FCnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(PPLOIL6FFreqSelAry[6]);

		if(PPLOIL6FCnt<PPLOIL6NRept123456C-1)
		{
			EchoStorAddr += 2*PPLOIL6FNe123456C;
			StartS1msModule(PPLOIL6FTw123456C*FPGA_BC);
		}
	}

	RELAY_ON_CLOSE = RelayAry[PPLOIL6FFreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//相关存储
		SaveNTempPt	= (int *)PPLOIL6FTABLE_START;
		*SaveNTempPt= 0x990D;
		SaveNTempPt++;
		*SaveNTempPt= PPLOIL6FFreqSelLow;
		SaveNTempPt++;
		*SaveNTempPt= PPLOIL6FFreqSelHi;
		SaveNTempPt++;
		SavePhaseWord();
		SaveNTempPt	= (int *)(PPLOIL6FTABLE_START+DataTotalNum+58);
		*SaveNTempPt= 0x294;
		SaveNTempPt	= (int *)(PPLOIL6FTABLE_START+DataTotalNum+59);
		SaveSTempPt	= (Uint16 *)(PPLOIL6FTABLE_START+DataTotalNum+4);
		StoreMiniAryPt	= &PPLOIL6FMiniNumAry[0];
		StoreMini(6,SaveNTempPt,SaveSTempPt);
		McbspSendData(PPLOIL6FTABLE_START,DataTotalNum+3*EchoNum+77);
		ChangePhase();
		return;
}


