//###########################################################################
//
// FILE:   T1T2DModeTop.c
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

#pragma CODE_SECTION(ST1T2DModeTop,"Datatable");

void ST1T2DModeTop(void)
{
	ScaleMn	= 1;	
	ScaleM	= 0;
	EchoNum	= 2*(2+T12DCBWNReptAB+T12DDEmnAB+3*T12DNRept890AB);
	DataTotalNum	= 4*(T12DCPMGNe1AB+T12DCBWNeAB*T12DCBWNReptAB+T12DCPMGNe2AB+T12DDENeAB*T12DDEmnAB+T12DNRept890AB*(T12DCPMGNe8AB+T12DCPMGNe9AB+T12DCPMGNe0AB));	
	MiniStorAddr1	= MINITABLE_START+1;
	PhaseFlag		= POSITIVE;	   
//A1+-
	RELAY_ON_CLOSE = RelayAry[T12DFreqSel];   //¼ÌµçÆ÷±ÕºÏ
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	Tes	= (Uint32)100 * T12DTesAB *  FPGA_COUNT;
	Tel	= Tes;  
	Ne	= T12DCPMGNe1AB;
	Pulse90StoreAddr	= T12D_STORE_START+(Uint32)DataTotalNum+24;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= T12D_STORE_START+(Uint32)12;
	for (T12DCnt=0;T12DCnt<2;T12DCnt++)
	{
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;
		if (T12DCnt==0)
		{
			InverseTurnFlag	= SET;
		}
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		if (T12DCnt==0)
		{		
			StartS1msModule(T12DCPMGTw1AB*FPGA_BC+T12D_REPAIR1-MINI_TEST);		
		}
		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*T12DCPMGNe1AB;					  
	}
//A11+-
	PhaseFlag		= POSITIVE;
	Tes	= (Uint32)100 * T12DCBWTeAB *  FPGA_COUNT;
	Tel	= Tes;  
	Ne	= T12DCBWNeAB;

	for (T12DCnt=0;T12DCnt<2*T12DCBWNReptAB;T12DCnt++)
	{
		if (T12DCnt==0)
		{
			StartS1msModule(T12DCBWTwAB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
			MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
			MiniStorAddr1	+=12;				
		}
		else
		{
			StartS1msModule(T12DCBWTwAB*FPGA_BC-T12D_REPAIR2);
		}
						
		DCWorkOnce(T12DFreqSel);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;	
		if (T12DCnt==T12DCBWNReptAB-1)
		{
			ChangePhase();
		}					  
	}
//A2+-
	PhaseFlag		= POSITIVE;
	Tes	= (Uint32)100 * T12DTesAB *  FPGA_COUNT;
	Tel	= Tes;  
	Ne	= T12DCPMGNe2AB;

	for (T12DCnt=0;T12DCnt<2;T12DCnt++)
	{
		StartS1msModule(T12DCPMGTw2AB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;				
				
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		
		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*T12DCPMGNe2AB;
		InverseTurnFlag	= SET;				  
	}
//DE:A34567+-
//	Tes	= (Uint32)100 * T12DTesAB *  FPGA_COUNT;	
	Ne	= T12DDENeAB;
	ScaleM	= T12DDEmAB;

	for (T12DCnt=0;T12DCnt<2*T12DDEmnAB;T12DCnt++)
	{
		StartS1msModule(T12DDETwAB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;				

		Tel	= (Uint32)100 * T12DTelABAry[T12DCnt>>1] *  FPGA_COUNT;	
		if (T12DCnt==2*T12DDEmnAB-1)
		{;}
		else
		{
			InverseTurnFlag	= SET;	
		}
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		
		ChangePhase();
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*T12DDENeAB;				  
	}
//A8+-
//	Tes	= (Uint32)100 * T12DTesAB *  FPGA_COUNT;
	Tel	= Tes;  	  
	Ne	= T12DCPMGNe8AB;
	ScaleM	= 0;

	for (T12DCnt=0;T12DCnt<2*T12DNRept890AB;T12DCnt++)
	{
		StartS1msModule(T12DCPMGTw8AB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;				
				
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T12DCnt==T12DNRept890AB-1)
		{
			 ChangePhase();
		}
				  
	}
	PhaseFlag		= POSITIVE;
//A9+-
	//Tes	= (Uint32)100 * 5 *  FPGA_COUNT;
	//Tel	= Tes;	  
	Ne	= T12DCPMGNe9AB;

	for (T12DCnt=0;T12DCnt<2*T12DNRept890AB;T12DCnt++)
	{
		StartS1msModule(T12DCPMGTw9AB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;				
				
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T12DCnt==T12DNRept890AB-1)
		{
			 ChangePhase();
		}				  
	}
	PhaseFlag		= POSITIVE;
//A10+-
	//Tes	= (Uint32)100 * 5 *  FPGA_COUNT;
	//Tel	= Tes;	  
	Ne	= T12DCPMGNe0AB;

	for (T12DCnt=0;T12DCnt<2*T12DNRept890AB;T12DCnt++)
	{
		StartS1msModule(T12DCPMGTw0AB*FPGA_BC+T12D_REPAIR1-MINI_TEST);
		MiniScan(FreqAry[T12DFreqSel],MiniStorAddr1+9,MiniStorAddr1);
		MiniStorAddr1	+=12;				
		if (T12DCnt==2*T12DNRept890AB-1)
		{	
			InverseTurnFlag	= SET;
		}
		DCWorkOnce(T12DFreqSel);
		//Delay(30);
		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;
		EchoStorAddr += 2*Ne;
		if (T12DCnt==T12DNRept890AB-1)
		{
			 ChangePhase();
		}				  
	}

	RELAY_ON_CLOSE = RelayAry[T12DFreqSel]<<8;   
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
//other data store
	SaveNTempPt	= (int *)T12D_STORE_START;
	*SaveNTempPt	= 0x9995;
	SaveNTempPt++;
	*SaveNTempPt	= 0x0060;
	SaveSixFreq();
	SaveNTempPt++;
	*SaveNTempPt	= T12DFreqSel;
	SaveNTempPt++;
	*SaveNTempPt	= 0x55AA;

	SaveNTempPt	= (int *)(T12D_STORE_START+DataTotalNum+21);
	SaveSTempPt	= (Uint16 *)(T12D_STORE_START+DataTotalNum+12);
	T12DMiniNumAry[0]= 5+2*T12DDEmnAB+6*T12DNRept890AB;
	StoreMiniAryPt	= &T12DMiniNumAry[0];
	StoreMini(1,SaveNTempPt,SaveSTempPt); 

	McbspSendData(T12D_STORE_START,DataTotalNum+3*EchoNum+24);
	return;		
}

