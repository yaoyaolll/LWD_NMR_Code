//###########################################################################
//
// FILE:   MyFunctions.c
//
// TITLE:
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

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"
#include "IQmathLib.h"

#pragma CODE_SECTION(Delay, "secureRamFuncs");
#pragma CODE_SECTION(AcqNoise, "secureRamFuncs");
#pragma CODE_SECTION(CalNoise, "secureRamFuncs");
#pragma CODE_SECTION(SaveNoise, "secureRamFuncs");
#pragma CODE_SECTION(ScanFreqOnce, "secureRamFuncs");
#pragma CODE_SECTION(CalSignal, "secureRamFuncs");
#pragma CODE_SECTION(DCWorkOnce, "secureRamFuncs");
#pragma CODE_SECTION(StoreMini, "secureRamFuncs");

Uint32 TesN;
Uint32 TelN;

void PulseParamIncrement(void)
{
	Pulse90StoreAddr++;
	PulseF180StoreAddr++;
	PulseL180StoreAddr++;
}

void Delay(unsigned int nDelay)
{
	int ii, jj, kk = 0;
	for (ii = 0; ii < nDelay; ii++)
	{
		for (jj = 0; jj < 16; jj++)
		{
			kk++;
		}
	}
	return;
}

//Noise acquire function
void AcqNoise(void)
{
	//Select Noise acquisition Channel
	CTRL_CHOICE = 0x0;			  //选择扫频控制通路，控制信号：CTRL_CHOICE 为0扫频、为1刻度、为2激励采集，复用function_parts
	DSP_NS_CTRL_EN = USER_ENABLE; //选择噪声数据通道，控制信号：DSP_NS_CTRL_EN选择噪声数据通道，控制信号：DSP_NS_CTRL_DIS选择信号数据通道
	PLUSE_NOISE_EN = USER_ENABLE; //选择噪声采集通路

	RstNoiseModule();
	//Load Noise Parameters
	NSTATE_CHOICE_EN = USER_ENABLE; //使能噪声状态机参数选择信号，NTimeDec为DECOUPLE板导通稳定所需时间的FPGA计数值
	NSTATE_DATA = NTimeDec;			//DSP向FPGA发送噪声状态机参数
	NSTATE_LOAD_EN = USER_ENABLE;	//使能噪声状态机参数装载信号
	NSTATE_LOAD_DIS = USER_DISABLE; //清零噪声状态机参数装载信号

	NSTATE_CHOICE_DIS = USER_DISABLE;		 //使能噪声状态机参数选择信号
	NSTATE_DATA = NoiseAcqTime * FPGA_COUNT; //装载信号：噪声采集时间的FPGA计数值
	NSTATE_LOAD_EN = USER_ENABLE;			 //使能噪声状态机参数装载信号
	NSTATE_LOAD_DIS = USER_DISABLE;			 //清零噪声状态机参数装载信号

	NoiseDivFreq = 1000 / NoiseAcqFreq;
	NoiseDivNum = (NoiseDivFreq / 2) * 33 + NoiseDivFreq % 2; //噪声分频系数
	NoiseAcqNum = NoiseAcqTime * NoiseAcqFreq / 10;			  //噪声采样点数

	NRAM_ACQNUM = NoiseAcqNum; //装载噪声采样点数
	NRAM_DIVNUM = NoiseDivNum; //装载噪声分频字
	NRAM_LOAD_EN = USER_ENABLE;
	NRAM_LOAD_DIS = USER_DISABLE;
	//start acquire
	ACQCLK_EN = 0x1;			  //使能ACQ采集时钟输出控制信号
	NOISE_START_EN = USER_ENABLE; //使能噪声状态机启动信号

	CycleFlag = SET; //噪声状态机启动后DSP循环执行此处，直至噪声状态机执行完，扫频中断发生，将flag_scanone清零，退出循环
	do
	{
		;
	} while (CycleFlag == SET);
	return;
}

