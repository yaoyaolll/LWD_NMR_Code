//###########################################################################
//
// FILE:   T1T2ModeTop.c
//
// TITLE:  .
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H. | Changes since previous version (v.58 Alpha)
//      |             |      | Additional comments added to explain the PLL
//      |             |      |    initialization.
//      |             |      | Changed the PLL initialization to take into
//      |             |      |    account bit definitions for the PLLCR register
//      |             |      | Removed DFT initialization - no longer needed 
//      |             |      |    as of Rev C F2810/12 silicon
//      |             |      | Split some operations into their own function
//      |             |      |    for better modularity
//      |             |      | Added pipeline flush after the Flash Init
//###########################################################################
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ST1T2ModeTop,"Datatable");

void ST1T2ModeTop(void)
{
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零

	EchoNum	= 0;
	DataTotalNum = 0;
	for (T1T2Cnt=1;T1T2Cnt<=9;T1T2Cnt++)
	{
		EchoNum	+= T1T2NReptAAry[T1T2Cnt];
		DataTotalNum += T1T2NeAAry[T1T2Cnt]*T1T2NReptAAry[T1T2Cnt];
	}
	EchoNum	*= 2;
	DataTotalNum *= 4;

	MiniStorAddr1	= MINITABLE_START+1;
//A1	
	RELAY_ON_CLOSE = RelayAry[T1T2FreqSel];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 

	PhaseFlag		= POSITIVE;
	Tes	= (Uint32)100 * T1T2CPMGTe * FPGA_COUNT;
	Tel	= Tes;
	Ne	= T1T2NeAAry[1];
	Pulse90StoreAddr	= T1T2_STORE_START+(Uint32)DataTotalNum+24;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= T1T2_STORE_START+(Uint32)12;
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[1];T1T2Cnt++)
	{		  				
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;

		DCWorkOnce(T1T2FreqSel);

		if (T1T2Cnt==0)
		{
			StartS1msModule(T1T2TwAAry[1]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		}
		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		if (PhaseFlag==NEGATIVE)
		{
			EchoStorAddr += 2*(Uint32)Ne*T1T2NReptAAry[1];
		}
		else if(T1T2Cnt==2*T1T2NReptAAry[1]-1)
		{
			EchoStorAddr += 2*Ne;
		}
		else
		{
			EchoStorAddr -= 2*(Uint32)Ne*(T1T2NReptAAry[1]-1);
		}	
	}
//A5
	Ne	= T1T2NeAAry[5];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[5];T1T2Cnt++)
	{		  			
		StartS1msModule(T1T2TwAAry[5]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T1T2Cnt==T1T2NReptAAry[5]-1)
		{
			ChangePhase();
		}	
	}
	PhaseFlag		= POSITIVE;
//A4
	Ne	= T1T2NeAAry[4];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[4];T1T2Cnt++)
	{		  			
		StartS1msModule(T1T2TwAAry[4]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T1T2Cnt==T1T2NReptAAry[4]-1)
		{
			ChangePhase();
		}	
	}
	PhaseFlag		= POSITIVE;
//A2
	Ne	= T1T2NeAAry[2];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[2];T1T2Cnt++)
	{		  			
		StartS1msModule(T1T2TwAAry[2]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);
		
		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		if (PhaseFlag==NEGATIVE)
		{
			EchoStorAddr += 2*(Uint32)Ne*T1T2NReptAAry[2];
		}
		else if(T1T2Cnt==2*T1T2NReptAAry[2]-1)
		{
			EchoStorAddr += 2*Ne;
		}
		else
		{
			EchoStorAddr -= 2*(Uint32)Ne*(T1T2NReptAAry[2]-1);
		}	
	}
