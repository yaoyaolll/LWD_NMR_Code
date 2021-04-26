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

// �¼���״̬��
enum EB_STATE
{
	IDLE_STAT = 0, OPERATION_STAT, CASING_DETECT_STAT, ACQ_FIN_STAT
};

#define STATE_NUM	4

extern void (* eventFunc[])(void);

extern Uint16 _caseingDetectFlag;
extern Uint16 _operationFlag;
extern Uint16 _modeDataSendFlag;

// ģʽ��־λ
extern Uint16 PPModeFlag;
extern Uint16 PPDIFModeFlag;
extern Uint16 PPT1ModeFlag;
extern Uint16 PPOFTWModeFlag;
extern Uint16 PPShortModeFlag;


// �̶�ģʽ��������⾮ģʽ�������в���
extern Uint16 CenterFreq;         // ����Ƶ��
extern Uint16 ScanDeltaFreq;      // ɨ�貽��Ƶ��
extern Uint16 NoiseAcqTime;       // �����ɼ�ʱ��
extern Uint16 NoiseAcqFreq;       // ����������
extern Uint16 HegtWidth;          // 180������Ƕȣ��������ݴ˽Ƕȼ����������
extern Uint16 SiglAcqPrdNum;	   //signal acquisition period number:�ز��źŲɼ�������
extern Uint16 SiglAcqFreqTim;     // �ز�����������ڻز��ź�Ƶ�ʵı�����signal acquisition freqency times
extern Uint16 EchoAcqWindowShift; // �ز��ɼ�ʱ�䴰ƫ��
extern Uint16 Width90Pulse;       // 90��������


// �̶�ģʽ������˽�в���
extern Uint16 ScalePeriod;           // �̶Ȳɼ�ָ��ʱ����
extern Uint16 Angle180Pulse;
extern Uint16 Calib_TE;          // �̶�ʱ��TE
extern Uint16 Calib_NE;          // �̶�ʱ��NE
extern Uint16 PulseTestPulseTime; // ������ʱ�ķ���������
extern Uint16 PulseTestAcqFreq; // ������ʱ�Ĳ�����

// �⾮ģʽ������˽�в���
// STWTEģʽ
extern Uint16 STWTE_Period;     // ģʽ����
extern Uint16 STWTE_TE;         // NEֵ
extern Uint16 STWTE_NE;         // TEֵ

// PPMODE
extern Uint16 PPM_Period;
extern Uint16 PPM_TW_1C;
extern Uint16 PPM_TE_1A;
extern Uint16 PPM_TE_1C;
extern Uint16 PPM_NE_1A;
extern Uint16 PPM_NE_1C;
extern Uint16 PPM_Nrept_1C;

// PPDIF MODE
extern Uint16 PPDIF_Period;
extern Uint16 PPDIF_TW_1C;
extern Uint16 PPDIF_TW_1B;
extern Uint16 PPDIF_TE_1A1B;
extern Uint16 PPDIF_TE_1C;
extern Uint16 PPDIF_NE_1A1B;
extern Uint16 PPDIF_NE_1C;
extern Uint16 PPDIF_Nrept_1C;

// PPT1 MODE
extern Uint16 PPT1_Period;
extern Uint16 PPT1_TW_1C;
extern Uint16 PPT1_TW_1D;
extern Uint16 PPT1_TW_1E;
extern Uint16 PPT1_TW_1F;
extern Uint16 PPT1_TW_1G;
extern Uint16 PPT1_TW_1H;
extern Uint16 PPT1_TW_Code;
extern Uint16 PPT1_TE_1A;
extern Uint16 PPT1_TE_1CDEFGH;
extern Uint16 PPT1_NE_1A;
extern Uint16 PPT1_NE_1C;
extern Uint16 PPT1_NE_1DEFGH;
extern Uint16 PPT1_Nrept_1C;

// PPOFTW MODE
extern Uint16 PPOFTW_Period;
extern Uint16 PPOFTW_TW_1C;
extern Uint16 PPOFTW_TW_1D;
extern Uint16 PPOFTW_TW_1E;
extern Uint16 PPOFTW_TW_1F;
extern Uint16 PPOFTW_TW_1G;
extern Uint16 PPOFTW_TW_1H;
extern Uint16 PPOFTW_TE_1ADEFGH;
extern Uint16 PPOFTW_TE_1C;
extern Uint16 PPOFTW_Nrept_1C;

// PPShort
extern Uint16 PPShort_Period;
extern Uint16 PPShort_TW_1C;
extern Uint16 PPShort_TE_1A;
extern Uint16 PPShort_TE_1C;
extern Uint16 PPShort_NE_1A;
extern Uint16 PPShort_NE_1C;
extern Uint16 PPShort_Nrept_1C;


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
extern Uint16 SiglAcqPrdNum;
extern Uint16 SiglAcqFreqTim;

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
extern _iq NoiseAveShiftIQ;    //������ֵ�ľ�ֵ����2vƫ�ã�
extern _iq NoiseAveIQ;    //������ֵ�ľ�ֵ
extern _iq NoiseCalNumIQ;   //������������ݸ���
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
extern int32 SinOne;           //������
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
extern Uint16 MainDumpTime;     //��й��ʱ��

