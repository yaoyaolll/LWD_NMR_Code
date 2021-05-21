//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_McBSP.c
//
// TITLE:	DSP28 Deviec McBSP Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP281x_Device.h"

//---------------------------------------------------------------------------
// InitMcbsp: 
//---------------------------------------------------------------------------
// This function initializes the McBSP to a known state.
//
void InitMcbsp(void)
{
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x3F00;    //  0011 1111 0000 0000 ,����ʹ��MCBSP����ͬʱ����δ���õ�����Ĭ��ΪIO.
	EDIS;

//	����MCBSP�����뷢���ж�
	PieCtrlRegs.PIEIER6.bit.INTx5 = 1;  
	PieCtrlRegs.PIEIER6.bit.INTx6 = 0;
	
// ��MCBSP������Ӧ�Ĵ�������Ӧ������	
	McbspaRegs.SPCR1.bit.RRST = 0;     // ���ڽ��ո�λ
	McbspaRegs.SPCR2.bit.XRST = 0;     //���ڷ��͸�λ
	McbspaRegs.SPCR2.bit.GRST = 0;     // �����ʷ�������λ
	McbspaRegs.SPCR2.bit.FRST = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");

	
	McbspaRegs.SPCR1.all = 0;    //���ڿ��ƼĴ���SPCR1����
	McbspaRegs.XCR1.all = 0x40;  //0-0000000(ÿ������)-010(ÿ��λ��)-00000 ��16λ,���ڷ���������(��λ:��) ÿ��1��,ÿ��16λ
	McbspaRegs.XCR2.all = 0x05;  //0(������λ1)-0000000(������2����)-000(������2����)-00(����ѹ��ģʽ)-1(���������Ե�һ��ͬ�������ͬ��)-01(���������ӳ�1λ)
	McbspaRegs.RCR1.all = 0x40;  //0-0000000(������ÿ������1��)-010(�������ֳ�16λ)-00000
	McbspaRegs.RCR2.all = 0x05;  //0(����λ�����ṹ)-0000000(��2�ĳ���)-000(�������ֳ���)-00(������ѹ��)-1(���������Ե�һ��ͬ�������)-01(��������һλ�ӳ�)
	McbspaRegs.PCR.all = 0x0A00; //���������ڲ�����,���������ⲿ����,�����������ͬ������Ч,����ʱ����������Ч,����ʱ���½�����Ч.
	
	McbspaRegs.SPCR2.bit.GRST = 1;  //�����ʷ������ſ���λ,ʹ�ܲ����ʷ�����
	
	McbspaRegs.SPCR1.bit.RINTM=0;  //�ж���RRDY����
	McbspaRegs.SPCR2.bit.XINTM=0;  //�ж���XRDY����	
	McbspaRegs.SRGR1.all = 0xff04;  //����������,��FSGM=0ʱ��ʧЧ,����ʱ��1M(���25M�ڲ�ʱ������)
	McbspaRegs.SRGR2.all = 0xa000;  // ��DXR��XSR��,����������ͬ��,FSGMλ��ʱΪ0��FPR��FWIDʧЧ.
	McbspaRegs.MFFINT.bit.RINT = 1;  //��FIFOģʽ��ʹ�ܽ����ж�
	
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	
	McbspaRegs.SPCR1.bit.RRST = 1;  //���մ���ʹ��
	McbspaRegs.SPCR2.bit.XRST = 1;  //���䴮��ʹ��
    McbspaRegs.SPCR2.bit.FRST = 1; //ʹ���ڲ������ʷ�����������ͬ������
	asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
	return;
}

unsigned int Mcbsp_TxRdy(void)
{
	if(McbspaRegs.SPCR2.bit.XRDY == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

	
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  

