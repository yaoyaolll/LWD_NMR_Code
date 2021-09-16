/*
 * @Descripttion: 璋冭皭鍒诲害妯″紡
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-06 16:02:23
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-14 14:47:32
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

/**
 * @brief 仪器有10个继电器，控制着10个调谐电容。
 * 当某个继电器闭合时，其对应的调谐电容与天线并联，
 * 实现特定的共振频率，因此改变继电器的闭合组合，就可以调天线的共振频率。
 * 采集每组数据时都需要重新下发一次参数表。
 * 整个调谐刻度模式的流程由上位机控制。
 * 最后要通过共振频率计算出调谐码。                                                                                                                                                   
 */

#define	TUNING_MODE_DATA_LEN 43

void TuningModeTop(void) 
{
	Uint16 Q_value; 			// Q值
	
	K1_DIS = USER_DISABLE; // 储能短接断开信号
	K2_DIS = USER_DISABLE;
	HVState = HV_OFF;

	NTimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT; //计算噪声采集状态机参数NTimeDec，NTimeDec为DECOUPLE板导通稳定所需时间的FPGA计数值
	STimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;

	// TODO: RelayCode可能需要特殊处理
	// 开启继电器
    RelayOpen(RelayCode);

	//Scan Band Once
	MiniFreq = CenterFreq;
	MiniFreq -= ScanDeltaFreq * 4;
	for (MiniFreqCnt = 0; MiniFreqCnt < 9; MiniFreqCnt++) //某频带已扫频个数0-8
	{
		FreqScan = MiniFreq + MiniFreqCnt * ScanDeltaFreq; //计算扫频频率FreqScan，以理论工作频率MiniFreq为中心，加上i-5倍的步进频率ScanDeltaFreq
		AcqNoise();										   //采集噪声
		CalNoise();										   //计算噪声

		SaveNTempPt = (int *)(SCANTABLE_START + MiniFreqCnt * 3 + 5); //指向均值地址
		*SaveNTempPt = _IQint(_IQmpy(NoiseAveIQ, _IQ(10)));

		SaveNTempPt++; //指向标准偏差地址
		*SaveNTempPt = _IQint(_IQmpy(NoiseSqrAveIQ, _IQ(10)));

		SaveNTempPt++; //指向最大偏差地址
		*SaveNTempPt = _IQint(_IQmpy(NoiseMaxValIQ, _IQ(10)));

		*(Uint16 *)DDS_FREQ_ADDR = FreqScan;
		ScanFreqOnce();			  //扫频操作
		CalSignal(ScanSignalNum); //计算信号
		SaveSignal(SCANTABLE_START + MiniFreqCnt + 32);
	}

	// 关闭继电器
    RelayClose(RelayCode);

	// 计算Q值
	int cnt = 0;
	MiniFreq = CenterFreq;
	MiniFreq -= ScanDeltaFreq * 4;
	SaveSTempPt = (Uint16 *)SCANTABLE_START + 32;	// 迷你扫频数据存储区域
	for (cnt = 0; cnt < 9; cnt++)
	{
		x[cnt] = MiniFreq + ScanDeltaFreq * cnt;
		y[cnt] = *SaveSTempPt++;
	}

	// 计算中心频率
	GaussFit(x,y , &a, &b, &c);

	// 计算Q值
	Q_value = (Uint16)(c*Q_FACTOR);

	//存储数据
	SaveNTempPt = (int *)SCANTABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;		   // 数据头部
	*SaveNTempPt++ = TUNING_MODE_DATA_LEN; // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;		   // 从机标识
	*SaveNTempPt++ = 0x0007;				   // 工作模式
	*SaveNTempPt = CenterFreq * 10;			   // 中心频率，下发和上传的中心频率单位是0.1kHz

	SaveNTempPt = (int *)(SCANTABLE_START + 41);
	*SaveNTempPt++ = Q_value;		// Q值
	*SaveNTempPt++ = 0x294; // 参考幅值

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(SCANTABLE_START);
	int i = 0;
	for (; i < TUNING_MODE_DATA_LEN; ++i) // CheckSum计算前面的数据时，除去CheckSum本身
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = TUNING_MODE_DATA_LEN + 1;

	//上传数据
	//SciaSendDataNWords(SCANTABLE_START, SCAN_MODE_DATA_FRAME_LEN);
	return;
}
