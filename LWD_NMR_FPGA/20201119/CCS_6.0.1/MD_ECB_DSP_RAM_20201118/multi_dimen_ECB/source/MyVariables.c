//###########################################################################
//
// FILE:	MyVariables.c
//
// TITLE:	User variables defination.
//
// NOTES:   CpuTimer1 and CpuTimer2 are reserved for use with DSP BIOS and
//          other realtime operating systems.  
//
//          Do not use these two timers in your application if you ever plan
//          on integrating DSP-BIOS or another realtime OS. 
//
//          For this reason, the code to manipulate these two timers is
//          commented out and not used in these examples.
//           
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H  | Changes since previous version (v.58 Alpha)
//      |             |      | Removed some incorrect parameters in the timer
//      |             |      | setup that are not available on this device
//###########################################################################

#include "DSP281x_Device.h"
#include "IQmathlib.h"
#include "MyDefine.h"

//Quantity variables defination
	//Used by state 1 ms machine
Uint16 HVState;  //state of HV:高压状态
Uint32 PulseCycle;  //
Uint32 MDumpTime; 
Uint32 SDumpTime; 
Uint32 CutTime;     
Uint16 CutTimeLow;
Uint16 CutTimeHi;
	//Used by send parameter table
Uint16 SendTableFlag;	//send table flag:发送参数表标志，为1时发送参数表
Uint32 SendCnt;			//send table counter:发送表时用到的计数器，指示已发送了多少数据
Uint16 ZeroCnt;
Uint16 DENum;
Uint16 PhaseFlag;		//phase flag:90度发射正反相标志
	//Used by scan and miniscan mode
Uint16 ScanModeFlag;	//scan mode flag：扫频模式标志，为1时要进入扫频模式
Uint16 StepFreq;		//step freqency:扫频时的步进频率数
Uint16 SiglAcqPrdNum;	//signal acquisition period number:回波信号采集周期数
Uint16 SiglAcqFreqTim;	//signal acquisition freqency times:回波信号采集频率相对于回波信号频率的倍数
Uint16 NoiseAcqTim;		//noise acquisition time：噪声采集时间长度
Uint16 NoiseAcqFreq;	//noise acquisition freqency:噪声采集时的采集频率
Uint16 ScanTE;			//te in scan mode:扫频时的te值
Uint16 ScaleTe;			//te in scale mode:主刻度、孔隙度刻度时的回波间隔
Uint16 ScaleNe;			//ne in scale mode:主刻度、孔隙度刻度时的回波个数
Uint16 ScanSignalNum;	//number of signal in scan mode:扫频时的信号采集点数 
Uint16 BandCnt;			//band counter:扫频时的频带计数器
Uint16 ScaleCnt;		//scale counter:刻度时刻度次数计数器
Uint16 MiniFreqCnt;		//freqency counter in mini freqency:迷你扫频时的扫频次数计数器
Uint16 FreqScan;		//scaning frequency
Uint16 MiniFreq;
Uint16 NTimeDec;		//noise acquisition time 
Uint16 STimeDec;		//signal acquisition time in scan mode

Uint16 SaveCnt;

Uint16 CycleFlag;
Uint16 DumpSustainFlag;
Uint16 DSTTimeOne;
	//Used in noise acquisition mode
Uint16 NoiseDivFreq;
Uint16 NoiseDivNum;	
Uint16 NoiseAcqNum;		//number of noise acquisition data 
Uint16 NoiseAcqCnt;
Uint32 NoiseSum;		// sum of noise data
//_iq NoiseSumIQ;
_iq NoiseAveShiftIQ;    //噪声数值的均值（有2v偏置）
_iq NoiseAveIQ;			//噪声数值的均值
_iq NoiseCalNumIQ;		//计算的噪声数据个数
_iq NoiseMaxValIQ;		//最大噪声
_iq NoiseOfsIQ;			//噪声偏差
_iq NoiseOfsAbsIQ;
_iq NoiseSqrAveIQ;
_iq3 NoiseOfsIQ3;
_iq3 NoiseSquSumIQ3;	//偏差平方和,即方差
_iq3 NoiseSquAveIQ3;	//方差均值
	//Used by DDS configuration
Uint32 DDSFreq;			//dds需要配置的频率
Uint16 CalDivData;
Uint32 DDSMid1;
Uint32 DDSMid2;
Uint32 DDSMid3;
Uint32 DDSMid4;
Uint32 DDSMid5;
Uint32 DDSMid6;
Uint32 DDSMid7;
Uint32 DDSCfgWords;
double DDSRefItg;
double DDSRefDcm;
Uint16 DDSCfgHi;
Uint16 DDSCfgLow;
	 //Used in signal calculation through DPSD algorithm
Uint16 AdderCnt;
int32 SinOne;           //计算用
int32 SinTwo;
int32 SinThree;
int32 SinFour;
int32 CosOne;
int32 CosTwo;
int32 CosThree;
int32 CosFour;
int32 CosFive;
_iq SinSumIQ;
_iq CosSumIQ;
Uint16 SignalCalNum;	//number of signal data in calculation
_iq SinAveIQ;
_iq CosAveIQ;
_iq SignalAmpIQ;
_iq SignalPhaIQ;
	//Used in dump parameter calculation
Uint16 DumpPara1;
Uint16 DumpPara2;
Uint16 DumpPara3;
Uint16 DumpPara4;
Uint16 DumpPara5;
Uint16 DumpPara6;
Uint16 MainDumpTime;     //主泄放时间
	//Used in in-out-bridge parameter calculation
Uint16 ScaleDDSDiv;		//刻度激励用dds分频系数
Uint16 HalfFreqNum;     //起震计数值
Uint16 BriWidthData;	//内外桥宽度计数值（注意数据格式）
Uint16 BriMid;
	//Used in pulse acquisition mode
Uint16 MatAcqFreqTim;	//维护时发射波形采集频率倍数
Uint16 MatTime;			//维护时发射波形采集时间段长度
Uint16 MatFreqSel;
Uint16 MatFreq;
Uint16 PulseAcqFlag;
Uint16 PulseTime;
Uint16 PulseNum;
Uint16 PulseDivNum;
Uint16 PulseMid4;
float PulseMid1;
float PulseMid2;
float PulseMid3;
Uint16 PulseDataCnt;
	//Used by PD state machine parameters 
Uint16 PdPara1;
Uint16 PdPara2;
Uint16 PdPara3;
Uint16 Pd90Time;
Uint16 Pd180Time;
	//Used in pulse data calculation 
int16 PulseGain;
_iq PulseGainIQ;
Uint16 StripBuf;
double PulseSum;
double PulseAve;
Uint16 PulseBuf;
double PulseRec;
_iq PulseRecIQ;
Uint16 PulseCalNum;
Uint16 PulseReadBuf;
	//Used in single frequency DE or CPMG sequence
