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
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(CheckReadTable,"Datatable");
#pragma CODE_SECTION(CheckWorkMode,"Datatable");

void SendTable(void)
{
	TableTempPt = (Uint16 *)0x8000;
	*TableTempPt= 0x9921;
	for(SendCnt=0;SendCnt<TABLE_TOTAL_NUM+1;SendCnt++)      
	{
		while(McbspaRegs.SPCR2.bit.XRDY==0)              //如果不能发送，等待
		{ ; }
		McbspaRegs.DXR1.all=*TableTempPt;     //发送表数据
		TableTempPt++;
		//Delay(2);                        //指针指向下一个数据
	}
	while(McbspaRegs.SPCR2.bit.XRDY==0)         //如果不能发送，等待
	{;}
	McbspaRegs.DXR1.all=0xAA55;     //发送数据尾
	return;

	Uint16 CheckSum = 0;
	Uint16 i=0;
	if (SendTableID == 0x2)
	{
		TableTempPt = (Uint16 *)0x8002;
		Uint16 CheckSum = 0;
		Uint16 i=0;
		for (;i<20;++i)
		{
			CheckSum += (*TableTempPt);
			TableTempPt++;
		}
		TableTempPt = CheckSum;
	}
	else if (SendTableID == 0x3)
	{
		TableTempPt = (Uint16 *)0x8017;
		for (;i<58;++i)
		{
			CheckSum += (*TableTempPt);
			TableTempPt++;
		}
		TableTempPt = CheckSum;
	}
	
}

void CheckWorkMode(void)
{
	WorkMode	= *(Uint16 *)0x8001;

	if (WorkMode < 1 || WorkMode > 0xB)
	{
		*(Uint16 *)0x8001	= 0x0008;//默认扫频模式
		WorkMode			= 0x0008;
	}
	return;
}



