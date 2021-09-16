/*
 * @Descripttion: ���Ƽ̵���
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-03 17:49:32
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-06 16:19:58
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

// ���㷢��Ƶ�ʺͼ̵���������
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

	RelayCtrlCode_f = RELAY_f_k * TransmitFre + RELAY_f_b;
	// �޷���0-1023
	if (RelayCtrlCode_f < 0)
		RelayCtrlCode = 0;
	else if (RelayCtrlCode_f > 1023)
		RelayCtrlCode = 1023;
	else
		RelayCtrlCode = (Uint16)RelayCtrlCode_f;  // ǿ������ת��
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
