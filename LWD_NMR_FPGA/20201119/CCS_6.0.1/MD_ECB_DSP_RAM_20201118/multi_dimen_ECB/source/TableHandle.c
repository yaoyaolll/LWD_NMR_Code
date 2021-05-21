//###########################################################################
//
// FILE:   TableHandle.c
//
// TITLE:  .
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H. | Changes since previous version (v.58 Alpha)
//      |             |      | Additional comments added to explain the PLL
//      |             |      |    initialization.
//      |             |      | Changed the PLL initialization to take into
//      |             |      |    account bit definitions for the PLLCR register
//      |             |      | Removed DFT initialization - no longer needed 
//      |             |      |    as of Rev C F2810/12 silicon
//      |             |      | Split some operations into their own function
//      |             |      |    for better modularity
//      |             |      | Added pipeline flush after the Flash Init
//###########################################################################
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(CheckReadTable,"Datatable");
#pragma CODE_SECTION(ChangeTable995,"Datatable");
#pragma CODE_SECTION(ChangeTable996,"Datatable");
#pragma CODE_SECTION(ChangeTable999,"Datatable");
#pragma CODE_SECTION(ChangeTable99A,"Datatable");
#pragma CODE_SECTION(CheckWorkMode,"Datatable");

void SendTable(void)
{
	TableTempPt = (Uint16 *)0x8000; 
	*TableTempPt= 0x9921;
	for(SendCnt=0;SendCnt<TABLE_TOTAL_NUM+1;SendCnt++)      
	{
		while(McbspaRegs.SPCR2.bit.XRDY==0)              //如果不能发送，等待
		{ ; }
		McbspaRegs.DXR1.all=*TableTempPt;     //发送表数据
		TableTempPt++;
		//Delay(2);                        //指针指向下一个数据
	}
	while(McbspaRegs.SPCR2.bit.XRDY==0)         //如果不能发送，等待
	{;}
	McbspaRegs.DXR1.all=0xAA55;     //发送数据尾
	return;
}

void ChangeTable995(Uint16 ChangeBuffer)
{
	if(ChgTable995Flag==CLEAR)
	{
		CaseBuffer		= ChangeBuffer&0x00FF;
		ChgTable995Flag = SET;
        switch(CaseBuffer)
		{
			case 0x0050: ChgTablePt = (Uint16 *)(TABLE_START+2);TableChgCnt=1;break;
			case 0x0051: ChgTablePt = (Uint16 *)(TABLE_START+3);TableChgCnt=1;break;
			case 0x0052: ChgTablePt = (Uint16 *)(TABLE_START+4);TableChgCnt=1;break;
			case 0x0053: ChgTablePt = (Uint16 *)(TABLE_START+5);TableChgCnt=1;break;
			case 0x0054: ChgTablePt = (Uint16 *)(TABLE_START+6);TableChgCnt=1;break;
			case 0x0055: ChgTablePt = (Uint16 *)(TABLE_START+7);TableChgCnt=1;break;
			case 0x0056: ChgTablePt = (Uint16 *)(TABLE_START+8);TableChgCnt=1;break;
			case 0x0057: ChgTablePt = (Uint16 *)(TABLE_START+9);TableChgCnt=1;break;
			case 0x005A:
				ChgTablePt = (Uint16 *)(TABLE_START+10);
				TableChgCnt=2;
				break;
			default: TableChgCnt=0;break;
		}
	}
	else if((ChgTable995Flag==SET)&&(TableChgCnt!=0))
	{
		*ChgTablePt = ChangeBuffer;
		TableChgCnt--;
		if(TableChgCnt==0)
		{
			ChgTable995Flag = CLEAR;
		}
		else
		{
			ChgTablePt++;
		}
	}
	return;
}

void ChangeTable996(Uint16 ChangeBuffer)
{
	if(ChgTable996Flag==CLEAR)
	{
		CaseBuffer = ChangeBuffer&0x00FF;
		ChgTable996Flag = SET;
        switch(CaseBuffer)
        {
			case 0x0060: ChgTablePt = (Uint16 *)(TABLE_START+12);TableChgCnt=1;break;
			case 0x0061: ChgTablePt = (Uint16 *)(TABLE_START+13);TableChgCnt=1;break;
			case 0x0062: ChgTablePt = (Uint16 *)(TABLE_START+14);TableChgCnt=1;break;
			case 0x0063: ChgTablePt = (Uint16 *)(TABLE_START+15);TableChgCnt=1;break;
			case 0x0064: ChgTablePt = (Uint16 *)(TABLE_START+16);TableChgCnt=1;break;
			case 0x0065: ChgTablePt = (Uint16 *)(TABLE_START+17);TableChgCnt=1;break;
			case 0x0066: ChgTablePt = (Uint16 *)(TABLE_START+18);TableChgCnt=1;break;
			case 0x0067: ChgTablePt = (Uint16 *)(TABLE_START+19);TableChgCnt=1;break;
			case 0x0068: ChgTablePt = (Uint16 *)(TABLE_START+20);TableChgCnt=1;break;
			default: TableChgCnt=0;break;
		}
	}
	else if((ChgTable996Flag==SET)&&(TableChgCnt!=0))
	{
		*ChgTablePt = ChangeBuffer;
		ChgTable996Flag = CLEAR;
	}
	return;
}

void ChangeTable999(Uint16 ChangeBuffer)
{
	if(ChgTable999Flag==CLEAR)
	{
		CaseBuffer = ChangeBuffer&0x00FF;
		ChgTable999Flag = SET;
        switch(CaseBuffer)
        {
			case 0x0094: ChgTablePt = (Uint16 *)(TABLE_START+21);TableChgCnt=1;break;
			case 0x0095:
				ChgTablePt = (Uint16 *)(TABLE_START+1);
				TableChgCnt=1;
				break;
			case 0x0096: ChgTablePt = (Uint16 *)(TABLE_START+22);TableChgCnt=1;break;
			case 0x0097: ChgTablePt = (Uint16 *)(TABLE_START+23);TableChgCnt=1;break;
			case 0x0098: ChgTablePt = (Uint16 *)(TABLE_START+24);TableChgCnt=1;break;
			case 0x0099: ChgTablePt = (Uint16 *)(TABLE_START+25);TableChgCnt=1;break;
			case 0x009A: ChgTablePt = (Uint16 *)(TABLE_START+26);TableChgCnt=1;break;
			case 0x009B: ChgTablePt = (Uint16 *)(TABLE_START+27);TableChgCnt=1;break;
			case 0x009C: ChgTablePt = (Uint16 *)(TABLE_START+28);TableChgCnt=1;break;
			case 0x009D: ChgTablePt = (Uint16 *)(TABLE_START+29);TableChgCnt=1;break;
			case 0x009E: ChgTablePt = (Uint16 *)(TABLE_START+30);TableChgCnt=1;break;
			case 0x009F: ChgTablePt = (Uint16 *)(TABLE_START+31);TableChgCnt=1;break;
			default: TableChgCnt=0;break;
		}
	}
	else if((ChgTable999Flag==SET)&&(TableChgCnt!=0))
	{
		*ChgTablePt = ChangeBuffer;
		ChgTable999Flag = CLEAR;
	}
	return;
}

void ChangeTable99A(Uint16 ChangeBuffer)
{
	if(ChgTable99AFlag==CLEAR)
	{
		CaseBuffer = ChangeBuffer&0x00FF;
		ChgTable99AFlag = SET;
        switch(CaseBuffer)
        {
			case 0x00A1: ChgTablePt = (Uint16 *)(TABLE_START+32);TableChgCnt=1;break;
			default: TableChgCnt=0;break;
		}
	}
	else if((ChgTable99AFlag==SET)&&(TableChgCnt!=0))
	{
		*ChgTablePt = ChangeBuffer;
		ChgTable99AFlag = CLEAR;
	}
	return;
}

void CheckWorkMode(void)
{
	Uint16 WorkModecnt=0;
	Uint16 ModeFindFlag=CLEAR;
	WorkMode	= *(Uint16 *)0x8001;

	while(ModeFindFlag==CLEAR &&(WorkModecnt!=MODE_CHOICE))
	{
		if(WorkMode==WorkModeChoice[WorkModecnt])
		{
			ModeFindFlag=SET;

		}
		WorkModecnt++;

	}

	if (ModeFindFlag	== CLEAR)
	{
		*(Uint16 *)0x8001	= 0x0009;//默认扫频模式
		WorkMode			= 0x0009;

	}
	return;
}