void CheckReadTable(void)
{
	//common parameters     
	CheckWorkMode();

	// 刻度模式与测井模式共用同一个90度脉冲宽度
	CheckTablePt = (Uint16*)0x800D;
	Width90Pulse = *CheckTablePt;
	if (Width90Pulse < 10 || Width90Pulse > 100)            // us
	{
		Width90Pulse = 48;
		*CheckTablePt = 48;
	}

	CheckTablePt = (Uint16*)0x8000;        // choose table id
	// scale mode parameter table
	if (*CheckTablePt == 0x0002)
	{
		CheckTablePt = (Uint16*)0x8008;
		CenterFreq = *CheckTablePt;
		if (CenterFreq < 4500 || CenterFreq > 5150)             // unit 0.1kHz
		{
			CenterFreq = 4750;
			*CheckTablePt = 4750;
		}
		CenterFreq /= 10;

		CheckTablePt = (Uint16*)0x8009;
		ScanDeltaFreq = *CheckTablePt;
		if (ScanDeltaFreq < 10 || ScanDeltaFreq > 100)             // 0.1kHz
		{
			ScanDeltaFreq = 50;
			*CheckTablePt = 50;
		}
		ScanDeltaFreq /= 10;

		CheckTablePt = (Uint16*)0x800A;
		NoiseAcqTime = *CheckTablePt;
		if (NoiseAcqTime < 10 || NoiseAcqTime > 100)            // us
		{
			NoiseAcqTime = 60;
			*CheckTablePt = 60;
		}

		CheckTablePt = (Uint16*)0x800B;
		NoiseAcqFreq = *CheckTablePt;
		if (NoiseAcqFreq < 20 || NoiseAcqFreq > 80)            // 0.1MHz
		{
			NoiseAcqFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16*)0x800C;
		ScalePeriod = *CheckTablePt;
		if (ScalePeriod > 100)                        // s
		{
			ScalePeriod = 10;
			*CheckTablePt = 10;
		}

		CheckTablePt = (Uint16*)0x800E;
		Angle180Pulse = *CheckTablePt;
		if (Angle180Pulse < 90 || Angle180Pulse > 270)           // deg
		{
			Angle180Pulse = 135;
			*CheckTablePt = 135;
		}

		CheckTablePt = (Uint16*)0x800F;
		SiglAcqPrdNum = *CheckTablePt;
		if (SiglAcqPrdNum < 1 || SiglAcqPrdNum > 32)      // number
		{
			SiglAcqPrdNum = 16;
			*CheckTablePt = 16;
		}

		CheckTablePt = (Uint16*)0x8010;
		SiglAcqFreqTim = *CheckTablePt;
		if (SiglAcqFreqTim != 4 || SiglAcqFreqTim != 8)        // number
		{
			SiglAcqFreqTim = 8;
			*CheckTablePt = 8;
		}

		CheckTablePt = (Uint16*)0x8011;
		EchoAcqWindowShift = *CheckTablePt;
		if (EchoAcqWindowShift < 1 || EchoAcqWindowShift > 100)  // us
		{
			EchoAcqWindowShift = 23;
			*CheckTablePt = 23;
		}

		CheckTablePt = (Uint16*)0x8012;
		Calib_TE = *CheckTablePt;
		if (Calib_TE < 6 || Calib_TE > 100)                        // 0.1ms
		{
			if (WorkMode == 0x000A)     // 孔隙度刻度
			{
				Calib_TE = 6;
				*CheckTablePt = 6;
			}
			else                        // 磁场扫频和主刻度
			{
				Calib_TE = 10;
				*CheckTablePt = 10;
			}
		}

		CheckTablePt = (Uint16*)0x8013;
		Calib_NE = *CheckTablePt;
		if (Calib_NE < 10 || Calib_NE > 2000)                     // number
		{
			if (WorkMode == 0x000A)     // 孔隙度刻度
			{
				Calib_NE = 150;
				*CheckTablePt = 150;
			}
			else						// 磁场扫频和主刻度
			{
				Calib_NE = 60;
				*CheckTablePt = 60;
			}
		}

		CheckTablePt = (Uint16*)0x8014;
		PulseTestPulseTime = *CheckTablePt;
		if (PulseTestPulseTime < 50 || PulseTestPulseTime > 200)  // us
		{
			PulseTestPulseTime = 100;
			*CheckTablePt = 100;
		}

		CheckTablePt = (Uint16*)0x8015;
		PulseTestAcqFreq = *CheckTablePt;
		if (PulseTestAcqFreq < 50 || PulseTestAcqFreq > 100)      // 0.1MHz
		{
			PulseTestAcqFreq = 80;
			*CheckTablePt = 80;
		}
	}

	// well mode parameter table
	else if (*CheckTablePt == 0x0003)
	{
		CheckTablePt = (Uint16*)0x801D;
		CenterFreq = *CheckTablePt;
		if (CenterFreq < 4500 || CenterFreq > 5150)             // unit 0.1kHz
		{
			CenterFreq = 4850;
			*CheckTablePt = 4850;
		}
		CenterFreq /= 10;

		CheckTablePt = (Uint16*)0x801E;
		ScanDeltaFreq = *CheckTablePt;
		if (ScanDeltaFreq < 10 || ScanDeltaFreq > 100)             // 0.1kHz
		{
			ScanDeltaFreq = 50;
			*CheckTablePt = 50;
		}
		ScanDeltaFreq /= 10;

		CheckTablePt = (Uint16*)0x801F;
		NoiseAcqTime = *CheckTablePt;
		if (NoiseAcqTime < 10 || NoiseAcqTime > 100)            // us
		{
			NoiseAcqTime = 60;
			*CheckTablePt = 60;
		}

		CheckTablePt = (Uint16*)0x8020;
		NoiseAcqFreq = *CheckTablePt;
		if (NoiseAcqFreq < 20 || NoiseAcqFreq > 80)             // 0.1MHz
		{
			NoiseAcqFreq = 50;
			*CheckTablePt = 50;
		}

		CheckTablePt = (Uint16*)0x8021;
		Angle180Pulse = *CheckTablePt;
		if (Angle180Pulse < 90 || Angle180Pulse > 270)           // deg
		{
			Angle180Pulse = 135;
			*CheckTablePt = 135;
		}

		CheckTablePt = (Uint16*)0x8022;
		SiglAcqPrdNum = *CheckTablePt;
		if (SiglAcqPrdNum < 1 || SiglAcqPrdNum > 32)      // number
		{
			SiglAcqPrdNum = 16;
			*CheckTablePt = 16;
		}

		CheckTablePt = (Uint16*)0x8023;
		SiglAcqFreqTim = *CheckTablePt;
		if (SiglAcqFreqTim != 4 || SiglAcqFreqTim != 8)        // number
		{
			SiglAcqFreqTim = 8;
			*CheckTablePt = 8;
		}

		CheckTablePt = (Uint16*)0x8024;
		EchoAcqWindowShift = *CheckTablePt;
		if (EchoAcqWindowShift < 1 || EchoAcqWindowShift > 100)  // us
		{
			EchoAcqWindowShift = 23;
			*CheckTablePt = 23;
		}

		// 模式特有参数校验
		// STWTE
		if (WorkMode == 1)
		{
			CheckTablePt = (Uint16*)0x8025;
			STWTE_Period = *CheckTablePt;
			if (STWTE_Period < 8 || STWTE_Period > 50)   // s
			{
				STWTE_Period = 10;
				*CheckTablePt = 10;
			}

			CheckTablePt = (Uint16*)0x8026;
			STWTE_TE = *CheckTablePt;
			if (STWTE_TE < 1 || STWTE_TE > 200)          // 0.1ms
			{
				STWTE_TE = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x8027;
			STWTE_NE = *CheckTablePt;
			if (STWTE_NE < 1 || STWTE_NE > 3000)         // number
			{
				STWTE_NE = 1000;
				*CheckTablePt = 23;
			}
		}

		// PPMode
		else if (WorkMode == 2)
		{
			CheckTablePt = (Uint16*)0x8028;
			PPM_Period = *CheckTablePt;
			if (PPM_Period < 17 || PPM_Period > 50)   // s
			{
				PPM_Period = 17;
				*CheckTablePt = 17;
			}

			CheckTablePt = (Uint16*)0x8029;
			PPM_TW_1C = *CheckTablePt;
			if (PPM_TW_1C < 10 || PPM_TW_1C > 200)          // 1ms
			{
				PPM_TW_1C = 30;
				*CheckTablePt = 30;
			}

			CheckTablePt = (Uint16*)0x802A;
			PPM_TE_1A = *CheckTablePt;
			if (PPM_TE_1A < 1 || PPM_TE_1A > 200)         // 0.1ms
			{
				PPM_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x802B;
			PPM_TE_1C = *CheckTablePt;
			if (PPM_TE_1C < 1 || PPM_TE_1C > 200)          // 0.1ms
			{
				PPM_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x802C;
			PPM_NE_1A = *CheckTablePt;
			if (PPM_NE_1A < 1 || PPM_NE_1A > 3000)         // number
			{
				PPM_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16*)0x802D;
			PPM_NE_1C = *CheckTablePt;
			if (PPM_NE_1C < 1 || PPM_NE_1C > 300)          // number
			{
				PPM_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16*)0x802E;
			PPM_Nrept_1C = *CheckTablePt;
			if (PPM_Nrept_1C < 1 || PPM_Nrept_1C > 300)    // number
			{
				PPM_Nrept_1C = 96;
				*CheckTablePt = 96;
			}
		}

		// PPDIF
		else if (WorkMode == 3)
		{
			CheckTablePt = (Uint16*)0x802F;
			PPDIF_Period = *CheckTablePt;
			if (PPDIF_Period < 17 || PPDIF_Period > 50)    // s
			{
				PPDIF_Period = 17;
				*CheckTablePt = 17;
			}

			CheckTablePt = (Uint16*)0x8030;
			PPDIF_TW_1C = *CheckTablePt;
			if (PPDIF_TW_1C < 10 || PPDIF_TW_1C > 200)    // ms
			{
				PPDIF_TW_1C = 30;
				*CheckTablePt = 30;
			}

			CheckTablePt = (Uint16*)0x8031;
			PPDIF_TW_1B = *CheckTablePt;
			if (PPDIF_TW_1B < 10 || PPDIF_TW_1B > 10000)    // ms
			{
				PPDIF_TW_1B = 1800;
				*CheckTablePt = 1800;
			}

			CheckTablePt = (Uint16*)0x8032;
			PPDIF_TE_1A1B = *CheckTablePt;
			if (PPDIF_TE_1A1B < 1 || PPDIF_TE_1A1B > 200)    // 0.1ms
			{
				PPDIF_TE_1A1B = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x8033;
			PPDIF_TE_1C = *CheckTablePt;
			if (PPDIF_TE_1C < 1 || PPDIF_TE_1C > 200)    // 0.1ms
			{
				PPDIF_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x8034;
			PPDIF_NE_1A1B = *CheckTablePt;
			if (PPDIF_NE_1A1B < 1 || PPDIF_NE_1A1B > 3000)    // number
			{
				PPDIF_NE_1A1B = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16*)0x8035;
			PPDIF_NE_1C = *CheckTablePt;
			if (PPDIF_NE_1C < 1 || PPDIF_NE_1C > 300)     // number
			{
				PPDIF_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16*)0x8036;
			PPDIF_Nrept_1C = *CheckTablePt;
			if (PPDIF_Nrept_1C < 1 || PPDIF_Nrept_1C > 300)    // number
			{
				PPDIF_Nrept_1C = 25;
				*CheckTablePt = 25;
			}
		}

		// PPT1
		else if (WorkMode == 4)
		{
			// TW CODE
			CheckTablePt = (Uint16*)0x8039;
			PPT1_TW_Code = *CheckTablePt;
			if (PPT1_TW_Code != 1 || PPT1_TW_Code != 2)
			{
				PPT1_TW_Code = 1;                         // 默认为1
				*CheckTablePt = 1;
			}
			if (PPT1_TW_Code == 1)
			{
				PPT1_TW_1D = 3000;                        // 0.1ms
				PPT1_TW_1E = 1000;
				PPT1_TW_1F = 500;
				PPT1_TW_1G = 300;
				PPT1_TW_1H = 100;
			}
			else
			{
				PPT1_TW_1D = 6000;                        // 0.1ms
				PPT1_TW_1E = 3000;
				PPT1_TW_1F = 1000;
				PPT1_TW_1G = 300;
				PPT1_TW_1H = 100;
			}

			CheckTablePt = (Uint16*)0x8037;
			PPT1_Period = *CheckTablePt;
			if (PPT1_TW_Code == 1)
			{
				if (PPT1_Period < 20 || PPT1_Period > 50)    // s
				{
					PPT1_Period = 20;
					*CheckTablePt = 20;
				}
			}
			else
			{
				if (PPT1_Period < 25 || PPT1_Period > 50)    // s
				{
					PPT1_Period = 25;
					*CheckTablePt = 25;
				}
			}

			CheckTablePt = (Uint16*)0x8038;
			PPT1_TW_1C = *CheckTablePt;
			if (PPT1_TW_1C < 10 || PPT1_TW_1C > 200)       // ms
			{
				PPT1_TW_1C = 40;
				*CheckTablePt = 30;
			}

			CheckTablePt = (Uint16*)0x803A;
			PPT1_TE_1A = *CheckTablePt;
			if (PPT1_TE_1A < 11 || PPT1_TE_1A > 200)             // 0.1ms
			{
				PPT1_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x803B;
			PPT1_TE_1CDEFGH = *CheckTablePt;
			if (PPT1_TE_1CDEFGH < 1 || PPT1_TE_1CDEFGH > 200)    // 0.1ms
			{
				PPT1_TE_1CDEFGH = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x803C;
			PPT1_NE_1A = *CheckTablePt;
			if (PPT1_NE_1A < 1 || PPT1_NE_1A > 3000)             // number
			{
				PPT1_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16*)0x803D;
			PPT1_NE_1C = *CheckTablePt;
			if (PPT1_NE_1C < 1 || PPT1_NE_1C > 300)              // number
			{
				PPT1_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16*)0x803E;
			PPT1_NE_1DEFGH = *CheckTablePt;
			if (PPT1_NE_1DEFGH < 1 || PPT1_NE_1DEFGH > 300)      // number
			{
				PPT1_NE_1DEFGH = 16;
				*CheckTablePt = 16;
			}

			CheckTablePt = (Uint16*)0x803F;
			PPT1_Nrept_1C = *CheckTablePt;
			if (PPT1_Nrept_1C < 1 || PPT1_Nrept_1C > 300)        // number
			{
				PPT1_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}

		// PPOFTW
		else if (WorkMode == 5)
		{
			CheckTablePt = (Uint16*)0x8040;
			PPOFTW_Period = *CheckTablePt;
			if (PPOFTW_Period < 71 || PPOFTW_Period > 80)        // s
			{
				PPOFTW_Period = 71;
				*CheckTablePt = 71;
			}

			CheckTablePt = (Uint16*)0x8041;
			PPOFTW_TW_1C = *CheckTablePt;
			if (PPOFTW_TW_1C < 10 || PPOFTW_TW_1C > 200)          // ms
			{
				PPOFTW_TW_1C = 40;
				*CheckTablePt = 40;
			}

			CheckTablePt = (Uint16*)0x8042;
			PPOFTW_TW_1D = *CheckTablePt;
			if (PPOFTW_TW_1D < 10 || PPOFTW_TW_1D > 2000)          // ms
			{
				PPOFTW_TW_1D = 13000;
				*CheckTablePt = 13000;
			}

			CheckTablePt = (Uint16*)0x8043;
			PPOFTW_TW_1E = *CheckTablePt;
			if (PPOFTW_TW_1E < 10 || PPOFTW_TW_1E > 2000)          // ms
			{
				PPOFTW_TW_1E = 11000;
				*CheckTablePt = 11000;
			}

			CheckTablePt = (Uint16*)0x8044;
			PPOFTW_TW_1F = *CheckTablePt;
			if (PPOFTW_TW_1F < 10 || PPOFTW_TW_1F > 2000)          // ms
			{
				PPOFTW_TW_1F = 10000;
				*CheckTablePt = 10000;
			}

			CheckTablePt = (Uint16*)0x8045;
			PPOFTW_TW_1G = *CheckTablePt;
			if (PPOFTW_TW_1G < 10 || PPOFTW_TW_1G > 2000)          // ms
			{
				PPOFTW_TW_1G = 8000;
				*CheckTablePt = 8000;
			}

			CheckTablePt = (Uint16*)0x8046;
			PPOFTW_TW_1H = *CheckTablePt;
			if (PPOFTW_TW_1H < 10 || PPOFTW_TW_1H > 2000)          // ms
			{
				PPOFTW_TW_1H = 6000;
				*CheckTablePt = 6000;
			}

			CheckTablePt = (Uint16*)0x8047;
			PPOFTW_TE_1ADEFGH = *CheckTablePt;
			if (PPOFTW_TE_1ADEFGH < 1 || PPOFTW_TE_1ADEFGH > 200)          // 0.1ms
			{
				PPOFTW_TE_1ADEFGH = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x8048;
			PPOFTW_TE_1C = *CheckTablePt;
			if (PPOFTW_TE_1C < 1 || PPOFTW_TE_1C > 200)                   // 0.1ms
			{
				PPOFTW_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x8049;
			PPOFTW_Nrept_1C = *CheckTablePt;
			if (PPOFTW_Nrept_1C < 1 || PPOFTW_Nrept_1C > 300)             // 0.1ms
			{
				PPOFTW_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}

		// PPShort
		else if (WorkMode == 6)
		{
			CheckTablePt = (Uint16*)0x804A;
			PPShort_Period = *CheckTablePt;
			if (PPShort_Period < 6 || PPShort_Period > 50)               // s
			{
				PPShort_Period = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x804B;
			PPShort_TW_1C = *CheckTablePt;
			if (PPShort_TW_1C < 10 || PPShort_TW_1C > 200)                // ms
			{
				PPShort_TW_1C = 40;
				*CheckTablePt = 40;
			}

			CheckTablePt = (Uint16*)0x804C;
			PPShort_TE_1A = *CheckTablePt;
			if (PPShort_TE_1A < 1 || PPShort_TE_1A > 200)                // 0.1ms
			{
				PPShort_TE_1A = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x804D;
			PPShort_TE_1C = *CheckTablePt;
			if (PPShort_TE_1C < 1 || PPShort_TE_1C > 200)                // 0.1ms
			{
				PPShort_TE_1C = 6;
				*CheckTablePt = 6;
			}

			CheckTablePt = (Uint16*)0x804E;
			PPShort_NE_1A = *CheckTablePt;
			if (PPShort_NE_1A < 1 || PPShort_NE_1A > 3000)                // number
			{
				PPShort_NE_1A = 1000;
				*CheckTablePt = 1000;
			}

			CheckTablePt = (Uint16*)0x804F;
			PPShort_NE_1C = *CheckTablePt;
			if (PPShort_NE_1C < 1 || PPShort_NE_1C > 300)                // number
			{
				PPShort_NE_1C = 50;
				*CheckTablePt = 50;
			}

			CheckTablePt = (Uint16*)0x8050;
			PPShort_Nrept_1C = *CheckTablePt;
			if (PPShort_Nrept_1C < 1 || PPShort_Nrept_1C > 300)                // number
			{
				PPShort_Nrept_1C = 50;
				*CheckTablePt = 50;
			}
		}
	}
	return;
}


Uint16 DownloadTableCnt = 0;
Uint16 ParamTableLen = 0;
#define CAL_TABLE_LEN  19   // 刻度模式参数表长度
#define WELL_TABLE_LEN 57	// 测井模式参数表长度

void DownloadTable(Uint16 DownDataBuf)
{
	if (DownDataBuf==0x1328 && DownTableFlag==CLEAR)        //表明为下载数据命令
	{
		DownTableFlag	= SET;
		DownloadTableCnt = 1;
	}
	else if (DownloadTableCnt == 1 && DownTableFlag == SET) // 参数表长度
	{
		ParamTableLen = DownDataBuf;              // ParamTableLen = n+2
		if (ParamTableLen == CAL_TABLE_LEN+2)
		{
			SaveTablePt = (Uint16 *)0x8002;
		}
		else if (ParamTableLen == WELL_TABLE_LEN+2)
		{
			SaveTablePt = (Uint16 *)0x8017;
		}
		*SaveTablePt	= ParamTableLen;
		DownloadTableCnt = 2;		
	}
	else if (DownloadTableCnt == 2 && DownTableFlag == SET)   // 参数表ID
	{
		*SaveTablePt++	= DownDataBuf;
		*(Uint16 *)0x8000 = DownDataBuf;
	}
	else if (DownloadTableCnt == ParamTableLen && DownTableFlag == SET)   // 最后一个数据为CheckSum
	{
		// CheckSum校验
		Uint16 check_sum = 0;
		int i=1;
		for (;i<=ParamTableLen-1;++i)
		{
			check_sum += (*(SaveTablePt-i));
		}
		check_sum += 0x1328;
		
		if (check_sum == DownDataBuf)                   // success
		{
			*SaveTablePt = DownDataBuf;

			GpioDataRegs.GPFDAT.bit.GPIOF9 = 1;    		// SCIA设置为发送状态
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0x0003;              	// 发送数据
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = *SaveTablePt;           // 发送数据
			while (SciaTx_Ready() == 0) {}
			SciaRegs.SCITXBUF = 0x0003+*SaveTablePt;    // 发送数据
			GpioDataRegs.GPFDAT.bit.GPIOF9 = 0;    		// SCIA设置为接收状态

			if (*(Uint16 *)0x8000 == 0x0002)            // 设置工作模式
				*(Uint16 *)0x8001 = *(Uint16 *)0x8007;
			else if (*(Uint16 *)0x8000 == 0x0003)
				*(Uint16 *)0x8001 = *(Uint16 *)0x801C;
		}
		else                                            // error
		{
			ErrorSendData(0x1, DownDataBuf);
		}
		//下载标志位清除
		DownTableFlag	= CLEAR;
	}
	else if (DownTableFlag == SET)
	{
		*SaveTablePt++	= DownDataBuf;
		DownloadTableCnt++;
	}
 	return;
}

Uint16 RecSendTableCnt = 0;
// 接收上传参数表命令
void RecSendTableCommand(Uint16 DownDataBuf)
{
	if (BufferSciaDataAll==0x1428 && RecSendTableFlag==CLEAR)
	{
		RecSendTableFlag == SET;
		RecSendTableCnt = 1;
	}	
	else if (RecSendTableCnt==1 && RecSendTableFlag==SET)
	{
		RecSendTableCmdParaLen = DownDataBuf;
		RecSendTableCnt = 2;
	}
	else if (RecSendTableCnt==2 && RecSendTableFlag==SET)
	{
		SendTableID = DownDataBuf;    // 保存需要上传的参数表的ID
		RecSendTableCnt = 3;
	}
	else if (RecSendTableCnt==3 && RecSendTableFlag==SET)
	{	
		Uint16 CheckSum = 0;
		CheckSum += 0x1428;
		CheckSum += RecSendTableCmdParaLen;
		CheckSum += SendTableID;

		if (CheckSum == DownDataBuf)
			SendTableFlag = SET;
		else
			ErrorSendData(0x2, DownDataBuf);
		
		RecSendTableFlag = CLEAR;
	}
}
