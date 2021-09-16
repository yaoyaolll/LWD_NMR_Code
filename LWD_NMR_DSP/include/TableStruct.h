/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-14 19:40:19
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-14 22:14:35
 */

#ifndef _TABLESTRUCT_H_
#define _TABLESTRUCT_H_

typedef unsigned int    Uint16;


/* ����̶Ȳ�����ṹ�� */
// ��ͷ
typedef struct
{
    Uint16 table_ID; 
    Uint16 table_len;   
    Uint16 rsv_word[2]; 
}TableHead_t;

// ������ʶ
typedef struct
{
    Uint16 tool_ID[5];
}InstuctmentInfo_t;

typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x8057
    TableHead_t table_head;
    InstuctmentInfo_t instruct_info;
    // ��г�̶Ȳ���
    Uint16 relay_time[2];
    Uint16 probe_temp;
    float rca0;
    float rca1;
    float rca2;
    Uint16 noise_amp;
    Uint16 noise_std;
    Uint16 noise_max_amp;
    Uint16 scan_time[2];
    Uint16 probe_temp2;
    Uint16 set_center_freq;
    Uint16 scan_delta_freq;
    Uint16 scan_amp[9];
    Uint16 fit_freq;
    Uint16 fit_freq_amp;
    Uint16 Q_value;
    Uint16 noise_amp2;
    Uint16 noise_std2;
    Uint16 noise_max_amp2;
    // MainCalib
    Uint16 main_cal_time[2];
    Uint16 probe_temp3;
    Uint16 width90_P;
    Uint16 pulse90_amp;
    Uint16 main_cal_E90;
    Uint16 DCHV;
    Uint16 width_90_start;
    Uint16 width_90_step;
    Uint16 width_90_step_num;
    Uint16 power_veriA[2];
    Uint16 power_veriB[2];
    Uint16 power_veriC[2];
    // PoroCalib;
    Uint16 pro_cal_time[2];
    Uint16 probe_temp4;
    Uint16 echo_amp;
    Uint16 T2LM;
    Uint16 PSweep_freq;
    Uint16 PSweep_amp;
    Uint16 PSweep_Q;
    Uint16 PORCal_delta_FRQ;
    Uint16 poro_verif;
    Uint16 noise_verif;
    Uint16 ring_verif;
    // CheckSum
    Uint16 checksum;
}TuningTableEntry_t;


/* �����������ò����� */
typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x80A2
    TableHead_t table_head;
    // ����
    Uint16 time_stamp[2]; 
    Uint16 auto_acq;
    Uint16 auto_acq_Thd;
    Uint16 interval_case_det;
    Uint16 freq_offset_SThd;
    Uint16 log_mode;
    Uint16 heat_Thd;
    Uint16 freq_offset_MThd;
    Uint16 vib1010_Thd;
    Uint16 vib1011_S1Thd;
    Uint16 vib_MoThd;
    Uint16 mstatic_Thd;
    Uint16 mtrip_Thd;
    Uint16 P90_emit_Thd;
    // CheckSum
    Uint16 checksum;
}ConfigTableEntry_t;

// ����̶�ģʽ������


// ����⾮ģʽ������


#endif
