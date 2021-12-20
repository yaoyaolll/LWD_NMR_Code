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
#include "MyFunctions.h"
#include "MyVariables.h"

// 继电器控制变量和发射频率变量
float TransmitFre_f;  		// 发射频率float型
Uint16 TransmitFre;       	// 发射频率Uint16型
float RelayCtrlCode_f;   	// 继电器控制码float型
Uint16 RelayCtrlCode; 		// 继电器控制码Uint16型

// PAPS结构体
PAPSEntry_t PAPSEntry;

// 参数表的入口指针
volatile TuningTableEntry_t* TuningTableEntry;	// 刻度参数表
volatile ConfigTableEntry_t* ConfigTableEntry;	// 仪器配置参数表

// 高斯拟合变量
float x[9];
float y[9];
float a;
float b;
float c;

// 发送模式数据长度
Uint16 modeDataSendLen;

// 事件板状态字
enum EB_STATE EventBoardState;

//void (*eventFunc[])(void) = {0, IdleStateCtl, OperaStateCtl, CasDctStateCtl, TestStateCtl, ScaleStateCtl, AcqFinStateCtl};
void (*eventFunc[])(void) = {0, IdleStateCtl, OperaStateCtl, CasDctStateCtl, AcqFinStateCtl};

// 下述标志位通知模式函数进行事件处理
Uint16 _caseingDetectFlag = CLEAR;	 	// 套管检测启动标志位
Uint16 _operationFlag = CLEAR;		 	// 工作模式启动标志位
Uint16 _modeDataSendFlag = CLEAR;	 	// 上传模式数据标志位
Uint16 _casingDetectErrFlag = CLEAR; 	// 工作模式启动时，套管检测是否正常
Uint16 _casingOrOperaFlag = CLEAR;	 	// 用作流程判断，在ACQ_FIN状态时，上一个状态是Casing还是Operation
Uint16 _PAPSUpDataFlag = CLEAR;			// PAPS上传数据标志位

// 模式标志位
Uint16 SingleModeFlag;
Uint16 PPModeFlag;
Uint16 PPDIFModeFlag;
Uint16 PPT1ModeFlag;
Uint16 PPOFTWModeFlag;
Uint16 PPShortModeFlag;
Uint16 TuningModeFlag;	// 调谐刻度模式
Uint16 ScanModeFlag; 	// scan mode flag：扫频模式标志，为1时要进入扫频模式
Uint16 ScaleModeFlag;
Uint16 HoleModeFlag;
Uint16 PulseAcqFlag;

// 刻度模式参数表与测井模式参数表共有部分
Uint16 CenterFreq;		   // 工作频率
Uint16 ScanDeltaFreq;	   // 扫描步进频率
Uint16 NoiseAcqTime;	   // 噪声采集时间
Uint16 NoiseAcqFreq;	   // 噪声采样率
Uint16 SiglAcqPrdNum;	   // signal acquisition period number:回波信号采集周期数
Uint16 SiglAcqFreqTim;	   // 回波采样率相对于回波信号频率的倍数，signal acquisition freqency times
Uint16 EchoAcqWindowShift; // 回波采集时间窗偏移
Uint16 Width90Pulse;	   // 90度脉冲宽度

// 刻度模式参数表私有部分
Uint16 RelayCode;	// 调谐码
Uint16 ScalePeriod; // 刻度采集指令时间间隔
Uint16 Angle180Pulse;
Uint16 Calib_TE;		   // 刻度时的TE
Uint16 Calib_NE;		   // 刻度时的NE
Uint16 PulseTestPulseTime; // 脉冲检测时的发射脉冲宽度
Uint16 PulseTestAcqFreq;   // 脉冲检测时的采样率

// 测井模式参数表私有部分
// STWTE模式
Uint16 STWTE_Period; // 模式周期
Uint16 STWTE_TE;	 // NE值
Uint16 STWTE_NE;	 // TE值

// PPMODE
Uint16 PPM_Period;
Uint16 PPM_TW_1C;
Uint16 PPM_TE_1A;
Uint16 PPM_TE_1C;
Uint16 PPM_NE_1A;
Uint16 PPM_NE_1C;
Uint16 PPM_Nrept_1C;

