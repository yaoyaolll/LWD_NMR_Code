//###########################################################################
//
// FILE:	MyVariables.h
//
// TITLE:	User variables declaration.
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
extern Uint16 HVState;
extern Uint32 PulseCycle; 
extern Uint32 MDumpTime; 
extern Uint32 SDumpTime; 
extern Uint32 CutTime;     
extern Uint16 CutTimeLow;
extern Uint16 CutTimeHi;

extern Uint16 SendTableFlag;
extern Uint32 SendCnt;
extern Uint16 ZeroCnt;
extern Uint16 DENum;
extern Uint16 PhaseFlag;

extern Uint16 ScanModeFlag;
extern Uint16 StepFreq;
extern Uint16 SiglAcqPrdNum;
extern Uint16 SiglAcqFreqTim;
extern Uint16 NoiseAcqTim;
extern Uint16 NoiseAcqFreq;
extern Uint16 ScanTE;
extern Uint16 ScaleTe;
extern Uint16 ScaleNe;
extern Uint16 ScanSignalNum;
extern Uint16 BandCnt;
extern Uint16 ScaleCnt;
extern Uint16 MiniFreqCnt;
extern Uint16 FreqScan;
extern Uint16 MiniFreq;
extern Uint16 NTimeDec;
extern Uint16 STimeDec;

extern Uint16 SaveCnt;

extern Uint16 CycleFlag;
extern Uint16 DumpSustainFlag;
extern Uint16 DSTTimeOne;

extern Uint16 NoiseDivFreq;
extern Uint16 NoiseDivNum;	
extern Uint16 NoiseAcqNum;
extern Uint16 NoiseAcqCnt;
extern Uint32 NoiseSum;
//extern _iq NoiseSumIQ;
extern _iq NoiseAveShiftIQ;    //噪声数值的均值（有2v偏置）
extern _iq NoiseAveIQ;    //噪声数值的均值
extern _iq NoiseCalNumIQ;   //计算的噪声数据个数
extern _iq NoiseMaxValIQ;
extern _iq NoiseOfsIQ;
extern _iq NoiseOfsAbsIQ;
extern _iq NoiseSqrAveIQ;
extern _iq3 NoiseOfsIQ3;
extern _iq3 NoiseSquSumIQ3; 
extern _iq3 NoiseSquAveIQ3;  

extern Uint32 DDSFreq;
extern Uint16 CalDivData;

extern Uint32 DDSMid1;
extern Uint32 DDSMid2;
extern Uint32 DDSMid3;
extern Uint32 DDSMid4;
extern Uint32 DDSMid5;
extern Uint32 DDSMid6;
extern Uint32 DDSMid7;
extern Uint32 DDSCfgWords;
extern double DDSRefItg;
extern double DDSRefDcm;
extern Uint16 DDSCfgHi;
extern Uint16 DDSCfgLow;

extern Uint16 AdderCnt;
extern int32 SinOne;           //计算用
extern int32 SinTwo;
extern int32 SinThree;
extern int32 SinFour;
extern int32 CosOne;
extern int32 CosTwo;
extern int32 CosThree;
extern int32 CosFour;
extern int32 CosFive;
extern _iq SinSumIQ;
extern _iq CosSumIQ;
extern Uint16 SignalCalNum;
extern _iq SinAveIQ;
extern _iq CosAveIQ;
extern _iq SignalAmpIQ;
extern _iq SignalPhaIQ;

extern Uint16 DumpPara1;
extern Uint16 DumpPara2;
extern Uint16 DumpPara3;
extern Uint16 DumpPara4;
extern Uint16 DumpPara5;
extern Uint16 DumpPara6;
extern Uint16 MainDumpTime;     //主泄放时间

extern Uint16 ScaleDDSDiv;  //刻度激励用dds分频系数
extern Uint16 HalfFreqNum;     //起震计数值
extern Uint16 BriWidthData;      //内外桥宽度计数值（注意数据格式）
extern Uint16 BriMid;

extern Uint16 MatAcqFreqTim;            //维护时发射波形采集频率倍数
extern Uint16 MatTime;            //维护时发射波形采集时间段长度
extern Uint16 MatFreqSel;
extern Uint16 MatFreq;
extern Uint16 PulseAcqFlag;
extern Uint16 PulseTime;
extern Uint16 PulseNum;
extern Uint16 PulseDivNum;
extern Uint16 PulseMid4;
extern float PulseMid1;
extern float PulseMid2;
extern float PulseMid3;
extern Uint16 PulseDataCnt;