void CheckReadTable(void)
{
//common parameters     
	CheckWorkMode();
	CheckTablePt = (Uint16 *)0x8002;						//CheckTablePt = (Uint16 *)0x8002;   //????F1????
	FreqAry[1] = *CheckTablePt;
	if(FreqAry[1]<300||FreqAry[1]>1200)
	{
		*CheckTablePt	= 585;
		FreqAry[1]		= 585;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8003;   //????F2????
	FreqAry[2] = *CheckTablePt;
	if(FreqAry[2]<300||FreqAry[2]>1200)
	{
		*CheckTablePt	= 625;
		FreqAry[2]		= 625;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8004;   //????F3????
	FreqAry[3] = *CheckTablePt;
	if(FreqAry[3]<300||FreqAry[3]>1200)
	{
		*CheckTablePt	= 666;
		FreqAry[3]		= 666;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8005;   //????F4????
	FreqAry[4] = *CheckTablePt;
	if(FreqAry[4]<300||FreqAry[4]>1200)
	{
		*CheckTablePt	= 726;
		FreqAry[4]		= 726;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8006;   //????F4????
	FreqAry[5] = *CheckTablePt;
	if(FreqAry[5]<300||FreqAry[5]>1200)
	{
		*CheckTablePt	= 775;
		FreqAry[5]		= 775;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8007;   //????F4????
	FreqAry[6] = *CheckTablePt;
	if(FreqAry[6]<300||FreqAry[6]>1200)
	{
		*CheckTablePt	= 820;
		FreqAry[6]		= 820;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8008;
	FreqAry[7] = *CheckTablePt;
	if(FreqAry[7]<300||FreqAry[7]>1200)
	{
		*CheckTablePt	= 865;
		FreqAry[6]		= 865;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8009;
	FreqAry[8] = *CheckTablePt;
	if(FreqAry[8]<300||FreqAry[8]>1200)
	{
		*CheckTablePt	= 963;
		FreqAry[8]		= 963;
	}
	CheckTablePt += 3;						//CheckTablePt = (Uint16 *)0x800C;   //????F4????
	NintyWidthAry[1] = *CheckTablePt;
	if(NintyWidthAry[1]<10||NintyWidthAry[1]>100)
	{
		*CheckTablePt	= 54;
		NintyWidthAry[1]= 54;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x800D;   //????F4????
	NintyWidthAry[2] = *CheckTablePt;
	if(NintyWidthAry[2]<10||NintyWidthAry[2]>100)
	{
		*CheckTablePt	= 52;
		NintyWidthAry[2]= 52;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x800E;   //????F4????
	NintyWidthAry[3] = *CheckTablePt;
	if(NintyWidthAry[3]<10||NintyWidthAry[3]>100)
	{
		*CheckTablePt	= 49;
		NintyWidthAry[3]= 49;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x800F;   //????F4????
	NintyWidthAry[4] = *CheckTablePt;
	if(NintyWidthAry[4]<10||NintyWidthAry[4]>100)
	{
		*CheckTablePt	= 46;
		NintyWidthAry[4]= 46;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8010;   //????F4????
	NintyWidthAry[5] = *CheckTablePt;
	if(NintyWidthAry[5]<10||NintyWidthAry[5]>100)
	{
		*CheckTablePt	= 43;
		NintyWidthAry[5]= 43;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8011;   //????F4????
	NintyWidthAry[6] = *CheckTablePt;
	if(NintyWidthAry[6]<10||NintyWidthAry[6]>100)
	{
		*CheckTablePt	= 40;
		NintyWidthAry[6]= 40;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8012;   //????F4????
	NintyWidthAry[7] = *CheckTablePt;
	if(NintyWidthAry[7]<10||NintyWidthAry[7]>100)
	{
		*CheckTablePt	= 37;
		NintyWidthAry[7]= 37;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8013;
	NintyWidthAry[8] = *CheckTablePt;
	if(NintyWidthAry[8]<10||NintyWidthAry[8]>100)
	{
		*CheckTablePt	= 34;
		NintyWidthAry[8]= 34;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8014;
	HegtWidth		= *CheckTablePt;       //??????????
	if(HegtWidth<90||HegtWidth>270)
	{
		*CheckTablePt	= 135;
		HegtWidth		= 135;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8015;   //????F4????
	StepFreq	= *CheckTablePt;         //??????
	if(StepFreq<1||StepFreq>50)
	{
		*CheckTablePt	= 5;
		StepFreq		= 5;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8016;   //????F4????
	SiglAcqPrdNum	= *CheckTablePt;     //??????????
	if(SiglAcqPrdNum<5||SiglAcqPrdNum>100)
	{
		*CheckTablePt	= 16;
		SiglAcqPrdNum	= 16;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8017;   //????F4????
	SiglAcqFreqTim	= *CheckTablePt;    //?????????
	if(SiglAcqFreqTim<5||SiglAcqFreqTim>8)
	{
		*CheckTablePt	= 8;
		SiglAcqFreqTim	= 8;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8018;   //????F4????
	NoiseAcqTim	= *CheckTablePt;     //????????
	if(NoiseAcqTim<10||NoiseAcqTim>120)
	{
		*CheckTablePt	= 60;
		NoiseAcqTim		= 60;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8019;   //????F4????
	NoiseAcqFreq	= *CheckTablePt;     //???????
	if(NoiseAcqFreq<20||NoiseAcqFreq>100)
	{
		*CheckTablePt	= 50;
		NoiseAcqFreq	= 50;
	}
     //开辟的噪声数组有限
	if(NoiseAcqTim*NoiseAcqFreq>5000)
	{
		*(Uint16 *)0x8018	= 60;
		*(Uint16 *)0x8019	= 50;
		NoiseAcqTim	= 60;     //读取噪声采集时间
		NoiseAcqFreq= 50;     //读取噪声采样率
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801A;
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801B;   //????F4????
	SftWinWidth	= *CheckTablePt;
	if(SftWinWidth<1||SftWinWidth>100)
	{
		*CheckTablePt	= 23;
		SftWinWidth		= 23;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801C;   //????F4????
	MatTime	= *CheckTablePt;      //????????????????
	if(MatTime<10||MatTime>200)
	{
		*CheckTablePt	= 100;
		MatTime			= 100;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801D;   //????F4????
	MatAcqFreqTim	= *CheckTablePt;  //??????????????
	if(MatAcqFreqTim<20||MatAcqFreqTim>80)
	{
		*CheckTablePt	= 80;
		MatAcqFreqTim	= 80;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801E;   //????F4????
	MatFreqSel	= *CheckTablePt;      //?????????????
	if(MatFreqSel<1||MatFreqSel>8)
	{
		*CheckTablePt	= 7;
		MatFreqSel		= 7;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x801F;   //????F4????
	ScaleTe	= *CheckTablePt;          //?????TE
	if(ScaleTe<4||ScaleTe>200)
	{
		*CheckTablePt	= 6;
		ScaleTe			= 6;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8020;   //????F4????
	ScaleNe	= *CheckTablePt;          //?????NE
	if(ScaleNe<1||ScaleNe>3000)
	{
		*CheckTablePt	= 150;
		ScaleNe			= 150;
	}
//1D parameters
/*	if(WorkMode==0x0001||WorkMode==0x0003||WorkMode==0x0004||WorkMode==0x0007)
	{
*/
//频率选择没有保护
	if (WorkMode==0x0001)//STESTW
	{
			DCFreqSel	= *(Uint16 *)0x800A;
			if (DCFreqSel<1||DCFreqSel>8)
			{
				DCFreqSel	= 7;
				*(Uint16 *)0x800A	= 7;
			}
			*(Uint16 *)0x800B	= 0;

		//STESTW
		CheckTablePt = (Uint16 *)0x8021;
		DCTes	= *CheckTablePt;          //??TE
		if(DCTes<4||DCTes>200)
		{
			*CheckTablePt	= 6;
			DCTes			= 6;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		DCNe	= *CheckTablePt;          //??NE
		if(DCNe<10||DCNe>3000)
		{
			*CheckTablePt	= 800;
			DCNe			= 800;
		}
		DCMn		= 1;                  //读取MN
		DCm			= 0;
	}

	else if (WorkMode==0x0002)//3 freqencies PP parameters
	{
		PP3FreqSel	= *(Uint16 *)0x800A;         //读取频率选择码
		PP3FreqSelAry[1]	= (PP3FreqSel&0x0F00)>>8;
		PP3FreqSelAry[2]	= (PP3FreqSel&0x00F0)>>4;
		PP3FreqSelAry[3]	= (PP3FreqSel&0x000F);
		if (PP3FreqSel>0x0FFF||PP3FreqSelAry[1]<1||PP3FreqSelAry[1]>8||PP3FreqSelAry[2]<1||PP3FreqSelAry[2]>8||PP3FreqSelAry[3]<1||PP3FreqSelAry[3]>8)
		{
			PP3FreqSel	= 0x0825;
			*(Uint16 *)0x800A	= 0x0825;
			PP3FreqSelAry[1]	= 8;
			PP3FreqSelAry[2]	= 2;
			PP3FreqSelAry[3]	= 5;
		}
		*(Uint16 *)0x800B	= 0x0000;

		//3 freqencies PP parameters
		CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //3频PP模式下的TE
		PP3FTe1A23DE	= (ReadTableBuf&0xFF00)>>8;
		PP3FTe1C		= (ReadTableBuf&0x00FF);
		if(PP3FTe1A23DE<4||PP3FTe1A23DE>200||PP3FTe1C<4||PP3FTe1C>200)
		{
			*CheckTablePt	= 0x0C06;
			PP3FTe1A23DE	= 0x000C;
			PP3FTe1C		= 0x0006;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		PP3FNe23DE		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		PP3FNe1C		= ReadTableBuf&0x00FF;             //NE???
		if(PP3FNe23DE<1||PP3FNe23DE>250||PP3FNe1C<1||PP3FNe1C>250)
		{
			*CheckTablePt	= 0x1910;
			PP3FNe23DE	= 0x0019;
			PP3FNe1C	= 0x0010;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		PP3FNe1A	= *CheckTablePt;            //NE???
		if(PP3FNe1A<1||PP3FNe1A>3000)
		{
			*CheckTablePt	= 0x01A0;
			PP3FNe1A		= 0x01A0;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		PP3FTw1C	= *CheckTablePt;
		if(PP3FTw1C!=30&&PP3FTw1C!=20)
		{
			*CheckTablePt	= 0x001E;
			PP3FTw1C		= 0x001E;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8025;
		PP3FNRept1C		= *CheckTablePt;
		if(PP3FNRept1C<1||PP3FNRept1C>150)
		{
			*CheckTablePt	= 0x0024;
			PP3FNRept1C		= 0x0024;
		}
	}


	else if (WorkMode==0x0003)//6 freqencies PP parameters
	{
			PP6FreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
			PP6FreqSelAry[6]= (PP6FreqSelLow&0x000F);
			PP6FreqSelAry[5]= (PP6FreqSelLow&0x00F0)>>4;
			PP6FreqSelAry[4]= (PP6FreqSelLow&0x0F00)>>8;
			PP6FreqSelAry[3]= (PP6FreqSelLow&0xF000)>>12;
			PP6FreqSelHi	= *(Uint16 *)0x800B;
			PP6FreqSelAry[2]= (PP6FreqSelHi&0x000F);
			PP6FreqSelAry[1]= (PP6FreqSelHi&0x00F0)>>4;

			if (PP6FreqSelHi>0x00FF||PP6FreqSelAry[1]<1||PP6FreqSelAry[1]>8||PP6FreqSelAry[2]<1||PP6FreqSelAry[2]>8)
			{
				PP6FreqSelHi= 0x0082;
				*(Uint16 *)0x800B	= 0x0082;
				PP6FreqSelAry[2]= 2;
				PP6FreqSelAry[1]= 8;
			}
			if (PP6FreqSelAry[3]<1||PP6FreqSelAry[3]>8||PP6FreqSelAry[4]<1||PP6FreqSelAry[4]>8||PP6FreqSelAry[5]<1||PP6FreqSelAry[5]>8||PP6FreqSelAry[6]<1||PP6FreqSelAry[6]>8)
			{
				PP6FreqSelLow		= 0x5714;
				*(Uint16 *)0x800A	= 0x5714;
				PP6FreqSelAry[6]= 4;
				PP6FreqSelAry[5]= 1;
				PP6FreqSelAry[4]= 7;
				PP6FreqSelAry[3]= 5;
			}

		//6 freqencies PP parameters
		CheckTablePt = (Uint16 *)0x8021;					//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //6频PP模式下的TE
		PP6FTe14A2356DE	= (ReadTableBuf&0xFF00)>>8;      
		PP6FTe1346C		= (ReadTableBuf&0x00FF);  
		if(PP6FTe14A2356DE<4||PP6FTe14A2356DE>200||PP6FTe1346C<4||PP6FTe1346C>200)
		{
			*CheckTablePt	= 0x0604;
			PP6FTe14A2356DE	= 6;
			PP6FTe1346C		= 4;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		ReadTableBuf	= *CheckTablePt;						          
		PP6FNe1346C	= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		PP6FNe2356DE= ReadTableBuf&0x00FF;             //NE???
		if(PP6FNe1346C<1||PP6FNe1346C>250||PP6FNe2356DE<1||PP6FNe2356DE>250)
		{
			*CheckTablePt	= 0x1832;
			PP6FNe2356DE	= 0x0032;
			PP6FNe1346C		= 0x0018;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		PP6FNe14A	= *CheckTablePt;            //NE???
		if(PP6FNe14A<1||PP6FNe14A>3000)
		{
			*CheckTablePt	= 0x0341;
			PP6FNe14A		= 0x0341;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		PP6FTw1346C	= *CheckTablePt;
		if(PP6FTw1346C!=30&&PP6FTw1346C!=20)
		{
			*CheckTablePt	= 0x0014;
			PP6FTw1346C		= 0x0014;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8025;
		ReadTableBuf	= *CheckTablePt;
		PP6FNRept14C= (ReadTableBuf&0xFF00)>>8;
		PP6FNRept36C= ReadTableBuf&0x00FF;
		if(PP6FNRept14C<1||PP6FNRept14C>150||PP6FNRept36C<1||PP6FNRept36C>150)
		{
			*CheckTablePt	= 0x2420;
			PP6FNRept36C	= 0x0020;
			PP6FNRept14C	= 0x0024;
		}          
	}


	else if (WorkMode==0x0004)//3 freqencise oil parameters
	{
			Oil3FreqSel	= *(Uint16 *)0x800A;         //读取频率选择码
			Oil3FreqSelAry[1]	= (Oil3FreqSel&0x0F00)>>8;
			Oil3FreqSelAry[2]	= (Oil3FreqSel&0x00F0)>>4;
			Oil3FreqSelAry[3]	= (Oil3FreqSel&0x000F);
			if (Oil3FreqSel>0x0FFF||Oil3FreqSelAry[1]<1||Oil3FreqSelAry[1]>8||Oil3FreqSelAry[2]<1||Oil3FreqSelAry[2]>8||Oil3FreqSelAry[3]<1||Oil3FreqSelAry[3]>8)
			{
				Oil3FreqSel	= 0x0875;
				*(Uint16 *)0x800A	= 0x0875;
				Oil3FreqSelAry[1]	= 8;
				Oil3FreqSelAry[2]	= 7;
				Oil3FreqSelAry[3]	= 5;
			}
			*(Uint16 *)0x800B	= 0x0000;


		//3 freqencise oil parameters
		CheckTablePt = (Uint16 *)0x8021;					//CheckTablePt = (Uint16 *)0x8021;
		Oil3Te1C2C3CDEF	= *CheckTablePt;
		if(Oil3Te1C2C3CDEF<4||Oil3Te1C2C3CDEF>200)
		{
			*CheckTablePt	= 0x0004;
			Oil3Te1C2C3CDEF	= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;
		ReadTableBuf		= *CheckTablePt;         //读取  
		Oil3Ne123C		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		Oil3Ne3D		= ReadTableBuf&0x00FF;           //NE???
		if(Oil3Ne123C<1||Oil3Ne123C>250||Oil3Ne3D<1||Oil3Ne3D>250)
		{
			*CheckTablePt	= 0x1919;
			Oil3Ne123C		= 0x0019;
			Oil3Ne3D		= 0x0019;
		}
		CheckTablePt++;  					//CheckTablePt = (Uint16 *)0x8023;
		ReadTableBuf		= *CheckTablePt;         //读取
		Oil3Ne3E		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		Oil3Ne3F		= ReadTableBuf&0x00FF;           //NE???
		if(Oil3Ne3E<1||Oil3Ne3E>250||Oil3Ne3F<1||Oil3Ne3F>250)
		{
			*CheckTablePt	= 0x4B7D;
			Oil3Ne3E		= 0x004B;
			Oil3Ne3F		= 0x007D;
		}
		CheckTablePt++;   					//CheckTablePt = (Uint16 *)0x8024;
		ReadTableBuf		= *CheckTablePt;         //读取  
		Oil3Tw123C		= (ReadTableBuf&0xFF00)>>8;
		Oil3Tw3D		= ReadTableBuf&0x00FF; 
		if(Oil3Tw123C<10||Oil3Tw123C>200||Oil3Tw3D<10||Oil3Tw3D>200)
		{
			*CheckTablePt	= 0x1432;
			Oil3Tw123C		= 0x0014;
			Oil3Tw3D		= 0x0032;
		}
		CheckTablePt++;   					//CheckTablePt = (Uint16 *)0x8025;
		ReadTableBuf		= *CheckTablePt;         //读取  
		Oil3Tw3E		= (ReadTableBuf&0xFF00)>>8;
		Oil3Tw3F		= ReadTableBuf&0x00FF;        //??
		if(Oil3Tw3E<10||Oil3Tw3E>255||Oil3Tw3F<10||Oil3Tw3F>255)
		{
			*CheckTablePt	= 0x64C8;
			Oil3Tw3E		= 0x0064;
			Oil3Tw3F		= 0x00C8;
		}
		CheckTablePt++;   					//CheckTablePt = (Uint16 *)0x8026;
		ReadTableBuf		= *CheckTablePt;    
		Oil3NRept123C	= (ReadTableBuf&0xFF00)>>8;
		Oil3NRept3D		= ReadTableBuf&0x00FF; 
		if(Oil3NRept123C<1||Oil3NRept123C>150||Oil3NRept3D<1||Oil3NRept3D>150)
		{
			*CheckTablePt	= 0x1808;
			Oil3NRept123C	= 0x0018;
			Oil3NRept3D		= 0x0008;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8027;
		ReadTableBuf		= *CheckTablePt;    
		Oil3NRept3E		= (ReadTableBuf&0xFF00)>>8;
		Oil3NRept3F		= ReadTableBuf&0x00FF;
		if(Oil3NRept3E<1||Oil3NRept3E>150||Oil3NRept3F<1||Oil3NRept3F>150)
		{
			*CheckTablePt	= 0x0804;
			Oil3NRept3E		= 0x0008;
			Oil3NRept3F		= 0x0004;
		}
	}

	//PPHOIL6F
else if (WorkMode==0x0005)
{
	PPHOIL6FFreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
	PPHOIL6FFreqSelAry[6]= (PPHOIL6FFreqSelLow&0x000F);
	PPHOIL6FFreqSelAry[5]= (PPHOIL6FFreqSelLow&0x00F0)>>4;
	PPHOIL6FFreqSelAry[4]= (PPHOIL6FFreqSelLow&0x0F00)>>8;
	PPHOIL6FFreqSelAry[3]= (PPHOIL6FFreqSelLow&0xF000)>>12;
	PPHOIL6FFreqSelHi	= *(Uint16 *)0x800B;
	PPHOIL6FFreqSelAry[2]= (PPHOIL6FFreqSelHi&0x000F);
	PPHOIL6FFreqSelAry[1]= (PPHOIL6FFreqSelHi&0x00F0)>>4;

	if (PPHOIL6FFreqSelHi>0x00FF||PPHOIL6FFreqSelAry[1]<1||PPHOIL6FFreqSelAry[1]>8||PPHOIL6FFreqSelAry[2]<1||PPHOIL6FFreqSelAry[2]>8)
	{
		PPHOIL6FFreqSelHi= 0x0082;
		*(Uint16 *)0x800B	= 0x0082;
		PPHOIL6FFreqSelAry[2]= 2;
		PPHOIL6FFreqSelAry[1]= 8;
	}
	if (PPHOIL6FFreqSelAry[3]<1||PPHOIL6FFreqSelAry[3]>8||PPHOIL6FFreqSelAry[4]<1||PPHOIL6FFreqSelAry[4]>8||PPHOIL6FFreqSelAry[5]<1||PPHOIL6FFreqSelAry[5]>8||PPHOIL6FFreqSelAry[6]<1||PPHOIL6FFreqSelAry[6]>8)
	{
		PPHOIL6FFreqSelLow	= 0x5714;
		*(Uint16 *)0x800A	= 0x5714;
		PPHOIL6FFreqSelAry[6]= 4;
		PPHOIL6FFreqSelAry[5]= 1;
		PPHOIL6FFreqSelAry[4]= 7;
		PPHOIL6FFreqSelAry[3]= 5;
	}

	//6 freqencies PP Heavy Oil parameters
	CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
	ReadTableBuf	= *CheckTablePt;  	   //6频PP Heavy Oil 模式下的TE
	PPHOIL6F_TE_123456C	= (ReadTableBuf&0xFF00)>>8;
	PPHOIL6F_TE_246A		= (ReadTableBuf&0x00FF);
	if(PPHOIL6F_TE_123456C<4||PPHOIL6F_TE_123456C>200||PPHOIL6F_TE_246A<4||PPHOIL6F_TE_246A>200)
	{
		*CheckTablePt	= 0x0404;
		PPHOIL6F_TE_123456C	= 0x0004;
		PPHOIL6F_TE_246A	= 0x0004;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
	ReadTableBuf	= *CheckTablePt;
	PPHOIL6FNe12345C	= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
	PPHOIL6FNe6C		= ReadTableBuf&0x00FF;             //NE???
	if(PPHOIL6FNe12345C<1||PPHOIL6FNe12345C>250||PPHOIL6FNe6C<1||PPHOIL6FNe6C>250)
	{
		*CheckTablePt	= 0x194B;
		PPHOIL6FNe12345C	= 0x0019;
		PPHOIL6FNe6C		= 0x004B;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
	PPHOIL6FNe246A	= *CheckTablePt;            //NE???
	if(PPHOIL6FNe246A<1||PPHOIL6FNe246A>3000)
	{
		*CheckTablePt	= 0x02EE;
		PPHOIL6FNe246A		= 0x02EE;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
	PPHOIL6FTw123456C	= *CheckTablePt;
	if(PPHOIL6FTw123456C!=30&&PPHOIL6FTw123456C!=20)
	{
		*CheckTablePt			= 0x0014;
		PPHOIL6FTw123456C		= 0x0014;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8025;   //????F4????
	ReadTableBuf		= *CheckTablePt;
	PPHOIL6FNRept1234C	= (ReadTableBuf&0x0F00)>>8;
	PPHOIL6FNRept5C		= (ReadTableBuf&0x00F0)>>4;
	PPHOIL6FNRept6C		= ReadTableBuf&0x000F;
	if(PPHOIL6FNRept1234C<1||PPHOIL6FNRept1234C>150||PPHOIL6FNRept5C<1||PPHOIL6FNRept5C>150||PPHOIL6FNRept6C<1||PPHOIL6FNRept6C>150)
	{
		*CheckTablePt		= 0x0864;
		PPHOIL6FNRept1234C	= 0x0008;
		PPHOIL6FNRept5C		= 0x0006;
		PPHOIL6FNRept6C		= 0x0004;
	}
}


else if (WorkMode==0x0006)//FBW2
{
	FBW2FFreqSel	= *(Uint16 *)0x800A;         //读取频率选择码
	FBW2FFreqSelAry[1]	= (FBW2FFreqSel&0x00F0)>>4;
	FBW2FFreqSelAry[2]	= (FBW2FFreqSel&0x000F);
	if (FBW2FFreqSel>0x0FFF||FBW2FFreqSelAry[1]<1||FBW2FFreqSelAry[1]>8||FBW2FFreqSelAry[2]<1||FBW2FFreqSelAry[2]>8)
	{
		FBW2FFreqSel	= 0x0087;
		*(Uint16 *)0x800A	= 0x0087;
		FBW2FFreqSelAry[1]	= 8;
		FBW2FFreqSelAry[2]	= 7;
	}
	*(Uint16 *)0x800B	= 0x0000;

	//2 freqencies FBW parameters
	CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
	ReadTableBuf	= *CheckTablePt;  	   //6频PP Heavy Oil 模式下的TE
	FBW2FTe12B		= (ReadTableBuf&0xFF00)>>8;
	FBW2FTe12C		= (ReadTableBuf&0x00FF);
	if(FBW2FTe12B<4||FBW2FTe12B>200||FBW2FTe12C<4||FBW2FTe12C>200)
	{
		*CheckTablePt	= 0x0404;
		FBW2FTe12B	= 0x0004;
		FBW2FTe12C	= 0x0004;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
	ReadTableBuf	= *CheckTablePt;
	FBW2FNe12B		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
	FBW2FNe12C		= ReadTableBuf&0x00FF;             //NE???
	if(FBW2FNe12B<1||FBW2FNe12B>250||FBW2FNe12C<1||FBW2FNe12C>250)
	{
		*CheckTablePt	= 0xE119;
		FBW2FNe12B	= 0x00E1;
		FBW2FNe12C	= 0x0019;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
	FBW2FTw12C	= *CheckTablePt;
	if(FBW2FTw12C!=30&&FBW2FTw12C!=20)
	{
		*CheckTablePt			= 0x0014;
		FBW2FTw12C				= 0x0014;
	}
	CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;
	FBW2FNRept12C		= *CheckTablePt;
	if(FBW2FNRept12C<1||FBW2FNRept12C>150)
	{
		*CheckTablePt		= 0x0016;
		FBW2FNRept12C		= 0x0016;
	}
}


	else if (WorkMode==0x0007)//6 freqencise GAS parameters
	{
		Gas6FreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
		Gas6FreqSelHi	= *(Uint16 *)0x800B;         //读取频率选择码
		Gas6FreqSelAry[1]	= (Gas6FreqSelHi&0x00F0)>>4;
		Gas6FreqSelAry[2]	= Gas6FreqSelHi&0x000F;
		Gas6FreqSelAry[3]	= (Gas6FreqSelLow&0xF000)>>12;
		Gas6FreqSelAry[4]	= (Gas6FreqSelLow&0x0F00)>>8;
		Gas6FreqSelAry[5]	= (Gas6FreqSelLow&0x00F0)>>4;
		Gas6FreqSelAry[6]	= Gas6FreqSelLow&0x000F;

		if (Gas6FreqSelHi>0x00FF||Gas6FreqSelAry[1]<1||Gas6FreqSelAry[1]>8||Gas6FreqSelAry[2]<1||Gas6FreqSelAry[2]>8)
		{
			Gas6FreqSelHi= 0x0058;
			*(Uint16 *)0x800B	= 0x0058;
			Gas6FreqSelAry[2]= 8;
			Gas6FreqSelAry[1]= 5;
		}
		if (Gas6FreqSelAry[3]<1||Gas6FreqSelAry[3]>8||Gas6FreqSelAry[4]<1||Gas6FreqSelAry[4]>8||Gas6FreqSelAry[5]<1||Gas6FreqSelAry[5]>8||Gas6FreqSelAry[6]<1||Gas6FreqSelAry[6]>8)
		{
			Gas6FreqSelLow		= 0x4721;
			*(Uint16 *)0x800A	= 0x4721;
			Gas6FreqSelAry[6]= 1;
			Gas6FreqSelAry[5]= 2;
			Gas6FreqSelAry[4]= 7;
			Gas6FreqSelAry[3]= 4;
		}


		//6 freqencise GAS parameters
		CheckTablePt = (Uint16 *)0x8021;  				//CheckTablePt = (Uint16 *)0x8021;
		Gas6Te123456C24DE		= *CheckTablePt;        //??
		if(Gas6Te123456C24DE<4||Gas6Te123456C24DE>200)
		{
			*CheckTablePt	= 0x0004;
			Gas6Te123456C24DE	= 0x0004;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8022;
		Gas6Ne123456C24DE		= *CheckTablePt;         //?? 
		if(Gas6Ne123456C24DE<1||Gas6Ne123456C24DE>300)
		{
			*CheckTablePt	= 0x0019;
			Gas6Ne123456C24DE	= 0x0019;
		}
		 CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8023;
		ReadTableBuf	= *CheckTablePt;         //读取  
		Gas6Tw123456C	= (ReadTableBuf&0xFF00)>>8;
		Gas6Tw24D		= ReadTableBuf&0x00FF;
		if(Gas6Tw123456C<10||Gas6Tw123456C>200||Gas6Tw24D<10||Gas6Tw24D>200)
		{
			*CheckTablePt	= 0x1432;
			Gas6Tw123456C	= 0x0014;
			Gas6Tw24D		= 0x0032;
		} 
		CheckTablePt++;        //PPgas1模式下的TW的地址CheckTablePt = (Uint16 *)0x8024;
		Gas6Tw24E		= *CheckTablePt;         //??
		if(Gas6Tw24E<1||Gas6Tw24E>500)
		{
			*CheckTablePt	= 0x0064;
			Gas6Tw24E		= 0x0064;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8025;
		ReadTableBuf	= *CheckTablePt;         //读取    
		Gas6NRept24D	= (ReadTableBuf&0xFF00)>>8;
		Gas6NRept24E	= ReadTableBuf&0x00FF;  
		if(Gas6NRept24D<1||Gas6NRept24D>150||Gas6NRept24E<1||Gas6NRept24E>150)
		{
			*CheckTablePt	= 0x0804;
			Gas6NRept24D	= 0x0008;
			Gas6NRept24E	= 0x0004;
		}
		CheckTablePt++;        //PPgas1模式下的NREPT的地址CheckTablePt = (Uint16 *)0x8026;
		ReadTableBuf	= *CheckTablePt;         //读取     
		Gas6NRept1234C	= (ReadTableBuf&0xFF00)>>8;
		Gas6NRept56C	= ReadTableBuf&0x00FF; 
		if(Gas6NRept1234C<1||Gas6NRept1234C>150||Gas6NRept56C<1||Gas6NRept56C>150)
		{
			*CheckTablePt	= 0x2010;
			Gas6NRept1234C	= 0x0020;
			Gas6NRept56C	= 0x0010;
		}
	}



	else if (WorkMode==0x0008)//6 freqencise GAS2 parameters
	{
		Gas6_2FreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
		Gas6_2FreqSelHi	= *(Uint16 *)0x800B;         //读取频率选择码
		Gas6_2FreqSelAry[1]	= (Gas6_2FreqSelHi&0x00F0)>>4;
		Gas6_2FreqSelAry[2]	= Gas6_2FreqSelHi&0x000F;
		Gas6_2FreqSelAry[3]	= (Gas6_2FreqSelLow&0xF000)>>12;
		Gas6_2FreqSelAry[4]	= (Gas6_2FreqSelLow&0x0F00)>>8;
		Gas6_2FreqSelAry[5]	= (Gas6_2FreqSelLow&0x00F0)>>4;
		Gas6_2FreqSelAry[6]	= Gas6_2FreqSelLow&0x000F;

		if (Gas6_2FreqSelHi>0x00FF||Gas6_2FreqSelAry[1]<1||Gas6_2FreqSelAry[1]>8||Gas6_2FreqSelAry[2]<1||Gas6_2FreqSelAry[2]>8)
		{
			Gas6_2FreqSelHi= 0x0058;
			*(Uint16 *)0x800B	= 0x0058;
			Gas6_2FreqSelAry[2]= 8;
			Gas6_2FreqSelAry[1]= 5;
		}
		if (Gas6_2FreqSelAry[3]<1||Gas6_2FreqSelAry[3]>8||Gas6_2FreqSelAry[4]<1||Gas6_2FreqSelAry[4]>8||Gas6_2FreqSelAry[5]<1||Gas6_2FreqSelAry[5]>8||Gas6_2FreqSelAry[6]<1||Gas6_2FreqSelAry[6]>8)
		{
			Gas6_2FreqSelLow		= 0x4721;
			*(Uint16 *)0x800A	= 0x4721;
			Gas6_2FreqSelAry[6]= 1;
			Gas6_2FreqSelAry[5]= 2;
			Gas6_2FreqSelAry[4]= 7;
			Gas6_2FreqSelAry[3]= 4;
		}


		//6 freqencise GAS2 parameters
		CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;
		Gas6_2Te123456C24DE		= *CheckTablePt;        //??
		if(Gas6_2Te123456C24DE<4||Gas6_2Te123456C24DE>200)
		{
			*CheckTablePt		= 0x0004;
			Gas6_2Te123456C24DE	= 0x0004;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8022;
		Gas6_2Ne123456C24DE		= *CheckTablePt;         //??
		if(Gas6_2Ne123456C24DE<1||Gas6_2Ne123456C24DE>300)
		{
			*CheckTablePt	= 0x0019;
			Gas6_2Ne123456C24DE	= 0x0019;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8023;
		ReadTableBuf	= *CheckTablePt;         //读取
		Gas6_2Tw123456C	= (ReadTableBuf&0xFF00)>>8;
		Gas6_2Tw24D		= ReadTableBuf&0x00FF;
		if(Gas6_2Tw123456C<10||Gas6_2Tw123456C>200||Gas6_2Tw24D<10||Gas6_2Tw24D>200)
		{
			*CheckTablePt	= 0x1432;
			Gas6_2Tw123456C	= 0x0014;
			Gas6_2Tw24D		= 0x0032;
		}
		CheckTablePt++;        //PPGAS6_2模式下的TW的地址CheckTablePt = (Uint16 *)0x8024;
		Gas6_2Tw24E		= *CheckTablePt;         //??
		if(Gas6_2Tw24E<1||Gas6_2Tw24E>500)
		{
			*CheckTablePt	= 0x0064;
			Gas6_2Tw24E		= 0x0064;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8025;
		ReadTableBuf	= *CheckTablePt;         //读取
		Gas6_2NRept24D	= (ReadTableBuf&0xFF00)>>8;
		Gas6_2NRept24E	= ReadTableBuf&0x00FF;
		if(Gas6_2NRept24D<1||Gas6_2NRept24D>150||Gas6_2NRept24E<1||Gas6_2NRept24E>150)
		{
			*CheckTablePt	= 0x0804;
			Gas6_2NRept24D	= 0x0008;
			Gas6_2NRept24E	= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8026;
		Gas6_2NRept123456C		= *CheckTablePt;
		if(Gas6_2NRept123456C<1||Gas6_2NRept123456C>150)
		{
			*CheckTablePt			= 0x0010;
			Gas6_2NRept123456C		= 0x0010;
		}
	}
		//PPLOIL6F
	else if (WorkMode==0x000D)//6 freqencies PP Light Oil parameters
	{
		PPLOIL6FFreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
		PPLOIL6FFreqSelAry[6]= (PPLOIL6FFreqSelLow&0x000F);
		PPLOIL6FFreqSelAry[5]= (PPLOIL6FFreqSelLow&0x00F0)>>4;
		PPLOIL6FFreqSelAry[4]= (PPLOIL6FFreqSelLow&0x0F00)>>8;
		PPLOIL6FFreqSelAry[3]= (PPLOIL6FFreqSelLow&0xF000)>>12;
		PPLOIL6FFreqSelHi	= *(Uint16 *)0x800B;
		PPLOIL6FFreqSelAry[2]= (PPLOIL6FFreqSelHi&0x000F);
		PPLOIL6FFreqSelAry[1]= (PPLOIL6FFreqSelHi&0x00F0)>>4;

		if (PPLOIL6FFreqSelHi>0x00FF||PPLOIL6FFreqSelAry[1]<1||PPLOIL6FFreqSelAry[1]>8||PPLOIL6FFreqSelAry[2]<1||PPLOIL6FFreqSelAry[2]>8)
		{
			PPLOIL6FFreqSelHi= 0x0082;
			*(Uint16 *)0x800B	= 0x0082;
			PPLOIL6FFreqSelAry[1]= 8;
			PPLOIL6FFreqSelAry[2]= 2;
		}
		if (PPLOIL6FFreqSelAry[3]<1||PPLOIL6FFreqSelAry[3]>8||PPLOIL6FFreqSelAry[4]<1||PPLOIL6FFreqSelAry[4]>8||PPLOIL6FFreqSelAry[5]<1||PPLOIL6FFreqSelAry[5]>8||PPLOIL6FFreqSelAry[6]<1||PPLOIL6FFreqSelAry[6]>8)
		{
			PPLOIL6FFreqSelLow	= 0x5714;
			*(Uint16 *)0x800A	= 0x5714;
			PPLOIL6FFreqSelAry[6]= 4;
			PPLOIL6FFreqSelAry[5]= 1;
			PPLOIL6FFreqSelAry[4]= 7;
			PPLOIL6FFreqSelAry[3]= 5;
		}

		//6 freqencies PP Light Oil parameters
		CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //6频PP Light Oil 模式下的TE
		PPLOIL6F_TE_156A1B	= (ReadTableBuf&0xFF00)>>8;
		PPLOIL6F_TE_23AB	= (ReadTableBuf&0x00FF);
		if(PPLOIL6F_TE_156A1B<4||PPLOIL6F_TE_156A1B>200||PPLOIL6F_TE_23AB<4||PPLOIL6F_TE_23AB>200)
		{
			*CheckTablePt	= 0x041B;
			PPLOIL6F_TE_156A1B	= 0x0004;
			PPLOIL6F_TE_23AB	= 0x001B;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //6频PP Light Oil 模式下的TE
		PPLOIL6F_TE_4AB	= (ReadTableBuf&0xFF00)>>8;
		PPLOIL6F_TE_123456C	= (ReadTableBuf&0x00FF);
		if(PPLOIL6F_TE_4AB<4||PPLOIL6F_TE_4AB>200||PPLOIL6F_TE_123456C<4||PPLOIL6F_TE_123456C>200)
		{
			*CheckTablePt	= 0x0E04;
			PPLOIL6F_TE_4AB	= 0x000E;
			PPLOIL6F_TE_123456C	= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //6频PP Light Oil 模式下的TE
		PPLOIL6F_TE_2DE	= (ReadTableBuf&0xFF00)>>8;
		PPLOIL6F_TE_4DE	= (ReadTableBuf&0x00FF);
		if(PPLOIL6F_TE_2DE<4||PPLOIL6F_TE_2DE>200||PPLOIL6F_TE_4DE<4||PPLOIL6F_TE_4DE>200)
		{
			*CheckTablePt	= 0x0404;
			PPLOIL6F_TE_2DE	= 0x0004;
			PPLOIL6F_TE_4DE	= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		PPLOIL6FNe156A1B	= *CheckTablePt;            //NE???
		if(PPLOIL6FNe156A1B<1||PPLOIL6FNe156A1B>3000)
		{
			*CheckTablePt			= 0x03E8;
			PPLOIL6FNe156A1B		= 0x03E8;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8025;
		PPLOIL6FNe23AB		= *CheckTablePt;         //??
		if(PPLOIL6FNe23AB<1||PPLOIL6FNe23AB>300)
		{
			*CheckTablePt	= 0x0094;
			PPLOIL6FNe23AB	= 0x0094;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8026;
		PPLOIL6FNe4AB		= *CheckTablePt;         //??
		if(PPLOIL6FNe4AB<1||PPLOIL6FNe4AB>300)
		{
			*CheckTablePt	= 0x011D;
			PPLOIL6FNe4AB	= 0x011D;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8027;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		PPLOIL6FNe24DE		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		PPLOIL6FNe123456C		= ReadTableBuf&0x00FF;             //NE???
		if(PPLOIL6FNe24DE<1||PPLOIL6FNe24DE>250||PPLOIL6FNe123456C<1||PPLOIL6FNe123456C>250)
		{
			*CheckTablePt		= 0x1919;
			PPLOIL6FNe24DE		= 0x0019;
			PPLOIL6FNe123456C	= 0x0019;
		}
		CheckTablePt++;        //TW的地址CheckTablePt = (Uint16 *)0x8028;
		PPLOIL6FTw1234B		= *CheckTablePt;         //??
		if(PPLOIL6FTw1234B<1||PPLOIL6FTw1234B>2000)
		{
			*CheckTablePt		= 0x03E8;
			PPLOIL6FTw1234B		= 0x03E8;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8029;
		ReadTableBuf	= *CheckTablePt;         //读取
		PPLOIL6FTw24D	= (ReadTableBuf&0xFF00)>>8;
		PPLOIL6FTw24E		= ReadTableBuf&0x00FF;
		if(PPLOIL6FTw24D<10||PPLOIL6FTw24D>200||PPLOIL6FTw24E<10||PPLOIL6FTw24E>200)
		{
			*CheckTablePt		= 0x3264;
			PPLOIL6FTw24D		= 0x0032;
			PPLOIL6FTw24E		= 0x0064;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x802A;   //????F4????
		PPLOIL6FTw123456C	= *CheckTablePt;
		if(PPLOIL6FTw123456C!=30&&PPLOIL6FTw123456C!=20)
		{
			*CheckTablePt			= 0x0014;
			PPLOIL6FTw123456C		= 0x0014;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x802B;
		ReadTableBuf	= *CheckTablePt;         //读取
		PPLOIL6NRept24D	= (ReadTableBuf&0xFF00)>>8;
		PPLOIL6NRept24E	= ReadTableBuf&0x00FF;
		if(PPLOIL6NRept24D<1||PPLOIL6NRept24D>150||PPLOIL6NRept24E<1||PPLOIL6NRept24E>150)
		{
			*CheckTablePt	= 0x0804;
			PPLOIL6NRept24D	= 0x0008;
			PPLOIL6NRept24E	= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x802C;
		PPLOIL6NRept123456C		= *CheckTablePt;
		if(PPLOIL6NRept123456C<1||PPLOIL6NRept123456C>150)
		{
			*CheckTablePt			= 0x0010;
			PPLOIL6NRept123456C		= 0x0010;
		}
	}

	else if (WorkMode == 0x00E)// HRT1T22F parameters
	{
		HRT1T22FFreqSel = *(Uint16 *)0x800A; // 读取频率选择码
		HRT1T22FFreqSelAry[1] = (HRT1T22FFreqSel & 0x00F0) >> 4;
		HRT1T22FFreqSelAry[2] = HRT1T22FFreqSel & 0x000F;

		if (HRT1T22FFreqSel > 0x00FF || HRT1T22FFreqSelAry[1] < 1 || HRT1T22FFreqSelAry[2] < 1 || HRT1T22FFreqSelAry[1] > 8 || HRT1T22FFreqSelAry[2] > 8)
		{
			HRT1T22FFreqSel = 0x0085;
			*(Uint16 *)0x800A = 0x0085;
			HRT1T22FFreqSelAry[1] = 8;
			HRT1T22FFreqSelAry[2] = 5;
		}


		// HRT1T22F parameters
		CheckTablePt			= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		HRT1T22FMode_TW_A1		= *CheckTablePt;
		if (HRT1T22FMode_TW_A1 < 1 || HRT1T22FMode_TW_A1 > 7000)
		{
			*CheckTablePt = 5000;
			HRT1T22FMode_TW_A1 = 5000;
		}
		CheckTablePt++;
		HRT1T22FMode_TW_B1 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		if (HRT1T22FMode_TW_B1 < 1 || HRT1T22FMode_TW_B1 > 3000)
		{
			*CheckTablePt = 1620;
			HRT1T22FMode_TW_B1 = 1620;
		}
		CheckTablePt++;
		HRT1T22FMode_TW_B2 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		if (HRT1T22FMode_TW_B2 < 1 || HRT1T22FMode_TW_B2 > 1000)
		{
			*CheckTablePt = 400;
			HRT1T22FMode_TW_B2 = 400;
		}
		CheckTablePt++;
		HRT1T22FMode_TW_B3 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		if (HRT1T22FMode_TW_B3 < 1 || HRT1T22FMode_TW_B3 > 500)
		{
			*CheckTablePt = 200;
			HRT1T22FMode_TW_B3 = 200;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TW_B4 = (ReadTableBuf&0xFF00)>>8; // 取高8位//CheckTablePt = (Uint16 *)0x8025;   //????F4????
		HRT1T22FMode_TW_B5 = ReadTableBuf&0x00FF;		  // 取低8位
		if (HRT1T22FMode_TW_B4 < 1 || HRT1T22FMode_TW_B4 > 0xF0 || HRT1T22FMode_TW_B5 < 1 || HRT1T22FMode_TW_B6 > 0xF0)
		{
			HRT1T22FMode_TW_B4 = 0x64;
			HRT1T22FMode_TW_B5 = 0x50;
			*CheckTablePt = 0x6450;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TW_B6 = (ReadTableBuf&0xFF00)>>8; // 取高8位//CheckTablePt = (Uint16 *)0x8026;   //????F4????
		HRT1T22FMode_TW_B7 = ReadTableBuf&0x00FF;		  // 取低8位
		if (HRT1T22FMode_TW_B6 < 1 || HRT1T22FMode_TW_B6 > 0xF0 || HRT1T22FMode_TW_B7 < 1 || HRT1T22FMode_TW_B7 > 0xF0)
		{
			HRT1T22FMode_TW_B6 = 0x28;
			HRT1T22FMode_TW_B7 = 0x14;
			*CheckTablePt = 0x2814;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TE_A1 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8027;   //????F4????
		HRT1T22FMode_TE_B1 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_TE_A1 < 4 || HRT1T22FMode_TE_A1 > 0xF0 || HRT1T22FMode_TE_B1 < 4 || HRT1T22FMode_TE_B1 > 0xF0)
		{
			HRT1T22FMode_TE_A1 = 0x05;
			HRT1T22FMode_TE_B1 = 0x05;
			*CheckTablePt = 0x0505;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TE_B2 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8028;   //????F4????
		HRT1T22FMode_TE_B3 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_TE_B2 < 4 || HRT1T22FMode_TE_B2 > 0xF0 || HRT1T22FMode_TE_B3 < 4 || HRT1T22FMode_TE_B3 > 0xF0)
		{
			HRT1T22FMode_TE_B2 = 0x05;
			HRT1T22FMode_TE_B3 = 0x04;
			*CheckTablePt = 0x0504;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TE_B4 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8029;   //????F4????
		HRT1T22FMode_TE_B5 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_TE_B4 < 4 || HRT1T22FMode_TE_B4 > 0xF0 || HRT1T22FMode_TE_B5 < 4 || HRT1T22FMode_TE_B5 > 0xF0)
		{
			HRT1T22FMode_TE_B4 = 0x04;
			HRT1T22FMode_TE_B5 = 0x04;
			*CheckTablePt = 0x0404;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_TE_B6 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x802A;   //????F4????
		HRT1T22FMode_TE_B7 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_TE_B6 < 4 || HRT1T22FMode_TE_B6 > 0xF0 || HRT1T22FMode_TE_B7 < 4 || HRT1T22FMode_TE_B7 > 0xF0)
		{
			HRT1T22FMode_TE_B6 = 0x04;
			HRT1T22FMode_TE_B7 = 0x04;
			*CheckTablePt = 0x0404;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_A1 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x802B;   //????F4????
		if (HRT1T22FMode_NE_A1 < 1 || HRT1T22FMode_NE_A1 > 5000)
		{
			*CheckTablePt = 1000;
			HRT1T22FMode_NE_A1 = 1000;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_B1 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x802C;   //????F4????
		if (HRT1T22FMode_NE_B1 < 1 || HRT1T22FMode_NE_B1 > 5000)
		{
			*CheckTablePt = 1000;
			HRT1T22FMode_NE_B1 = 1000;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_B2 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x802D;   //????F4????
		if (HRT1T22FMode_NE_B2 < 1 || HRT1T22FMode_NE_B2 > 5000)
		{
			*CheckTablePt = 400;
			HRT1T22FMode_NE_B2 = 400;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_B3 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x802E;   //????F4????
		if (HRT1T22FMode_NE_B3 < 1 || HRT1T22FMode_NE_B3 > 1000)
		{
			*CheckTablePt = 300;
			HRT1T22FMode_NE_B3 = 300;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_B4 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x802F;   //????F4????
		if (HRT1T22FMode_NE_B4 < 1 || HRT1T22FMode_NE_B4 > 1000)
		{
			*CheckTablePt = 225;
			HRT1T22FMode_NE_B4 = 225;
		}
		CheckTablePt++;
		HRT1T22FMode_NE_B5 = *CheckTablePt;//CheckTablePt = (Uint16 *)0x8030;   //????F4????
		if (HRT1T22FMode_NE_B5 < 1 || HRT1T22FMode_NE_B5 > 1000)
		{
			*CheckTablePt = 150;
			HRT1T22FMode_NE_B5 = 150;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_NE_B6 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8031;   //????F4????
		HRT1T22FMode_NE_B7 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_NE_B6 < 1 || HRT1T22FMode_NE_B6 > 0xF0 || HRT1T22FMode_NE_B7 < 1 || HRT1T22FMode_NE_B7 > 0xF0)
		{
			HRT1T22FMode_NE_B6 = 0x4B;
			HRT1T22FMode_NE_B7 = 0x19;
			*CheckTablePt = 0x4B19;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_NREPT_B2 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8032;   //????F4????
		HRT1T22FMode_NREPT_B3 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_NREPT_B2 < 1 || HRT1T22FMode_NREPT_B2 > 0xF0 || HRT1T22FMode_NREPT_B3 < 1 || HRT1T22FMode_NREPT_B3 > 0xF0)
		{
			HRT1T22FMode_NREPT_B2 = 0x01;
			HRT1T22FMode_NREPT_B3 = 0x02;
			*CheckTablePt = 0x0102;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_NREPT_B4 = (ReadTableBuf&0xFF00)>>8;
		HRT1T22FMode_NREPT_B5 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_NREPT_B4 < 1 || HRT1T22FMode_NREPT_B4 > 0xF0 || HRT1T22FMode_NREPT_B5 < 1 || HRT1T22FMode_NREPT_B5 > 0xF0)
		{
			HRT1T22FMode_NREPT_B4 = 0x02;
			HRT1T22FMode_NREPT_B5 = 0x02;
			*CheckTablePt = 0x0202;
		}
		CheckTablePt++;
		ReadTableBuf	= *CheckTablePt;
		HRT1T22FMode_NREPT_B6 = (ReadTableBuf&0xFF00)>>8;//CheckTablePt = (Uint16 *)0x8034;   //????F4????
		HRT1T22FMode_NREPT_B7 = ReadTableBuf&0x00FF;
		if (HRT1T22FMode_NREPT_B6 < 1 || HRT1T22FMode_NREPT_B6 > 0xF0 || HRT1T22FMode_NREPT_B7 < 1 || HRT1T22FMode_NREPT_B7 > 0xF0)
		{
			HRT1T22FMode_NREPT_B6 = 0x04;
			HRT1T22FMode_NREPT_B7 = 0x28;
			*CheckTablePt = 0x0428;
		}
	}


	else if (WorkMode==0x000F)//6 freqencies PP Heavy Oil2 parameters
	{
		PPHOIL6F_2FreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
		PPHOIL6F_2FreqSelAry[6]= (PPHOIL6F_2FreqSelLow&0x000F);
		PPHOIL6F_2FreqSelAry[5]= (PPHOIL6F_2FreqSelLow&0x00F0)>>4;
		PPHOIL6F_2FreqSelAry[4]= (PPHOIL6F_2FreqSelLow&0x0F00)>>8;
		PPHOIL6F_2FreqSelAry[3]= (PPHOIL6F_2FreqSelLow&0xF000)>>12;
		PPHOIL6F_2FreqSelHi	= *(Uint16 *)0x800B;
		PPHOIL6F_2FreqSelAry[2]= (PPHOIL6F_2FreqSelHi&0x000F);
		PPHOIL6F_2FreqSelAry[1]= (PPHOIL6F_2FreqSelHi&0x00F0)>>4;

		if (PPHOIL6F_2FreqSelHi>0x00FF||PPHOIL6F_2FreqSelAry[1]<1||PPHOIL6F_2FreqSelAry[1]>8||PPHOIL6F_2FreqSelAry[2]<1||PPHOIL6F_2FreqSelAry[2]>8)
		{
			PPHOIL6F_2FreqSelHi= 0x0082;
			*(Uint16 *)0x800B	= 0x0082;
			PPHOIL6F_2FreqSelAry[2]= 2;
			PPHOIL6F_2FreqSelAry[1]= 8;
		}
		if (PPHOIL6F_2FreqSelAry[3]<1||PPHOIL6F_2FreqSelAry[3]>8||PPHOIL6F_2FreqSelAry[4]<1||PPHOIL6F_2FreqSelAry[4]>8||PPHOIL6F_2FreqSelAry[5]<1||PPHOIL6F_2FreqSelAry[5]>8||PPHOIL6F_2FreqSelAry[6]<1||PPHOIL6F_2FreqSelAry[6]>8)
		{
			PPHOIL6F_2FreqSelLow	= 0x5714;
			*(Uint16 *)0x800A	= 0x5714;
			PPHOIL6F_2FreqSelAry[6]= 4;
			PPHOIL6F_2FreqSelAry[5]= 1;
			PPHOIL6F_2FreqSelAry[4]= 7;
			PPHOIL6F_2FreqSelAry[3]= 5;
		}


		//6 freqencies PP Heavy Oil2 parameters
		CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   //6频PP Heavy Oil2 模式下的TE
		PPHOIL6F_2_TE_123456C	= (ReadTableBuf&0xFF00)>>8;
		PPHOIL6F_2_TE_246A		= (ReadTableBuf&0x00FF);
		if(PPHOIL6F_2_TE_123456C<4||PPHOIL6F_2_TE_123456C>200||PPHOIL6F_2_TE_246A<4||PPHOIL6F_2_TE_246A>200)
		{
			*CheckTablePt	= 0x0404;
			PPHOIL6F_2_TE_123456C	= 0x0004;
			PPHOIL6F_2_TE_246A		= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		PPHOIL6F_2Ne12346C	= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		PPHOIL6F_2Ne5C		= ReadTableBuf&0x00FF;             //NE???
		if(PPHOIL6F_2Ne12346C<1||PPHOIL6F_2Ne12346C>250||PPHOIL6F_2Ne5C<1||PPHOIL6F_2Ne5C>250)
		{
			*CheckTablePt	= 0x1932;
			PPHOIL6F_2Ne12346C	= 0x0019;
			PPHOIL6F_2Ne5C		= 0x0032;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		PPHOIL6F_2Ne246A	= *CheckTablePt;            //NE???
		if(PPHOIL6F_2Ne246A<1||PPHOIL6F_2Ne246A>3000)
		{
			*CheckTablePt			= 0x02EE;
			PPHOIL6F_2Ne246A		= 0x02EE;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		PPHOIL6F_2Tw123456C	= *CheckTablePt;
		if(PPHOIL6F_2Tw123456C!=30&&PPHOIL6F_2Tw123456C!=20)
		{
			*CheckTablePt			= 0x0014;
			PPHOIL6F_2Tw123456C		= 0x0014;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8025;
		PPHOIL6F_2NRept123456C		= *CheckTablePt;
		if(PPHOIL6F_2NRept123456C<1||PPHOIL6F_2NRept123456C>150)
		{
			*CheckTablePt				= 0x0010;
			PPHOIL6F_2NRept123456C		= 0x0010;
		}
	}


	else if (WorkMode==0x0011) //3D6F
	{
		P3D6FFreqSelLow	= *(Uint16 *)0x800A;         //读取频率选择码
		P3D6FFreqSelAry[6]= (P3D6FFreqSelLow&0x000F);
		P3D6FFreqSelAry[5]= (P3D6FFreqSelLow&0x00F0)>>4;
		P3D6FFreqSelAry[4]= (P3D6FFreqSelLow&0x0F00)>>8;
		P3D6FFreqSelAry[3]= (P3D6FFreqSelLow&0xF000)>>12;
		P3D6FFreqSelHi	= *(Uint16 *)0x800B;
		P3D6FFreqSelAry[2]= (P3D6FFreqSelHi&0x000F);
		P3D6FFreqSelAry[1]= (P3D6FFreqSelHi&0x00F0)>>4;

		if (P3D6FFreqSelHi>0x00FF||P3D6FFreqSelAry[1]<1||P3D6FFreqSelAry[1]>8||P3D6FFreqSelAry[2]<1||P3D6FFreqSelAry[2]>8)
		{
			P3D6FFreqSelHi= 0x0082;
			*(Uint16 *)0x800B	= 0x0082;
			P3D6FFreqSelAry[2]= 2;
			P3D6FFreqSelAry[1]= 8;
		}
		if (P3D6FFreqSelAry[3]<1||P3D6FFreqSelAry[3]>8||P3D6FFreqSelAry[4]<1||P3D6FFreqSelAry[4]>8||P3D6FFreqSelAry[5]<1||P3D6FFreqSelAry[5]>8||P3D6FFreqSelAry[6]<1||P3D6FFreqSelAry[6]>8)
		{
			P3D6FFreqSelLow	= 0x5714;
			*(Uint16 *)0x800A	= 0x5714;
			P3D6FFreqSelAry[6]= 4;
			P3D6FFreqSelAry[5]= 1;
			P3D6FFreqSelAry[4]= 7;
			P3D6FFreqSelAry[3]= 5;
		}


		//P3D6F parameters
		CheckTablePt	= (Uint16 *)0x8021;//CheckTablePt = (Uint16 *)0x8021;   //????F4????
		ReadTableBuf	= *CheckTablePt;  	   // P3D6F模式下的TE
		P3D6F_TE_1A	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_2A	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_1A<4||P3D6F_TE_1A>200||P3D6F_TE_2A<4||P3D6F_TE_2A>200)
		{
			*CheckTablePt	= 0x050A;
			P3D6F_TE_1A		= 0x0005;
			P3D6F_TE_2A		= 0x000A;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8022;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6F_TE_3A	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_4A	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_3A<4||P3D6F_TE_3A>200||P3D6F_TE_4A<4||P3D6F_TE_4A>200)
		{
			*CheckTablePt	= 0x1428;
			P3D6F_TE_3A		= 0x0014;
			P3D6F_TE_4A		= 0x0028;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8023;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6F_TE_5B	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_6B	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_5B<4||P3D6F_TE_5B>200||P3D6F_TE_6B<4||P3D6F_TE_6B>200)
		{
			*CheckTablePt	= 0x3C64;
			P3D6F_TE_5B		= 0x003C;
			P3D6F_TE_6B		= 0x0064;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8024;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6F_TE_1C	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_2D	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_1C<4||P3D6F_TE_1C>200||P3D6F_TE_2D<4||P3D6F_TE_2D>200)
		{
			*CheckTablePt	= 0x0404;
			P3D6F_TE_1C		= 0x0004;
			P3D6F_TE_2D		= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8025;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6F_TE_3E	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_4F	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_3E<4||P3D6F_TE_3E>200||P3D6F_TE_4F<4||P3D6F_TE_4F>200)
		{
			*CheckTablePt	= 0x0404;
			P3D6F_TE_3E		= 0x0004;
			P3D6F_TE_4F		= 0x0004;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8026;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6F_TE_5F	= (ReadTableBuf&0xFF00)>>8;
		P3D6F_TE_6F	= (ReadTableBuf&0x00FF);
		if(P3D6F_TE_5F<4||P3D6F_TE_5F>200||P3D6F_TE_6F<4||P3D6F_TE_6F>200)
		{
			*CheckTablePt	= 0x0404;
			P3D6F_TE_5F		= 0x0004;
			P3D6F_TE_6F		= 0x0004;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8027;
		P3D6FNe1A		= *CheckTablePt;         //??
		if(P3D6FNe1A<1||P3D6FNe1A>3000)
		{
			*CheckTablePt	= 0X03E8;
			P3D6FNe1A		= 0X03E8;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8028;
		P3D6FNe2A		= *CheckTablePt;         //??
		if(P3D6FNe2A<1||P3D6FNe2A>1000)
		{
			*CheckTablePt	= 0X01F4;
			P3D6FNe2A		= 0X01F4;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8029;
		P3D6FNe3A		= *CheckTablePt;         //??
		if(P3D6FNe3A<1||P3D6FNe3A>500)
		{
			*CheckTablePt	= 0X00FA;
			P3D6FNe3A		= 0X00FA;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x802A;
		P3D6FNe4A		= *CheckTablePt;         //??
		if(P3D6FNe4A<1||P3D6FNe4A>300)
		{
			*CheckTablePt	= 0X007D;
			P3D6FNe4A		= 0X007D;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x802B;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6FNe5B		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		P3D6FNe6B		= ReadTableBuf&0x00FF;             //NE???
		if(P3D6FNe5B<1||P3D6FNe5B>250||P3D6FNe6B<1||P3D6FNe6B>250)
		{
			*CheckTablePt		= 0x5032;
			P3D6FNe5B			= 0x0050;
			P3D6FNe6B			= 0x0032;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x802C;   //????F4????
		ReadTableBuf	= *CheckTablePt;
		P3D6FNe1C		= (ReadTableBuf&0xFF00)>>8;            //NE寄存器(高位)
		P3D6FNe2D		= ReadTableBuf&0x00FF;             //NE???
		if(P3D6FNe1C<1||P3D6FNe1C>250||P3D6FNe2D<1||P3D6FNe2D>250)
		{
			*CheckTablePt		= 0x194B;
			P3D6FNe1C			= 0x0019;
			P3D6FNe2D			= 0x004B;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x802D;
		P3D6FNe3E		= *CheckTablePt;         //??
		if(P3D6FNe3E<1||P3D6FNe3E>300)
		{
			*CheckTablePt	= 0X0096;
			P3D6FNe3E		= 0X0096;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x802E;
		P3D6FNe4F		= *CheckTablePt;         //??
		if(P3D6FNe4F<1||P3D6FNe4F>300)
		{
			*CheckTablePt	= 0X00E1;
			P3D6FNe4F		= 0X00E1;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x802F;
		P3D6FNe5F		= *CheckTablePt;         //??
		if(P3D6FNe5F<1||P3D6FNe5F>500)
		{
			*CheckTablePt	= 0X012C;
			P3D6FNe5F		= 0X012C;
		}
		CheckTablePt++;   				//CheckTablePt = (Uint16 *)0x8030;
		P3D6FNe6F		= *CheckTablePt;         //??
		if(P3D6FNe6F<1||P3D6FNe6F>1000)
		{
			*CheckTablePt	= 0X01F4;
			P3D6FNe6F		= 0X01F4;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8031;
		ReadTableBuf	= *CheckTablePt;         //读取
		P3D6FTw1C		= (ReadTableBuf&0xFF00)>>8;
		P3D6FTw2D		= ReadTableBuf&0x00FF;
		if(P3D6FTw1C<10||P3D6FTw1C>200||P3D6FTw2D<10||P3D6FTw2D>200)
		{
			*CheckTablePt		= 0x1428;
			P3D6FTw1C		= 0x0014;
			P3D6FTw2D		= 0x0028;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8032;
		ReadTableBuf	= *CheckTablePt;         //读取
		P3D6FTw3E		= (ReadTableBuf&0xFF00)>>8;
		P3D6FTw4F		= ReadTableBuf&0x00FF;
		if(P3D6FTw3E<10||P3D6FTw3E>200||P3D6FTw4F<10||P3D6FTw4F>200)
		{
			*CheckTablePt		= 0x50A0;
			P3D6FTw3E		= 0x0050;
			P3D6FTw4F		= 0x00A0;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8033;   //????F4????
		P3D6FTw5F	= *CheckTablePt;
		if(P3D6FTw5F<10||P3D6FTw5F>500)
		{
			*CheckTablePt	= 0X0140;
			P3D6FTw5F		= 0X0140;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8034;   //????F4????
		P3D6FTw6F	= *CheckTablePt;
		if(P3D6FTw6F<10||P3D6FTw6F>1000)
		{
			*CheckTablePt	= 0X0280;
			P3D6FTw6F		= 0X0280;
		}
		CheckTablePt++;        		//CheckTablePt = (Uint16 *)0x8035;
		ReadTableBuf	= *CheckTablePt;         //读取
		P3D6FNRept1C	= (ReadTableBuf&0xFF00)>>8;
		P3D6FNRept2D	= ReadTableBuf&0x00FF;
		if(P3D6FNRept1C<1||P3D6FNRept1C>150||P3D6FNRept2D<1||P3D6FNRept2D>150)
		{
			*CheckTablePt	= 0x2010;
			P3D6FNRept1C	= 0x0020;
			P3D6FNRept2D	= 0x0010;
		}
		CheckTablePt++;						//CheckTablePt = (Uint16 *)0x8036;   //????F4????
		ReadTableBuf		= *CheckTablePt;
		P3D6FNRept3E			= (ReadTableBuf&0x0F00)>>8;
		P3D6FNRept4F			= (ReadTableBuf&0x00F0)>>4;
		P3D6FNRept5F			= ReadTableBuf&0x000F;
		if(P3D6FNRept3E<1||P3D6FNRept3E>150||P3D6FNRept4F<1||P3D6FNRept4F>150||P3D6FNRept5F<1||P3D6FNRept5F>150)
		{
			*CheckTablePt		= 0x0842;
			P3D6FNRept3E		= 0x0008;
			P3D6FNRept4F		= 0x0004;
			P3D6FNRept5F		= 0x0002;
		}
	}
//single and double frequency T2D mode parameters 
	else if(WorkMode==0x0010)
	{
		*(Uint16 *)0x800B	= 0;
		//if (WorkMode==0x0010)

		T2DFreqSel	= *(Uint16 *)0x800A;
		if (T2DFreqSel<1||T2DFreqSel>6)
		{
			T2DFreqSel	= 6;
			*(Uint16 *)0x800A	= 6;
		}

		CheckTablePt  	= (Uint16 *)0x8021;   //?/?????????CPMG?TW//CheckTablePt   = (Uint16 *)0x8021;
		T2DCPMGTwA		= *CheckTablePt;         //??
		if(T2DCPMGTwA<1000||T2DCPMGTwA>30000)
		{
			*CheckTablePt	= 10000;
			T2DCPMGTwA		= 10000;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8022;   //?/?????????DE?TW
		T2DDETwA	= *CheckTablePt;         //??
		if(T2DDETwA<500||T2DDETwA>30000)
		{
			*CheckTablePt	= 1200;
			T2DDETwA		= 1200;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8023;   //?/?????????CBW?TW
		T2DCBWTwA	= *CheckTablePt;         //??
		if(T2DCBWTwA<10||T2DCBWTwA>500)
		{
			*CheckTablePt	= 0x0014;
			T2DCBWTwA		= 0x0014;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8024;   //?/?????????DE?TW
		T2DCBWTeAB	= *CheckTablePt;         //??
		if(T2DCBWTeAB<4||T2DCBWTeAB>100)
		{
			*CheckTablePt	= 4;
			T2DCBWTeAB		= 4;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8025;   //?/?????????DE?TW
		T2DDCTesA	= *CheckTablePt;         //??
		if(T2DDCTesA<4||T2DDCTesA>200)
		{
			*CheckTablePt	= 0x0005;
			T2DDCTesA		= 0x0005;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8026;   //?/?????????DE?TW
		T2DDETelAAry[1]	= *CheckTablePt;         //??
		if(T2DDETelAAry[1]<4||T2DDETelAAry[1]>800)
		{
			*CheckTablePt	= 0x0014;
			T2DDETelAAry[1]	= 0x0014;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8027;   //?/?????????DE?TW
		T2DDETelAAry[2]	= *CheckTablePt;         //??
		if(T2DDETelAAry[2]<4||T2DDETelAAry[2]>800)
		{
			*CheckTablePt	= 0x001E;
			T2DDETelAAry[2]	= 0x001E;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8028;   //?/?????????DE?TW
		T2DDETelAAry[3]	= *CheckTablePt;         //??
		if(T2DDETelAAry[3]<4||T2DDETelAAry[3]>800)
		{
			*CheckTablePt	= 0x0032;
			T2DDETelAAry[3]	= 0x0032;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8029;   //?/?????????DE?TW
		T2DDETelAAry[4]	= *CheckTablePt;         //??
		if(T2DDETelAAry[4]<4||T2DDETelAAry[4]>800)
		{
			*CheckTablePt	= 0x0050;
			T2DDETelAAry[4]	= 0x0050;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802A;   //?/?????????DE?TW
		T2DDETelAAry[5]	= *CheckTablePt;         //??
		if(T2DDETelAAry[5]<4||T2DDETelAAry[5]>800)
		{
			*CheckTablePt	= 0x0096;
			T2DDETelAAry[5]	= 0x0096;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802B;   //?/?????????DE?TW
		T2DDETelAAry[6]	= *CheckTablePt;         //??
		if(T2DDETelAAry[6]<4||T2DDETelAAry[6]>800)
		{
			*CheckTablePt	= 0x00F0;
			T2DDETelAAry[6]	= 0x00F0;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802C;   //?/?????????DE?TW
		T2DCBWNreptA	= *CheckTablePt;         //??
		if(T2DCBWNreptA<3||T2DCBWNreptA>200)
		{
			*CheckTablePt	= 0x0018;
			T2DCBWNreptA	= 0x0018;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802D;   //?/?????????DE?TW
		T2DCPMGNeA	= *CheckTablePt;         //??
		if(T2DCPMGNeA<3||T2DCPMGNeA>3000)
		{
			*CheckTablePt	= 1002;
			T2DCPMGNeA		= 1002;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802E;   //?/?????????DE?TW
		T2DDENeA	= *CheckTablePt;         //??
		if(T2DDENeA<3||T2DDENeA>3000)
		{
			*CheckTablePt	= 1002;
			T2DDENeA		= 1002;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802F;   //?/?????????DE?TW
		T2DCBWNeA	= *CheckTablePt;         //??
		if(T2DCBWNeA<3||T2DCBWNeA>200)
		{
			*CheckTablePt	= 0x0019;
			T2DCBWNeA		= 0x0019;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8030;   //?/?????????DE?TW
		T2DDEmn	= *CheckTablePt;         //??
		if(T2DDEmn<1||T2DDEmn>6)
		{
			*CheckTablePt	= 6;
			T2DDEmn			= 6;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8031;   //?/?????????DE?TW
		T2DDEm	= *CheckTablePt;         //??
		if(T2DDEm<1||T2DDEm>8)
		{
			*CheckTablePt	= 2;
			T2DDEm			= 2;
		}
	}


//double frequency T2D parameters
	else if(WorkMode==0x0020)
	{

		*(Uint16 *)0x800B	= 0;
		T2DFreqSel		= *(Uint16 *)0x800A;
		T2DFreqSelAry[1]= (T2DFreqSel&0x00F0)>>4;
		T2DFreqSelAry[2]= T2DFreqSel&0x000F;
		if  (T2DFreqSel>0x00FF||T2DFreqSelAry[1]<1||T2DFreqSelAry[1]>6||T2DFreqSelAry[2]<1||T2DFreqSelAry[2]>6)
		{
			T2DFreqSel		= 0x0063;
			*(Uint16 *)0x800A	= 0x0063;
			T2DFreqSelAry[1]= 6;
			T2DFreqSelAry[2]= 3;
		}

			CheckTablePt = (Uint16 *)0x8021;   			//CheckTablePt   = (Uint16 *)0x8021;
			T2DCPMGTwA		= *CheckTablePt;         //??
			if(T2DCPMGTwA<1000||T2DCPMGTwA>30000)
			{
				*CheckTablePt	= 9800;
				T2DCPMGTwA		= 9800;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8022;   //?/?????????DE?TW
			T2DDETwA	= *CheckTablePt;         //??
			if(T2DDETwA<400||T2DDETwA>30000)
			{
				*CheckTablePt	= 1200;
				T2DDETwA		= 1200;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8023;   //?/?????????DE?TW
			T2DCBWTwA	= *CheckTablePt;         //??
			if(T2DCBWTwA<5||T2DCBWTwA>500)
			{
				*CheckTablePt	= 0x0014;
				T2DCBWTwA		= 0x0014;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8024;   //?/?????????DE?TW
			T2DCBWTeAB	= *CheckTablePt;         //??
			if(T2DCBWTeAB<4||T2DCBWTeAB>100)
			{
				*CheckTablePt	= 0x0004;
				T2DCBWTeAB		= 0x0004;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8025;   //?/?????????DE?TW
			T2DDETesA	= *CheckTablePt;         //??
			if(T2DDETesA<4||T2DDETesA>200)
			{
				*CheckTablePt	= 0x0005;
				T2DDETesA		= 0x0005;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8026;   //?/?????????DE?TW
			T2DDETelAAry[1]	= *CheckTablePt;         //??
			if(T2DDETelAAry[1]<4||T2DDETelAAry[1]>400)
			{
				*CheckTablePt	= 0x0014;
				T2DDETelAAry[1]	= 0x0014;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8027;   //?/?????????DE?TW
			T2DDETelAAry[2]	= *CheckTablePt;         //??
			if(T2DDETelAAry[2]<4||T2DDETelAAry[2]>400)
			{
				*CheckTablePt	= 0x001E;
				T2DDETelAAry[2]	= 0x001E;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8028;   //?/?????????DE?TW
			T2DDETelAAry[3]	= *CheckTablePt;         //??
			if(T2DDETelAAry[3]<4||T2DDETelAAry[3]>400)
			{
				*CheckTablePt	= 0x0032;
				T2DDETelAAry[3]	= 0x0032;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8029;   //?/?????????DE?TW
			T2DDETelAAry[4]	= *CheckTablePt;         //??
			if(T2DDETelAAry[4]<4||T2DDETelAAry[4]>400)
			{
				*CheckTablePt	= 0x0050;
				T2DDETelAAry[4]	= 0x0050;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802A;   //?/?????????DE?TW
			T2DDETelAAry[5]	= *CheckTablePt;         //??
			if(T2DDETelAAry[5]<4||T2DDETelAAry[5]>400)
			{
				*CheckTablePt	= 0x0078;
				T2DDETelAAry[5]	= 0x0078;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802B;   //?/?????????DE?TW
			T2DDETelAAry[6]	= *CheckTablePt;         //??
			if(T2DDETelAAry[6]<4||T2DDETelAAry[6]>400)
			{
				*CheckTablePt	= 240;
				T2DDETelAAry[6]	= 240;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802C;   //?/?????????DE?TW
			T2DCBWNreptA	= *CheckTablePt;         //??
			if(T2DCBWNreptA<4||T2DCBWNreptA>150)
			{
				*CheckTablePt	= 0x0018;
				T2DCBWNreptA	= 0x0018;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802D;   //?/?????????DE?TW
			T2DCPMGNeA	= *CheckTablePt;         //??
			if(T2DCPMGNeA<4||T2DCPMGNeA>3000)
			{
				*CheckTablePt	= 1002;
				T2DCPMGNeA		= 1002;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802E;   //?/?????????DE?TW
			T2DDENeA	= *CheckTablePt;         //??
			if(T2DDENeA<4||T2DDENeA>3000)
			{
				*CheckTablePt	= 1002;
				T2DDENeA		= 1002;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x802F;   //?/?????????DE?TW
			T2DCBWNeA	= *CheckTablePt;         //??
			if(T2DCBWNeA<4||T2DCBWNeA>300)
			{
				*CheckTablePt	= 0x0019;
				T2DCBWNeA		= 0x0019;
			}
			CheckTablePt++;
			T2DDEmn	= *CheckTablePt;         //??
			if(T2DDEmn<1||T2DDEmn>6)
			{
				*CheckTablePt	= 0x0006;
				T2DDEmn		= 0x0006;
			}
			CheckTablePt++;
			T2DDEm	= *CheckTablePt;         //??
			if(T2DDEm<2||T2DDEm>100)
			{
				*CheckTablePt	= 0x0002;
				T2DDEm		= 0x0002;
			}
			CheckTablePt++;   			//CheckTablePt   = (Uint16 *)0x8030;
			T2DCPMGTwB		= *CheckTablePt;         //??
			if(T2DCPMGTwB<1000||T2DCPMGTwB>30000)
			{
				*CheckTablePt	= 9800;
				T2DCPMGTwB		= 9800;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8031;   //?/?????????DE?TW
			T2DDETwB	= *CheckTablePt;         //??
			if(T2DDETwB<400||T2DDETwB>30000)
			{
				*CheckTablePt	= 1200;
				T2DDETwB		= 1200;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8032;   //?/?????????DE?TW
			T2DCBWTwB	= *CheckTablePt;         //??
			if(T2DCBWTwB<5||T2DCBWTwB>500)
			{
				*CheckTablePt	= 0x0014;
				T2DCBWTwB		= 0x0014;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8033;   //?/?????????DE?TW
			T2DDETesB	= *CheckTablePt;         //??
			if(T2DDETesB<4||T2DDETesB>200)
			{
				*CheckTablePt	= 0x0005;
				T2DDETesB		= 0x0005;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8034;   //?/?????????DE?TW
			T2DDETelBAry[1]	= *CheckTablePt;         //??
			if(T2DDETelBAry[1]<4||T2DDETelBAry[1]>400)
			{
				*CheckTablePt	= 0x001E;
				T2DDETelBAry[1]	= 0x001E;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8035;   //?/?????????DE?TW
			T2DDETelBAry[2]	= *CheckTablePt;         //??
			if(T2DDETelBAry[2]<4||T2DDETelBAry[2]>400)
			{
				*CheckTablePt	= 0x0028;
				T2DDETelBAry[2]	= 0x0028;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8036;   //?/?????????DE?TW
			T2DDETelBAry[3]	= *CheckTablePt;         //??
			if(T2DDETelBAry[3]<4||T2DDETelBAry[3]>400)
			{
				*CheckTablePt	= 0x0046;
				T2DDETelBAry[3]	= 0x0046;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8037;   //?/?????????DE?TW
			T2DDETelBAry[4]	= *CheckTablePt;         //??
			if(T2DDETelBAry[4]<4||T2DDETelBAry[4]>400)
			{
				*CheckTablePt	= 0x0064;
				T2DDETelBAry[4]	= 0x0064;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8038;   //?/?????????DE?TW
			T2DDETelBAry[5]	= *CheckTablePt;         //??
			if(T2DDETelBAry[5]<4||T2DDETelBAry[5]>400)
			{
				*CheckTablePt	= 0x00A0;
				T2DDETelBAry[5]	= 0x00A0;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8039;   //?/?????????DE?TW
			T2DDETelBAry[6]	= *CheckTablePt;         //??
			if(T2DDETelBAry[6]<4||T2DDETelBAry[6]>400)
			{
				*CheckTablePt	= 0x0140;
				T2DDETelBAry[6]	= 0x0140;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x803A;   //?/?????????DE?TW
			T2DCBWNreptB	= *CheckTablePt;         //??
			if(T2DCBWNreptB<4||T2DCBWNreptB>150)
			{
				*CheckTablePt	= 0x0018;
				T2DCBWNreptB	= 0x0018;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x803B;   //?/?????????DE?TW
			T2DCPMGNeB	= *CheckTablePt;         //??
			if(T2DCPMGNeB<4||T2DCPMGNeB>3000)
			{
				*CheckTablePt	= 1002;
				T2DCPMGNeB		= 1002;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x803C;   //?/?????????DE?TW
			T2DDENeB	= *CheckTablePt;         //??
			if(T2DDENeB<4||T2DDENeB>3000)
			{
				*CheckTablePt	= 1002;
				T2DDENeB		= 1002;
			}
			CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x803D;   //?/?????????DE?TW
			T2DCBWNeB	= *CheckTablePt;         //??
			if(T2DCBWNeB<4||T2DCBWNeB>300)
			{
				*CheckTablePt	= 0x0019;
				T2DCBWNeB		= 0x0019;
			}
	}

//multiple T2D mode parameters
	else if(WorkMode==0x0030)
	{
		T2DFreqSel		= *(Uint16 *)0x800A;
		T2DFreqSelAry[1]= (T2DFreqSel&0x0F00)>>8;
		T2DFreqSelAry[2]= (T2DFreqSel&0x00F0)>>4;
		T2DFreqSelAry[3]= T2DFreqSel&0x000F;
		if (T2DFreqSel>0x0FFF||T2DFreqSelAry[1]<1||T2DFreqSelAry[1]>6||T2DFreqSelAry[2]<1||T2DFreqSelAry[2]>6||T2DFreqSelAry[3]<1||T2DFreqSelAry[3]>6)
		{
			T2DFreqSel		= 0x0852;
			*(Uint16 *)0x800A	= 0x0852;
			T2DFreqSelAry[1]= 8;
			T2DFreqSelAry[2]= 5;
			T2DFreqSelAry[3]= 2;		
		}
		*(Uint16 *)0x800B	= 0x0;

		CheckTablePt	= (Uint16 *)0x8021;   //??A?CPMG?TW//CheckTablePt   = (Uint16 *)0x8021;
		T2DCPMGTwA		= *CheckTablePt;         //??
		if(T2DCPMGTwA<1000||T2DCPMGTwA>30000)
		{
			*CheckTablePt	= 10000;
			T2DCPMGTwA		= 10000;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8022;   //??BC?DE?TW
		T2DDETwBC	= *CheckTablePt;         //??
		if(T2DDETwBC<50||T2DDETwBC>30000)
		{
			*CheckTablePt	= 1200;
			T2DDETwBC		= 1200;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8023;   //??A?CBW?TW
		T2DCBWTwA	= *CheckTablePt;         //??
		if(T2DCBWTwA<10||T2DCBWTwA>500)
		{
			*CheckTablePt	= 20;
			T2DCBWTwA		= 20;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8024;   //CPMG&DE?TES
		T2DDCTes	= *CheckTablePt;         //??
		if(T2DDCTes<4||T2DDCTes>500)
		{
			*CheckTablePt	= 5;
			T2DDCTes		= 5;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8025;   //??B1?TEL
		T2DDETelBAry[1]	= *CheckTablePt;         //??
		if(T2DDETelBAry[1]<4||T2DDETelBAry[1]>500)
		{
			*CheckTablePt	= 20;
			T2DDETelBAry[1]	= 20;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8026;   //??B1?TEL
		T2DDETelBAry[2]	= *CheckTablePt;         //??
		if(T2DDETelBAry[2]<4||T2DDETelBAry[2]>500)
		{
			*CheckTablePt	= 80;
			T2DDETelBAry[2]	= 80;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8027;   //??B1?TEL
		T2DDETelBAry[3]	= *CheckTablePt;         //??
		if(T2DDETelBAry[3]<4||T2DDETelBAry[3]>500)
		{
			*CheckTablePt	= 240;
			T2DDETelBAry[3]	= 240;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8028;   //??C1?TEL
		T2DDETelCAry[1]	= *CheckTablePt;         //??
		if(T2DDETelCAry[1]<4||T2DDETelCAry[1]>500)
		{
			*CheckTablePt	= 30;
			T2DDETelCAry[1]	= 30;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x8029;   //??C1?TEL
		T2DDETelCAry[2]	= *CheckTablePt;         //??
		if(T2DDETelCAry[2]<4||T2DDETelCAry[2]>500)
		{
			*CheckTablePt	= 50;
			T2DDETelCAry[2]	= 50;
		}
		CheckTablePt++;				//CheckTablePt   = (Uint16 *)0x802A;   //??C1?TEL
		T2DDETelCAry[3]	= *CheckTablePt;         //??
		if(T2DDETelCAry[3]<4||T2DDETelCAry[3]>500)
		{
			*CheckTablePt	= 120;
			T2DDETelCAry[3]	= 120;
		}
		CheckTablePt++;				//= (Uint16 *)0x802B;   //??A?CBW?????
		T2DCBWNreptA	= *CheckTablePt;         //??
		if(T2DCBWNreptA<1||T2DCBWNreptA>150)
		{
			*CheckTablePt	= 24;
			T2DCBWNreptA	= 24;
		}
		CheckTablePt++;				//= (Uint16 *)0x802C;   //??A?CPMG?NE
		T2DCPMGNeA	= *CheckTablePt;         //??
		if(T2DCPMGNeA<4||T2DCPMGNeA>3000)
		{
			*CheckTablePt	= 1002;
			T2DCPMGNeA		= 1002;
		}
		CheckTablePt++;				//= (Uint16 *)0x802D;   //??BC?DE?NE
		T2DDENeBC	= *CheckTablePt;         //??
		if(T2DDENeBC<4||T2DDENeBC>3000)
		{
			*CheckTablePt	= 1002;
			T2DDENeBC		= 1002;
		}
		CheckTablePt++;				//= (Uint16 *)0x802E;   //??A?CBW?NE
		T2DCBWNeA	= *CheckTablePt;         //??
		if(T2DCBWNeA<4||T2DCBWNeA>300)
		{
			*CheckTablePt	= 0x0019;
			T2DCBWNeA		= 0x0019;
		}
		CheckTablePt++;				//= (Uint16 *)0x802F;   //DE????
		T2DDEmn	= *CheckTablePt;         //??
		if(T2DDEmn<1||T2DDEmn>6)
		{
			*CheckTablePt	= 3;
			T2DDEmn			= 3;
		}
		CheckTablePt++;				//= (Uint16 *)0x8030;   //DE????????
		T2DDEm	= *CheckTablePt;         //??
		if(T2DDEm<1||T2DDEm>8)
		{
			*CheckTablePt	= 2;
			T2DDEm			= 2;
		}
		CheckTablePt++;				//= (Uint16 *)0x8031;   //DE????????
		T2DCBWTeA	= *CheckTablePt;         //??
		if(T2DCBWTeA<4||T2DCBWTeA>200)
		{
			*CheckTablePt	= 4;
			T2DCBWTeA		= 4;
		}
	}
 
//single frequency T1T2 mode parameters
	else if(WorkMode==0x0040)
	{
		T1T2FreqSel	= *(Uint16 *)0x800A;
		if (T1T2FreqSel<1||T1T2FreqSel>6)
		{
			T1T2FreqSel	= 6;
			*(Uint16 *)0x800A	= 6;
		}
		*(Uint16 *)0x800B	= 0;
		CheckTablePt	= (Uint16 *)0x8021;   //A1?TW//CheckTablePt   = (Uint16 *)0x8021;
		T1T2TwAAry[1]	= *CheckTablePt;         //??
		if(T1T2TwAAry[1]<1000||T1T2TwAAry[1]>30000)
		{
			*CheckTablePt	= 12000;
			T1T2TwAAry[1]	= 12000;
		}
		CheckTablePt++;			//CheckTablePt   = (Uint16 *)0x8022;   //A2?TW
		T1T2TwAAry[2] = *CheckTablePt;         //??
		if(T1T2TwAAry[2]<10||T1T2TwAAry[2]>30000)
		{
			*CheckTablePt	= 3000;
			T1T2TwAAry[2]	= 3000;
		}
		CheckTablePt++;			//= (Uint16 *)0x8023;   //A3?TW
		T1T2TwAAry[3] = *CheckTablePt;         //??
		if(T1T2TwAAry[3]<10||T1T2TwAAry[3]>30000)
		{
			*CheckTablePt	= 1000;
			T1T2TwAAry[3]	= 1000;
		}
		CheckTablePt++;			//= (Uint16 *)0x8024;   //A4?TW
		T1T2TwAAry[4] = *CheckTablePt;         //??
		if(T1T2TwAAry[4]<10||T1T2TwAAry[4]>30000)
		{
			*CheckTablePt	= 400;
			T1T2TwAAry[4]	= 400;
		}
		CheckTablePt++;			//= (Uint16 *)0x8025;   //A5?TW
		T1T2TwAAry[5] = *CheckTablePt;         //??
		if(T1T2TwAAry[5]<10||T1T2TwAAry[5]>30000)
		{
			*CheckTablePt	= 200;
			T1T2TwAAry[5]	= 200;
		}
		CheckTablePt++;			//= (Uint16 *)0x8026;   //A6?TW
		T1T2TwAAry[6] = *CheckTablePt;         //??
		if(T1T2TwAAry[6]<10||T1T2TwAAry[6]>30000)
		{
			*CheckTablePt	= 80;
			T1T2TwAAry[6]	= 80;
		}
		CheckTablePt++;			//= (Uint16 *)0x8027;   //A7?TW
		T1T2TwAAry[7] = *CheckTablePt;         //??
		if(T1T2TwAAry[7]<10||T1T2TwAAry[7]>30000)
		{
			*CheckTablePt	= 40;
			T1T2TwAAry[7]	= 40;
		}
		CheckTablePt++;			//= (Uint16 *)0x8028;   //A8?TW
		T1T2TwAAry[8] = *CheckTablePt;         //??
		if(T1T2TwAAry[8]<4||T1T2TwAAry[8]>500)
		{
			*CheckTablePt	= 20;
			T1T2TwAAry[8]	= 20;
		}
		CheckTablePt++;			//= (Uint16 *)0x8029;   //A9?TW
		T1T2TwAAry[9] = *CheckTablePt;         //??
		if(T1T2TwAAry[9]<4||T1T2TwAAry[9]>500)
		{
			*CheckTablePt	= 10;
			T1T2TwAAry[9]	= 10;
		}
		CheckTablePt++;			//= (Uint16 *)0x802A;   //A1?NE
		T1T2NeAAry[1] = *CheckTablePt;         //??
		if(T1T2NeAAry[1]<4||T1T2NeAAry[1]>3000)
		{
			*CheckTablePt	= 1000;
			T1T2NeAAry[1]	= 1000;
		}
		CheckTablePt++;			//= (Uint16 *)0x802B;   //A1?NE
		T1T2NeAAry[2] = *CheckTablePt;         //??
		if(T1T2NeAAry[2]<4||T1T2NeAAry[2]>3000)
		{
			*CheckTablePt	= 1000;
			T1T2NeAAry[2]	= 1000;
		}
		CheckTablePt++;			//= (Uint16 *)0x802C;   //A1?NE
		T1T2NeAAry[3] = *CheckTablePt;         //??
		if(T1T2NeAAry[3]<4||T1T2NeAAry[3]>3000)
		{
			*CheckTablePt	= 1000;
			T1T2NeAAry[3]	= 1000;
		}
		CheckTablePt++;			//= (Uint16 *)0x802D;   //A4?NE
		T1T2NeAAry[4] = *CheckTablePt;         //??
		if(T1T2NeAAry[4]<4||T1T2NeAAry[4]>3000)
		{
			*CheckTablePt	= 512;
			T1T2NeAAry[4]	= 512;
		}
		CheckTablePt++;			//= (Uint16 *)0x802E;   //A4?NE
		T1T2NeAAry[5] = *CheckTablePt;         //??
		if(T1T2NeAAry[5]<4||T1T2NeAAry[5]>3000)
		{
			*CheckTablePt	= 256;
			T1T2NeAAry[5]	= 256;
		}
		CheckTablePt++;			//= (Uint16 *)0x802F;   //A4?NE
		T1T2NeAAry[6] = *CheckTablePt;         //??
		if(T1T2NeAAry[6]<4||T1T2NeAAry[6]>3000)
		{
			*CheckTablePt	= 128;
			T1T2NeAAry[6]	= 128;
		}
		CheckTablePt++;			//= (Uint16 *)0x8030;   //A4?NE
		T1T2NeAAry[7] = *CheckTablePt;         //??
		if(T1T2NeAAry[7]<4||T1T2NeAAry[7]>3000)
		{
			*CheckTablePt	= 64;
			T1T2NeAAry[7]	= 64;
		}
		CheckTablePt++;			//= (Uint16 *)0x8031;   //A4?NE
		T1T2NeAAry[8] = *CheckTablePt;         //??
		if(T1T2NeAAry[8]<4||T1T2NeAAry[8]>300)
		{
			*CheckTablePt	= 32;
			T1T2NeAAry[8]	= 32;
		}
		CheckTablePt++;			//= (Uint16 *)0x8032;   //A4?NE
		T1T2NeAAry[9] = *CheckTablePt;         //??
		if(T1T2NeAAry[9]<4||T1T2NeAAry[9]>300)
		{
			*CheckTablePt	= 16;
			T1T2NeAAry[9]	= 16;
		}
		CheckTablePt++;			//= (Uint16 *)0x8033;   //A4?NE
		T1T2NReptAAry[1] = *CheckTablePt;         //??
		if(T1T2NReptAAry[1]<1||T1T2NReptAAry[1]>150)
		{
			*CheckTablePt	= 1;
			T1T2NReptAAry[1]= 1;
		}
		CheckTablePt++;			//= (Uint16 *)0x8034;   //A2?NREPT
		T1T2NReptAAry[2] = *CheckTablePt;         //??
		if(T1T2NReptAAry[2]<1||T1T2NReptAAry[2]>150)
		{
			*CheckTablePt	= 1;
			T1T2NReptAAry[2]= 1;
		}
		CheckTablePt++;			//= (Uint16 *)0x8035;   //A2?NREPT
		T1T2NReptAAry[3] = *CheckTablePt;         //??
		if(T1T2NReptAAry[3]<1||T1T2NReptAAry[3]>150)
		{
			*CheckTablePt	= 1;
			T1T2NReptAAry[3]= 1;
		}
		CheckTablePt++;			//= (Uint16 *)0x8036;   //A4?NREPT
		T1T2NReptAAry[4] = *CheckTablePt;         //??
		if(T1T2NReptAAry[4]<1||T1T2NReptAAry[4]>150)
		{
			*CheckTablePt	= 2;
			T1T2NReptAAry[4]= 2;
		}
		CheckTablePt++;			//= (Uint16 *)0x8037;   //A4?NREPT
		T1T2NReptAAry[5] = *CheckTablePt;         //??
		if(T1T2NReptAAry[5]<1||T1T2NReptAAry[5]>150)
		{
			*CheckTablePt	= 2;
			T1T2NReptAAry[5]= 2;
		}
		CheckTablePt++;			//= (Uint16 *)0x8038;   //A4?NREPT
		T1T2NReptAAry[6] = *CheckTablePt;         //??
		if(T1T2NReptAAry[6]<1||T1T2NReptAAry[6]>150)
		{
			*CheckTablePt	= 4;
			T1T2NReptAAry[6]= 4;
		}
		CheckTablePt++;			//= (Uint16 *)0x8039;   //A4?NREPT
		T1T2NReptAAry[7] = *CheckTablePt;         //??
		if(T1T2NReptAAry[7]<1||T1T2NReptAAry[7]>150)
		{
			*CheckTablePt	= 4;
			T1T2NReptAAry[7]= 4;
		}
		CheckTablePt++;			//= (Uint16 *)0x803A;   //A4?NREPT
		T1T2NReptAAry[8] = *CheckTablePt;         //??
		if(T1T2NReptAAry[8]<5||T1T2NReptAAry[8]>150)
		{
			*CheckTablePt	= 8;
			T1T2NReptAAry[8]= 8;
		}
		CheckTablePt++;			//= (Uint16 *)0x803B;   //A4?NREPT
		T1T2NReptAAry[9] = *CheckTablePt;         //??
		if(T1T2NReptAAry[9]<10||T1T2NReptAAry[9]>150)
		{
			*CheckTablePt	= 16;
			T1T2NReptAAry[9]= 16;
		}
		CheckTablePt++;			//= (Uint16 *)0x803C;   //A4?NREPT
		T1T2CPMGTe = *CheckTablePt;         //??
		if(T1T2CPMGTe<4||T1T2CPMGTe>200)
		{
			*CheckTablePt	= 5;
			T1T2CPMGTe		= 5;
		}
		CheckTablePt++;			//= (Uint16 *)0x803D;   //A4?NREPT
		T1T2CBWTe = *CheckTablePt;         //??
		if(T1T2CBWTe<4||T1T2CBWTe>200)
		{
			*CheckTablePt	= 5;
			T1T2CBWTe		= 5;
		}
	}
//single\double frequency T1T2D mode parameters
	else if(WorkMode==0x0060)
	{
		T12DFreqSel	= *(Uint16 *)0x800A;	//read frequency selected code
		if (T12DFreqSel<1||T12DFreqSel>8)
		{
			T12DFreqSel		= 8;	//read frequency selected code
			*(Uint16 *)0x800A	= 8;
		}
		*(Uint16 *)0x800B	= 0;

		CheckTablePt= (Uint16 *)0x8021;   //CPMG?TW(A1)//= (Uint16 *)0x8021;
		T12DCPMGTw1AB	= *CheckTablePt;         //??
		if(T12DCPMGTw1AB<1000||T12DCPMGTw1AB>30000)
		{
			*CheckTablePt	= 9800;
			T12DCPMGTw1AB	= 9800;
		}
		CheckTablePt++;			//= (Uint16 *)0x8022;   //CPMG?TW(A2)
		T12DCPMGTw2AB	= *CheckTablePt;         //??
		if(T12DCPMGTw2AB<1000||T12DCPMGTw2AB>30000)
		{
			*CheckTablePt	= 2400;
			T12DCPMGTw2AB	= 2400;
		}
		CheckTablePt++;			//= (Uint16 *)0x8023;   //CPMG?TW(A8)
		T12DCPMGTw8AB	= *CheckTablePt;         //??
		if(T12DCPMGTw8AB<100||T12DCPMGTw8AB>30000)
		{
			*CheckTablePt	= 800;
			T12DCPMGTw8AB	= 800;
		}
		CheckTablePt++;			//= (Uint16 *)0x8024;   //CPMG?TW(A9)
		T12DCPMGTw9AB	= *CheckTablePt;         //??
		if(T12DCPMGTw9AB<12||T12DCPMGTw9AB>30000)
		{
			*CheckTablePt	= 100;
			T12DCPMGTw9AB	= 100;
		}
		CheckTablePt++;			//= (Uint16 *)0x8025;   //CPMG?TW(A10)
		T12DCPMGTw0AB	= *CheckTablePt;         //??
		if(T12DCPMGTw0AB<10||T12DCPMGTw0AB>30000)
		{
			*CheckTablePt	= 32;
			T12DCPMGTw0AB	= 32;
		}
		CheckTablePt++;			//= (Uint16 *)0x8026;   //DE?TW
		T12DDETwAB	= *CheckTablePt;         //??
		if(T12DDETwAB<100||T12DDETwAB>30000)
		{
			*CheckTablePt	= 1200;
			T12DDETwAB		= 1200;
		}
		CheckTablePt++;			//= (Uint16 *)0x8027;   //CBW?TW
		T12DCBWTwAB	= *CheckTablePt;         //??
		if(T12DCBWTwAB<10||T12DCBWTwAB>500)
		{
			*CheckTablePt	= 20;
			T12DCBWTwAB		= 20;
		}
		CheckTablePt++;			//= (Uint16 *)0x8028;   //TES
		T12DCBWTeAB	= *CheckTablePt;         //??
		if(T12DCBWTeAB<4||T12DCBWTeAB>100)
		{
			*CheckTablePt	= 5;
			T12DCBWTeAB		= 5;
		}
		CheckTablePt++;			//= (Uint16 *)0x8029;   //TES
		T12DTesAB	= *CheckTablePt;         //??
		if(T12DTesAB<4||T12DTesAB>200)
		{
			*CheckTablePt	= 5;
			T12DTesAB		= 5;
		}
		CheckTablePt++;			//= (Uint16 *)0x802A;   //TEL1
		T12DTelABAry[0]	= *CheckTablePt;         //??
		if(T12DTelABAry[0]<4||T12DTelABAry[0]>500)
		{
			*CheckTablePt	= 20;
			T12DTelABAry[0]	= 20;
		}
		CheckTablePt++;			//= (Uint16 *)0x802B;   //TEL1
		T12DTelABAry[1]	= *CheckTablePt;         //??
		if(T12DTelABAry[1]<4||T12DTelABAry[1]>500)
		{
			*CheckTablePt	= 30;
			T12DTelABAry[1]	= 30;
		}
		CheckTablePt++;			//= (Uint16 *)0x802C;   //TEL1
		T12DTelABAry[2]	= *CheckTablePt;         //??
		if(T12DTelABAry[2]<4||T12DTelABAry[2]>500)
		{
			*CheckTablePt	= 50;
			T12DTelABAry[2]	= 50;
		}
		CheckTablePt++;			//= (Uint16 *)0x802D;   //TEL1
		T12DTelABAry[3]	= *CheckTablePt;         //??
		if(T12DTelABAry[3]<4||T12DTelABAry[3]>500)
		{
			*CheckTablePt	= 80;
			T12DTelABAry[3]	= 80;
		}
		CheckTablePt++;			//= (Uint16 *)0x802E;   //TEL1
		T12DTelABAry[4]	= *CheckTablePt;         //??
		if(T12DTelABAry[4]<4||T12DTelABAry[4]>500)
		{
			*CheckTablePt	= 120;
			T12DTelABAry[4]	= 120;
		}
		CheckTablePt++;			//= (Uint16 *)0x802F;   //A8A9A10?????
		T12DNRept890AB	= *CheckTablePt;         //??
		if(T12DNRept890AB<1||T12DNRept890AB>100)
		{
			*CheckTablePt	= 2;
			T12DNRept890AB	= 2;
		}
		CheckTablePt++;			//= (Uint16 *)0x8030;   //A8A9A10?????
		T12DCBWNReptAB	= *CheckTablePt;         //??
		if(T12DCBWNReptAB<1||T12DCBWNReptAB>150)
		{
			*CheckTablePt	= 24;
			T12DCBWNReptAB	= 24;
		}
		CheckTablePt++;			//= (Uint16 *)0x8031;   //CPMG?NE(A1)
		T12DCPMGNe1AB	= *CheckTablePt;         //??
		if(T12DCPMGNe1AB<4||T12DCPMGNe1AB>3000)
		{
			*CheckTablePt	= 1002;
			T12DCPMGNe1AB	= 1002;
		}
		CheckTablePt++;			//= (Uint16 *)0x8032;   //CPMG?NE(A2)
		T12DCPMGNe2AB	= *CheckTablePt;         //??
		if(T12DCPMGNe2AB<4||T12DCPMGNe2AB>3000)
		{
			*CheckTablePt	= 802;
			T12DCPMGNe2AB	= 802;
		}
		CheckTablePt++;			//= (Uint16 *)0x8033;   //CPMG?NE(A8)
		T12DCPMGNe8AB	= *CheckTablePt;         //??
		if(T12DCPMGNe8AB<4||T12DCPMGNe8AB>3000)
		{
			*CheckTablePt	= 700;
			T12DCPMGNe8AB	= 700;
		}
		CheckTablePt++;			//= (Uint16 *)0x8034;   //CPMG?NE(A9)
		T12DCPMGNe9AB	= *CheckTablePt;         //??
		if(T12DCPMGNe9AB<4||T12DCPMGNe9AB>3000)
		{
			*CheckTablePt	= 192;
			T12DCPMGNe9AB	= 192;
		}
		CheckTablePt++;			//= (Uint16 *)0x8035;   //CPMG?NE(A10)
		T12DCPMGNe0AB	= *CheckTablePt;         //??
		if(T12DCPMGNe0AB<4||T12DCPMGNe0AB>3000)
		{
			*CheckTablePt	= 64;
			T12DCPMGNe0AB	= 64;
		}
		CheckTablePt++;			//= (Uint16 *)0x8036;   //DE?NE
		T12DDENeAB	= *CheckTablePt;         //??
		if(T12DDENeAB<4||T12DDENeAB>3000)
		{
			*CheckTablePt	= 802;
			T12DDENeAB		= 802;
		}
		CheckTablePt++;			//= (Uint16 *)0x8037;   //CBW?NE
		T12DCBWNeAB	= *CheckTablePt;         //??
		if(T12DCBWNeAB<4||T12DCBWNeAB>300)
		{
			*CheckTablePt	= 25;
			T12DCBWNeAB		= 25;
		}
		CheckTablePt++;			//= (Uint16 *)0x8038;   //DE?????
		T12DDEmnAB	= *CheckTablePt;         //??
		if(T12DDEmnAB<1||T12DDEmnAB>6)
		{
			*CheckTablePt	= 5;
			T12DDEmnAB		= 5;
		}
		CheckTablePt++;			//= (Uint16 *)0x8039;   //DE????????
		T12DDEmAB	= *CheckTablePt;         //??
		if(T12DDEmAB<1||T12DDEmAB>8)
		{
			*CheckTablePt	= 2;
			T12DDEmAB		= 2;
		}
	}
	else if (WorkMode == 0x0070)
	{
		DFT1T2DFreqSel = *(Uint16 *)0x800A;
		DFT1T2DFreqSelAry[1] = (DFT1T2DFreqSel & 0x00F0) >> 4; // A频
		DFT1T2DFreqSelAry[2] = DFT1T2DFreqSel & 0x000F;
		if (DFT1T2DFreqSel > 0x00FF || DFT1T2DFreqSelAry[1] < 1 || DFT1T2DFreqSelAry[1] > 8 || DFT1T2DFreqSelAry[2] < 1 || DFT1T2DFreqSelAry[2] > 8)
		{
			DFT1T2DFreqSelAry[1] = 8;
			DFT1T2DFreqSelAry[2] = 5;
			(*(Uint16 *)0x800A) = 0x0085;
		}
		*(Uint16 *)0x800B = 0;

		CheckTablePt = (Uint16 *)0x8021;
		DFT1T2D_TW_A1B1	= *CheckTablePt;         //??
		if(DFT1T2D_TW_A1B1<1000||DFT1T2D_TW_A1B1>30000)
		{
			*CheckTablePt	= 10200;
			DFT1T2D_TW_A1B1	= 10200;
		}
		CheckTablePt++;
		DFT1T2D_TW_A2B2 = *CheckTablePt;
		if (DFT1T2D_TW_A2B2 < 1 || DFT1T2D_TW_A2B2 > 5000)
		{
			*CheckTablePt = 2624;
			DFT1T2D_TW_A2B2 = 2624;
		}
		CheckTablePt++;
		DFT1T2D_TW_A8B8 = *CheckTablePt;
		if (DFT1T2D_TW_A8B8 < 1 || DFT1T2D_TW_A8B8 > 1500)
		{
			*CheckTablePt = 825;
			DFT1T2D_TW_A8B8 = 825;
		}
		CheckTablePt++;
		DFT1T2D_TW_A9B9 = *CheckTablePt;
		if (DFT1T2D_TW_A9B9 < 1 || DFT1T2D_TW_A9B9 > 500)
		{
			*CheckTablePt = 99;
			DFT1T2D_TW_A9B9 = 99;
		}
		CheckTablePt++;
		DFT1T2D_TW_A10B10 = *CheckTablePt;
		if (DFT1T2D_TW_A10B10 < 1 || DFT1T2D_TW_A10B10 > 100)
		{
			*CheckTablePt = 40;
			DFT1T2D_TW_A10B10 = 40;
		}
		CheckTablePt++;
		DFT1T2D_TW_DE = *CheckTablePt;
		if (DFT1T2D_TW_DE < 1 || DFT1T2D_TW_DE > 3000)
		{
			*CheckTablePt = 1121;
			DFT1T2D_TW_DE = 1121;
		}
		CheckTablePt++;
		DFT1T2D_TW_CBW = *CheckTablePt;
		if (DFT1T2D_TW_CBW < 1 || DFT1T2D_TW_CBW > 100)
		{
			*CheckTablePt = 20;
			DFT1T2D_TW_CBW = 20;
		}
		CheckTablePt++;
		DFT1T2D_TE_CBW = *CheckTablePt;
		if (DFT1T2D_TE_CBW < 4 || DFT1T2D_TE_CBW > 10)
		{
			*(CheckTablePt) = 5;
			DFT1T2D_TE_CBW = 5;
		}
		CheckTablePt++;
		DFT1T2D_TES_DE_T2_T1 = *CheckTablePt;
		if (DFT1T2D_TES_DE_T2_T1 < 4 || DFT1T2D_TES_DE_T2_T1 > 10)
		{
			*CheckTablePt = 5;
			DFT1T2D_TES_DE_T2_T1 = 5;
		}
		CheckTablePt++;
		DFT1T2D_TEL1_DE = *CheckTablePt;
		if (DFT1T2D_TEL1_DE < 4 || DFT1T2D_TEL1_DE > 100)
		{
			*CheckTablePt = 20;
			DFT1T2D_TEL1_DE = 20;
		}
		CheckTablePt++;
		DFT1T2D_TEL2_DE = *CheckTablePt;
		if (DFT1T2D_TEL2_DE < 4 || DFT1T2D_TEL2_DE > 100)
		{
			*CheckTablePt = 30;
			DFT1T2D_TEL2_DE = 30;
		}
		CheckTablePt++;
		DFT1T2D_TEL3_DE = *CheckTablePt;
		if (DFT1T2D_TEL3_DE < 4 || DFT1T2D_TEL3_DE > 100)
		{
			*CheckTablePt = 50;
			DFT1T2D_TEL3_DE = 50;
		}
		CheckTablePt++;
		DFT1T2D_TEL4_DE = *CheckTablePt;
		if (DFT1T2D_TEL4_DE < 4 || DFT1T2D_TEL4_DE > 100)
		{
			*CheckTablePt = 80;
			DFT1T2D_TEL4_DE = 80;
		}
		CheckTablePt++;
		DFT1T2D_TEL5_DE = *CheckTablePt;
		if (DFT1T2D_TEL5_DE < 4 || DFT1T2D_TEL5_DE > 200)
		{
			*CheckTablePt = 120;
			DFT1T2D_TEL5_DE = 120;
		}
		CheckTablePt++;
		DFT1T2D_NREPT_CBW = *CheckTablePt;
		if (DFT1T2D_NREPT_CBW < 1 || DFT1T2D_NREPT_CBW > 100)
		{
			*CheckTablePt = 24;
			DFT1T2D_NREPT_CBW = 24;
		}
		CheckTablePt++;
		DFT1T2D_NE_A1B1 = *CheckTablePt;
		if (DFT1T2D_NE_A1B1 < 1 || DFT1T2D_NE_A1B1 > 2000)
		{
			*CheckTablePt = 1002;
			DFT1T2D_NE_A1B1 = 1002;
		}
		CheckTablePt++;
		DFT1T2D_NE_A2B2 = *CheckTablePt;
		if (DFT1T2D_NE_A2B2 < 1 || DFT1T2D_NE_A2B2 > 1000)
		{
			*CheckTablePt = 752;
			DFT1T2D_NE_A2B2 = 752;
		}
		CheckTablePt++;
		DFT1T2D_NE_A8B8 = *CheckTablePt;
		if (DFT1T2D_NE_A8B8 < 1 || DFT1T2D_NE_A8B8 > 1000)
		{
			*CheckTablePt = 650;
			DFT1T2D_NE_A8B8 = 650;
		}
		CheckTablePt++;
		DFT1T2D_NE_A9B9 = *CheckTablePt;
		if (DFT1T2D_NE_A9B9 < 1 || DFT1T2D_NE_A9B9 > 500)
		{
			*CheckTablePt = 176;
			DFT1T2D_NE_A9B9 = 176;
		}
		CheckTablePt++;
		DFT1T2D_NE_A10B10 = *CheckTablePt;
		if (DFT1T2D_NE_A10B10 < 1 || DFT1T2D_NE_A10B10 > 100)
		{
			*CheckTablePt = 64;
			DFT1T2D_NE_A10B10 = 64;
		}
		CheckTablePt++;
		DFT1T2D_NE_DE = *CheckTablePt;
		if (DFT1T2D_NE_DE < 1 || DFT1T2D_NE_DE > 1000)
		{
			*CheckTablePt = 752;
			DFT1T2D_NE_DE = 752;
		}
		CheckTablePt++;
		DFT1T2D_NE_CBW = *CheckTablePt;
		if (DFT1T2D_NE_CBW < 1 || DFT1T2D_NE_CBW > 100)
		{
			*CheckTablePt = 25;
			DFT1T2D_NE_CBW = 25;
		}
		CheckTablePt++;
		DFT1T2D_group_DE = *CheckTablePt;
		if (DFT1T2D_group_DE < 1 || DFT1T2D_group_DE > 100)
		{
			*CheckTablePt = 5;
			DFT1T2D_group_DE = 5;
		}
		CheckTablePt++;
		DFT1T2D_DE_TEL_num = *CheckTablePt;
		if (DFT1T2D_DE_TEL_num < 1 || DFT1T2D_DE_TEL_num > 10)
		{
			*CheckTablePt = 2;
			DFT1T2D_DE_TEL_num = 2;
		}
	}

	else if((WorkMode==0x000A)||(WorkMode==0x000B)||(WorkMode==0x000C))// WorkMode==0x000A||WorkMode==0x000B|||WorkMode==0x000C
	{
		*(Uint16 *)0x800A	= 0x4321;
		*(Uint16 *)0x800B	= 0x8765;
	}

	return;
}

void DownloadTable(Uint16 DownDataBuf)
{
	if(DownDataBuf==0x9931 && DownTableFlag==CLEAR)        //表明为下载数据命令
	{
		DownTableFlag	= SET;   
		/*
		SaveTablePt		= (Uint16 *)0x8042;                
		for (ZeroCnt=0;ZeroCnt<14;ZeroCnt++)
		{
			*SaveTablePt= 0;
			SaveTablePt	++;
		}
		*/
		*(Uint16 *)0x8000 = 0x9931;
		SaveTablePt		= (Uint16 *)0x8001;   //指针初始化
	}  
	else if(DownDataBuf!=0xAA55 && DownTableFlag==SET)  //表明为下载数据
	{
		*SaveTablePt	= DownDataBuf;        //读取数据到表中
		SaveTablePt++;                //指针指向下一个位置
	}  
	else if(DownDataBuf==0xAA55 && DownTableFlag==SET)   //表明为下载数据结束命令
	{
		                        //下载标志位清除
		while(McbspaRegs.SPCR2.bit.XRDY==0)         //如果不能发送，等待
		{ ; }
		McbspaRegs.DXR1.all=0x9931;     //回复
		DownTableFlag	= 0;
	}
  return;
}