// PPDIF MODE
Uint16 PPDIF_Period;
Uint16 PPDIF_TW_1C;
Uint16 PPDIF_TW_1B;
Uint16 PPDIF_TE_1A1B;
Uint16 PPDIF_TE_1C;
Uint16 PPDIF_NE_1A1B;
Uint16 PPDIF_NE_1C;
Uint16 PPDIF_Nrept_1C;

// PPT1 MODE
Uint16 PPT1_Period;
Uint16 PPT1_TW_1C;
Uint16 PPT1_TW_1D;
Uint16 PPT1_TW_1E;
Uint16 PPT1_TW_1F;
Uint16 PPT1_TW_1G;
Uint16 PPT1_TW_1H;
Uint16 PPT1_TW_Code;
Uint16 PPT1_TE_1A;
Uint16 PPT1_TE_1CDEFGH;
Uint16 PPT1_NE_1A;
Uint16 PPT1_NE_1C;
Uint16 PPT1_NE_1DEFGH;
Uint16 PPT1_Nrept_1C;

// PPOFTW MODE
Uint16 PPOFTW_Period;
Uint16 PPOFTW_TW_1C;
Uint16 PPOFTW_TW_1D;
Uint16 PPOFTW_TW_1E;
Uint16 PPOFTW_TW_1F;
Uint16 PPOFTW_TW_1G;
Uint16 PPOFTW_TW_1H;
Uint16 PPOFTW_TE_1ADEFGH;
Uint16 PPOFTW_TE_1C;
Uint16 PPOFTW_Nrept_1C;

// PPShort
Uint16 PPShort_Period;
Uint16 PPShort_TW_1C;
Uint16 PPShort_TE_1A;
Uint16 PPShort_TE_1C;
Uint16 PPShort_NE_1A;
Uint16 PPShort_NE_1C;
Uint16 PPShort_Nrept_1C;

Uint16 FreqNum2;
Uint16 MiniCycCnt1;
Uint16 MiniCycCnt2;
Uint16 MiniCycCnt3;
Uint16 MiniNoiseMax;
Uint16 MiniBuf;

// 回波个数和回波点个数
Uint32 DataTotalNum;
Uint16 EchoNum;

//Quantity variables defination
//Used by state 1 ms machine
Uint16 HVState;	   //state of HV:高压状态
Uint32 PulseCycle; //
Uint32 MDumpTime;
Uint32 SDumpTime;
Uint32 CutTime;
Uint16 CutTimeLow;
Uint16 CutTimeHi;
//Used by send parameter table
Uint16 SendTableFlag; //send table flag:发送参数表标志，为1时发送参数表
Uint32 SendCnt;		  //send table counter:发送表时用到的计数器，指示已发送了多少数据
Uint16 ZeroCnt;
Uint16 DENum;
Uint16 PhaseFlag; //phase flag:90度发射正反相标志
//Used by scan and miniscan mode

Uint16 ScanSignalNum; //number of signal in scan mode:扫频时的信号采集点数

Uint16 BandCnt;		//band counter:扫频时的频带计数器
Uint16 ScaleCnt;	//scale counter:刻度时刻度次数计数器
Uint16 MiniFreqCnt; //freqency counter in mini freqency:迷你扫频时的扫频次数计数器
Uint16 FreqScan;	//scaning frequency
Uint16 MiniFreq;
Uint16 NTimeDec; //noise acquisition time
Uint16 STimeDec; //signal acquisition time in scan mode

Uint16 SaveCnt;

Uint16 CycleFlag;
Uint16 DumpSustainFlag;
Uint16 DSTTimeOne;
//Used in noise acquisition mode
Uint16 NoiseDivFreq;
Uint16 NoiseDivNum;
Uint16 NoiseAcqNum; //number of noise acquisition data
Uint16 NoiseAcqCnt;
Uint32 NoiseSum; // sum of noise data
//_iq NoiseSumIQ;
_iq NoiseAveShiftIQ; //噪声数值的均值（有2v偏置）
_iq NoiseAveIQ;		 //噪声数值的均值
_iq NoiseCalNumIQ;	 //计算的噪声数据个数
_iq NoiseMaxValIQ;	 //最大噪声
_iq NoiseOfsIQ;		 //噪声偏差
_iq NoiseOfsAbsIQ;
_iq NoiseSqrAveIQ;
_iq3 NoiseOfsIQ3;
_iq3 NoiseSquSumIQ3; //偏差平方和,即方差
_iq3 NoiseSquAveIQ3; //方差均值
					 //Used by DDS configuration