extern Uint16 PdPara1;
extern Uint16 PdPara2;
extern Uint16 PdPara3;
extern Uint16 Pd90Time;
extern Uint16 Pd180Time;

extern int16 PulseGain;
extern _iq PulseGainIQ;
extern Uint16 StripBuf;
extern double PulseSum;
extern double PulseAve;
extern Uint16 PulseBuf;
extern double PulseRec;
extern _iq PulseRecIQ;
extern Uint16 PulseCalNum;
extern Uint16 PulseReadBuf;

extern Uint16 SingleModeFlag;
extern Uint16 DEMn;
extern Uint16 WidthCnt;
extern Uint16 HegtWidth;   //回波发射脉冲宽度寄存器数值
extern Uint16 SftWinWidth;  //采集窗时间滑动寄存器;
extern Uint16 DCFreqSel;
extern Uint16 DCPulseWidth;
extern Uint16 DCTes;
extern Uint16 DCNe;
extern Uint16 DCMn;
extern Uint16 DCm;
extern Uint16 ScaleM;
extern Uint16 Ne;
extern Uint16 ScaleMn;

extern Uint32 Pulse90Width;
extern Uint32 Pulse180Width;
extern Uint32 Pulse180WidthHalf;
extern float EchoMid1;
extern float EchoMid2;
extern float EchoMid3;
extern float EchoMid4;
extern Uint16 DCWorkFreq;
extern Uint16 EchoAcqTime;      //采集时间
extern Uint16 EchoAcqTimeFHalf;
extern Uint16 EchoAcqTimeBHalf;

extern Uint16 InverseTurnFlag;

extern float TNMid1;
extern float TNMid2;
extern Uint32 TNTime;

extern Uint32 Tes;           //短te时间
extern Uint32 Tel;
extern Uint32 TesCmp;         // 取整的短te
extern Uint32 TelCmp;         //取整的长te

extern Uint32 CmpTesHalf;
extern Uint32 CmpTelHalf;   //长TE下TEL_C
extern Uint32 Cmp90;
extern Uint32 CmpI90;
extern Uint32 Cmp180FHalf;
extern Uint32 Cmp180BHalf;

extern Uint32 Cut90Time;    //90度隔离时间
extern Uint16 Cut90TimeLow;
extern Uint16 Cut90TimeHi;
extern Uint32 CutI90Time;    //90度隔离时间
extern Uint16 CutI90TimeLow;
extern Uint16 CutI90TimeHi;
extern Uint32 Open180LTime;	//长TE下的DEC打开时间
extern Uint16 Open180LTimeMS;   
extern Uint16 Open180LTimeLow;  
extern Uint16 Open180LTimeHi;
extern Uint32 Cut180LTime;     //长TE下的180隔离时间
extern Uint16 Cut180LTimeLow;
extern Uint16 Cut180LTimeHi;
extern Uint32 Cut180STime;
extern Uint16 Cut180STimeLow;
extern Uint16 Cut180STimeHi;
extern Uint32 Open180STime;	//长TE下的DEC打开时间   
extern Uint16 Open180STimeLow;  
extern Uint16 Open180STimeHi;

extern Uint16 EchoAcqNum;

extern Uint32 TesCCheck;
extern Uint32 TelCCheck;
extern Uint16 P90PrdNum;
extern Uint16 P180PrdNum;

extern Uint16 Acq90Num;     //90度激励采集点数
extern Uint16 Acq180Num;    //180激励采集点数
extern Uint16 Strip90Num;     //90度激励舍去点数
extern Uint16 Strip180Num;     //180度激励舍去点数

extern Uint16 SdAcqNum1;
extern Uint16 SdAcqNum2;
extern Uint16 SdAcqNum3;
extern Uint32 SdAcqNum4;
extern Uint32 SdAcqNum5;
extern Uint32 SdAcqNum6;
extern Uint32 SdAcqNum7;
extern Uint16 SdAcqNum4Low;
extern Uint16 SdAcqNum4Hi;
extern Uint16 SdAcqNum5Low;
extern Uint16 SdAcqNum5Hi;
extern Uint16 SdAcqNum6Low;
extern Uint16 SdAcqNum6Hi;
extern Uint16 SdAcqNum7Low;
extern Uint16 SdAcqNum7Hi;
extern float SdAcqTimeMid1;
extern float SdAcqTimeMid2;
extern float SdAcqTimeMid3;

