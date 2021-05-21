//###########################################################################
//
// FILE:   MyFunctions.h
//
// TITLE:  User functions declaration.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H. | No change since previous version (v.58 Alpha)
//###########################################################################

//Functions defined in MainInitial.c
extern void InitAll(void);
extern void InitGpio(void);
extern void InitFPGA(void);
extern void InitPulseGain(void);
extern void InitVariables(void);
extern void InitTable(void);
extern void InitInterruptMcbsp(void);
extern void LoadParaDis(void);

//Functions defined in Mcbsp_interrupt.c
extern interrupt void MRINTA_ISR1(void);     //Mcbsp中断函数

//Functions defined in MyFPGAFunctions.c
extern void ShutdownHV(void);

extern void RstNoiseModule(void);
extern void RstPulseModule(void);

extern void LoadDDSPara(void);
extern void LoadBriDumpPara(void);
extern void LoadPdPara(void);

extern void StartS1msModule(Uint16);

extern void ChangePhase(void);

//Functions defined in MyFunctions.c
extern void McbspSendData(Uint32,Uint32);
extern void AcqNoise(void);
extern void CalNoise(void);
extern void SaveNoise(Uint32);
extern void ScanFreqOnce(void);
extern void CalSignal(Uint16);
extern void SaveSignal(Uint32);
extern void Delay(unsigned int );	// 延时子程
extern void MiniScan(Uint16,Uint32,Uint32);
extern interrupt void XINT1_STOP(void);
extern void SavePulse(Uint32);
extern void SaveEcho(Uint32);
extern void SavePhaseWord(void);
extern void SaveSixFreq(void);
extern void StoreMini(Uint16,int *,Uint16 *);
extern void DCWorkOnce(Uint16);

//Functions defined in ScanTop.c
extern void ScanModeTop(void);

//Functions defined in PulseTop.c
extern void PulseTop(void);
extern void PulseAcq(void);
extern void PulseSave(void);

//Functions defined in DE_cpmg.c
extern void DeCpmgTop(void);
extern interrupt void XINT2_DCStorData(void);

//Functions defined in TableHandle.c
extern void DownloadTable(Uint16);
extern void CheckWorkMode(void);
extern void CheckReadTable(void);
extern void SendTable(void);
extern void ChangeTable995(Uint16);
extern void ChangeTable996(Uint16);
extern void ChangeTable999(Uint16);
extern void ChangeTable99A(Uint16);

//Functions defined in ScaleHoleTop.c
extern void ScaleHoleModeTop(void);

//Functions defined in PP6FreqTop.c
extern void PP6ModeTop(void);

//Functions defined in Oil3FreqTop.c
extern void Oil3ModeTop(void);

//Functions defined in Gas6FreqTop.c
extern void Gas6ModeTop(void);

//Functions defined in T2DModeTop.c
extern void ST2DModeTop(void);
extern void DT2DModeTop(void);
extern void MT2DModeTop(void);

//Functions defined in T1T2ModeTop.c
extern void ST1T2ModeTop(void);

//Functions defined in T1T2DModeTop.c
extern void ST12DModeTop(void);

extern void ST1T2DModeTop(void);
extern void PPLOIL6FModeTop(void);
extern void freq3PP_top(void);
extern void FBW2FModeTop(void);
extern void PPHOIL6FModeTop(void);
extern void Gas6_2ModeTop(void);
extern void PPHOIL6F_2ModeTop(void);
extern void P3D6FModeTop(void);
extern void HRT1T22FModeTop(void);
extern void DFT1T2DModeTop(void);