Uint16 SingleModeFlag;
Uint16 DEMn;
Uint16 WidthCnt;
Uint16 HegtWidth;		//回波发射脉冲宽度寄存器数值
Uint16 SftWinWidth;		//采集窗时间滑动寄存器
Uint16 DCFreqSel;
Uint16 DCPulseWidth;
Uint16 DCTes;
Uint16 DCNe;
Uint16 DCMn;
Uint16 DCm;
Uint16 ScaleM;
Uint16 Ne;
Uint16 ScaleMn;
	//Used by SCALE state machine parameters calculation
Uint32 Pulse90Width;
Uint32 Pulse180Width;
Uint32 Pulse180WidthHalf;
float EchoMid1;
float EchoMid2;
float EchoMid3;
float EchoMid4;
Uint16 DCWorkFreq;
Uint16 EchoAcqTime;      //采集时间
Uint16 EchoAcqTimeFHalf;
Uint16 EchoAcqTimeBHalf;

Uint16 InverseTurnFlag;

float TNMid1;
float TNMid2;
Uint32 TNTime;
Uint32 Tes;           //短te时间
Uint32 Tel;
Uint32 TesCmp;         // 取整的短te
Uint32 TelCmp;         //取整的长te

Uint32 CmpTesHalf;		//cmp:compare
Uint32 CmpTelHalf;   //长TE下TEL_C
Uint32 Cmp90;
Uint32 CmpI90;
Uint32 Cmp180FHalf;
Uint32 Cmp180BHalf;

Uint32 Cut90Time;    //90度隔离时间
Uint16 Cut90TimeLow;
Uint16 Cut90TimeHi;
Uint32 CutI90Time;    //反90度隔离时间
Uint16 CutI90TimeLow;
Uint16 CutI90TimeHi;
Uint32 Open180LTime;	//长TE下的DEC打开时间  
Uint16 Open180LTimeMS; 
Uint16 Open180LTimeLow;  
Uint16 Open180LTimeHi;
Uint32 Cut180LTime;     //长TE下的180隔离时间
Uint16 Cut180LTimeLow;
Uint16 Cut180LTimeHi;
Uint32 Cut180STime;
Uint16 Cut180STimeLow;
Uint16 Cut180STimeHi;
Uint32 Open180STime;	//长TE下的DEC打开时间   
Uint16 Open180STimeLow;  
Uint16 Open180STimeHi;

Uint16 EchoAcqNum;   //echo采集点数

Uint32 TesCCheck;
Uint32 TelCCheck;
Uint16 P90PrdNum;
Uint16 P180PrdNum;

Uint16 Acq90Num;     //90度激励采集点数
Uint16 Acq180Num;    //180激励采集点数
Uint16 Strip90Num;     //90度激励舍去点数
Uint16 Strip180Num;     //180度激励舍去点数
	//Used by SD state machine parameters 
Uint16 SdAcqNum1;
Uint16 SdAcqNum2;
Uint16 SdAcqNum3;
Uint32 SdAcqNum4;
Uint32 SdAcqNum5;
Uint32 SdAcqNum6;
Uint32 SdAcqNum7;
Uint16 SdAcqNum4Low;
Uint16 SdAcqNum4Hi;
Uint16 SdAcqNum5Low;
Uint16 SdAcqNum5Hi;
Uint16 SdAcqNum6Low;
Uint16 SdAcqNum6Hi;
Uint16 SdAcqNum7Low;
Uint16 SdAcqNum7Hi;
float SdAcqTimeMid1;
float SdAcqTimeMid2;
float SdAcqTimeMid3;

Uint16 StoreCnt;
_iq PulseAmpCrtIQ;
Uint32 Pulse90StoreAddr;
Uint32 PulseF180StoreAddr;
Uint32 PulseL180StoreAddr;
Uint32 EchoStorAddr;

Uint16 McbspRcvBuf;
Uint16 DownTableFlag;
Uint16 WorkMode;
Uint16 PP6ModeFlag;
Uint16 ScaleModeFlag;
Uint16 HoleModeFlag;
Uint16 ST2DFlag;
Uint16 DT2DFlag;
Uint16 MT2DFlag;
Uint16 ST1T2Flag;
Uint16 DT1T2Flag;
Uint16 ST12DFlag;
Uint16 DT12DFlag;
Uint16 DFT1T2DFlag;
	//Used when changing table
Uint16 ChangeTableBuf;
Uint16 CaseBuffer;
Uint16 TableChgCnt;
Uint16 ChgTable995Flag;
Uint16 ChgTable996Flag;
Uint16 ChgTable999Flag;
Uint16 ChgTable99AFlag;



Uint16 ToMSFreq;		//frequency transferred to miniscan() function
Uint32 ToMSNoiseAddr;	//noise-store address transferred to miniscan() function
Uint32 ToMSSignalAddr;	//signal-store address transferred to miniscan() function

Uint16 ReadTableBuf;
Uint16 ZeroOne;
	//Used in PP6 mode
Uint16 PP6FreqSelLow;
Uint16 PP6FreqSelHi;         
Uint16 PP6FTe14A2356DE;
Uint16 PP6FTe1346C;
Uint16 PP6FNe1346C;
Uint16 PP6FNe2356DE;
Uint16 PP6FNe14A;
Uint16 PP6FTw1346C;
Uint16 PP6FNRept14C;
Uint16 PP6FNRept36C;
Uint16 PP6FCmp1;
Uint16 PP6FCmp2;
Uint16 PP6FTime36DWait;
Uint32 DataTotalNum;
Uint16 EchoNum;
Uint32 PP6FCnt;

Uint16 FreqNum2;
Uint16 MiniCycCnt1;
Uint16 MiniCycCnt2;
Uint16 MiniCycCnt3;
Uint16 MiniNoiseMax;
Uint16 MiniBuf;
	//Used in OIL3 mode
Uint16 Oil3ModeFlag;
Uint16 Oil3FreqSel;
Uint16 Oil3Te1C2C3CDEF;
Uint16 Oil3Ne123C;
Uint16 Oil3Ne3D;
Uint16 Oil3Ne3E;
Uint16 Oil3Ne3F;
Uint16 Oil3Tw123C;
Uint16 Oil3Tw3D;
Uint16 Oil3Tw3E;
Uint16 Oil3Tw3F;
Uint16 Oil3NRept123C;
Uint16 Oil3NRept3D;
Uint16 Oil3NRept3E;
Uint16 Oil3NRept3F;
Uint16 Oil3Cnt;
	//Used in GAS6 mode
Uint16 Gas6ModeFlag;
Uint16 Gas6FreqSelLow;
Uint16 Gas6FreqSelHi;
Uint16 Gas6Te123456C24DE;
Uint16 Gas6Ne123456C24DE;
Uint16 Gas6Tw123456C;
Uint16 Gas6Tw24D;
Uint16 Gas6Tw24E;
Uint16 Gas6NRept24D;
Uint16 Gas6NRept24E;
Uint16 Gas6NRept1234C;
Uint16 Gas6NRept56C;
Uint16 Gas6Cnt;
	//Used in ST2D , DT2D and MT2D mode
