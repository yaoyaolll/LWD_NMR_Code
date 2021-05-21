/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(InitAll,"Datatable");
#pragma CODE_SECTION(InitTable,"Datatable");
#pragma CODE_SECTION(InitPulseGain,"Datatable");
#pragma CODE_SECTION(InitGpio,"Datatable");
#pragma CODE_SECTION(InitFPGA,"Datatable");
#pragma CODE_SECTION(InitVariables,"Datatable");
#pragma CODE_SECTION(InitInterruptMcbsp,"Datatable");
#pragma CODE_SECTION(LoadParaDis,"Datatable");

void InitAll(void)
{ 
	//System initial 
    InitSysCtrl(); //CPU初始化
                    
	//Initial GPIO and FPGA chip
    InitGpio();//复位GPIO
	InitFPGA(); //复位FPGA

	//Initial PIE module	
    DINT;                           
    IER &= 0x0000;            
    IFR &= 0x0000;
    InitPieCtrl();            
    InitPieVectTable(); 

	DINT;                                  //关中断
	IER = 0x0000;                          //禁止所有的中断
	IFR = 0x0000;
                                                    
	EALLOW;                                //保护寄存器 
	PieVectTable.XINT1 = &XINT1_STOP;      //外部中断1入口地址
	PieVectTable.XINT2 = &XINT2_DCStorData;      //外部中断2入口地址
	EDIS;                                  // 释放保护的寄存器  
	         
	IER |= M_INT1;                        
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;
	XIntruptRegs.XINT1CR.all =0x5;         //打开管脚xint1外中断,设置上升沿中断
	XIntruptRegs.XINT2CR.all =0x5;         //打开管脚xint2外中断,设置上升沿中断
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;    //清除PIE分组1的中断响应位
	EINT;                                  // Enable Global interrupt INTM       
            
	//Initial MCBSP module    
    InitMcbsp();               
	//McBSP interrupt initialization
	InitInterruptMcbsp(); 
	   
    InitPulseGain(); //初始化激励衰减倍数表
    ShutdownHV();//储能短接断开
	LoadParaDis();
    STATE1MS_RST_EN		= USER_ENABLE;     
    STATE1MS_RST_DIS	= USER_ENABLE; 
	STATE1MS_START_DIS	= USER_DISABLE;
    //Load State 1ms Parameters 
	PulseCycle	= 100;
    PulseTime	= 1000;
    MDumpTime	= 1800;
    SDumpTime	= 3000;
    CutTime		= 94000;
    CutTimeLow  = CutTime&0x0000ffff;
    CutTimeHi	= (CutTime&0xffff0000)>>16;
    
    STATE1MS_CHOICE 	= 0;
    STATE1MS_DATA 		= (Uint16)PulseCycle;    
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;

    STATE1MS_CHOICE 	= 1;
    STATE1MS_DATA 		= (Uint16)PulseTime;
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;
    
    STATE1MS_CHOICE		= 2;
    STATE1MS_DATA		= (Uint16)MDumpTime;
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;
    
    STATE1MS_CHOICE		= 3;
    STATE1MS_DATA		= (Uint16)SDumpTime;
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;
    
    STATE1MS_CHOICE		= 4;
    STATE1MS_DATA		= CutTimeLow;
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;

    STATE1MS_CHOICE		= 5;
    STATE1MS_DATA		= CutTimeHi;
    STATE1MS_LOAD_EN 	= USER_ENABLE;
    STATE1MS_LOAD_DIS 	= USER_DISABLE;    

    TIMER_STOP = 0x2;

	//Reset Scan Module
    SCAN_START_DIS	= USER_DISABLE;
    SCAN_RST_EN		= USER_ENABLE;  
    SCAN_RST_DIS	= USER_DISABLE; 
	RstPulseModule();
	RstNoiseModule();
	//Reset Scale Module
    SCALE_START_DIS	= USER_DISABLE;
    SCALE_RST_EN	= USER_ENABLE;
    SCALE_RST_DIS	= USER_DISABLE; 
	//Variables initialization   
	InitVariables();
	//Parameter-table initialization    
    InitTable(); //初始化参数表
    return;        
}

