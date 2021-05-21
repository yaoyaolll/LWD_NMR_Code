 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(Oil3ModeTop,"Datatable");

//pp_oil主函数
void Oil3ModeTop(void)       //pp_oil主函数
{         
	ScaleMn	= 1;	
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 5+5*Oil3NRept123C+Oil3NRept3D+Oil3NRept3E+Oil3NRept3F;
	DataTotalNum = 2*(2*OIL3_NE_1AB+5*Oil3Ne123C*Oil3NRept123C+2*OIL3_NE_2AB+OIL3_NE_3A+Oil3Ne3D*Oil3NRept3D+Oil3Ne3E*Oil3NRept3E+Oil3Ne3F*Oil3NRept3F);

//ppoil__1A
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[1]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 

	MiniScan(FreqAry[Oil3FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 *OIL3_TE_1AB *  FPGA_COUNT;
	Tel	= Tes;  
	Ne	= OIL3_NE_1AB;
	Pulse90StoreAddr	= OIL3TABLE_START+(Uint32)DataTotalNum+40;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= OIL3TABLE_START+(Uint32)3;
	DCWorkOnce(Oil3FreqSelAry[1]);
//ppoil__1C
	StartS1msModule(Oil3Tw123C*FPGA_BC+PPoil_REPAIR2-MINI_TEST);   

	MiniScan(FreqAry[Oil3FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

	Tes	= (Uint32)100*Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne123C;
	EchoStorAddr += 2*OIL3_NE_1AB;   
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept123C;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[1]);    
		EchoStorAddr += 2*Oil3Ne123C;

		if(Oil3Cnt<Oil3NRept123C-1)
		{
			StartS1msModule(Oil3Tw123C*FPGA_BC-PPoil_REPAIR1);
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//ppoil__2A  
	StartS1msModule(1500-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[2]];   
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Oil3FreqSelAry[2]],MINITABLE_START+58,MINITABLE_START+49);
            
	Tes	= (Uint32)100*OIL3_TE_2AB * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= OIL3_NE_2AB;  
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Oil3FreqSelAry[2]);
//ppoil__2C
	StartS1msModule(Oil3Tw123C*FPGA_BC+PPoil_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Oil3FreqSelAry[2]],MINITABLE_START+70,MINITABLE_START+61);

	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne123C;
	EchoStorAddr += 2*OIL3_NE_2AB; 
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept123C;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[2]);    
		EchoStorAddr += 2*Oil3Ne123C;

		if(Oil3Cnt<Oil3NRept123C-1)
		{
			StartS1msModule(Oil3Tw123C*FPGA_BC-PPoil_REPAIR1);
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//ppoil__1B
	StartS1msModule(1000-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[1]];   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
   
	MiniScan(FreqAry[Oil3FreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);
               
	Tes	= (Uint32)100*OIL3_TE_1AB *FPGA_COUNT;
	Tel	= Tes;  
	Ne	= OIL3_NE_1AB; 
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Oil3FreqSelAry[1]);
//ppoil__1C   
	StartS1msModule(Oil3Tw123C*FPGA_BC+PPoil_REPAIR2-MINI_TEST);
   
	MiniScan(FreqAry[Oil3FreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);
   
	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne123C;
	EchoStorAddr += 2*OIL3_NE_1AB; 
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept123C;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[1]);    
		EchoStorAddr += 2*Oil3Ne123C;

		if(Oil3Cnt<Oil3NRept123C-1)
		{
			StartS1msModule(Oil3Tw123C*FPGA_BC-PPoil_REPAIR1);
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//ppoil__2B 
	StartS1msModule(1500-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[2]];   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Oil3FreqSelAry[2]],MINITABLE_START+82,MINITABLE_START+73);
            
	Tes	= (Uint32)100*OIL3_TE_2AB * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= OIL3_NE_2AB;  
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Oil3FreqSelAry[2]);
//ppoil__2C   
	StartS1msModule(Oil3Tw123C*FPGA_BC+PPoil_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Oil3FreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne123C;
	EchoStorAddr += 2*OIL3_NE_2AB; 
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept123C;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[2]);    
		EchoStorAddr += 2*Oil3Ne123C;

		if(Oil3Cnt<Oil3NRept123C-1)
		{
			StartS1msModule(Oil3Tw123C*FPGA_BC-PPoil_REPAIR1);//此处等待时间与一维不一样，经过与其他模式对比，怀疑原一维此处不对。
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//ppoil__3A 
	StartS1msModule(1500-MINI_TEST);

	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[3]];   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Oil3FreqSelAry[3]],MINITABLE_START+106,MINITABLE_START+97);

	Tes	= (Uint32)100*OIL3_TE_3A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= OIL3_NE_3A; 
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;            
	DCWorkOnce(Oil3FreqSelAry[3]);
