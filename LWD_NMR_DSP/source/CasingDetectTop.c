/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-04-26 14:28:14
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-14 14:49:39
 */
/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

Uint16 CasingMiniNumAry = 5;
Uint16 center_fre;	   	// �ɲ�ֵ�õ�������Ƶ�ʣ���Ҫ�빤��Ƶ�����ֿ���
Uint16 center_fre_amp; 	// ����Ƶ�ʷ�ֵ

#define CASING_DATA_LEN 33

Uint16 getCenterFreq()
{
	return center_fre;
}

Uint16 getCenterFreqAmp()
{
	return center_fre_amp;
}

void CasingDetectTop()
{
	Uint16 Q_value; 			// Qֵ
	
	// ���MiniɨƵ
    int cnt = 0;
    // �̵�������
    RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 11);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// ���MiniɨƵ
	RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 8);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 20);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// ����Qֵ
	Q_value = CalQValue(TransmitFre, CASING_TABLE_START + 20);
	// ��������Ƶ�ʺ͸�ֵ
	CalFreAndAmp(&center_fre, &center_fre_amp);

	// �洢����
	SaveNTempPt = (int *)CASING_TABLE_START;
	*SaveNTempPt++ = REPLY_CASING_F;    // ����ͷ��
	*SaveNTempPt++ = CASING_DATA_LEN;   // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;    // �ӻ���ʶ
	*SaveNTempPt++ = 0x0008;		    // ����ģʽ�洢Ϊ��ɨƵģʽ
	*SaveNTempPt = TransmitFre;	    // ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 29);
	*SaveNTempPt++ = Q_value;			// Qֵ
	*SaveNTempPt++ = 0x294;		   	    // �ο���ֵ
	*SaveNTempPt++ = center_fre;  	    // ����Ƶ��
	*SaveNTempPt = center_fre_amp; 	    // ����Ƶ�ʷ�ֵ

	Uint16 CheckSum = 0;
	SaveNTempPt = (int *)(CASING_TABLE_START);
	int i = 0;
	for (; i < CASING_DATA_LEN; ++i) // CheckSum����ǰ�������ʱ����ȥCheckSum����
	{
		CheckSum += *SaveNTempPt;
		SaveNTempPt++;
	}
	*SaveNTempPt = CheckSum;

	modeDataSendLen = CASING_DATA_LEN + 1;
}

// �����⾮ģʽ֮ǰ��Ҫͨ��ɨƵ���ж������Ƿ����׹��У���δʹ��
int CasingDetectOnce()
{
	// ���MiniɨƵ
    int cnt = 0;
	for (cnt=0;cnt<5;++cnt)
	{
	    // �̵�������
	    RelayOpen(RelayCtrlCode);
		MiniScan(TransmitFre, MINITABLE_START+10+12*cnt, MINITABLE_START+1+12*cnt);
		RelayClose(RelayCtrlCode);
	}
	// ��ʱ�������������ڴ˴�
	SaveNTempPt	= (int *)(CASING_TABLE_START+4);
	SaveSTempPt	= (Uint16 *)(CASING_TABLE_START+10);
	StoreMiniAryPt	= &CasingMiniNumAry;
	StoreMini(1,SaveNTempPt,SaveSTempPt);

	// ��ֵ��������Ƶ�ʼ����ֵ
	MiniFreq = TransmitFre;
	MiniFreq -= ScanDeltaFreq*4;
	for (cnt=0;cnt<9;cnt++)
	{
	    x[cnt] = MiniFreq + ScanDeltaFreq*cnt;
	    y[cnt] = *SaveSTempPt++;
	}

	// ��������Ƶ�ʼ����ֵ
	// ��˹��Ϲ�ʽΪ y=a*e(-((x-b)/c)^2)
	// bΪ��ϳ������ĵ�
	GaussFit(x, y, &a, &b, &c);

	// ��������Ƶ�ʺͷ�ֵ
	center_fre = (Uint16)b;
	center_fre_amp = (Uint16)CublicSplineInterpolation(x, y, b);	// ǿ������ת��

	/*
	// ����Qֵ
	Q_value = (Uint16)(c*Q_FACTOR);
    */

//    if (center_fre_amp <= ParamOrderData.data.AutoAmpThd)   // ��ֵ�쳣
//        return 0;

	// TODO: ��������Ƶ�ʼ����ֵ����Ƶ����ѡ

    return 1;
}

// Ϊ�˷���ʹ�ã���������������д
// ����Qֵ
Uint16 CalQValue(Uint16 CenterFre, Uint32 AmpAddr)
{
    // ��ʼ��
    int cnt = 0;
    MiniFreq = CenterFre;
    MiniFreq -= ScanDeltaFreq * 4;
    SaveSTempPt = (Uint16 *)AmpAddr;
    for (cnt = 0; cnt < 9; cnt++)
    {
        x[cnt] = MiniFreq + ScanDeltaFreq * cnt;
        y[cnt] = *SaveSTempPt++;
    }
    // ��������Ƶ�ʼ����ֵ
    // ��˹��Ϲ�ʽΪ y=a*e(-((x-b)/c)^2)
    // bΪ��ϳ������ĵ㣬aΪ��ֵ
    GaussFit(x, y, &a, &b, &c);
    return (Uint16)(c*Q_FACTOR/b);
}

// ��������Ƶ�ʺͷ�ֵ
void CalFreAndAmp(Uint16 *fre, Uint16* amp)
{
    *fre = (Uint16)b;
    *amp = (Uint16)CublicSplineInterpolation(x, y, b);
}
