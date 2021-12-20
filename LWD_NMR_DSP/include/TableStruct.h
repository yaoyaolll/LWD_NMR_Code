/*
 * @Descripttion: 
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-14 19:40:19
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-17 20:10:04
 */

#ifndef _TABLESTRUCT_H_
#define _TABLESTRUCT_H_

#include "DSP281x_Device.h"

/* 定义刻度参数表结构体 */
// 表头
typedef struct
{
    Uint16 table_ID; 
    Uint16 table_len;   
    Uint16 rsv_word[2]; 
}TableHead_t;

// 仪器标识
typedef struct
{
    Uint16 tool_ID[5];
}InstuctmentInfo_t;

typedef union
{
    Uint16 data[2];
    float real_data;
}Float2Uint16_u;

typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x8057
    TableHead_t table_head;
    InstuctmentInfo_t instruct_info;
    // 调谐刻度参数
    Uint16 relay_time[2];
    Uint16 probe_temp;
    Uint16 rca0[2];
    Uint16 rca1[2];
    Uint16 rca2[2];
    //float rca0;
    //float rca1;
    //float rca2;
//    Float2Uint16_u rca0;
//    Float2Uint16_u rca1;
//    Float2Uint16_u rca2;
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
    Uint16 PTa0[2];
    Uint16 PTa1[2];
    Uint16 PTa2[2];
    // CheckSum
    Uint16 checksum;
}TuningTableEntry_t;


/* 定义仪器配置参数表，事件板中不使用 */
typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x80A2
    TableHead_t table_head;
    // 参数
    Uint16 time_stamp[2]; 
    Uint16 auto_acq;
    Uint16 auto_amp_Thd;
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

// 定义刻度模式参数表，未使用
typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x8002
    TableHead_t table_head;
    // 刻度参数
    Uint16 mode;
    Uint16 relay_code; 
    Uint16 center_freq;
    Uint16 scan_delta_freq;
    Uint16 noise_acq_time;
    Uint16 noise_acq_freq;
    Uint16 period;
    Uint16 width_90pulse;
    Uint16 angle_90pulse;
    Uint16 echo_acq_period_num;
    Uint16 echo_acq_freq_rate;
    Uint16 echo_acq_window_shift;
    Uint16 calib_TE;
    Uint16 calib_NE;
    Uint16 pulse_test_pulse_time;
    Uint16 pulse_test_acq_freq;
    // checksum
    Uint16 checksum;
}ScaleTableEntry_t;

// 定义测井模式参数表，未使用
typedef struct
{
    Uint16 length;      // length = table_len+2, addr is 0x8018
    TableHead_t table_head;
    // common parameters
    Uint16 mode;
    Uint16 center_freq;
    Uint16 scan_delta_freq;
    Uint16 noise_acq_time;
    Uint16 noise_acq_freq;
    Uint16 angle_180pulse;
    Uint16 echo_acq_period_num;
    Uint16 echo_acq_freq_rate;
    Uint16 echo_acq_window_shift;
    // STWTE
    Uint16 STWTE_Period;
    Uint16 STWTE_TE;
    Uint16 STWTE_NE;
    // PPMODE
    Uint16 PPM_Period; 
    Uint16 PPM_TW_1C;
    Uint16 PPM_TE_1A;
    Uint16 PPM_TE_1C;
    Uint16 PPM_NE_1A;
    Uint16 PPM_NE_1C;
    Uint16 PPM_Nrept_1C;
    // PPDIF
    Uint16 PPDIF_Period;
    Uint16 PPDIF_TW_1C;
    Uint16 PPDIF_TW_1B;
    Uint16 PPDIF_TE_1A1B;
    Uint16 PPDIF_TE_1C;
    Uint16 PPDIF_NE_1A1B;
    Uint16 PPDIF_NE_1C;
    Uint16 PPDIF_Nrept_1C;
    // PPT1
    Uint16 PPT1_Period;
    Uint16 PPT1_TW_1C;
    Uint16 PPT1_TW_Code;
    Uint16 PPT1_TE_1A;
    Uint16 PPT1_TE_1CDEFGH;
    Uint16 PPT1_NE_1A;
    Uint16 PPT1_NE_1C;
    Uint16 PPT1_NE_1DEFGH;
    Uint16 PPT1_Nrept_1C;
    // PPOFTW
    Uint16 PPOFTW_Period;
    Uint16 PPOFTW_TW_1C;
    Uint16 PPOFTW_TW_1D;
    Uint16 PPOFTW_TW_1E;
    Uint16 PPOFTW_TW_1F;
    Uint16 PPOFTW_TW_1G;
    Uint16 PPOFTW_TW_1H;
    Uint16 PPOFTW_TE_1ADEFGH;
    Uint16 PPOFTW_TE_1C;
    Uint16 PPOFTW_Nrept_1C;
    // PPShort
    Uint16 PPShort_Period;
    Uint16 PPShort_TW_1C;
    Uint16 PPShort_TE_1A;
    Uint16 PPShort_TE_1C;
    Uint16 PPShort_NE_1A;
    Uint16 PPShort_NE_1C;
    Uint16 PPShort_Nrept_1C;
    // checksum
    Uint16 checksum;
}WellTableEntry_t;

#endif