//A9
	Tes	= (Uint32)100 * T1T2CBWTe * FPGA_COUNT;
	Tel	= Tes;
	Ne	= T1T2NeAAry[9];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[9];T1T2Cnt++)
	{		  			
		if (T1T2Cnt==0)
		{
			StartS1msModule(T1T2TwAAry[9]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);
			MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
			MiniStorAddr1 += 12;		
		}
		else
		{
			StartS1msModule(T1T2TwAAry[9]*FPGA_BC-T1T2_REPAIR2);
		}		
		
		DCWorkOnce(T1T2FreqSel);

		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*(Uint32)Ne;
		if (T1T2Cnt==T1T2NReptAAry[9]-1)
		{
			ChangePhase();
		}
	}
	PhaseFlag		= POSITIVE;
//A8
	Ne	= T1T2NeAAry[8];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[8];T1T2Cnt++)
	{		  			
		if (T1T2Cnt==0)
		{
			StartS1msModule(T1T2TwAAry[8]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);
			MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
			MiniStorAddr1 += 12;		
		}
		else
		{
			StartS1msModule(T1T2TwAAry[8]*FPGA_BC-T1T2_REPAIR2);
		}		
		
		DCWorkOnce(T1T2FreqSel);

		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T1T2Cnt==T1T2NReptAAry[8]-1)
		{
			ChangePhase();
		}
	}
	PhaseFlag		= POSITIVE;
//A3
	Tes	= (Uint32)100 * T1T2CPMGTe * FPGA_COUNT;
	Tel	= Tes;
	Ne	= T1T2NeAAry[3];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[3];T1T2Cnt++)
	{		  		
		StartS1msModule(T1T2TwAAry[3]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);

		ChangePhase();	
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		if (PhaseFlag==NEGATIVE)
		{
			EchoStorAddr += 2*(Uint32)Ne*T1T2NReptAAry[3];
		}
		else if(T1T2Cnt==2*T1T2NReptAAry[3]-1)
		{
			EchoStorAddr += 2*Ne;
		}
		else
		{
			EchoStorAddr -= 2*(Uint32)Ne*(T1T2NReptAAry[3]-1);
		}
	}
//A7
	Ne	= T1T2NeAAry[7];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[7];T1T2Cnt++)
	{		  		
		StartS1msModule(T1T2TwAAry[7]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);

		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T1T2Cnt==T1T2NReptAAry[7]-1)
		{
			ChangePhase();
		}
	}
	PhaseFlag		= POSITIVE;
//A6
	Ne	= T1T2NeAAry[6];
	for (T1T2Cnt=0;T1T2Cnt<2*T1T2NReptAAry[6];T1T2Cnt++)
	{		  			
		StartS1msModule(T1T2TwAAry[6]*FPGA_BC+T1T2_REPAIR1-MINI_TEST);		
		MiniScan(FreqAry[T1T2FreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1 += 12;		
		
		DCWorkOnce(T1T2FreqSel);
	
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T1T2Cnt==T1T2NReptAAry[6]-1)
		{
			ChangePhase();
		}
	}

	RELAY_ON_CLOSE = RelayAry[T1T2FreqSel]<<8;   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
//other data store
	SaveNTempPt	= (int *)T1T2_STORE_START;
	*SaveNTempPt	= 0x9995;
	SaveNTempPt++;
	*SaveNTempPt	= 0x0040;
	SaveSixFreq();
	SaveNTempPt++;
	*SaveNTempPt	= T1T2FreqSel;
	SaveNTempPt++;
	*SaveNTempPt	= 0x55AA;

	SaveNTempPt	= (int *)(T2D_STORE_START+DataTotalNum+21);
	SaveSTempPt	= (Uint16 *)(T2D_STORE_START+DataTotalNum+12);
	T1T2MiniNumAry[0]= EchoNum+2-2*(T1T2NReptAAry[8]+T1T2NReptAAry[9]);
	StoreMiniAryPt	= &T1T2MiniNumAry[0];
	StoreMini(1,SaveNTempPt,SaveSTempPt); 

	McbspSendData(T2D_STORE_START,DataTotalNum+3*EchoNum+24);
	return;		
}