Uint16 T2DCPMGTwA;
Uint16 T2DDETwA;
Uint16 T2DCBWTwA;
Uint16 T2DDETesA;
Uint16 T2DCBWTeAB;
Uint16 T2DDCTesA;
Uint16 T2DCBWNreptA;
Uint16 T2DCPMGNeA;
Uint16 T2DDENeA;
Uint16 T2DCBWNeA;
Uint16 T2DDEmn;
Uint16 T2DDEm;
Uint16 T2DCPMGTwB;
Uint16 T2DDETwB;
Uint16 T2DCBWTwB;
Uint16 T2DDETesB;
Uint16 T2DDETel1B;
Uint16 T2DDETel2B;
Uint16 T2DDETel3B;
Uint16 T2DDETel4B;
Uint16 T2DDETel5B;
Uint16 T2DDETel6B;
Uint16 T2DCBWNreptB;
Uint16 T2DCPMGNeB;
Uint16 T2DDENeB;
Uint16 T2DCBWNeB;
Uint16 T2DCnt;
Uint16 T2DFreqSel;
Uint16 T2DTwMid1;
Uint16 T2DTwMid2;
Uint16 ST2DMiniNum;

Uint32 MiniStorAddr1;
Uint32 MiniStorAddr2;
Uint32 MiniStorAddr3;
Uint32 MiniStorAddr4;
Uint32 MiniStorAddr5;
Uint32 MiniStorAddr6;
	//Used in MT2D mode
Uint16 T2DCBWTeA;
Uint16 T2DDETwBC;
Uint16 T2DDCTes;
Uint16 T2DDENeBC;
	//Used in T1T2 mode
Uint16 T1T2FreqSel;
Uint16 T1T2Cnt;
Uint16 T1T2CPMGTe;
Uint16 T1T2CBWTe;
	//Used in T1T2D mode
Uint16 T12DCPMGTw1AB;
Uint16 T12DCPMGTw2AB;
Uint16 T12DCPMGTw8AB;
Uint16 T12DCPMGTw9AB;
Uint16 T12DCPMGTw0AB;
Uint16 T12DDETwAB;
Uint16 T12DCBWTwAB;
Uint16 T12DCBWTeAB;
Uint16 T12DTesAB;
Uint16 T12DNRept890AB;
Uint16 T12DCBWNReptAB;
Uint16 T12DCPMGNe1AB;
Uint16 T12DCPMGNe2AB;
Uint16 T12DCPMGNe8AB;
Uint16 T12DCPMGNe9AB;
Uint16 T12DCPMGNe0AB;
Uint16 T12DDENeAB;
Uint16 T12DCBWNeAB;
Uint16 T12DDEmnAB;
Uint16 T12DDEmAB;
Uint16 T12DFreqSel;
Uint16 T12DCnt;

	//Used in DFT1T2D mode
Uint16 DFT1T2D_TW_A1B1; //default: 9800+
Uint16 DFT1T2D_TW_A2B2;
Uint16 DFT1T2D_TW_A8B8;
Uint16 DFT1T2D_TW_A9B9;
Uint16 DFT1T2D_TW_A10B10;
Uint16 DFT1T2D_TW_DE;
Uint16 DFT1T2D_TW_CBW;
Uint16 DFT1T2D_TE_CBW;
Uint16 DFT1T2D_TES_DE_T2_T1;
Uint16 DFT1T2D_TEL1_DE;
Uint16 DFT1T2D_TEL2_DE;
Uint16 DFT1T2D_TEL3_DE;
Uint16 DFT1T2D_TEL4_DE;
Uint16 DFT1T2D_TEL5_DE;
Uint16 DFT1T2D_NREPT_CBW;
Uint16 DFT1T2D_NE_A1B1;
Uint16 DFT1T2D_NE_A2B2;
Uint16 DFT1T2D_NE_A8B8;
Uint16 DFT1T2D_NE_A9B9;
Uint16 DFT1T2D_NE_A10B10;
Uint16 DFT1T2D_NE_DE;
Uint16 DFT1T2D_NE_CBW;
Uint16 DFT1T2D_group_DE;
Uint16 DFT1T2D_DE_TEL_num;
Uint16 DFT1T2D_cnt ;
Uint16 DFT1T2DFreqSel;

	//Used in PPLOIL6F mode
Uint16 PPLOIL6NRept123456C;
Uint16 PPLOIL6NRept24D;
Uint16 PPLOIL6NRept24E;
Uint16 PPLOIL6FNe156A1B;
Uint16 PPLOIL6FNe23AB;
Uint16 PPLOIL6FNe4AB;
Uint16 PPLOIL6FNe24DE;
Uint16 PPLOIL6FNe123456C;
Uint16 PPLOIL6F_TE_156A1B;
Uint16 PPLOIL6F_TE_23AB;
Uint16 PPLOIL6F_TE_4AB;
Uint16 PPLOIL6F_TE_123456C;
Uint16 PPLOIL6F_TE_2DE;
Uint16 PPLOIL6F_TE_4DE;
Uint16 PPLOIL6FTw1234B;
Uint16 PPLOIL6FTw24D;
Uint16 PPLOIL6FTw24E;
Uint16 PPLOIL6FTw123456C;
Uint16 PPLOIL6FCnt;
Uint16 PPLOIL6FFlag;
Uint16 PPLOIL6FFreqSelLow;
Uint16 PPLOIL6FFreqSelHi;
Uint16 PPLOIL6FFreqSel;

//Used in PP3 mode
Uint16 PP3FNRept1C;
Uint16 PP3FNe1A;
Uint16 PP3FNe1C;
Uint16 PP3FNe23DE;
Uint16 PP3FTe1A23DE;
Uint16 PP3FTe1C;
Uint16 PP3FTw1C;
Uint16 PP3FCnt;
Uint16 flag_pp3;
Uint16 PP3FreqSelLow;
Uint16 PP3FreqSelHi;
Uint16 PP3FreqSel;

//Used in FBW2F mode
Uint16 FBW2FNRept12C;
Uint16 FBW2FNe12B;
Uint16 FBW2FNe12C;
Uint16 FBW2FTe12B;
Uint16 FBW2FTe12C;
Uint16 FBW2FTw12C;
Uint16 FBW2FCnt;
Uint16 FBW2FFlag;
Uint16 FBW2FFreqSelLow;
Uint16 FBW2FFreqSelHi;
Uint16 FBW2FFreqSel;

//Used in PPHOIL6F mode
Uint16 PPHOIL6FNRept1234C;
Uint16 PPHOIL6FNRept5C;
Uint16 PPHOIL6FNRept6C;
Uint16 PPHOIL6FNe12345C;
Uint16 PPHOIL6FNe246A;
/*
Uint16 PPHOIL6FNe1B;
Uint16 PPHOIL6FNe2B;
Uint16 PPHOIL6FNe3B;
Uint16 PPHOIL6FNe4B;
Uint16 PPHOIL6FNe5B;
Uint16 PPHOIL6FNe6B;
*/
Uint16 PPHOIL6FNe6C;
Uint16 PPHOIL6F_TE_1B;
Uint16 PPHOIL6F_TE_123456C;
Uint16 PPHOIL6F_TE_246A;
Uint16 PPHOIL6F_TE_3B;
Uint16 PPHOIL6F_TE_2B;
Uint16 PPHOIL6F_TE_5B;
Uint16 PPHOIL6F_TE_4B;
Uint16 PPHOIL6F_TE_6B;
Uint16 PPHOIL6FTw123456C;
Uint16 PPHOIL6FFlag;
Uint16 PPHOIL6FCnt;
Uint16 PPHOIL6FFreqSelLow;
Uint16 PPHOIL6FFreqSelHi;
Uint16 PPHOIL6FFreqSel;

