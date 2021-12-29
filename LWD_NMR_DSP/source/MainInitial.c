/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"
#include "TableStruct.h"

#ifndef DEBUG
extern Uint16 secureRamFuncs_runstart;
extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadend;
#endif

void InitAll(void)
{
	//System initial
	InitSysCtrl(); //CPU初始化

#ifndef DEBUG
	/* FLASH版本必须添加这两个函数:memcpy()和InitFlash */
	memcpy(&secureRamFuncs_runstart,
	    &secureRamFuncs_loadstart,
	    &secureRamFuncs_loadend - &secureRamFuncs_loadstart);

    /* FLASH 初始化 */
    InitFlash();
#endif

	//Initial GPIO and FPGA chip
	InitGpio();     //复位GPIO，SCIA配置在这里面
	clear_sci_rec_buf();	
	InitSci();
	InitFPGA(); //复位FPGA
    // Initial timer module
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 30, 1000);
	//Initial PIE module
	DINT;
	IER &= 0x0000;
	IFR &= 0x0000;
	InitPieCtrl();
	InitPieVectTable();

	DINT;		  //关中断
	IER = 0x0000; //禁止所有的中断
	IFR = 0x0000;

	//SciaRegs.SCICTL1.bit.SLEEP=1;   //启动SCI睡眠模式

	EALLOW;									//保护寄存器
	PieVectTable.XINT1 = &XINT1_STOP;		//外部中断1入口地址
	PieVectTable.XINT2 = &XINT2_DCStorData; //外部中断2入口地址
	PieVectTable.RXAINT = &SCIRXINTA_ISR;	//SCIA接收中断向量入口地址
	PieVectTable.TINT0 = &CpuTimer0ISR;    //定时器0中断入口地址
	EDIS;									// 释放保护的寄存器

	IER |= M_INT1;
	IER |= M_INT9;

	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// SCIA
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	XIntruptRegs.XINT1CR.all = 0x5;			//打开管脚xint1外中断,设置上升沿中断
	XIntruptRegs.XINT2CR.all = 0x5;			//打开管脚xint2外中断,设置上升沿中断
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //清除PIE分组1的中断响应位
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
	EINT; 	// Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM


	GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; //485接收器为接收状态

    CpuTimer0Regs.TCR.bit.TSS = 0;    // 启动定时器

	// Initial MCBSP module
	// InitMcbsp();
	// McBSP interrupt initialization
	// InitInterruptMcbsp();

	// RS485 SCIA_T/GPIOF4 SCIA_R/GPIOF5 SCIA_RE/GPIOF11

	InitPulseGain(); //初始化激励衰减倍数表
	ShutdownHV();	 //储能短接断开
	LoadParaDis();
	STATE1MS_RST_EN = USER_ENABLE;
	STATE1MS_RST_DIS = USER_ENABLE;
	STATE1MS_START_DIS = USER_DISABLE;
	//Load State 1ms Parameters
	PulseCycle = 100;
	PulseTime = 1000;
	MDumpTime = 1800;
	SDumpTime = 3000;
	CutTime = 94000;
	CutTimeLow = CutTime & 0x0000ffff;
	CutTimeHi = (CutTime & 0xffff0000) >> 16;

	STATE1MS_CHOICE = 0;
	STATE1MS_DATA = (Uint16)PulseCycle;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	STATE1MS_CHOICE = 1;
	STATE1MS_DATA = (Uint16)PulseTime;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	STATE1MS_CHOICE = 2;
	STATE1MS_DATA = (Uint16)MDumpTime;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	STATE1MS_CHOICE = 3;
	STATE1MS_DATA = (Uint16)SDumpTime;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	STATE1MS_CHOICE = 4;
	STATE1MS_DATA = CutTimeLow;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	STATE1MS_CHOICE = 5;
	STATE1MS_DATA = CutTimeHi;
	STATE1MS_LOAD_EN = USER_ENABLE;
	STATE1MS_LOAD_DIS = USER_DISABLE;

	TIMER_STOP = 0x2;

	//Reset Scan Module
	SCAN_START_DIS = USER_DISABLE;
	SCAN_RST_EN = USER_ENABLE;
	SCAN_RST_DIS = USER_DISABLE;
	RstPulseModule();
	RstNoiseModule();
	//Reset Scale Module
	SCALE_START_DIS = USER_DISABLE;
	SCALE_RST_EN = USER_ENABLE;
	SCALE_RST_DIS = USER_DISABLE;
	//Variables initialization
	InitVariables();
	//Parameter-table initialization
	InitTable(); //初始化参数表
	return;
}