extern Uint16 StoreCnt;
extern _iq PulseAmpCrtIQ;
extern Uint32 Pulse90StoreAddr;
extern Uint32 PulseF180StoreAddr;
extern Uint32 PulseL180StoreAddr;
extern Uint32 EchoStorAddr;

extern Uint16 McbspRcvBuf;
extern Uint16 DownTableFlag;
extern Uint16 WorkMode;
extern Uint16 PP6ModeFlag;
extern Uint16 ScaleModeFlag;
extern Uint16 HoleModeFlag;
extern Uint16 ST2DFlag;
extern Uint16 DT2DFlag;
extern Uint16 MT2DFlag;
extern Uint16 ST1T2Flag;
extern Uint16 DT1T2Flag;
extern Uint16 ST12DFlag;
extern Uint16 DT12DFlag;
extern Uint16 DFT1T2DFlag;

extern Uint16 ChangeTableBuf;
extern Uint16 CaseBuffer;
extern Uint16 TableChgCnt;
extern Uint16 * ChgTablePt;
extern Uint16 ChgTable995Flag;
extern Uint16 ChgTable996Flag;
extern Uint16 ChgTable999Flag;
extern Uint16 ChgTable99AFlag;


extern Uint16 ToMSFreq;
extern Uint32 ToMSNoiseAddr;
extern Uint32 ToMSSignalAddr;

extern Uint16 ReadTableBuf;
extern Uint16 ZeroOne;

extern Uint16 PP6FreqSelLow;
extern Uint16 PP6FreqSelHi;         
extern Uint16 PP6FTe14A2356DE;
extern Uint16 PP6FTe1346C;
extern Uint16 PP6FNe1346C;
extern Uint16 PP6FNe2356DE;
extern Uint16 PP6FNe14A;
extern Uint16 PP6FTw1346C;
extern Uint16 PP6FNRept14C;
extern Uint16 PP6FNRept36C;
extern Uint16 PP6FCmp1;
extern Uint16 PP6FCmp2;
extern Uint16 PP6FTime36DWait;
extern Uint32 DataTotalNum;
extern Uint16 EchoNum;
extern Uint32 PP6FCnt;

extern Uint16 FreqNum2;
extern Uint16 MiniCycCnt1;
extern Uint16 MiniCycCnt2;
extern Uint16 MiniCycCnt3;
extern Uint16 MiniNoiseMax;
extern Uint16 MiniBuf;

extern Uint16 Oil3ModeFlag;
extern Uint16 Oil3FreqSel;
extern Uint16 Oil3Te1C2C3CDEF;
extern Uint16 Oil3Ne123C;
extern Uint16 Oil3Ne3D;
extern Uint16 Oil3Ne3E;
extern Uint16 Oil3Ne3F;
extern Uint16 Oil3Tw123C;
extern Uint16 Oil3Tw3D;
extern Uint16 Oil3Tw3E;
extern Uint16 Oil3Tw3F;
extern Uint16 Oil3NRept123C;
extern Uint16 Oil3NRept3D;
extern Uint16 Oil3NRept3E;
extern Uint16 Oil3NRept3F;
extern Uint16 Oil3Cnt;

extern Uint16 Gas6ModeFlag;
extern Uint16 Gas6FreqSelLow;
extern Uint16 Gas6FreqSelHi;
extern Uint16 Gas6Te123456C24DE;
extern Uint16 Gas6Ne123456C24DE;
extern Uint16 Gas6Tw123456C;
extern Uint16 Gas6Tw24D;
extern Uint16 Gas6Tw24E;
extern Uint16 Gas6NRept24D;
extern Uint16 Gas6NRept24E;
extern Uint16 Gas6NRept1234C;
extern Uint16 Gas6NRept56C;
extern Uint16 Gas6Cnt;