//Used in GAS6_2 mode
Uint16 Gas6_2ModeFlag;
Uint16 Gas6_2FreqSelLow;
Uint16 Gas6_2FreqSelHi;
Uint16 Gas6_2Te123456C24DE;
Uint16 Gas6_2Ne123456C24DE;
Uint16 Gas6_2Tw123456C;
Uint16 Gas6_2Tw24D;
Uint16 Gas6_2Tw24E;
Uint16 Gas6_2NRept24D;
Uint16 Gas6_2NRept24E;
Uint16 Gas6_2NRept123456C;
Uint16 Gas6_2Cnt;

//Used in PPHOIL6F_2 mode
Uint16 PPHOIL6F_2NRept123456C;
Uint16 PPHOIL6F_2Ne12346C;
Uint16 PPHOIL6F_2Ne246A;
/*
Uint16 PPHOIL6F_2Ne1B;
Uint16 PPHOIL6F_2Ne2B;
Uint16 PPHOIL6F_2Ne3B;
Uint16 PPHOIL6F_2Ne4B;
Uint16 PPHOIL6F_2Ne5B;
Uint16 PPHOIL6F_2Ne6B;
*/
Uint16 PPHOIL6F_2Ne5C;
Uint16 PPHOIL6F_2_TE_1B;
Uint16 PPHOIL6F_2_TE_123456C;
Uint16 PPHOIL6F_2_TE_246A;
Uint16 PPHOIL6F_2_TE_3B;
Uint16 PPHOIL6F_2_TE_2B;
Uint16 PPHOIL6F_2_TE_5B;
Uint16 PPHOIL6F_2_TE_4B;
Uint16 PPHOIL6F_2_TE_6B;
Uint16 PPHOIL6F_2Tw123456C;
Uint16 PPHOIL6F_2Flag;
Uint16 PPHOIL6F_2Cnt;
Uint16 PPHOIL6F_2FreqSelLow;
Uint16 PPHOIL6F_2FreqSelHi;
Uint16 PPHOIL6F_2FreqSel;

//Used in P3D6FModeTop mode
Uint16 P3D6F_TE_1A;
Uint16 P3D6F_TE_2A;
Uint16 P3D6F_TE_3A;
Uint16 P3D6F_TE_4A;
Uint16 P3D6F_TE_5B;
Uint16 P3D6F_TE_6B;
Uint16 P3D6F_TE_1C;
Uint16 P3D6F_TE_2D;
Uint16 P3D6F_TE_3E;
Uint16 P3D6F_TE_4F;
Uint16 P3D6F_TE_5F;
Uint16 P3D6F_TE_6F;
Uint16 P3D6FNe1A;
Uint16 P3D6FNe2A;
Uint16 P3D6FNe3A;
Uint16 P3D6FNe4A;
Uint16 P3D6FNe5B;
Uint16 P3D6FNe6B;
Uint16 P3D6FNe1C;
Uint16 P3D6FNe2D;
Uint16 P3D6FNe3E;
Uint16 P3D6FNe4F;
Uint16 P3D6FNe5F;
Uint16 P3D6FNe6F;
Uint16 P3D6FTw1C;
Uint16 P3D6FTw2D;
Uint16 P3D6FTw3E;
Uint16 P3D6FTw4F;
Uint16 P3D6FTw5F;
Uint16 P3D6FTw6F;
Uint16 P3D6FNRept1C;
Uint16 P3D6FNRept2D;
Uint16 P3D6FNRept3E;
Uint16 P3D6FNRept4F;
Uint16 P3D6FNRept5F;
Uint16 P3D6FFlag;
Uint16 P3D6FCnt;
Uint16 P3D6FFreqSelLow;
Uint16 P3D6FFreqSelHi;
Uint16 P3D6FFreqSel;

//Used in P3D6FModeTop mode
Uint16 HRT1T22FMode_TW_A1;
Uint16 HRT1T22FMode_TW_B1;
Uint16 HRT1T22FMode_TW_B2;
Uint16 HRT1T22FMode_TW_B3;
Uint16 HRT1T22FMode_TW_B4;
Uint16 HRT1T22FMode_TW_B5;
Uint16 HRT1T22FMode_TW_B6;
Uint16 HRT1T22FMode_TW_B7;
Uint16 HRT1T22FMode_TE_A1;
Uint16 HRT1T22FMode_TE_B1;
Uint16 HRT1T22FMode_TE_B2;
Uint16 HRT1T22FMode_TE_B3;
Uint16 HRT1T22FMode_TE_B4;
Uint16 HRT1T22FMode_TE_B5;
Uint16 HRT1T22FMode_TE_B6;
Uint16 HRT1T22FMode_TE_B7;
Uint16 HRT1T22FMode_NE_A1;
Uint16 HRT1T22FMode_NE_B1;
Uint16 HRT1T22FMode_NE_B2;
Uint16 HRT1T22FMode_NE_B3;
Uint16 HRT1T22FMode_NE_B4;
Uint16 HRT1T22FMode_NE_B5;
Uint16 HRT1T22FMode_NE_B6;
Uint16 HRT1T22FMode_NE_B7;
Uint16 HRT1T22FMode_NREPT_B2;
Uint16 HRT1T22FMode_NREPT_B3;
Uint16 HRT1T22FMode_NREPT_B4;
Uint16 HRT1T22FMode_NREPT_B5;
Uint16 HRT1T22FMode_NREPT_B6;
Uint16 HRT1T22FMode_NREPT_B7;
Uint16 HRT1T22FFlag;
Uint16 HRT1T22FCnt;
Uint16 HRT1T22FFreqSel;


	//Array variables defination
float PulseGainAry[501];
Uint16 FreqAry[BAND_NUM];
Uint16 RelayAry[BAND_NUM];

Uint16 AdderLowAry[11];
Uint32 AdderResAry[11];
Uint16 NoiseDataAry[512];

Uint16 NintyWidthAry[9];

Uint16 PP6FMiniNumAry[6];
Uint16 Oil3MiniNumAry[3];
Uint16 Gas6FMiniNumAry[6];
Uint16 Gas6_2FMiniNumAry[6];
Uint16 PPLOIL6FMiniNumAry[6];
Uint16 PP3FMiniNumAry[3];
Uint16 FBW2FMiniNumAry[2];
Uint16 PPHOIL6FMiniNumAry[6];
Uint16 PPHOIL6F_2MiniNumAry[6];
Uint16 P3D6FMiniNumAry[6];
Uint16 HRT1T22FMiniNumAry[2];
int32 MiniAddAry[12];

