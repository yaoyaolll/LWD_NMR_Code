/*
 * @Descripttion: ���Ƽ̵���
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-03 17:49:32
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:06:17
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
    Float2Uint16_u rca0;
    Float2Uint16_u rca1;
    Float2Uint16_u rca2;
    float frequency = TransmitFre / 10.0;
    rca0.data[0] = TuningTableEntry->rca0[0];
    rca0.data[1] = TuningTableEntry->rca0[1];
    rca1.data[0] = TuningTableEntry->rca1[0];
    rca1.data[1] = TuningTableEntry->rca1[1];
    rca2.data[0] = TuningTableEntry->rca2[0];
    rca2.data[1] = TuningTableEntry->rca2[1];
	// ��������Ϲ�ʽ�����ݿ̶Ȳ������·�����������
//    TransmitFre = TransmitFre / 10;
    RelayCtrlCode_f = rca0.real_data + rca1.real_data*frequency + rca2.real_data*frequency*frequency;
	// Ŀǰֻʹ����8���̵�������Ҫʱ������
	// �޷���0~255
	if (RelayCtrlCode_f < 0)
		return 0;
	else if (RelayCtrlCode_f > 255)
		return 255;
	else
		return (Uint16)RelayCtrlCode_f;  // ǿ������ת��
}

// ���㷢��Ƶ�ʺͼ̵��������֣�����PAPSֵ
void ParamUpdate()
{
    // �������ذ巢�����¶ȼ��㷢��Ƶ�ʺͼ̵�����
    float temperature = ParamOrderData.data.Temperature / 10.0;
	TransmitFre_f = f_T_k * temperature + f_T_b;
	// Ƶ���޷�
	if (TransmitFre_f < 4400)   // 0.1kHz
	    TransmitFre = 4400;
	else if (TransmitFre_f > 5800)
	    TransmitFre = 5800;
	else
	    TransmitFre = (Uint16)TransmitFre_f;

	RelayCtrlCode = CalRelayFromFre(TransmitFre);

	// PAPS���Ӵ���
	PAPSEntry.STKLEV = ParamOrderData.data.PAPS_STKLEV;
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
