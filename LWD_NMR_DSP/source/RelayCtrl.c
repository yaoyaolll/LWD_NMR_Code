/*
 * @Descripttion: ���Ƽ̵���
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-03 17:49:32
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-17 00:07:55
 */

/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// // �¶ȡ�Ƶ�ʼ��㹫ʽ
// float CalFreFromTemperature(Uint16 temperature) 
// {
// 	return f_T_k * temperature + f_T_b;
// } 

// ��Ƶ�ʼ�����̵�����ֵ
// TODO: ȷ��TransmitFre�ĵ�λ

Uint16 CalRelayFromFre(Uint16 TransmitFre)
{
    // ����̵�����
    float rca0;
    float rca1;
    float rca2;
    float frequency = TransmitFre / 10.0;

    rca0 = type_transform(TuningTableEntry->rca0[0], TuningTableEntry->rca0[1]);
    rca1 = type_transform(TuningTableEntry->rca1[0], TuningTableEntry->rca1[1]);
    rca2 = type_transform(TuningTableEntry->rca2[0], TuningTableEntry->rca2[1]);

	// ��������Ϲ�ʽ�����ݿ̶Ȳ������·�����������
    RelayCtrlCode_f = rca0 + rca1*frequency + rca2*frequency*frequency;

	// Ŀǰֻʹ����8���̵�������Ҫʱ������
	// �޷���0~255
	if (RelayCtrlCode_f < 0)
		return 0;
	else if (RelayCtrlCode_f > 255)
		return 255;
	else
		return (Uint16)(RelayCtrlCode_f + 0.5);  // ǿ������ת��
}



/* �̵���Ϊ�������� */
// ����ʹ�̵����պϵ������壬������Ϊ970us
void RelayOpen(Uint16 relay_code)
{
    RELAY_CLOSE = relay_code;   // �̵����Ͽ�
    Delay(120);
    RELAY_CLOSE = 0;
}

// ����ʹ�̵����Ͽ��������壬��������Ϊ970us
void RelayClose(Uint16 relay_code)
{
    RELAY_ON = relay_code;  // �̵����պ�
    Delay(120);
    RELAY_ON = 0;
}