void InitTable(void)
{
	TableTempPt = (Uint16 *)0x8000;
	*TableTempPt++ = 2; // 0x8000, TableID : 2, 参数表选择刻度模式
	*TableTempPt++ = 8; // 0x8001, WorkMode: 8, 模式选择仪器扫频模式

	// 刻度模式参数表
	*TableTempPt++ = 22;	 // 0x8002, Length: 22, 参数表长度+Length字段+CheckSum
	*TableTempPt++ = 2;		 // 0x8003, TableID: 2, 刻度模式参数表ID
	*TableTempPt++ = 20;	 // 0x8004, 刻度表Length: 20, 参数表长度
	*TableTempPt++ = 0xFFFF; // 预留字
	*TableTempPt++ = 0xFFFF; // 预留字
	*TableTempPt++ = 8;		 // 0x8007, Mode: 8, 刻度模式选择仪器扫频模式
	*TableTempPt++ = 512;	 // 0x8008, RelayCode: 512, num, 调谐码
	*TableTempPt++ = 4750;	 // 0x8009, CenterFreq: 4750, 0.1kHz, 发射频率
	*TableTempPt++ = 50;	 // 0x800A, ScanDeltaFreq: 50, 0.1kHz, 扫描步进频率
	*TableTempPt++ = 60;	 // 0x800B, NoiseAcqTime: 60, us, 噪声采集时间
	*TableTempPt++ = 50;	 // 0x800C, NoiseAcqFreq: 50, 0.1MHz, 噪声采样率
	*TableTempPt++ = 10;	 // 0x800D, Period: 10, s,  刻度采集指令时间间隔
	*TableTempPt++ = 48;	 // 0x800E, Width90Pulse: 48, us, 90度宽度脉冲
	*TableTempPt++ = 135;	 // 0x800F, Angle180Pulse: 135, deg, 180度脉冲角度
	*TableTempPt++ = 16;	 // 0x8010, EchoAcqPeriodNum: 16, number, 回波周期数
	*TableTempPt++ = 8;		 // 0x8011, EchoAcqFreqRate: 8, number, 回波采样率相对于回波信号频率的倍数
	*TableTempPt++ = 23;	 // 0x8012, EchoAcqWindowShift: 23, us, 回波采集时间窗偏移
	*TableTempPt++ = 10;	 // 0x8013, CalibTE: 10, 0.1ms, 刻度时的TE
	*TableTempPt++ = 60;	 // 0x8014, CalibNE: 60, number, 刻度时的NE
	*TableTempPt++ = 100;	 // 0x8015, PulseTestPulseTime: 100, us, 脉冲检测时的发射脉冲宽度
	*TableTempPt++ = 80;	 // 0x8016, PulseTestAcqFreq: 80, 0.1MHz, 脉冲检测时的采样率
							 // 0x8017, CheckSum

	// 测井模式参数表，common params
	TableTempPt = (Uint16 *)0x8018;
	*TableTempPt++ = 59;	 // 0x8018, Length: 59, 参数表长度+Length字段+CheckSum
	*TableTempPt++ = 3;		 // 0x8019, TableID: 3, 测井模式参数表ID
	*TableTempPt++ = 57;	 // 0x801A, 测井表Length: 57, 参数表长度
	*TableTempPt++ = 0xFFFF; // 预留字
	*TableTempPt++ = 0xFFFF; // 预留字
	*TableTempPt++ = 0x0001; // 0x801D, Mode: 1, 单频模式
	*TableTempPt++ = 4850;	 // 0x801E, CenterFreq: 4850, 0.1kHz, 发射频率

	*TableTempPt++ = 50;  	// 0x801F, ScanDeltaFreq: 50, 0.1kHz, 扫描步进频率
	*TableTempPt++ = 60;  	// 0x8020, NoiseAcqTime: 60, us, 噪声采集时间
	*TableTempPt++ = 50;  	// 0x8021, NoiseAcqFreq: 50, 0.1MHz, 噪声采样率
	*TableTempPt++ = 135; 	// 0x8022, Angle180Pulse: 135, deg, 180度脉冲角度
	*TableTempPt++ = 16;  	// 0x8023, EchoAcqPeriodNum: 16, number, 回波周期数
	*TableTempPt++ = 8;	  	// 0x8024, EchoAcqFreqRate: 8, number, 回波采样率相对于回波信号频率的倍数
	*TableTempPt++ = 23;  	// 0x8025, EchoAcqWindowShift: 23, us, 回波采集时间窗偏移

	// 测井模式下属各个模式参数
	// STWTE
	*TableTempPt++ = 10;	// 0x8026, 模式周期
	*TableTempPt++ = 6;		// 0x8027, TE
	*TableTempPt++ = 1000;	// 0x8028, NE
	// PPMODE
	*TableTempPt++ = 17;	// 0x8029, 模式周期
	*TableTempPt++ = 30;	// 0x802A, 1C序列的TW
	*TableTempPt++ = 6;		// 0x802B, 1A序列的TE
	*TableTempPt++ = 6;		// 0x802C, 1C序列的TE
	*TableTempPt++ = 1000;	// 0x802D, 1A序列的NE
	*TableTempPt++ = 50;	// 0x802E, 1C序列的NE
	*TableTempPt++ = 96;	// 0x802F, 1C序列的重复次数
	// PPDIF
	*TableTempPt++ = 17;	// 0x8030, 模式周期
	*TableTempPt++ = 30;	// 0x8031, 1C序列的TW
	*TableTempPt++ = 1800;	// 0x8032, 1B序列的TW
	*TableTempPt++ = 6;		// 0x8033, 1A、1B序列的TE
	*TableTempPt++ = 6;		// 0x8034, 1C序列的TE
	*TableTempPt++ = 1000;	// 0x8035, 1A、1B序列的NE
	*TableTempPt++ = 50;	// 0x8036, 1C序列的NE
	*TableTempPt++ = 25;	// 0x8037, 1C序列的重复次数
	// PPT1
	*TableTempPt++ = 20;	// 0x8038, 模式周期
	*TableTempPt++ = 40;	// 0x8039, 1C序列的TW
	*TableTempPt++ = 2;		// 0x803A, 1D、1E、1F、1G、1H序列的TW选择码
	*TableTempPt++ = 6;		// 0x803B, 1A序列的TE
	*TableTempPt++ = 6;		// 0x803C, 1C、1D、1E、1F、1G、1H序列的TE
	*TableTempPt++ = 1000;	// 0x803D, 1A序列的NE
	*TableTempPt++ = 50;	// 0x803E, 1C序列的NE
	*TableTempPt++ = 16;	// 0x803F, 1D&1E&1F&1G&1H序列的NE
	*TableTempPt++ = 50;	// 0x8040, 1C序列的重复次数
	// PPOFTW
	*TableTempPt++ = 71;	// 0x8041, 模式周期
	*TableTempPt++ = 40;	// 0x8042, 1C序列的TW
	*TableTempPt++ = 13000;	// 0x8043, 1D序列的TW
	*TableTempPt++ = 11000;	// 0x8044, 1E序列的TW
	*TableTempPt++ = 10000;	// 0x8045, 1F序列的TW
	*TableTempPt++ = 8000;	// 0x8046, 1G序列的TW
	*TableTempPt++ = 6000;	// 0x8047, 1H序列的TW
	*TableTempPt++ = 6;		// 0x8048, 1A&1D&1E&1F&1G&1H序列的TE
	*TableTempPt++ = 6;		// 0x8049, 1C序列的TE
	*TableTempPt++ = 50;	// 0x804A, 1C序列的重复次数
	// PPShort
	*TableTempPt++ = 6;		// 0x804B, 模式周期
	*TableTempPt++ = 40;	// 0x804C, 1C序列的TW
	*TableTempPt++ = 6;		// 0x804D, 1A序列的TE
	*TableTempPt++ = 6;		// 0x804E, 1C序列的TE
	*TableTempPt++ = 1000;	// 0x804F, 1A序列的NE
	*TableTempPt++ = 50;	// 0x8050, 1C序列的NE
	*TableTempPt++ = 50;	// 0x8051, 1C序列的重复次数
	*TableTempPt++ = 0;		// CheckSum

	// 刻度参数表
    // 此表中实际上只需要拟合系数
	Float2Uint16_u rca;
	rca.real_data = 2604.9;
    TuningTableEntry->rca0[0] = rca.data[0];
    TuningTableEntry->rca0[1] = rca.data[1];
    rca.real_data = -8.9288;
    TuningTableEntry->rca1[0] = rca.data[0];
    TuningTableEntry->rca1[1] = rca.data[1];
    rca.real_data = 0.0074;
    TuningTableEntry->rca2[0] = rca.data[0];
    TuningTableEntry->rca2[1] = rca.data[1];

	TuningTableEntry->length = 77;
	TuningTableEntry->table_head.table_ID = 1;
	TuningTableEntry->table_head.table_len = 75;
	TuningTableEntry->table_head.rsv_word[0] = 0xFFFF;
	TuningTableEntry->table_head.rsv_word[1] = 0xFFFF;
	TuningTableEntry->instruct_info.tool_ID[0] = 0x6D72;	// "MR"
	TuningTableEntry->instruct_info.tool_ID[1] = 0x7439;	// "T9"
	TuningTableEntry->instruct_info.tool_ID[2] = 0x352D;	// "5-"
	TuningTableEntry->instruct_info.tool_ID[3] = 0x3231;	// "21"
	TuningTableEntry->instruct_info.tool_ID[4] = 0x3031;	// "01"
	// PTa
	TuningTableEntry->PTa0[0] = 0;
	TuningTableEntry->PTa0[1] = 0;
	TuningTableEntry->PTa1[0] = 0;
	TuningTableEntry->PTa1[1] = 0;
	TuningTableEntry->PTa2[0] = 0;
	TuningTableEntry->PTa2[1] = 0;

	// 配置参数表
	// TODO: 目前还没有需要使用的参数
}