float DDSFreq;		 //dds需要配置的频率
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
int32 SinOne; //计算用
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
Uint16 SignalCalNum; //number of signal data in calculation
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
Uint16 MainDumpTime; //主泄放时间
					 //Used in in-out-bridge parameter calculation
Uint16 ScaleDDSDiv;	 //刻度激励用dds分频系数
Uint16 HalfFreqNum;	 //起震计数值
Uint16 BriWidthData; //内外桥宽度计数值（注意数据格式）
Uint16 BriMid;
//Used in pulse acquisition mode

Uint16 MatFreqSel;
Uint16 MatFreq;
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

Uint16 DEMn;
Uint16 WidthCnt;
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
Uint16 EchoAcqTime; //采集时间
Uint16 EchoAcqTimeFHalf;
Uint16 EchoAcqTimeBHalf;

Uint16 InverseTurnFlag;

float TNMid1;
float TNMid2;
Uint32 TNTime;
Uint32 Tes; //短te时间
Uint32 Tel;
Uint32 TesCmp; // 取整的短te
Uint32 TelCmp; //取整的长te

Uint32 CmpTesHalf; //cmp:compare
Uint32 CmpTelHalf; //长TE下TEL_C
Uint32 Cmp90;
Uint32 CmpI90;
Uint32 Cmp180FHalf;
Uint32 Cmp180BHalf;

Uint32 Cut90Time; //90度隔离时间
Uint16 Cut90TimeLow;
Uint16 Cut90TimeHi;
Uint32 CutI90Time; //反90度隔离时间
Uint16 CutI90TimeLow;
Uint16 CutI90TimeHi;
Uint32 Open180LTime; //长TE下的DEC打开时间
Uint16 Open180LTimeMS;
Uint16 Open180LTimeLow;
Uint16 Open180LTimeHi;
Uint32 Cut180LTime; //长TE下的180隔离时间
Uint16 Cut180LTimeLow;
Uint16 Cut180LTimeHi;
Uint32 Cut180STime;
Uint16 Cut180STimeLow;
Uint16 Cut180STimeHi;
Uint32 Open180STime; //长TE下的DEC打开时间
Uint16 Open180STimeLow;
Uint16 Open180STimeHi;

Uint16 EchoAcqNum; //echo采集点数

Uint32 TesCCheck;
Uint32 TelCCheck;
Uint16 P90PrdNum;
Uint16 P180PrdNum;

Uint16 Acq90Num;	//90度激励采集点数
Uint16 Acq180Num;	//180激励采集点数
Uint16 Strip90Num;	//90度激励舍去点数
Uint16 Strip180Num; //180度激励舍去点数
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

Uint16 DownTableFlag;
Uint16 WorkMode;

Uint16 ToMSFreq;	   //frequency transferred to miniscan() function
Uint32 ToMSNoiseAddr;  //noise-store address transferred to miniscan() function
Uint32 ToMSSignalAddr; //signal-store address transferred to miniscan() function

Uint16 ReadTableBuf;
Uint16 ZeroOne;

Uint32 MiniStorAddr1;
Uint32 MiniStorAddr2;
Uint32 MiniStorAddr3;
Uint32 MiniStorAddr4;
Uint32 MiniStorAddr5;
Uint32 MiniStorAddr6;

//Array variables defination
float PulseGainAry[501];
// Uint16 FreqAry[BAND_NUM];
// Uint16 RelayAry[BAND_NUM];

Uint16 AdderLowAry[11];
Uint32 AdderResAry[11];
Uint16 NoiseDataAry[512];

Uint16 NintyWidthAry[9];

int32 MiniAddAry[12];

//Pointer variables defination
Uint16 *TableTempPt;
Uint16 *SaveSTempPt;
Uint16 *CheckTablePt;
int *SaveNTempPt;
Uint16 *SendTempPt;
Uint16 *StoreMiniAryPt;
Uint16 *MiniTablePt;
Uint16 *ChgTablePt;
Uint16 *SaveTablePt;