extern Uint16 T2DCPMGTwA;
extern Uint16 T2DDETwA;
extern Uint16 T2DCBWTwA;
extern Uint16 T2DDETesA;
extern Uint16 T2DCBWTeAB;
extern Uint16 T2DDCTesA;
extern Uint16 T2DCBWNreptA;
extern Uint16 T2DCPMGNeA;
extern Uint16 T2DDENeA;
extern Uint16 T2DCBWNeA;
extern Uint16 T2DDEmn;
extern Uint16 T2DDEm;
extern Uint16 T2DCPMGTwB;
extern Uint16 T2DDETwB;
extern Uint16 T2DCBWTwB;
extern Uint16 T2DDETesB;
extern Uint16 T2DDETel1B;
extern Uint16 T2DDETel2B;
extern Uint16 T2DDETel3B;
extern Uint16 T2DDETel4B;
extern Uint16 T2DDETel5B;
extern Uint16 T2DDETel6B;
extern Uint16 T2DCBWNreptB;
extern Uint16 T2DCPMGNeB;
extern Uint16 T2DDENeB;
extern Uint16 T2DCBWNeB;
extern Uint16 T2DCnt;
extern Uint16 T2DFreqSel;
extern Uint16 T2DTwMid1;
extern Uint16 T2DTwMid2;
extern Uint16 ST2DMiniNum;

extern Uint32 MiniStorAddr1;
extern Uint32 MiniStorAddr2;
extern Uint32 MiniStorAddr3;
extern Uint32 MiniStorAddr4;
extern Uint32 MiniStorAddr5;
extern Uint32 MiniStorAddr6;

extern Uint16 T2DCBWTeA;
extern Uint16 T2DDETwBC;
extern Uint16 T2DDCTes;
extern Uint16 T2DDENeBC;

extern Uint16 T1T2FreqSel;
extern Uint16 T1T2Cnt;
extern Uint16 T1T2CPMGTe;
extern Uint16 T1T2CBWTe;

extern Uint16 T12DCPMGTw1AB;
extern Uint16 T12DCPMGTw2AB;
extern Uint16 T12DCPMGTw8AB;
extern Uint16 T12DCPMGTw9AB;
extern Uint16 T12DCPMGTw0AB;
extern Uint16 T12DDETwAB;
extern Uint16 T12DCBWTwAB;
extern Uint16 T12DCBWTeAB;
extern Uint16 T12DTesAB;
extern Uint16 T12DNRept890AB;
extern Uint16 T12DCBWNReptAB;
extern Uint16 T12DCPMGNe1AB;
extern Uint16 T12DCPMGNe2AB;
extern Uint16 T12DCPMGNe8AB;
extern Uint16 T12DCPMGNe9AB;
extern Uint16 T12DCPMGNe0AB;
extern Uint16 T12DDENeAB;
extern Uint16 T12DCBWNeAB;
extern Uint16 T12DDEmnAB;
extern Uint16 T12DDEmAB;
extern Uint16 T12DFreqSel;
extern Uint16 T12DCnt;

extern Uint16 DFT1T2D_TW_A1B1; //default: 9800+
extern Uint16 DFT1T2D_TW_A2B2;
extern Uint16 DFT1T2D_TW_A8B8;
extern Uint16 DFT1T2D_TW_A9B9;
extern Uint16 DFT1T2D_TW_A10B10;
extern Uint16 DFT1T2D_TW_DE;
extern Uint16 DFT1T2D_TW_CBW;
extern Uint16 DFT1T2D_TE_CBW;
extern Uint16 DFT1T2D_TES_DE_T2_T1;
extern Uint16 DFT1T2D_TEL1_DE;
extern Uint16 DFT1T2D_TEL2_DE;
extern Uint16 DFT1T2D_TEL3_DE;
extern Uint16 DFT1T2D_TEL4_DE;
extern Uint16 DFT1T2D_TEL5_DE;
extern Uint16 DFT1T2D_NREPT_CBW;
extern Uint16 DFT1T2D_NE_A1B1;
extern Uint16 DFT1T2D_NE_A2B2;
extern Uint16 DFT1T2D_NE_A8B8;
extern Uint16 DFT1T2D_NE_A9B9;
extern Uint16 DFT1T2D_NE_A10B10;
extern Uint16 DFT1T2D_NE_DE;
extern Uint16 DFT1T2D_NE_CBW;
extern Uint16 DFT1T2D_group_DE;
extern Uint16 DFT1T2D_DE_TEL_num;
extern Uint16 DFT1T2D_cnt ;
extern Uint16 DFT1T2DFreqSel;

