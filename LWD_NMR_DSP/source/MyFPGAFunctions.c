//###########################################################################
//
// FILE:   MyFPGAFunctions.c
//
// TITLE:  interface functions with FPGA 
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

#include "MyHeaderFiles.h"
#include "DSP281x_Device.h" 

#pragma CODE_SECTION(LoadDDSPara, "secureRamFuncs");
#pragma CODE_SECTION(LoadBriDumpPara, "secureRamFuncs");
#pragma CODE_SECTION(LoadPdPara, "secureRamFuncs");
#pragma CODE_SECTION(StartS1msModule, "secureRamFuncs");

void ShutdownHV(void)
{
    // K1闭合，K2断开
    K1_EN = USER_ENABLE;   // K1输出高
    K2_DIS = USER_DISABLE;  // K2输出低
    HVState = HV_OFF;
	return;
}

void RstNoiseModule(void)
{
    NOISE_START_DIS	= USER_DISABLE;
    NOISE_RST_EN	= USER_ENABLE; 
    NOISE_RST_DIS	= USER_DISABLE;    

	NRAM_RST_EN		= USER_ENABLE;
    NRAM_RST_DIS	= USER_DISABLE;
    NRAM_RD_DIS		= USER_DISABLE;
	return;
}

void RstPulseModule(void)
{	    
    PLUSE_START_DIS	= USER_DISABLE;
    PLUSE_RST_EN	= USER_ENABLE;
    PLUSE_RST_DIS	= USER_DISABLE; 
    
	NRAM_RST_EN		= USER_ENABLE;
    NRAM_RST_DIS	= USER_DISABLE;
    NRAM_RD_DIS		= USER_DISABLE;   
	return;
}

void LoadDDSPara(void)
{
//	DDSFreq		= *(Uint16 *)DDS_FREQ_ADDR;
//	DDSFreq		*=(Uint32)SiglAcqFreqTim*4;
//	DDSMid1		= DDSFreq<<15;             //1Khz对应频率字的整数部分
//	DDSMid2		= DDSFreq<<13;
//	DDSMid3		= DDSFreq<<10;
//	DDSMid4		= DDSFreq<<9;
//	DDSMid5		= DDSFreq<<8;
//	DDSRefItg	= 197.0;
//	DDSRefDcm	= 0.67296;         //1Khz对应频率字的小数部分
//	DDSMid6		= (Uint32)(DDSFreq*DDSRefItg);
//	DDSMid7		= (Uint32)(DDSFreq*DDSRefDcm);
//	DDSCfgWords	= DDSMid1+DDSMid2+DDSMid3+DDSMid4+DDSMid5+DDSMid6+DDSMid7;
//	DDSCfgHi	= DDSCfgWords/65536;
//	DDSCfgLow	= DDSCfgWords%65536;

    Uint16 DDSData = *(Uint16 *)DDS_FREQ_ADDR;
    DDSFreq = DDSData / 10 * SiglAcqFreqTim * 4;            // 这里有点别扭，DDSFreq还要供外部变量使用
    float _DDSFreq = DDSData * SiglAcqFreqTim * 400.0;    // 0.1kHz 变换为 Hz，32倍频，__DDSFreq临时使用
    #define DDS_COE 42.94967296f
    Uint32 DDSCfgWord = (Uint32)(_DDSFreq * DDS_COE);
    DDSCfgLow = DDSCfgWord & 0xFFFF;
    DDSCfgHi = (DDSCfgWord >> 16) & 0xFFFF;

   	DDS_DATACHOICE_DIS	= USER_DISABLE;
	DDS_CONFDATA		= DDSCfgLow;   //装载dds频率字低位
	DDS_DATALOAD_EN		= USER_ENABLE;
	DDS_DATALOAD_DIS	= USER_DISABLE;

	DDS_DATACHOICE_EN	= USER_ENABLE;
	DDS_CONFDATA		= DDSCfgHi;   //装载dds频率字高位
	DDS_DATALOAD_EN		= USER_ENABLE;
	DDS_DATALOAD_DIS	= USER_DISABLE;
	return;
}

