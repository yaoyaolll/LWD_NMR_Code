/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(DeCpmgTop,"Datatable");

void DeCpmgTop(void)       //单TE单TW主函数
{      
	Ne			= DCNe;
	ScaleM		= DCm;
	ScaleMn		= DCMn;
	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;      

	MiniScan(FreqAry[DCFreqSel],DECPMGTABLE_START+2*Ne+15,DECPMGTABLE_START+2*Ne+5);

	Tes	= (Uint32)100 * DCTes * FPGA_COUNT;        //短TE值
	Tel	= Tes;//将SINGLE_TE转换为10ns单位即FPGA计数值
	Pulse90StoreAddr	= DECPMGTABLE_START+2*Ne+18;//计算90°脉冲的幅值地址pluse90addr
	PulseF180StoreAddr	= DECPMGTABLE_START+2*Ne+19;//计算首个180°脉冲的幅值地址pluse180addr1
	PulseL180StoreAddr	= DECPMGTABLE_START+2*Ne+20;//计算末个180°脉冲的幅值地址pluse180addr2
	EchoStorAddr		= DECPMGTABLE_START+5;//计算回波数据的首地址echostraddr
	InverseTurnFlag	= SET;	
	DCWorkOnce(DCFreqSel);//工作一次

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //继电器断开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
		
	StartS1msModule(1000);//延时
//存储 
	SaveNTempPt	= (int *)(DECPMGTABLE_START);//数据存储指针指向单TETW表首地址
	*SaveNTempPt= 0x9901;
	SaveNTempPt++;
	*SaveNTempPt= DCTes;//存储单TETW表的TE值
	SaveNTempPt++;
	*SaveNTempPt= Ne;//存储单TETW表的NE值
	SaveNTempPt++;
	*SaveNTempPt= DCFreqSel;//存储单TETW的频率选择码DCFreqSel
	SaveNTempPt++;
	SavePhaseWord();//存储发射脉冲相位
	SaveNTempPt = (int *)(DECPMGTABLE_START+14+2*Ne);//存储参考刻度信号幅值
	*SaveNTempPt= 0x294;
		//上传数据
	McbspSendData(DECPMGTABLE_START,2*Ne+21);		  	     
	ChangePhase();//取反发射脉冲相位
	return;       
}

interrupt void XINT2_DCStorData(void)
{
    StoreCnt++;    //中断计数StoreCnt加1
    if(StoreCnt==1)//90°激励采集中断？
	{
		CalSignal(Acq90Num);//计算信号
		SavePulse(Pulse90StoreAddr);//存储90°信号到刻度表相应地址
    }
    else if(StoreCnt==2||StoreCnt==2+Ne)//180°激励采集中断？
	{
		CalSignal(Acq180Num);     //计算信号
		if(StoreCnt==2)//第一个180°激励采集中断？
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

