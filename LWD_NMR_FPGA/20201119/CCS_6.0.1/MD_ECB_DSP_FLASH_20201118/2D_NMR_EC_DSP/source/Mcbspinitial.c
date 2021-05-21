//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_McBSP.c
//
// TITLE:	DSP28 Deviec McBSP Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP281x_Device.h"

//---------------------------------------------------------------------------
// InitMcbsp: 
//---------------------------------------------------------------------------
// This function initializes the McBSP to a known state.
//
void InitMcbsp(void)
{
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x3F00;    //  0011 1111 0000 0000 ,设置使能MCBSP引脚同时其他未设置的引脚默认为IO.
	EDIS;

//	开启MCBSP接受与发送中断
	PieCtrlRegs.PIEIER6.bit.INTx5 = 1;  
	PieCtrlRegs.PIEIER6.bit.INTx6 = 0;
	
// 对MCBSP串口相应寄存器做相应的配置	
	McbspaRegs.SPCR1.bit.RRST = 0;     // 串口接收复位
	McbspaRegs.SPCR2.bit.XRST = 0;     //串口发送复位
	McbspaRegs.SPCR2.bit.GRST = 0;     // 采样率发生器复位
	McbspaRegs.SPCR2.bit.FRST = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");

	
	McbspaRegs.SPCR1.all = 0;    //串口控制寄存器SPCR1设置
	McbspaRegs.XCR1.all = 0x40;  //0-0000000(每祯字数)-010(每字位数)-00000 共16位,串口发送祯长度(单位:字) 每祯1字,每字16位
	McbspaRegs.XCR2.all = 0x05;  //0(发送相位1)-0000000(发送祯2长度)-000(发送字2长度)-00(发送压缩模式)-1(发送祯忽略第一祯同步后的祯同步)-01(发送数据延迟1位)
	McbspaRegs.RCR1.all = 0x40;  //0-0000000(接收祯每祯长度1字)-010(接收祯字长16位)-00000
	McbspaRegs.RCR2.all = 0x05;  //0(祯相位单祯结构)-0000000(祯2的长度)-000(接收祯字长度)-00(接受无压缩)-1(接收祯忽略第一祯同步后的祯)-01(接受数据一位延迟)
	McbspaRegs.PCR.all = 0x0A00; //发送祯由内部产生,接收祯由外部产生,发送与接收祯同步高有效,发送时钟上升沿有效,接收时钟下降沿有效.
	
	McbspaRegs.SPCR2.bit.GRST = 1;  //采样率发生器放开复位,使能采样率发生器
	
	McbspaRegs.SPCR1.bit.RINTM=0;  //中断由RRDY产生
	McbspaRegs.SPCR2.bit.XINTM=0;  //中断由XRDY产生	
	McbspaRegs.SRGR1.all = 0xff04;  //祯正脉冲宽度,当FSGM=0时候失效,发送时钟1M(针对25M内部时钟输入)
	McbspaRegs.SRGR2.all = 0xa000;  // 当DXR到XSR后,产生发送祯同步,FSGM位此时为0则FPR与FWID失效.
	McbspaRegs.MFFINT.bit.RINT = 1;  //非FIFO模式下使能接受中断
	
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	
	McbspaRegs.SPCR1.bit.RRST = 1;  //接收串口使能
	McbspaRegs.SPCR2.bit.XRST = 1;  //发射串口使能
    McbspaRegs.SPCR2.bit.FRST = 1; //使能内部采样率发生器发送祯同步功能
	asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
	return;
}

unsigned int Mcbsp_TxRdy(void)
{
	if(McbspaRegs.SPCR2.bit.XRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

	
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  

