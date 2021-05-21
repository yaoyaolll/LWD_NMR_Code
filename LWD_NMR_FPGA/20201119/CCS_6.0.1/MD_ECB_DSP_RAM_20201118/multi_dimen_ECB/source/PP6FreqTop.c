 /*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(PP6ModeTop,"Datatable");

//6Ƶpp������
void PP6ModeTop(void)       //6Ƶpp������
{      
	ScaleMn	= 1;
	ScaleM	= 0;		//�ڴ�ģʽ�У�ScaleM����һֱ��Ϊ��
	EchoNum	= 10+2*PP6FNRept14C+2*PP6FNRept36C;
	DataTotalNum	= 4*(PP6FNe14A+PP6FNe1346C*(PP6FNRept14C+PP6FNRept36C)+4*PP6FNe2356DE);  
 
//6Ƶpp__1A
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[1]];   //�̵����պ�
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
 //6Ƶpp__1C
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
		    
		//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(PP6FCnt<PP6FNRept14C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1������Ϊ    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[1]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//6Ƶpp__2D 
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]];   //�̵����պ�
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
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//6Ƶpp__3D
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[3]],MINITABLE_START+58,MINITABLE_START+49);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[3]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;                
//6Ƶpp__2E
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[2]],MINITABLE_START+46,MINITABLE_START+37);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[2]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[2]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;                                      
//6Ƶpp__3E
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[3]],MINITABLE_START+70,MINITABLE_START+61);
                       
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[3]); 
//6Ƶpp__3C
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
		      
		//�ӳ�30ms��13C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(PP6FCnt<PP6FNRept36C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1������Ϊ    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[3]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
//6Ƶpp__4A
	StartS1msModule(1500-MINI_TEST);    //for test 
	    
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[4]];   //�̵����պ�
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
//6Ƶpp__4C   
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
		        
		//�ӳ�30ms��1C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(PP6FCnt<PP6FNRept14C-1)
		{
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1������Ϊ    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[4]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
//6Ƶpp__5D
	StartS1msModule(1000-MINI_TEST);    //for test   

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]];   //�̵����պ�
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
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;    
//6Ƶpp__6D 
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[6]],MINITABLE_START+142,MINITABLE_START+133);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[6]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;       
//6Ƶpp__5E
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[5]],MINITABLE_START+130,MINITABLE_START+121);

	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[5]);   
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[5]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;     
//6Ƶpp__6E
	StartS1msModule(1000-MINI_TEST);    //for test

	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
   
	MiniScan(FreqAry[PP6FreqSelAry[6]],MINITABLE_START+154,MINITABLE_START+145);
                       
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
	EchoStorAddr += 2*PP6FNe2356DE;
	DCWorkOnce(PP6FreqSelAry[6]); 
//6�pp__6C  
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
		       
		//�ӳ�20ms��13C_TW,��Ҫ��ȥ����ʱ��,����ʱ����Ҫʵ��ȷ����
		if(PP6FCnt<PP6FNRept36C-1)
		{
			EchoStorAddr += 2*PP6FNe1346C;
			StartS1msModule(PP6FTw1346C*FPGA_BC-PP6_REPAIR1);	//1������Ϊ    
		}
	}
   
	RELAY_ON_CLOSE = RelayAry[PP6FreqSelAry[6]]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;    
//��ش洢
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
	StoreMini(6,SaveNTempPt,SaveSTempPt); ////����ĳһ����Ƶ��9��miniɨƵ���ƽ��ֵ��������ֵ��ƽ��ֵ��������׼ƫ���ƽ��ֵ
//�ϴ�����
	McbspSendData(PP6TABLE_START,DataTotalNum+3*EchoNum+77);  
	ChangePhase();
	return; 
}

/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 


