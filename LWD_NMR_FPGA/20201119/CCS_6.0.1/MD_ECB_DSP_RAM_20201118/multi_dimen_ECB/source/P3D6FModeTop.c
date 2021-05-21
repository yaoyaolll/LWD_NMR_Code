/*
 * P3D6FModeTop.c
 *
 *  Created on: 2020-5-12
 *      Author: PJX
 */

 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(P3D6FModeTop,"Datatable");

void P3D6FModeTop(void)       //3D6F主函数
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零

	/********************20201022修改**************************/
	// 将3D6F模式NREPT for 3E or 4F or 5F固定为8 4 2，不使用下发参数
	//EchoNum	= 7+P3D6FNRept1C+P3D6FNRept2D+P3D6FNRept3E+P3D6FNRept4F+P3D6FNRept5F;
	//DataTotalNum	= 2*(P3D6FNe1A+P3D6FNe2A+P3D6FNe3A+P3D6FNe4A+P3D6FNe5B+P3D6FNe6B+P3D6FNRept1C*P3D6FNe1C+P3D6FNRept2D*P3D6FNe2D+P3D6FNRept3E*P3D6FNe3E+P3D6FNRept4F*P3D6FNe4F+P3D6FNRept5F*P3D6FNe5F+P3D6FNe6F);
	EchoNum	= 7+P3D6FNRept1C+P3D6FNRept2D+8+4+2;
	DataTotalNum	= 2*(P3D6FNe1A+P3D6FNe2A+P3D6FNe3A+P3D6FNe4A+P3D6FNe5B+P3D6FNe6B+P3D6FNRept1C*P3D6FNe1C+
			          P3D6FNRept2D*P3D6FNe2D+8*P3D6FNe3E+4*P3D6FNe4F+2*P3D6FNe5F+P3D6FNe6F);

	//3D6F__1A
		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[1]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

		Tes	= (Uint32)100 * P3D6F_TE_1A * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe1A;
		Pulse90StoreAddr	= P3D6FSTABLE_START+(Uint32)DataTotalNum+77;  //0x123897
		PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;                   //0x1238DC
		PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;                 //0x123921
		EchoStorAddr		= P3D6FSTABLE_START+(Uint32)4;                //0x120004
		DCWorkOnce(P3D6FFreqSelAry[1]);
	 //3D6F__1C
		StartS1msModule(P3D6FTw1C*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	   	Tes	= (Uint32)100 * P3D6F_TE_1C * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe1C;
		EchoStorAddr += 2*P3D6FNe1A;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept1C;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[1]);
			EchoStorAddr += 2*P3D6FNe1C;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept1C-1)
			{
				StartS1msModule(P3D6FTw1C*FPGA_BC);	//1个计数为
			}
		}

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[1]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//3D6F__2A
		StartS1msModule(1000-MINI_TEST);    //for test

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[2]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[2]],MINITABLE_START+34,MINITABLE_START+25);

		Tes	= (Uint32)100 * P3D6F_TE_2A * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe2A;
		Pulse90StoreAddr++;          // 0x1238B8
		PulseF180StoreAddr++;		 // 0x1238FD
		PulseL180StoreAddr++;		 // 0x123942
		DCWorkOnce(P3D6FFreqSelAry[2]);

		 //3D6F__2D
		StartS1msModule(P3D6FTw2D*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[2]],MINITABLE_START+46,MINITABLE_START+37);

		Tes	= (Uint32)100 * P3D6F_TE_2D * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe2D;
		EchoStorAddr += 2*P3D6FNe2A;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept2D;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[2]);
			EchoStorAddr += 2*P3D6FNe2D;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept2D-1)
			{
				StartS1msModule(P3D6FTw2D*FPGA_BC);	//1个计数为
			}
		}

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[2]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//3D6F__3A
		StartS1msModule(1000-MINI_TEST);    //for test

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[3]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[3]],MINITABLE_START+58,MINITABLE_START+49);

		Tes	= (Uint32)100 * P3D6F_TE_3A * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe3A;
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(P3D6FFreqSelAry[3]);

		 //3D6F__3E
		StartS1msModule(P3D6FTw3E*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[3]],MINITABLE_START+70,MINITABLE_START+61);

		Tes	= (Uint32)100 * P3D6F_TE_3E * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe3E;
		EchoStorAddr += 2*P3D6FNe3A;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept3E;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[3]);
			EchoStorAddr += 2*P3D6FNe3E;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept3E-1)
			{
				StartS1msModule(P3D6FTw3E*FPGA_BC);	//1个计数为
			}
		}

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[3]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//3D6F__4A
		StartS1msModule(1000-MINI_TEST);    //for test

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[4]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[4]],MINITABLE_START+82,MINITABLE_START+73);

		Tes	= (Uint32)100 * P3D6F_TE_4A * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe4A;
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(P3D6FFreqSelAry[4]);

		 //3D6F__4F
		StartS1msModule(P3D6FTw4F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[4]],MINITABLE_START+94,MINITABLE_START+85);

		Tes	= (Uint32)100 * P3D6F_TE_4F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe4F;
		EchoStorAddr += 2*P3D6FNe4A;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept4F;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[4]);
			EchoStorAddr += 2*P3D6FNe4F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept4F-1)
			{
				StartS1msModule(P3D6FTw4F*FPGA_BC);	//1个计数为
			}
		}

		 //3D6F__4F
		StartS1msModule(P3D6FTw4F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[4]],MINITABLE_START+106,MINITABLE_START+97);

		Tes	= (Uint32)100 * P3D6F_TE_4F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe4F;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept4F;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[4]);
			EchoStorAddr += 2*P3D6FNe4F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept4F-1)
			{
				StartS1msModule(P3D6FTw4F*FPGA_BC);	//1个计数为
			}
		}

		 //3D6F__4F
		StartS1msModule(P3D6FTw4F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[4]],MINITABLE_START+118,MINITABLE_START+109);

		Tes	= (Uint32)100 * P3D6F_TE_4F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe4F;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept4F;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[4]);
			EchoStorAddr += 2*P3D6FNe4F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept4F-1)
			{
				StartS1msModule(P3D6FTw4F*FPGA_BC);	//1个计数为
			}
		}

		 //3D6F__4F
		StartS1msModule(P3D6FTw4F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[4]],MINITABLE_START+130,MINITABLE_START+121);

		Tes	= (Uint32)100 * P3D6F_TE_4F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe4F;
		for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept4F;P3D6FCnt++)
		{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[4]);
			EchoStorAddr += 2*P3D6FNe4F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			if(P3D6FCnt<P3D6FNRept4F-1)
			{
				StartS1msModule(P3D6FTw4F*FPGA_BC);	//1个计数为
			}
		}

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[4]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//3D6F__5B
		StartS1msModule(1000-MINI_TEST);    //for test

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[5]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[5]],MINITABLE_START+142,MINITABLE_START+133);

		Tes	= (Uint32)100 * P3D6F_TE_5B * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe5B;
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(P3D6FFreqSelAry[5]);

		//3D6F__5F
		StartS1msModule(P3D6FTw5F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[5]],MINITABLE_START+154,MINITABLE_START+145);

		Tes	= (Uint32)100 * P3D6F_TE_5F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe5F;
		EchoStorAddr += 2*P3D6FNe5B;
		/**********************20201022修改**************************/
		// 将5F循环次数固定为2
		//for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept5F;P3D6FCnt++)
		//for(P3D6FCnt=0;P3D6FCnt<2;P3D6FCnt++)
		//{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[5]);
			EchoStorAddr += 2*P3D6FNe5F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			//if(P3D6FCnt<P3D6FNRept5F-1)
			//{
				//StartS1msModule(P3D6FTw5F*FPGA_BC);	//1个计数为
			//}
		//}

		//3D6F__5F
		StartS1msModule(P3D6FTw5F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[5]],MINITABLE_START+166,MINITABLE_START+157);

		Tes	= (Uint32)100 * P3D6F_TE_5F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe5F;
		//for(P3D6FCnt=0;P3D6FCnt<P3D6FNRept5F;P3D6FCnt++)
		//{
			Pulse90StoreAddr++;
			PulseF180StoreAddr++;
			PulseL180StoreAddr++;
			DCWorkOnce(P3D6FFreqSelAry[5]);
			EchoStorAddr += 2*P3D6FNe5F;

			//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
			//if(P3D6FCnt<P3D6FNRept5F-1)
			//{
				//StartS1msModule(P3D6FTw5F*FPGA_BC);	//1个计数为
			//}
		//}

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[5]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//3D6F__6B
		StartS1msModule(1000-MINI_TEST);    //for test

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[6]];   //继电器闭合
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		MiniScan(FreqAry[P3D6FFreqSelAry[6]],MINITABLE_START+178,MINITABLE_START+169);

		Tes	= (Uint32)100 * P3D6F_TE_6B * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe6B;
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(P3D6FFreqSelAry[6]);

		 //3D6F__6F
		StartS1msModule(P3D6FTw6F*FPGA_BC-MINI_TEST);

		MiniScan(FreqAry[P3D6FFreqSelAry[6]],MINITABLE_START+190,MINITABLE_START+181);

		Tes	= (Uint32)100 * P3D6F_TE_6F * FPGA_COUNT;
		Tel	= Tes;
		Ne	= P3D6FNe6F;
		EchoStorAddr += 2*P3D6FNe6B;
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		DCWorkOnce(P3D6FFreqSelAry[6]);

		RELAY_ON_CLOSE = RelayAry[P3D6FFreqSelAry[6]]<<8;   //继电器断开
		Delay(120);
		RELAY_ON_CLOSE = 0x0000;

		//相关存储
		SaveNTempPt	= (int *)P3D6FSTABLE_START;
		*SaveNTempPt= 0x9911;
		SaveNTempPt++;
		*SaveNTempPt= P3D6FFreqSelLow;
		SaveNTempPt++;
		*SaveNTempPt= P3D6FFreqSelHi;
		SaveNTempPt++;
		SavePhaseWord();
		SaveNTempPt	= (int *)(P3D6FSTABLE_START+DataTotalNum+58);
		*SaveNTempPt= 0x294;
		SaveNTempPt++;
		SaveSTempPt	= (Uint16 *)(P3D6FSTABLE_START+DataTotalNum+4);
		StoreMiniAryPt	= &P3D6FMiniNumAry[0];
		StoreMini(6,SaveNTempPt,SaveSTempPt);
		//上传数据
		McbspSendData(P3D6FSTABLE_START,DataTotalNum+3*EchoNum+77);
		ChangePhase();
		return;
}