Uint16 SendTableID;			   // 上传表ID

void (*singleOrderFunc[])(void) = {EmptyDeal, InquireDeal, OperationDeal, CasingDeal, DataUpDeal, ModeConfirmDeal, K1K2EnDeal, K1K2DisDeal, HVStateDeal, SysCheckDeal, PAPSDataUpDeal};

#pragma DATA_SECTION(singleOrderFunc, "MyVariablesZone");
#pragma DATA_SECTION(SendTableID, "MyVariablesZone");

#pragma DATA_SECTION(HVState, "MyVariablesZone");
#pragma DATA_SECTION(PulseCycle, "MyVariablesZone");
#pragma DATA_SECTION(MDumpTime, "MyVariablesZone");
#pragma DATA_SECTION(SDumpTime, "MyVariablesZone");
#pragma DATA_SECTION(CutTime, "MyVariablesZone");
#pragma DATA_SECTION(CutTimeLow, "MyVariablesZone");
#pragma DATA_SECTION(CutTimeHi, "MyVariablesZone");

#pragma DATA_SECTION(SendTableFlag, "MyVariablesZone");
#pragma DATA_SECTION(SendCnt, "MyVariablesZone");
#pragma DATA_SECTION(ZeroCnt, "MyVariablesZone");
#pragma DATA_SECTION(DENum, "MyVariablesZone");
#pragma DATA_SECTION(PhaseFlag, "MyVariablesZone");

#pragma DATA_SECTION(ScanModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqFreq, "MyVariablesZone");
#pragma DATA_SECTION(ScanSignalNum, "MyVariablesZone");
#pragma DATA_SECTION(BandCnt, "MyVariablesZone");
#pragma DATA_SECTION(ScaleCnt, "MyVariablesZone");
#pragma DATA_SECTION(MiniFreqCnt, "MyVariablesZone");
#pragma DATA_SECTION(FreqScan, "MyVariablesZone");
#pragma DATA_SECTION(MiniFreq, "MyVariablesZone");
#pragma DATA_SECTION(NTimeDec, "MyVariablesZone");
#pragma DATA_SECTION(STimeDec, "MyVariablesZone");

#pragma DATA_SECTION(SaveCnt, "MyVariablesZone");

#pragma DATA_SECTION(CycleFlag, "MyVariablesZone");
#pragma DATA_SECTION(DumpSustainFlag, "MyVariablesZone");
#pragma DATA_SECTION(DSTTimeOne, "MyVariablesZone");

#pragma DATA_SECTION(NoiseDivFreq, "MyVariablesZone");
#pragma DATA_SECTION(NoiseDivNum, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqNum, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqCnt, "MyVariablesZone");
#pragma DATA_SECTION(NoiseSum, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAveShiftIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAveIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseCalNumIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseMaxValIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsAbsIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseSqrAveIQ, "MyVariablesZone");
#pragma DATA_SECTION(NoiseOfsIQ3, "MyVariablesZone");
#pragma DATA_SECTION(NoiseSquSumIQ3, "MyVariablesZone");
#pragma DATA_SECTION(NoiseSquAveIQ3, "MyVariablesZone");

#pragma DATA_SECTION(DDSFreq, "MyVariablesZone");
#pragma DATA_SECTION(CalDivData, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid1, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid2, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid3, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid4, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid5, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid6, "MyVariablesZone");
#pragma DATA_SECTION(DDSMid7, "MyVariablesZone");
#pragma DATA_SECTION(DDSCfgWords, "MyVariablesZone");
#pragma DATA_SECTION(DDSRefItg, "MyVariablesZone");
#pragma DATA_SECTION(DDSRefDcm, "MyVariablesZone");
#pragma DATA_SECTION(DDSCfgHi, "MyVariablesZone");
#pragma DATA_SECTION(DDSCfgLow, "MyVariablesZone");

