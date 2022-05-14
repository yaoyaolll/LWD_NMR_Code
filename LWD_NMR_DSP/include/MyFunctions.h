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

#include "PAPSTop.h"

//Functions defined in MainInitial.c
void InitAll(void);
void InitTable(void);
void InitGpio(void);
void InitFPGA(void);
void InitPulseGain(void);
void InitVariables(void);
void LoadParaDis(void);
void InitSci(void);

//Functions defined in SCIA_interrupt.c
unsigned int SciaTx_Ready(void);
unsigned int SciaRx_Ready(void);
void SciaSendOneWord(Uint16 data);
void clear_sci_rec_buf();
interrupt void CpuTimer0ISR(void);
void reset_sci();
interrupt void SCIRXINTA_ISR(void);
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var);
void ReplyNoVarFrame(Uint16 frameHead);
void ReplyStateFrame(Uint16 state);
void ReplyLastCheckFrame(Uint16 frameHead, Uint16 lastCheckSum);
void ReplyUpTableFrame(Uint16 tableID);
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen);
void ReplyCasingErrFrame();
void parse_sci_rec_buf();
void down_table_cmd(void);
void up_table_cmd();
float type_transform(Uint16 data1, Uint16 data2);
void parameter_cmd();
void K1K2_ctl_cmd();
void single_order_cmd();

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
void Delay(unsigned int); // —” ±≥Ã–Ú
void MiniScan(Uint16, Uint32, Uint32);
interrupt void XINT1_STOP(void);
void SavePulse(Uint32);
void SaveEcho(Uint32);
void SavePhaseWord(void);
//void SaveSixFreq(void);
void StoreMini(Uint16, int *, Uint16 *);
void DCWorkOnce(Uint16);
void ChangePhase(void);

//Functions defined in ScanTop.c
void ScanModeTop(void);

//Functions defined in PulseTop.c
void PulseTop(void);
void PulseAcq(void);
void PulseSave(void);

//Functions defined in TableHandle.c
void RecDownTableCommand(Uint16);
void RecUpTableCommand(Uint16 DownDataBuf);
void RecParameterCommand(Uint16 DownDataBuf);
void RecSingleOrderCommand(Uint16);
void RecK1K2CtrlCommand(Uint16 DownDataBuf);
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

//Functions defined in TuningModeTop.c
void TuningModeTop(void);

//Functions defined in main.c
void IdleStateCtl(void);
void OperaStateCtl(void);
void CasDctStateCtl(void);
void AcqFinStateCtl(void);

// Functions defined in CasingDetectTop.c
Uint16 getCenterFreq();
Uint16 getCenterFreqAmp();
int CasingDetectOnce();
void CasingDetectTop();
void CalFreAndAmp(Uint16 *fre, Uint16* amp);
Uint16 CalQValue(Uint16 CenterFre, Uint32 AmpAddr);

// Functions defined in GuassFitAlgorithm.c
void GaussFit(const float x[9], const float y[9], float *a, float *b, float *c);

// Functions defined in CubicSplineAlgorithm.c
float CublicSplineInterpolation(float x[9], float y[9], float fre);

// Functions defined in SingleOrderDeal.c
Uint16 CheckSumCal();
void EmptyDeal();
void InquireDeal();
void OperationDeal();
void CasingDeal();
void DataUpDeal();
void ModeConfirmDeal();
void K1K2EnDeal();
void K1K2DisDeal();
void HVStateDeal();
void SysCheckDeal();
void PAPSDataUpDeal();

// Functions defined in RelayCtrl.c
Uint16 CalRelayFromFre(Uint16 TransmitFre);
void RelayClose(Uint16 relay_code);
void RelayOpen(Uint16 relay_code);
void ParamUpdate();

// Function defined in PAPS.c
int PAPSDataGenerate(PAPSEntry_t* PAPSEntryPt);
void StorgePAPSToFIFO(PAPSEntry_t* PAPSEntryPt);
void PAPSTop(void);