void InitPulseGain(void) //表初始化函数
{
	PulseGainAry[0] = 847.858;
	PulseGainAry[1] = 847.933;
	PulseGainAry[2] = 848.022;
	PulseGainAry[3] = 848.125;
	PulseGainAry[4] = 848.242;
	PulseGainAry[5] = 848.372;
	PulseGainAry[6] = 848.516;
	PulseGainAry[7] = 848.672;
	PulseGainAry[8] = 848.841;
	PulseGainAry[9] = 849.022;
	PulseGainAry[10] = 849.215;
	PulseGainAry[11] = 849.419;
	PulseGainAry[12] = 849.634;
	PulseGainAry[13] = 849.86;
	PulseGainAry[14] = 850.097;
	PulseGainAry[15] = 850.344;
	PulseGainAry[16] = 850.6;
	PulseGainAry[17] = 850.866;
	PulseGainAry[18] = 851.141;
	PulseGainAry[19] = 851.425;
	PulseGainAry[20] = 851.717;
	PulseGainAry[21] = 852.017;
	PulseGainAry[22] = 852.326;
	PulseGainAry[23] = 852.641;
	PulseGainAry[24] = 852.964;
	PulseGainAry[25] = 853.293;
	PulseGainAry[26] = 853.628;
	PulseGainAry[27] = 853.97;
	PulseGainAry[28] = 854.318;
	PulseGainAry[29] = 854.671;
	PulseGainAry[30] = 855.028;
	PulseGainAry[31] = 855.391;
	PulseGainAry[32] = 855.758;
	PulseGainAry[33] = 856.129;
	PulseGainAry[34] = 856.504;
	PulseGainAry[35] = 856.882;
	PulseGainAry[36] = 857.263;
	PulseGainAry[37] = 857.647;
	PulseGainAry[38] = 858.033;
	PulseGainAry[39] = 858.421;
	PulseGainAry[40] = 858.811;
	PulseGainAry[41] = 859.202;
	PulseGainAry[42] = 859.594;
	PulseGainAry[43] = 859.987;
	PulseGainAry[44] = 860.38;
	PulseGainAry[45] = 860.774;
	PulseGainAry[46] = 861.166;
	PulseGainAry[47] = 861.559;
	PulseGainAry[48] = 861.95;
	PulseGainAry[49] = 862.34;
	PulseGainAry[50] = 862.728;
	PulseGainAry[51] = 863.114;
	PulseGainAry[52] = 863.497;
	PulseGainAry[53] = 863.878;
	PulseGainAry[54] = 864.256;
	PulseGainAry[55] = 864.631;
	PulseGainAry[56] = 865.001;
	PulseGainAry[57] = 865.368;
	PulseGainAry[58] = 865.73;
	PulseGainAry[59] = 866.088;
	PulseGainAry[60] = 866.441;
	PulseGainAry[61] = 866.788;
	PulseGainAry[62] = 867.129;
	PulseGainAry[63] = 867.464;
	PulseGainAry[64] = 867.793;
	PulseGainAry[65] = 868.115;
	PulseGainAry[66] = 868.429;
	PulseGainAry[67] = 868.732;
	PulseGainAry[68] = 869.027;
	PulseGainAry[69] = 869.313;
	PulseGainAry[70] = 869.594;
	PulseGainAry[71] = 869.868;
	PulseGainAry[72] = 870.138;
	PulseGainAry[73] = 870.406;
	PulseGainAry[74] = 870.67;
	PulseGainAry[75] = 870.934;
	PulseGainAry[76] = 871.198;
	PulseGainAry[77] = 871.463;
	PulseGainAry[78] = 871.731;
	PulseGainAry[79] = 872.002;
	PulseGainAry[80] = 872.277;
	PulseGainAry[81] = 872.558;
	PulseGainAry[82] = 872.846;
	PulseGainAry[83] = 873.141;
	PulseGainAry[84] = 873.446;
	PulseGainAry[85] = 873.761;
	PulseGainAry[86] = 874.086;
	PulseGainAry[87] = 874.428;
	PulseGainAry[88] = 874.789;
	PulseGainAry[89] = 875.168;
	PulseGainAry[90] = 875.562;
	PulseGainAry[91] = 875.971;
	PulseGainAry[92] = 876.393;
	PulseGainAry[93] = 876.825;
	PulseGainAry[94] = 877.267;
	PulseGainAry[95] = 877.717;
	PulseGainAry[96] = 878.173;
	PulseGainAry[97] = 878.634;
	PulseGainAry[98] = 879.098;
	PulseGainAry[99] = 879.564;
	PulseGainAry[100] = 880.029;
	PulseGainAry[101] = 880.493;
	PulseGainAry[102] = 880.953;
	PulseGainAry[103] = 881.409;
	PulseGainAry[104] = 881.858;
	PulseGainAry[105] = 882.299;
	PulseGainAry[106] = 882.73;
	PulseGainAry[107] = 883.15;
	PulseGainAry[108] = 883.557;
	PulseGainAry[109] = 883.95;
	PulseGainAry[110] = 884.326;
	PulseGainAry[111] = 884.685;
	PulseGainAry[112] = 885.025;
	PulseGainAry[113] = 885.343;
	PulseGainAry[114] = 885.639;
	PulseGainAry[115] = 885.912;
	PulseGainAry[116] = 886.164;
	PulseGainAry[117] = 886.401;
	PulseGainAry[118] = 886.626;
	PulseGainAry[119] = 886.84;
	PulseGainAry[120] = 887.043;
	PulseGainAry[121] = 887.236;
	PulseGainAry[122] = 887.422;
	PulseGainAry[123] = 887.601;
	PulseGainAry[124] = 887.774;
	PulseGainAry[125] = 887.943;
	PulseGainAry[126] = 888.109;
	PulseGainAry[127] = 888.274;
	PulseGainAry[128] = 888.437;
	PulseGainAry[129] = 888.602;
	PulseGainAry[130] = 888.768;
	PulseGainAry[131] = 888.938;
	PulseGainAry[132] = 889.111;
	PulseGainAry[133] = 889.291;
	PulseGainAry[134] = 889.477;
	PulseGainAry[135] = 889.672;
	PulseGainAry[136] = 889.876;
	PulseGainAry[137] = 890.09;
	PulseGainAry[138] = 890.316;
	PulseGainAry[139] = 890.555;
	PulseGainAry[140] = 890.811;
	PulseGainAry[141] = 891.084;
	PulseGainAry[142] = 891.375;
	PulseGainAry[143] = 891.68;
	PulseGainAry[144] = 892;
	PulseGainAry[145] = 892.333;
	PulseGainAry[146] = 892.678;
	PulseGainAry[147] = 893.034;
	PulseGainAry[148] = 893.399;
	PulseGainAry[149] = 893.773;
	PulseGainAry[150] = 894.153;
	PulseGainAry[151] = 894.54;
	PulseGainAry[152] = 894.931;
	PulseGainAry[153] = 895.325;
	PulseGainAry[154] = 895.722;
	PulseGainAry[155] = 896.12;
	PulseGainAry[156] = 896.518;
	PulseGainAry[157] = 896.915;
	PulseGainAry[158] = 897.309;
	PulseGainAry[159] = 897.699;
	PulseGainAry[160] = 898.084;
	PulseGainAry[161] = 898.463;
	PulseGainAry[162] = 898.835;
	PulseGainAry[163] = 899.198;
	PulseGainAry[164] = 899.551;
	PulseGainAry[165] = 899.894;
	PulseGainAry[166] = 900.224;
	PulseGainAry[167] = 900.541;
	PulseGainAry[168] = 900.843;
	PulseGainAry[169] = 901.13;
	PulseGainAry[170] = 901.399;
	PulseGainAry[171] = 901.654;
	PulseGainAry[172] = 901.898;
	PulseGainAry[173] = 902.131;
	PulseGainAry[174] = 902.355;
	PulseGainAry[175] = 902.571;
	PulseGainAry[176] = 902.78;
	PulseGainAry[177] = 902.983;
	PulseGainAry[178] = 903.18;
	PulseGainAry[179] = 903.373;
	PulseGainAry[180] = 903.563;
	PulseGainAry[181] = 903.75;
	PulseGainAry[182] = 903.936;
	PulseGainAry[183] = 904.122;
	PulseGainAry[184] = 904.308;
	PulseGainAry[185] = 904.495;
	PulseGainAry[186] = 904.685;
	PulseGainAry[187] = 904.878;
	PulseGainAry[188] = 905.076;
	PulseGainAry[189] = 905.279;
	PulseGainAry[190] = 905.488;
	PulseGainAry[191] = 905.705;
	PulseGainAry[192] = 905.93;
	PulseGainAry[193] = 906.164;
	PulseGainAry[194] = 906.409;
	PulseGainAry[195] = 906.664;
	PulseGainAry[196] = 906.94;
	PulseGainAry[197] = 907.241;
	PulseGainAry[198] = 907.567;
	PulseGainAry[199] = 907.914;
	PulseGainAry[200] = 908.283;
	PulseGainAry[201] = 908.669;
	PulseGainAry[202] = 909.072;
	PulseGainAry[203] = 909.49;
	PulseGainAry[204] = 909.92;
	PulseGainAry[205] = 910.361;
	PulseGainAry[206] = 910.811;
	PulseGainAry[207] = 911.268;
	PulseGainAry[208] = 911.729;
	PulseGainAry[209] = 912.193;
	PulseGainAry[210] = 912.659;
	PulseGainAry[211] = 913.123;
	PulseGainAry[212] = 913.585;
	PulseGainAry[213] = 914.042;
	PulseGainAry[214] = 914.492;
	PulseGainAry[215] = 914.934;
	PulseGainAry[216] = 915.365;
	PulseGainAry[217] = 915.783;
	PulseGainAry[218] = 916.187;
	PulseGainAry[219] = 916.575;
	PulseGainAry[220] = 916.944;
	PulseGainAry[221] = 917.293;
	PulseGainAry[222] = 917.62;
	PulseGainAry[223] = 917.923;
	PulseGainAry[224] = 918.2;
	PulseGainAry[225] = 918.449;
	PulseGainAry[226] = 918.668;
	PulseGainAry[227] = 918.855;
	PulseGainAry[228] = 919.009;
	PulseGainAry[229] = 919.127;
	PulseGainAry[230] = 919.207;
	PulseGainAry[231] = 919.265;
	PulseGainAry[232] = 919.317;
	PulseGainAry[233] = 919.364;
	PulseGainAry[234] = 919.407;
	PulseGainAry[235] = 919.446;
	PulseGainAry[236] = 919.481;
	PulseGainAry[237] = 919.512;
	PulseGainAry[238] = 919.541;
	PulseGainAry[239] = 919.567;
	PulseGainAry[240] = 919.591;
	PulseGainAry[241] = 919.614;
	PulseGainAry[242] = 919.635;
	PulseGainAry[243] = 919.656;
	PulseGainAry[244] = 919.676;
	PulseGainAry[245] = 919.697;
	PulseGainAry[246] = 919.718;
	PulseGainAry[247] = 919.74;
	PulseGainAry[248] = 919.763;
	PulseGainAry[249] = 919.788;
	PulseGainAry[250] = 919.815;
	PulseGainAry[251] = 919.845;
	PulseGainAry[252] = 919.879;
	PulseGainAry[253] = 919.915;
	PulseGainAry[254] = 919.956;
	PulseGainAry[255] = 920.001;
	PulseGainAry[256] = 920.051;
	PulseGainAry[257] = 920.106;
	PulseGainAry[258] = 920.166;
	PulseGainAry[259] = 920.248;
	PulseGainAry[260] = 920.364;
	PulseGainAry[261] = 920.509;
	PulseGainAry[262] = 920.679;
	PulseGainAry[263] = 920.869;
	PulseGainAry[264] = 921.074;
	PulseGainAry[265] = 921.291;
	PulseGainAry[266] = 921.514;
	PulseGainAry[267] = 921.74;
	PulseGainAry[268] = 921.963;
	PulseGainAry[269] = 922.18;
	PulseGainAry[270] = 922.385;
	PulseGainAry[271] = 922.59;
	PulseGainAry[272] = 922.808;
	PulseGainAry[273] = 923.037;
	PulseGainAry[274] = 923.274;
	PulseGainAry[275] = 923.519;
	PulseGainAry[276] = 923.768;
	PulseGainAry[277] = 924.021;
	PulseGainAry[278] = 924.274;
	PulseGainAry[279] = 924.527;
	PulseGainAry[280] = 924.778;
	PulseGainAry[281] = 925.023;
	PulseGainAry[282] = 925.263;
	PulseGainAry[283] = 925.493;
	PulseGainAry[284] = 925.714;
	PulseGainAry[285] = 925.922;
	PulseGainAry[286] = 926.115;
	PulseGainAry[287] = 926.293;
	PulseGainAry[288] = 926.453;
	PulseGainAry[289] = 926.592;
	PulseGainAry[290] = 926.709;
	PulseGainAry[291] = 926.812;
	PulseGainAry[292] = 926.908;
	PulseGainAry[293] = 926.998;
	PulseGainAry[294] = 927.083;
	PulseGainAry[295] = 927.163;
	PulseGainAry[296] = 927.238;
	PulseGainAry[297] = 927.31;
	PulseGainAry[298] = 927.378;
	PulseGainAry[299] = 927.443;
	PulseGainAry[300] = 927.505;
	PulseGainAry[301] = 927.565;
	PulseGainAry[302] = 927.624;
	PulseGainAry[303] = 927.682;
	PulseGainAry[304] = 927.739;
	PulseGainAry[305] = 927.796;
	PulseGainAry[306] = 927.854;
	PulseGainAry[307] = 927.913;
	PulseGainAry[308] = 927.972;
	PulseGainAry[309] = 928.034;
	PulseGainAry[310] = 928.098;
	PulseGainAry[311] = 928.165;
	PulseGainAry[312] = 928.236;
	PulseGainAry[313] = 928.309;
	PulseGainAry[314] = 928.385;
	PulseGainAry[315] = 928.462;
	PulseGainAry[316] = 928.542;
	PulseGainAry[317] = 928.622;
	PulseGainAry[318] = 928.704;
	PulseGainAry[319] = 928.787;
	PulseGainAry[320] = 928.87;
	PulseGainAry[321] = 928.954;
	PulseGainAry[322] = 929.038;
	PulseGainAry[323] = 929.121;
	PulseGainAry[324] = 929.203;
	PulseGainAry[325] = 929.285;
	PulseGainAry[326] = 929.366;
	PulseGainAry[327] = 929.445;
	PulseGainAry[328] = 929.522;
	PulseGainAry[329] = 929.597;
	PulseGainAry[330] = 929.67;
	PulseGainAry[331] = 929.74;
	PulseGainAry[332] = 929.807;
	PulseGainAry[333] = 929.871;
	PulseGainAry[334] = 929.932;
	PulseGainAry[335] = 929.988;
	PulseGainAry[336] = 930.041;
	PulseGainAry[337] = 930.089;
	PulseGainAry[338] = 930.135;
	PulseGainAry[339] = 930.177;
	PulseGainAry[340] = 930.216;
	PulseGainAry[341] = 930.252;
	PulseGainAry[342] = 930.287;
	PulseGainAry[343] = 930.319;
	PulseGainAry[344] = 930.35;
	PulseGainAry[345] = 930.379;
	PulseGainAry[346] = 930.407;
	PulseGainAry[347] = 930.435;
	PulseGainAry[348] = 930.462;
	PulseGainAry[349] = 930.488;
	PulseGainAry[350] = 930.515;
	PulseGainAry[351] = 930.542;
	PulseGainAry[352] = 930.57;
	PulseGainAry[353] = 930.598;
	PulseGainAry[354] = 930.628;
	PulseGainAry[355] = 930.66;
	PulseGainAry[356] = 930.693;
	PulseGainAry[357] = 930.728;
	PulseGainAry[358] = 930.766;
	PulseGainAry[359] = 930.807;
	PulseGainAry[360] = 930.85;
	PulseGainAry[361] = 930.897;
	PulseGainAry[362] = 930.947;
	PulseGainAry[363] = 931.001;
	PulseGainAry[364] = 931.06;
	PulseGainAry[365] = 931.122;
	PulseGainAry[366] = 931.194;
	PulseGainAry[367] = 931.28;
	PulseGainAry[368] = 931.378;
	PulseGainAry[369] = 931.491;
	PulseGainAry[370] = 931.616;
	PulseGainAry[371] = 931.754;
	PulseGainAry[372] = 931.904;
	PulseGainAry[373] = 932.067;
	PulseGainAry[374] = 932.243;
	PulseGainAry[375] = 932.43;
	PulseGainAry[376] = 932.63;
	PulseGainAry[377] = 932.841;
	PulseGainAry[378] = 933.064;
	PulseGainAry[379] = 933.298;
	PulseGainAry[380] = 933.543;
	PulseGainAry[381] = 933.799;
	PulseGainAry[382] = 934.067;
	PulseGainAry[383] = 934.344;
	PulseGainAry[384] = 934.633;
	PulseGainAry[385] = 934.931;
	PulseGainAry[386] = 935.299;
	PulseGainAry[387] = 935.784;
	PulseGainAry[388] = 936.37;
	PulseGainAry[389] = 937.042;
	PulseGainAry[390] = 937.781;
	PulseGainAry[391] = 938.573;
	PulseGainAry[392] = 939.401;
	PulseGainAry[393] = 940.248;
	PulseGainAry[394] = 941.098;
	PulseGainAry[395] = 941.936;
	PulseGainAry[396] = 942.743;
	PulseGainAry[397] = 943.506;
	PulseGainAry[398] = 944.206;
	PulseGainAry[399] = 944.828;
	PulseGainAry[400] = 945.355;
	PulseGainAry[401] = 945.771;
	PulseGainAry[402] = 946.115;
	PulseGainAry[403] = 946.437;
	PulseGainAry[404] = 946.739;
	PulseGainAry[405] = 947.021;
	PulseGainAry[406] = 947.286;
	PulseGainAry[407] = 947.535;
	PulseGainAry[408] = 947.768;
	PulseGainAry[409] = 947.989;
	PulseGainAry[410] = 948.197;
	PulseGainAry[411] = 948.395;
	PulseGainAry[412] = 948.583;
	PulseGainAry[413] = 948.764;
	PulseGainAry[414] = 948.938;
	PulseGainAry[415] = 949.107;
	PulseGainAry[416] = 949.273;
	PulseGainAry[417] = 949.437;
	PulseGainAry[418] = 949.599;
	PulseGainAry[419] = 949.763;
	PulseGainAry[420] = 949.928;
	PulseGainAry[421] = 950.097;
	PulseGainAry[422] = 950.27;
	PulseGainAry[423] = 950.45;
	PulseGainAry[424] = 950.638;
	PulseGainAry[425] = 950.834;
	PulseGainAry[426] = 951.041;
	PulseGainAry[427] = 951.26;
	PulseGainAry[428] = 951.492;
	PulseGainAry[429] = 951.739;
	PulseGainAry[430] = 952.002;
	PulseGainAry[431] = 952.283;
	PulseGainAry[432] = 952.582;
	PulseGainAry[433] = 952.902;
	PulseGainAry[434] = 953.238;
	PulseGainAry[435] = 953.586;
	PulseGainAry[436] = 953.946;
	PulseGainAry[437] = 954.319;
	PulseGainAry[438] = 954.706;
	PulseGainAry[439] = 955.106;
	PulseGainAry[440] = 955.52;
	PulseGainAry[441] = 955.948;
	PulseGainAry[442] = 956.391;
	PulseGainAry[443] = 956.849;
	PulseGainAry[444] = 957.322;
	PulseGainAry[445] = 957.812;
	PulseGainAry[446] = 958.317;
	PulseGainAry[447] = 958.84;
	PulseGainAry[448] = 959.379;
	PulseGainAry[449] = 959.936;
	PulseGainAry[450] = 960.51;
	PulseGainAry[451] = 961.103;
	PulseGainAry[452] = 961.715;
	PulseGainAry[453] = 962.345;
	PulseGainAry[454] = 962.995;
	PulseGainAry[455] = 963.665;
	PulseGainAry[456] = 964.354;
	PulseGainAry[457] = 965.065;
	PulseGainAry[458] = 965.796;
	PulseGainAry[459] = 966.548;
	PulseGainAry[460] = 967.323;
	PulseGainAry[461] = 968.119;
	PulseGainAry[462] = 968.938;
	PulseGainAry[463] = 969.78;
	PulseGainAry[464] = 970.645;
	PulseGainAry[465] = 971.534;
	PulseGainAry[466] = 972.447;
	PulseGainAry[467] = 973.384;
	PulseGainAry[468] = 974.346;
	PulseGainAry[469] = 975.333;
	PulseGainAry[470] = 976.346;
	PulseGainAry[471] = 977.385;
	PulseGainAry[472] = 978.45;
	PulseGainAry[473] = 979.542;
	PulseGainAry[474] = 980.662;
	PulseGainAry[475] = 981.808;
	PulseGainAry[476] = 982.983;
	PulseGainAry[477] = 984.186;
	PulseGainAry[478] = 985.524;
	PulseGainAry[479] = 987.093;
	PulseGainAry[480] = 988.878;
	PulseGainAry[481] = 990.865;
	PulseGainAry[482] = 993.04;
	PulseGainAry[483] = 995.388;
	PulseGainAry[484] = 997.895;
	PulseGainAry[485] = 1000.547;
	PulseGainAry[486] = 1003.328;
	PulseGainAry[487] = 1006.225;
	PulseGainAry[488] = 1009.222;
	PulseGainAry[489] = 1012.307;
	PulseGainAry[490] = 1015.463;
	PulseGainAry[491] = 1018.677;
	PulseGainAry[492] = 1021.935;
	PulseGainAry[493] = 1025.221;
	PulseGainAry[494] = 1028.521;
	PulseGainAry[495] = 1031.822;
	PulseGainAry[496] = 1035.108;
	PulseGainAry[497] = 1038.385;
	PulseGainAry[498] = 1041.669;
	PulseGainAry[499] = 1044.961;
	PulseGainAry[500] = 1048.259;
	return;
}