#pragma DATA_SECTION(AdderCnt, "MyVariablesZone");
#pragma DATA_SECTION(SinOne, "MyVariablesZone");
#pragma DATA_SECTION(SinTwo, "MyVariablesZone");
#pragma DATA_SECTION(SinThree, "MyVariablesZone");
#pragma DATA_SECTION(SinFour, "MyVariablesZone");
#pragma DATA_SECTION(CosOne, "MyVariablesZone");
#pragma DATA_SECTION(CosTwo, "MyVariablesZone");
#pragma DATA_SECTION(CosThree, "MyVariablesZone");
#pragma DATA_SECTION(CosFour, "MyVariablesZone");
#pragma DATA_SECTION(CosFive, "MyVariablesZone");
#pragma DATA_SECTION(SinSumIQ, "MyVariablesZone");
#pragma DATA_SECTION(CosSumIQ, "MyVariablesZone");
#pragma DATA_SECTION(SignalCalNum, "MyVariablesZone");
#pragma DATA_SECTION(SinAveIQ, "MyVariablesZone");
#pragma DATA_SECTION(CosAveIQ, "MyVariablesZone");
#pragma DATA_SECTION(SignalAmpIQ, "MyVariablesZone");
#pragma DATA_SECTION(SignalPhaIQ, "MyVariablesZone");

#pragma DATA_SECTION(DumpPara1, "MyVariablesZone");
#pragma DATA_SECTION(DumpPara2, "MyVariablesZone");
#pragma DATA_SECTION(DumpPara3, "MyVariablesZone");
#pragma DATA_SECTION(DumpPara4, "MyVariablesZone");
#pragma DATA_SECTION(DumpPara5, "MyVariablesZone");
#pragma DATA_SECTION(DumpPara6, "MyVariablesZone");
#pragma DATA_SECTION(MainDumpTime, "MyVariablesZone");

#pragma DATA_SECTION(ScaleDDSDiv, "MyVariablesZone");
#pragma DATA_SECTION(HalfFreqNum, "MyVariablesZone");
#pragma DATA_SECTION(BriWidthData, "MyVariablesZone");
#pragma DATA_SECTION(BriMid, "MyVariablesZone");

#pragma DATA_SECTION(MatFreqSel, "MyVariablesZone");
#pragma DATA_SECTION(MatFreq, "MyVariablesZone");
#pragma DATA_SECTION(PulseAcqFlag, "MyVariablesZone");
#pragma DATA_SECTION(PulseTime, "MyVariablesZone");
#pragma DATA_SECTION(PulseNum, "MyVariablesZone");
#pragma DATA_SECTION(PulseDivNum, "MyVariablesZone");
#pragma DATA_SECTION(PulseMid4, "MyVariablesZone");
#pragma DATA_SECTION(PulseMid1, "MyVariablesZone");
#pragma DATA_SECTION(PulseMid2, "MyVariablesZone");
#pragma DATA_SECTION(PulseMid3, "MyVariablesZone");
#pragma DATA_SECTION(PulseDataCnt, "MyVariablesZone");

#pragma DATA_SECTION(PdPara1, "MyVariablesZone");
#pragma DATA_SECTION(PdPara2, "MyVariablesZone");
#pragma DATA_SECTION(PdPara3, "MyVariablesZone");
#pragma DATA_SECTION(Pd90Time, "MyVariablesZone");
#pragma DATA_SECTION(Pd180Time, "MyVariablesZone");

#pragma DATA_SECTION(PulseGain, "MyVariablesZone");
#pragma DATA_SECTION(PulseGainIQ, "MyVariablesZone");
#pragma DATA_SECTION(StripBuf, "MyVariablesZone");
#pragma DATA_SECTION(PulseSum, "MyVariablesZone");
#pragma DATA_SECTION(PulseAve, "MyVariablesZone");
#pragma DATA_SECTION(PulseBuf, "MyVariablesZone");
#pragma DATA_SECTION(PulseRec, "MyVariablesZone");
#pragma DATA_SECTION(PulseRecIQ, "MyVariablesZone");
#pragma DATA_SECTION(PulseCalNum, "MyVariablesZone");
#pragma DATA_SECTION(PulseReadBuf, "MyVariablesZone");

