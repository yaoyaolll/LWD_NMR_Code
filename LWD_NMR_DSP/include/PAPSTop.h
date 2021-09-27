/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-22 17:03:18
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 11:47:22
 */

#ifndef _PAPSTOP_H_
#define _PAPSTOP_H_

#include "DSP281x_Device.h"

#define PAPS_FIFO_ADDR 0x130000                     // PAPS FIFO地址
#define PAPS_UPDATA_ADDR 0x140000                   // PAPS数据上传指令的回复数据帧首地址
#define PAPS_STORAGE_DATA_ADDR PAPS_UPDATA_ADDR+8   // PAPS数据存储地址
#define PAPS_FIFO_LEN 4             // FIFO深度为16
#define PAPS_FIFO_MASK 0x000F       // FIFO mask，取低四位

typedef struct
{
    Uint16 last_well_mode;      // 记录上一个测井模式字
    Uint16 current_well_mode;   // 记录当前测井模式字

    Uint16 PAPSFIFO_start;      // FIFO头部
    Uint16 PAPSFIFO_end;        // FIFO尾部

    Uint16 STKLEV;                  // 叠加次数

    Uint16 echo_1A_num;             // 1A回波点数
    Uint32 echo_1A_addr;            // 1A回波数据起始地址
    // 在PPDIF模式下，有两轮1C回波，每轮1C回波的重复次数相同
    Uint16 echo_1C_num;             // 1C回波点数
    Uint32 echo_1C_addr1;           // 1C回波点数起始地址1
    Uint32 echo_1C_addr2;           // 1C回波点数起始地址2
    Uint32 echo_1C_nrept;           // 1C回波重复次数
}PAPSEntry_t;

#endif

