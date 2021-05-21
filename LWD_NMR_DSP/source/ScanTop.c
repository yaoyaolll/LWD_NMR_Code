/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#define SCAN_MODE_DATA_FRAME_LEN 43

void ScanModeTop(void)        
{      
    K1_DIS = USER_DISABLE;   // ���ܶ̽ӶϿ��ź�
    K2_DIS = USER_DISABLE;
    HVState = HV_OFF;

	NTimeDec	= (Calib_TE*50-90)*FPGA_COUNT;//���������ɼ�״̬������NTimeDec��NTimeDecΪDECOUPLE�嵼ͨ�ȶ�����ʱ���FPGA����ֵ
	STimeDec	= (Calib_TE*50-90)*FPGA_COUNT;

	// ��ʱ���ü̵����˿�Ϊ1
	RELAY_ON_CLOSE = RelayAry[1];   //Ƶ��1�̵����պ�
	Delay(120);       				//��ʱʹ�պ��ȶ�
	RELAY_ON_CLOSE = 0x0000;		//����պ��ź�

	//Scan Band Once
	MiniFreq	= CenterFreq;
	MiniFreq	-= ScanDeltaFreq*4;
	for(MiniFreqCnt=0;MiniFreqCnt<9;MiniFreqCnt++)//ĳƵ����ɨƵ����0-8
	{
		FreqScan = MiniFreq + MiniFreqCnt*ScanDeltaFreq; //����ɨƵƵ��FreqScan�������۹���Ƶ��MiniFreqΪ���ģ�����i-5���Ĳ���Ƶ��ScanDeltaFreq
		AcqNoise();//�ɼ�����
		CalNoise(); //��������

		SaveNTempPt	= (int *)(SCANTABLE_START + MiniFreqCnt*3 + 4);    //ָ���ֵ��ַ
		*SaveNTempPt	= _IQint(_IQmpy(NoiseAveIQ,_IQ(10)));

		SaveNTempPt++;    //ָ���׼ƫ���ַ
		*SaveNTempPt	= _IQint(_IQmpy(NoiseSqrAveIQ,_IQ(10)));

		SaveNTempPt++;    //ָ�����ƫ���ַ
		*SaveNTempPt	= _IQint(_IQmpy(NoiseMaxValIQ,_IQ(10)));

		*(Uint16 *)DDS_FREQ_ADDR	= FreqScan;
		ScanFreqOnce(); //ɨƵ����
		CalSignal(ScanSignalNum);  //�����ź�
		SaveSignal(SCANTABLE_START + MiniFreqCnt + 31);
	}

	RELAY_ON_CLOSE = RelayAry[1]<<8;   //Ƶ��1�̵����Ͽ�
	Delay(120);
	RELAY_ON_CLOSE = 0x0000;


	//�洢8������Ƶ��
	SaveNTempPt 	= (int *)SCANTABLE_START;
	*SaveNTempPt++	= 0x9995;        	// ����ͷ��
	*SaveNTempPt++	= 42;				// ����
	*SaveNTempPt++	= 0x0008;        	// ����ģʽ
	*SaveNTempPt	= CenterFreq * 10;  // ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(SCANTABLE_START + 40);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(SCANTABLE_START);
	int i=0;
	for (;i<SCAN_MODE_DATA_FRAME_LEN-1;++i)  // CheckSum����ǰ�������ʱ����ȥCheckSum����
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = SCAN_MODE_DATA_FRAME_LEN;
	
     //�ϴ�����
	//SciaSendDataNWords(SCANTABLE_START, SCAN_MODE_DATA_FRAME_LEN);  
	return;
}