#pragma DATA_SECTION(SingleModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(DEMn, "MyVariablesZone");
#pragma DATA_SECTION(WidthCnt, "MyVariablesZone");
#pragma DATA_SECTION(DCFreqSel, "MyVariablesZone");
#pragma DATA_SECTION(DCPulseWidth, "MyVariablesZone");
#pragma DATA_SECTION(DCTes, "MyVariablesZone");
#pragma DATA_SECTION(DCNe, "MyVariablesZone");
#pragma DATA_SECTION(DCMn, "MyVariablesZone");
#pragma DATA_SECTION(DCm, "MyVariablesZone");
#pragma DATA_SECTION(ScaleM, "MyVariablesZone");
#pragma DATA_SECTION(Ne, "MyVariablesZone");
#pragma DATA_SECTION(ScaleMn, "MyVariablesZone");

#pragma DATA_SECTION(Pulse90Width, "MyVariablesZone");
#pragma DATA_SECTION(Pulse180Width, "MyVariablesZone");
#pragma DATA_SECTION(Pulse180WidthHalf, "MyVariablesZone");
#pragma DATA_SECTION(EchoMid1, "MyVariablesZone");
#pragma DATA_SECTION(EchoMid2, "MyVariablesZone");
#pragma DATA_SECTION(EchoMid3, "MyVariablesZone");
#pragma DATA_SECTION(EchoMid4, "MyVariablesZone");
#pragma DATA_SECTION(DCWorkFreq, "MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTime, "MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTimeFHalf, "MyVariablesZone");
#pragma DATA_SECTION(EchoAcqTimeBHalf, "MyVariablesZone");

#pragma DATA_SECTION(InverseTurnFlag, "MyVariablesZone");

#pragma DATA_SECTION(TNMid1, "MyVariablesZone");
#pragma DATA_SECTION(TNMid2, "MyVariablesZone");
#pragma DATA_SECTION(TNTime, "MyVariablesZone");
#pragma DATA_SECTION(Tes, "MyVariablesZone");
#pragma DATA_SECTION(Tel, "MyVariablesZone");
#pragma DATA_SECTION(TesCmp, "MyVariablesZone");
#pragma DATA_SECTION(TelCmp, "MyVariablesZone");

#pragma DATA_SECTION(CmpTesHalf, "MyVariablesZone");
#pragma DATA_SECTION(CmpTelHalf, "MyVariablesZone");
#pragma DATA_SECTION(Cmp90, "MyVariablesZone");
#pragma DATA_SECTION(CmpI90, "MyVariablesZone");
#pragma DATA_SECTION(Cmp180FHalf, "MyVariablesZone");
#pragma DATA_SECTION(Cmp180BHalf, "MyVariablesZone");

#pragma DATA_SECTION(Cut90Time, "MyVariablesZone");
#pragma DATA_SECTION(Cut90TimeLow, "MyVariablesZone");
#pragma DATA_SECTION(Cut90TimeHi, "MyVariablesZone");
#pragma DATA_SECTION(CutI90Time, "MyVariablesZone");
#pragma DATA_SECTION(CutI90TimeLow, "MyVariablesZone");
#pragma DATA_SECTION(CutI90TimeHi, "MyVariablesZone");
#pragma DATA_SECTION(Open180LTime, "MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeMS, "MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeLow, "MyVariablesZone");
#pragma DATA_SECTION(Open180LTimeHi, "MyVariablesZone");
#pragma DATA_SECTION(Cut180LTime, "MyVariablesZone");
#pragma DATA_SECTION(Cut180LTimeLow, "MyVariablesZone");
#pragma DATA_SECTION(Cut180LTimeHi, "MyVariablesZone");
#pragma DATA_SECTION(Cut180STime, "MyVariablesZone");
#pragma DATA_SECTION(Cut180STimeLow, "MyVariablesZone");
#pragma DATA_SECTION(Cut180STimeHi, "MyVariablesZone");
#pragma DATA_SECTION(Open180STime, "MyVariablesZone");
#pragma DATA_SECTION(Open180STimeLow, "MyVariablesZone");
#pragma DATA_SECTION(Open180STimeHi, "MyVariablesZone");

#pragma DATA_SECTION(EchoAcqNum, "MyVariablesZone");

#pragma DATA_SECTION(TesCCheck, "MyVariablesZone");
#pragma DATA_SECTION(TelCCheck, "MyVariablesZone");
#pragma DATA_SECTION(P90PrdNum, "MyVariablesZone");
#pragma DATA_SECTION(P180PrdNum, "MyVariablesZone");