extern Uint16 PPLOIL6NRept123456C;
extern Uint16 PPLOIL6NRept24D;
extern Uint16 PPLOIL6NRept24E;
extern Uint16 PPLOIL6FNe156A1B;
extern Uint16 PPLOIL6FNe23AB;
extern Uint16 PPLOIL6FNe4AB;
extern Uint16 PPLOIL6FNe24DE;
extern Uint16 PPLOIL6FNe123456C;
extern Uint16 PPLOIL6F_TE_156A1B;
extern Uint16 PPLOIL6F_TE_23AB;
extern Uint16 PPLOIL6F_TE_4AB;
extern Uint16 PPLOIL6F_TE_123456C;
extern Uint16 PPLOIL6F_TE_2DE;
extern Uint16 PPLOIL6F_TE_4DE;
extern Uint16 PPLOIL6FTw1234B;
extern Uint16 PPLOIL6FTw24D;
extern Uint16 PPLOIL6FTw24E;
extern Uint16 PPLOIL6FTw123456C;
extern Uint16 PPLOIL6FCnt;
extern Uint16 PPLOIL6FFlag;
extern Uint16 PPLOIL6FFreqSelLow;
extern Uint16 PPLOIL6FFreqSelHi;
extern Uint16 PPLOIL6FFreqSel;

extern Uint16 PP3FNRept1C;
extern Uint16 PP3FNe1A;
extern Uint16 PP3FNe1C;
extern Uint16 PP3FNe23DE;
extern Uint16 PP3FTe1A23DE;
extern Uint16 PP3FTe1C;
extern Uint16 PP3FTw1C;
extern Uint16 PP3FCnt;
extern Uint16 flag_pp3;
extern Uint16 PP3FreqSelLow;
extern Uint16 PP3FreqSelHi;
extern Uint16 PP3FreqSel;

extern Uint16 FBW2FNRept12C;
extern Uint16 FBW2FNe12B;
extern Uint16 FBW2FNe12C;
extern Uint16 FBW2FTe12B;
extern Uint16 FBW2FTe12C;
extern Uint16 FBW2FTw12C;
extern Uint16 FBW2FCnt;
extern Uint16 FBW2FFlag;
extern Uint16 FBW2FFreqSelLow;
extern Uint16 FBW2FFreqSelHi;
extern Uint16 FBW2FFreqSel;

extern Uint16 PPHOIL6FNRept1234C;
extern Uint16 PPHOIL6FNRept5C;
extern Uint16 PPHOIL6FNRept6C;
extern Uint16 PPHOIL6FNe12345C;
extern Uint16 PPHOIL6FNe246A;
/*
extern Uint16 PPHOIL6FNe1B;
extern Uint16 PPHOIL6FNe2B;
extern Uint16 PPHOIL6FNe3B;
extern Uint16 PPHOIL6FNe4B;
extern Uint16 PPHOIL6FNe5B;
extern Uint16 PPHOIL6FNe6B;
*/
extern Uint16 PPHOIL6FNe6C;
extern Uint16 PPHOIL6F_TE_1B;
extern Uint16 PPHOIL6F_TE_123456C;
extern Uint16 PPHOIL6F_TE_246A;
extern Uint16 PPHOIL6F_TE_3B;
extern Uint16 PPHOIL6F_TE_2B;
extern Uint16 PPHOIL6F_TE_5B;
extern Uint16 PPHOIL6F_TE_4B;
extern Uint16 PPHOIL6F_TE_6B;
extern Uint16 PPHOIL6FTw123456C;
extern Uint16 PPHOIL6FFlag;
extern Uint16 PPHOIL6FCnt;
extern Uint16 PPHOIL6FFreqSelLow;
extern Uint16 PPHOIL6FFreqSelHi;
extern Uint16 PPHOIL6FFreqSel;


