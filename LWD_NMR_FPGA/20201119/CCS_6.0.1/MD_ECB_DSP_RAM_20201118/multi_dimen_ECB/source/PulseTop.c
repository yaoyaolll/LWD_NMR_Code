/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

//pluse波形采集检测主函数
void PulseTop(void)       //波形检测主函数
{    
	MatFreq		= FreqAry[MatFreqSel];
	PhaseFlag	= POSITIVE;
	RELAY_ON_CLOSE = RelayAry[MatFreqSel];   //继电器闭合
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  
//mini scan and pulse acquisition
	MiniScan(MatFreq,PLUSETABLE_START+12,PLUSETABLE_START+2);//mini扫频
//波形检测
	PulseAcq();
	PulseSave();
  
	RELAY_ON_CLOSE = RelayAry[MatFreqSel]<<8;   
	Delay(100);                       
	RELAY_ON_CLOSE = 0x0000; 
//存储其他
	SaveNTempPt	= (int *)PLUSETABLE_START;
	*SaveNTempPt= 0x990C;//存储发射波形频率编号
	SaveNTempPt++;
	*SaveNTempPt= MatFreqSel;//存储参考刻度信号幅值
	SaveNTempPt	= (int *)(PLUSETABLE_START+11);
	*SaveNTempPt= 0x294;  
	SaveNTempPt	= (int *)(PLUSETABLE_START+15);
	*SaveNTempPt= MatAcqFreqTim;  //存储发射波形采样率倍数
	SaveNTempPt++;
	*SaveNTempPt= PulseCalNum;//存储发射信号采样点数
//上传数据 
	McbspSendData(PLUSETABLE_START,17+PulseCalNum); //上传激励检测结果
	return;
}

//激励采集
void PulseAcq(void)
{	 
	//Select Pulse Channel
	CTRL_CHOICE		= 0x2;  //控制通路选择，为0扫频、为1刻度、为2激励采集
	DSP_NS_CTRL_EN	= USER_ENABLE;
	PLUSE_SCALE_DIS	= USER_DISABLE;
	PLUSE_NOISE_DIS	= USER_DISABLE;

	RstPulseModule();	
	LoadBriDumpPara();	
	*(Uint16 *)DDS_FREQ_ADDR	= MatFreq;
	LoadDDSPara();        
    //Load Pulse acquisition Parameters
	PulseTime	= MatTime * FPGA_COUNT;//计算发射波形采集时间的FPGA计数值plusetime
	PulseMid1	= (float)1000/MatAcqFreqTim;//计算采样率倍数的浮点型分频系数pluse_mid1
	PulseMid2	= 1000/((Uint16)PulseMid1);//计算浮点型采样率倍数pluse_mid2
	PulseNum	= (Uint16)((PulseMid2 * (MatTime+30))/10);//计算激励检测采样点数plusenum
	PulseMid4	= 1000/MatAcqFreqTim;//计算激励采集时钟的分频系数plusedivmid
	PulseDivNum	= (PulseMid4/2)*33 + PulseMid4%2;	//转换分频系数为所需格式plusediv
	
	PLUSE_LCHOICE_DIS	= USER_DISABLE;
	PLUSE_DATA			= PulseTime; //装载激励检测状态机参数PLUSE_DATA，DSP向FPGA发送激励检测状态机参数plusetime
	PLUSE_LOAD_EN		= USER_ENABLE;
	PLUSE_LOAD_DIS		= USER_DISABLE; 

	PLUSE_LCHOICE_EN	= USER_ENABLE;
	PLUSE_DATA			= MainDumpTime; //装载激励检测状态机参数PLUSE_DATA，DSP向FPGA发送激励检测状态机参数MainDumpTime
	PLUSE_LOAD_EN		= USER_ENABLE;
	PLUSE_LOAD_DIS		= USER_DISABLE;

	NRAM_ACQNUM		= PulseNum;    //装载pluse采样点数，DSP向FPGA发送激励采样点数plusenum
	NRAM_DIVNUM		= PulseDivNum;    //装载pluse分频字，DSP向FPGA发送激励采集时钟的分频系数plusediv
	NRAM_LOAD_EN	= USER_ENABLE;//使能noise_ram相关参数装载信号
	NRAM_LOAD_DIS	= USER_DISABLE;//清零noise_ram相关参数装载信号
	//Load Pd Parameter
	Pd90Time	= PulseTime;
	//Pd180Time	= PulseTime+10;
    LoadPdPara();
	//Load phase 
	POSI_NEGE_EN	= USER_ENABLE;              

	ACQCLK_EN		= USER_ENABLE;//使能ACQ采集时钟输出控制信号
	PLUSE_START_EN	= USER_ENABLE;//使能激励检测状态机启动信号

	CycleFlag		= SET;               
	do
	{;}while(CycleFlag==SET);	
	return;
}

//发射信号波形采集检测激励存储函数
void PulseSave(void)    // 发射信号波形采集检测激励存储函数
{
	PulseGain = MatFreq - 500;//计算增益补偿参数gn，当前激励信号频率对应一个gn即gn = sfrq – gainstart，由gn查增益数组plusegain[gn]得到当前激励信号的衰减倍数，用于反推激励幅值
	if(PulseGain<0)
	{
		PulseGain = 0;
	}
	else if(PulseGain>500)
	{
		PulseGain = 500;
	}
  
	PulseGainIQ = _IQ(PulseGainAry[PulseGain]);//根据gn读取当前激励信号的衰减倍数pgain并转化为Q格式
   
	NRAM_RST_EN		= USER_ENABLE;//使能noise_ram读复位信号
    NRAM_RST_DIS	= USER_DISABLE;//清零noise_ram读复位信号
    NRAM_RD_EN		= USER_ENABLE;//使能noise_ram读控制信号
	for(PulseDataCnt=0;PulseDataCnt<PLUSE_STRIP;PulseDataCnt++)//已读取数据个数<=激励舍去点数？
	{
		StripBuf = READ_NOISE;//从地址READ_NOISE读数据到StripBuf
	}

	PulseCalNum	= PulseNum-PLUSE_STRIP;//有效激励点数
	PulseSum	= 0;//清零激励数值的总和PulseSum
	SaveSTempPt = (Uint16 *)(PLUSETABLE_START+17);    //指向幅值地址    
	for(PulseDataCnt=0;PulseDataCnt<PulseCalNum;PulseDataCnt++)
	{
		PulseReadBuf	= READ_NOISE;//从地址READ_NOISE读数据到plusestrip
		*SaveSTempPt	= PulseReadBuf;//从FPGA的noise_ram中依次将采集到的激励数据读到激励检测表的相应位置
		PulseSum		+=PulseReadBuf;//累加得到激励数值的总和PulseSum
		SaveSTempPt++;
	}
   
	PulseAve = PulseSum/(double)(PulseCalNum);
  
	SaveSTempPt = (Uint16 *)(PLUSETABLE_START+17);    //指向幅值地址
	for(PulseDataCnt=0;PulseDataCnt<PulseCalNum;PulseDataCnt++)//将激励数值转化为相对均值的偏差，并根据衰减倍数做增益补偿，再存储到原先数值对应的位置
	{
		PulseBuf	= *SaveSTempPt;
		PulseRec	= (double)PulseBuf - PulseAve;
		PulseRecIQ	= _IQmpy(_IQ(PulseRec),PulseGainIQ);
		*SaveSTempPt= _IQint(_IQdiv(PulseRecIQ,_IQ(100)));  
		SaveSTempPt++;
	} 
	return;
}

/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  


