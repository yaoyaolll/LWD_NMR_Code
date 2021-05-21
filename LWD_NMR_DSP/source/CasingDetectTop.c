/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

Uint16 CasingMiniNumAry = 5;
Uint16 _centerFreq;		// �ɲ�ֵ�õ�������Ƶ�ʣ���Ҫ�빤��Ƶ�����ֿ���
Uint16 _centerFreqAmp;	// ����Ƶ�ʷ�ֵ

Uint16 getCenterFreq()
{
	return _centerFreq;
}

Uint16 getCenterFreqAmp()
{
	return _centerFreqAmp;
}

void CasingDetectTop()
{
	// ���MiniɨƵ
	int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// ���MiniɨƵ
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	SaveNTempPt	= (int *)(CASING_TABLE_START+7);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+19);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);
	
    // ��ֵ��������Ƶ�ʼ����ֵ������Ƶ��Ϊb����ֵΪa
    MiniFreq -= ScanDeltaFreq*4;
    for (cnt=0;cnt<9;cnt++)
    {
        x[cnt] = MiniFreq + MiniFreqCnt*cnt;
        y[cnt] = *SaveSTempPt++;
    }

    guassFit_C(x, y, &a, &b, &c);
	
	// �洢����
	SaveNTempPt 	= (int *)CASING_TABLE_START;
	*SaveNTempPt++	= REPLY_CASING_F;   // ����ͷ��
	*SaveNTempPt++	= 32;				// ����
	*SaveNTempPt++	= 0x0008;        	// ����ģʽ
	*SaveNTempPt	= CenterFreq * 10;  // ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 28);
	*SaveNTempPt++ = 0;          		// Qֵ
	*SaveNTempPt++ = 0x294;				// �ο���ֵ
	*SaveNTempPt++ = b;					// ����Ƶ��
	*SaveNTempPt   = a;					// ����Ƶ�ʷ�ֵ
	
	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(CASING_TABLE_START);
	int i=0;
	for (;i<32;++i)  // CheckSum����ǰ�������ʱ����ȥCheckSum����
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = 33;
}

// �����⾮ģʽ֮ǰ��Ҫͨ��ɨƵ���ж������Ƿ����׹���
int CasingDetectOnce()
{
	// ���MiniɨƵ
/*	int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
		MiniScan(CenterFreq, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
	}
	// ��ʱ�������������ڴ˴�
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// ��ֵ��������Ƶ�ʼ����ֵ
	MiniFreq -= ScanDeltaFreq*4;
	for (cnt=0;cnt<9;cnt++)
	{
	    x[cnt] = MiniFreq + MiniFreqCnt*cnt;
	    y[cnt] = *SaveSTempPt++;
	}
	guassFit_C(x, y, &a, &b, &c);*/

	// ��������Ƶ�ʼ����ֵ����Ƶ����ѡ

	return 1;
}