extern Uint16 Gas6_2ModeFlag;
extern Uint16 Gas6_2FreqSelLow;
extern Uint16 Gas6_2FreqSelHi;
extern Uint16 Gas6_2Te123456C24DE;
extern Uint16 Gas6_2Ne123456C24DE;
extern Uint16 Gas6_2Tw123456C;
extern Uint16 Gas6_2Tw24D;
extern Uint16 Gas6_2Tw24E;
extern Uint16 Gas6_2NRept24D;
extern Uint16 Gas6_2NRept24E;
extern Uint16 Gas6_2NRept123456C;
extern Uint16 Gas6_2Cnt;


extern Uint16 PPHOIL6F_2NRept123456C;
extern Uint16 PPHOIL6F_2Ne12346C;
extern Uint16 PPHOIL6F_2Ne246A;
/*
extern Uint16 PPHOIL6F_2Ne1B;
extern Uint16 PPHOIL6F_2Ne2B;
extern Uint16 PPHOIL6F_2Ne3B;
extern Uint16 PPHOIL6F_2Ne4B;
extern Uint16 PPHOIL6F_2Ne5B;
extern Uint16 PPHOIL6F_2Ne6B;
*/
extern Uint16 PPHOIL6F_2Ne5C;
extern Uint16 PPHOIL6F_2_TE_1B;
extern Uint16 PPHOIL6F_2_TE_123456C;
extern Uint16 PPHOIL6F_2_TE_246A;
extern Uint16 PPHOIL6F_2_TE_3B;
extern Uint16 PPHOIL6F_2_TE_2B;
extern Uint16 PPHOIL6F_2_TE_5B;
extern Uint16 PPHOIL6F_2_TE_4B;
extern Uint16 PPHOIL6F_2_TE_6B;
extern Uint16 PPHOIL6F_2Tw123456C;
extern Uint16 PPHOIL6F_2Flag;
extern Uint16 PPHOIL6F_2Cnt;
extern Uint16 PPHOIL6F_2FreqSelLow;
extern Uint16 PPHOIL6F_2FreqSelHi;
extern Uint16 PPHOIL6F_2FreqSel;


extern Uint16 P3D6F_TE_1A;
extern Uint16 P3D6F_TE_2A;
extern Uint16 P3D6F_TE_3A;
extern Uint16 P3D6F_TE_4A;
extern Uint16 P3D6F_TE_5B;
extern Uint16 P3D6F_TE_6B;
extern Uint16 P3D6F_TE_1C;
extern Uint16 P3D6F_TE_2D;
extern Uint16 P3D6F_TE_3E;
extern Uint16 P3D6F_TE_4F;
extern Uint16 P3D6F_TE_5F;
extern Uint16 P3D6F_TE_6F;
extern Uint16 P3D6FNe1A;
extern Uint16 P3D6FNe2A;
extern Uint16 P3D6FNe3A;
extern Uint16 P3D6FNe4A;
extern Uint16 P3D6FNe5B;
extern Uint16 P3D6FNe6B;
extern Uint16 P3D6FNe1C;
extern Uint16 P3D6FNe2D;
extern Uint16 P3D6FNe3E;
extern Uint16 P3D6FNe4F;
extern Uint16 P3D6FNe5F;
extern Uint16 P3D6FNe6F;
extern Uint16 P3D6FTw1C;
extern Uint16 P3D6FTw2D;
extern Uint16 P3D6FTw3E;
extern Uint16 P3D6FTw4F;
extern Uint16 P3D6FTw5F;
extern Uint16 P3D6FTw6F;
extern Uint16 P3D6FNRept1C;
extern Uint16 P3D6FNRept2D;
extern Uint16 P3D6FNRept3E;
extern Uint16 P3D6FNRept4F;
extern Uint16 P3D6FNRept5F;
extern Uint16 P3D6FFlag;
extern Uint16 P3D6FCnt;
extern Uint16 P3D6FFreqSelLow;
extern Uint16 P3D6FFreqSelHi;
extern Uint16 P3D6FFreqSel;


