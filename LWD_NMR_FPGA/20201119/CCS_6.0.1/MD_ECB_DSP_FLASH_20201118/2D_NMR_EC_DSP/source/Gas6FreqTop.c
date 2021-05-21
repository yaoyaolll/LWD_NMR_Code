 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(Gas6ModeTop,"Datatable");

//pp_oil
void Gas6ModeTop(void)       //pp_oil
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
	ScaleM	= 0;		//ScaleM
	EchoNum	= 10+2*(Gas6NRept24D+Gas6NRept24E)+8*Gas6NRept1234C+2*Gas6NRept56C;
	DataTotalNum = 2*(10*GAS6_NE_1234AB56A+2*Gas6Ne123456C24DE*(4*Gas6NRept1234C+Gas6NRept24D+Gas6NRept24E+Gas6NRept56C));	      
//gas_1A
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[1]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Gas6FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr	= PP6TABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PP6TABLE_START+(Uint32)4;
	DCWorkOnce(Gas6FreqSelAry[1]);
//ppgas__1C 
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR2-MINI_TEST);
   
	MiniScan(FreqAry[Gas6FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[1]);         
		EchoStorAddr += 2*Gas6Ne123456C24DE;

		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//gas_2A
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[2]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+58,MINITABLE_START+49);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[2]);
//ppgas__2C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+70,MINITABLE_START+61);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[2]);        
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		 
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//gas_1B
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[1]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[1]],MINITABLE_START+34,MINITABLE_START+25);

	Tes	= (Uint32)100 * GAS6_TE_1234B * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[1]);
//ppgas__1C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[1]],MINITABLE_START+46,MINITABLE_START+37);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[1]);   
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		      
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//gas_2B
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[2]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+82,MINITABLE_START+73);

	Tes	= (Uint32)100 * GAS6_TE_1234B * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[2]); 
//ppgas__2C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR2-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+94,MINITABLE_START+85);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[2]);        
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		 
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	} 
//ppgas__2D
	StartS1msModule(Gas6Tw24D*FPGA_BC+PPgas_REPAIR3-MINI_TEST);   
      
	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+106,MINITABLE_START+97);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept24D;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[2]);       
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		  
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept24D-1)
		{
			StartS1msModule(Gas6Tw24D*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
//ppgas__2E      
	StartS1msModule(Gas6Tw24E*FPGA_BC+PPgas_REPAIR3-MINI_TEST);   
      
	MiniScan(FreqAry[Gas6FreqSelAry[2]],MINITABLE_START+118,MINITABLE_START+109);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept24E;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[2]);  
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		       
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept24E-1)
		{
			StartS1msModule(Gas6Tw24E*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//gas_3A           
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[3]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[3]],MINITABLE_START+130,MINITABLE_START+121);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[3]);
//ppgas__3C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR2-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[3]],MINITABLE_START+142,MINITABLE_START+133);     

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[3]);     
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		    
		//迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}   
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//gas_4A
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[4]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+178,MINITABLE_START+169);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[4]);
//ppgas__4C 
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+190,MINITABLE_START+181);     

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[4]);   
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		      
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}   
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
//gas_3B
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[3]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[3]],MINITABLE_START+154,MINITABLE_START+145);

	Tes	= (Uint32)100 * GAS6_TE_1234B * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[3]);
//ppgas__3C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[3]],MINITABLE_START+166,MINITABLE_START+157);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[3]);
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		         
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
//gas_4B
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[4]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+202,MINITABLE_START+193);

	Tes	= (Uint32)100 * GAS6_TE_1234B * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[4]); 
//ppgas__4C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+214,MINITABLE_START+205);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept1234C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[4]);  
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		       
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept1234C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	} 
//ppgas__4D
	StartS1msModule(Gas6Tw24D*FPGA_BC+PPgas_REPAIR3-MINI_TEST);   
      
	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+226,MINITABLE_START+217);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept24D;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[4]);   
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		      
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept24D-1)
		{
			StartS1msModule(Gas6Tw24D*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
//ppgas__4E      
	StartS1msModule(Gas6Tw24E*FPGA_BC+PPgas_REPAIR3-MINI_TEST);   
      
	MiniScan(FreqAry[Gas6FreqSelAry[4]],MINITABLE_START+238,MINITABLE_START+229);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept24E;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[4]);  
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		       
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept24E-1)
		{
			StartS1msModule(Gas6Tw24E*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
//gas_5A
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[5]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Gas6FreqSelAry[5]],MINITABLE_START+250,MINITABLE_START+241);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[5]);
//ppgas__5C   
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR2-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[5]],MINITABLE_START+262,MINITABLE_START+253);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept56C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[5]); 
		EchoStorAddr += 2*Gas6Ne123456C24DE;
		        
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept56C-1)
		{
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[5]]<<8;   //继电
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//gas_6A
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[6]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[Gas6FreqSelAry[6]],MINITABLE_START+274,MINITABLE_START+265);

	Tes	= (Uint32)100 * GAS6_TE_123456A * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= GAS6_NE_1234AB56A;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(Gas6FreqSelAry[6]);
//ppgas__6C
	StartS1msModule(Gas6Tw123456C*FPGA_BC+PPgas_REPAIR3-MINI_TEST);

	MiniScan(FreqAry[Gas6FreqSelAry[6]],MINITABLE_START+286,MINITABLE_START+277);

   	Tes	= (Uint32)100 * Gas6Te123456C24DE * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= Gas6Ne123456C24DE;
	EchoStorAddr += 2*GAS6_NE_1234AB56A;
	for(Gas6Cnt=0;Gas6Cnt<Gas6NRept56C;Gas6Cnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(Gas6FreqSelAry[6]);     
		    
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(Gas6Cnt<Gas6NRept56C-1)
		{
			EchoStorAddr += 2*Gas6Ne123456C24DE;
			StartS1msModule(Gas6Tw123456C*FPGA_BC-PPgas_REPAIR1);	//1个计数为    
		}
	}
	RELAY_ON_CLOSE = RelayAry[Gas6FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;   
//相关存储
	SaveNTempPt	= (int *)PPGASTABLE_START;
	*SaveNTempPt= 0x9907;
	SaveNTempPt++;
	*SaveNTempPt= Gas6FreqSelLow;  
	SaveNTempPt++;
	*SaveNTempPt= Gas6FreqSelHi; 
	SaveNTempPt++; 
	SavePhaseWord();
  	SaveNTempPt	= (int *)(PPGASTABLE_START+DataTotalNum+58);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
  	SaveSTempPt	= (Uint16 *)(PP6TABLE_START+DataTotalNum+4);
	StoreMiniAryPt	= &Gas6FMiniNumAry[0];
	StoreMini(6,SaveNTempPt,SaveSTempPt);     
//上传数据
	McbspSendData(PPGASTABLE_START,DataTotalNum+3*EchoNum+77);
	ChangePhase();  
	return;
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 