#pragma DATA_SECTION(Acq90Num, "MyVariablesZone");
#pragma DATA_SECTION(Acq180Num, "MyVariablesZone");
#pragma DATA_SECTION(Strip90Num, "MyVariablesZone");
#pragma DATA_SECTION(Strip180Num, "MyVariablesZone");

#pragma DATA_SECTION(SdAcqNum1, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum2, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum3, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4Low, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum4Hi, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5Low, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum5Hi, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6Low, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum6Hi, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7Low, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqNum7Hi, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid1, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid2, "MyVariablesZone");
#pragma DATA_SECTION(SdAcqTimeMid3, "MyVariablesZone");

#pragma DATA_SECTION(StoreCnt, "MyVariablesZone");
#pragma DATA_SECTION(PulseAmpCrtIQ, "MyVariablesZone");
#pragma DATA_SECTION(Pulse90StoreAddr, "MyVariablesZone");
#pragma DATA_SECTION(PulseF180StoreAddr, "MyVariablesZone");
#pragma DATA_SECTION(PulseL180StoreAddr, "MyVariablesZone");
#pragma DATA_SECTION(EchoStorAddr, "MyVariablesZone");

#pragma DATA_SECTION(DownTableFlag, "MyVariablesZone");
#pragma DATA_SECTION(WorkMode, "MyVariablesZone");
#pragma DATA_SECTION(ScaleModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(HoleModeFlag, "MyVariablesZone");

#pragma DATA_SECTION(ToMSFreq, "MyVariablesZone");
#pragma DATA_SECTION(ToMSNoiseAddr, "MyVariablesZone");
#pragma DATA_SECTION(ToMSSignalAddr, "MyVariablesZone");

#pragma DATA_SECTION(ReadTableBuf, "MyVariablesZone");
#pragma DATA_SECTION(ZeroOne, "MyVariablesZone");

#pragma DATA_SECTION(PulseGainAry, "MyVariablesZone");
//#pragma DATA_SECTION(FreqAry, "MyVariablesZone");
//#pragma DATA_SECTION(RelayAry, "MyVariablesZone");

#pragma DATA_SECTION(AdderLowAry, "MyVariablesZone");
#pragma DATA_SECTION(AdderResAry, "MyVariablesZone");
#pragma DATA_SECTION(NoiseDataAry, "MyVariablesZone");

#pragma DATA_SECTION(NintyWidthAry, "MyVariablesZone");

#pragma DATA_SECTION(MiniAddAry, "MyVariablesZone");

#pragma DATA_SECTION(TableTempPt, "MyVariablesZone");
#pragma DATA_SECTION(SaveSTempPt, "MyVariablesZone");
#pragma DATA_SECTION(CheckTablePt, "MyVariablesZone");
#pragma DATA_SECTION(SaveNTempPt, "MyVariablesZone");
#pragma DATA_SECTION(StoreMiniAryPt, "MyVariablesZone");
#pragma DATA_SECTION(MiniTablePt, "MyVariablesZone");
#pragma DATA_SECTION(ChgTablePt, "MyVariablesZone");
#pragma DATA_SECTION(SaveTablePt, "MyVariablesZone");

#pragma DATA_SECTION(PPModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(PPDIFModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(PPT1ModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTWModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(PPShortModeFlag, "MyVariablesZone");
#pragma DATA_SECTION(TuningModeFlag, "MyVariablesZone");

#pragma DATA_SECTION(CenterFreq, "MyVariablesZone");
#pragma DATA_SECTION(ScanDeltaFreq, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqTime, "MyVariablesZone");
#pragma DATA_SECTION(NoiseAcqFreq, "MyVariablesZone");
#pragma DATA_SECTION(SiglAcqPrdNum, "MyVariablesZone");
#pragma DATA_SECTION(SiglAcqFreqTim, "MyVariablesZone");
#pragma DATA_SECTION(EchoAcqWindowShift, "MyVariablesZone");
#pragma DATA_SECTION(Width90Pulse, "MyVariablesZone");

