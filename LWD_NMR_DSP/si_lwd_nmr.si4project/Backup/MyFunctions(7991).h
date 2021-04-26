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
void InitAll(void);
void InitTable(void);
void InitGpio(void);
void InitFPGA(void);
void InitPulseGain(void);
void InitVariables(void);
void LoadParaDis(void);

//Functions defined in SCIA_interrupt.c
unsigned int SciaTx_Ready(void);
unsigned int SciaRx_Ready(void);
void SciaSendData(Uint16 data);
interrupt void SCIRXINTA_ISR(void);
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var);
void ReplyStateFrame(Uint16 state);
void ReplyDownTableFrame(Uint16 lastCheckSum);
void ReplyUpTableFrame(Uint16 tableID);
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen);

//Functions defined in MyFPGAFunctions.c
void ShutdownHV(void);
void RstNoiseModule(void);
void RstPulseModule(void);
void LoadDDSPara(void);
void LoadBriDumpPara(void);
void LoadPdPara(void);
void StartS1msModule(Uint16);

//Functions defined in MyFunctions.c
void PulseParamIncrement(void);
void AcqNoise(void);
void CalNoise(void);
void SaveNoise(Uint32);
void ScanFreqOnce(void);
void CalSignal(Uint16);
void SaveSignal(Uint32);
void Delay(unsigned int );	// —” ±≥Ã–Ú
void MiniScan(Uint16,Uint32,Uint32);
interrupt void XINT1_STOP(void);
void SavePulse(Uint32);
void SaveEcho(Uint32);
void SavePhaseWord(void);
void SaveSixFreq(void);
void StoreMini(Uint16,int *,Uint16 *);
void DCWorkOnce(Uint16);
void ChangePhase(void);

//Functions defined in ScanTop.c
void ScanModeTop(void);

//Functions defined in PulseTop.c
void PulseTop(void);
void PulseAcq(void);
void PulseSave(void);

//Functions defined in TableHandle.c
void DownloadTable(Uint16);
void RecUpTableCommand(Uint16 DownDataBuf);

interrupt void XINT2_DCStorData(void);
void CheckWorkMode(void);
void CheckReadTable(void);
void SendTable(void);

//Functions defined in DE_CPMG_Top.c
void DeCpmgTop(void);
interrupt void XINT2_DCStorData(void);

//Functions defined in ScaleHoleTop.c
void ScaleHoleModeTop(void);

//Functions defined in PPModeTop.c
void PPModeTop(void);

//Functions defined in PPDIFModeTop.c
void PPDIFModeTop(void);

//Functions defined in PPT1ModeTop.c
void PPT1ModeTop(void);

//Functions defined in PPOFTWModeTop.c
void PPOFTWModeTop(void);

//Functions defined in PPOFTWModeTop.c
void PPShortModeTop(void);

//Functions defined in main.c
Uint16 IdleStateCtl(void);
Uint16 OperaStateCtl(void);
Uint16 CasDctStateCtl(void);
Uint16 AcqFinStateCtl(void);




