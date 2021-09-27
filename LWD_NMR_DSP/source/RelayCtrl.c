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
Uint16 CalRelayFromFre(Uint16 TransmitFre)
{
	// ��������Ϲ�ʽ�����ݿ̶Ȳ������·�����������
	RelayCtrlCode_f = TuningTableEntry->rca0 + TuningTableEntry->rca1*TransmitFre + TuningTableEntry->rca2*TransmitFre*TransmitFre;
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
	TransmitFre_f = f_T_k * ParamOrderData.data.Temperature + f_T_b;
	// Ƶ���޷�
	if (TransmitFre_f < 440)
	    TransmitFre = 440;
	else if (TransmitFre_f > 580)
	    TransmitFre = 580;
	else
	    TransmitFre = (Uint16)TransmitFre_f;

	RelayCtrlCode = CalRelayFromFre(TransmitFre);

	// PAPS���Ӵ���
	PAPSEntry.STKLEV = ParamOrderData.data.PAPS_STKLEV;
}

// ����ʹ�̵����պϵ������壬������Ϊ970us
void RelayOpen(Uint16 relay_code)
{
	RELAY_ON = relay_code;	// �̵����պ�
	Delay(120);
	RELAY_ON = 0;
}

// ����ʹ�̵����Ͽ��������壬��������Ϊ970us
void RelayClose(Uint16 relay_code)
{
	RELAY_CLOSE = relay_code;	// �̵����Ͽ�
	Delay(120);
	RELAY_CLOSE = 0;
}
