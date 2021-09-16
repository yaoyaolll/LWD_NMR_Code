/*
 * @Descripttion: 调谐刻度模式
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-06 16:02:23
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-14 14:47:32
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

/**
 * @brief ������10���̵�����������10����г���ݡ�
 * ��ĳ���̵����պ�ʱ�����Ӧ�ĵ�г���������߲�����
 * ʵ���ض��Ĺ���Ƶ�ʣ���˸ı�̵����ıպ���ϣ��Ϳ��Ե����ߵĹ���Ƶ�ʡ�
 * �ɼ�ÿ������ʱ����Ҫ�����·�һ�β�����
 * ������г�̶�ģʽ����������λ�����ơ�
 * ���Ҫͨ������Ƶ�ʼ������г�롣                                                                                                                                                   
 */

#define	TUNING_MODE_DATA_LEN 43

void TuningModeTop(void) 
{
	Uint16 Q_value; 			// Qֵ
	
	K1_DIS = USER_DISABLE; // ���ܶ̽ӶϿ��ź�
	K2_DIS = USER_DISABLE;
	HVState = HV_OFF;

	NTimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT; //���������ɼ�״̬������NTimeDec��NTimeDecΪDECOUPLE�嵼ͨ�ȶ�����ʱ���FPGA����ֵ
	STimeDec = (Calib_TE * 50 - 90) * FPGA_COUNT;

	// TODO: RelayCode������Ҫ���⴦��
	// �����̵���
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

	// �رռ̵���
    RelayClose(RelayCode);

	// ����Qֵ
	int cnt = 0;
	MiniFreq = CenterFreq;
	MiniFreq -= ScanDeltaFreq * 4;
	SaveSTempPt = (Uint16 *)SCANTABLE_START + 32;	// ����ɨƵ���ݴ洢����
	for (cnt = 0; cnt < 9; cnt++)
	{
		x[cnt] = MiniFreq + ScanDeltaFreq * cnt;
		y[cnt] = *SaveSTempPt++;
	}

	// ��������Ƶ��
	GaussFit(x,y , &a, &b, &c);

	// ����Qֵ
	Q_value = (Uint16)(c*Q_FACTOR);

	//�洢����
	SaveNTempPt = (int *)SCANTABLE_START;
	*SaveNTempPt++ = REPLY_MODE_DATA_F;		   // ����ͷ��
	*SaveNTempPt++ = TUNING_MODE_DATA_LEN; // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;		   // �ӻ���ʶ
	*SaveNTempPt++ = 0x0007;				   // ����ģʽ
	*SaveNTempPt = CenterFreq * 10;			   // ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(SCANTABLE_START + 41);
	*SaveNTempPt++ = Q_value;		// Qֵ
	*SaveNTempPt++ = 0x294; // �ο���ֵ

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(SCANTABLE_START);
	int i = 0;
	for (; i < TUNING_MODE_DATA_LEN; ++i) // CheckSum����ǰ�������ʱ����ȥCheckSum����
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = TUNING_MODE_DATA_LEN + 1;

	//�ϴ�����
	//SciaSendDataNWords(SCANTABLE_START, SCAN_MODE_DATA_FRAME_LEN);
	return;
}