void InitTable(void)             
{  
	TableTempPt = (Uint16 *)0x8001;   
	*TableTempPt++= 9;			//Addr: 0x8001; Func: Work mode; Unit: N
	*TableTempPt++= 585;			//Addr: 0x8002; Func: the first operating frequency; Unit: kHz
	*TableTempPt++= 625;			//Addr: 0x8003; Func: the second operating frequency; Unit: kHz
	*TableTempPt++= 666;			//Addr: 0x8004; Func: the third operating frequency; Unit: kHz
	*TableTempPt++= 726;			//Addr: 0x8005; Func: the fourth operating frequency; Unit: kHz
	*TableTempPt++= 775;			//Addr: 0x8006; Func: the fifth operating frequency; Unit: kHz
	*TableTempPt++= 820;			//Addr: 0x8007; Func: the sixth operating frequency; Unit: kHz
	*TableTempPt++= 865;			//Addr: 0x8008; Func: the seventh operating frequency; Unit: kHz
	*TableTempPt++= 963;			//Addr: 0x8009; Func: the eighth operating frequency; Unit: kHz
  
	*TableTempPt++= 0x0007;		///Addr: 0x800A; Func: operating frequency selection high word
	*TableTempPt++= 0x0000;		///Addr: 0x800B; Func: operating frequency selection low word
    
	*TableTempPt++= 54;			//Addr: 0x800C; Func: 90 degree pulse width of the first frequency; Unit: us
	*TableTempPt++= 52;			//Addr: 0x800D; Func: 90 degree pulse width of the second frequency; Unit: us
	*TableTempPt++= 49;			//Addr: 0x800E; Func: 90 degree pulse width of the third frequency; Unit: us
	*TableTempPt++= 46;			//Addr: 0x800F; Func: 90 degree pulse width of the fourth frequency; Unit: us
	*TableTempPt++= 43;			//Addr: 0x8010; Func: 90 degree pulse width of the fifth frequency; Unit: us
	*TableTempPt++= 40;			//Addr: 0x8011; Func: 90 degree pulse width of the sixth frequency; Unit: us
	*TableTempPt++= 37;			//Addr: 0x8012; Func: 90 degree pulse width of the seventh frequency; Unit: us
	*TableTempPt++= 34;			//Addr: 0x8013; Func: 90 degree pulse width of the eighth frequency; Unit: us
  	*TableTempPt++= 135;			//Addr: 0x8014; Func: degree of 180 degree pulse width; Unit: degree
    
  	*TableTempPt++= 5;			//Addr: 0x8015; Func: step freqency of scan module; Unit: kH
    
  	*TableTempPt++= 16;			//Addr: 0x8016; Func: times of the period of signal while acquiring; Unit: N
  	*TableTempPt++= 8;			//Addr: 0x8017; Func: times of the frequncy of signal while acquiring; Unit: N
    
  	*TableTempPt++= 60;			//Addr: 0x8018; Func: time of noise acquisition; Unit: us
  	*TableTempPt++= 50;			//Addr: 0x8019; Func: frequency of noise acquisition; Unit: 0.1MHz
    
  	*TableTempPt++= 1;			//Addr: 0x801A; Func: times of data sending order; Unit: N
    
  	*TableTempPt++= 23;			//Addr: 0x801B; Func: translation time of acquisition window; Unit: us
    
  	*TableTempPt++= 100;		//Addr: 0x801C; Func: time of pulse acquisition in maintenance mode; Unit: us
  	*TableTempPt++= 80;			//Addr: 0x801D; Func: times of the frequncy of pulse in maintenance mode; Unit: us
  	*TableTempPt++= 7;			//Addr: 0x801E; Func: the selected NO. of frequency in maintenance mode; Unit: N
    
  	*TableTempPt++= 6;			//Addr: 0x801F; Func: value of TE in scale mode; Unit: us
  	*TableTempPt++= 150;		//Addr: 0x8020; Func: value of NE in scale mode; Unit: N
    
  	*TableTempPt++= 6;			//Addr: 0x8021; Func: value of TE in STESTW mode; Unit: us
  	*TableTempPt++= 800;		//Addr: 0x8022; Func: value of NE in STESTW mode; Unit: N

  	for (ZeroCnt=0;ZeroCnt<49;ZeroCnt++)   //Addr: 0x8023-0x8053;; Func: reserved word; Unit:
  	{
  		*TableTempPt++= 0;
	}
    
/*  	*TableTempPt++= 0x0604;			//Addr: 0x8023; Func: value of TE in PP6 mode for T2, BVI or CBW; Unit: us
  	*TableTempPt++= 0x3218;			//Addr: 0x8024; Func: value of NE in PP6 mode for BVI or CBW; Unit: N
  	*TableTempPt++= 833;			//Addr: 0x8025; Func: value of NE in PP6 mode for T2; Unit: N
  	*TableTempPt++= 20;				//Addr: 0x8026; Func: value of TW in PP6 mode for CBW; Unit: ms
  	*TableTempPt++= 0x2420;			//Addr: 0x8027; Func: value of Repeat time in PP6 mode for CBW; Unit: N
    
  	*TableTempPt++= 0x0004;			//Addr: 0x8028; Func: value of TE in PPoil3 mode for BVI and CBW; Unit: us
  	*TableTempPt++= 0x1919;			//Addr: 0x8029; Func: value of NE in PPoil3 mode for BVI and CBW(3D); Unit: N
  	*TableTempPt++= 0x4B7D;			//Addr: 0x802A; Func: value of NE in PPoil3 mode for BVI(3E and 3F); Unit: N
  	*TableTempPt++= 0x1432;			//Addr: 0x802B; Func: value of TW in PPoil3 mode for BVI and CBW(3D); Unit: ms
  	*TableTempPt++= 0x64C8;			//Addr: 0x802C; Func: value of TW in PPoil3 mode for BVI(3E and 3F); Unit: ms
  	*TableTempPt++= 0x1808;			//Addr: 0x802D; Func: value of Repeat time in PPoil3 mode for BVI and CBW(3D); Unit: N
  	*TableTempPt++= 0x0804;			//Addr: 0x802E; Func: value of Repeat time in PPoil3 mode for BVI(3E and 3F); Unit: N
    
  	*TableTempPt++= 0x0004;			//Addr: 0x802F; Func: value of TE in PPGas6 mode for  CBW; Unit: us
  	*TableTempPt++= 0x0019;			//Addr: 0x8030; Func: value of NE in PPGas6 mode for CBW; Unit: N
  	*TableTempPt++= 0x1432;			//Addr: 0x8031; Func: value of TW in PPGas6 mode for CBW(C and D); Unit: ms
  	*TableTempPt++= 0x0064;			//Addr: 0x8032; Func: value of TW in PPGas6 mode for CBW(E); Unit: ms
  	*TableTempPt++= 0x0804;			//Addr: 0x8033; Func: value of Repeat time in PPGas6 mode for CBW(D and E); Unit: N
  	*TableTempPt++= 0x2010;			//Addr: 0x8034; Func: value of Repeat time in PPGas6 mode for CBW(C); Unit: N
*/

 /* 	*TableTempPt++= 0x0C06;			//Addr: 0x8035; Func: value of TE in PP3 mode for T2, BVI or CBW; Unit: us
  	*TableTempPt++= 0x1910;			//Addr: 0x8036; Func: value of NE in PP3 mode for BVI or CBW; Unit: N
  	*TableTempPt++= 416;			//Addr: 0x8037; Func: value of NE in PP3 mode for T2; Unit: N
  	*TableTempPt++= 30;				//Addr: 0x8038; Func: value of TW in PP3 mode for CBW; Unit: ms
  	*TableTempPt++= 36;				//Addr: 0x8039; Func: value of Repeat time in PP3 mode for CBW; Unit: N

  	*TableTempPt++= 0x0404;			//Addr: 0x803A; Func: value of TE in PPHOIL6F mode for T2 or CBW; Unit: us
  	*TableTempPt++= 0x194B;			//Addr: 0x803B; Func: value of NE in PPHOIL6F mode for CBW; Unit: N
  	*TableTempPt++= 750;			//Addr: 0x803C; Func: value of NE in PPHOIL6F mode for T2; Unit: N
  	*TableTempPt++= 20;				//Addr: 0x803D; Func: value of TW in PPHOIL6F mode for CBW; Unit: ms
  	*TableTempPt++= 0x0864;			//Addr: 0x803E; Func: value of Repeat time in PPHOIL6F mode for CBW; Unit: N

  	*TableTempPt++= 0x0404;			//Addr: 0x803F; Func: value of TE in FBW2F mode for BVI or CBW; Unit: us
  	*TableTempPt++= 0xE119;			//Addr: 0x8040; Func: value of NE in FBW2F mode for BVI or CBW; Unit: N
  	*TableTempPt++= 0x0014;			//Addr: 0x8041; Func: value of TW in FBW2F mode for CBW; Unit: ms
  	*TableTempPt++= 0x0016;			//Addr: 0x8042; Func: value of Repeat time in FBW2F mode for CBW; Unit: N

  	*TableTempPt++= 0x0004;			//Addr: 0x8043; Func: value of TE in PPGAS6F_2 mode for  CBW; Unit: us
  	*TableTempPt++= 0x0019;			//Addr: 0x8044; Func: value of NE in PPGAS6F_2 mode for CBW; Unit: N
  	*TableTempPt++= 0x1432;			//Addr: 0x8045; Func: value of TW in PPGAS6F_2 mode for CBW(C and D); Unit: ms
  	*TableTempPt++= 0x0064;			//Addr: 0x8046; Func: value of TW in PPGAS6F_2 mode for CBW(E); Unit: ms
  	*TableTempPt++= 0x0804;			//Addr: 0x8047; Func: value of Repeat time in PPGAS6F_2 mode for CBW(D and E); Unit: N
  	*TableTempPt++= 0x0010;			//Addr: 0x8048; Func: value of Repeat time in PPGAS6F_2 mode for CBW(C); Unit: N

  	*TableTempPt++= 0x041B;			//Addr: 0x8049; Func: value of TE in PPLOIL6F mode for T2; Unit: us
  	*TableTempPt++= 0x0E04;			//Addr: 0x804A; Func: value of TE in PPLOIL6F mode for T2 or CBW; Unit: us
  	*TableTempPt++= 0x0404;			//Addr: 0x804B; Func: value of TE in PPLOIL6F mode for BVI; Unit: us
  	*TableTempPt++= 1000;			//Addr: 0x804C; Func: value of NE in PPLOIL6F mode for T2; Unit: N
  	*TableTempPt++= 148;			//Addr: 0x804D; Func: value of NE in PPLOIL6F mode for T2; Unit: N
  	*TableTempPt++= 285;			//Addr: 0x804E; Func: value of NE in PPLOIL6F mode for T2; Unit: N
  	*TableTempPt++= 0x1919;			//Addr: 0x804F; Func: value of NE in PPLOIL6F mode for BVI or CBW; Unit: N
  	*TableTempPt++= 1000;			//Addr: 0x8050; Func: value of TW in PPLOIL6F mode for T2; Unit: ms
  	*TableTempPt++= 0x3264;			//Addr: 0x8051; Func: value of TW in PPLOIL6F mode for BVI; Unit: ms
  	*TableTempPt++= 20;				//Addr: 0x8052; Func: value of TW in PPLOIL6F mode for CBW; Unit: ms
  	*TableTempPt++= 0x0804;			//Addr: 0x8053; Func: value of Repeat time in PPLOIL6F mode for BVI; Unit: N
  	*TableTempPt++= 0x0010;			//Addr: 0x8054; Func: value of Repeat time in PPLOIL6F mode for CBW; Unit: N

  	*TableTempPt++= 0x0404;			//Addr: 0x8055; Func: value of TE in PPHOIL6F_2 mode for T2 or CBW; Unit: us
  	*TableTempPt++= 0x1932;			//Addr: 0x8056; Func: value of NE in PPHOIL6F_2 mode for CBW; Unit: N
  	*TableTempPt++= 750;			//Addr: 0x8057; Func: value of NE in PPHOIL6F_2 mode for T2; Unit: N
  	*TableTempPt++= 20;				//Addr: 0x8058; Func: value of TW in PPHOIL6F_2 mode for CBW; Unit: ms
  	*TableTempPt++= 16;				//Addr: 0x8059; Func: value of Repeat time in PPHOIL6F_2 mode for CBW; Unit: N

  	*TableTempPt++= 0x050A;			//Addr: 0x805A; Func: value of TE in 3D6F mode for 1A or 2A; Unit: us
  	*TableTempPt++= 0x1428;			//Addr: 0x805B; Func: value of TE in 3D6F mode for 3A or 4A; Unit: us
  	*TableTempPt++= 0x3C64;			//Addr: 0x805C; Func: value of TE in 3D6F mode for 5B or 6B; Unit: us
  	*TableTempPt++= 0x0404;			//Addr: 0x805D; Func: value of TE in 3D6F mode for 1C or 2D; Unit: us
  	*TableTempPt++= 0x0404;			//Addr: 0x805E; Func: value of TE in 3D6F mode for 3E or 4F; Unit: us
  	*TableTempPt++= 0x0404;			//Addr: 0x805F; Func: value of TE in 3D6F mode for 5F or 6F; Unit: us
  	*TableTempPt++= 0X03E8;			//Addr: 0x8060; Func: value of NE in 3D6F mode for 1A; Unit: N
  	*TableTempPt++= 0X01F4;			//Addr: 0x8061; Func: value of NE in 3D6F mode for 2A; Unit: N
  	*TableTempPt++= 0X00FA;			//Addr: 0x8062; Func: value of NE in 3D6F mode for 3A; Unit: N
  	*TableTempPt++= 0X007D;			//Addr: 0x8063; Func: value of NE in 3D6F mode for 4A; Unit: N
  	*TableTempPt++= 0x5032;			//Addr: 0x8064; Func: value of NE in 3D6F mode for 5B or 6B; Unit: N
  	*TableTempPt++= 0x194B;			//Addr: 0x8065; Func: value of NE in 3D6F mode for 1C or 2D; Unit: N
  	*TableTempPt++= 0X0096;			//Addr: 0x8066; Func: value of NE in 3D6F mode for 3F; Unit: N
  	*TableTempPt++= 0X00E1;			//Addr: 0x8067; Func: value of NE in 3D6F mode for 4F; Unit: N
  	*TableTempPt++= 0X012C;			//Addr: 0x8068; Func: value of NE in 3D6F mode for 5F; Unit: N
  	*TableTempPt++= 0X01F4;			//Addr: 0x8069; Func: value of NE in 3D6F mode for 6F; Unit: N
  	*TableTempPt++= 0x1428;			//Addr: 0x806A; Func: value of TW in 3D6F mode for 1C or 2D; Unit: ms
  	*TableTempPt++= 0x50A0;			//Addr: 0x806B; Func: value of TW in 3D6F mode for 3E or 4F; Unit: ms
  	*TableTempPt++= 0X0140;			//Addr: 0x806C; Func: value of TW in 3D6F mode for 5F; Unit: ms
  	*TableTempPt++= 0X0280;			//Addr: 0x806D; Func: value of TW in 3D6F mode for 6F; Unit: ms
  	*TableTempPt++= 0x2010;			//Addr: 0x806E; Func: value of Repeat time in 3D6F mode for 1C or 2D; Unit: N
  	*TableTempPt++= 0x0842;			//Addr: 0x806F; Func: value of Repeat time in 3D6F mode for 3E or 4F or 5F; Unit: N

  	*TableTempPt++= 5000;			//Addr: 0x8070; Func: value of TW in HRT1T22F mode for A1; Unit: us
  	*TableTempPt++= 1620;			//Addr: 0x8071; Func: value of TW in HRT1T22F mode for B1; Unit: us
  	*TableTempPt++= 400;			//Addr: 0x8072; Func: value of TW in HRT1T22F mode for B2; Unit: us
  	*TableTempPt++= 200;			//Addr: 0x8073; Func: value of TW in HRT1T22F mode for B3; Unit: us
  	*TableTempPt++= 0x6450;			//Addr: 0x8074; Func: value of TW in HRT1T22F mode for B4 or B5; Unit: us
  	*TableTempPt++= 0x2814;			//Addr: 0x8075; Func: value of TW in HRT1T22F mode for B6 or B7; Unit: us
  	*TableTempPt++= 0x0505;			//Addr: 0x8076; Func: value of TE in HRT1T22F mode for A1 or B1; Unit: N
  	*TableTempPt++= 0x0504;			//Addr: 0x8077; Func: value of TE in HRT1T22F mode for B2 or B3; Unit: N
  	*TableTempPt++= 0x0404;			//Addr: 0x8078; Func: value of TE in HRT1T22F mode for B4 or B5; Unit: N
  	*TableTempPt++= 0x0404;			//Addr: 0x8079; Func: value of TE in HRT1T22F mode for B6 or B7; Unit: N
  	*TableTempPt++= 1000;			//Addr: 0x807A; Func: value of NE in HRT1T22F mode for A1; Unit: N
  	*TableTempPt++= 1000;			//Addr: 0x807B; Func: value of NE in HRT1T22F mode for B1; Unit: N
  	*TableTempPt++= 400;			//Addr: 0x807C; Func: value of NE in HRT1T22F mode for B2; Unit: N
  	*TableTempPt++= 300;			//Addr: 0x807D; Func: value of NE in HRT1T22F mode for B3; Unit: N
  	*TableTempPt++= 225;			//Addr: 0x807E; Func: value of NE in HRT1T22F mode for B4; Unit: N
  	*TableTempPt++= 150;			//Addr: 0x807F; Func: value of NE in HRT1T22F mode for B5; Unit: N
  	*TableTempPt++= 0x4B19;			//Addr: 0x8080; Func: value of NE in HRT1T22F mode for B6 or B7; Unit: ms
  	*TableTempPt++= 0x0102;			//Addr: 0x8081; Func: value of Repeat in HRT1T22F mode for B2 or B3; Unit: ms
  	*TableTempPt++= 0x0202;			//Addr: 0x8082; Func: value of Repeat in HRT1T22F mode for B4 or B5; Unit: ms
  	*TableTempPt++= 0x0428;			//Addr: 0x8083; Func: value of Repeat in HRT1T22F mode for B6 or B7; Unit: ms

*/
    

	return;
}