#pragma DATA_SECTION(ScalePeriod, "MyVariablesZone");
#pragma DATA_SECTION(Angle180Pulse, "MyVariablesZone");
#pragma DATA_SECTION(Calib_TE, "MyVariablesZone");
#pragma DATA_SECTION(Calib_NE, "MyVariablesZone");
#pragma DATA_SECTION(PulseTestPulseTime, "MyVariablesZone");
#pragma DATA_SECTION(PulseTestAcqFreq, "MyVariablesZone");

#pragma DATA_SECTION(STWTE_Period, "MyVariablesZone");
#pragma DATA_SECTION(STWTE_TE, "MyVariablesZone");
#pragma DATA_SECTION(STWTE_NE, "MyVariablesZone");

#pragma DATA_SECTION(PPM_Period, "MyVariablesZone");
#pragma DATA_SECTION(PPM_TW_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPM_TE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPM_TE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPM_NE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPM_NE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPM_Nrept_1C, "MyVariablesZone");

#pragma DATA_SECTION(PPDIF_Period, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_TW_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_TW_1B, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_TE_1A1B, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_TE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_NE_1A1B, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_NE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPDIF_Nrept_1C, "MyVariablesZone");

#pragma DATA_SECTION(PPT1_Period, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1D, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1E, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1F, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1G, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_1H, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TW_Code, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_TE_1CDEFGH, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_NE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_NE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_NE_1DEFGH, "MyVariablesZone");
#pragma DATA_SECTION(PPT1_Nrept_1C, "MyVariablesZone");

#pragma DATA_SECTION(PPOFTW_Period, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1D, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1E, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1F, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1G, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TW_1H, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TE_1ADEFGH, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_TE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPOFTW_Nrept_1C, "MyVariablesZone");

#pragma DATA_SECTION(PPShort_Period, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_TW_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_TE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_TE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_NE_1A, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_NE_1C, "MyVariablesZone");
#pragma DATA_SECTION(PPShort_Nrept_1C, "MyVariablesZone");

#pragma DATA_SECTION(FreqNum2, "MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt1, "MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt2, "MyVariablesZone");
#pragma DATA_SECTION(MiniCycCnt3, "MyVariablesZone");
#pragma DATA_SECTION(MiniNoiseMax, "MyVariablesZone");
#pragma DATA_SECTION(MiniBuf, "MyVariablesZone");

#pragma DATA_SECTION(DataTotalNum, "MyVariablesZone");
#pragma DATA_SECTION(EchoNum, "MyVariablesZone");
#pragma DATA_SECTION(EventBoardState, "MyVariablesZone");
#pragma DATA_SECTION(eventFunc, "MyVariablesZone");

#pragma DATA_SECTION(_caseingDetectFlag, "MyVariablesZone");
#pragma DATA_SECTION(_operationFlag, "MyVariablesZone");
#pragma DATA_SECTION(_modeDataSendFlag, "MyVariablesZone");
#pragma DATA_SECTION(modeDataSendLen, "MyVariablesZone");
#pragma DATA_SECTION(_casingDetectErrFlag, "MyVariablesZone");
#pragma DATA_SECTION(_casingOrOperaFlag, "MyVariablesZone");
#pragma DATA_SECTION(_PAPSUpDataFlag, "MyVariablesZone");

#pragma DATA_SECTION(x, "MyVariablesZone");
#pragma DATA_SECTION(y, "MyVariablesZone");
#pragma DATA_SECTION(a, "MyVariablesZone");
#pragma DATA_SECTION(b, "MyVariablesZone");
#pragma DATA_SECTION(c, "MyVariablesZone");

#pragma DATA_SECTION(RelayCode, "MyVariablesZone");

#pragma DATA_SECTION(TransmitFre_f, "MyVariablesZone");
#pragma DATA_SECTION(TransmitFre, "MyVariablesZone");
#pragma DATA_SECTION(RelayCtrlCode_f, "MyVariablesZone");
#pragma DATA_SECTION(RelayCtrlCode, "MyVariablesZone");

#pragma DATA_SECTION(ConfigTableEntry, "MyVariablesZone");
#pragma DATA_SECTION(TuningTableEntry, "MyVariablesZone");

#pragma DATA_SECTION(PAPSEntry, "MyVariablesZone");
