/*
 * @Descripttion: 控制继电器
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-06-03 17:49:32
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-12-17 00:07:55
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
// TODO: 确定TransmitFre的单位

Uint16 CalRelayFromFre(Uint16 TransmitFre)
{
    // 计算继电器码
    float rca0;
    float rca1;
    float rca2;
    float frequency = TransmitFre / 10.0;

    rca0 = type_transform(TuningTableEntry->rca0[0], TuningTableEntry->rca0[1]);
    rca1 = type_transform(TuningTableEntry->rca1[0], TuningTableEntry->rca1[1]);
    rca2 = type_transform(TuningTableEntry->rca2[0], TuningTableEntry->rca2[1]);

	// 二次项拟合公式，根据刻度参数表下发参数来计算
    RelayCtrlCode_f = rca0 + rca1*frequency + rca2*frequency*frequency;

	// 目前只使用了8个继电器，需要时再扩增
	// 限幅到0~255
	if (RelayCtrlCode_f < 0)
		return 0;
	else if (RelayCtrlCode_f > 255)
		return 255;
	else
		return (Uint16)(RelayCtrlCode_f + 0.5);  // 强制类型转换
}



/* 继电器为常开开关 */
// 产生使继电器闭合的正脉冲，脉冲宽度为970us
void RelayOpen(Uint16 relay_code)
{
    RELAY_CLOSE = relay_code;   // 继电器断开
    Delay(120);
    RELAY_CLOSE = 0;
}

// 产生使继电器断开的正脉冲，，脉冲宽度为970us
void RelayClose(Uint16 relay_code)
{
    RELAY_ON = relay_code;  // 继电器闭合
    Delay(120);
    RELAY_ON = 0;
}
