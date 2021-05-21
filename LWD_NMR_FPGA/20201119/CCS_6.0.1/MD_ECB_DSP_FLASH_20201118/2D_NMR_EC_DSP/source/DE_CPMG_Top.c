/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(DeCpmgTop,"Datatable");

void DeCpmgTop(void)       //��TE��TW������
{      
	Ne			= DCNe;
	ScaleM		= DCm;
	ScaleMn		= DCMn;
	RELAY_ON_CLOSE = RelayAry[DCFreqSel];   //�̵����պ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000;      

	MiniScan(FreqAry[DCFreqSel],DECPMGTABLE_START+2*Ne+15,DECPMGTABLE_START+2*Ne+5);

	Tes	= (Uint32)100 * DCTes * FPGA_COUNT;        //��TEֵ
	Tel	= Tes;//��SINGLE_TEת��Ϊ10ns��λ��FPGA����ֵ
	Pulse90StoreAddr	= DECPMGTABLE_START+2*Ne+18;//����90������ķ�ֵ��ַpluse90addr
	PulseF180StoreAddr	= DECPMGTABLE_START+2*Ne+19;//�����׸�180������ķ�ֵ��ַpluse180addr1
	PulseL180StoreAddr	= DECPMGTABLE_START+2*Ne+20;//����ĩ��180������ķ�ֵ��ַpluse180addr2
	EchoStorAddr		= DECPMGTABLE_START+5;//����ز����ݵ��׵�ַechostraddr
	InverseTurnFlag	= SET;	
	DCWorkOnce(DCFreqSel);//����һ��

	RELAY_ON_CLOSE = RelayAry[DCFreqSel]<<8;   //�̵����Ͽ�
	Delay(120);                       
	RELAY_ON_CLOSE = 0x0000; 
		
	StartS1msModule(1000);//��ʱ
//�洢 
	SaveNTempPt	= (int *)(DECPMGTABLE_START);//���ݴ洢ָ��ָ��TETW���׵�ַ
	*SaveNTempPt= 0x9901;
	SaveNTempPt++;
	*SaveNTempPt= DCTes;//�洢��TETW���TEֵ
	SaveNTempPt++;
	*SaveNTempPt= Ne;//�洢��TETW���NEֵ
	SaveNTempPt++;
	*SaveNTempPt= DCFreqSel;//�洢��TETW��Ƶ��ѡ����DCFreqSel
	SaveNTempPt++;
	SavePhaseWord();//�洢����������λ
	SaveNTempPt = (int *)(DECPMGTABLE_START+14+2*Ne);//�洢�ο��̶��źŷ�ֵ
	*SaveNTempPt= 0x294;
		//�ϴ�����
	McbspSendData(DECPMGTABLE_START,2*Ne+21);		  	     
	ChangePhase();//ȡ������������λ
	return;       
}

interrupt void XINT2_DCStorData(void)
{
    StoreCnt++;    //�жϼ���StoreCnt��1
    if(StoreCnt==1)//90�㼤���ɼ��жϣ�
	{
		CalSignal(Acq90Num);//�����ź�
		SavePulse(Pulse90StoreAddr);//�洢90���źŵ��̶ȱ���Ӧ��ַ
    }
    else if(StoreCnt==2||StoreCnt==2+Ne)//180�㼤���ɼ��жϣ�
	{
		CalSignal(Acq180Num);     //�����ź�
		if(StoreCnt==2)//��һ��180�㼤���ɼ��жϣ�
		{
			SavePulse(PulseF180StoreAddr);//�洢��һ��180���źŵ��̶ȱ���Ӧ��ַ
		}
		else
		{
			SavePulse(PulseL180StoreAddr);//�洢���һ��180���źŵ��̶ȱ���Ӧ��ַ
		}
	}
	else if(StoreCnt<=Ne+3 && StoreCnt>2)//�ز��ɼ��жϣ�
    {
		if (StoreCnt==4)
		{
			DUMP_SUSTAIN_DIS= USER_DISABLE;
			DumpSustainFlag	= CLEAR;
		}
		CalSignal(EchoAcqNum);    // �����ź�
		if (StoreCnt==Ne+3)
		{
			SaveEcho(EchoStorAddr+2*StoreCnt-8);//�洢���һ���ز��źŵ��̶ȱ���Ӧ��ַ
		}
		else//ǰne-1���ز��ɼ��жϣ�
		{
			SaveEcho(EchoStorAddr+2*StoreCnt-6);//�洢ǰne-1���ز��źŵ��̶ȱ���Ӧ��ַ
		}
		      
	}
	IER|=M_INT1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;//���PIE����1���ж�Ӧ��λ
	EINT;
	return;
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/ 

