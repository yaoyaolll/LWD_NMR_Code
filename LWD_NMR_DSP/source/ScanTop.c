/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:31:40
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:11:00
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#ifndef DEBUG
#pragma CODE_SECTION(ScanModeTop, "secureRamFuncs");
#endif

#define SCAN_MODE_DATA_FRAME_LEN 43

void ScanModeTop(void)
{
	// ��ģʽ�µļ̵���������·���Ƶ�ʼ���õ�
	RelayCode = CalRelayFromFre(CenterFreq);
	
	K1_DIS = USER_DISABLE; // ���ܶ̽ӶϿ��ź�
	K2_DIS = USER_DISABLE;
	HVState = HV_OFF;

	NTimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT; //���������ɼ�״̬������NTimeDec��NTimeDecΪDECOUPLE�嵼ͨ�ȶ�����ʱ���FPGA����ֵ
	STimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;

    RelayOpen(RelayCode);

	//Scan Band Once
	MiniFreq = CenterFreq;
	MiniFreq -= ScanDeltaFreq * 4;
	for (MiniFreqCnt = 0; MiniFreqCnt < 9; MiniFreqCnt++) //ĳƵ����ɨƵ����0-8
	{
		FreqScan = MiniFreq + MiniFreqCnt * ScanDeltaFreq; //����ɨƵƵ��FreqScan�������۹���Ƶ��MiniFreqΪ���ģ�����i-5���Ĳ���Ƶ��ScanDeltaFreq
		AcqNoise();										   //�ɼ�����
		CalNoise();										   //��������

		SaveNTempPt = (int *)(SCANTABLE_START + MiniFreqCnt * 3 + 5); //ָ���ֵ��ַ
		*SaveNTempPt = _IQint(_IQmpy(NoiseAveIQ, _IQ(10)));

		SaveNTempPt++; //ָ���׼ƫ���ַ
		*SaveNTempPt = _IQint(_IQmpy(NoiseSqrAveIQ, _IQ(10)));

		SaveNTempPt++; //ָ�����ƫ���ַ
		*SaveNTempPt = _IQint(_IQmpy(NoiseMaxValIQ, _IQ(10)));

		*(Uint16 *)DDS_FREQ_ADDR = FreqScan;
		ScanFreqOnce();			  //ɨƵ����
		CalSignal(ScanSignalNum); //�����ź�
		SaveSignal(SCANTABLE_START + MiniFreqCnt + 32);
	}

    RelayClose(RelayCode);

	//�洢8������Ƶ��
	SaveNTempPt = (int *)SCANTABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;		   // ����ͷ��
	*SaveNTempPt++ = SCAN_MODE_DATA_FRAME_LEN; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;		   // �ӻ���ʶ
	*SaveNTempPt++ = 0x0008;				   // ����ģʽ
	*SaveNTempPt = CenterFreq;			   // ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(SCANTABLE_START + 41);
	*SaveNTempPt++ = CalQValue(CenterFreq, SCANTABLE_START + 32);		// Qֵ
	*SaveNTempPt++ = 0x294; // �ο���ֵ

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(SCANTABLE_START);
	int i = 0;
	for (; i < SCAN_MODE_DATA_FRAME_LEN; ++i) // CheckSum����ǰ�������ʱ����ȥCheckSum����
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	PAPSEntry.last_well_mode = 0x0008;

	modeDataSendLen = SCAN_MODE_DATA_FRAME_LEN + 1;

	//�ϴ�����
	//SciaSendDataNWords(SCANTABLE_START, SCAN_MODE_DATA_FRAME_LEN);
	return;
}

