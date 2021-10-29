/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-03-17 13:26:24
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-06-01 09:29:19
 */

/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

int main()
{
	DINT;
	InitAll(); //初始化

	CheckReadTable();

	while (1)
	{
	    // 状态机执行函数
		//(*(eventFunc[EventBoardState]))();
	    DeCpmgTop();
	}
}