//计算存储噪声函数
void CalNoise(void)
{
	NRAM_RST_EN = USER_ENABLE;
	NRAM_RST_DIS = USER_DISABLE;
	NRAM_RD_EN = USER_ENABLE;
	for (NoiseAcqCnt = 0; NoiseAcqCnt < NoiseAcqNum; NoiseAcqCnt++)
	{
		if (NoiseAcqCnt > 511) // 防止数组越界
			break;
		NoiseDataAry[NoiseAcqCnt] = READ_NOISE;
	}

	//计算平均值
	NoiseSum = 0;
	for (NoiseAcqCnt = NOISE_STRIP - 1; NoiseAcqCnt < NoiseAcqNum - 1; NoiseAcqCnt++)
	{
		NoiseSum += (Uint32)NoiseDataAry[NoiseAcqCnt];
	}

	NoiseCalNumIQ = _IQ(NoiseAcqNum - NOISE_STRIP);
	NoiseAveShiftIQ = _IQdiv(_IQ(NoiseSum), NoiseCalNumIQ);
	NoiseAveIQ = NoiseAveShiftIQ - _IQ(2048);

	//计算标准偏差和最大偏差
	NoiseSquSumIQ3 = _IQ3(0);
	NoiseMaxValIQ = _IQ(0);
	for (NoiseAcqCnt = NOISE_STRIP - 1; NoiseAcqCnt < NoiseAcqNum - 1; NoiseAcqCnt++)
	{
		NoiseOfsIQ = _IQ(NoiseDataAry[NoiseAcqCnt]) - NoiseAveShiftIQ;
		NoiseOfsIQ3 = _IQtoIQ3(NoiseOfsIQ);
		NoiseSquSumIQ3 += _IQ3mpy(NoiseOfsIQ3, NoiseOfsIQ3);
		NoiseOfsAbsIQ = _IQabs(NoiseOfsIQ);
		if (NoiseOfsAbsIQ > NoiseMaxValIQ) //如当前点噪声绝对值大于现存最大值，则替代
		{
			NoiseMaxValIQ = NoiseOfsAbsIQ;
		}
	}
	NoiseSquAveIQ3 = _IQ3div(NoiseSquSumIQ3, _IQtoIQ3(NoiseCalNumIQ));
	NoiseSqrAveIQ = _IQsqrt(_IQ3toIQ(NoiseSquAveIQ3));
	return;
}

void SaveNoise(Uint32 AddrStr)
{
	SaveNTempPt = (int *)(AddrStr); //指向均值地址
	*SaveNTempPt = _IQint(_IQmpy(NoiseAveIQ, _IQ(10)));

	SaveNTempPt++; //指向标准偏差地址
	*SaveNTempPt = _IQint(_IQmpy(NoiseSqrAveIQ, _IQ(10)));

	SaveNTempPt++; //指向最大偏差地址
	*SaveNTempPt = _IQint(_IQmpy(NoiseMaxValIQ, _IQ(10)));
	return;
}

void ScanFreqOnce() //扫频子函
{
	//Select Scan Channel
	DSP_NS_CTRL_DIS = USER_DISABLE; //选择信号数据通道，控制信号：DSP_NS_CTRL_EN选择噪声数据通道，控制信号：DSP_NS_CTRL_DIS选择信号数据通道
	CTRL_CHOICE = 0x0;				//控制通路选择
									//Reset Scan Module
	SCAN_RST_EN = USER_ENABLE;		//使能扫频状态机复位信号
	SCAN_RST_DIS = USER_DISABLE;
	//Load Scan Parameters
	SCAN_CHOICE_EN = USER_ENABLE; //使能状态机参数选择信号，STimeDec为DECOUPLE板导通稳定所需时间的FPGA计数值
	SCAN_DATA = STimeDec;
	SCAN_LOAD_EN = USER_ENABLE;
	SCAN_LOAD_DIS = USER_DISABLE;

	SCAN_CHOICE_DIS = USER_DISABLE;
	SCAN_DATA = 7200; //装载信号采集时间
	//SCAN_DATA		= 37000/FreqScan*FPGA_COUNT;
	SCAN_LOAD_EN = USER_ENABLE;
	SCAN_LOAD_DIS = USER_DISABLE;

	ScanSignalNum = (Uint16)(36) * SiglAcqFreqTim; //信号采样点数
	SIGNAL_ACQNUM = ScanSignalNum;				   //装载信号采样点数
	SIGNAL_PERIODNUM = SiglAcqFreqTim;
	SIGNAL_LOAD_EN = USER_ENABLE;
	SIGNAL_LOAD_DIS = USER_DISABLE;
	//Load Cal Parameter
	CalDivData = 2 * SiglAcqFreqTim; //cal信号分频系数
	CAL_DIVDATA = CalDivData;		 //装载cal分频字
	CAL_DATALOAD_EN = USER_ENABLE;
	CAL_DATALOAD_DIS = USER_DISABLE;

	LoadDDSPara(); //装载DDS参数

	ACQCLK_EN = USER_ENABLE;	 //控制FPGA输出的采集时钟，此时选择的是信号数据通道，故输出信号采集时钟
	SCAN_START_EN = USER_ENABLE; //FPGA扫频状态机启动信号为高，有效

	CycleFlag = SET; //扫频状态机启动后DSP循环执行此处，直至扫频状态机执行完，中断发生，将flag_scanone清零，退出循环
	do
	{
		;
	} while (CycleFlag == SET);

	return;
}

