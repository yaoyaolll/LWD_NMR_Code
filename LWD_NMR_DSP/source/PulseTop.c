/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:31:40
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:11:37
 */
/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#ifndef DEBUG
#pragma CODE_SECTION(PulseAcq, "secureRamFuncs");
#pragma CODE_SECTION(PulseSave, "secureRamFuncs");
#endif

//pluse波形采集检测主函数
void PulseTop(void) //波形检测主函数
{
	// 此模式下的继电器码根据下发的频率计算得到
	RelayCode = CalRelayFromFre(CenterFreq);

	MatFreq = CenterFreq;		// 此处必须对MatFreq赋值，0.1kHz
	PhaseFlag = POSITIVE;

    RelayOpen(RelayCode);

	//mini scan and pulse acquisition
	MiniScan(MatFreq, PLUSETABLE_START + 5, PLUSETABLE_START + 8); //mini扫频

//    AcqNoise();                                        //采集噪声
//    CalNoise();                                        //计算噪声
//
//    SaveNTempPt = (int *)(PLUSETABLE_START + 4); //指向均值地址
//    *SaveNTempPt = _IQint(_IQmpy(NoiseAveIQ, _IQ(10)));
//
//    SaveNTempPt++; //指向标准偏差地址
//    *SaveNTempPt = _IQint(_IQmpy(NoiseSqrAveIQ, _IQ(10)));
//
//    SaveNTempPt++; //指向最大偏差地址
//    *SaveNTempPt = _IQint(_IQmpy(NoiseMaxValIQ, _IQ(10)));
//
//    MiniFreq = MatFreq;
//    MiniFreq -= ScanDeltaFreq * 4;
//    for (MiniFreqCnt = 0; MiniFreqCnt < 9; MiniFreqCnt++) //某频带已扫频个数0-8
//    {
//        FreqScan = MiniFreq + MiniFreqCnt * ScanDeltaFreq; //计算扫频频率FreqScan，以理论工作频率MiniFreq为中心，加上i-5倍的步进频率ScanDeltaFreq
//
//        *(Uint16 *)DDS_FREQ_ADDR = FreqScan;
//        ScanFreqOnce();           //扫频操作
//        CalSignal(ScanSignalNum); //计算信号
//        SaveSignal(PLUSETABLE_START + 7 + MiniFreqCnt);
//    }



	//波形检测
	PulseAcq();
	PulseSave();

    RelayClose(RelayCode);

	//存储其他
	SaveNTempPt = (int *)PLUSETABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F; // 数据头
	*SaveNTempPt++ = PulseCalNum + 20;	// 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;	// 从机标识
	*SaveNTempPt++ = 0x000B;			// 工作模式
	*SaveNTempPt = CenterFreq;  		// 中心频率

	SaveNTempPt = (int *)PLUSETABLE_START + 17;
	*SaveNTempPt++ = CalQValue(CenterFreq, SCANTABLE_START + 8);			// Q值
	*SaveNTempPt++ = 0x294;		// 参考幅值
	*SaveNTempPt = PulseCalNum; // 脉冲采集数据量大小，有效激励点数

	Uint16 CheckSum = 0;
	int i = 0;
	SaveNTempPt = (int *)(PLUSETABLE_START);
	for (; i < PulseCalNum + 20; ++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	PAPSEntry.last_well_mode = 0x000B;

	modeDataSendLen = PulseCalNum + 21;

	//上传数据
	//SciaSendDataNWords(PLUSETABLE_START, PulseCalNum+20);
	return;
}

//激励采集
void PulseAcq(void)
{
	//Select Pulse Channel
	CTRL_CHOICE = 0x2; //控制通路选择，为0扫频、为1刻度、为2激励采集
	DSP_NS_CTRL_EN = USER_ENABLE;
	PLUSE_SCALE_DIS = USER_DISABLE;
	PLUSE_NOISE_DIS = USER_DISABLE;

	RstPulseModule();
	LoadBriDumpPara();
	*(Uint16 *)DDS_FREQ_ADDR = MatFreq;
	LoadDDSPara();
	//Load Pulse acquisition Parameters
	PulseTime = PulseTestPulseTime * FPGA_COUNT;					   //计算发射波形采集时间的FPGA计数值plusetime
	PulseMid1 = (float)1000 / PulseTestAcqFreq;						   //计算采样率倍数的浮点型分频系数pluse_mid1
	PulseMid2 = 1000 / ((Uint16)PulseMid1);							   //计算浮点型采样率倍数pluse_mid2
	PulseNum = (Uint16)((PulseMid2 * (PulseTestPulseTime + 30)) / 10); //计算激励检测采样点数plusenum
	PulseMid4 = 1000 / PulseTestAcqFreq;							   //计算激励采集时钟的分频系数plusedivmid
	PulseDivNum = (PulseMid4 / 2) * 33 + PulseMid4 % 2;				   //转换分频系数为所需格式plusediv

	PLUSE_LCHOICE_DIS = USER_DISABLE;
	PLUSE_DATA = PulseTime; //装载激励检测状态机参数PLUSE_DATA，DSP向FPGA发送激励检测状态机参数plusetime
	PLUSE_LOAD_EN = USER_ENABLE;
	PLUSE_LOAD_DIS = USER_DISABLE;

	PLUSE_LCHOICE_EN = USER_ENABLE;
	PLUSE_DATA = MainDumpTime; //装载激励检测状态机参数PLUSE_DATA，DSP向FPGA发送激励检测状态机参数MainDumpTime
	PLUSE_LOAD_EN = USER_ENABLE;
	PLUSE_LOAD_DIS = USER_DISABLE;

	NRAM_ACQNUM = PulseNum;		  //装载pluse采样点数，DSP向FPGA发送激励采样点数plusenum
	NRAM_DIVNUM = PulseDivNum;	  //装载pluse分频字，DSP向FPGA发送激励采集时钟的分频系数plusediv
	NRAM_LOAD_EN = USER_ENABLE;	  //使能noise_ram相关参数装载信号
	NRAM_LOAD_DIS = USER_DISABLE; //清零noise_ram相关参数装载信号
	//Load Pd Parameter
	Pd90Time = PulseTime;
	//Pd180Time	= PulseTime+10;
	LoadPdPara();
	//Load phase
	POSI_NEGE_EN = USER_ENABLE;

	ACQCLK_EN = USER_ENABLE;	  //使能ACQ采集时钟输出控制信号
	PLUSE_START_EN = USER_ENABLE; //使能激励检测状态机启动信号

	CycleFlag = SET;
	do
	{
		;
	} while (CycleFlag == SET);
	return;
}

//发射信号波形采集检测激励存储函数
void PulseSave(void) // 发射信号波形采集检测激励存储函数
{
	PulseGain = MatFreq/10 - 500; //计算增益补偿参数gn，当前激励信号频率对应一个gn即gn = sfrq – gainstart，由gn查增益数组plusegain[gn]得到当前激励信号的衰减倍数，用于反推激励幅值
	if (PulseGain < 0)
	{
		PulseGain = 0;
	}
	else if (PulseGain > 500)
	{
		PulseGain = 500;
	}

	PulseGainIQ = _IQ(PulseGainAry[PulseGain]); //根据gn读取当前激励信号的衰减倍数pgain并转化为Q格式

	NRAM_RST_EN = USER_ENABLE;										   //使能noise_ram读复位信号
	NRAM_RST_DIS = USER_DISABLE;									   //清零noise_ram读复位信号
	NRAM_RD_EN = USER_ENABLE;										   //使能noise_ram读控制信号
	for (PulseDataCnt = 0; PulseDataCnt < PLUSE_STRIP; PulseDataCnt++) //已读取数据个数<=激励舍去点数？
	{
		StripBuf = READ_NOISE; //从地址READ_NOISE读数据到StripBuf
	}

	PulseCalNum = PulseNum - PLUSE_STRIP;			 //有效激励点数
	PulseSum = 0;									 //清零激励数值的总和PulseSum
	SaveSTempPt = (Uint16 *)(PLUSETABLE_START + 20); //指向幅值地址
	for (PulseDataCnt = 0; PulseDataCnt < PulseCalNum; PulseDataCnt++)
	{
		PulseReadBuf = READ_NOISE;	 //从地址READ_NOISE读数据到plusestrip
		*SaveSTempPt = PulseReadBuf; //从FPGA的noise_ram中依次将采集到的激励数据读到激励检测表的相应位置
		PulseSum += PulseReadBuf;	 //累加得到激励数值的总和PulseSum
		SaveSTempPt++;
	}

	PulseAve = PulseSum / (double)(PulseCalNum);

	SaveSTempPt = (Uint16 *)(PLUSETABLE_START + 20);				   //指向幅值地址
	for (PulseDataCnt = 0; PulseDataCnt < PulseCalNum; PulseDataCnt++) //将激励数值转化为相对均值的偏差，并根据衰减倍数做增益补偿，再存储到原先数值对应的位置
	{
		PulseBuf = *SaveSTempPt;
		PulseRec = (double)PulseBuf - PulseAve;
		PulseRecIQ = _IQmpy(_IQ(PulseRec), PulseGainIQ);
		*SaveSTempPt = _IQint(_IQdiv(PulseRecIQ, _IQ(100)));
		SaveSTempPt++;
	}
	return;
}

/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/
/*-----------------------------------------------------------------------------------------*/