//ppoil__3C
	StartS1msModule(Oil3Tw123C*FPGA_BC+PPoil_REPAIR3-PPoil_REPAIR1-MINI_TEST);

	MiniScan(FreqAry[Oil3FreqSelAry[3]],MINITABLE_START+118,MINITABLE_START+109);

	Tes	= (Uint32)100 *Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne123C;
	EchoStorAddr += 2*OIL3_NE_3A; 
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept123C;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[3]);    
		EchoStorAddr += 2*Oil3Ne123C;

		if(Oil3Cnt<Oil3NRept123C-1)
		{
			StartS1msModule(Oil3Tw123C*FPGA_BC-PPoil_REPAIR1);
		}
	}
//ppoil__3D
	StartS1msModule(Oil3Tw3D*FPGA_BC+PPoil_REPAIR3-MINI_TEST);         

	MiniScan(FreqAry[Oil3FreqSelAry[3]],MINITABLE_START+130,MINITABLE_START+121); 

	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne3D;
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept3D;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[3]);    
		EchoStorAddr += 2*Oil3Ne3D;

		if(Oil3Cnt<Oil3NRept3D-1)
		{
			StartS1msModule(Oil3Tw3D*FPGA_BC-PPoil_REPAIR1);
		}
	}
//ppoil__3E
	StartS1msModule(Oil3Tw3E*FPGA_BC+PPoil_REPAIR3-MINI_TEST);         

	MiniScan(FreqAry[Oil3FreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);   

	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne3E; 
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept3E;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[3]);    
		EchoStorAddr += 2*Oil3Ne3E;
		if(Oil3Cnt<Oil3NRept3E-1)
		{
			StartS1msModule(Oil3Tw3E*FPGA_BC-PPoil_REPAIR1);
		}
	}
//ppoil__3F
	StartS1msModule(Oil3Tw3F*FPGA_BC+PPoil_REPAIR3-MINI_TEST);         

	MiniScan(FreqAry[Oil3FreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);   

	Tes	= (Uint32)100 * Oil3Te1C2C3CDEF * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= Oil3Ne3F;
	for(Oil3Cnt=0;Oil3Cnt<Oil3NRept3F;Oil3Cnt++)
	{
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Oil3FreqSelAry[3]);    

		if(Oil3Cnt<Oil3NRept3F-1)
		{
			EchoStorAddr += 2*Oil3Ne3F;
			StartS1msModule(Oil3Tw3F*FPGA_BC-PPoil_REPAIR1);
		}
	}
	RELAY_ON_CLOSE = RelayAry[Oil3FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//相关存储
	SaveNTempPt	= (int *)OIL3TABLE_START;
	*SaveNTempPt= 0x9904;
	SaveNTempPt++;
	*SaveNTempPt= Oil3FreqSel;  
	SaveNTempPt++; 
	SavePhaseWord();
	SaveNTempPt	= (int *)(OIL3TABLE_START+DataTotalNum+30);
	*SaveNTempPt= 0x294;
	SaveNTempPt	= (int *)(OIL3TABLE_START+DataTotalNum+31);
	SaveSTempPt	= (Uint16 *)(OIL3TABLE_START+DataTotalNum+3);
	StoreMiniAryPt	= &Oil3MiniNumAry[0];
	StoreMini(3,SaveNTempPt,SaveSTempPt); 
	McbspSendData(OIL3TABLE_START,DataTotalNum+3*EchoNum+40);
	ChangePhase();
	return;
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 


