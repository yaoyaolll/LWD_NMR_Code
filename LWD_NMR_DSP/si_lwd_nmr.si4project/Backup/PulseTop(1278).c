/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"


//pluse���βɼ����������
void PulseTop(void)       //���μ��������
{    
	MatFreq		= CenterFreq;
	PhaseFlag	= POSITIVE;

	RELAY_ON_CLOSE = RelayAry[1];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;  

	//mini scan and pulse acquisition
	MiniScan(MatFreq, PLUSETABLE_START+3, PLUSETABLE_START+6);//miniɨƵ

	//���μ��
	PulseAcq();
	PulseSave();
  
	RELAY_ON_CLOSE = RelayAry[1]<<8;   
	Delay(100);                       
	RELAY_ON_CLOSE = 0x0000; 

	//�洢����
	SaveNTempPt	= (int *)PLUSETABLE_START;
	*SaveNTempPt= 0x9995;   // ����ͷ
	SaveNTempPt++;
	*SaveNTempPt = 0x000B;  // ����ģʽ
	SaveNTempPt++;
	*SaveNTempPt = CenterFreq;  // ����Ƶ��

	SaveNTempPt = (int *)PLUSETABLE_START + 15;
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt = PulseCalNum;			// ����ɼ���������С����Ч��������

	Uint16 CheckSum = 0;
	int i=0;
	SaveNTempPt = (int *)(PLUSETABLE_START);
	for (;i<PulseCalNum+19;++i)
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	//�ϴ�����
	SciaSendDataNWords(DECPMGTABLE_START, PulseCalNum+19);
	return;
}

//�����ɼ�
void PulseAcq(void)
{	 
	//Select Pulse Channel
	CTRL_CHOICE		= 0x2;  //����ͨ·ѡ��Ϊ0ɨƵ��Ϊ1�̶ȡ�Ϊ2�����ɼ�
	DSP_NS_CTRL_EN	= USER_ENABLE;
	PLUSE_SCALE_DIS	= USER_DISABLE;
	PLUSE_NOISE_DIS	= USER_DISABLE;

	RstPulseModule();	
	LoadBriDumpPara();	
	*(Uint16 *)DDS_FREQ_ADDR	= MatFreq;
	LoadDDSPara();        
    //Load Pulse acquisition Parameters
	PulseTime	= PulseTestPulseTime * FPGA_COUNT;         //���㷢�䲨�βɼ�ʱ���FPGA����ֵplusetime
	PulseMid1	= (float)1000/PulseTestAcqFreq; //��������ʱ����ĸ����ͷ�Ƶϵ��pluse_mid1
	PulseMid2	= 1000/((Uint16)PulseMid1);     //���㸡���Ͳ����ʱ���pluse_mid2
	PulseNum	= (Uint16)((PulseMid2 * (PulseTestPulseTime+30))/10);//���㼤������������plusenum
	PulseMid4	= 1000/PulseTestAcqFreq;        //���㼤���ɼ�ʱ�ӵķ�Ƶϵ��plusedivmid
	PulseDivNum	= (PulseMid4/2)*33 + PulseMid4%2;	//ת����Ƶϵ��Ϊ�����ʽplusediv
	
	PLUSE_LCHOICE_DIS	= USER_DISABLE;
	PLUSE_DATA			= PulseTime; //װ�ؼ������״̬������PLUSE_DATA��DSP��FPGA���ͼ������״̬������plusetime
	PLUSE_LOAD_EN		= USER_ENABLE;
	PLUSE_LOAD_DIS		= USER_DISABLE; 

	PLUSE_LCHOICE_EN	= USER_ENABLE;
	PLUSE_DATA			= MainDumpTime; //װ�ؼ������״̬������PLUSE_DATA��DSP��FPGA���ͼ������״̬������MainDumpTime
	PLUSE_LOAD_EN		= USER_ENABLE;
	PLUSE_LOAD_DIS		= USER_DISABLE;

	NRAM_ACQNUM		= PulseNum;    //װ��pluse����������DSP��FPGA���ͼ�����������plusenum
	NRAM_DIVNUM		= PulseDivNum; //װ��pluse��Ƶ�֣�DSP��FPGA���ͼ����ɼ�ʱ�ӵķ�Ƶϵ��plusediv
	NRAM_LOAD_EN	= USER_ENABLE; //ʹ��noise_ram��ز���װ���ź�
	NRAM_LOAD_DIS	= USER_DISABLE;//����noise_ram��ز���װ���ź�
	//Load Pd Parameter
	Pd90Time	= PulseTime;
	//Pd180Time	= PulseTime+10;
    LoadPdPara();
	//Load phase 
	POSI_NEGE_EN	= USER_ENABLE;              

	ACQCLK_EN		= USER_ENABLE;//ʹ��ACQ�ɼ�ʱ����������ź�
	PLUSE_START_EN	= USER_ENABLE;//ʹ�ܼ������״̬�������ź�

	CycleFlag		= SET;               
	do
	{;}while(CycleFlag==SET);	
	return;
}

//�����źŲ��βɼ���⼤���洢����
void PulseSave(void)    // �����źŲ��βɼ���⼤���洢����
{
	PulseGain = MatFreq - 500;//�������油������gn����ǰ�����ź�Ƶ�ʶ�Ӧһ��gn��gn = sfrq �C gainstart����gn����������plusegain[gn]�õ���ǰ�����źŵ�˥�����������ڷ��Ƽ�����ֵ
	if(PulseGain<0)
	{
		PulseGain = 0;
	}
	else if(PulseGain>500)
	{
		PulseGain = 500;
	}
  
	PulseGainIQ = _IQ(PulseGainAry[PulseGain]);//����gn��ȡ��ǰ�����źŵ�˥������pgain��ת��ΪQ��ʽ
   
	NRAM_RST_EN		= USER_ENABLE;//ʹ��noise_ram����λ�ź�
    NRAM_RST_DIS	= USER_DISABLE;//����noise_ram����λ�ź�
    NRAM_RD_EN		= USER_ENABLE;//ʹ��noise_ram�������ź�
	for(PulseDataCnt=0;PulseDataCnt<PLUSE_STRIP;PulseDataCnt++)//�Ѷ�ȡ���ݸ���<=������ȥ������
	{
		StripBuf = READ_NOISE;//�ӵ�ַREAD_NOISE�����ݵ�StripBuf
	}

	PulseCalNum	= PulseNum-PLUSE_STRIP;//��Ч��������
	PulseSum	= 0;//���㼤����ֵ���ܺ�PulseSum
	SaveSTempPt = (Uint16 *)(PLUSETABLE_START+18);    //ָ���ֵ��ַ
	for(PulseDataCnt=0;PulseDataCnt<PulseCalNum;PulseDataCnt++)
	{
		PulseReadBuf	= READ_NOISE;//�ӵ�ַREAD_NOISE�����ݵ�plusestrip
		*SaveSTempPt	= PulseReadBuf;//��FPGA��noise_ram�����ν��ɼ����ļ������ݶ��������������Ӧλ��
		PulseSum		+=PulseReadBuf;//�ۼӵõ�������ֵ���ܺ�PulseSum
		SaveSTempPt++;
	}
   
	PulseAve = PulseSum/(double)(PulseCalNum);
  
	SaveSTempPt = (Uint16 *)(PLUSETABLE_START+18);    //ָ���ֵ��ַ
	for(PulseDataCnt=0;PulseDataCnt<PulseCalNum;PulseDataCnt++)//��������ֵת��Ϊ��Ծ�ֵ��ƫ�������˥�����������油�����ٴ洢��ԭ����ֵ��Ӧ��λ��
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


