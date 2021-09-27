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

#define PAPS_FIFO_ADDR 0x130000                     // PAPS FIFO��ַ
#define PAPS_UPDATA_ADDR 0x140000                   // PAPS�����ϴ�ָ��Ļظ�����֡�׵�ַ
#define PAPS_STORAGE_DATA_ADDR PAPS_UPDATA_ADDR+8   // PAPS���ݴ洢��ַ
#define PAPS_FIFO_LEN 4             // FIFO���Ϊ16
#define PAPS_FIFO_MASK 0x000F       // FIFO mask��ȡ����λ

typedef struct
{
    Uint16 last_well_mode;      // ��¼��һ���⾮ģʽ��
    Uint16 current_well_mode;   // ��¼��ǰ�⾮ģʽ��

    Uint16 PAPSFIFO_start;      // FIFOͷ��
    Uint16 PAPSFIFO_end;        // FIFOβ��

    Uint16 STKLEV;                  // ���Ӵ���

    Uint16 echo_1A_num;             // 1A�ز�����
    Uint32 echo_1A_addr;            // 1A�ز�������ʼ��ַ
    // ��PPDIFģʽ�£�������1C�ز���ÿ��1C�ز����ظ�������ͬ
    Uint16 echo_1C_num;             // 1C�ز�����
    Uint32 echo_1C_addr1;           // 1C�ز�������ʼ��ַ1
    Uint32 echo_1C_addr2;           // 1C�ز�������ʼ��ַ2
    Uint32 echo_1C_nrept;           // 1C�ز��ظ�����
}PAPSEntry_t;

#endif

