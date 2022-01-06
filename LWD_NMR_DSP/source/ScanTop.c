/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:31:40
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:11:00
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#ifndef DEBUG
#pragma CODE_SECTION(ScanModeTop, "secureRamFuncs");
#endif

#define SCAN_MODE_DATA_FRAME_LEN 43

void ScanModeTop(void)
{
	// 此模式下的继电器码根据下发的频率计算得到
	RelayCode = CalRelayFromFre(CenterFreq);
	
//    K1_EN = USER_ENABLE;    // K1输出高
//    K2_DIS = USER_DISABLE;  // K2输出低
//	HVState = HV_OFF;

	NTimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT; //计算噪声采集状态机参数NTimeDec，NTimeDec为DECOUPLE板导通稳定所需时间的FPGA计数值
	STimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;

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

    RelayClose(RelayCode);

	//存储8个中心频率
	SaveNTempPt = (int *)SCANTABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;		   // 数据头部
	*SaveNTempPt++ = SCAN_MODE_DATA_FRAME_LEN; // 长度
	*SaveNTempPt++ = EVENT_BOARD_ID;		   // 从机标识
	*SaveNTempPt++ = 0x0008;				   // 工作模式
	*SaveNTempPt = CenterFreq;			   // 工作频率，下发和上传的中心频率单位是0.1kHz

	SaveNTempPt = (int *)(SCANTABLE_START + 41);
	*SaveNTempPt++ = CalQValue(CenterFreq, SCANTABLE_START + 32);		// Q值
	*SaveNTempPt++ = 0x294; // 参考幅值

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(SCANTABLE_START);
	int i = 0;
	for (; i < SCAN_MODE_DATA_FRAME_LEN; ++i) // CheckSum计算前面的数据时，除去CheckSum本身
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	PAPSEntry.last_well_mode = 0x0008;

	modeDataSendLen = SCAN_MODE_DATA_FRAME_LEN + 1;

	//上传数据
	//SciaSendDataNWords(SCANTABLE_START, SCAN_MODE_DATA_FRAME_LEN);
	return;
}

