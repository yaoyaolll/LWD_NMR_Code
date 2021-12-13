//###########################################################################
//
// FILE:   TableHandle.c
//
// TITLE:  .
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
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(RecDownTableCommand, "secureRamFuncs");
#pragma CODE_SECTION(RecParameterCommand, "secureRamFuncs");
#pragma CODE_SECTION(RecSingleOrderCommand, "secureRamFuncs");

Uint16 DownloadTableCnt = 0;
Uint16 ParamTableLen = 0;
Uint16 *tempSaveTablePt;
extern Uint16 rec_complete_flag;

void CheckWorkMode(void)
{
	WorkMode = *(Uint16 *)0x8001;

	if (WorkMode < 1 || WorkMode > 0xB)
	{
		*(Uint16 *)0x8001 = 0x0008; //默认扫频模式
		WorkMode = 0x0008;
	}
	return;
}


void CheckReadTable(void)
{
	//common parameters
	CheckWorkMode();

	// 刻度模式与测井模式共用同一个90度脉冲宽度
	CheckTablePt = (Uint16 *)0x800E;
	Width90Pulse = *CheckTablePt;
	if (Width90Pulse < 10 || Width90Pulse > 100) // us
	{
		Width90Pulse = 48;
		*CheckTablePt = 48;
	}

	CheckTablePt = (Uint16 *)0x8000; // choose table id
	// scale mode parameter table
	if (*CheckTablePt == 0x0002)
	{
		CheckTablePt = (Uint16 *)0x8008;
		RelayCode = *CheckTablePt;
		if (RelayCode > 1023)					// 调谐码
		{
			RelayCode = 512;
			*CheckTablePt = 512;
		}

		CheckTablePt = (Uint16 *)0x8009;
		CenterFreq = *CheckTablePt;
		if (CenterFreq < 4500 || CenterFreq > 5150) // unit 0.1kHz
		{
			CenterFreq = 4750;
			*CheckTablePt = 4750;
		}

		CheckTablePt = (Uint16 *)0x800A;
		ScanDeltaFreq = *CheckTablePt;
		if (ScanDeltaFreq < 1 || ScanDeltaFreq > 200) // 0.1kHz
		{
			ScanDeltaFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16 *)0x800B;
		NoiseAcqTime = *CheckTablePt;
		if (NoiseAcqTime < 10 || NoiseAcqTime > 100) // us
		{
			NoiseAcqTime = 60;
			*CheckTablePt = 60;
		}

		CheckTablePt = (Uint16 *)0x800C;
		NoiseAcqFreq = *CheckTablePt;
		if (NoiseAcqFreq < 20 || NoiseAcqFreq > 80) // 0.1MHz
		{
			NoiseAcqFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16 *)0x800D;
		ScalePeriod = *CheckTablePt;
		if (ScalePeriod > 100) // s
		{
			ScalePeriod = 10;
			*CheckTablePt = 10;
		}

		CheckTablePt = (Uint16 *)0x800F;
		Angle180Pulse = *CheckTablePt;
		if (Angle180Pulse < 90 || Angle180Pulse > 270) // deg
		{
			Angle180Pulse = 135;
			*CheckTablePt = 135;
		}

		CheckTablePt = (Uint16 *)0x8010;
		SiglAcqPrdNum = *CheckTablePt;
		if (SiglAcqPrdNum < 1 || SiglAcqPrdNum > 32) // number
		{
			SiglAcqPrdNum = 16;
			*CheckTablePt = 16;
		}

		CheckTablePt = (Uint16 *)0x8011;
		SiglAcqFreqTim = *CheckTablePt;
		if (SiglAcqFreqTim != 4 || SiglAcqFreqTim != 8) // number
		{
			SiglAcqFreqTim = 8;
			*CheckTablePt = 8;
		}

		CheckTablePt = (Uint16 *)0x8012;
		EchoAcqWindowShift = *CheckTablePt;
		if (EchoAcqWindowShift < 1 || EchoAcqWindowShift > 100) // us
		{
			EchoAcqWindowShift = 23;
			*CheckTablePt = 23;
		}

		CheckTablePt = (Uint16 *)0x8013;
		Calib_TE = *CheckTablePt;
		if (Calib_TE < 6 || Calib_TE > 100) // 0.1ms
		{
			if (WorkMode == 0x000A) // 孔隙度刻度
			{
				Calib_TE = 6;
				*CheckTablePt = 6;
			}
			else // 调谐刻度和主刻度
			{
				Calib_TE = 10;
				*CheckTablePt = 10;
			}
		}

		CheckTablePt = (Uint16 *)0x8014;
		Calib_NE = *CheckTablePt;
		if (Calib_NE < 10 || Calib_NE > 2000) // number
		{
			if (WorkMode == 0x000A) // 孔隙度刻度
			{
				Calib_NE = 150;
				*CheckTablePt = 150;
			}
			else // 磁场扫频和主刻度
			{
				Calib_NE = 60;
				*CheckTablePt = 60;
			}
		}

		CheckTablePt = (Uint16 *)0x8015;
		PulseTestPulseTime = *CheckTablePt;
		if (PulseTestPulseTime < 50 || PulseTestPulseTime > 200) // us
		{
			PulseTestPulseTime = 100;
			*CheckTablePt = 100;
		}

		CheckTablePt = (Uint16 *)0x8016;
		PulseTestAcqFreq = *CheckTablePt;
		if (PulseTestAcqFreq < 50 || PulseTestAcqFreq > 100) // 0.1MHz
		{
			PulseTestAcqFreq = 80;
			*CheckTablePt = 80;
		}
	}

	// well mode parameter table
	else if (*CheckTablePt == 0x0003)
	{
		CheckTablePt = (Uint16 *)0x801E;
		CenterFreq = *CheckTablePt;
		if (CenterFreq < 4500 || CenterFreq > 5150) // unit 0.1kHz
		{
			CenterFreq = 4850;
			*CheckTablePt = 4850;
		}

		CheckTablePt = (Uint16 *)0x801F;
		ScanDeltaFreq = *CheckTablePt;
		if (ScanDeltaFreq < 10 || ScanDeltaFreq > 100) // 0.1kHz
		{
			ScanDeltaFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16 *)0x8020;
		NoiseAcqTime = *CheckTablePt;
		if (NoiseAcqTime < 10 || NoiseAcqTime > 100) // us
		{
			NoiseAcqTime = 60;
			*CheckTablePt = 60;
		}

		CheckTablePt = (Uint16 *)0x8021;
		NoiseAcqFreq = *CheckTablePt;
		if (NoiseAcqFreq < 20 || NoiseAcqFreq > 80) // 0.1MHz
		{
			NoiseAcqFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16 *)0x8022;
		Angle180Pulse = *CheckTablePt;
		if (Angle180Pulse < 90 || Angle180Pulse > 270) // deg
		{
			Angle180Pulse = 135;
			*CheckTablePt = 135;
		}

		CheckTablePt = (Uint16 *)0x8023;
		SiglAcqPrdNum = *CheckTablePt;
		if (SiglAcqPrdNum < 1 || SiglAcqPrdNum > 32) // number
		{
			SiglAcqPrdNum = 16;
			*CheckTablePt = 16;
		}

		CheckTablePt = (Uint16 *)0x8024;
		SiglAcqFreqTim = *CheckTablePt;
		if (SiglAcqFreqTim != 4 || SiglAcqFreqTim != 8) // number
		{
			SiglAcqFreqTim = 8;
			*CheckTablePt = 8;
		}

		CheckTablePt = (Uint16 *)0x8025;
		EchoAcqWindowShift = *CheckTablePt;
		if (EchoAcqWindowShift < 1 || EchoAcqWindowShift > 100) // us
		{
			EchoAcqWindowShift = 23;
			*CheckTablePt = 23;
		}

		// 模式特有参数校验
		// STWTE
		if (WorkMode == 1)
		{
			CheckTablePt = (Uint16 *)0x8026;
			STWTE_Period = *CheckTablePt;
			if (STWTE_Period < 8 || STWTE_Period > 50) // s
			{
				STWTE_Period = 10;
				*CheckTablePt = 10;
			}

			CheckTablePt = (Uint16 *)0x8027;
			STWTE_TE = *CheckTablePt;
			if (STWTE_TE < 1 || STWTE_TE > 200) // 0.1ms
			{
				STWTE_TE = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x8028;
			STWTE_NE = *CheckTablePt;
			if (STWTE_NE < 1 || STWTE_NE > 3000) // number
			{
				STWTE_NE = 1000;
				*CheckTablePt = 1000;
			}
		}

		// PPMode
		else if (WorkMode == 2)
		{
			CheckTablePt = (Uint16 *)0x8029;
			PPM_Period = *CheckTablePt;
			if (PPM_Period < 17 || PPM_Period > 50) // s
			{
				PPM_Period = 17;
				*CheckTablePt = 17;
			}

			CheckTablePt = (Uint16 *)0x802A;
			PPM_TW_1C = *CheckTablePt;
			if (PPM_TW_1C < 10 || PPM_TW_1C > 200) // 1ms
			{
				PPM_TW_1C = 30;
				*CheckTablePt = 30;
			}

			CheckTablePt = (Uint16 *)0x802B;
			PPM_TE_1A = *CheckTablePt;
			if (PPM_TE_1A < 1 || PPM_TE_1A > 200) // 0.1ms
			{
				PPM_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x802C;
			PPM_TE_1C = *CheckTablePt;
			if (PPM_TE_1C < 1 || PPM_TE_1C > 200) // 0.1ms
			{
				PPM_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x802D;
			PPM_NE_1A = *CheckTablePt;
			if (PPM_NE_1A < 1 || PPM_NE_1A > 3000) // number
			{
				PPM_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16 *)0x802E;
			PPM_NE_1C = *CheckTablePt;
			if (PPM_NE_1C < 1 || PPM_NE_1C > 300) // number
			{
				PPM_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16 *)0x802F;
			PPM_Nrept_1C = *CheckTablePt;
			if (PPM_Nrept_1C < 1 || PPM_Nrept_1C > 300) // number
			{
				PPM_Nrept_1C = 96;
				*CheckTablePt = 96;
			}
		}

		// PPDIF
		else if (WorkMode == 3)
		{
			CheckTablePt = (Uint16 *)0x8030;
			PPDIF_Period = *CheckTablePt;
			if (PPDIF_Period < 17 || PPDIF_Period > 50) // s
			{
				PPDIF_Period = 17;
				*CheckTablePt = 17;
			}

			CheckTablePt = (Uint16 *)0x8031;
			PPDIF_TW_1C = *CheckTablePt;
			if (PPDIF_TW_1C < 10 || PPDIF_TW_1C > 200) // ms
			{
				PPDIF_TW_1C = 30;
				*CheckTablePt = 30;
			}

			CheckTablePt = (Uint16 *)0x8032;
			PPDIF_TW_1B = *CheckTablePt;
			if (PPDIF_TW_1B < 10 || PPDIF_TW_1B > 10000) // ms
			{
				PPDIF_TW_1B = 1800;
				*CheckTablePt = 1800;
			}

			CheckTablePt = (Uint16 *)0x8033;
			PPDIF_TE_1A1B = *CheckTablePt;
			if (PPDIF_TE_1A1B < 1 || PPDIF_TE_1A1B > 200) // 0.1ms
			{
				PPDIF_TE_1A1B = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x8034;
			PPDIF_TE_1C = *CheckTablePt;
			if (PPDIF_TE_1C < 1 || PPDIF_TE_1C > 200) // 0.1ms
			{
				PPDIF_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x8035;
			PPDIF_TE_1C = *CheckTablePt;
			if (PPDIF_NE_1A1B < 1 || PPDIF_NE_1A1B > 3000) // number
			{
				PPDIF_NE_1A1B = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16 *)0x8036;
			PPDIF_NE_1C = *CheckTablePt;
			if (PPDIF_NE_1C < 1 || PPDIF_NE_1C > 300) // number
			{
				PPDIF_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16 *)0x8037;
			PPDIF_Nrept_1C = *CheckTablePt;
			if (PPDIF_Nrept_1C < 1 || PPDIF_Nrept_1C > 300) // number
			{
				PPDIF_Nrept_1C = 25;
				*CheckTablePt = 25;
			}
		}

		// PPT1
		else if (WorkMode == 4)
		{
			// TW CODE
			CheckTablePt = (Uint16 *)0x803A;
			PPT1_TW_Code = *CheckTablePt;
			if (PPT1_TW_Code != 1 || PPT1_TW_Code != 2)
			{
				PPT1_TW_Code = 2; // 默认为1
				*CheckTablePt = 2;
			}
			if (PPT1_TW_Code == 1)
			{
				PPT1_TW_1D = 3000; // unit: 1ms
				PPT1_TW_1E = 1000;
				PPT1_TW_1F = 500;
				PPT1_TW_1G = 300;
				PPT1_TW_1H = 100;
			}
			else
			{
				PPT1_TW_1D = 6000; // unit: 1ms
				PPT1_TW_1E = 3000;
				PPT1_TW_1F = 1000;
				PPT1_TW_1G = 300;
				PPT1_TW_1H = 100;
			}

			CheckTablePt = (Uint16 *)0x8038;
			PPT1_Period = *CheckTablePt;
			if (PPT1_TW_Code == 1)
			{
				if (PPT1_Period < 20 || PPT1_Period > 50) // s
				{
					PPT1_Period = 20;
					*CheckTablePt = 20;
				}
			}
			else
			{
				if (PPT1_Period < 25 || PPT1_Period > 50) // s
				{
					PPT1_Period = 25;
					*CheckTablePt = 25;
				}
			}

			CheckTablePt = (Uint16 *)0x8039;
			PPT1_TW_1C = *CheckTablePt;
			if (PPT1_TW_1C < 10 || PPT1_TW_1C > 200) // ms
			{
				PPT1_TW_1C = 40;
				*CheckTablePt = 40;
			}

			CheckTablePt = (Uint16 *)0x803B;
			PPT1_TE_1A = *CheckTablePt;
			if (PPT1_TE_1A < 1 || PPT1_TE_1A > 200) // 0.1ms
			{
				PPT1_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x803C;
			PPT1_TE_1CDEFGH = *CheckTablePt;
			if (PPT1_TE_1CDEFGH < 1 || PPT1_TE_1CDEFGH > 200) // 0.1ms
			{
				PPT1_TE_1CDEFGH = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x803D;
			PPT1_NE_1A = *CheckTablePt;
			if (PPT1_NE_1A < 1 || PPT1_NE_1A > 3000) // number
			{
				PPT1_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16 *)0x803E;
			PPT1_NE_1C = *CheckTablePt;
			if (PPT1_NE_1C < 1 || PPT1_NE_1C > 300) // number
			{
				PPT1_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16 *)0x803F;
			PPT1_NE_1DEFGH = *CheckTablePt;
			if (PPT1_NE_1DEFGH < 1 || PPT1_NE_1DEFGH > 300) // number
			{
				PPT1_NE_1DEFGH = 16;
				*CheckTablePt = 16;
			}

			CheckTablePt = (Uint16 *)0x8040;
			PPT1_Nrept_1C = *CheckTablePt;
			if (PPT1_Nrept_1C < 1 || PPT1_Nrept_1C > 300) // number
			{
				PPT1_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}

		// PPOFTW
		else if (WorkMode == 5)
		{
			CheckTablePt = (Uint16 *)0x8041;
			PPOFTW_Period = *CheckTablePt;
			if (PPOFTW_Period < 71 || PPOFTW_Period > 80) // s
			{
				PPOFTW_Period = 71;
				*CheckTablePt = 71;
			}

			CheckTablePt = (Uint16 *)0x8042;
			PPOFTW_TW_1C = *CheckTablePt;
			if (PPOFTW_TW_1C < 10 || PPOFTW_TW_1C > 200) // ms
			{
				PPOFTW_TW_1C = 40;
				*CheckTablePt = 40;
			}

			CheckTablePt = (Uint16 *)0x8043;
			PPOFTW_TW_1D = *CheckTablePt;
			if (PPOFTW_TW_1D < 10 || PPOFTW_TW_1D > 20000) // ms
			{
				PPOFTW_TW_1D = 13000;
				*CheckTablePt = 13000;
			}

			CheckTablePt = (Uint16 *)0x8044;
			PPOFTW_TW_1E = *CheckTablePt;
			if (PPOFTW_TW_1E < 10 || PPOFTW_TW_1E > 20000) // ms
			{
				PPOFTW_TW_1E = 11000;
				*CheckTablePt = 11000;
			}

			CheckTablePt = (Uint16 *)0x8045;
			PPOFTW_TW_1F = *CheckTablePt;
			if (PPOFTW_TW_1F < 10 || PPOFTW_TW_1F > 20000) // ms
			{
				PPOFTW_TW_1F = 10000;
				*CheckTablePt = 10000;
			}

			CheckTablePt = (Uint16 *)0x8046;
			PPOFTW_TW_1G = *CheckTablePt;
			if (PPOFTW_TW_1G < 10 || PPOFTW_TW_1G > 20000) // ms
			{
				PPOFTW_TW_1G = 8000;
				*CheckTablePt = 8000;
			}

			CheckTablePt = (Uint16 *)0x8047;
			PPOFTW_TW_1H = *CheckTablePt;
			if (PPOFTW_TW_1H < 10 || PPOFTW_TW_1H > 20000) // ms
			{
				PPOFTW_TW_1H = 6000;
				*CheckTablePt = 6000;
			}

			CheckTablePt = (Uint16 *)0x8048;
			PPOFTW_TE_1ADEFGH = *CheckTablePt;
			if (PPOFTW_TE_1ADEFGH < 1 || PPOFTW_TE_1ADEFGH > 200) // 0.1ms
			{
				PPOFTW_TE_1ADEFGH = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x8049;
			PPOFTW_TE_1C = *CheckTablePt;
			if (PPOFTW_TE_1C < 1 || PPOFTW_TE_1C > 200) // 0.1ms
			{
				PPOFTW_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x804A;
			PPOFTW_Nrept_1C = *CheckTablePt;
			if (PPOFTW_Nrept_1C < 1 || PPOFTW_Nrept_1C > 300) // 0.1ms
			{
				PPOFTW_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}

		// PPShort
		else if (WorkMode == 6)
		{
			CheckTablePt = (Uint16 *)0x804B;
			PPShort_Period = *CheckTablePt;
			if (PPShort_Period < 6 || PPShort_Period > 50) // s
			{
				PPShort_Period = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x804C;
			PPShort_TW_1C = *CheckTablePt;
			if (PPShort_TW_1C < 10 || PPShort_TW_1C > 200) // ms
			{
				PPShort_TW_1C = 40;
				*CheckTablePt = 40;
			}

			CheckTablePt = (Uint16 *)0x804D;
			PPShort_TE_1A = *CheckTablePt;
			if (PPShort_TE_1A < 1 || PPShort_TE_1A > 200) // 0.1ms
			{
				PPShort_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x804E;
			PPShort_TE_1C = *CheckTablePt;
			if (PPShort_TE_1C < 1 || PPShort_TE_1C > 200) // 0.1ms
			{
				PPShort_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16 *)0x804F;
			PPShort_NE_1A = *CheckTablePt;
			if (PPShort_NE_1A < 1 || PPShort_NE_1A > 3000) // number
			{
				PPShort_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16 *)0x8050;
			PPShort_NE_1C = *CheckTablePt;
			if (PPShort_NE_1C < 1 || PPShort_NE_1C > 300) // number
			{
				PPShort_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16 *)0x8051;
			PPShort_Nrept_1C = *CheckTablePt;
			if (PPShort_Nrept_1C < 1 || PPShort_Nrept_1C > 300) // number
			{
				PPShort_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}
	}
	return;
}


void RecDownTableCommand(Uint16 DownDataBuf)
{
	if (DownDataBuf == DATA_DOWN_TABLE_F && DownTableFlag == CLEAR) //表明为下载数据命令，DownDataBuf为帧头
	{
		DownTableFlag = SET;
		DownloadTableCnt = 1;
	}
	else if (DownloadTableCnt == 1 && DownTableFlag == SET) // DownDataBuf为帧长度
	{
		ParamTableLen = DownDataBuf; // ParamTableLen = n+3，n为参数表长度
		if (ParamTableLen == CAL_TABLE_LEN + 3)
		{
			SaveTablePt = ADDR_CAL_TABLE_START; 	// Length
		}
		else if (ParamTableLen == WELL_TABLE_LEN + 3)
		{
			SaveTablePt = ADDR_WELL_TABLE_START;
		}
		else if (ParamTableLen == TUNING_TABLE_LEN + 3)
		{
			SaveTablePt = ADDR_TUNING_TABLE_START;
		}
		else if (ParamTableLen == CONFIG_TABLE_LEN + 3)
		{
			SaveTablePt = ADDR_CONFIG_TABLE_START;
		}

		*SaveTablePt++ = ParamTableLen - 1;
		tempSaveTablePt = SaveTablePt; 			// 0x8003/0x8019/0x8058/0x80A3 tableID
		DownloadTableCnt = 2;
	}
	else if (DownloadTableCnt == 2 && DownTableFlag == SET) // DownDataBuf为从机标识
	{
		if (DownDataBuf != EVENT_BOARD_ID)
		{
			DownTableFlag = CLEAR;
		}
		DownloadTableCnt = 3;
	}
	else if (DownloadTableCnt == 3 && DownTableFlag == SET) // 参数表ID
	{
		*SaveTablePt++ = DownDataBuf;

		// 当只有参数表是刻度模式参数表和测井模式参数表时才将表ID放入0x8000地址
		if (DownDataBuf == 2 || DownDataBuf == 3)		
		{
			*(Uint16 *)0x8000 = DownDataBuf;		
		}
		
		DownloadTableCnt++;
	}
	else if (DownloadTableCnt == ParamTableLen && DownTableFlag == SET) // 最后一个数据为CheckSum
	{
		// CheckSum校验
		Uint16 CheckSum = DATA_DOWN_TABLE_F; // 帧头
		CheckSum += ParamTableLen;			 // 长度
		CheckSum += EVENT_BOARD_ID;			 // 从机标识

		int i = 0;
		SaveTablePt = tempSaveTablePt; // SaveTablePt指向0x8003/0x8019/0x8058/0x80A3
		for (i = 0; i < ParamTableLen - 3; ++i)
		{
			CheckSum += *SaveTablePt;
			SaveTablePt++;
		}
		*SaveTablePt = CheckSum;

		if (CheckSum == DownDataBuf) // success
		{
			if (*(Uint16 *)0x8000 == 0x0002) // 设置工作模式
				*(Uint16 *)0x8001 = *(Uint16 *)0x8007;
			else if (*(Uint16 *)0x8000 == 0x0003)
				*(Uint16 *)0x8001 = *(Uint16 *)0x801D;
	        // 当校验成功时返回校验和
	        ReplyLastCheckFrame(REPLY_DOWN_TABLE_F, CheckSum); // 返回校验和
		}

		//下载标志位清除
		DownTableFlag = CLEAR;
		rec_complete_flag = 1;
	}
	else if (DownTableFlag == SET)
	{
		*SaveTablePt++ = DownDataBuf;
		DownloadTableCnt++;
	}
	return;
}

Uint16 RecSendTableCnt = 0;
// 接收上传参数表指令
void RecUpTableCommand(Uint16 DownDataBuf)
{
	if (DownDataBuf == DATA_UP_TABLE_F && RecSendTableFlag == CLEAR)
	{
		RecSendTableFlag = SET;
		RecSendTableCnt = 1;
	}
	else if (RecSendTableCnt == 1 && RecSendTableFlag == SET)
	{
		RecSendTableCmdParaLen = DownDataBuf;
		RecSendTableCnt = 2;
	}
	else if (RecSendTableCnt == 2 && RecSendTableFlag == SET)
	{
		if (EVENT_BOARD_ID != DownDataBuf)
		{
			RecSendTableFlag = CLEAR;
		}
		RecSendTableCnt = 3;
	}
	else if (RecSendTableCnt == 3 && RecSendTableFlag == SET)
	{
		SendTableID = DownDataBuf; // 保存需要上传的参数表的ID
		RecSendTableCnt = 4;
	}
	else if (RecSendTableCnt == 4 && RecSendTableFlag == SET)
	{
		Uint16 CheckSum = 0;
		CheckSum += DATA_UP_TABLE_F;
		CheckSum += RecSendTableCmdParaLen;
		CheckSum += EVENT_BOARD_ID;
		CheckSum += SendTableID;

		if (CheckSum == DownDataBuf)
			SendTableFlag = SET;

		RecSendTableFlag = CLEAR;
		rec_complete_flag = 1;
	}
}

Uint16 RecParameterCnt = 0;
void RecParameterCommand(Uint16 DownDataBuf)
{
    if (RecParamOrderFlag == CLEAR && DownDataBuf == DATA_Parameter_F)  // 帧头
    {
        ParamOrderData.data.frameHead = DownDataBuf;
        RecParamOrderFlag = SET;
        RecParameterCnt = 1;
    }
    else if (RecParameterCnt == 1 && RecParamOrderFlag == SET)
    {
        ParamOrderData.data.len = DownDataBuf;
        RecParameterCnt = 2;
    }
    else if (RecParameterCnt == 2 && RecParamOrderFlag == SET)
    {
        ParamOrderData.data.slaveID = DownDataBuf;
        RecParameterCnt = 3;
        if (DownDataBuf != EVENT_BOARD_ID)
        {
            RecParameterCnt = 0;
            RecParamOrderFlag = CLEAR;
        }
    }
    else if (RecParameterCnt < ParamOrderData.data.len && RecParamOrderFlag == SET)
    {
        ParamOrderData.dataAry[RecParameterCnt] = DownDataBuf;
        RecParameterCnt++;
    }
    else if (RecParameterCnt == ParamOrderData.data.len && RecParamOrderFlag == SET)
    {
        ParamOrderData.data.checkSum = DownDataBuf;
        Uint16 checkSum = 0;
        int i=0;
        for (;i<ParamOrderData.data.len;++i)
        {
            checkSum += ParamOrderData.dataAry[i];
        }

        if (ParamOrderData.data.checkSum == checkSum)
        {
            ParamUpdate();
            // 回复帧
            ReplyLastCheckFrame(REPLY_Parameter_F, checkSum);
        }

        RecParamOrderFlag = CLEAR;
        rec_complete_flag = 1;
        RecParameterCnt = 0;
    }
}

Uint16 RecSingleOrderCnt = 0;
// 接收主控板单个指令
void RecSingleOrderCommand(Uint16 DownDataBuf)
{
	if (RecSingleOrderFlag == CLEAR && DownDataBuf >= DATA_INQUIRE_F && DownDataBuf <= DATA_PAPS_F)
	{
	    SingleOrderData.frameHead = DownDataBuf;
		RecSingleOrderFlag = SET;
		RecSingleOrderCnt = 1;
	}
	else if (RecSingleOrderCnt == 1 && RecSingleOrderFlag == SET)
	{
	    SingleOrderData.len = DownDataBuf;
		RecSingleOrderCnt = 2;
		if (DownDataBuf != 3)
		{
		    RecSingleOrderCnt = 0;
		    RecSingleOrderFlag = CLEAR;
		}
	}
	else if (RecSingleOrderCnt == 2 && RecSingleOrderFlag == SET)
	{
	    SingleOrderData.slaveID = DownDataBuf;
		RecSingleOrderCnt = 3;
		if (DownDataBuf != EVENT_BOARD_ID)
		{
			RecSingleOrderCnt = 0;
			RecSingleOrderFlag = CLEAR;
		}
	}
	else if (RecSingleOrderCnt == 3 && RecSingleOrderFlag == SET)
	{
	    SingleOrderData.checkSum = DownDataBuf;
		SingleOrderAryChoice = SingleOrderData.frameHead & 0x000F;

		// 接收到来自主控的数据延迟到此时处理
		if (SingleOrderAryChoice <= 0xA) // 防止SingleOrderAryChoice越界
		{
			(*(singleOrderFunc[SingleOrderAryChoice]))(); // 单帧数据处理函数
			SingleOrderAryChoice = 0;
		}

		RecSingleOrderCnt = 0;
		RecSingleOrderFlag = CLEAR;
		rec_complete_flag = 1;
	}
}

Uint16 RecK1K2CtrlCnt = 0;
Uint16 K1K2CtrlOrder = 0;
// 接收储能短节K1K2控制指令
void RecK1K2CtrlCommand(Uint16 DownDataBuf)
{
    if (DownDataBuf == DATA_K1K2_EN_F && RecK1K2CtrlFlag == CLEAR)
    {
        RecK1K2CtrlFlag = SET;
        RecK1K2CtrlCnt = 1;
    }
    else if (RecK1K2CtrlCnt == 1 && RecK1K2CtrlFlag == SET)
    {
        RecK1K2CtrlCnt = 2;
        if (DownDataBuf != 4)       // order length
        {
            RecK1K2CtrlFlag = CLEAR;
            RecK1K2CtrlCnt = 0;
        }
    }
    else if (RecK1K2CtrlCnt == 2 && RecK1K2CtrlFlag == SET)
    {
        if (EVENT_BOARD_ID != DownDataBuf)
        {
            RecK1K2CtrlFlag = CLEAR;
        }
        RecK1K2CtrlCnt = 3;
    }
    else if (RecK1K2CtrlCnt == 3 && RecK1K2CtrlFlag == SET)
    {
        K1K2CtrlOrder = DownDataBuf; // 保存需要上传的参数表的ID
        RecK1K2CtrlCnt = 4;
    }
    else if (RecK1K2CtrlCnt == 4 && RecK1K2CtrlFlag == SET)
    {
        Uint16 CheckSum = 0;
        CheckSum += DATA_K1K2_EN_F;
        CheckSum += 4;
        CheckSum += EVENT_BOARD_ID;
        CheckSum += K1K2CtrlOrder;

        /*
         * K1K2: high level means close
         *       low level means open
         * FPGA code:
                 *-----k1------*
                 'h00A0:
                            k1 <= 1;
                 'h00A1:
                            k1 <= 0;

                 *-----k2------*
                 'h00A2:
                            k2 <= 1;
                 'h00A3:
                            k2 <= 0;
         */
        if (CheckSum == DownDataBuf)
        {
            // K2为高字节，K1为低字节
            if (K1K2CtrlOrder == 0x0001)            // 打开K1，闭合K2
            {
                K1_DIS = USER_ENABLE;       // K1打开（输出低）
                K2_EN  = USER_ENABLE;       // K2闭合（输出高）
                HVState = HV_OFF;           // 表明高压未启用
            }
            else if (K1K2CtrlOrder == 0x0101)       // K1 K2均打开
            {
                K1_DIS = USER_ENABLE;       // K1打开（输出低）
                K2_DIS = USER_ENABLE;       // K2打开（输出低）
                HVState = HV_OFF;           // 表明高压未启用
            }
            else if (K1K2CtrlOrder == 0)            // K1 K2均闭合
            {
                K1_EN = USER_DISABLE;      // K1闭合（输出高）
                K2_EN = USER_DISABLE;      // K2闭合（输出高）
                HVState = HV_ON;            // 表明开通状态
            }
            ReplyNoVarFrame(DATA_K1K2_EN_F);
        }

        RecK1K2CtrlFlag = CLEAR;
        rec_complete_flag = 1;
    }
}
