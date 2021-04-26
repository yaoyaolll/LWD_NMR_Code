/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(DeCpmgTop,"Datatable");

void DeCpmgTop(void)       //单TE单TW主函数
{      
	Ne			= STWTE_NE;
	ScaleM		= DCm;
	ScaleMn		= DCMn;

	// 暂时设置继电器端口为1
	DCFreqSel = 1;
	FreqAry[DCFreqSel]  = CenterFreq;

	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;      

	MiniScan(CenterFreq, DECPMGTABLE_START+4, DECPMGTABLE_START+7);   

	Tes	= (Uint32)100 * STWTE_TE * FPGA_COUNT;        	//短TE值 TE 0.1ms
	Tel	= Tes;                                        	//将SINGLE_TE转换为10ns 单位即FPGA计数值
	Pulse90StoreAddr	= DECPMGTABLE_START+2*Ne+20;  	//计算90°脉冲的幅值地址pluse90addr
	PulseF180StoreAddr	= DECPMGTABLE_START+2*Ne+21;  	//计算首个180°脉冲的幅值地址pluse180addr1
	PulseL180StoreAddr	= DECPMGTABLE_START+2*Ne+22;  	//计算末个180°脉冲的幅值地址pluse180addr2
	EchoStorAddr		= DECPMGTABLE_START+20;       	//计算回波数据的首地址echostoraddr
	InverseTurnFlag		= SET;							// -90脉冲

	DCWorkOnce(DCFreqSel);//工作一次

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
		
	StartS1msModule(10000); //延时10000+ms

	//存储
	SaveNTempPt	= (int *)(DECPMGTABLE_START);//数据存储指针指向单TETW表首地址
	*SaveNTempPt++= 0x9995;               	// 数据头
	*SaveNTempPt++= 2*Ne+23;				// 长度
	*SaveNTempPt++= 0x0001; 	     		// 工作模式
	*SaveNTempPt= CenterFreq*10;      		// 工作频率

	SaveNTempPt = (int *)(DECPMGTABLE_START + 16);
	*SaveNTempPt++ = 0;          		// Q值
	*SaveNTempPt++ = 0x294;				// 参考幅值
	*SaveNTempPt++ = Width90Pulse;      // 90度脉冲宽度
	SavePhaseWord();					//存储发射脉冲相位

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(DECPMGTABLE_START);
	int i=0;
	for (i=0;i<2*Ne+23;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 2*Ne+24;
		
	//上传数据
	//SciaSendDataNWords(DECPMGTABLE_START, 2*Ne+24);

	ChangePhase();//取反发射脉冲相位
	return;       
}

interrupt void XINT2_DCStorData(void)
{
    StoreCnt++;    			//中断计数StoreCnt加1
    if(StoreCnt==1)			//90°激励采集中断？
	{
		CalSignal(Acq90Num);//计算信号
		SavePulse(Pulse90StoreAddr);//存储90°信号到刻度表相应地址
    }
    else if(StoreCnt==2||StoreCnt==2+Ne)//180°激励采集中断？
	{
		CalSignal(Acq180Num);     //计算信号
		if(StoreCnt==2)		//第一个180°激励采集中断？
		{
			SavePulse(PulseF180StoreAddr);//存储第一个180°信号到刻度表相应地址
		}
		else
		{
			SavePulse(PulseL180StoreAddr);//存储最后一个180°信号到刻度表相应地址
		}
	}
	else if(StoreCnt<=Ne+3 && StoreCnt>2)//回波采集中断？
    {
		if (StoreCnt==4)
		{
			DUMP_SUSTAIN_DIS= USER_DISABLE;
			DumpSustainFlag	= CLEAR;
		}
		CalSignal(EchoAcqNum);    // 计算信号
		if (StoreCnt==Ne+3)
		{
			SaveEcho(EchoStorAddr+2*StoreCnt-8);//存储最后一个回波信号到刻度表相应地址
		}
		else//前ne-1个回波采集中断？
		{
			SaveEcho(EchoStorAddr+2*StoreCnt-6);//存储前ne-1个回波信号到刻度表相应地址
		}
		      
	}
	IER|=M_INT1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;//清除PIE分组1的中断应答位
	EINT;
	return;
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 

