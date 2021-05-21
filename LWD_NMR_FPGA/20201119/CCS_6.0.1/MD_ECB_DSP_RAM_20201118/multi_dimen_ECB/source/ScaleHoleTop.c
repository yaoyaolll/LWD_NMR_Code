/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(ScaleHoleModeTop,"Datatable");

//刻度主函数
void ScaleHoleModeTop(void)
{          
	if(ScaleModeFlag==SET)//主刻度
	{
		ScaleTe	= 10;
		ScaleNe	= 60;
	}     
	Tes	= (Uint32)100 * ScaleTe * FPGA_COUNT;
	Tel	= Tes;  //将TE转换为10ns单位即FPGA计数值
	Ne	= ScaleNe;
	ScaleMn	= 1;
	ScaleM	= 0;   
	for (ZeroOne=0;ZeroOne<2;ZeroOne++)
	{	
		for (ScaleCnt=1;ScaleCnt<9;ScaleCnt+=2)
		{     
			BandCnt	= ScaleCnt + ZeroOne;
			if(BandCnt==2)//延时
			{
				StartS1msModule(25000);
			}
			else
			{
				StartS1msModule(1000);
			}
			
			RELAY_ON_CLOSE	= RelayAry[BandCnt];   //频带1继电器闭合
			Delay(120);                       
			RELAY_ON_CLOSE	= 0x0000;
	
			ToMSFreq		= FreqAry[BandCnt];
			if(ScaleModeFlag==SET)//主刻度
			{
				ToMSNoiseAddr	= SCALETABLE_START+16*Ne+3*BandCnt+73;
				ToMSSignalAddr	= SCALETABLE_START+16*Ne+9*BandCnt-6;
			}
			else//孔隙度刻度
			{
				ToMSNoiseAddr	= HOLETABLE_START+16*Ne+3*BandCnt+80;
				ToMSSignalAddr	= HOLETABLE_START+16*Ne+9*BandCnt+1;
			}		                                                                              
			MiniScan(ToMSFreq,ToMSNoiseAddr,ToMSSignalAddr);//mini扫频

			if(ScaleModeFlag==SET)//主刻度
			{
				Pulse90StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+99;
				PulseF180StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+107;
				PulseL180StoreAddr	= SCALETABLE_START+16*Ne+BandCnt+115;
				EchoStorAddr		= SCALETABLE_START+2*Ne*(BandCnt-1)+3;
			}
			else
			{
				Pulse90StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+106;
				PulseF180StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+114;
				PulseL180StoreAddr	= HOLETABLE_START+16*Ne+BandCnt+122;
				EchoStorAddr		= HOLETABLE_START+2*Ne*(BandCnt-1)+10;
			}
			DCWorkOnce(BandCnt); //刻度
      
			RELAY_ON_CLOSE = RelayAry[BandCnt]<<8;   //频带1继电器断开
			Delay(120);            
			RELAY_ON_CLOSE = 0x0000;
		} 
	}                  
//存储
	if(ScaleModeFlag==SET)   //刻度
	{    
		SaveNTempPt	= (int *)(SCALETABLE_START);
		*SaveNTempPt= 0x990A;
		SaveNTempPt++;
		*SaveNTempPt= NintyWidthAry[1]; //储存F1工作频率下的90度脉冲宽度
		SaveNTempPt++;
		if(PhaseFlag==POSITIVE)
		{
			*SaveNTempPt	= 0x0; 
		}
		else
		{
			*SaveNTempPt	= 0x1111; 
		}
		SaveNTempPt	= (int *)(SCALETABLE_START+16*Ne+75);
		*SaveNTempPt= 0x294;//储存参考刻度信号幅值
		McbspSendData(SCALETABLE_START,16*Ne+124);//上传刻度结果
	}     
	else//孔隙度
	{
		SaveNTempPt	= (int *)(HOLETABLE_START);
		*SaveNTempPt= 0x990B;
		SaveNTempPt++;
		for(SaveCnt=1;SaveCnt<9;SaveCnt++)//分别存储F1~F8工作频率下90度脉冲宽度
		{
			*SaveNTempPt= NintyWidthAry[SaveCnt];
			SaveNTempPt++;		
		}   
		if(PhaseFlag==SET)
		{
			*SaveNTempPt	= 0x0; 
		}
		else
		{
			*SaveNTempPt	= 0x1111; 
		}
		SaveNTempPt	= (int *)(HOLETABLE_START+16*Ne+82);
		*SaveNTempPt = 0x294;//储存参考刻度信号幅值
	    McbspSendData(HOLETABLE_START,16*Ne+131);//上传刻度结果
	}             
	ChangePhase();
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  