void InitPulseGain(void)             //表初始化函数
{
	PulseGainAry[0]		= 847.858;
	PulseGainAry[1]		= 847.933;
	PulseGainAry[2]		= 848.022;
	PulseGainAry[3]		= 848.125;
	PulseGainAry[4]		= 848.242;
	PulseGainAry[5]		= 848.372;
	PulseGainAry[6]		= 848.516;
	PulseGainAry[7]		= 848.672;
	PulseGainAry[8]		= 848.841;
	PulseGainAry[9]		= 849.022;
	PulseGainAry[10]	= 849.215;
	PulseGainAry[11]	= 849.419;
	PulseGainAry[12]	= 849.634;
	PulseGainAry[13]	= 849.86;
	PulseGainAry[14]	= 850.097;
	PulseGainAry[15]	= 850.344;
	PulseGainAry[16]	= 850.6;
	PulseGainAry[17]	= 850.866;
	PulseGainAry[18]	= 851.141;
	PulseGainAry[19]	= 851.425;
	PulseGainAry[20]	= 851.717;
	PulseGainAry[21]	= 852.017;
	PulseGainAry[22]	= 852.326;
	PulseGainAry[23]	= 852.641;
	PulseGainAry[24]	= 852.964;
	PulseGainAry[25]	= 853.293;
	PulseGainAry[26]	= 853.628;
	PulseGainAry[27]	= 853.97;
	PulseGainAry[28]	= 854.318;
	PulseGainAry[29]	= 854.671;
	PulseGainAry[30]	= 855.028;
	PulseGainAry[31]	= 855.391;
	PulseGainAry[32]	= 855.758;
	PulseGainAry[33]	= 856.129;
	PulseGainAry[34]	= 856.504;
	PulseGainAry[35]	= 856.882;
	PulseGainAry[36]	= 857.263;
	PulseGainAry[37]	= 857.647;
	PulseGainAry[38]	= 858.033;
	PulseGainAry[39]	= 858.421;
	PulseGainAry[40]	= 858.811;
	PulseGainAry[41]	= 859.202;
	PulseGainAry[42]	= 859.594;
	PulseGainAry[43]	= 859.987;
	PulseGainAry[44]	= 860.38;
	PulseGainAry[45]	= 860.774;
	PulseGainAry[46]	= 861.166;
	PulseGainAry[47]	= 861.559;
	PulseGainAry[48]	= 861.95;
	PulseGainAry[49]	= 862.34;
	PulseGainAry[50]	= 862.728;
	PulseGainAry[51]	= 863.114;
	PulseGainAry[52]	= 863.497;
	PulseGainAry[53]	= 863.878;
	PulseGainAry[54]	= 864.256;
	PulseGainAry[55]	= 864.631;
	PulseGainAry[56]	= 865.001;
	PulseGainAry[57]	= 865.368;
	PulseGainAry[58]	= 865.73;
	PulseGainAry[59]	= 866.088;
	PulseGainAry[60]	= 866.441;
	PulseGainAry[61]	= 866.788;
	PulseGainAry[62]	= 867.129;
	PulseGainAry[63]	= 867.464;
	PulseGainAry[64]	= 867.793;
	PulseGainAry[65]	= 868.115;
	PulseGainAry[66]	= 868.429;
	PulseGainAry[67]	= 868.732;
	PulseGainAry[68]	= 869.027;
	PulseGainAry[69]	= 869.313;
	PulseGainAry[70]	= 869.594;
	PulseGainAry[71]	= 869.868;
	PulseGainAry[72]	= 870.138;
	PulseGainAry[73]	= 870.406;
	PulseGainAry[74]	= 870.67;
	PulseGainAry[75]	= 870.934;
	PulseGainAry[76]	= 871.198;
	PulseGainAry[77]	= 871.463;
	PulseGainAry[78]	= 871.731;
	PulseGainAry[79]	= 872.002;
	PulseGainAry[80]	= 872.277;
	PulseGainAry[81]	= 872.558;
	PulseGainAry[82]	= 872.846;
	PulseGainAry[83]	= 873.141;
	PulseGainAry[84]	= 873.446;
	PulseGainAry[85]	= 873.761;
	PulseGainAry[86]	= 874.086;
	PulseGainAry[87]	= 874.428;
	PulseGainAry[88]	= 874.789;
	PulseGainAry[89]	= 875.168;
	PulseGainAry[90]	= 875.562;
	PulseGainAry[91]	= 875.971;
	PulseGainAry[92]	= 876.393;
	PulseGainAry[93]	= 876.825;
	PulseGainAry[94]	= 877.267;
	PulseGainAry[95]	= 877.717;
	PulseGainAry[96]	= 878.173;
	PulseGainAry[97]	= 878.634;
	PulseGainAry[98]	= 879.098;
	PulseGainAry[99]	= 879.564;
	PulseGainAry[100]	= 880.029;
	PulseGainAry[101]	= 880.493;
	PulseGainAry[102]	= 880.953;
	PulseGainAry[103]	= 881.409;
	PulseGainAry[104]	= 881.858;
	PulseGainAry[105]	= 882.299;
	PulseGainAry[106]	= 882.73;
	PulseGainAry[107]	= 883.15;
	PulseGainAry[108]	= 883.557;
	PulseGainAry[109]	= 883.95;
	PulseGainAry[110]	= 884.326;
	PulseGainAry[111]	= 884.685;
	PulseGainAry[112]	= 885.025;
	PulseGainAry[113]	= 885.343;
	PulseGainAry[114]	= 885.639;
	PulseGainAry[115]	= 885.912;
	PulseGainAry[116]	= 886.164;
	PulseGainAry[117]	= 886.401;
	PulseGainAry[118]	= 886.626;
	PulseGainAry[119]	= 886.84;
	PulseGainAry[120]	= 887.043;
	PulseGainAry[121]	= 887.236;
	PulseGainAry[122]	= 887.422;
	PulseGainAry[123]	= 887.601;
	PulseGainAry[124]	= 887.774;
	PulseGainAry[125]	= 887.943;
	PulseGainAry[126]	= 888.109;
	PulseGainAry[127]	= 888.274;
	PulseGainAry[128]	= 888.437;
	PulseGainAry[129]	= 888.602;
	PulseGainAry[130]	= 888.768;
	PulseGainAry[131]	= 888.938;
	PulseGainAry[132]	= 889.111;
	PulseGainAry[133]	= 889.291;
	PulseGainAry[134]	= 889.477;
	PulseGainAry[135]	= 889.672;
	PulseGainAry[136]	= 889.876;
	PulseGainAry[137]	= 890.09;
	PulseGainAry[138]	= 890.316;
	PulseGainAry[139]	= 890.555;
	PulseGainAry[140]	= 890.811;
	PulseGainAry[141]	= 891.084;
	PulseGainAry[142]	= 891.375;
	PulseGainAry[143]	= 891.68;
	PulseGainAry[144]	= 892;
	PulseGainAry[145]	= 892.333;
	PulseGainAry[146]	= 892.678;
	PulseGainAry[147]	= 893.034;
	PulseGainAry[148]	= 893.399;
	PulseGainAry[149]	= 893.773;
	PulseGainAry[150]	= 894.153;
	PulseGainAry[151]	= 894.54;
	PulseGainAry[152]	= 894.931;
	PulseGainAry[153]	= 895.325;
	PulseGainAry[154]	= 895.722;
	PulseGainAry[155]	= 896.12;
	PulseGainAry[156]	= 896.518;
	PulseGainAry[157]	= 896.915;
	PulseGainAry[158]	= 897.309;
	PulseGainAry[159]	= 897.699;
	PulseGainAry[160]	= 898.084;
	PulseGainAry[161]	= 898.463;
	PulseGainAry[162]	= 898.835;
	PulseGainAry[163]	= 899.198;
	PulseGainAry[164]	= 899.551;
	PulseGainAry[165]	= 899.894;
	PulseGainAry[166]	= 900.224;
	PulseGainAry[167]	= 900.541;
	PulseGainAry[168]	= 900.843;
	PulseGainAry[169]	= 901.13;
	PulseGainAry[170]	= 901.399;
	PulseGainAry[171]	= 901.654;
	PulseGainAry[172]	= 901.898;
	PulseGainAry[173]	= 902.131;
	PulseGainAry[174]	= 902.355;
	PulseGainAry[175]	= 902.571;
	PulseGainAry[176]	= 902.78;
	PulseGainAry[177]	= 902.983;
	PulseGainAry[178]	= 903.18;
	PulseGainAry[179]	= 903.373;
	PulseGainAry[180]	= 903.563;
	PulseGainAry[181]	= 903.75;
	PulseGainAry[182]	= 903.936;
	PulseGainAry[183]	= 904.122;
	PulseGainAry[184]	= 904.308;
	PulseGainAry[185]	= 904.495;
	PulseGainAry[186]	= 904.685;
	PulseGainAry[187]	= 904.878;
	PulseGainAry[188]	= 905.076;
	PulseGainAry[189]	= 905.279;
	PulseGainAry[190]	= 905.488;
	PulseGainAry[191]	= 905.705;
	PulseGainAry[192]	= 905.93;
	PulseGainAry[193]	= 906.164;
	PulseGainAry[194]	= 906.409;
	PulseGainAry[195]	= 906.664;
	PulseGainAry[196]	= 906.94;
	PulseGainAry[197]	= 907.241;
	PulseGainAry[198]	= 907.567;
	PulseGainAry[199]	= 907.914;
	PulseGainAry[200]	= 908.283;
	PulseGainAry[201]	= 908.669;
	PulseGainAry[202]	= 909.072;
	PulseGainAry[203]	= 909.49;
	PulseGainAry[204]	= 909.92;
	PulseGainAry[205]	= 910.361;
	PulseGainAry[206]	= 910.811;
	PulseGainAry[207]	= 911.268;
	PulseGainAry[208]	= 911.729;
	PulseGainAry[209]	= 912.193;
	PulseGainAry[210]	= 912.659;
	PulseGainAry[211]	= 913.123;
	PulseGainAry[212]	= 913.585;
	PulseGainAry[213]	= 914.042;
	PulseGainAry[214]	= 914.492;
	PulseGainAry[215]	= 914.934;
	PulseGainAry[216]	= 915.365;
	PulseGainAry[217]	= 915.783;
	PulseGainAry[218]	= 916.187;
	PulseGainAry[219]	= 916.575;
	PulseGainAry[220]	= 916.944;
	PulseGainAry[221]	= 917.293;
	PulseGainAry[222]	= 917.62;
	PulseGainAry[223]	= 917.923;
	PulseGainAry[224]	= 918.2;
	PulseGainAry[225]	= 918.449;
	PulseGainAry[226]	= 918.668;
	PulseGainAry[227]	= 918.855;
	PulseGainAry[228]	= 919.009;
	PulseGainAry[229]	= 919.127;
	PulseGainAry[230]	= 919.207;
	PulseGainAry[231]	= 919.265;
	PulseGainAry[232]	= 919.317;
	PulseGainAry[233]	= 919.364;
	PulseGainAry[234]	= 919.407;
	PulseGainAry[235]	= 919.446;
	PulseGainAry[236]	= 919.481;
	PulseGainAry[237]	= 919.512;
	PulseGainAry[238]	= 919.541;
	PulseGainAry[239]	= 919.567;
	PulseGainAry[240]	= 919.591;
	PulseGainAry[241]	= 919.614;
	PulseGainAry[242]	= 919.635;
	PulseGainAry[243]	= 919.656;
	PulseGainAry[244]	= 919.676;
	PulseGainAry[245]	= 919.697;
	PulseGainAry[246]	= 919.718;
	PulseGainAry[247]	= 919.74;
	PulseGainAry[248]	= 919.763;
	PulseGainAry[249]	= 919.788;
	PulseGainAry[250]	= 919.815;
	PulseGainAry[251]	= 919.845;
	PulseGainAry[252]	= 919.879;
	PulseGainAry[253]	= 919.915;
	PulseGainAry[254]	= 919.956;
	PulseGainAry[255]	= 920.001;
	PulseGainAry[256]	= 920.051;
	PulseGainAry[257]	= 920.106;
	PulseGainAry[258]	= 920.166;
	PulseGainAry[259]	= 920.248;
	PulseGainAry[260]	= 920.364;
	PulseGainAry[261]	= 920.509;
	PulseGainAry[262]	= 920.679;
	PulseGainAry[263]	= 920.869;
	PulseGainAry[264]	= 921.074;
	PulseGainAry[265]	= 921.291;
	PulseGainAry[266]	= 921.514;
	PulseGainAry[267]	= 921.74;
	PulseGainAry[268]	= 921.963;
	PulseGainAry[269]	= 922.18;
	PulseGainAry[270]	= 922.385;
	PulseGainAry[271]	= 922.59;
	PulseGainAry[272]	= 922.808;
	PulseGainAry[273]	= 923.037;
	PulseGainAry[274]	= 923.274;
	PulseGainAry[275]	= 923.519;
	PulseGainAry[276]	= 923.768;
	PulseGainAry[277]	= 924.021;
	PulseGainAry[278]	= 924.274;
	PulseGainAry[279]	= 924.527;
	PulseGainAry[280]	= 924.778;
	PulseGainAry[281]	= 925.023;
	PulseGainAry[282]	= 925.263;
	PulseGainAry[283]	= 925.493;
	PulseGainAry[284]	= 925.714;
	PulseGainAry[285]	= 925.922;
	PulseGainAry[286]	= 926.115;
	PulseGainAry[287]	= 926.293;
	PulseGainAry[288]	= 926.453;
	PulseGainAry[289]	= 926.592;
	PulseGainAry[290]	= 926.709;
	PulseGainAry[291]	= 926.812;
	PulseGainAry[292]	= 926.908;
	PulseGainAry[293]	= 926.998;
	PulseGainAry[294]	= 927.083;
	PulseGainAry[295]	= 927.163;
	PulseGainAry[296]	= 927.238;
	PulseGainAry[297]	= 927.31;
	PulseGainAry[298]	= 927.378;
	PulseGainAry[299]	= 927.443;
	PulseGainAry[300]	= 927.505;
	PulseGainAry[301]	= 927.565;
	PulseGainAry[302]	= 927.624;
	PulseGainAry[303]	= 927.682;
	PulseGainAry[304]	= 927.739;
	PulseGainAry[305]	= 927.796;
	PulseGainAry[306]	= 927.854;
	PulseGainAry[307]	= 927.913;
	PulseGainAry[308]	= 927.972;
	PulseGainAry[309]	= 928.034;
	PulseGainAry[310]	= 928.098;
	PulseGainAry[311]	= 928.165;
	PulseGainAry[312]	= 928.236;
	PulseGainAry[313]	= 928.309;
	PulseGainAry[314]	= 928.385;
	PulseGainAry[315]	= 928.462;
	PulseGainAry[316]	= 928.542;
	PulseGainAry[317]	= 928.622;
	PulseGainAry[318]	= 928.704;
	PulseGainAry[319]	= 928.787;
	PulseGainAry[320]	= 928.87;
	PulseGainAry[321]	= 928.954;
	PulseGainAry[322]	= 929.038;
	PulseGainAry[323]	= 929.121;
	PulseGainAry[324]	= 929.203;
	PulseGainAry[325]	= 929.285;
	PulseGainAry[326]	= 929.366;
	PulseGainAry[327]	= 929.445;
	PulseGainAry[328]	= 929.522;
	PulseGainAry[329]	= 929.597;
	PulseGainAry[330]	= 929.67;
	PulseGainAry[331]	= 929.74;
	PulseGainAry[332]	= 929.807;
	PulseGainAry[333]	= 929.871;
	PulseGainAry[334]	= 929.932;
	PulseGainAry[335]	= 929.988;
	PulseGainAry[336]	= 930.041;
	PulseGainAry[337]	= 930.089;
	PulseGainAry[338]	= 930.135;
	PulseGainAry[339]	= 930.177;
	PulseGainAry[340]	= 930.216;
	PulseGainAry[341]	= 930.252;
	PulseGainAry[342]	= 930.287;
	PulseGainAry[343]	= 930.319;
	PulseGainAry[344]	= 930.35;
	PulseGainAry[345]	= 930.379;
	PulseGainAry[346]	= 930.407;
	PulseGainAry[347]	= 930.435;
	PulseGainAry[348]	= 930.462;
	PulseGainAry[349]	= 930.488;
	PulseGainAry[350]	= 930.515;
	PulseGainAry[351]	= 930.542;
	PulseGainAry[352]	= 930.57;
	PulseGainAry[353]	= 930.598;
	PulseGainAry[354]	= 930.628;
	PulseGainAry[355]	= 930.66;
	PulseGainAry[356]	= 930.693;
	PulseGainAry[357]	= 930.728;
	PulseGainAry[358]	= 930.766;
	PulseGainAry[359]	= 930.807;
	PulseGainAry[360]	= 930.85;
	PulseGainAry[361]	= 930.897;
	PulseGainAry[362]	= 930.947;
	PulseGainAry[363]	= 931.001;
	PulseGainAry[364]	= 931.06;
	PulseGainAry[365]	= 931.122;
	PulseGainAry[366]	= 931.194;
	PulseGainAry[367]	= 931.28;
	PulseGainAry[368]	= 931.378;
	PulseGainAry[369]	= 931.491;
	PulseGainAry[370]	= 931.616;
	PulseGainAry[371]	= 931.754;
	PulseGainAry[372]	= 931.904;
	PulseGainAry[373]	= 932.067;
	PulseGainAry[374]	= 932.243;
	PulseGainAry[375]	= 932.43;
	PulseGainAry[376]	= 932.63;
	PulseGainAry[377]	= 932.841;
	PulseGainAry[378]	= 933.064;
	PulseGainAry[379]	= 933.298;
	PulseGainAry[380]	= 933.543;
	PulseGainAry[381]	= 933.799;
	PulseGainAry[382]	= 934.067;
	PulseGainAry[383]	= 934.344;
	PulseGainAry[384]	= 934.633;
	PulseGainAry[385]	= 934.931;
	PulseGainAry[386]	= 935.299;
	PulseGainAry[387]	= 935.784;
	PulseGainAry[388]	= 936.37;
	PulseGainAry[389]	= 937.042;
	PulseGainAry[390]	= 937.781;
	PulseGainAry[391]	= 938.573;
	PulseGainAry[392]	= 939.401;
	PulseGainAry[393]	= 940.248;
	PulseGainAry[394]	= 941.098;
	PulseGainAry[395]	= 941.936;
	PulseGainAry[396]	= 942.743;
	PulseGainAry[397]	= 943.506;
	PulseGainAry[398]	= 944.206;
	PulseGainAry[399]	= 944.828;
	PulseGainAry[400]	= 945.355;
	PulseGainAry[401]	= 945.771;
	PulseGainAry[402]	= 946.115;
	PulseGainAry[403]	= 946.437;
	PulseGainAry[404]	= 946.739;
	PulseGainAry[405]	= 947.021;
	PulseGainAry[406]	= 947.286;
	PulseGainAry[407]	= 947.535;
	PulseGainAry[408]	= 947.768;
	PulseGainAry[409]	= 947.989;
	PulseGainAry[410]	= 948.197;
	PulseGainAry[411]	= 948.395;
	PulseGainAry[412]	= 948.583;
	PulseGainAry[413]	= 948.764;
	PulseGainAry[414]	= 948.938;
	PulseGainAry[415]	= 949.107;
	PulseGainAry[416]	= 949.273;
	PulseGainAry[417]	= 949.437;
	PulseGainAry[418]	= 949.599;
	PulseGainAry[419]	= 949.763;
	PulseGainAry[420]	= 949.928;
	PulseGainAry[421]	= 950.097;
	PulseGainAry[422]	= 950.27;
	PulseGainAry[423]	= 950.45;
	PulseGainAry[424]	= 950.638;
	PulseGainAry[425]	= 950.834;
	PulseGainAry[426]	= 951.041;
	PulseGainAry[427]	= 951.26;
	PulseGainAry[428]	= 951.492;
	PulseGainAry[429]	= 951.739;
	PulseGainAry[430]	= 952.002;
	PulseGainAry[431]	= 952.283;
	PulseGainAry[432]	= 952.582;
	PulseGainAry[433]	= 952.902;
	PulseGainAry[434]	= 953.238;
	PulseGainAry[435]	= 953.586;
	PulseGainAry[436]	= 953.946;
	PulseGainAry[437]	= 954.319;
	PulseGainAry[438]	= 954.706;
	PulseGainAry[439]	= 955.106;
	PulseGainAry[440]	= 955.52;
	PulseGainAry[441]	= 955.948;
	PulseGainAry[442]	= 956.391;
	PulseGainAry[443]	= 956.849;
	PulseGainAry[444]	= 957.322;
	PulseGainAry[445]	= 957.812;
	PulseGainAry[446]	= 958.317;
	PulseGainAry[447]	= 958.84;
	PulseGainAry[448]	= 959.379;
	PulseGainAry[449]	= 959.936;
	PulseGainAry[450]	= 960.51;
	PulseGainAry[451]	= 961.103;
	PulseGainAry[452]	= 961.715;
	PulseGainAry[453]	= 962.345;
	PulseGainAry[454]	= 962.995;
	PulseGainAry[455]	= 963.665;
	PulseGainAry[456]	= 964.354;
	PulseGainAry[457]	= 965.065;
	PulseGainAry[458]	= 965.796;
	PulseGainAry[459]	= 966.548;
	PulseGainAry[460]	= 967.323;
	PulseGainAry[461]	= 968.119;
	PulseGainAry[462]	= 968.938;
	PulseGainAry[463]	= 969.78;
	PulseGainAry[464]	= 970.645;
	PulseGainAry[465]	= 971.534;
	PulseGainAry[466]	= 972.447;
	PulseGainAry[467]	= 973.384;
	PulseGainAry[468]	= 974.346;
	PulseGainAry[469]	= 975.333;
	PulseGainAry[470]	= 976.346;
	PulseGainAry[471]	= 977.385;
	PulseGainAry[472]	= 978.45;
	PulseGainAry[473]	= 979.542;
	PulseGainAry[474]	= 980.662;
	PulseGainAry[475]	= 981.808;
	PulseGainAry[476]	= 982.983;
	PulseGainAry[477]	= 984.186;
	PulseGainAry[478]	= 985.524;
	PulseGainAry[479]	= 987.093;
	PulseGainAry[480]	= 988.878;
	PulseGainAry[481]	= 990.865;
	PulseGainAry[482]	= 993.04;
	PulseGainAry[483]	= 995.388;
	PulseGainAry[484]	= 997.895;
	PulseGainAry[485]	= 1000.547;
	PulseGainAry[486]	= 1003.328;
	PulseGainAry[487]	= 1006.225;
	PulseGainAry[488]	= 1009.222;
	PulseGainAry[489]	= 1012.307;
	PulseGainAry[490]	= 1015.463;
	PulseGainAry[491]	= 1018.677;
	PulseGainAry[492]	= 1021.935;
	PulseGainAry[493]	= 1025.221;
	PulseGainAry[494]	= 1028.521;
	PulseGainAry[495]	= 1031.822;
	PulseGainAry[496]	= 1035.108;
	PulseGainAry[497]	= 1038.385;
	PulseGainAry[498]	= 1041.669;
	PulseGainAry[499]	= 1044.961;
	PulseGainAry[500]	= 1048.259; 
	return;
}