void CalSignal(Uint16 SignalNum)
{
	//-------------读取8路加法器结果数据--------------------------------------------//
	for (AdderCnt = 1; AdderCnt < 11; AdderCnt++)
	{
		DATACHOICE = 2 * AdderCnt - 1;
		asm(" NOP");
		AdderLowAry[AdderCnt] = RDDATA;
		DATACHOICE = 2 * AdderCnt;
		asm(" NOP");
		AdderResAry[AdderCnt] = RDDATA;
	}
	//-------------计算8路加法器结果数据----------------------------------------//
	for (AdderCnt = 1; AdderCnt < 11; AdderCnt++)
	{
		AdderResAry[AdderCnt] = (AdderResAry[AdderCnt] << 16) + AdderLowAry[AdderCnt];
	}
	//-------------计算----------------------------------------------------//
	SignalCalNum = SignalNum - SiglAcqFreqTim;

	//-------------采样率位每个周期10个点---------------------------------//
	if (SiglAcqFreqTim == 10)
	{
		SinOne = AdderResAry[2] - AdderResAry[7] + AdderResAry[5] - AdderResAry[10];
		SinTwo = AdderResAry[3] - AdderResAry[8] + AdderResAry[4] - AdderResAry[9];
		CosOne = AdderResAry[1] - AdderResAry[6];
		CosTwo = AdderResAry[2] - AdderResAry[5] + AdderResAry[10] - AdderResAry[7];
		CosThree = AdderResAry[3] - AdderResAry[4] + AdderResAry[9] - AdderResAry[8];

		SinSumIQ = _IQmpy(_IQ(0.5878), _IQ(SinOne)) + _IQmpy(_IQ(0.9511), _IQ(SinTwo));
		CosSumIQ = _IQmpy(_IQ(1), _IQ(CosOne)) + _IQmpy(_IQ(0.809), _IQ(CosTwo)) + _IQmpy(_IQ(0.309), _IQ(CosThree));
	}

	//-------------采样率位每个周期6个点---------------------------------//
	else if (SiglAcqFreqTim == 6)
	{
		SinOne = AdderResAry[2] + AdderResAry[3] - AdderResAry[5] - AdderResAry[6];
		CosOne = AdderResAry[1] - AdderResAry[4];
		CosTwo = AdderResAry[2] + AdderResAry[6] - AdderResAry[3] - AdderResAry[5];

		SinSumIQ = _IQmpy(_IQ(0.866), _IQ(SinOne));
		CosSumIQ = _IQmpy(_IQ(1), _IQ(CosOne)) + _IQmpy(_IQ(0.5), _IQ(CosTwo));
	}
	//-------------当采样率位每个周期不为6或10个点时，默认选择成8个点---------------------------------//
	else
	{
		SinOne = AdderResAry[3] - AdderResAry[7];
		SinTwo = AdderResAry[2] - AdderResAry[6] + AdderResAry[4] - AdderResAry[8];
		CosOne = AdderResAry[1] - AdderResAry[5];
		CosTwo = AdderResAry[2] - AdderResAry[4] + AdderResAry[8] - AdderResAry[6];

		SinSumIQ = _IQmpy(_IQ(1), _IQ(SinOne)) + _IQmpy(_IQ(0.7071), _IQ(SinTwo));
		CosSumIQ = _IQmpy(_IQ(1), _IQ(CosOne)) + _IQmpy(_IQ(0.7071), _IQ(CosTwo));
	}

	//-------------计算幅值相位---------------------------------//
	SinAveIQ = _IQdiv(SinSumIQ, _IQ(SignalCalNum)); //正弦信号卷积求平均
	CosAveIQ = _IQdiv(CosSumIQ, _IQ(SignalCalNum)); //余弦信号卷积求平均

	SignalAmpIQ = 2 * _IQmag(SinAveIQ, CosAveIQ);
	SignalPhaIQ = _IQatan2(CosAveIQ, SinAveIQ); //求输入信号相位
	return;
}