Uint16 PP6FreqSelAry[7];
Uint16 Oil3FreqSelAry[4];
Uint16 Gas6FreqSelAry[7];
Uint16 Gas6_2FreqSelAry[7];
Uint16 PPLOIL6FFreqSelAry[7];
Uint16 PP3FreqSelAry[4];
Uint16 FBW2FFreqSelAry[3];
Uint16 PPHOIL6FFreqSelAry[7];
Uint16 PPHOIL6F_2FreqSelAry[7];
Uint16 P3D6FFreqSelAry[7];
Uint16 HRT1T22FFreqSelAry[3];

Uint16 T2DFreqSelAry[4];
Uint16 T2DDETelAAry[7];
Uint16 T2DDETelBAry[7];
Uint16 T2DDETelCAry[4];
Uint16 DFT1T2DFreqSelAry[3];
Uint16 DT2DMiniNumAry[3];
Uint16 MT2DMiniNumAry[3];
Uint16 DFT1T2DMiniNumAry[3];

Uint16 T12DTelABAry[5];
Uint16 T12DMiniNumAry[3];

	//Used in ST1T2 mode
Uint16 T1T2TwAAry[10];
Uint16 T1T2NeAAry[10];
Uint16 T1T2NReptAAry[10];
Uint16 T1T2MiniNumAry[3];

	//Pointer variables defination
Uint16 * TableTempPt;
Uint16 * SaveSTempPt;
Uint16 * CheckTablePt;
int * SaveNTempPt;
Uint16 * SendTempPt;
Uint16 * StoreMiniAryPt;
Uint16 * MiniTablePt;
Uint16 * ChgTablePt;
Uint16 * SaveTablePt;

Uint16 WorkModeChoice[MODE_CHOICE];

#pragma DATA_SECTION(HVState           ,"MyVariablesZone");
#pragma DATA_SECTION(PulseCycle        ,"MyVariablesZone");
#pragma DATA_SECTION(MDumpTime         ,"MyVariablesZone");
#pragma DATA_SECTION(SDumpTime         ,"MyVariablesZone");
#pragma DATA_SECTION(CutTime           ,"MyVariablesZone");
#pragma DATA_SECTION(CutTimeLow        ,"MyVariablesZone");
#pragma DATA_SECTION(CutTimeHi         ,"MyVariablesZone");

#pragma DATA_SECTION(SendTableFlag     ,"MyVariablesZone");
#pragma DATA_SECTION(SendCnt           ,"MyVariablesZone");
#pragma DATA_SECTION(ZeroCnt           ,"MyVariablesZone");
#pragma DATA_SECTION(DENum             ,"MyVariablesZone");
#pragma DATA_SECTION(PhaseFlag         ,"MyVariablesZone");

#pragma DATA_SECTION(ScanModeFlag      ,"MyVariablesZone");
#pragma DATA_SECTION(StepFreq          ,"MyVariablesZone");
#pragma DATA_SECTION(SiglAcqPrdNum     ,"MyVariablesZone");
#pragma DATA_SECTION(SiglAcqFreqTim    ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqTim       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqFreq      ,"MyVariablesZone");
#pragma DATA_SECTION(ScanTE            ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleTe           ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleNe           ,"MyVariablesZone");
#pragma DATA_SECTION(ScanSignalNum     ,"MyVariablesZone");
#pragma DATA_SECTION(BandCnt           ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleCnt          ,"MyVariablesZone");
#pragma DATA_SECTION(MiniFreqCnt       ,"MyVariablesZone");
#pragma DATA_SECTION(FreqScan          ,"MyVariablesZone");
#pragma DATA_SECTION(MiniFreq          ,"MyVariablesZone");
#pragma DATA_SECTION(NTimeDec          ,"MyVariablesZone");
#pragma DATA_SECTION(STimeDec          ,"MyVariablesZone");

#pragma DATA_SECTION(SaveCnt           ,"MyVariablesZone");

#pragma DATA_SECTION(CycleFlag         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpSustainFlag   ,"MyVariablesZone");
#pragma DATA_SECTION(DSTTimeOne        ,"MyVariablesZone");

#pragma DATA_SECTION(NoiseDivFreq      ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseDivNum       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqNum       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqCnt       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseSum          ,"MyVariablesZone");
//#pragma DATA_SECTION(NoiseSumIQ        ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAveShiftIQ   ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseAveIQ        ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseCalNumIQ     ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseMaxValIQ     ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsIQ        ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsAbsIQ     ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseSqrAveIQ     ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsIQ3       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseSquSumIQ3    ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseSquAveIQ3    ,"MyVariablesZone");

#pragma DATA_SECTION(DDSFreq           ,"MyVariablesZone");
#pragma DATA_SECTION(CalDivData        ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid1           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid2           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid3           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid4           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid5           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid6           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSMid7           ,"MyVariablesZone");
#pragma DATA_SECTION(DDSCfgWords       ,"MyVariablesZone");
#pragma DATA_SECTION(DDSRefItg         ,"MyVariablesZone");
#pragma DATA_SECTION(DDSRefDcm         ,"MyVariablesZone");
#pragma DATA_SECTION(DDSCfgHi          ,"MyVariablesZone");
#pragma DATA_SECTION(DDSCfgLow         ,"MyVariablesZone");

#pragma DATA_SECTION(AdderCnt          ,"MyVariablesZone");
#pragma DATA_SECTION(SinOne            ,"MyVariablesZone");
#pragma DATA_SECTION(SinTwo            ,"MyVariablesZone");
#pragma DATA_SECTION(SinThree          ,"MyVariablesZone");
#pragma DATA_SECTION(SinFour           ,"MyVariablesZone");
#pragma DATA_SECTION(CosOne            ,"MyVariablesZone");
#pragma DATA_SECTION(CosTwo            ,"MyVariablesZone");
#pragma DATA_SECTION(CosThree          ,"MyVariablesZone");
#pragma DATA_SECTION(CosFour           ,"MyVariablesZone");
#pragma DATA_SECTION(CosFive            ,"MyVariablesZone");
#pragma DATA_SECTION(SinSumIQ          ,"MyVariablesZone");
#pragma DATA_SECTION(CosSumIQ          ,"MyVariablesZone");
#pragma DATA_SECTION(SignalCalNum      ,"MyVariablesZone");
#pragma DATA_SECTION(SinAveIQ          ,"MyVariablesZone");
#pragma DATA_SECTION(CosAveIQ          ,"MyVariablesZone");
#pragma DATA_SECTION(SignalAmpIQ       ,"MyVariablesZone");
#pragma DATA_SECTION(SignalPhaIQ       ,"MyVariablesZone");

#pragma DATA_SECTION(DumpPara1         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpPara2         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpPara3         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpPara4         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpPara5         ,"MyVariablesZone");
#pragma DATA_SECTION(DumpPara6         ,"MyVariablesZone");
#pragma DATA_SECTION(MainDumpTime      ,"MyVariablesZone");

#pragma DATA_SECTION(ScaleDDSDiv       ,"MyVariablesZone");
#pragma DATA_SECTION(HalfFreqNum       ,"MyVariablesZone");
#pragma DATA_SECTION(BriWidthData      ,"MyVariablesZone");
#pragma DATA_SECTION(BriMid            ,"MyVariablesZone");

