/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// SCIA_interrupt.c
Uint16 SciaDataEven;
Uint16 BufferSciaDataH;
Uint16 BufferSciaDataL;
Uint16 BufferSciaDataAll;
Uint16 SciaRecFlag = 0;

unsigned int SciaTx_Ready(void)   //准备发送数据时为1，否则为0
{
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void SciaSendData(Uint16 data)
{
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA设置为发送状态
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = data;              // 发送数据
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA设置为接收状态
}

void SciaSendDataNWords(Uint32 StartAddr,Uint32 DataNum)
{
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA设置为发送状态
	SendTempPt = (Uint16 *)(StartAddr);
	for (SendCnt=0; SendCnt<DataNum; SendCnt++)
	{
		while (SciaTx_Ready() == 0) {}
		SciaRegs.SCITXBUF = *SendTempPt++;
	}
	while (SciaTx_Ready() == 0) {}
	SciaRegs.SCITXBUF = 0xAA55;
	GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA设置为接收状态
}

/****************************************************************************
*
*名    称：SciaRx_Ready()
*准备接收数据时为1，否则为0*/
unsigned int SciaRx_Ready(void)   
{
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}


interrupt void SCIRXINTA_ISR(void)     // SCI-A接收中断函数
{
	//BufferSciaDate=SciaRegs.SCIRXBUF.all;	//读8位数据
	if(SciaDataEven == 0)
	{
		SciaDataEven = 1;
		BufferSciaDataH = SciaRegs.SCIRXBUF.bit.RXDT;
		SciaRecFlag = 0;
	}
	else
	{
		SciaDataEven = 0;
		BufferSciaDataL = SciaRegs.SCIRXBUF.bit.RXDT;
		BufferSciaDataAll = (BufferSciaDataH<<8)|BufferSciaDataL;   //读取主控板发送过来的16位数据
		SciaRecFlag = 1;    							//接收到16位数的标志
	}

	// 接收到16位数据
	if (SciaRecFlag)
	{
		if(BufferSciaDataAll==0x1328||DownTableFlag==1)              //下载表数据命令
		{
			DownloadTable(BufferSciaDataAll);
		}
		else if(BufferSciaDataAll==0x1428)     //上传表数据命令
		{
			SendTableFlag = SET;
		}
		else if(BufferSciaDataAll==0x0328)         //工作模式
		{
//			while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9910;     //回复

			SciaSendData(0x9910);           //回复   ？？？

	   		WorkMode = *(Uint16 *)0x8001;           //读取工作观测模式选择寄存器
			CheckWorkMode();
			switch(WorkMode)
			{
				case 0x0001: SingleModeFlag	= SET;break;
				case 0x0002: PPModeFlag		= SET;break;
				case 0x0003: PPDIFModeFlag	= SET;break;
				case 0x0004: PPT1ModeFlag	= SET;break;
				case 0x0005: PPOFTWModeFlag	= SET;break;
				case 0x0006: PPShortModeFlag= SET;break;
				//case 0x0007: 	= SET;break;
				case 0x0008: ScanModeFlag	= SET;break;
				case 0x0009: ScaleModeFlag	= SET;break;
				case 0x000A: HoleModeFlag	= SET;break;
				case 0x000B: PulseAcqFlag	= SET;break;
				default: break;
			}
		}
		else if(BufferSciaDataAll==0x5028)              //储能短节连接
		{
			K1_EN = USER_ENABLE;     //K1闭合（输出高）
			K2_EN = USER_ENABLE;     //K2闭合
			HVState = HV_ON;  //表明开通状态

			SciaSendData(0x9922);

//			while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9922;     //回复
		}
		else if(BufferSciaDataAll==0x9923)              //储能短节断开
		{
		    K1_DIS = USER_DISABLE;
		    K2_DIS = USER_DISABLE;
		    HVState = HV_OFF;

		    SciaSendData(0x9923);

//	        while(McbspaRegs.SPCR2.bit.XRDY==0)
//			{ ; }
//			McbspaRegs.DXR1.all=0x9923;     //回复
		}
		else if(BufferSciaDataAll==0x9924)              //储能短节判断
		{
			GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    // SCIA设置为发送状态
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0x9924;              // 发送数据
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = HVState;              // 发送数据
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0xAA55;              // 发送数据
			GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    // SCIA设置为接收状态
		}
		else if(BufferSciaDataAll==0x9901)              //系统自检测
		{
			TIMER_DATA = 1;   //1个计数为
			TIMER_START = 0x1;
			Delay(60);

			if(GpioDataRegs.GPADAT.bit.GPIOA9==1)
			{
//				while(McbspaRegs.SPCR2.bit.XRDY==0)
//				{ ; }
//				McbspaRegs.DXR1.all=0x0;
				SciaSendData(0);
			}
			else
			{
//				while(McbspaRegs.SPCR2.bit.XRDY==0)
//				{ ; }
//				McbspaRegs.DXR1.all=0x0020;
				SciaSendData(0x0020);
			}
			TIMER_STOP = 0x2;
		}
	}

    SciaRegs.SCIFFRX.bit.RXFIFORESET=0;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

//	GpioDataRegs.GPFDAT.bit.GPIOF11=1;
	EINT;
//		SciaRegs.SCICTL1.bit.SLEEP = 1;			//更改完成，结束 485 总线上 地址
	return;
}