void SaveSignal(Uint32 AddrStr)
{
	SaveSTempPt = (Uint16 *)(AddrStr); //指向幅值地址
	*SaveSTempPt = _IQint(_IQmpy(SignalAmpIQ, _IQ(10)));
	return;
}

// 第二个参数为噪声地址，第三个参数为扫频数据存储地址
void MiniScan(Uint16 MiniFreq, Uint32 NoiseStorAddr, Uint32 SiglStorAddr)
{
	//Acquire noise data once
	NTimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;
	STimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;
	AcqNoise();
	CalNoise();
	SaveNoise(NoiseStorAddr);
	//Scan once
	MiniFreq -= ScanDeltaFreq * 4;
	for (MiniFreqCnt = 0; MiniFreqCnt < 9; MiniFreqCnt++)
	{
		FreqScan = MiniFreq + MiniFreqCnt * ScanDeltaFreq;
		*(Uint16 *)DDS_FREQ_ADDR = FreqScan;
		ScanFreqOnce();
		CalSignal(ScanSignalNum);
		SaveSignal(SiglStorAddr + MiniFreqCnt);
	}
	return;
}

interrupt void XINT1_STOP(void)
{
	SCAN_START_DIS = USER_DISABLE;
	NOISE_START_DIS = USER_DISABLE;

	PLUSE_START_DIS = USER_DISABLE;

	SCALE_START_DIS = USER_DISABLE;

	ACQCLK_DIS = USER_DISABLE;

	CycleFlag = CLEAR;

	IER |= M_INT1;
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;
	EINT;
	return;
}

//存储激励函数
void SavePulse(Uint32 StoreAddr) // 刻度存储90度激励函数
{
	PulseGainIQ = _IQ(PulseGainAry[PulseGain]);
	PulseAmpCrtIQ = _IQmpy(SignalAmpIQ, PulseGainIQ);
	SaveSTempPt = (Uint16 *)(StoreAddr); //指向幅值地址
	*SaveSTempPt = _IQint(_IQdiv(PulseAmpCrtIQ, _IQ(100)));
	return;
}

void SaveEcho(Uint32 StoreEchoAddr) // 刻度存储回波函数
{
	SaveSTempPt = (Uint16 *)(StoreEchoAddr); //指向i幅值地址
	*SaveSTempPt = _IQint(_IQmpy(SinAveIQ, _IQ(10)));
	SaveSTempPt = (Uint16 *)(StoreEchoAddr + 1); //指向i幅值地址
	*SaveSTempPt = _IQint(_IQmpy(CosAveIQ, _IQ(10)));
	return;
}

void SavePhaseWord(void)
{
	if (PhaseFlag == POSITIVE)
	{
		*SaveNTempPt = 0x0;
	}
	else if (PhaseFlag == NEGATIVE)
	{
		*SaveNTempPt = 0x1111;
	}
}

//void SaveSixFreq(void) //改为8个频率
//{
//	for (SaveCnt = 1; SaveCnt < BAND_NUM; SaveCnt++)
//	{
//		SaveNTempPt++;
//		*SaveNTempPt = FreqAry[SaveCnt];
//	}
//}

void StoreMini(Uint16 FreqNum1, int *NoiseStoreAddr, Uint16 *SignalStoreAddr)
{
	//计算某一工作频率9个mini扫频点的平均值、噪声均值的平均值、噪声标准偏差的平均值
	MiniTablePt = (Uint16 *)(MINITABLE_START);
	for (MiniCycCnt1 = 0; MiniCycCnt1 < FreqNum1; MiniCycCnt1++)
	{
		FreqNum2 = *StoreMiniAryPt;
		MiniNoiseMax = 0;
		for (MiniCycCnt2 = 1; MiniCycCnt2 < 12; MiniCycCnt2++)
		{
			MiniAddAry[MiniCycCnt2] = 0;
		}
		for (MiniCycCnt2 = 0; MiniCycCnt2 < FreqNum2; MiniCycCnt2++)
		{
			for (MiniCycCnt3 = 1; MiniCycCnt3 < 13; MiniCycCnt3++)
			{
				if (MiniCycCnt3 < 12)
				{
					MiniAddAry[MiniCycCnt3] += *(MiniTablePt + MiniCycCnt3);
				}
				else
				{
					MiniBuf = *(Uint16 *)(MiniTablePt + MiniCycCnt3);
					if (MiniBuf > MiniNoiseMax)
					{
						MiniNoiseMax = MiniBuf;
					}
				}
			}
			MiniTablePt += 12;
		}
		for (MiniCycCnt2 = 1; MiniCycCnt2 < 12; MiniCycCnt2++)
		{
			MiniAddAry[MiniCycCnt2] /= FreqNum2;
		}
		for (MiniCycCnt2 = 1; MiniCycCnt2 < 10; MiniCycCnt2++)
		{
			*SignalStoreAddr = (Uint16)MiniAddAry[MiniCycCnt2];
			SignalStoreAddr++;
		}
		for (MiniCycCnt2 = 10; MiniCycCnt2 < 12; MiniCycCnt2++)
		{
			*NoiseStoreAddr = (int)MiniAddAry[MiniCycCnt2];
			NoiseStoreAddr++;
		}
		*NoiseStoreAddr = MiniNoiseMax;
		NoiseStoreAddr++;
		StoreMiniAryPt++;
	}
}