extern Uint16 ScaleDDSDiv;  //�̶ȼ�����dds��Ƶϵ��
extern Uint16 HalfFreqNum;     //�������ֵ
extern Uint16 BriWidthData;      //�����ſ�ȼ���ֵ��ע�����ݸ�ʽ��
extern Uint16 BriMid;

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
extern Uint16 HegtWidth;   //�ز����������ȼĴ�����ֵ
extern Uint16 SftWinWidth;  //�ɼ���ʱ�们���Ĵ���;
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
extern Uint16 EchoAcqTime;      //�ɼ�ʱ��
extern Uint16 EchoAcqTimeFHalf;
extern Uint16 EchoAcqTimeBHalf;

extern Uint16 InverseTurnFlag;

extern float TNMid1;
extern float TNMid2;
extern Uint32 TNTime;

extern Uint32 Tes;           //��teʱ��
extern Uint32 Tel;
extern Uint32 TesCmp;         // ȡ���Ķ�te
extern Uint32 TelCmp;         //ȡ���ĳ�te

extern Uint32 CmpTesHalf;
extern Uint32 CmpTelHalf;   //��TE��TEL_C
extern Uint32 Cmp90;
extern Uint32 CmpI90;
extern Uint32 Cmp180FHalf;
extern Uint32 Cmp180BHalf;

extern Uint32 Cut90Time;    //90�ȸ���ʱ��
extern Uint16 Cut90TimeLow;
extern Uint16 Cut90TimeHi;
extern Uint32 CutI90Time;    //90�ȸ���ʱ��
extern Uint16 CutI90TimeLow;
extern Uint16 CutI90TimeHi;
extern Uint32 Open180LTime;	//��TE�µ�DEC��ʱ��
extern Uint16 Open180LTimeMS;   
extern Uint16 Open180LTimeLow;  
extern Uint16 Open180LTimeHi;
extern Uint32 Cut180LTime;     //��TE�µ�180����ʱ��
extern Uint16 Cut180LTimeLow;
extern Uint16 Cut180LTimeHi;
extern Uint32 Cut180STime;
extern Uint16 Cut180STimeLow;
extern Uint16 Cut180STimeHi;
extern Uint32 Open180STime;	//��TE�µ�DEC��ʱ��   
extern Uint16 Open180STimeLow;  
extern Uint16 Open180STimeHi;

extern Uint16 EchoAcqNum;

extern Uint32 TesCCheck;
extern Uint32 TelCCheck;
extern Uint16 P90PrdNum;
extern Uint16 P180PrdNum;

extern Uint16 Acq90Num;     //90�ȼ����ɼ�����
extern Uint16 Acq180Num;    //180�����ɼ�����
extern Uint16 Strip90Num;     //90�ȼ�����ȥ����
extern Uint16 Strip180Num;     //180�ȼ�����ȥ����

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
extern Uint16 ScaleModeFlag;
extern Uint16 HoleModeFlag;

extern Uint16 ChangeTableBuf;
extern Uint16 CaseBuffer;
extern Uint16 TableChgCnt;
extern Uint16 * ChgTablePt;

extern Uint16 ToMSFreq;
extern Uint32 ToMSNoiseAddr;
extern Uint32 ToMSSignalAddr;

extern Uint16 ReadTableBuf;
extern Uint16 ZeroOne;

extern Uint32 DataTotalNum;
extern Uint16 EchoNum;

extern Uint16 FreqNum2;
extern Uint16 MiniCycCnt1;
extern Uint16 MiniCycCnt2;
extern Uint16 MiniCycCnt3;
extern Uint16 MiniNoiseMax;
extern Uint16 MiniBuf;




extern Uint32 MiniStorAddr1;
extern Uint32 MiniStorAddr2;
extern Uint32 MiniStorAddr3;
extern Uint32 MiniStorAddr4;
extern Uint32 MiniStorAddr5;
extern Uint32 MiniStorAddr6;


//Array variables defination
extern float PulseGainAry[501];
extern Uint16 FreqAry[];
extern Uint16 RelayAry[];

extern Uint16 AdderLowAry[11];
extern Uint32 AdderResAry[11];
extern Uint16 NoiseDataAry[512];

extern Uint16 NintyWidthAry[9];

extern int32 MiniAddAry[12];

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

extern Uint16 RecSendTableFlag;
extern Uint16 SendTableID;	
extern Uint16 RecSendTableCmdParaLen;