void InitGpio(void) //GPIOA，B口配置函数
{
	EALLOW;
	GpioMuxRegs.GPAMUX.all = 0x0000; //设置GPIOA
	GpioMuxRegs.GPADIR.all = 0x00ff;
	GpioMuxRegs.GPAQUAL.all = 0x0000;

	GpioMuxRegs.GPBMUX.all = 0x0000; //设置GPIOB
	GpioMuxRegs.GPBDIR.all = 0xffff;
	GpioMuxRegs.GPBQUAL.all = 0x0000;
	EDIS;

	EALLOW;

	// 在这里插入初始化函数的代码
	GpioMuxRegs.GPFMUX.bit.SCITXDA_GPIOF4 = 1; //设置SCIA的发送引脚
	GpioMuxRegs.GPFMUX.bit.SCIRXDA_GPIOF5 = 1; //设置SCIA的接收引脚
	GpioMuxRegs.GPFMUX.bit.MFSRA_GPIOF11 = 0;  //通用数字IO口
	GpioMuxRegs.GPFDIR.bit.GPIOF11 = 1;		   //配置为输出口

	EDIS;
	return;
}

void InitSci(void)
{
	SciaRegs.SCICCR.bit.STOPBITS = 0;
	SciaRegs.SCICCR.bit.PARITYENA = 0;
	SciaRegs.SCICCR.bit.LOOPBKENA = 0;
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
	SciaRegs.SCICCR.bit.SCICHAR = 7;
	SciaRegs.SCICTL1.bit.TXENA = 1; //SCIA模块的发送使能
	SciaRegs.SCICTL1.bit.RXENA = 1; //SCIA模块的接收使能
	SciaRegs.SCICTL1.bit.RXERRINTENA=1; //使能错误接收中断
	SciaRegs.SCIHBAUD = 0x0;
	SciaRegs.SCILBAUD = 2;
	/*
	 * SCILBAUD = 2, 1.25M; SCILBAUD = 32, 115200
	*/
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
	SciaRegs.SCICTL1.bit.SWRESET = 1;

	/*    EALLOW;
//  SciaRegs.SCICTL1.bit.SWRESET=0;
    SciaRegs.SCICCR.bit.STOPBITS=0;        //1位停止位
    SciaRegs.SCICCR.bit.PARITYENA=0;       //禁止极性功能
    SciaRegs.SCICCR.bit.LOOPBKENA=0;       //禁止回送测试模式功能
//  SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //空闲线模式
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE=1;   //address模式
    SciaRegs.SCICCR.bit.SCICHAR=7;         //8位数据位

    SciaRegs.SCICTL1.bit.TXENA=1;          //SCIA模块的发送使能
    SciaRegs.SCICTL1.bit.RXENA=1;          //SCIA模块的接收使能

    // 新增
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    SciaRegs.SCIHBAUD=0x0;
    SciaRegs.SCILBAUD=32;                //波特率为115200
    //SciaRegs.SCILBAUD=0xF3; // 19200

    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFTX.bit.SCIFFENA=1;

    SciaRegs.SCIFFRX.bit.RXFFOVF=0;      //接收FIFO没有溢出
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;    //对RXFFOVF标志位没有影响
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;  //重新使能接收FIFO的操作
    SciaRegs.SCIFFRX.bit.RXFIFST=0;      //接收FIFO队列为空
    SciaRegs.SCIFFRX.bit.RXFFINT=0;      //没有产生接收中断
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   //清除接收中断标志位
    SciaRegs.SCIFFRX.bit.RXFFIENA=1;     //使能FIFO接收中断
    SciaRegs.SCIFFRX.bit.RXFFIL=1;       //FIFO接收中断级别为8.也就是说当接收FIFO中有8个字符时发生中断

    SciaRegs.SCICTL1.bit.SWRESET=1;        //重启SCI
    EDIS;*/
}