void InitGpio(void)                //GPIOA，B口配置函数
{
	EALLOW;
    GpioMuxRegs.GPAMUX.all=0x0000;              //设置GPIOA
    GpioMuxRegs.GPADIR.all=0x00ff;   
    GpioMuxRegs.GPAQUAL.all=0x0000;
 
    GpioMuxRegs.GPBMUX.all=0x0000;              //设置GPIOB
    GpioMuxRegs.GPBDIR.all=0xffff;   
    GpioMuxRegs.GPBQUAL.all=0x0000;  
	EDIS;
	return;
}

void InitFPGA(void)
{
	GpioDataRegs.GPADAT.bit.GPIOA3 = 0;
    Delay(20);
    GpioDataRegs.GPADAT.bit.GPIOA3 = 1;
    Delay(50);
    GpioDataRegs.GPADAT.bit.GPIOA3 = 0;
    Delay(200);
	RELAY_ON_CLOSE = 0xFF00;   //继电器打开
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;
	return;
}  

void InitVariables(void)
{
	RelayAry[1]		= RELAY_CTR_1;
	RelayAry[2]		= RELAY_CTR_2;
	RelayAry[3]		= RELAY_CTR_3;
	RelayAry[4]		= RELAY_CTR_4;
	RelayAry[5]		= RELAY_CTR_5;
	RelayAry[6]		= RELAY_CTR_6;
	RelayAry[7]		= RELAY_CTR_7;
	RelayAry[8]		= RELAY_CTR_8;

	PP6FMiniNumAry[0]	= 2;
	PP6FMiniNumAry[1]	= 2;
	PP6FMiniNumAry[2]	= 3;
	PP6FMiniNumAry[3]	= 2;
	PP6FMiniNumAry[4]	= 2;
	PP6FMiniNumAry[5]	= 3;

	Oil3MiniNumAry[0]	= 4;
	Oil3MiniNumAry[1]	= 4;
	Oil3MiniNumAry[2]	= 5;

	Gas6FMiniNumAry[0]	= 4;
	Gas6FMiniNumAry[1]	= 6;
	Gas6FMiniNumAry[2]	= 4;
	Gas6FMiniNumAry[3]	= 6;
	Gas6FMiniNumAry[4]	= 2;
	Gas6FMiniNumAry[5]	= 2;

	PP3FMiniNumAry[0] 	= 2;
	PP3FMiniNumAry[1] 	= 2;
	PP3FMiniNumAry[2] 	= 2;

	PPHOIL6FMiniNumAry[0] = 7;
	PPHOIL6FMiniNumAry[1] = 4;
	PPHOIL6FMiniNumAry[2] = 7;
	PPHOIL6FMiniNumAry[3] = 3;
	PPHOIL6FMiniNumAry[4] = 3;
	PPHOIL6FMiniNumAry[5] = 3;

	FBW2FMiniNumAry[0]	= 2;
	FBW2FMiniNumAry[1]	= 2;

	Gas6_2FMiniNumAry[0] = 4;
	Gas6_2FMiniNumAry[1] = 6;
	Gas6_2FMiniNumAry[2] = 4;
	Gas6_2FMiniNumAry[3] = 6;
	Gas6_2FMiniNumAry[4] = 2;
	Gas6_2FMiniNumAry[5] = 2;

	PPLOIL6FMiniNumAry[0] = 4;
	PPLOIL6FMiniNumAry[1] = 6;
	PPLOIL6FMiniNumAry[2] = 4;
	PPLOIL6FMiniNumAry[3] = 6;
	PPLOIL6FMiniNumAry[4] = 2;
	PPLOIL6FMiniNumAry[5] = 2;

	HRT1T22FMiniNumAry[0] = 1;
	HRT1T22FMiniNumAry[1] = 7;

	PPHOIL6F_2MiniNumAry[0] = 7;
	PPHOIL6F_2MiniNumAry[1] = 4;
	PPHOIL6F_2MiniNumAry[2] = 7;
	PPHOIL6F_2MiniNumAry[3] = 3;
	PPHOIL6F_2MiniNumAry[4] = 4;
	PPHOIL6F_2MiniNumAry[5] = 4;

	P3D6FMiniNumAry[0] = 2;
	P3D6FMiniNumAry[1] = 2;
	P3D6FMiniNumAry[2] = 2;
	P3D6FMiniNumAry[3] = 5;
	P3D6FMiniNumAry[4] = 3;
	P3D6FMiniNumAry[5] = 2;


	DT2DMiniNumAry[0]	= 15;
	DT2DMiniNumAry[1]	= 15;

	MT2DMiniNumAry[0]	= 3;
	MT2DMiniNumAry[1]	= 6;
	MT2DMiniNumAry[2]	= 6;

	DFT1T2DMiniNumAry[0] = 27;
	DFT1T2DMiniNumAry[1] = 27;

	WorkModeChoice[0] = 0x0001;
	WorkModeChoice[1] = 0x0002;
	WorkModeChoice[2] = 0x0003;
	WorkModeChoice[3] = 0x0004;
	WorkModeChoice[4] = 0x0005;
	WorkModeChoice[5] = 0x0006;
	WorkModeChoice[6] = 0x0007;
	WorkModeChoice[7] = 0x0008;
	WorkModeChoice[8] = 0x0009;
	WorkModeChoice[9] = 0x000A;
	WorkModeChoice[10] = 0x000B;
	WorkModeChoice[11] = 0x000C;
	WorkModeChoice[12] = 0x000D;
	WorkModeChoice[13] = 0x000E;
	WorkModeChoice[14] = 0x000F;
	WorkModeChoice[15] = 0x0010;
	WorkModeChoice[16] = 0x0011;
	WorkModeChoice[17] = 0x0020;
	WorkModeChoice[18] = 0x0030;
	WorkModeChoice[19] = 0x0040;
	WorkModeChoice[20] = 0x0060;
	WorkModeChoice[21] = 0x0070;

	SendTableFlag		= CLEAR;	//send table flag:发送参数表标志，为1时发送参数表
	DENum				= 0;
	PhaseFlag			= POSITIVE;
	ScanModeFlag		= CLEAR;
	CycleFlag			= CLEAR;
	PulseAcqFlag		= CLEAR;
	SingleModeFlag		= CLEAR;
	WorkMode			= 9;
	DownTableFlag		= CLEAR;
	PP6ModeFlag			= CLEAR;
	Oil3ModeFlag		= CLEAR;
	Gas6ModeFlag		= CLEAR;
	ScaleModeFlag		= CLEAR;
	HoleModeFlag		= CLEAR;
	ST2DFlag			= CLEAR;
	DT2DFlag			= CLEAR;
	MT2DFlag			= CLEAR;
	ST1T2Flag			= CLEAR;
	DT1T2Flag			= CLEAR;
	ST12DFlag			= CLEAR;
	DT12DFlag			= CLEAR;
	PPLOIL6FFlag		= CLEAR;
	flag_pp3			= CLEAR;
	FBW2FFlag			= CLEAR;
	PPHOIL6FFlag		= CLEAR;
	Gas6_2ModeFlag		= CLEAR;
	PPHOIL6F_2Flag		= CLEAR;
	P3D6FFlag			= CLEAR;
	HRT1T22FFlag		= CLEAR;
	DFT1T2DFlag			= CLEAR;

	ChgTable995Flag		= CLEAR;
	ChgTable996Flag		= CLEAR;
	ChgTable999Flag		= CLEAR;
	ChgTable99AFlag		= CLEAR;

	DUMP_SUSTAIN_DIS	= USER_DISABLE;
	INV_TURN_DIS		= USER_DISABLE;
	DumpSustainFlag		= CLEAR;
	InverseTurnFlag		= CLEAR;
	return;
}

void InitInterruptMcbsp(void)
{
   	EALLOW;	 
	PieVectTable.MRINTA = &MRINTA_ISR1;   	//Mcbsp中断向量入口地址
	EDIS;		

    IER |= M_INT6;
	PieCtrlRegs.PIEIER6.all = 0x0010;      //使能MCBSP接收中断
	PieCtrlRegs.PIEACK.all=PIEACK_GROUP6;
	EINT;   // Enable Global interrupt INTM 
}

void LoadParaDis(void)
{
	STATE1MS_LOAD_DIS 	= USER_DISABLE;

	CAL_DATALOAD_DIS= USER_DISABLE;
	DDS_DATALOAD_DIS= USER_DISABLE;
	SCAN_LOAD_DIS	= USER_DISABLE; 
	SIGNAL_LOAD_DIS	= USER_DISABLE;

	NSTATE_LOAD_DIS = USER_DISABLE;
	NRAM_LOAD_DIS	= USER_DISABLE;

	PLUSE_LOAD_DIS	= USER_DISABLE;
	BRIDGE_LOAD_DIS	= USER_DISABLE;     
	DUMP_LOAD_DIS	= USER_DISABLE;
	SCALE_LOAD_DIS	= USER_DISABLE;
	return;
}

