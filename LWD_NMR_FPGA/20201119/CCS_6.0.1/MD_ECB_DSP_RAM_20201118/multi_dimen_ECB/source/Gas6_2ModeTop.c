/*
 * Gas6_2_2ModeTop.c
 *
 *  Created on: 2020-5-7
 *      Author: PJX
 */
 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(Gas6_2ModeTop,"Datatable");

void Gas6_2ModeTop(void)
{
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	ScaleMn	= 1;
	ScaleM	= 0;
	EchoNum	= 10+2*(Gas6_2NRept24D+Gas6_2NRept24E)+10*Gas6_2NRept123456C;
	DataTotalNum = 2*(10*Gas6_2_NE_1234AB56A+2*Gas6_2Ne123456C24DE*(5*Gas6_2NRept123456C+Gas6_2NRept24D+Gas6_2NRept24E));

	//gas_1A
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr	= PPGAS6_2TABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PPGAS6_2TABLE_START+(Uint32)4;
	DCWorkOnce(Gas6_2FreqSelAry[1]);

	//PPGAS6_2__1C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[1]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

				//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_2A
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[2]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+58,MINITABLE_START+49);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[2]);
	//PPGAS6_2__2C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+70,MINITABLE_START+61);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[2]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;
	//gas_1B
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[1]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * Gas6_2_TE_1234B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[1]);
	//PPGAS6_2__1C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[1]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_2B
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[2]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+82,MINITABLE_START+73);

	Tes	= (Uint32)100 * Gas6_2_TE_1234B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[2]);
	//PPGAS6_2__2C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[2]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}

	//PPGAS6_2__2D
	StartS1msModule(Gas6_2Tw24D*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+106,MINITABLE_START+97);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept24D;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[2]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept24D-1)
		{
			StartS1msModule(Gas6_2Tw24D*FPGA_BC);	//1个计数为
		}
	}
	//PPGAS6_2__2E
	StartS1msModule(Gas6_2Tw24E*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[2]],MINITABLE_START+118,MINITABLE_START+109);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept24E;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[2]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept24E-1)
		{
			StartS1msModule(Gas6_2Tw24E*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_3A
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[3]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[3]],MINITABLE_START+130,MINITABLE_START+121);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[3]);
	//PPGAS6_2__3C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[3]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_4A
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[4]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+178,MINITABLE_START+169);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[4]);
//PPGAS6_2__4C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+190,MINITABLE_START+181);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[4]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_3B
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[3]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);

	Tes	= (Uint32)100 * Gas6_2_TE_1234B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[3]);
//PPGAS6_2__3C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[3]],MINITABLE_START+166,MINITABLE_START+157);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[3]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//gas_4B
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[4]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+202,MINITABLE_START+193);

	Tes	= (Uint32)100 * Gas6_2_TE_1234B * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[4]);
//PPGAS6_2__4C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+214,MINITABLE_START+205);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[4]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}

//PPGAS6_2__4D
	StartS1msModule(Gas6_2Tw24D*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+226,MINITABLE_START+217);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept24D;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[4]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept24D-1)
		{
			StartS1msModule(Gas6_2Tw24D*FPGA_BC);	//1个计数为
		}
	}
//PPGAS6_2__4E
	StartS1msModule(Gas6_2Tw24E*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[4]],MINITABLE_START+238,MINITABLE_START+229);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept24E;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[4]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept24E-1)
		{
			StartS1msModule(Gas6_2Tw24E*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

//gas_5A
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[5]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[5]],MINITABLE_START+250,MINITABLE_START+241);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[5]);
//PPGAS6_2__5C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[5]],MINITABLE_START+262,MINITABLE_START+253);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[5]);
		EchoStorAddr += 2*Gas6_2Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[5]]<<8;   //继电器
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	//gas_6A
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[6]];   //继电器闭合
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6_2FreqSelAry[6]],MINITABLE_START+274,MINITABLE_START+265);

	Tes	= (Uint32)100 * Gas6_2_TE_123456A * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6_2FreqSelAry[6]);
//PPGAS6_2__6C
	StartS1msModule(Gas6_2Tw123456C*FPGA_BC-MINI_TEST);

	MiniScan(FreqAry[Gas6_2FreqSelAry[6]],MINITABLE_START+286,MINITABLE_START+277);

	Tes	= (Uint32)100 * Gas6_2Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;
	Ne	= Gas6_2Ne123456C24DE;
	EchoStorAddr += 2*Gas6_2_NE_1234AB56A;
	for(Gas6_2Cnt=0;Gas6_2Cnt<Gas6_2NRept123456C;Gas6_2Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(Gas6_2FreqSelAry[6]);

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6_2Cnt<Gas6_2NRept123456C-1)
		{
			EchoStorAddr += 2*Gas6_2Ne123456C24DE;
			StartS1msModule(Gas6_2Tw123456C*FPGA_BC);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6_2FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;
//相关存储
	SaveNTempPt	= (int *)PPGAS6_2TABLE_START;
	*SaveNTempPt= 0x9908;
	SaveNTempPt++;
	*SaveNTempPt= Gas6_2FreqSelLow;
	SaveNTempPt++;
	*SaveNTempPt= Gas6_2FreqSelHi;
	SaveNTempPt++;
	SavePhaseWord();
	SaveNTempPt	= (int *)(PPGAS6_2TABLE_START+DataTotalNum+58);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
	SaveSTempPt	= (Uint16 *)(PPGAS6_2TABLE_START+DataTotalNum+4);
	StoreMiniAryPt	= &Gas6_2FMiniNumAry[0];
	StoreMini(6,SaveNTempPt,SaveSTempPt);
	//上传数据
	McbspSendData(PPGAS6_2TABLE_START,DataTotalNum+3*EchoNum+77);
	ChangePhase();
	return;
}