void InitFPGA(void)
{
	GpioDataRegs.GPADAT.bit.GPIOA3 = 0;
	Delay(20);
	GpioDataRegs.GPADAT.bit.GPIOA3 = 1;
	Delay(50);
	GpioDataRegs.GPADAT.bit.GPIOA3 = 0;
	Delay(200);
	RelayClose(0xFFFF);     //所有继电器断开
	return;
}

void InitVariables(void)
{
	// 初始化表入口指针
	ConfigTableEntry = (ConfigTableEntry_t*)ADDR_CONFIG_TABLE_START;
	TuningTableEntry = (TuningTableEntry_t*)ADDR_TUNING_TABLE_START;

	// PAPSEntry
	PAPSEntry.last_well_mode = 0;

	EventBoardState = IDLE_STAT;

	DENum = 0;
	PhaseFlag = POSITIVE;
	CycleFlag = CLEAR;

	SendTableFlag = CLEAR; //send table flag:发送参数表标志，为1时发送参数表

	SingleModeFlag = CLEAR;
	PPModeFlag = CLEAR;
	PPDIFModeFlag = CLEAR;
	PPT1ModeFlag = CLEAR;
	PPOFTWModeFlag = CLEAR;
	PPShortModeFlag = CLEAR;
	TuningModeFlag = CLEAR;
	ScanModeFlag = CLEAR;
	ScaleModeFlag = CLEAR;
	HoleModeFlag = CLEAR;
	PulseAcqFlag = CLEAR;

	WorkMode = 8; // 扫频模式

	SendTableID = 0x2; // 刻度参数表ID

	DUMP_SUSTAIN_DIS = USER_DISABLE;
	INV_TURN_DIS = USER_DISABLE;
	DumpSustainFlag = CLEAR;
	InverseTurnFlag = CLEAR;

	PAPSEntry.STKLEV  = 0;

	return;
}

void LoadParaDis(void)
{
	STATE1MS_LOAD_DIS = USER_DISABLE;

	CAL_DATALOAD_DIS = USER_DISABLE;
	DDS_DATALOAD_DIS = USER_DISABLE;
	SCAN_LOAD_DIS = USER_DISABLE;
	SIGNAL_LOAD_DIS = USER_DISABLE;

	NSTATE_LOAD_DIS = USER_DISABLE;
	NRAM_LOAD_DIS = USER_DISABLE;

	PLUSE_LOAD_DIS = USER_DISABLE;
	BRIDGE_LOAD_DIS = USER_DISABLE;
	DUMP_LOAD_DIS = USER_DISABLE;
	SCALE_LOAD_DIS = USER_DISABLE;
	return;
}
