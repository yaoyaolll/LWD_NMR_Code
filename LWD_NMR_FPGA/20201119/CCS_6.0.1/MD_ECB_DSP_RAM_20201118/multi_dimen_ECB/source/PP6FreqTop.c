 /*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PP6ModeTop,"Datatable");

//6频pp主函数
void PP6ModeTop(void)       //6频pp主函数
{      
	ScaleMn	= 1;
	ScaleM	= 0;		//在此模式中，ScaleM参数一直都为零
	EchoNum	= 10+2*PP6FNRept14C+2*PP6FNRept36C;
	DataTotalNum	= 4*(PP6FNe14A+PP6FNe1346C*(PP6FNRept14C+PP6FNRept36C)+4*PP6FNe2356DE);  
 
//6频pp__1A
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[1]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 

	MiniScan(FreqAry[PP6FreqSelAry[1]],MINITABLE_START+10,MINITABLE_START+1);
            
	Tes	= (Uint32)100 * PP6FTe14A2356DE * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= PP6FNe14A;
	Pulse90StoreAddr	= PP6TABLE_START+(Uint32)DataTotalNum+77;
	PulseF180StoreAddr	= Pulse90StoreAddr+EchoNum;
	PulseL180StoreAddr	= PulseF180StoreAddr+EchoNum;
	EchoStorAddr		= PP6TABLE_START+(Uint32)4;
	DCWorkOnce(PP6FreqSelAry[1]);
 //6频pp__1C
	StartS1msModule(PP6FTw1346C*FPGA_BC+PP6_REPAIR2-MINI_TEST);      

	MiniScan(FreqAry[PP6FreqSelAry[1]],MINITABLE_START+22,MINITABLE_START+13);

   	Tes	= (Uint32)100 * PP6FTe1346C * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= PP6FNe1346C;
	EchoStorAddr += 2*PP6FNe14A;
	for(PP6FCnt=0;PP6FCnt<PP6FNRept14C;PP6FCnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(PP6FreqSelAry[1]);     
		EchoStorAddr += 2*PP6FNe1346C;
		    
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(PP6FCnt<PP6FNRept14C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[1]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//6频pp__2D 
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[2]],MINITABLE_START+34,MINITABLE_START+25);
    
	Tes	= (Uint32)100 * PP6FTe14A2356DE * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= PP6FNe2356DE;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PP6FreqSelAry[2]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//6频pp__3D
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[3]],MINITABLE_START+58,MINITABLE_START+49);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[3]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;                
//6频pp__2E
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[2]],MINITABLE_START+46,MINITABLE_START+37);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[2]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;                                      
//6频pp__3E
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[3]],MINITABLE_START+70,MINITABLE_START+61);
                       
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[3]); 
//6频pp__3C
	StartS1msModule(PP6FTw1346C*FPGA_BC+PP6_REPAIR2-MINI_TEST);    //for test     

	MiniScan(FreqAry[PP6FreqSelAry[3]],MINITABLE_START+82,MINITABLE_START+73);
   
   	Tes	= (Uint32)100 * PP6FTe1346C * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= PP6FNe1346C;
	EchoStorAddr += 2*PP6FNe2356DE;
	for(PP6FCnt=0;PP6FCnt<PP6FNRept36C;PP6FCnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(PP6FreqSelAry[3]);   
		EchoStorAddr += 2*PP6FNe1346C;
		      
		//延迟30ms（13C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(PP6FCnt<PP6FNRept36C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
//6频pp__4A
	StartS1msModule(1500-MINI_TEST);    //for test 
	    
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[4]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;

	MiniScan(FreqAry[PP6FreqSelAry[4]],MINITABLE_START+94,MINITABLE_START+85);

	Tes	= (Uint32)100 * PP6FTe14A2356DE * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= PP6FNe14A;

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PP6FreqSelAry[4]);
//6频pp__4C   
	StartS1msModule(PP6FTw1346C*FPGA_BC+PP6_REPAIR2-MINI_TEST);    //for test     

	MiniScan(FreqAry[PP6FreqSelAry[4]],MINITABLE_START+106,MINITABLE_START+97);

   	Tes	= (Uint32)100 * PP6FTe1346C * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= PP6FNe1346C;
	EchoStorAddr += 2*PP6FNe14A;
	for(PP6FCnt=0;PP6FCnt<PP6FNRept14C;PP6FCnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(PP6FreqSelAry[4]); 
		EchoStorAddr += 2*PP6FNe1346C;
		        
		//延迟30ms（1C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(PP6FCnt<PP6FNRept14C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[4]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
//6频pp__5D
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[5]],MINITABLE_START+118,MINITABLE_START+109);
    
	Tes	= (Uint32)100 * PP6FTe14A2356DE * FPGA_COUNT;
	Tel	= Tes;  
	Ne	= PP6FNe2356DE;
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	DCWorkOnce(PP6FreqSelAry[5]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;    
//6频pp__6D 
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[6]],MINITABLE_START+142,MINITABLE_START+133);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[6]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;       
//6频pp__5E
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[5]],MINITABLE_START+130,MINITABLE_START+121);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[5]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//6频pp__6E
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[6]],MINITABLE_START+154,MINITABLE_START+145);
                       
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[6]); 
//6祊p__6C  
	StartS1msModule(PP6FTw1346C*FPGA_BC+PP6_REPAIR2-MINI_TEST);    //for test     

	MiniScan(FreqAry[PP6FreqSelAry[6]],MINITABLE_START+166,MINITABLE_START+157);
   
   	Tes	= (Uint32)100 * PP6FTe1346C * FPGA_COUNT;
	Tel	= Tes;   
	Ne	= PP6FNe1346C;
	EchoStorAddr += 2*PP6FNe2356DE;
	for(PP6FCnt=0;PP6FCnt<PP6FNRept36C;PP6FCnt++)
	{		
		Pulse90StoreAddr++;
		PulseF180StoreAddr++;
		PulseL180StoreAddr++;		
		DCWorkOnce(PP6FreqSelAry[6]);  		
		       
		//延迟20ms（13C_TW,还要减去补偿时间,补偿时间需要实验确定）
		if(PP6FCnt<PP6FNRept36C-1)
		{
			EchoStorAddr += 2*PP6FNe1346C;
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1个计数为    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;    
//相关存储
	SaveNTempPt	= (int *)PP6TABLE_START;
	*SaveNTempPt= 0x9903;
	SaveNTempPt++;
	*SaveNTempPt= PP6FreqSelLow;  
	SaveNTempPt++;
	*SaveNTempPt= PP6FreqSelHi; 
	SaveNTempPt++; 
	SavePhaseWord();
  	SaveNTempPt	= (int *)(PP6TABLE_START+DataTotalNum+58);
	*SaveNTempPt= 0x294;
	SaveNTempPt++;
  	SaveSTempPt	= (Uint16 *)(PP6TABLE_START+DataTotalNum+4);
	StoreMiniAryPt	= &PP6FMiniNumAry[0];
	StoreMini(6,SaveNTempPt,SaveSTempPt); ////计算某一工作频率9个mini扫频点的平均值、噪声均值的平均值、噪声标准偏差的平均值
//上传数据
	McbspSendData(PP6TABLE_START,DataTotalNum+3*EchoNum+77);  
	ChangePhase();
	return; 
}

/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 


