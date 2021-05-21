/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

void ScanModeTop(void)        
{      
    K1_DIS = USER_DISABLE;   //使储能短接断开信号
    K2_DIS = USER_DISABLE;
    HVState = HV_OFF;

	NTimeDec	= (ScaleTe*50-90)*FPGA_COUNT;//计算噪声采集状态机参数NTimeDec，NTimeDec为DECOUPLE板导通稳定所需时间的FPGA计数值
	STimeDec	= (ScaleTe*50-90)*FPGA_COUNT;
              	      
	for (BandCnt=1;BandCnt<BAND_NUM;BandCnt++)//扫频带1-8
	{
		RELAY_ON_CLOSE = RelayAry[BandCnt];   //频带1继电器闭合
		Delay(120);       //延时使闭合稳定
		RELAY_ON_CLOSE = 0x0000;//清零闭合信号
     
		//Scan Band Once
		MiniFreq	= FreqAry[BandCnt];
		MiniFreq	-= StepFreq*4; 
		for(MiniFreqCnt=0;MiniFreqCnt<9;MiniFreqCnt++)//某频带已扫频个数0-8
		{
			FreqScan = MiniFreq + MiniFreqCnt*StepFreq;//计算扫频频率FreqScan，以理论工作频率MiniFreq为中心，加上i-5倍的步进频率STEP_FREQ，即为当前第i个循环所要采用的扫频频率（i=1~8）
			AcqNoise();//采集噪声
			CalNoise(); //计算噪声

			SaveNTempPt	= (int *)(SCANTABLE_START+BandCnt*27+MiniFreqCnt*3-18);    //指向均值地址
			*SaveNTempPt	= _IQint(_IQmpy(NoiseAveIQ,_IQ(10)));

			SaveNTempPt++;    //指向标准偏差地址
			*SaveNTempPt	= _IQint(_IQmpy(NoiseSqrAveIQ,_IQ(10)));

			SaveNTempPt++;    //指向最大偏差地址
			*SaveNTempPt	= _IQint(_IQmpy(NoiseMaxValIQ,_IQ(10)));

			*(Uint16 *)DDS_FREQ_ADDR	= FreqScan;
			ScanFreqOnce(); //扫频操作
			CalSignal(ScanSignalNum);  //计算信号

			SaveSTempPt = (Uint16 *)(SCANTABLE_START+216+BandCnt*9+MiniFreqCnt);    //指向幅值地址
			*SaveSTempPt = _IQint(_IQmpy(SignalAmpIQ,_IQ(10)));
		}                                   
     
		RELAY_ON_CLOSE = RelayAry[BandCnt]<<8;   //频带1继电器断开
		Delay(120);            
		RELAY_ON_CLOSE = 0x0000;
	}
//存储8个中心频率
     SaveNTempPt 	= (int *)SCANTABLE_START;
	 *SaveNTempPt	= 0x9909;
	 SaveSixFreq();//存储得到的8个中心频率，利用指针SaveNTempPt将扫频得到的8个中心频率F_FREQ[i]分别储存到以SCANTABLE_START+1为首地址的存储单元
     SaveNTempPt	= (int *)(SCANTABLE_START+297);//数据指针指向参考刻度信号幅值地址（通讯协议规定）
     *SaveNTempPt	= 0x294;//储存参考刻度信号幅值
//上传数据 
    McbspSendData(SCANTABLE_START,298);
	return;
}