#pragma DATA_SECTION(MatAcqFreqTim     ,"MyVariablesZone");
#pragma DATA_SECTION(MatTime           ,"MyVariablesZone");
#pragma DATA_SECTION(MatFreqSel        ,"MyVariablesZone");
#pragma DATA_SECTION(MatFreq           ,"MyVariablesZone");
#pragma DATA_SECTION(PulseAcqFlag      ,"MyVariablesZone");
#pragma DATA_SECTION(PulseTime         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseNum          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseDivNum       ,"MyVariablesZone");
#pragma DATA_SECTION(PulseMid4         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseMid1         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseMid2         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseMid3         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseDataCnt	   ,"MyVariablesZone");

#pragma DATA_SECTION(PdPara1           ,"MyVariablesZone");
#pragma DATA_SECTION(PdPara2           ,"MyVariablesZone");
#pragma DATA_SECTION(PdPara3           ,"MyVariablesZone");
#pragma DATA_SECTION(Pd90Time          ,"MyVariablesZone");
#pragma DATA_SECTION(Pd180Time         ,"MyVariablesZone");

#pragma DATA_SECTION(PulseGain         ,"MyVariablesZone");
#pragma DATA_SECTION(PulseGainIQ       ,"MyVariablesZone");
#pragma DATA_SECTION(StripBuf          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseSum          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseAve          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseBuf          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseRec          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseRecIQ        ,"MyVariablesZone");
#pragma DATA_SECTION(PulseCalNum       ,"MyVariablesZone");
#pragma DATA_SECTION(PulseReadBuf      ,"MyVariablesZone");

#pragma DATA_SECTION(SingleModeFlag    ,"MyVariablesZone");
#pragma DATA_SECTION(DEMn              ,"MyVariablesZone");
#pragma DATA_SECTION(WidthCnt          ,"MyVariablesZone");
#pragma DATA_SECTION(HegtWidth         ,"MyVariablesZone");
#pragma DATA_SECTION(SftWinWidth       ,"MyVariablesZone");
#pragma DATA_SECTION(DCFreqSel         ,"MyVariablesZone");
#pragma DATA_SECTION(DCPulseWidth      ,"MyVariablesZone");
#pragma DATA_SECTION(DCTes             ,"MyVariablesZone");
#pragma DATA_SECTION(DCNe              ,"MyVariablesZone");
#pragma DATA_SECTION(DCMn              ,"MyVariablesZone");
#pragma DATA_SECTION(DCm               ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleM            ,"MyVariablesZone");
#pragma DATA_SECTION(Ne                ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleMn           ,"MyVariablesZone");

#pragma DATA_SECTION(Pulse90Width      ,"MyVariablesZone");
#pragma DATA_SECTION(Pulse180Width     ,"MyVariablesZone");
#pragma DATA_SECTION(Pulse180WidthHalf ,"MyVariablesZone");
#pragma DATA_SECTION(EchoMid1          ,"MyVariablesZone");
#pragma DATA_SECTION(EchoMid2          ,"MyVariablesZone");
#pragma DATA_SECTION(EchoMid3          ,"MyVariablesZone");
#pragma DATA_SECTION(EchoMid4          ,"MyVariablesZone");
#pragma DATA_SECTION(DCWorkFreq        ,"MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTime       ,"MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTimeFHalf  ,"MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTimeBHalf  ,"MyVariablesZone");

#pragma DATA_SECTION(InverseTurnFlag   ,"MyVariablesZone");

#pragma DATA_SECTION(TNMid1            ,"MyVariablesZone");
#pragma DATA_SECTION(TNMid2            ,"MyVariablesZone");
#pragma DATA_SECTION(TNTime            ,"MyVariablesZone");
#pragma DATA_SECTION(Tes               ,"MyVariablesZone");
#pragma DATA_SECTION(Tel               ,"MyVariablesZone");
#pragma DATA_SECTION(TesCmp            ,"MyVariablesZone");
#pragma DATA_SECTION(TelCmp            ,"MyVariablesZone");

#pragma DATA_SECTION(CmpTesHalf        ,"MyVariablesZone");
#pragma DATA_SECTION(CmpTelHalf        ,"MyVariablesZone");
#pragma DATA_SECTION(Cmp90             ,"MyVariablesZone");
#pragma DATA_SECTION(CmpI90            ,"MyVariablesZone");
#pragma DATA_SECTION(Cmp180FHalf       ,"MyVariablesZone");
#pragma DATA_SECTION(Cmp180BHalf       ,"MyVariablesZone");

#pragma DATA_SECTION(Cut90Time         ,"MyVariablesZone");
#pragma DATA_SECTION(Cut90TimeLow      ,"MyVariablesZone");
#pragma DATA_SECTION(Cut90TimeHi       ,"MyVariablesZone");
#pragma DATA_SECTION(CutI90Time         ,"MyVariablesZone");
#pragma DATA_SECTION(CutI90TimeLow      ,"MyVariablesZone");
#pragma DATA_SECTION(CutI90TimeHi       ,"MyVariablesZone");
#pragma DATA_SECTION(Open180LTime      ,"MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeMS    ,"MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeLow   ,"MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeHi    ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180LTime       ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180LTimeLow    ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180LTimeHi     ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180STime       ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180STimeLow    ,"MyVariablesZone");
#pragma DATA_SECTION(Cut180STimeHi     ,"MyVariablesZone");
#pragma DATA_SECTION(Open180STime      ,"MyVariablesZone");
#pragma DATA_SECTION(Open180STimeLow   ,"MyVariablesZone");
#pragma DATA_SECTION(Open180STimeHi    ,"MyVariablesZone");

#pragma DATA_SECTION(EchoAcqNum        ,"MyVariablesZone");

#pragma DATA_SECTION(TesCCheck         ,"MyVariablesZone");
#pragma DATA_SECTION(TelCCheck         ,"MyVariablesZone");
#pragma DATA_SECTION(P90PrdNum         ,"MyVariablesZone");
#pragma DATA_SECTION(P180PrdNum        ,"MyVariablesZone");

#pragma DATA_SECTION(Acq90Num          ,"MyVariablesZone");
#pragma DATA_SECTION(Acq180Num         ,"MyVariablesZone");
#pragma DATA_SECTION(Strip90Num        ,"MyVariablesZone");
#pragma DATA_SECTION(Strip180Num       ,"MyVariablesZone");

#pragma DATA_SECTION(SdAcqNum1         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum2         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum3         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7         ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4Low      ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4Hi       ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5Low      ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5Hi       ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6Low      ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6Hi       ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7Low      ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7Hi       ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid1     ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid2     ,"MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid3     ,"MyVariablesZone");

#pragma DATA_SECTION(StoreCnt          ,"MyVariablesZone");
#pragma DATA_SECTION(PulseAmpCrtIQ     ,"MyVariablesZone");
#pragma DATA_SECTION(Pulse90StoreAddr  ,"MyVariablesZone");
#pragma DATA_SECTION(PulseF180StoreAddr,"MyVariablesZone");
#pragma DATA_SECTION(PulseL180StoreAddr,"MyVariablesZone");
#pragma DATA_SECTION(EchoStorAddr      ,"MyVariablesZone");