extern Uint16 HRT1T22FMode_TW_A1;
extern Uint16 HRT1T22FMode_TW_B1;
extern Uint16 HRT1T22FMode_TW_B2;
extern Uint16 HRT1T22FMode_TW_B3;
extern Uint16 HRT1T22FMode_TW_B4;
extern Uint16 HRT1T22FMode_TW_B5;
extern Uint16 HRT1T22FMode_TW_B6;
extern Uint16 HRT1T22FMode_TW_B7;
extern Uint16 HRT1T22FMode_TE_A1;
extern Uint16 HRT1T22FMode_TE_B1;
extern Uint16 HRT1T22FMode_TE_B2;
extern Uint16 HRT1T22FMode_TE_B3;
extern Uint16 HRT1T22FMode_TE_B4;
extern Uint16 HRT1T22FMode_TE_B5;
extern Uint16 HRT1T22FMode_TE_B6;
extern Uint16 HRT1T22FMode_TE_B7;
extern Uint16 HRT1T22FMode_NE_A1;
extern Uint16 HRT1T22FMode_NE_B1;
extern Uint16 HRT1T22FMode_NE_B2;
extern Uint16 HRT1T22FMode_NE_B3;
extern Uint16 HRT1T22FMode_NE_B4;
extern Uint16 HRT1T22FMode_NE_B5;
extern Uint16 HRT1T22FMode_NE_B6;
extern Uint16 HRT1T22FMode_NE_B7;
extern Uint16 HRT1T22FMode_NREPT_B2;
extern Uint16 HRT1T22FMode_NREPT_B3;
extern Uint16 HRT1T22FMode_NREPT_B4;
extern Uint16 HRT1T22FMode_NREPT_B5;
extern Uint16 HRT1T22FMode_NREPT_B6;
extern Uint16 HRT1T22FMode_NREPT_B7;
extern Uint16 HRT1T22FFlag;
extern Uint16 HRT1T22FCnt;
extern Uint16 HRT1T22FFreqSel;



//Array variables defination
extern float PulseGainAry[501];
extern Uint16 FreqAry[];
extern Uint16 RelayAry[];

extern Uint16 AdderLowAry[11];
extern Uint32 AdderResAry[11];
extern Uint16 NoiseDataAry[512];

extern Uint16 NintyWidthAry[9];

extern Uint16 PP6FMiniNumAry[6];
extern Uint16 Oil3MiniNumAry[3];
extern Uint16 Gas6FMiniNumAry[6];
extern Uint16 Gas6_2FMiniNumAry[6];
extern Uint16 PPLOIL6FMiniNumAry[6];
extern Uint16 PP3FMiniNumAry[3];
extern Uint16 FBW2FMiniNumAry[2];
extern Uint16 PPHOIL6FMiniNumAry[6];
extern Uint16 PPHOIL6F_2MiniNumAry[6];
extern Uint16 P3D6FMiniNumAry[6];
extern Uint16 HRT1T22FMiniNumAry[2];
extern int32 MiniAddAry[12];

extern Uint16 PP6FreqSelAry[7];
extern Uint16 Oil3FreqSelAry[4];
extern Uint16 Gas6FreqSelAry[7];
extern Uint16 Gas6_2FreqSelAry[7];
extern Uint16 PPLOIL6FFreqSelAry[7];
extern Uint16 PP3FreqSelAry[4];
extern Uint16 FBW2FFreqSelAry[3];
extern Uint16 PPHOIL6FFreqSelAry[7];
extern Uint16 PPHOIL6F_2FreqSelAry[7];
extern Uint16 P3D6FFreqSelAry[7];
extern Uint16 HRT1T22FFreqSelAry[3];

extern Uint16 T2DFreqSelAry[4];
extern Uint16 T2DDETelAAry[7];
extern Uint16 T2DDETelBAry[7];
extern Uint16 T2DDETelCAry[4];
extern Uint16 DFT1T2DFreqSelAry[3];
extern Uint16 DT2DMiniNumAry[3];
extern Uint16 MT2DMiniNumAry[3];
extern Uint16 DFT1T2DMiniNumAry[3];

extern Uint16 T12DTelABAry[5];
extern Uint16 T12DMiniNumAry[3];

extern Uint16 T1T2TwAAry[10];
extern Uint16 T1T2NeAAry[10];
extern Uint16 T1T2NReptAAry[10];
extern Uint16 T1T2MiniNumAry[3];

//Pointer variables defination
extern Uint16 * TableTempPt;
extern Uint16 * SaveSTempPt;
extern Uint16 * CheckTablePt;
extern int * SaveNTempPt;
extern Uint16 * SendTempPt;
extern Uint16 * StoreMiniAryPt;
extern Uint16 * MiniTablePt;
extern Uint16 * SaveTablePt;
extern Uint16 WorkModeChoice[];
