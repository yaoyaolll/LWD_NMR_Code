/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

void ScanModeTop(void)        
{      
    K1_DIS = USER_DISABLE;   //ʹ���ܶ̽ӶϿ��ź�
    K2_DIS = USER_DISABLE;
    HVState = HV_OFF;

	NTimeDec	= (ScaleTe*50-90)*FPGA_COUNT;//���������ɼ�״̬������NTimeDec��NTimeDecΪDECOUPLE�嵼ͨ�ȶ�����ʱ���FPGA����ֵ
	STimeDec	= (ScaleTe*50-90)*FPGA_COUNT;
              	      
	for (BandCnt=1;BandCnt<BAND_NUM;BandCnt++)//ɨƵ��1-8
	{
		RELAY_ON_CLOSE = RelayAry[BandCnt];   //Ƶ��1�̵����պ�
		Delay(120);       //��ʱʹ�պ��ȶ�
		RELAY_ON_CLOSE = 0x0000;//����պ��ź�
     
		//Scan Band Once
		MiniFreq	= FreqAry[BandCnt];
		MiniFreq	-= StepFreq*4; 
		for(MiniFreqCnt=0;MiniFreqCnt<9;MiniFreqCnt++)//ĳƵ����ɨƵ����0-8
		{
			FreqScan = MiniFreq + MiniFreqCnt*StepFreq;//����ɨƵƵ��FreqScan�������۹���Ƶ��MiniFreqΪ���ģ�����i-5���Ĳ���Ƶ��STEP_FREQ����Ϊ��ǰ��i��ѭ����Ҫ���õ�ɨƵƵ�ʣ�i=1~8��
			AcqNoise();//�ɼ�����
			CalNoise(); //��������

			SaveNTempPt	= (int *)(SCANTABLE_START+BandCnt*27+MiniFreqCnt*3-18);    //ָ���ֵ��ַ
			*SaveNTempPt	= _IQint(_IQmpy(NoiseAveIQ,_IQ(10)));

			SaveNTempPt++;    //ָ���׼ƫ���ַ
			*SaveNTempPt	= _IQint(_IQmpy(NoiseSqrAveIQ,_IQ(10)));

			SaveNTempPt++;    //ָ�����ƫ���ַ
			*SaveNTempPt	= _IQint(_IQmpy(NoiseMaxValIQ,_IQ(10)));

			*(Uint16 *)DDS_FREQ_ADDR	= FreqScan;
			ScanFreqOnce(); //ɨƵ����
			CalSignal(ScanSignalNum);  //�����ź�

			SaveSTempPt = (Uint16 *)(SCANTABLE_START+216+BandCnt*9+MiniFreqCnt);    //ָ���ֵ��ַ
			*SaveSTempPt = _IQint(_IQmpy(SignalAmpIQ,_IQ(10)));
		}                                   
     
		RELAY_ON_CLOSE = RelayAry[BandCnt]<<8;   //Ƶ��1�̵����Ͽ�
		Delay(120);            
		RELAY_ON_CLOSE = 0x0000;
	}
//�洢8������Ƶ��
     SaveNTempPt 	= (int *)SCANTABLE_START;
	 *SaveNTempPt	= 0x9909;
	 SaveSixFreq();//�洢�õ���8������Ƶ�ʣ�����ָ��SaveNTempPt��ɨƵ�õ���8������Ƶ��F_FREQ[i]�ֱ𴢴浽��SCANTABLE_START+1Ϊ�׵�ַ�Ĵ洢��Ԫ
     SaveNTempPt	= (int *)(SCANTABLE_START+297);//����ָ��ָ��ο��̶��źŷ�ֵ��ַ��ͨѶЭ��涨��
     *SaveNTempPt	= 0x294;//����ο��̶��źŷ�ֵ
//�ϴ����� 
    McbspSendData(SCANTABLE_START,298);
	return;
}


