/*
 * @Descripttion: 控制继电器
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-03 17:49:32
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 16:06:17
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

// // 温度、频率计算公式
// float CalFreFromTemperature(Uint16 temperature) 
// {
// 	return f_T_k * temperature + f_T_b;
// } 

// 由频率计算出继电器码值
Uint16 CalRelayFromFre(Uint16 TransmitFre)
{
	// 二次项拟合公式，根据刻度参数表下发参数来计算
	RelayCtrlCode_f = TuningTableEntry->rca0 + TuningTableEntry->rca1*TransmitFre + TuningTableEntry->rca2*TransmitFre*TransmitFre;
	// 目前只使用了8个继电器，需要时再扩增
	// 限幅到0~255
	if (RelayCtrlCode_f < 0)
		return 0;
	else if (RelayCtrlCode_f > 255)
		return 255;
	else
		return (Uint16)RelayCtrlCode_f;  // 强制类型转换
}

// 计算发射频率和继电器控制字，更新PAPS值
void ParamUpdate()
{
	TransmitFre_f = f_T_k * ParamOrderData.data.Temperature + f_T_b;
	// 频率限幅
	if (TransmitFre_f < 440)
	    TransmitFre = 440;
	else if (TransmitFre_f > 580)
	    TransmitFre = 580;
	else
	    TransmitFre = (Uint16)TransmitFre_f;

	RelayCtrlCode = CalRelayFromFre(TransmitFre);

	// PAPS叠加次数
	PAPSEntry.STKLEV = ParamOrderData.data.PAPS_STKLEV;
}

// 产生使继电器闭合的正脉冲，脉冲宽度为970us
void RelayOpen(Uint16 relay_code)
{
	RELAY_ON = relay_code;	// 继电器闭合
	Delay(120);
	RELAY_ON = 0;
}

// 产生使继电器断开的正脉冲，，脉冲宽度为970us
void RelayClose(Uint16 relay_code)
{
	RELAY_CLOSE = relay_code;	// 继电器断开
	Delay(120);
	RELAY_CLOSE = 0;
}