void ChangePhase(void)
{
	if (PhaseFlag == POSITIVE)
	{
		PhaseFlag = NEGATIVE;
	}
	else if (PhaseFlag == NEGATIVE)
	{
		PhaseFlag = POSITIVE;
	}
	return;
}

void DCWorkOnce(Uint16 Freq)    // Freq，单位为0.1kHz
{
	//Select Scale Channel
	CTRL_CHOICE = 0x1;				//控制通路选择
	DSP_NS_CTRL_DIS = USER_DISABLE; //选择信号数据通道，控制信号：DSP_NS_CTRL_EN选择噪声数据通道，控制信号：DSP_NS_CTRL_DIS选择信号数据通道
	PLUSE_SCALE_EN = USER_ENABLE;	//选择刻度激励通路，控制信号PLUSE_SCALE_EN选择刻度通路，控制信号PLUSE_SCALE_DIS选择激励检测通路，复用刻度模块的内外桥
									//Reset Scale Module
	SCALE_START_DIS = USER_DISABLE;
	SCALE_RST_EN = USER_ENABLE; // 复位ScaleState状态机
	SCALE_RST_DIS = USER_DISABLE;

	DCWorkFreq = Freq / 10;     // 转换为kHz
	LoadBriDumpPara();
	*(Uint16 *)DDS_FREQ_ADDR = Freq;
	LoadDDSPara();

	SIGNAL_PERIODNUM = SiglAcqFreqTim; //装载信号采样率SIGNAL_PERIODNUM，DSP向FPGA发送信号采样率SIGNAL_ACQFREQ
	SIGNAL_LOAD_EN = USER_ENABLE;
	SIGNAL_LOAD_DIS = USER_DISABLE;
	//90度激励时间计数值
	Pulse90Width = Width90Pulse * FPGA_COUNT; // Width90Pulse在CheckTable()中获取值
	//180度激励时间计数值
	PulseMid1 = Angle180Pulse * 1.0;
	PulseMid2 = PulseMid1 / 180;
	PulseMid3 = PulseMid2 * Pulse90Width;
	Pulse180WidthHalf = (Uint32)PulseMid3;
	Pulse180Width = Pulse180WidthHalf * 2;
	//回波采集时间计算
	EchoMid1 = SiglAcqPrdNum * 0.5;
	EchoMid2 = DCWorkFreq * 1.0;
	EchoMid3 = (1000 / EchoMid2) * (EchoMid1 + 1) * FPGA_COUNT;
	EchoMid4 = (1000 / EchoMid2) * EchoMid1 * FPGA_COUNT;
	EchoAcqTimeFHalf = (Uint16)EchoMid3;
	EchoAcqTimeBHalf = (Uint16)EchoMid4 + 2 * FPGA_COUNT;
	EchoAcqTime = EchoAcqTimeFHalf + EchoAcqTimeBHalf;
	//90度脉冲补偿时间计算
	TNMid1 = T_N * 1.0;
	TNMid2 = (1000 / EchoMid2) * TNMid1 * FPGA_COUNT;
	TNTime = (Uint32)(TNMid2 + 0.5);
	//导通和关断时间计算,回波采集点数计算

	TesN = ((Tes / 2000) * DCWorkFreq / 10 + 5) / 10;
	TesCmp = ((TesN * 200000 / DCWorkFreq + 1) / 2) * 2;
	TelN = ((Tel / 2000) * DCWorkFreq / 10 + 5) / 10;
	TelCmp = ((TelN * 200000 / DCWorkFreq + 1) / 2) * 2;

	Cmp90 = Pulse90Width + MainDumpTime + SOFT_DUMP_TIME + SCALE_REPAIR1 + TNTime;
	Cmp180FHalf = Pulse180WidthHalf + MainDumpTime + SOFT_DUMP_TIME + EchoAcqTimeFHalf + SWITCH_REPAIR - EchoAcqWindowShift * FPGA_COUNT;
	Cmp180BHalf = Pulse180WidthHalf + EchoAcqTimeBHalf + SCALE_REPAIR2 + EchoAcqWindowShift * FPGA_COUNT;
	CmpTesHalf = TesCmp >> 1;
	CmpTelHalf = TelCmp >> 1; //长TE下的隔离板的打开与隔离时间
	//时间计算检查
	if (Cmp90 > CmpTelHalf || Cmp180FHalf > CmpTelHalf || Cmp180BHalf > CmpTelHalf || Cmp180BHalf > CmpTesHalf || Cmp180BHalf > CmpTesHalf)
	{
		TesCCheck = 60000;
		TelCCheck = TesCCheck;
		//90度激励时间计数值,默认为34us
		Pulse90Width = 3400;
		//回波发射脉冲宽度，默认为135度，可计算180度的脉冲宽度
		Pulse180WidthHalf = 2550; //135/180×3400=2550
		Pulse180Width = 5100;	  //135/180×3400×2=5100
		//回波采集周期数默认为16，计算如下参数
		EchoMid3 = (1000 / EchoMid2) * (8 + 1) * FPGA_COUNT;
		EchoMid4 = (1000 / EchoMid2) * 8 * FPGA_COUNT;
		EchoAcqTimeFHalf = (Uint16)EchoMid3;
		EchoAcqTimeBHalf = (Uint16)EchoMid4 + 2 * FPGA_COUNT;
		EchoAcqTime = EchoAcqTimeFHalf + EchoAcqTimeBHalf;
		//采集窗平移时间恢复默认值为23us，计算如下参数
		Cmp90 = Pulse90Width + MainDumpTime + SOFT_DUMP_TIME + SCALE_REPAIR1 + TNTime;
		Cmp180FHalf = Pulse180WidthHalf + MainDumpTime + SOFT_DUMP_TIME + EchoAcqTimeFHalf + SWITCH_REPAIR - 23 * FPGA_COUNT;
		Cmp180BHalf = Pulse180WidthHalf + EchoAcqTimeBHalf + SCALE_REPAIR2 + 23 * FPGA_COUNT;
		CmpTesHalf = TesCCheck >> 1;
		CmpTelHalf = TelCCheck >> 1;

		Cut90Time = CmpTelHalf - Cmp90 - 1;
		Open180LTime = CmpTelHalf - Cmp180FHalf;
		Cut180LTime = CmpTelHalf - Cmp180BHalf - 2;
		Cut180STime = CmpTesHalf - Cmp180BHalf - 2;
		Open180STime = CmpTesHalf - Cmp180FHalf;
		EchoAcqNum = (16 + 1) * SiglAcqFreqTim;
	}
	else
	{
		Cut90Time = CmpTelHalf - Cmp90 - 1;
		Open180LTime = CmpTelHalf - Cmp180FHalf;
		Cut180LTime = CmpTelHalf - Cmp180BHalf - 2;
		Cut180STime = CmpTesHalf - Cmp180BHalf - 2;
		Open180STime = CmpTesHalf - Cmp180FHalf;
		EchoAcqNum = (SiglAcqPrdNum + 1) * SiglAcqFreqTim;
	}
	CmpI90 = Pulse180Width + MainDumpTime + 4000 + SCALE_REPAIR1;
	if ((CmpI90 >= (CmpTesHalf - 100)) || (InverseTurnFlag == CLEAR))
	{
		CutI90TimeLow = 200;
		CutI90TimeHi = 0;
		INV_TURN_DIS = USER_DISABLE;
	}
	else
	{
		CutI90Time = CmpTesHalf - CmpI90;
		CutI90TimeLow = CutI90Time & 0x0000ffff;
		CutI90TimeHi = (CutI90Time & 0xffff0000) >> 1;
		INV_TURN_EN = USER_ENABLE;
	}

	Cut90TimeLow = Cut90Time & 0x0000ffff;
	Cut90TimeHi = (Cut90Time & 0xffff0000) >> 16;
	Open180STimeLow = Open180STime & 0x0000ffff;
	Open180STimeHi = (Open180STime & 0xffff0000) >> 16;
	Cut180STimeLow = Cut180STime & 0x0000ffff;
	Cut180STimeHi = (Cut180STime & 0xffff0000) >> 16;
	Open180LTimeLow = Open180LTime & 0x0000ffff;
	Open180LTimeHi = (Open180LTime & 0xffff0000) >> 16;
	Cut180LTimeLow = Cut180LTime & 0x0000ffff;
	Cut180LTimeHi = (Cut180LTime & 0xffff0000) >> 16;
	//计算脉冲采集周期数计采集点数
	EchoMid1 = DCWorkFreq * 0.00001;
	EchoMid2 = Pulse90Width * EchoMid1;
	EchoMid3 = Pulse180Width * EchoMid1;
	P90PrdNum = (Uint16)EchoMid2;  //如有必要，该值应该减1
	P180PrdNum = (Uint16)EchoMid3; //如有必要，该值应该减1

	if (P90PrdNum > 6)
	{
		Acq90Num = SiglAcqFreqTim * 6; //90度激励采集点数
		Strip90Num = (P90PrdNum - 6) * SiglAcqFreqTim;
	}
	else
	{
		Acq90Num = SiglAcqFreqTim * P90PrdNum; //90度激励采集点数
		Strip90Num = 0;
	}

	if (P180PrdNum > 11)
	{
		Acq180Num = SiglAcqFreqTim * 11; //180度激励采集点数
		Strip180Num = (P180PrdNum - 11) * SiglAcqFreqTim;
	}
	else
	{
		Acq180Num = SiglAcqFreqTim * P180PrdNum; //180度激励采集点数
		Strip180Num = 0;
	}
	//加载PD模块参数
	Pd90Time = Pulse90Width;
	Pd180Time = Pulse180Width;
	LoadPdPara();
	//加载SD模块参数
	SdAcqNum1 = (Uint16)(((SD_SACQ_T2 - SD_SACQ_T1) * DDSFreq) / 100000);
	SdAcqNum2 = (Uint16)(((SD_SACQ_T2 - SD_SACQ_T1 + Pulse90Width) * DDSFreq) / 100000);
	SdAcqNum3 = (Uint16)(((SD_SACQ_T2 - SD_SACQ_T1 + Pulse180Width) * DDSFreq) / 100000);

	SdAcqTimeMid1 = (float)(CmpTesHalf + EchoAcqWindowShift * FPGA_COUNT + Pulse180WidthHalf + SCALE_REPAIR2 - EchoAcqTimeFHalf - SWITCH_REPAIR);
	SdAcqTimeMid2 = SdAcqTimeMid1 - SD_SACQ_T1;
	SdAcqTimeMid3 = SdAcqTimeMid1 - SD_SACQ_T1 + EchoAcqTime;
	SdAcqNum4 = (Uint32)((SdAcqTimeMid2 * DDSFreq) / 100000);
	SdAcqNum5 = (Uint32)((SdAcqTimeMid3 * DDSFreq) / 100000);
	SdAcqNum4Hi = SdAcqNum4 / 65536;
	SdAcqNum4Low = SdAcqNum4 % 65536;
	SdAcqNum5Hi = SdAcqNum5 / 65536;
	SdAcqNum5Low = SdAcqNum5 % 65536;

	SdAcqTimeMid1 = (float)(CmpTelHalf + EchoAcqWindowShift * FPGA_COUNT + Pulse180WidthHalf + SCALE_REPAIR2 - EchoAcqTimeFHalf - SWITCH_REPAIR);
	SdAcqTimeMid2 = SdAcqTimeMid1 - SD_SACQ_T1;
	SdAcqTimeMid3 = SdAcqTimeMid1 - SD_SACQ_T1 + EchoAcqTime;
	SdAcqNum6 = (Uint32)((SdAcqTimeMid2 * DDSFreq) / 100000);
	SdAcqNum7 = (Uint32)((SdAcqTimeMid3 * DDSFreq) / 100000);
	SdAcqNum6Hi = SdAcqNum6 / 65536;
	SdAcqNum6Low = SdAcqNum6 % 65536;
	SdAcqNum7Hi = SdAcqNum7 / 65536;
	SdAcqNum7Low = SdAcqNum7 % 65536;

	SD_SACQ_CHOICE = 0x1;
	SD_SACQ_DATA = SdAcqNum1;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x2;
	SD_SACQ_DATA = SdAcqNum2;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x3;
	SD_SACQ_DATA = SdAcqNum3;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x4;
	SD_SACQ_DATA = SdAcqNum4Low;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x5;
	SD_SACQ_DATA = SdAcqNum4Hi;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x6;
	SD_SACQ_DATA = SdAcqNum5Low;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x7;
	SD_SACQ_DATA = SdAcqNum5Hi;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x8;
	SD_SACQ_DATA = SdAcqNum6Low;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0x9;
	SD_SACQ_DATA = SdAcqNum6Hi;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0xA;
	SD_SACQ_DATA = SdAcqNum7Low;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;

	SD_SACQ_CHOICE = 0xB;
	SD_SACQ_DATA = SdAcqNum7Hi;
	SD_SACQ_LOAD_EN = USER_ENABLE;
	SD_SACQ_LOAD_DIS = USER_DISABLE;
	//加载Cal模块参数
	SCALE_CHOICE = 0x0;
	SCALE_DATA = (Uint16)Pulse90Width; //pluse90=3400
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x1;
	SCALE_DATA = (Uint16)Pulse180Width; //pluse180=5100
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x2;
	SCALE_DATA = MainDumpTime;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x3;
	SCALE_DATA = SOFT_DUMP_TIME;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x4;
	SCALE_DATA = Cut90TimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x5;
	SCALE_DATA = Cut90TimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x6;
	SCALE_DATA = Cut180STimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x7;
	SCALE_DATA = Cut180STimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x8;
	SCALE_DATA = Open180STimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x9;
	SCALE_DATA = Open180STimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xA;
	SCALE_DATA = EchoAcqTime;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xB;
	SCALE_DATA = Ne; //装载NE个数
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xC;
	SCALE_DATA = Acq90Num;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xD;
	SCALE_DATA = Acq180Num;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xE;
	SCALE_DATA = EchoAcqNum;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0xF;
	SCALE_DATA = Strip90Num;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x10;
	SCALE_DATA = Strip180Num;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;
	//DE参数
	SCALE_CHOICE = 0x11;
	SCALE_DATA = ScaleM; //装载长TE冲个数
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x12;
	SCALE_DATA = Cut180LTimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x13;
	SCALE_DATA = Cut180LTimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x14;
	SCALE_DATA = Open180LTimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x15;
	SCALE_DATA = Open180LTimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x16;
	SCALE_DATA = Cut180STimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x17;
	SCALE_DATA = Cut180STimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x18;
	SCALE_DATA = CutI90TimeLow;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	SCALE_CHOICE = 0x19;
	SCALE_DATA = CutI90TimeHi;
	SCALE_LOAD_EN = USER_ENABLE;
	SCALE_LOAD_DIS = USER_DISABLE;

	PulseGain = DCWorkFreq - 500;
	if (PulseGain < 0)
	{
		PulseGain = 0;
	}
	else if (PulseGain > 500)
	{
		PulseGain = 500;
	}
	//load phase
	if (PhaseFlag == POSITIVE)
	{
		POSI_NEGE_EN = USER_ENABLE;
	}
	else if (PhaseFlag == NEGATIVE)
	{
		POSI_NEGE_DIS = USER_DISABLE;
	}
	//dump_sustain_timer controller
	Open180LTimeMS = (Uint16)((Open180LTime + SOFT_DUMP_TIME) / 10000);
	if (Open180LTimeMS > 9) //present time exceed 1ms.
	{
		DSTTimeOne = (Open180LTimeMS - 9) % 10;
		DUMP_SUSTAIN_DATA = DSTTimeOne;
		DUMP_SUSTAIN_EN = USER_ENABLE;
		DumpSustainFlag = SET;
	}

	ACQCLK_EN = USER_ENABLE;
	SCALE_START_EN = USER_ENABLE;

	CycleFlag = SET;
	StoreCnt = 0;

	do
	{
		;
	} while (CycleFlag == SET);

	InverseTurnFlag = CLEAR;
	INV_TURN_DIS = USER_DISABLE;
	/*
	if (DumpSustainFlag==SET)
	{
		DUMP_SUSTAIN_DIS= USER_DISABLE;
		DumpSustainFlag	= CLEAR;
	}
*/
	return;
}