#pragma DATA_SECTION(McbspRcvBuf       ,"MyVariablesZone");
#pragma DATA_SECTION(DownTableFlag     ,"MyVariablesZone");
#pragma DATA_SECTION(WorkMode          ,"MyVariablesZone");
#pragma DATA_SECTION(PP6ModeFlag       ,"MyVariablesZone");
#pragma DATA_SECTION(ScaleModeFlag     ,"MyVariablesZone");
#pragma DATA_SECTION(HoleModeFlag      ,"MyVariablesZone");
#pragma DATA_SECTION(ST2DFlag          ,"MyVariablesZone");
#pragma DATA_SECTION(DT2DFlag          ,"MyVariablesZone");
#pragma DATA_SECTION(MT2DFlag          ,"MyVariablesZone");
#pragma DATA_SECTION(ST1T2Flag         ,"MyVariablesZone");
#pragma DATA_SECTION(DT1T2Flag         ,"MyVariablesZone");
#pragma DATA_SECTION(ST12DFlag         ,"MyVariablesZone");
#pragma DATA_SECTION(DT12DFlag         ,"MyVariablesZone");

#pragma DATA_SECTION(ChangeTableBuf    ,"MyVariablesZone");
#pragma DATA_SECTION(CaseBuffer        ,"MyVariablesZone");
#pragma DATA_SECTION(TableChgCnt       ,"MyVariablesZone");
#pragma DATA_SECTION(ChgTable995Flag   ,"MyVariablesZone");
#pragma DATA_SECTION(ChgTable996Flag   ,"MyVariablesZone");
#pragma DATA_SECTION(ChgTable999Flag   ,"MyVariablesZone");
#pragma DATA_SECTION(ChgTable99AFlag   ,"MyVariablesZone");


#pragma DATA_SECTION(ToMSFreq          ,"MyVariablesZone");
#pragma DATA_SECTION(ToMSNoiseAddr     ,"MyVariablesZone");
#pragma DATA_SECTION(ToMSSignalAddr    ,"MyVariablesZone");

#pragma DATA_SECTION(ReadTableBuf      ,"MyVariablesZone");
#pragma DATA_SECTION(ZeroOne           ,"MyVariablesZone");

#pragma DATA_SECTION(PP6FreqSelLow     ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FreqSelHi      ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FTe14A2356DE   ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FTe1346C       ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FNe1346C       ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FNe2356DE      ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FNe14A         ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FTw1346C       ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FNRept14C      ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FNRept36C      ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FCmp1          ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FCmp2          ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FTime36DWait   ,"MyVariablesZone");
#pragma DATA_SECTION(DataTotalNum      ,"MyVariablesZone");
#pragma DATA_SECTION(EchoNum           ,"MyVariablesZone");
#pragma DATA_SECTION(PP6FCnt           ,"MyVariablesZone");

#pragma DATA_SECTION(FreqNum2          ,"MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt1       ,"MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt2       ,"MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt3       ,"MyVariablesZone");
#pragma DATA_SECTION(MiniNoiseMax      ,"MyVariablesZone");
#pragma DATA_SECTION(MiniBuf           ,"MyVariablesZone");

#pragma DATA_SECTION(Oil3ModeFlag      ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3FreqSel       ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Te1C2C3CDEF   ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Ne123C        ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Ne3D          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Ne3E          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Ne3F          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Tw123C        ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Tw3D          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Tw3E          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Tw3F          ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3NRept123C     ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3NRept3D       ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3NRept3E       ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3NRept3F       ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3Cnt           ,"MyVariablesZone");

#pragma DATA_SECTION(Gas6ModeFlag      ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6FreqSelLow    ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6FreqSelHi     ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Te123456C24DE ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Ne123456C24DE ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Tw123456C     ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Tw24D         ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Tw24E         ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6NRept24D      ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6NRept24E      ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6NRept1234C    ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6NRept56C      ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6Cnt           ,"MyVariablesZone");

#pragma DATA_SECTION(T2DCPMGTwA        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETwA          ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWTwA         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETesA         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWTeAB        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDCTesA         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWNreptA      ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCPMGNeA        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDENeA          ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWNeA         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDEmn           ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDEm            ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCPMGTwB        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETwB          ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWTwB         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETesB         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel1B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel2B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel3B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel4B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel5B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETel6B        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWNreptB      ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCPMGNeB        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDENeB          ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCBWNeB         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DCnt            ,"MyVariablesZone");
#pragma DATA_SECTION(T2DFreqSel        ,"MyVariablesZone");
#pragma DATA_SECTION(T2DTwMid1         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DTwMid2         ,"MyVariablesZone");
#pragma DATA_SECTION(ST2DMiniNum       ,"MyVariablesZone");

#pragma DATA_SECTION(MiniStorAddr1     ,"MyVariablesZone");
#pragma DATA_SECTION(MiniStorAddr2     ,"MyVariablesZone");
#pragma DATA_SECTION(MiniStorAddr3     ,"MyVariablesZone");
#pragma DATA_SECTION(MiniStorAddr4     ,"MyVariablesZone");
#pragma DATA_SECTION(MiniStorAddr5     ,"MyVariablesZone");
#pragma DATA_SECTION(MiniStorAddr6     ,"MyVariablesZone");

#pragma DATA_SECTION(T2DCBWTeA         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETwBC         ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDCTes          ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDENeBC         ,"MyVariablesZone");

#pragma DATA_SECTION(T1T2FreqSel       ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2Cnt           ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2CPMGTe        ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2CBWTe         ,"MyVariablesZone");

#pragma DATA_SECTION(T12DCPMGTw1AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGTw2AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGTw8AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGTw9AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGTw0AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DDETwAB        ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCBWTwAB       ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCBWTeAB       ,"MyVariablesZone");
#pragma DATA_SECTION(T12DTesAB         ,"MyVariablesZone");
#pragma DATA_SECTION(T12DNRept890AB    ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCBWNReptAB    ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGNe1AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGNe2AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGNe8AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGNe9AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCPMGNe0AB     ,"MyVariablesZone");
#pragma DATA_SECTION(T12DDENeAB        ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCBWNeAB       ,"MyVariablesZone");
#pragma DATA_SECTION(T12DDEmnAB        ,"MyVariablesZone");
#pragma DATA_SECTION(T12DDEmAB         ,"MyVariablesZone");
#pragma DATA_SECTION(T12DFreqSel       ,"MyVariablesZone");
#pragma DATA_SECTION(T12DCnt           ,"MyVariablesZone");

#pragma DATA_SECTION(DFT1T2DFlag            	,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_A1B1            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_A2B2            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_A8B8            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_A9B9            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_A10B10          ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_DE              ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TW_CBW             ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TE_CBW             ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TES_DE_T2_T1       ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TEL1_DE            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TEL2_DE            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TEL3_DE            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TEL4_DE            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_TEL5_DE            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NREPT_CBW          ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_A1B1            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_A2B2            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_A8B8            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_A9B9            ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_A10B10          ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_DE              ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_NE_CBW             ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_group_DE           ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_DE_TEL_num         ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2D_cnt                ,"MyVariablesZone");
#pragma DATA_SECTION(DFT1T2DFreqSel             ,"MyVariablesZone");