void LoadBriDumpPara(void)
{
	DumpPara1	= WAIT_DUMP_TIME;
	DumpPara2	= WAIT_DUMP_TIME + SHORT_DUMP_TIME;
	DumpPara3	= WAIT_DUMP_TIME + SHORT_DUMP_TIME + WAIT_DUMP_TIME;
	DumpPara4	= WAIT_DUMP_TIME + SHORT_DUMP_TIME + WAIT_DUMP_TIME + SHORT_DUMP_TIME;
	DumpPara5	= WAIT_DUMP_TIME + SHORT_DUMP_TIME + WAIT_DUMP_TIME + SHORT_DUMP_TIME + WAIT_DUMP_TIME;
	DumpPara6	= SHORT_DUMP_TIME *2 + WAIT_DUMP_TIME * 3 + LONG_DUMP_TIME;  
	MainDumpTime= DumpPara6 + 100;  
     
	if(SiglAcqFreqTim%2==0)
	{
		ScaleDDSDiv	= SiglAcqFreqTim/2 + SiglAcqFreqTim*4;
	}
	else if(SiglAcqFreqTim%2==1)
	{
		ScaleDDSDiv = (SiglAcqFreqTim-1)/2 + (SiglAcqFreqTim+1)*4;
	}
   
	HalfFreqNum = SHAKE_NUM * 8;

	if(((OUT_BRI_WIDTH-IN_BRI_WIDTH)/2)%2==1)
	{
		BriMid = (OUT_BRI_WIDTH-IN_BRI_WIDTH-10)/2;
	}
	else
	{
		BriMid = (OUT_BRI_WIDTH-IN_BRI_WIDTH)/2;
	}  
	BriWidthData = BriMid/10 + (BriMid+IN_BRI_WIDTH)/10*16 + OUT_BRI_WIDTH/10*1024; 
      
	DUMP_CHOICE		= 0x0;
	DUMP_DATA		= DumpPara1; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
    
	DUMP_CHOICE		= 0x1;
	DUMP_DATA		= DumpPara2; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
     
	DUMP_CHOICE		= 0x2;
	DUMP_DATA		= DumpPara3; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
   
	DUMP_CHOICE 	= 0x3;
	DUMP_DATA		= DumpPara4; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
    
	DUMP_CHOICE		= 0x4;
	DUMP_DATA		= DumpPara5; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
     
	DUMP_CHOICE		= 0x5;
	DUMP_DATA		= DumpPara6; 
	DUMP_LOAD_EN	= USER_ENABLE;
	DUMP_LOAD_DIS	= USER_DISABLE;
      
   //内外桥相关参数
	BRIDGE_DATA		= BriWidthData; 
	BRIDGE_LOAD_EN	= USER_ENABLE;
	BRIDGE_LOAD_DIS	= USER_DISABLE;
   
	HALF_DATA		= HalfFreqNum;
	BRIDGE_LOAD_EN	= USER_ENABLE;
	BRIDGE_LOAD_DIS	= USER_DISABLE;
   
	SCALE_DDSDIV	= ScaleDDSDiv; 
	BRIDGE_LOAD_EN	= USER_ENABLE;
	BRIDGE_LOAD_DIS	= USER_DISABLE;
	return;
}

void LoadPdPara(void)
{
	//DDSFreq	= *(Uint16 *)DDS_FREQ_ADDR;
	//DDSFreq	*=(Uint32)SiglAcqFreqTim*4;
	if (PulseAcqFlag==SET)
	{
		PdPara1 = (Uint16)(((P_PLUSE_T4-P_PLUSE_T3)*DDSFreq)/100000);
		PdPara2 = (Uint16)(((P_PLUSE_T4-P_PLUSE_T3+Pd90Time)*DDSFreq)/100000);
	}
	else
	{
		PdPara1 = (Uint16)(((P_PLUSE_T2-P_PLUSE_T1)*DDSFreq)/100000);
		PdPara2 = (Uint16)(((P_PLUSE_T2-P_PLUSE_T1+Pd90Time)*DDSFreq)/100000);		
		PdPara3	= (Uint16)(((P_PLUSE_T2-P_PLUSE_T1+Pd180Time)*DDSFreq)/100000);
    }
	PD_PLUSE_CHOICE	=0x1;
	PD_PLUSE_DATA	=PdPara1;
	PD_PLUSE_LOAD_EN=USER_ENABLE;
	PD_PLUSE_LOAD_DIS=USER_DISABLE;

	PD_PLUSE_CHOICE	=0x2;
	PD_PLUSE_DATA	=PdPara2;
	PD_PLUSE_LOAD_EN=USER_ENABLE;
	PD_PLUSE_LOAD_DIS=USER_DISABLE;

	if (PulseAcqFlag==CLEAR)
	{
		PD_PLUSE_CHOICE	=0x3;
		PD_PLUSE_DATA	=PdPara3;
		PD_PLUSE_LOAD_EN=USER_ENABLE;
		PD_PLUSE_LOAD_DIS=USER_DISABLE;
	}
	return;
}

// FPGA中实现了1ms的定时器，由5M时钟分频而来
void StartS1msModule(Uint16 TimeData)
{
    STATE1MS_RST_EN		= USER_ENABLE;     
    STATE1MS_RST_DIS	= USER_ENABLE;

	STATE1MS_START_EN	= USER_ENABLE;//1MS启动
	TIMER_DATA			= TimeData;   //for test
	TIMER_START			= 0x1;	
	do	
	{;} while(!GpioDataRegs.GPADAT.bit.GPIOA9);
	     
	TIMER_STOP			= 0x2;         //等待定时中断
	STATE1MS_START_DIS	= USER_DISABLE; //1MS禁止启动
	return;
}

