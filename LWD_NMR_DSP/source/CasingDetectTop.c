/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-04-26 14:28:14
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-27 10:04:08
 */
/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#define CASING_DATA_LEN 36

Uint16 CasingMiniNumAry = 5;

void CasingDetectTop()
{
	Uint16 Q_value1; 			// Qֵ1
	Uint16 center_fre1;	   		// �ɲ�ֵ�õ�������Ƶ��1
	Uint16 center_fre_amp1; 	// ����Ƶ�ʷ�ֵ1
	
	Uint16 Q_value2;			// Qֵ2
	Uint16 center_fre2;			// �ɲ�ֵ�õ�������Ƶ��2
	Uint16 center_fre_amp2;		// ����Ƶ�ʷ�ֵ2
    int cnt = 0;

	// ���MiniɨƵ1
    RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 5);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 8);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// ����Qֵ1������Ƶ��1�Լ�����Ƶ�ʷ�ֵ1
	Q_value1 =  CalQValue(TransmitFre, CASING_TABLE_START + 8);
	CalFreAndAmp(&center_fre1, &center_fre_amp1);

	// ���MiniɨƵ2
	RelayOpen(RelayCtrlCode);
	for (cnt = 0; cnt < 5; ++cnt)
	{
		MiniScan(TransmitFre, MINITABLE_START + 10 + 12 * cnt, MINITABLE_START + 1 + 12 * cnt);
	}
	RelayClose(RelayCtrlCode);
	SaveNTempPt = (int *)(CASING_TABLE_START + 20);
	SaveSTempPt = (Uint16 *)(CASING_TABLE_START + 23);
	StoreMiniAryPt = &CasingMiniNumAry;
	StoreMini(1, SaveNTempPt, SaveSTempPt);

	// ����Qֵ
	Q_value2 = CalQValue(TransmitFre, CASING_TABLE_START + 23);
	// ��������Ƶ�ʺ͸�ֵ
	CalFreAndAmp(&center_fre2, &center_fre_amp2);

	// �洢����
	SaveNTempPt = (int *)CASING_TABLE_START;
	*SaveNTempPt++ = REPLY_CASING_F;    // ����ͷ��
	*SaveNTempPt++ = CASING_DATA_LEN;   // ����
	*SaveNTempPt++ = EVENT_BOARD_ID;    // �ӻ���ʶ
	*SaveNTempPt++ = 0x0008;		    // ����ģʽ�洢Ϊ��ɨƵģʽ
	*SaveNTempPt = TransmitFre;	    	// ����Ƶ�ʣ��·����ϴ�������Ƶ�ʵ�λ��0.1kHz

	SaveNTempPt = (int *)(CASING_TABLE_START + 17);
	*SaveNTempPt++ = Q_value1;			// Qֵ1
	*SaveNTempPt++ = center_fre1;  	    // ����Ƶ��1
	*SaveNTempPt = center_fre_amp1; 	// ����Ƶ�ʷ�ֵ1

	SaveNTempPt = (int *)(CASING_TABLE_START + 32);
	*SaveNTempPt++ = Q_value2;    		// Qֵ2
	*SaveNTempPt++ = center_fre2;		// ����Ƶ��2
	*SaveNTempPt++ = center_fre_amp2;	// ����Ƶ�ʷ�ֵ2
	*SaveNTempPt = 0x294;				// �ο���ֵ

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

// Ϊ�˷���ʹ�ã���������������д
// ����Qֵ
Uint16 CalQValue(Uint16 CenterFre, Uint32 AmpAddr)
{
    // ��ʼ��
    int cnt = 0;
	float res = 0;
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
	res = c*Q_FACTOR/b;
    return (Uint16)res;
}

// ��������Ƶ�ʺͷ�ֵ
void CalFreAndAmp(Uint16 *fre, Uint16* amp)
{
    *fre = (Uint16)b;
    *amp = (Uint16)CublicSplineInterpolation(x, y, b);
}