#pragma DATA_SECTION(PPLOIL6NRept123456C        ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6NRept24D            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6NRept24E            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FNe156A1B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FNe23AB             ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FNe4AB              ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FNe24DE             ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FNe123456C          ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_156A1B         ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_23AB           ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_4AB            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_123456C        ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_2DE            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6F_TE_4DE            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FTw1234B            ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FTw24D              ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FTw24E              ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FTw123456C          ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FCnt                ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FFlag               ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FFreqSelLow         ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FFreqSelHi          ,"MyVariablesZone");
#pragma DATA_SECTION(PPLOIL6FFreqSel            ,"MyVariablesZone");

#pragma DATA_SECTION(PP3FNRept1C                ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FNe1A                   ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FNe1C                   ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FNe23DE                 ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FTe1A23DE               ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FTe1C                   ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FTw1C                   ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FCnt                    ,"MyVariablesZone");
#pragma DATA_SECTION(flag_pp3                   ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FreqSelLow              ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FreqSelHi               ,"MyVariablesZone");
#pragma DATA_SECTION(PP3FreqSel                 ,"MyVariablesZone");

#pragma DATA_SECTION(FBW2FNRept12C              ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FNe12B                 ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FNe12C                 ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FTe12B                 ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FTe12C                 ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FTw12C                 ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FCnt                   ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FFlag                  ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FFreqSelLow            ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FFreqSelHi             ,"MyVariablesZone");
#pragma DATA_SECTION(FBW2FFreqSel               ,"MyVariablesZone");

#pragma DATA_SECTION(PPHOIL6FNRept1234C         ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNRept5C            ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNRept6C            ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe12345C           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe246A             ,"MyVariablesZone");
/*
#pragma DATA_SECTION(PPHOIL6FNe1B               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe2B               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe3B               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe4B               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe5B               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FNe6B               ,"MyVariablesZone");
*/
#pragma DATA_SECTION(PPHOIL6FNe6C               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_1B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_123456C        ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_246A           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_3B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_2B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_5B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_4B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_TE_6B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FTw123456C          ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FFlag               ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FCnt                ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FFreqSelLow         ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FFreqSelHi          ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6FFreqSel            ,"MyVariablesZone");

#pragma DATA_SECTION(Gas6_2ModeFlag             ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2FreqSelLow           ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2FreqSelHi            ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Te123456C24DE        ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Ne123456C24DE        ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Tw123456C            ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Tw24D                ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Tw24E                ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2NRept24D             ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2NRept24E             ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2NRept123456C         ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6_2Cnt                  ,"MyVariablesZone");

#pragma DATA_SECTION(PPHOIL6F_2NRept123456C     ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne12346C         ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne246A           ,"MyVariablesZone");
/*
#pragma DATA_SECTION(PPHOIL6F_2Ne1B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne2B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne3B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne4B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne5B             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Ne6B             ,"MyVariablesZone");
*/
#pragma DATA_SECTION(PPHOIL6F_2Ne5C             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_1B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_123456C      ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_246A         ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_3B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_2B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_5B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_4B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2_TE_6B           ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Tw123456C        ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Flag             ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2Cnt              ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2FreqSelLow       ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2FreqSelHi        ,"MyVariablesZone");
#pragma DATA_SECTION(PPHOIL6F_2FreqSel          ,"MyVariablesZone");

#pragma DATA_SECTION(P3D6F_TE_1A                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_2A                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_3A                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_4A                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_5B                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_6B                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_1C                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_2D                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_3E                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_4F                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_5F                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6F_TE_6F                ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe1A                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe2A                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe3A                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe4A                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe5B                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe6B                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe1C                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe2D                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe3E                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe4F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe5F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNe6F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw1C                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw2D                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw3E                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw4F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw5F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FTw6F                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNRept1C               ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNRept2D               ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNRept3E               ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNRept4F               ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FNRept5F               ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FFlag                  ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FCnt                   ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FFreqSelLow            ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FFreqSelHi             ,"MyVariablesZone");
#pragma DATA_SECTION(P3D6FFreqSel               ,"MyVariablesZone");


#pragma DATA_SECTION(HRT1T22FMode_TW_A1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B2         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B3         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B4         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B5         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B6         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TW_B7         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_A1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B2         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B3         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B4         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B5         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B6         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_TE_B7         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_A1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B1         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B2         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B3         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B4         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B5         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B6         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NE_B7         ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B2      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B3      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B4      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B5      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B6      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FMode_NREPT_B7      ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FFlag               ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FCnt                ,"MyVariablesZone");
#pragma DATA_SECTION(HRT1T22FFreqSel            ,"MyVariablesZone");


#pragma DATA_SECTION(PulseGainAry      ,"MyVariablesZone");
#pragma DATA_SECTION(FreqAry           ,"MyVariablesZone");
#pragma DATA_SECTION(RelayAry          ,"MyVariablesZone");

#pragma DATA_SECTION(AdderLowAry       ,"MyVariablesZone");
#pragma DATA_SECTION(AdderResAry       ,"MyVariablesZone");
#pragma DATA_SECTION(NoiseDataAry      ,"MyVariablesZone");

#pragma DATA_SECTION(NintyWidthAry     ,"MyVariablesZone");

#pragma DATA_SECTION(PP6FMiniNumAry    ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3MiniNumAry    ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6FMiniNumAry   ,"MyVariablesZone");
#pragma DATA_SECTION(MiniAddAry        ,"MyVariablesZone");

#pragma DATA_SECTION(PP6FreqSelAry     ,"MyVariablesZone");
#pragma DATA_SECTION(Oil3FreqSelAry    ,"MyVariablesZone");
#pragma DATA_SECTION(Gas6FreqSelAry    ,"MyVariablesZone");

#pragma DATA_SECTION(T2DFreqSelAry     ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETelAAry      ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETelBAry      ,"MyVariablesZone");
#pragma DATA_SECTION(T2DDETelCAry      ,"MyVariablesZone");
#pragma DATA_SECTION(DT2DMiniNumAry    ,"MyVariablesZone");
#pragma DATA_SECTION(MT2DMiniNumAry    ,"MyVariablesZone");

#pragma DATA_SECTION(T12DTelABAry      ,"MyVariablesZone");
#pragma DATA_SECTION(T12DMiniNumAry    ,"MyVariablesZone");

#pragma DATA_SECTION(T1T2TwAAry        ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2NeAAry        ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2NReptAAry     ,"MyVariablesZone");
#pragma DATA_SECTION(T1T2MiniNumAry    ,"MyVariablesZone");

#pragma DATA_SECTION(TableTempPt       ,"MyVariablesZone");
#pragma DATA_SECTION(SaveSTempPt       ,"MyVariablesZone");
#pragma DATA_SECTION(CheckTablePt      ,"MyVariablesZone");
#pragma DATA_SECTION(SaveNTempPt       ,"MyVariablesZone");
#pragma DATA_SECTION(StoreMiniAryPt    ,"MyVariablesZone");
#pragma DATA_SECTION(MiniTablePt       ,"MyVariablesZone");
#pragma DATA_SECTION(ChgTablePt        ,"MyVariablesZone");
#pragma DATA_SECTION(SaveTablePt       ,"MyVariablesZone");

#pragma DATA_SECTION(WorkModeChoice       ,"MyVariablesZone");


