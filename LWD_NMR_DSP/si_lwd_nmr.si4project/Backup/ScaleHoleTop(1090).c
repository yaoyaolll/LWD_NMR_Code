/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop,"Datatable");


//刻度主函数
void ScaleHoleModeTop(void)
{
	// 20201016屏蔽此处代码
	/*if(ScaleModeFlag==SET)//主刻度
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}*/
	// 主刻度时TE默认为10，孔隙度刻度时默认为6
	// 主刻度时NE默认为60，孔隙度刻度时默认为150
	Tes	= (Uint32)100 * Calib_TE * FPGA_COUNT;
	Tel	= Tes;  //将TE转换为10ns单位即FPGA计数值
	Ne	= Calib_NE;
	ScaleMn	= 1;
	ScaleM	= 0;

	ToMSNoiseAddr	= SCALETABLE_START + 4;
	ToMSSignalAddr	= SCALETABLE_START + 7;
	EchoStorAddr		= SCALETABLE_START+20;
	Pulse90StoreAddr	= SCALETABLE_START+2*Ne+20;
	PulseF180StoreAddr	= SCALETABLE_START+2*Ne+21;
	PulseL180StoreAddr	= SCALETABLE_START+2*Ne+22;

	
	RELAY_ON_CLOSE	= RelayAry[1];   //频带1继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE	= 0x0000;

	StartS1msModule(25000);
	MiniScan(CenterFreq, ToMSNoiseAddr, ToMSSignalAddr);//mini扫频

	FreqAry[1] = CenterFreq;
	DCWorkOnce(1); //刻度

	RELAY_ON_CLOSE = RelayAry[1]<<8;   //频带1继电器断开
	Delay(120);            
	RELAY_ON_CLOSE = 0x0000;


	//存储
	if(ScaleModeFlag==SET)   //主刻度模式
	{    
		SaveNTempPt	= (int *)(SCALETABLE_START);
		*SaveNTempPt++ = 0x9995;    		// 参数头
		*SaveNTempPt++ = 0x0009;   			// 工作模式
		*SaveNTempPt++ = 2*Ne+23;			// 长度
		*SaveNTempPt = CenterFreq * 10; 	// 中心频率

		SaveNTempPt = (int *)(SCALETABLE_START + 16);
		*SaveNTempPt++ = 0;          		// Q值
		*SaveNTempPt++ = 0x294;				// 参考幅值
		*SaveNTempPt++ = Width90Pulse;      // 90度脉冲宽度
		SavePhaseWord();

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(SCALETABLE_START);
		int i=0;
		for (;i<2*Ne+23;++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		SciaSendDataNWords(SCALETABLE_START, 2*Ne+24);    //上传刻度结果
	}     
	else    // 孔隙度刻度与校验模式
	{
		SaveNTempPt	= (int *)(HOLETABLE_START);
		*SaveNTempPt++ = 0x9995;    		// 参数头
		*SaveNTempPt++ = 0x000A;   			// 工作模式
		*SaveNTempPt++ = 2*Ne+23;			// 长度
		*SaveNTempPt = CenterFreq * 10; 	// 中心频率

		SaveNTempPt = (int *)(HOLETABLE_START + 16);
		*SaveNTempPt++ = 0;          		// Q值
		*SaveNTempPt++ = 0x294;				// 参考幅值
		*SaveNTempPt++ = Width90Pulse;      // 90度脉冲宽度
		SavePhaseWord();       // 存储相位

		Uint16 CheckSum = 0;
		SaveNTempPt = (int *)(HOLETABLE_START);
		int i=0;
		for (;i<2*Ne+23;++i)
		{
			CheckSum += *SaveNTempPt;
			SaveNTempPt++;
		}
		*SaveNTempPt = CheckSum;

		SciaSendDataNWords(HOLETABLE_START, 2*Ne+24);    //上传刻度结果
	}             
	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  



