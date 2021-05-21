`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module NMR_TOP(
       zcs2,
       xwe,
       ddsfqud,
       ddsreset,
       ddswclk,
       cal_out,
       ddsdata,
       OCX40MHz,
       ddsclkout,
       interupt,
       rt_sw,
       soft_dump,
       sw_acq1,
       sw_acq2,
       dumpon,
       dumpoff,
       Q1Q8,
       Q3Q6,
       Q4Q5,
       Q2Q7,
       calcuinter,
       tri_ctrl,
       sigtimeup,
       k1,
       k2,
       gpio,
       pulse_start,
       pd_pulse_en,
       XRD,
       Acq_clk,
       sd_acq_en,
       s_acq180,
       GLA,
       xa,
       xd,
       relayclose_on,
       ADC
    );
input  zcs2;
input  xwe;
output ddsfqud;
output ddsreset;
output ddswclk;
output cal_out;
output ddsdata;
input  OCX40MHz;
input  ddsclkout;
output interupt;
output rt_sw;
output soft_dump;
output sw_acq1;
output sw_acq2;
output dumpon;
output dumpoff;
output Q1Q8;
output Q3Q6;
output Q4Q5;
output Q2Q7;
output calcuinter;
input  tri_ctrl;
output sigtimeup;
output k1;
output k2;
input  gpio;
output pulse_start;
output pd_pulse_en;
input  XRD;
output Acq_clk;
output sd_acq_en;
output s_acq180;
output GLA;
input  [18:0] xa;
inout  [15:0] xd;
output [15:0] relayclose_on;
input  [11:0] ADC;

    wire bri_div_start_0, bri_dump_sw_0_dumpoff_ctr, 
        bri_dump_sw_0_dump_start, bri_dump_sw_0_off_test, 
        bri_dump_sw_0_phase_ctr, bri_dump_sw_0_reset_out, 
        bri_dump_sw_0_tetw_pluse, bri_dump_sw_0_turn_delay, clk_4f_en, 
        ClockManagement_0_clock_10khz, dds_change_0_dds_conf, 
        dds_change_0_dds_rst, DUMP_0_dump_off, DUMP_0_dump_on, 
        DUMP_OFF_0_dump_off, DUMP_OFF_1_dump_off, DUMP_ON_0_dump_on, 
        GPMI_0_code_en, \GPMI_0_dataout_[15] , \GPMI_0_dataout_[14] , 
        \GPMI_0_dataout_[13] , \GPMI_0_dataout_[12] , 
        \GPMI_0_dataout_[11] , \GPMI_0_dataout_[10] , 
        \GPMI_0_dataout_[9] , \GPMI_0_dataout_[8] , 
        \GPMI_0_dataout_[7] , \GPMI_0_dataout_[6] , 
        \GPMI_0_dataout_[5] , \GPMI_0_dataout_[4] , 
        \GPMI_0_dataout_[3] , \GPMI_0_dataout_[2] , 
        \GPMI_0_dataout_[1] , \GPMI_0_dataout_[0] , net_27, net_33, 
        net_40, net_45, net_51, noisestate_0_dumpoff_ctr, 
        noisestate_0_dumpon_ctr, noisestate_0_n_acq, 
        noisestate_0_rt_sw, noisestate_0_soft_d, 
        noisestate_0_state_over_n, noisestate_0_sw_acq1, 
        noisestate_0_sw_acq2, \noisestate_0_timecount_[19] , 
        \noisestate_0_timecount_[18] , \noisestate_0_timecount_[17] , 
        \noisestate_0_timecount_[16] , \noisestate_0_timecount_[15] , 
        \noisestate_0_timecount_[14] , \noisestate_0_timecount_[13] , 
        \noisestate_0_timecount_[12] , \noisestate_0_timecount_[11] , 
        \noisestate_0_timecount_[10] , \noisestate_0_timecount_[9] , 
        \noisestate_0_timecount_[8] , \noisestate_0_timecount_[7] , 
        \noisestate_0_timecount_[6] , \noisestate_0_timecount_[5] , 
        \noisestate_0_timecount_[4] , \noisestate_0_timecount_[3] , 
        \noisestate_0_timecount_[2] , \noisestate_0_timecount_[1] , 
        \noisestate_0_timecount_[0] , nsctrl_choice_0_dumpoff_ctr, 
        nsctrl_choice_0_dumponoff_rst, nsctrl_choice_0_dumpon_ctr, 
        nsctrl_choice_0_intertodsp, nsctrl_choice_0_rt_sw, 
        nsctrl_choice_0_soft_d, nsctrl_choice_0_sw_acq1, 
        nsctrl_choice_0_sw_acq2, n_acq_change_0_n_acq_start, 
        n_acq_change_0_n_rst_n, OR2_1_Y, OR2_2_Y, 
        plusestate_0_dds_config, plusestate_0_dumpoff_ctr, 
        plusestate_0_dump_start, plusestate_0_off_test, 
        plusestate_0_pluse_acq, plusestate_0_pluse_start, 
        plusestate_0_rt_sw, plusestate_0_soft_d, 
        plusestate_0_state_over_n, plusestate_0_sw_acq1, 
        plusestate_0_sw_acq2, plusestate_0_tetw_pluse, 
        \plusestate_0_timecount_[19] , \plusestate_0_timecount_[18] , 
        \plusestate_0_timecount_[17] , \plusestate_0_timecount_[16] , 
        \plusestate_0_timecount_[15] , \plusestate_0_timecount_[14] , 
        \plusestate_0_timecount_[13] , \plusestate_0_timecount_[12] , 
        \plusestate_0_timecount_[11] , \plusestate_0_timecount_[10] , 
        \plusestate_0_timecount_[9] , \plusestate_0_timecount_[8] , 
        \plusestate_0_timecount_[7] , \plusestate_0_timecount_[6] , 
        \plusestate_0_timecount_[5] , \plusestate_0_timecount_[4] , 
        \plusestate_0_timecount_[3] , \plusestate_0_timecount_[2] , 
        \plusestate_0_timecount_[1] , \plusestate_0_timecount_[0] , 
        PLUSE_0_bri_cycle, rt_sw_net_1, scalestate_0_dds_conf, 
        scalestate_0_dumpoff_ctr, scalestate_0_dump_start, 
        scalestate_0_dump_sustain_ctrl, scalestate_0_load_out, 
        scalestate_0_long_opentime, scalestate_0_ne_le, 
        scalestate_0_off_test, scalestate_0_pluse_start, 
        scalestate_0_pn_out, scalestate_0_rt_sw, scalestate_0_soft_d, 
        scalestate_0_state_over_n, \scalestate_0_strippluse_[11] , 
        \scalestate_0_strippluse_[10] , \scalestate_0_strippluse_[9] , 
        \scalestate_0_strippluse_[8] , \scalestate_0_strippluse_[7] , 
        \scalestate_0_strippluse_[6] , \scalestate_0_strippluse_[5] , 
        \scalestate_0_strippluse_[4] , \scalestate_0_strippluse_[3] , 
        \scalestate_0_strippluse_[2] , \scalestate_0_strippluse_[1] , 
        \scalestate_0_strippluse_[0] , scalestate_0_sw_acq1, 
        scalestate_0_sw_acq2, scalestate_0_s_acq, 
        \scalestate_0_s_acqnum_[15] , \scalestate_0_s_acqnum_[14] , 
        \scalestate_0_s_acqnum_[13] , \scalestate_0_s_acqnum_[12] , 
        \scalestate_0_s_acqnum_[11] , \scalestate_0_s_acqnum_[10] , 
        \scalestate_0_s_acqnum_[9] , \scalestate_0_s_acqnum_[8] , 
        \scalestate_0_s_acqnum_[7] , \scalestate_0_s_acqnum_[6] , 
        \scalestate_0_s_acqnum_[5] , \scalestate_0_s_acqnum_[4] , 
        \scalestate_0_s_acqnum_[3] , \scalestate_0_s_acqnum_[2] , 
        \scalestate_0_s_acqnum_[1] , \scalestate_0_s_acqnum_[0] , 
        scalestate_0_tetw_pluse, \scalestate_0_timecount_[21] , 
        \scalestate_0_timecount_[20] , \scalestate_0_timecount_[19] , 
        \scalestate_0_timecount_[18] , \scalestate_0_timecount_[17] , 
        \scalestate_0_timecount_[16] , \scalestate_0_timecount_[15] , 
        \scalestate_0_timecount_[14] , \scalestate_0_timecount_[13] , 
        \scalestate_0_timecount_[12] , \scalestate_0_timecount_[11] , 
        \scalestate_0_timecount_[10] , \scalestate_0_timecount_[9] , 
        \scalestate_0_timecount_[8] , \scalestate_0_timecount_[7] , 
        \scalestate_0_timecount_[6] , \scalestate_0_timecount_[5] , 
        \scalestate_0_timecount_[4] , \scalestate_0_timecount_[3] , 
        \scalestate_0_timecount_[2] , \scalestate_0_timecount_[1] , 
        \scalestate_0_timecount_[0] , scanstate_0_calctrl, 
        scanstate_0_dds_conf, scanstate_0_dumpoff_ctr, 
        scanstate_0_dumpon_ctr, scanstate_0_rt_sw, scanstate_0_soft_d, 
        scanstate_0_state_over_n, scanstate_0_sw_acq1, 
        scanstate_0_sw_acq2, scanstate_0_s_acq, 
        \scanstate_0_timecount_[19] , \scanstate_0_timecount_[18] , 
        \scanstate_0_timecount_[17] , \scanstate_0_timecount_[16] , 
        \scanstate_0_timecount_[15] , \scanstate_0_timecount_[14] , 
        \scanstate_0_timecount_[13] , \scanstate_0_timecount_[12] , 
        \scanstate_0_timecount_[11] , \scanstate_0_timecount_[10] , 
        \scanstate_0_timecount_[9] , \scanstate_0_timecount_[8] , 
        \scanstate_0_timecount_[7] , \scanstate_0_timecount_[6] , 
        \scanstate_0_timecount_[5] , \scanstate_0_timecount_[4] , 
        \scanstate_0_timecount_[3] , \scanstate_0_timecount_[2] , 
        \scanstate_0_timecount_[1] , \scanstate_0_timecount_[0] , 
        scan_scale_sw_0_s_start, Signal_Noise_Acq_0_acq_clk, 
        \Signal_Noise_Acq_0_dataout_[15] , 
        \Signal_Noise_Acq_0_dataout_[14] , 
        \Signal_Noise_Acq_0_dataout_[13] , 
        \Signal_Noise_Acq_0_dataout_[12] , 
        \Signal_Noise_Acq_0_dataout_[11] , 
        \Signal_Noise_Acq_0_dataout_[10] , 
        \Signal_Noise_Acq_0_dataout_[9] , 
        \Signal_Noise_Acq_0_dataout_[8] , 
        \Signal_Noise_Acq_0_dataout_[7] , 
        \Signal_Noise_Acq_0_dataout_[6] , 
        \Signal_Noise_Acq_0_dataout_[5] , 
        \Signal_Noise_Acq_0_dataout_[4] , 
        \Signal_Noise_Acq_0_dataout_[3] , 
        \Signal_Noise_Acq_0_dataout_[2] , 
        \Signal_Noise_Acq_0_dataout_[1] , 
        \Signal_Noise_Acq_0_dataout_[0] , soft_dump_net_1, 
        state1ms_choice_0_bri_cycle, state1ms_choice_0_dump_start, 
        state1ms_choice_0_reset_out, state_1ms_0_bri_cycle, 
        state_1ms_0_dump_start, state_1ms_0_pluse_start, 
        state_1ms_0_reset_out, state_1ms_0_rt_sw, 
        state_1ms_0_soft_dump, \state_1ms_0_timecount_[19] , 
        \state_1ms_0_timecount_[18] , \state_1ms_0_timecount_[17] , 
        \state_1ms_0_timecount_[16] , \state_1ms_0_timecount_[15] , 
        \state_1ms_0_timecount_[14] , \state_1ms_0_timecount_[13] , 
        \state_1ms_0_timecount_[12] , \state_1ms_0_timecount_[11] , 
        \state_1ms_0_timecount_[10] , \state_1ms_0_timecount_[9] , 
        \state_1ms_0_timecount_[8] , \state_1ms_0_timecount_[7] , 
        \state_1ms_0_timecount_[6] , \state_1ms_0_timecount_[5] , 
        \state_1ms_0_timecount_[4] , \state_1ms_0_timecount_[3] , 
        \state_1ms_0_timecount_[2] , \state_1ms_0_timecount_[1] , 
        \state_1ms_0_timecount_[0] , \s_acq_change_0_s_acqnum_[15] , 
        \s_acq_change_0_s_acqnum_[14] , \s_acq_change_0_s_acqnum_[13] , 
        \s_acq_change_0_s_acqnum_[12] , \s_acq_change_0_s_acqnum_[11] , 
        \s_acq_change_0_s_acqnum_[10] , \s_acq_change_0_s_acqnum_[9] , 
        \s_acq_change_0_s_acqnum_[8] , \s_acq_change_0_s_acqnum_[7] , 
        \s_acq_change_0_s_acqnum_[6] , \s_acq_change_0_s_acqnum_[5] , 
        \s_acq_change_0_s_acqnum_[4] , \s_acq_change_0_s_acqnum_[3] , 
        \s_acq_change_0_s_acqnum_[2] , \s_acq_change_0_s_acqnum_[1] , 
        \s_acq_change_0_s_acqnum_[0] , s_acq_change_0_s_load, 
        s_acq_change_0_s_rst, \s_acq_change_0_s_stripnum_[11] , 
        \s_acq_change_0_s_stripnum_[10] , 
        \s_acq_change_0_s_stripnum_[9] , 
        \s_acq_change_0_s_stripnum_[8] , 
        \s_acq_change_0_s_stripnum_[7] , 
        \s_acq_change_0_s_stripnum_[6] , 
        \s_acq_change_0_s_stripnum_[5] , 
        \s_acq_change_0_s_stripnum_[4] , 
        \s_acq_change_0_s_stripnum_[3] , 
        \s_acq_change_0_s_stripnum_[2] , 
        \s_acq_change_0_s_stripnum_[1] , 
        \s_acq_change_0_s_stripnum_[0] , timer_top_0_clk_en_noise, 
        timer_top_0_clk_en_pluse, timer_top_0_clk_en_scale, 
        timer_top_0_clk_en_scan, timer_top_0_clk_en_st1ms, 
        top_code_0_acqclken, top_code_0_bridge_load, 
        \top_code_0_bri_datain_[15] , \top_code_0_bri_datain_[14] , 
        \top_code_0_bri_datain_[13] , \top_code_0_bri_datain_[12] , 
        \top_code_0_bri_datain_[11] , \top_code_0_bri_datain_[10] , 
        \top_code_0_bri_datain_[9] , \top_code_0_bri_datain_[8] , 
        \top_code_0_bri_datain_[7] , \top_code_0_bri_datain_[6] , 
        \top_code_0_bri_datain_[5] , \top_code_0_bri_datain_[4] , 
        \top_code_0_bri_datain_[3] , \top_code_0_bri_datain_[2] , 
        \top_code_0_bri_datain_[1] , \top_code_0_bri_datain_[0] , 
        \top_code_0_cal_data_[5] , \top_code_0_cal_data_[4] , 
        \top_code_0_cal_data_[3] , \top_code_0_cal_data_[2] , 
        \top_code_0_cal_data_[1] , \top_code_0_cal_data_[0] , 
        top_code_0_cal_load, \top_code_0_change_[1] , 
        \top_code_0_change_[0] , top_code_0_dds_choice, 
        \top_code_0_dds_configdata_[15] , 
        \top_code_0_dds_configdata_[14] , 
        \top_code_0_dds_configdata_[13] , 
        \top_code_0_dds_configdata_[12] , 
        \top_code_0_dds_configdata_[11] , 
        \top_code_0_dds_configdata_[10] , 
        \top_code_0_dds_configdata_[9] , 
        \top_code_0_dds_configdata_[8] , 
        \top_code_0_dds_configdata_[7] , 
        \top_code_0_dds_configdata_[6] , 
        \top_code_0_dds_configdata_[5] , 
        \top_code_0_dds_configdata_[4] , 
        \top_code_0_dds_configdata_[3] , 
        \top_code_0_dds_configdata_[2] , 
        \top_code_0_dds_configdata_[1] , 
        \top_code_0_dds_configdata_[0] , top_code_0_dds_load, 
        \top_code_0_dumpdata_0_[11] , \top_code_0_dumpdata_0_[10] , 
        \top_code_0_dumpdata_0_[9] , \top_code_0_dumpdata_0_[8] , 
        \top_code_0_dumpdata_0_[7] , \top_code_0_dumpdata_0_[6] , 
        \top_code_0_dumpdata_0_[5] , \top_code_0_dumpdata_0_[4] , 
        \top_code_0_dumpdata_0_[3] , \top_code_0_dumpdata_0_[2] , 
        \top_code_0_dumpdata_0_[1] , \top_code_0_dumpdata_0_[0] , 
        top_code_0_dumpload, \top_code_0_dump_cho_0_[2] , 
        \top_code_0_dump_cho_0_[1] , \top_code_0_dump_cho_0_[0] , 
        top_code_0_dump_sustain, \top_code_0_dump_sustain_data_[3] , 
        \top_code_0_dump_sustain_data_[2] , 
        \top_code_0_dump_sustain_data_[1] , 
        \top_code_0_dump_sustain_data_[0] , 
        \top_code_0_halfdata_0_[7] , \top_code_0_halfdata_0_[6] , 
        \top_code_0_halfdata_0_[5] , \top_code_0_halfdata_0_[4] , 
        \top_code_0_halfdata_0_[3] , \top_code_0_halfdata_0_[2] , 
        \top_code_0_halfdata_0_[1] , \top_code_0_halfdata_0_[0] , 
        top_code_0_inv_turn, \top_code_0_noisedata_[15] , 
        \top_code_0_noisedata_[14] , \top_code_0_noisedata_[13] , 
        \top_code_0_noisedata_[12] , \top_code_0_noisedata_[11] , 
        \top_code_0_noisedata_[10] , \top_code_0_noisedata_[9] , 
        \top_code_0_noisedata_[8] , \top_code_0_noisedata_[7] , 
        \top_code_0_noisedata_[6] , \top_code_0_noisedata_[5] , 
        \top_code_0_noisedata_[4] , \top_code_0_noisedata_[3] , 
        \top_code_0_noisedata_[2] , \top_code_0_noisedata_[1] , 
        \top_code_0_noisedata_[0] , top_code_0_noise_rst, 
        top_code_0_noise_start, top_code_0_nstatechoice, 
        top_code_0_nstateload, \top_code_0_n_acqnum_2_[11] , 
        \top_code_0_n_acqnum_2_[10] , \top_code_0_n_acqnum_2_[9] , 
        \top_code_0_n_acqnum_2_[8] , \top_code_0_n_acqnum_2_[7] , 
        \top_code_0_n_acqnum_2_[6] , \top_code_0_n_acqnum_2_[5] , 
        \top_code_0_n_acqnum_2_[4] , \top_code_0_n_acqnum_2_[3] , 
        \top_code_0_n_acqnum_2_[2] , \top_code_0_n_acqnum_2_[1] , 
        \top_code_0_n_acqnum_2_[0] , \top_code_0_n_divnum_0_[9] , 
        \top_code_0_n_divnum_0_[8] , \top_code_0_n_divnum_0_[7] , 
        \top_code_0_n_divnum_0_[6] , \top_code_0_n_divnum_0_[5] , 
        \top_code_0_n_divnum_0_[4] , \top_code_0_n_divnum_0_[3] , 
        \top_code_0_n_divnum_0_[2] , \top_code_0_n_divnum_0_[1] , 
        \top_code_0_n_divnum_0_[0] , top_code_0_n_load, 
        top_code_0_n_rd_en, top_code_0_n_s_ctrl, 
        \top_code_0_pd_pluse_choice_[3] , 
        \top_code_0_pd_pluse_choice_[2] , 
        \top_code_0_pd_pluse_choice_[1] , 
        \top_code_0_pd_pluse_choice_[0] , 
        \top_code_0_pd_pluse_data_[15] , 
        \top_code_0_pd_pluse_data_[14] , 
        \top_code_0_pd_pluse_data_[13] , 
        \top_code_0_pd_pluse_data_[12] , 
        \top_code_0_pd_pluse_data_[11] , 
        \top_code_0_pd_pluse_data_[10] , 
        \top_code_0_pd_pluse_data_[9] , \top_code_0_pd_pluse_data_[8] , 
        \top_code_0_pd_pluse_data_[7] , \top_code_0_pd_pluse_data_[6] , 
        \top_code_0_pd_pluse_data_[5] , \top_code_0_pd_pluse_data_[4] , 
        \top_code_0_pd_pluse_data_[3] , \top_code_0_pd_pluse_data_[2] , 
        \top_code_0_pd_pluse_data_[1] , \top_code_0_pd_pluse_data_[0] , 
        top_code_0_pd_pluse_load, \top_code_0_plusedata_[15] , 
        \top_code_0_plusedata_[14] , \top_code_0_plusedata_[13] , 
        \top_code_0_plusedata_[12] , \top_code_0_plusedata_[11] , 
        \top_code_0_plusedata_[10] , \top_code_0_plusedata_[9] , 
        \top_code_0_plusedata_[8] , \top_code_0_plusedata_[7] , 
        \top_code_0_plusedata_[6] , \top_code_0_plusedata_[5] , 
        \top_code_0_plusedata_[4] , \top_code_0_plusedata_[3] , 
        \top_code_0_plusedata_[2] , \top_code_0_plusedata_[1] , 
        \top_code_0_plusedata_[0] , top_code_0_pluseload, 
        top_code_0_pluse_lc, top_code_0_pluse_noise_ctrl, 
        top_code_0_pluse_rst, top_code_0_pluse_scale, 
        top_code_0_pluse_str, top_code_0_pn_change, 
        top_code_0_RAM_Rd_rst, \top_code_0_scalechoice_0_[4] , 
        \top_code_0_scalechoice_0_[3] , \top_code_0_scalechoice_0_[2] , 
        \top_code_0_scalechoice_0_[1] , \top_code_0_scalechoice_0_[0] , 
        \top_code_0_scaledatain_[15] , \top_code_0_scaledatain_[14] , 
        \top_code_0_scaledatain_[13] , \top_code_0_scaledatain_[12] , 
        \top_code_0_scaledatain_[11] , \top_code_0_scaledatain_[10] , 
        \top_code_0_scaledatain_[9] , \top_code_0_scaledatain_[8] , 
        \top_code_0_scaledatain_[7] , \top_code_0_scaledatain_[6] , 
        \top_code_0_scaledatain_[5] , \top_code_0_scaledatain_[4] , 
        \top_code_0_scaledatain_[3] , \top_code_0_scaledatain_[2] , 
        \top_code_0_scaledatain_[1] , \top_code_0_scaledatain_[0] , 
        \top_code_0_scaleddsdiv_[5] , \top_code_0_scaleddsdiv_[4] , 
        \top_code_0_scaleddsdiv_[3] , \top_code_0_scaleddsdiv_[2] , 
        \top_code_0_scaleddsdiv_[1] , \top_code_0_scaleddsdiv_[0] , 
        top_code_0_scaleload, top_code_0_scale_rst, 
        top_code_0_scale_start, top_code_0_scanchoice, 
        \top_code_0_scandata_[15] , \top_code_0_scandata_[14] , 
        \top_code_0_scandata_[13] , \top_code_0_scandata_[12] , 
        \top_code_0_scandata_[11] , \top_code_0_scandata_[10] , 
        \top_code_0_scandata_[9] , \top_code_0_scandata_[8] , 
        \top_code_0_scandata_[7] , \top_code_0_scandata_[6] , 
        \top_code_0_scandata_[5] , \top_code_0_scandata_[4] , 
        \top_code_0_scandata_[3] , \top_code_0_scandata_[2] , 
        \top_code_0_scandata_[1] , \top_code_0_scandata_[0] , 
        top_code_0_scanload, top_code_0_scan_start, 
        \top_code_0_sd_sacq_choice_[3] , 
        \top_code_0_sd_sacq_choice_[2] , 
        \top_code_0_sd_sacq_choice_[1] , 
        \top_code_0_sd_sacq_choice_[0] , 
        \top_code_0_sd_sacq_data_[15] , \top_code_0_sd_sacq_data_[14] , 
        \top_code_0_sd_sacq_data_[13] , \top_code_0_sd_sacq_data_[12] , 
        \top_code_0_sd_sacq_data_[11] , \top_code_0_sd_sacq_data_[10] , 
        \top_code_0_sd_sacq_data_[9] , \top_code_0_sd_sacq_data_[8] , 
        \top_code_0_sd_sacq_data_[7] , \top_code_0_sd_sacq_data_[6] , 
        \top_code_0_sd_sacq_data_[5] , \top_code_0_sd_sacq_data_[4] , 
        \top_code_0_sd_sacq_data_[3] , \top_code_0_sd_sacq_data_[2] , 
        \top_code_0_sd_sacq_data_[1] , \top_code_0_sd_sacq_data_[0] , 
        top_code_0_sd_sacq_load, top_code_0_sigrst, 
        \top_code_0_sigtimedata_[15] , \top_code_0_sigtimedata_[14] , 
        \top_code_0_sigtimedata_[13] , \top_code_0_sigtimedata_[12] , 
        \top_code_0_sigtimedata_[11] , \top_code_0_sigtimedata_[10] , 
        \top_code_0_sigtimedata_[9] , \top_code_0_sigtimedata_[8] , 
        \top_code_0_sigtimedata_[7] , \top_code_0_sigtimedata_[6] , 
        \top_code_0_sigtimedata_[5] , \top_code_0_sigtimedata_[4] , 
        \top_code_0_sigtimedata_[3] , \top_code_0_sigtimedata_[2] , 
        \top_code_0_sigtimedata_[1] , \top_code_0_sigtimedata_[0] , 
        \top_code_0_state_1ms_data_[15] , 
        \top_code_0_state_1ms_data_[14] , 
        \top_code_0_state_1ms_data_[13] , 
        \top_code_0_state_1ms_data_[12] , 
        \top_code_0_state_1ms_data_[11] , 
        \top_code_0_state_1ms_data_[10] , 
        \top_code_0_state_1ms_data_[9] , 
        \top_code_0_state_1ms_data_[8] , 
        \top_code_0_state_1ms_data_[7] , 
        \top_code_0_state_1ms_data_[6] , 
        \top_code_0_state_1ms_data_[5] , 
        \top_code_0_state_1ms_data_[4] , 
        \top_code_0_state_1ms_data_[3] , 
        \top_code_0_state_1ms_data_[2] , 
        \top_code_0_state_1ms_data_[1] , 
        \top_code_0_state_1ms_data_[0] , \top_code_0_state_1ms_lc_[3] , 
        \top_code_0_state_1ms_lc_[2] , \top_code_0_state_1ms_lc_[1] , 
        \top_code_0_state_1ms_lc_[0] , top_code_0_state_1ms_load, 
        top_code_0_state_1ms_rst_n, top_code_0_state_1ms_start, 
        \top_code_0_s_acqnum_2_[15] , \top_code_0_s_acqnum_2_[14] , 
        \top_code_0_s_acqnum_2_[13] , \top_code_0_s_acqnum_2_[12] , 
        \top_code_0_s_acqnum_2_[11] , \top_code_0_s_acqnum_2_[10] , 
        \top_code_0_s_acqnum_2_[9] , \top_code_0_s_acqnum_2_[8] , 
        \top_code_0_s_acqnum_2_[7] , \top_code_0_s_acqnum_2_[6] , 
        \top_code_0_s_acqnum_2_[5] , \top_code_0_s_acqnum_2_[4] , 
        \top_code_0_s_acqnum_2_[3] , \top_code_0_s_acqnum_2_[2] , 
        \top_code_0_s_acqnum_2_[1] , \top_code_0_s_acqnum_2_[0] , 
        \top_code_0_s_addchoice_[4] , \top_code_0_s_addchoice_[3] , 
        \top_code_0_s_addchoice_[2] , \top_code_0_s_addchoice_[1] , 
        \top_code_0_s_addchoice_[0] , top_code_0_s_load, 
        \top_code_0_s_periodnum_[3] , \top_code_0_s_periodnum_[2] , 
        \top_code_0_s_periodnum_[1] , \top_code_0_s_periodnum_[0] , 
        GND_net, VCC_net;
    
    n_pluse_acq n_acq_change_0 (.rst_n(net_27), .clk_sys(GLA), .change(
        top_code_0_pluse_noise_ctrl), .n_acq_startin1(
        noisestate_0_n_acq), .n_acq_startin2(plusestate_0_pluse_acq), 
        .n_acq_start(n_acq_change_0_n_acq_start), .n_rstin1_n(
        top_code_0_noise_rst), .n_rstin2_n(top_code_0_pluse_rst), 
        .n_rst_n(n_acq_change_0_n_rst_n));
    plusestate plusestate_0 (.clk_sys(GLA), .clken_p(
        timer_top_0_clk_en_pluse), .rst_n(top_code_0_pluse_rst), 
        .soft_d(plusestate_0_soft_d), .rt_sw(plusestate_0_rt_sw), 
        .sw_acq1(plusestate_0_sw_acq1), .sw_acq2(plusestate_0_sw_acq2), 
        .pluse_acq(plusestate_0_pluse_acq), .pluse_start(
        plusestate_0_pluse_start), .off_test(plusestate_0_off_test), 
        .load(top_code_0_pluseload), .loadchoice(top_code_0_pluse_lc), 
        .dump_start(plusestate_0_dump_start), .state_over_n(
        plusestate_0_state_over_n), .dds_config(
        plusestate_0_dds_config), .dumpoff_ctr(
        plusestate_0_dumpoff_ctr), .tetw_pluse(plusestate_0_tetw_pluse)
        , .timecount({\plusestate_0_timecount_[19] , 
        \plusestate_0_timecount_[18] , \plusestate_0_timecount_[17] , 
        \plusestate_0_timecount_[16] , \plusestate_0_timecount_[15] , 
        \plusestate_0_timecount_[14] , \plusestate_0_timecount_[13] , 
        \plusestate_0_timecount_[12] , \plusestate_0_timecount_[11] , 
        \plusestate_0_timecount_[10] , \plusestate_0_timecount_[9] , 
        \plusestate_0_timecount_[8] , \plusestate_0_timecount_[7] , 
        \plusestate_0_timecount_[6] , \plusestate_0_timecount_[5] , 
        \plusestate_0_timecount_[4] , \plusestate_0_timecount_[3] , 
        \plusestate_0_timecount_[2] , \plusestate_0_timecount_[1] , 
        \plusestate_0_timecount_[0] }), .datain({
        \top_code_0_plusedata_[15] , \top_code_0_plusedata_[14] , 
        \top_code_0_plusedata_[13] , \top_code_0_plusedata_[12] , 
        \top_code_0_plusedata_[11] , \top_code_0_plusedata_[10] , 
        \top_code_0_plusedata_[9] , \top_code_0_plusedata_[8] , 
        \top_code_0_plusedata_[7] , \top_code_0_plusedata_[6] , 
        \top_code_0_plusedata_[5] , \top_code_0_plusedata_[4] , 
        \top_code_0_plusedata_[3] , \top_code_0_plusedata_[2] , 
        \top_code_0_plusedata_[1] , \top_code_0_plusedata_[0] }));
    dds_change dds_change_0 (.rst_n(net_27), .clk_sys(GLA), .dds_rst(
        dds_change_0_dds_rst), .ddsrstin1(net_33), .ddsrstin2(net_45), 
        .ddsrstin3(top_code_0_pluse_rst), .dds_conf(
        dds_change_0_dds_conf), .dds_confin1(scanstate_0_dds_conf), 
        .dds_confin2(scalestate_0_dds_conf), .dds_confin3(
        plusestate_0_dds_config), .change({\top_code_0_change_[1] , 
        \top_code_0_change_[0] }));
    PLUSE PLUSE_0 (.state_start(pulse_start), .rst_n(
        bri_dump_sw_0_reset_out), .phase(bri_dump_sw_0_phase_ctr), 
        .quar_delay(net_51), .clk_sys(GLA), .pluse_load(
        top_code_0_bridge_load), .bri_cycle(PLUSE_0_bri_cycle), .Q1Q8(
        Q1Q8), .Q3Q6(Q3Q6), .Q4Q5(Q4Q5), .Q2Q7(Q2Q7), .clk_dds(
        ddsclkout), .clk_4f_en(clk_4f_en), .down(), .up(), .turn_delay(
        bri_dump_sw_0_turn_delay), .qq_para({
        \top_code_0_bri_datain_[15] , \top_code_0_bri_datain_[14] , 
        \top_code_0_bri_datain_[13] , \top_code_0_bri_datain_[12] , 
        \top_code_0_bri_datain_[11] , \top_code_0_bri_datain_[10] , 
        \top_code_0_bri_datain_[9] , \top_code_0_bri_datain_[8] , 
        \top_code_0_bri_datain_[7] , \top_code_0_bri_datain_[6] , 
        \top_code_0_bri_datain_[5] , \top_code_0_bri_datain_[4] , 
        \top_code_0_bri_datain_[3] , \top_code_0_bri_datain_[2] , 
        \top_code_0_bri_datain_[1] , \top_code_0_bri_datain_[0] }), 
        .bri_para({\top_code_0_halfdata_0_[7] , 
        \top_code_0_halfdata_0_[6] , \top_code_0_halfdata_0_[5] , 
        \top_code_0_halfdata_0_[4] , \top_code_0_halfdata_0_[3] , 
        \top_code_0_halfdata_0_[2] , \top_code_0_halfdata_0_[1] , 
        \top_code_0_halfdata_0_[0] }));
    DDS DDS_0 (.dds_load(top_code_0_dds_load), .dds_choice(
        top_code_0_dds_choice), .clk_sys(GLA), .rst_n(
        dds_change_0_dds_rst), .state_start(dds_change_0_dds_conf), 
        .reset(ddsreset), .fq_ud(ddsfqud), .w_clk(ddswclk), .data(
        ddsdata), .dds_para({\top_code_0_dds_configdata_[15] , 
        \top_code_0_dds_configdata_[14] , 
        \top_code_0_dds_configdata_[13] , 
        \top_code_0_dds_configdata_[12] , 
        \top_code_0_dds_configdata_[11] , 
        \top_code_0_dds_configdata_[10] , 
        \top_code_0_dds_configdata_[9] , 
        \top_code_0_dds_configdata_[8] , 
        \top_code_0_dds_configdata_[7] , 
        \top_code_0_dds_configdata_[6] , 
        \top_code_0_dds_configdata_[5] , 
        \top_code_0_dds_configdata_[4] , 
        \top_code_0_dds_configdata_[3] , 
        \top_code_0_dds_configdata_[2] , 
        \top_code_0_dds_configdata_[1] , 
        \top_code_0_dds_configdata_[0] }));
    AND2 AND2_0 (.A(Signal_Noise_Acq_0_acq_clk), .B(
        top_code_0_acqclken), .Y(Acq_clk));
    top_code top_code_0 (.rst_n(net_27), .clk_sys(GLA), .code_en(
        GPMI_0_code_en), .scan_rst(net_33), .scan_start(
        top_code_0_scan_start), .noise_rst(top_code_0_noise_rst), 
        .noise_start(top_code_0_noise_start), .dds_load(
        top_code_0_dds_load), .dds_choice(top_code_0_dds_choice), 
        .cal_load(top_code_0_cal_load), .s_load(top_code_0_s_load), 
        .scale_rst(top_code_0_scale_rst), .scale_start(
        top_code_0_scale_start), .scaleload(top_code_0_scaleload), 
        .bridge_load(top_code_0_bridge_load), .pn_change(
        top_code_0_pn_change), .dumpload(top_code_0_dumpload), 
        .pluse_noise_ctrl(top_code_0_pluse_noise_ctrl), .pluse_scale(
        top_code_0_pluse_scale), .pluse_str(top_code_0_pluse_str), 
        .pluse_rst(top_code_0_pluse_rst), .pluseload(
        top_code_0_pluseload), .pluse_lc(top_code_0_pluse_lc), .sigrst(
        top_code_0_sigrst), .scanchoice(top_code_0_scanchoice), 
        .scanload(top_code_0_scanload), .nstateload(
        top_code_0_nstateload), .nstatechoice(top_code_0_nstatechoice), 
        .acqclken(top_code_0_acqclken), .k1(k1), .k2(k2), 
        .state_1ms_rst_n(top_code_0_state_1ms_rst_n), .state_1ms_start(
        top_code_0_state_1ms_start), .state_1ms_load(
        top_code_0_state_1ms_load), .n_load(top_code_0_n_load), 
        .n_s_ctrl(top_code_0_n_s_ctrl), .sd_sacq_load(
        top_code_0_sd_sacq_load), .pd_pluse_load(
        top_code_0_pd_pluse_load), .RAM_Rd_rst(top_code_0_RAM_Rd_rst), 
        .n_rd_en(top_code_0_n_rd_en), .dump_sustain(
        top_code_0_dump_sustain), .inv_turn(top_code_0_inv_turn), .xa({
        xa[18], xa[17], xa[16], xa[15], xa[14], xa[13], xa[12], xa[11], 
        xa[10], xa[9], xa[8], xa[7], xa[6], xa[5], xa[4], xa[3], xa[2], 
        xa[1], xa[0]}), .xdata({\GPMI_0_dataout_[15] , 
        \GPMI_0_dataout_[14] , \GPMI_0_dataout_[13] , 
        \GPMI_0_dataout_[12] , \GPMI_0_dataout_[11] , 
        \GPMI_0_dataout_[10] , \GPMI_0_dataout_[9] , 
        \GPMI_0_dataout_[8] , \GPMI_0_dataout_[7] , 
        \GPMI_0_dataout_[6] , \GPMI_0_dataout_[5] , 
        \GPMI_0_dataout_[4] , \GPMI_0_dataout_[3] , 
        \GPMI_0_dataout_[2] , \GPMI_0_dataout_[1] , 
        \GPMI_0_dataout_[0] }), .dds_configdata({
        \top_code_0_dds_configdata_[15] , 
        \top_code_0_dds_configdata_[14] , 
        \top_code_0_dds_configdata_[13] , 
        \top_code_0_dds_configdata_[12] , 
        \top_code_0_dds_configdata_[11] , 
        \top_code_0_dds_configdata_[10] , 
        \top_code_0_dds_configdata_[9] , 
        \top_code_0_dds_configdata_[8] , 
        \top_code_0_dds_configdata_[7] , 
        \top_code_0_dds_configdata_[6] , 
        \top_code_0_dds_configdata_[5] , 
        \top_code_0_dds_configdata_[4] , 
        \top_code_0_dds_configdata_[3] , 
        \top_code_0_dds_configdata_[2] , 
        \top_code_0_dds_configdata_[1] , 
        \top_code_0_dds_configdata_[0] }), .cal_data({
        \top_code_0_cal_data_[5] , \top_code_0_cal_data_[4] , 
        \top_code_0_cal_data_[3] , \top_code_0_cal_data_[2] , 
        \top_code_0_cal_data_[1] , \top_code_0_cal_data_[0] }), 
        .s_acqnum({\top_code_0_s_acqnum_2_[15] , 
        \top_code_0_s_acqnum_2_[14] , \top_code_0_s_acqnum_2_[13] , 
        \top_code_0_s_acqnum_2_[12] , \top_code_0_s_acqnum_2_[11] , 
        \top_code_0_s_acqnum_2_[10] , \top_code_0_s_acqnum_2_[9] , 
        \top_code_0_s_acqnum_2_[8] , \top_code_0_s_acqnum_2_[7] , 
        \top_code_0_s_acqnum_2_[6] , \top_code_0_s_acqnum_2_[5] , 
        \top_code_0_s_acqnum_2_[4] , \top_code_0_s_acqnum_2_[3] , 
        \top_code_0_s_acqnum_2_[2] , \top_code_0_s_acqnum_2_[1] , 
        \top_code_0_s_acqnum_2_[0] }), .change({
        \top_code_0_change_[1] , \top_code_0_change_[0] }), 
        .scaledatain({\top_code_0_scaledatain_[15] , 
        \top_code_0_scaledatain_[14] , \top_code_0_scaledatain_[13] , 
        \top_code_0_scaledatain_[12] , \top_code_0_scaledatain_[11] , 
        \top_code_0_scaledatain_[10] , \top_code_0_scaledatain_[9] , 
        \top_code_0_scaledatain_[8] , \top_code_0_scaledatain_[7] , 
        \top_code_0_scaledatain_[6] , \top_code_0_scaledatain_[5] , 
        \top_code_0_scaledatain_[4] , \top_code_0_scaledatain_[3] , 
        \top_code_0_scaledatain_[2] , \top_code_0_scaledatain_[1] , 
        \top_code_0_scaledatain_[0] }), .scalechoice({
        \top_code_0_scalechoice_0_[4] , \top_code_0_scalechoice_0_[3] , 
        \top_code_0_scalechoice_0_[2] , \top_code_0_scalechoice_0_[1] , 
        \top_code_0_scalechoice_0_[0] }), .bri_datain({
        \top_code_0_bri_datain_[15] , \top_code_0_bri_datain_[14] , 
        \top_code_0_bri_datain_[13] , \top_code_0_bri_datain_[12] , 
        \top_code_0_bri_datain_[11] , \top_code_0_bri_datain_[10] , 
        \top_code_0_bri_datain_[9] , \top_code_0_bri_datain_[8] , 
        \top_code_0_bri_datain_[7] , \top_code_0_bri_datain_[6] , 
        \top_code_0_bri_datain_[5] , \top_code_0_bri_datain_[4] , 
        \top_code_0_bri_datain_[3] , \top_code_0_bri_datain_[2] , 
        \top_code_0_bri_datain_[1] , \top_code_0_bri_datain_[0] }), 
        .halfdata({\top_code_0_halfdata_0_[7] , 
        \top_code_0_halfdata_0_[6] , \top_code_0_halfdata_0_[5] , 
        \top_code_0_halfdata_0_[4] , \top_code_0_halfdata_0_[3] , 
        \top_code_0_halfdata_0_[2] , \top_code_0_halfdata_0_[1] , 
        \top_code_0_halfdata_0_[0] }), .dump_cho({
        \top_code_0_dump_cho_0_[2] , \top_code_0_dump_cho_0_[1] , 
        \top_code_0_dump_cho_0_[0] }), .dumpdata({
        \top_code_0_dumpdata_0_[11] , \top_code_0_dumpdata_0_[10] , 
        \top_code_0_dumpdata_0_[9] , \top_code_0_dumpdata_0_[8] , 
        \top_code_0_dumpdata_0_[7] , \top_code_0_dumpdata_0_[6] , 
        \top_code_0_dumpdata_0_[5] , \top_code_0_dumpdata_0_[4] , 
        \top_code_0_dumpdata_0_[3] , \top_code_0_dumpdata_0_[2] , 
        \top_code_0_dumpdata_0_[1] , \top_code_0_dumpdata_0_[0] }), 
        .scaleddsdiv({\top_code_0_scaleddsdiv_[5] , 
        \top_code_0_scaleddsdiv_[4] , \top_code_0_scaleddsdiv_[3] , 
        \top_code_0_scaleddsdiv_[2] , \top_code_0_scaleddsdiv_[1] , 
        \top_code_0_scaleddsdiv_[0] }), .plusedata({
        \top_code_0_plusedata_[15] , \top_code_0_plusedata_[14] , 
        \top_code_0_plusedata_[13] , \top_code_0_plusedata_[12] , 
        \top_code_0_plusedata_[11] , \top_code_0_plusedata_[10] , 
        \top_code_0_plusedata_[9] , \top_code_0_plusedata_[8] , 
        \top_code_0_plusedata_[7] , \top_code_0_plusedata_[6] , 
        \top_code_0_plusedata_[5] , \top_code_0_plusedata_[4] , 
        \top_code_0_plusedata_[3] , \top_code_0_plusedata_[2] , 
        \top_code_0_plusedata_[1] , \top_code_0_plusedata_[0] }), 
        .relayclose_on({relayclose_on[15], relayclose_on[14], 
        relayclose_on[13], relayclose_on[12], relayclose_on[11], 
        relayclose_on[10], relayclose_on[9], relayclose_on[8], 
        relayclose_on[7], relayclose_on[6], relayclose_on[5], 
        relayclose_on[4], relayclose_on[3], relayclose_on[2], 
        relayclose_on[1], relayclose_on[0]}), .sigtimedata({
        \top_code_0_sigtimedata_[15] , \top_code_0_sigtimedata_[14] , 
        \top_code_0_sigtimedata_[13] , \top_code_0_sigtimedata_[12] , 
        \top_code_0_sigtimedata_[11] , \top_code_0_sigtimedata_[10] , 
        \top_code_0_sigtimedata_[9] , \top_code_0_sigtimedata_[8] , 
        \top_code_0_sigtimedata_[7] , \top_code_0_sigtimedata_[6] , 
        \top_code_0_sigtimedata_[5] , \top_code_0_sigtimedata_[4] , 
        \top_code_0_sigtimedata_[3] , \top_code_0_sigtimedata_[2] , 
        \top_code_0_sigtimedata_[1] , \top_code_0_sigtimedata_[0] }), 
        .scandata({\top_code_0_scandata_[15] , 
        \top_code_0_scandata_[14] , \top_code_0_scandata_[13] , 
        \top_code_0_scandata_[12] , \top_code_0_scandata_[11] , 
        \top_code_0_scandata_[10] , \top_code_0_scandata_[9] , 
        \top_code_0_scandata_[8] , \top_code_0_scandata_[7] , 
        \top_code_0_scandata_[6] , \top_code_0_scandata_[5] , 
        \top_code_0_scandata_[4] , \top_code_0_scandata_[3] , 
        \top_code_0_scandata_[2] , \top_code_0_scandata_[1] , 
        \top_code_0_scandata_[0] }), .noisedata({
        \top_code_0_noisedata_[15] , \top_code_0_noisedata_[14] , 
        \top_code_0_noisedata_[13] , \top_code_0_noisedata_[12] , 
        \top_code_0_noisedata_[11] , \top_code_0_noisedata_[10] , 
        \top_code_0_noisedata_[9] , \top_code_0_noisedata_[8] , 
        \top_code_0_noisedata_[7] , \top_code_0_noisedata_[6] , 
        \top_code_0_noisedata_[5] , \top_code_0_noisedata_[4] , 
        \top_code_0_noisedata_[3] , \top_code_0_noisedata_[2] , 
        \top_code_0_noisedata_[1] , \top_code_0_noisedata_[0] }), 
        .state_1ms_lc({\top_code_0_state_1ms_lc_[3] , 
        \top_code_0_state_1ms_lc_[2] , \top_code_0_state_1ms_lc_[1] , 
        \top_code_0_state_1ms_lc_[0] }), .state_1ms_data({
        \top_code_0_state_1ms_data_[15] , 
        \top_code_0_state_1ms_data_[14] , 
        \top_code_0_state_1ms_data_[13] , 
        \top_code_0_state_1ms_data_[12] , 
        \top_code_0_state_1ms_data_[11] , 
        \top_code_0_state_1ms_data_[10] , 
        \top_code_0_state_1ms_data_[9] , 
        \top_code_0_state_1ms_data_[8] , 
        \top_code_0_state_1ms_data_[7] , 
        \top_code_0_state_1ms_data_[6] , 
        \top_code_0_state_1ms_data_[5] , 
        \top_code_0_state_1ms_data_[4] , 
        \top_code_0_state_1ms_data_[3] , 
        \top_code_0_state_1ms_data_[2] , 
        \top_code_0_state_1ms_data_[1] , 
        \top_code_0_state_1ms_data_[0] }), .n_divnum({
        \top_code_0_n_divnum_0_[9] , \top_code_0_n_divnum_0_[8] , 
        \top_code_0_n_divnum_0_[7] , \top_code_0_n_divnum_0_[6] , 
        \top_code_0_n_divnum_0_[5] , \top_code_0_n_divnum_0_[4] , 
        \top_code_0_n_divnum_0_[3] , \top_code_0_n_divnum_0_[2] , 
        \top_code_0_n_divnum_0_[1] , \top_code_0_n_divnum_0_[0] }), 
        .s_periodnum({\top_code_0_s_periodnum_[3] , 
        \top_code_0_s_periodnum_[2] , \top_code_0_s_periodnum_[1] , 
        \top_code_0_s_periodnum_[0] }), .n_acqnum({
        \top_code_0_n_acqnum_2_[11] , \top_code_0_n_acqnum_2_[10] , 
        \top_code_0_n_acqnum_2_[9] , \top_code_0_n_acqnum_2_[8] , 
        \top_code_0_n_acqnum_2_[7] , \top_code_0_n_acqnum_2_[6] , 
        \top_code_0_n_acqnum_2_[5] , \top_code_0_n_acqnum_2_[4] , 
        \top_code_0_n_acqnum_2_[3] , \top_code_0_n_acqnum_2_[2] , 
        \top_code_0_n_acqnum_2_[1] , \top_code_0_n_acqnum_2_[0] }), 
        .sd_sacq_choice({\top_code_0_sd_sacq_choice_[3] , 
        \top_code_0_sd_sacq_choice_[2] , 
        \top_code_0_sd_sacq_choice_[1] , 
        \top_code_0_sd_sacq_choice_[0] }), .sd_sacq_data({
        \top_code_0_sd_sacq_data_[15] , \top_code_0_sd_sacq_data_[14] , 
        \top_code_0_sd_sacq_data_[13] , \top_code_0_sd_sacq_data_[12] , 
        \top_code_0_sd_sacq_data_[11] , \top_code_0_sd_sacq_data_[10] , 
        \top_code_0_sd_sacq_data_[9] , \top_code_0_sd_sacq_data_[8] , 
        \top_code_0_sd_sacq_data_[7] , \top_code_0_sd_sacq_data_[6] , 
        \top_code_0_sd_sacq_data_[5] , \top_code_0_sd_sacq_data_[4] , 
        \top_code_0_sd_sacq_data_[3] , \top_code_0_sd_sacq_data_[2] , 
        \top_code_0_sd_sacq_data_[1] , \top_code_0_sd_sacq_data_[0] }), 
        .pd_pluse_choice({\top_code_0_pd_pluse_choice_[3] , 
        \top_code_0_pd_pluse_choice_[2] , 
        \top_code_0_pd_pluse_choice_[1] , 
        \top_code_0_pd_pluse_choice_[0] }), .pd_pluse_data({
        \top_code_0_pd_pluse_data_[15] , 
        \top_code_0_pd_pluse_data_[14] , 
        \top_code_0_pd_pluse_data_[13] , 
        \top_code_0_pd_pluse_data_[12] , 
        \top_code_0_pd_pluse_data_[11] , 
        \top_code_0_pd_pluse_data_[10] , 
        \top_code_0_pd_pluse_data_[9] , \top_code_0_pd_pluse_data_[8] , 
        \top_code_0_pd_pluse_data_[7] , \top_code_0_pd_pluse_data_[6] , 
        \top_code_0_pd_pluse_data_[5] , \top_code_0_pd_pluse_data_[4] , 
        \top_code_0_pd_pluse_data_[3] , \top_code_0_pd_pluse_data_[2] , 
        \top_code_0_pd_pluse_data_[1] , \top_code_0_pd_pluse_data_[0] })
        , .s_addchoice({\top_code_0_s_addchoice_[4] , 
        \top_code_0_s_addchoice_[3] , \top_code_0_s_addchoice_[2] , 
        \top_code_0_s_addchoice_[1] , \top_code_0_s_addchoice_[0] }), 
        .dump_sustain_data({\top_code_0_dump_sustain_data_[3] , 
        \top_code_0_dump_sustain_data_[2] , 
        \top_code_0_dump_sustain_data_[1] , 
        \top_code_0_dump_sustain_data_[0] }));
    VCC VCC (.Y(VCC_net));
    nsctrl_choice nsctrl_choice_0 (.rst_n(net_27), .clk_sys(GLA), 
        .change(top_code_0_n_s_ctrl), .soft_d_s(scanstate_0_soft_d), 
        .rt_sw_s(scanstate_0_rt_sw), .sw_acq1_s(scanstate_0_sw_acq1), 
        .sw_acq2_s(scanstate_0_sw_acq2), .inter_s(
        scanstate_0_state_over_n), .dumpon_ctr_s(
        scanstate_0_dumpon_ctr), .dumpoff_ctr_s(
        scanstate_0_dumpoff_ctr), .dumponoff_rst_s(net_33), .soft_d_n(
        noisestate_0_soft_d), .rt_sw_n(noisestate_0_rt_sw), .sw_acq1_n(
        noisestate_0_sw_acq1), .sw_acq2_n(noisestate_0_sw_acq2), 
        .inter_n(noisestate_0_state_over_n), .dumpon_ctr_n(
        noisestate_0_dumpon_ctr), .dumpoff_ctr_n(
        noisestate_0_dumpoff_ctr), .dumponoff_rst_n(
        top_code_0_noise_rst), .soft_d(nsctrl_choice_0_soft_d), .rt_sw(
        nsctrl_choice_0_rt_sw), .sw_acq1(nsctrl_choice_0_sw_acq1), 
        .sw_acq2(nsctrl_choice_0_sw_acq2), .intertodsp(
        nsctrl_choice_0_intertodsp), .dumpon_ctr(
        nsctrl_choice_0_dumpon_ctr), .dumpoff_ctr(
        nsctrl_choice_0_dumpoff_ctr), .dumponoff_rst(
        nsctrl_choice_0_dumponoff_rst));
    OR2 OR2_0 (.A(DUMP_0_dump_on), .B(DUMP_ON_0_dump_on), .Y(dumpon));
    GND GND (.Y(GND_net));
    state1ms_choice state1ms_choice_0 (.rst_n(net_27), .clk_sys(GLA), 
        .change(top_code_0_state_1ms_start), .pluse_start(
        bri_div_start_0), .pluse_start1(state_1ms_0_pluse_start), 
        .pluse_start2(bri_dump_sw_0_off_test), .dump_start(
        state1ms_choice_0_dump_start), .dump_start1(
        state_1ms_0_dump_start), .dump_start2(bri_dump_sw_0_dump_start)
        , .reset_out(state1ms_choice_0_reset_out), .reset_out1(
        state_1ms_0_reset_out), .reset_out2(bri_dump_sw_0_reset_out), 
        .bri_cycle(state1ms_choice_0_bri_cycle), .bri_cycle1(
        state_1ms_0_bri_cycle), .bri_cycle2(PLUSE_0_bri_cycle), .rt_sw(
        rt_sw), .rt_sw1(state_1ms_0_rt_sw), .rt_sw2(rt_sw_net_1), 
        .soft_dump(soft_dump), .soft_dump1(state_1ms_0_soft_dump), 
        .soft_dump2(soft_dump_net_1));
    DUMP_OFF DUMP_OFF_0 (.rst_n(bri_dump_sw_0_reset_out), .state_start(
        bri_dump_sw_0_dumpoff_ctr), .clk_sys(GLA), .dump_off(
        DUMP_OFF_0_dump_off));
    sd_acq_top sd_acq_top_0 (.dds(ddsclkout), .rst_n(net_27), .s_acq1(
        scalestate_0_s_acq), .clk_sys(GLA), .sd_sacq_load(
        top_code_0_sd_sacq_load), .bb_ch(net_51), .s_acq180(s_acq180), 
        .en(sd_acq_en), .long_opentime(scalestate_0_long_opentime), 
        .sd_sacq_choice({\top_code_0_sd_sacq_choice_[3] , 
        \top_code_0_sd_sacq_choice_[2] , 
        \top_code_0_sd_sacq_choice_[1] , 
        \top_code_0_sd_sacq_choice_[0] }), .sd_sacq_data({
        \top_code_0_sd_sacq_data_[15] , \top_code_0_sd_sacq_data_[14] , 
        \top_code_0_sd_sacq_data_[13] , \top_code_0_sd_sacq_data_[12] , 
        \top_code_0_sd_sacq_data_[11] , \top_code_0_sd_sacq_data_[10] , 
        \top_code_0_sd_sacq_data_[9] , \top_code_0_sd_sacq_data_[8] , 
        \top_code_0_sd_sacq_data_[7] , \top_code_0_sd_sacq_data_[6] , 
        \top_code_0_sd_sacq_data_[5] , \top_code_0_sd_sacq_data_[4] , 
        \top_code_0_sd_sacq_data_[3] , \top_code_0_sd_sacq_data_[2] , 
        \top_code_0_sd_sacq_data_[1] , \top_code_0_sd_sacq_data_[0] }));
    timer_top timer_top_0 (.clk_sys(GLA), .rst_n(net_27), .clk_en_scan(
        timer_top_0_clk_en_scan), .clk_en_st1ms(
        timer_top_0_clk_en_st1ms), .clk_en_pluse(
        timer_top_0_clk_en_pluse), .clk_en_scale(
        timer_top_0_clk_en_scale), .clk_en_noise(
        timer_top_0_clk_en_noise), .datain_state_1ms({
        \state_1ms_0_timecount_[19] , \state_1ms_0_timecount_[18] , 
        \state_1ms_0_timecount_[17] , \state_1ms_0_timecount_[16] , 
        \state_1ms_0_timecount_[15] , \state_1ms_0_timecount_[14] , 
        \state_1ms_0_timecount_[13] , \state_1ms_0_timecount_[12] , 
        \state_1ms_0_timecount_[11] , \state_1ms_0_timecount_[10] , 
        \state_1ms_0_timecount_[9] , \state_1ms_0_timecount_[8] , 
        \state_1ms_0_timecount_[7] , \state_1ms_0_timecount_[6] , 
        \state_1ms_0_timecount_[5] , \state_1ms_0_timecount_[4] , 
        \state_1ms_0_timecount_[3] , \state_1ms_0_timecount_[2] , 
        \state_1ms_0_timecount_[1] , \state_1ms_0_timecount_[0] }), 
        .datain_pluse({\plusestate_0_timecount_[19] , 
        \plusestate_0_timecount_[18] , \plusestate_0_timecount_[17] , 
        \plusestate_0_timecount_[16] , \plusestate_0_timecount_[15] , 
        \plusestate_0_timecount_[14] , \plusestate_0_timecount_[13] , 
        \plusestate_0_timecount_[12] , \plusestate_0_timecount_[11] , 
        \plusestate_0_timecount_[10] , \plusestate_0_timecount_[9] , 
        \plusestate_0_timecount_[8] , \plusestate_0_timecount_[7] , 
        \plusestate_0_timecount_[6] , \plusestate_0_timecount_[5] , 
        \plusestate_0_timecount_[4] , \plusestate_0_timecount_[3] , 
        \plusestate_0_timecount_[2] , \plusestate_0_timecount_[1] , 
        \plusestate_0_timecount_[0] }), .datain_scale({
        \scalestate_0_timecount_[21] , \scalestate_0_timecount_[20] , 
        \scalestate_0_timecount_[19] , \scalestate_0_timecount_[18] , 
        \scalestate_0_timecount_[17] , \scalestate_0_timecount_[16] , 
        \scalestate_0_timecount_[15] , \scalestate_0_timecount_[14] , 
        \scalestate_0_timecount_[13] , \scalestate_0_timecount_[12] , 
        \scalestate_0_timecount_[11] , \scalestate_0_timecount_[10] , 
        \scalestate_0_timecount_[9] , \scalestate_0_timecount_[8] , 
        \scalestate_0_timecount_[7] , \scalestate_0_timecount_[6] , 
        \scalestate_0_timecount_[5] , \scalestate_0_timecount_[4] , 
        \scalestate_0_timecount_[3] , \scalestate_0_timecount_[2] , 
        \scalestate_0_timecount_[1] , \scalestate_0_timecount_[0] }), 
        .datain_scan({\scanstate_0_timecount_[19] , 
        \scanstate_0_timecount_[18] , \scanstate_0_timecount_[17] , 
        \scanstate_0_timecount_[16] , \scanstate_0_timecount_[15] , 
        \scanstate_0_timecount_[14] , \scanstate_0_timecount_[13] , 
        \scanstate_0_timecount_[12] , \scanstate_0_timecount_[11] , 
        \scanstate_0_timecount_[10] , \scanstate_0_timecount_[9] , 
        \scanstate_0_timecount_[8] , \scanstate_0_timecount_[7] , 
        \scanstate_0_timecount_[6] , \scanstate_0_timecount_[5] , 
        \scanstate_0_timecount_[4] , \scanstate_0_timecount_[3] , 
        \scanstate_0_timecount_[2] , \scanstate_0_timecount_[1] , 
        \scanstate_0_timecount_[0] }), .datain_noise({
        \noisestate_0_timecount_[19] , \noisestate_0_timecount_[18] , 
        \noisestate_0_timecount_[17] , \noisestate_0_timecount_[16] , 
        \noisestate_0_timecount_[15] , \noisestate_0_timecount_[14] , 
        \noisestate_0_timecount_[13] , \noisestate_0_timecount_[12] , 
        \noisestate_0_timecount_[11] , \noisestate_0_timecount_[10] , 
        \noisestate_0_timecount_[9] , \noisestate_0_timecount_[8] , 
        \noisestate_0_timecount_[7] , \noisestate_0_timecount_[6] , 
        \noisestate_0_timecount_[5] , \noisestate_0_timecount_[4] , 
        \noisestate_0_timecount_[3] , \noisestate_0_timecount_[2] , 
        \noisestate_0_timecount_[1] , \noisestate_0_timecount_[0] }), 
        .start({top_code_0_state_1ms_start, top_code_0_pluse_str, 
        top_code_0_noise_start, top_code_0_scan_start, 
        top_code_0_scale_start}), .state_over_in({
        plusestate_0_state_over_n, noisestate_0_state_over_n, 
        scanstate_0_state_over_n, scalestate_0_state_over_n}));
    DSTimer DSTimer_0 (.clk_sys(GLA), .dump_sustain(
        top_code_0_dump_sustain), .rst_n(top_code_0_dump_sustain), 
        .start(net_40), .state_start(scalestate_0_dump_sustain_ctrl), 
        .clk_10k(ClockManagement_0_clock_10khz), .dump_sustain_data({
        \top_code_0_dump_sustain_data_[3] , 
        \top_code_0_dump_sustain_data_[2] , 
        \top_code_0_dump_sustain_data_[1] , 
        \top_code_0_dump_sustain_data_[0] }));
    bri_dump_sw bri_dump_sw_0 (.rst_n(net_27), .clk_sys(GLA), .change(
        top_code_0_pluse_scale), .pluse_start(pulse_start), 
        .pluse_start1(scalestate_0_pluse_start), .pluse_start2(
        plusestate_0_pluse_start), .off_test(bri_dump_sw_0_off_test), 
        .off_test1(scalestate_0_off_test), .off_test2(
        plusestate_0_off_test), .dump_start(bri_dump_sw_0_dump_start), 
        .dump_start1(scalestate_0_dump_start), .dump_start2(
        plusestate_0_dump_start), .phase_ctr(bri_dump_sw_0_phase_ctr), 
        .phase_ctr1(scalestate_0_pn_out), .phase_ctr2(
        top_code_0_pn_change), .reset_out(bri_dump_sw_0_reset_out), 
        .reset_out1(net_45), .reset_out2(top_code_0_pluse_rst), 
        .dumpoff_ctr(bri_dump_sw_0_dumpoff_ctr), .dumpoff_ctr1(
        scalestate_0_dumpoff_ctr), .dumpoff_ctr2(
        plusestate_0_dumpoff_ctr), .tetw_pluse(
        bri_dump_sw_0_tetw_pluse), .tetw_pluse1(
        scalestate_0_tetw_pluse), .tetw_pluse2(plusestate_0_tetw_pluse)
        , .turn_delay(bri_dump_sw_0_turn_delay), .turn_delay1(
        scalestate_0_ne_le), .turn_delay2(VCC_net));
    scan_scale_sw scan_scale_sw_0 (.rst_n(net_27), .dds(ddsclkout), 
        .s_start(scan_scale_sw_0_s_start), .s_startin1(
        scanstate_0_s_acq), .s_startin2(sd_acq_en), .change({
        \top_code_0_change_[1] , \top_code_0_change_[0] }));
    s_acq_change s_acq_change_0 (.rst_n(net_27), .clk_sys(GLA), 
        .s_load(s_acq_change_0_s_load), .s_loadin1(top_code_0_s_load), 
        .s_loadin2(scalestate_0_load_out), .s_rst(s_acq_change_0_s_rst)
        , .s_rstin1(net_33), .s_rstin2(net_45), .change({
        \top_code_0_change_[1] , \top_code_0_change_[0] }), .s_acqnum({
        \s_acq_change_0_s_acqnum_[15] , \s_acq_change_0_s_acqnum_[14] , 
        \s_acq_change_0_s_acqnum_[13] , \s_acq_change_0_s_acqnum_[12] , 
        \s_acq_change_0_s_acqnum_[11] , \s_acq_change_0_s_acqnum_[10] , 
        \s_acq_change_0_s_acqnum_[9] , \s_acq_change_0_s_acqnum_[8] , 
        \s_acq_change_0_s_acqnum_[7] , \s_acq_change_0_s_acqnum_[6] , 
        \s_acq_change_0_s_acqnum_[5] , \s_acq_change_0_s_acqnum_[4] , 
        \s_acq_change_0_s_acqnum_[3] , \s_acq_change_0_s_acqnum_[2] , 
        \s_acq_change_0_s_acqnum_[1] , \s_acq_change_0_s_acqnum_[0] }), 
        .s_acqnumin1({\top_code_0_s_acqnum_2_[15] , 
        \top_code_0_s_acqnum_2_[14] , \top_code_0_s_acqnum_2_[13] , 
        \top_code_0_s_acqnum_2_[12] , \top_code_0_s_acqnum_2_[11] , 
        \top_code_0_s_acqnum_2_[10] , \top_code_0_s_acqnum_2_[9] , 
        \top_code_0_s_acqnum_2_[8] , \top_code_0_s_acqnum_2_[7] , 
        \top_code_0_s_acqnum_2_[6] , \top_code_0_s_acqnum_2_[5] , 
        \top_code_0_s_acqnum_2_[4] , \top_code_0_s_acqnum_2_[3] , 
        \top_code_0_s_acqnum_2_[2] , \top_code_0_s_acqnum_2_[1] , 
        \top_code_0_s_acqnum_2_[0] }), .s_acqnumin2({
        \scalestate_0_s_acqnum_[15] , \scalestate_0_s_acqnum_[14] , 
        \scalestate_0_s_acqnum_[13] , \scalestate_0_s_acqnum_[12] , 
        \scalestate_0_s_acqnum_[11] , \scalestate_0_s_acqnum_[10] , 
        \scalestate_0_s_acqnum_[9] , \scalestate_0_s_acqnum_[8] , 
        \scalestate_0_s_acqnum_[7] , \scalestate_0_s_acqnum_[6] , 
        \scalestate_0_s_acqnum_[5] , \scalestate_0_s_acqnum_[4] , 
        \scalestate_0_s_acqnum_[3] , \scalestate_0_s_acqnum_[2] , 
        \scalestate_0_s_acqnum_[1] , \scalestate_0_s_acqnum_[0] }), 
        .s_stripnum({\s_acq_change_0_s_stripnum_[11] , 
        \s_acq_change_0_s_stripnum_[10] , 
        \s_acq_change_0_s_stripnum_[9] , 
        \s_acq_change_0_s_stripnum_[8] , 
        \s_acq_change_0_s_stripnum_[7] , 
        \s_acq_change_0_s_stripnum_[6] , 
        \s_acq_change_0_s_stripnum_[5] , 
        \s_acq_change_0_s_stripnum_[4] , 
        \s_acq_change_0_s_stripnum_[3] , 
        \s_acq_change_0_s_stripnum_[2] , 
        \s_acq_change_0_s_stripnum_[1] , 
        \s_acq_change_0_s_stripnum_[0] }), .s_stripnumin1({GND_net, 
        GND_net, GND_net, GND_net, GND_net, GND_net, GND_net, GND_net, 
        GND_net, GND_net, GND_net, GND_net}), .s_stripnumin2({
        \scalestate_0_strippluse_[11] , \scalestate_0_strippluse_[10] , 
        \scalestate_0_strippluse_[9] , \scalestate_0_strippluse_[8] , 
        \scalestate_0_strippluse_[7] , \scalestate_0_strippluse_[6] , 
        \scalestate_0_strippluse_[5] , \scalestate_0_strippluse_[4] , 
        \scalestate_0_strippluse_[3] , \scalestate_0_strippluse_[2] , 
        \scalestate_0_strippluse_[1] , \scalestate_0_strippluse_[0] }));
    scanstate scanstate_0 (.clk_sys(GLA), .clken_p(
        timer_top_0_clk_en_scan), .rst_n(net_33), .dumpon_ctr(
        scanstate_0_dumpon_ctr), .dumpoff_ctr(scanstate_0_dumpoff_ctr), 
        .soft_d(scanstate_0_soft_d), .rt_sw(scanstate_0_rt_sw), 
        .sw_acq1(scanstate_0_sw_acq1), .sw_acq2(scanstate_0_sw_acq2), 
        .s_acq(scanstate_0_s_acq), .dds_conf(scanstate_0_dds_conf), 
        .calctrl(scanstate_0_calctrl), .state_over_n(
        scanstate_0_state_over_n), .scanload(top_code_0_scanload), 
        .scanchoice(top_code_0_scanchoice), .resetout(), .timecount({
        \scanstate_0_timecount_[19] , \scanstate_0_timecount_[18] , 
        \scanstate_0_timecount_[17] , \scanstate_0_timecount_[16] , 
        \scanstate_0_timecount_[15] , \scanstate_0_timecount_[14] , 
        \scanstate_0_timecount_[13] , \scanstate_0_timecount_[12] , 
        \scanstate_0_timecount_[11] , \scanstate_0_timecount_[10] , 
        \scanstate_0_timecount_[9] , \scanstate_0_timecount_[8] , 
        \scanstate_0_timecount_[7] , \scanstate_0_timecount_[6] , 
        \scanstate_0_timecount_[5] , \scanstate_0_timecount_[4] , 
        \scanstate_0_timecount_[3] , \scanstate_0_timecount_[2] , 
        \scanstate_0_timecount_[1] , \scanstate_0_timecount_[0] }), 
        .datain({\top_code_0_scandata_[15] , 
        \top_code_0_scandata_[14] , \top_code_0_scandata_[13] , 
        \top_code_0_scandata_[12] , \top_code_0_scandata_[11] , 
        \top_code_0_scandata_[10] , \top_code_0_scandata_[9] , 
        \top_code_0_scandata_[8] , \top_code_0_scandata_[7] , 
        \top_code_0_scandata_[6] , \top_code_0_scandata_[5] , 
        \top_code_0_scandata_[4] , \top_code_0_scandata_[3] , 
        \top_code_0_scandata_[2] , \top_code_0_scandata_[1] , 
        \top_code_0_scandata_[0] }));
    state_1ms state_1ms_0 (.clk_sys(GLA), .clken_p(
        timer_top_0_clk_en_st1ms), .rst_n(top_code_0_state_1ms_rst_n), 
        .load(top_code_0_state_1ms_load), .reset_out(
        state_1ms_0_reset_out), .dump_start(state_1ms_0_dump_start), 
        .pluse_start(state_1ms_0_pluse_start), .bri_cycle(
        state_1ms_0_bri_cycle), .rt_sw(state_1ms_0_rt_sw), .soft_dump(
        state_1ms_0_soft_dump), .loadchoice({
        \top_code_0_state_1ms_lc_[3] , \top_code_0_state_1ms_lc_[2] , 
        \top_code_0_state_1ms_lc_[1] , \top_code_0_state_1ms_lc_[0] }), 
        .datain({\top_code_0_state_1ms_data_[15] , 
        \top_code_0_state_1ms_data_[14] , 
        \top_code_0_state_1ms_data_[13] , 
        \top_code_0_state_1ms_data_[12] , 
        \top_code_0_state_1ms_data_[11] , 
        \top_code_0_state_1ms_data_[10] , 
        \top_code_0_state_1ms_data_[9] , 
        \top_code_0_state_1ms_data_[8] , 
        \top_code_0_state_1ms_data_[7] , 
        \top_code_0_state_1ms_data_[6] , 
        \top_code_0_state_1ms_data_[5] , 
        \top_code_0_state_1ms_data_[4] , 
        \top_code_0_state_1ms_data_[3] , 
        \top_code_0_state_1ms_data_[2] , 
        \top_code_0_state_1ms_data_[1] , 
        \top_code_0_state_1ms_data_[0] }), .timecount({
        \state_1ms_0_timecount_[19] , \state_1ms_0_timecount_[18] , 
        \state_1ms_0_timecount_[17] , \state_1ms_0_timecount_[16] , 
        \state_1ms_0_timecount_[15] , \state_1ms_0_timecount_[14] , 
        \state_1ms_0_timecount_[13] , \state_1ms_0_timecount_[12] , 
        \state_1ms_0_timecount_[11] , \state_1ms_0_timecount_[10] , 
        \state_1ms_0_timecount_[9] , \state_1ms_0_timecount_[8] , 
        \state_1ms_0_timecount_[7] , \state_1ms_0_timecount_[6] , 
        \state_1ms_0_timecount_[5] , \state_1ms_0_timecount_[4] , 
        \state_1ms_0_timecount_[3] , \state_1ms_0_timecount_[2] , 
        \state_1ms_0_timecount_[1] , \state_1ms_0_timecount_[0] }));
    noisestate noisestate_0 (.clk_sys(GLA), .clken_p(
        timer_top_0_clk_en_noise), .rst_n(top_code_0_noise_rst), 
        .dumpon_ctr(noisestate_0_dumpon_ctr), .dumpoff_ctr(
        noisestate_0_dumpoff_ctr), .soft_d(noisestate_0_soft_d), 
        .rt_sw(noisestate_0_rt_sw), .sw_acq1(noisestate_0_sw_acq1), 
        .sw_acq2(noisestate_0_sw_acq2), .n_acq(noisestate_0_n_acq), 
        .state_over_n(noisestate_0_state_over_n), .nload(
        top_code_0_nstateload), .nchoice(top_code_0_nstatechoice), 
        .timecount({\noisestate_0_timecount_[19] , 
        \noisestate_0_timecount_[18] , \noisestate_0_timecount_[17] , 
        \noisestate_0_timecount_[16] , \noisestate_0_timecount_[15] , 
        \noisestate_0_timecount_[14] , \noisestate_0_timecount_[13] , 
        \noisestate_0_timecount_[12] , \noisestate_0_timecount_[11] , 
        \noisestate_0_timecount_[10] , \noisestate_0_timecount_[9] , 
        \noisestate_0_timecount_[8] , \noisestate_0_timecount_[7] , 
        \noisestate_0_timecount_[6] , \noisestate_0_timecount_[5] , 
        \noisestate_0_timecount_[4] , \noisestate_0_timecount_[3] , 
        \noisestate_0_timecount_[2] , \noisestate_0_timecount_[1] , 
        \noisestate_0_timecount_[0] }), .ndatain({
        \top_code_0_noisedata_[15] , \top_code_0_noisedata_[14] , 
        \top_code_0_noisedata_[13] , \top_code_0_noisedata_[12] , 
        \top_code_0_noisedata_[11] , \top_code_0_noisedata_[10] , 
        \top_code_0_noisedata_[9] , \top_code_0_noisedata_[8] , 
        \top_code_0_noisedata_[7] , \top_code_0_noisedata_[6] , 
        \top_code_0_noisedata_[5] , \top_code_0_noisedata_[4] , 
        \top_code_0_noisedata_[3] , \top_code_0_noisedata_[2] , 
        \top_code_0_noisedata_[1] , \top_code_0_noisedata_[0] }));
    bridge_div bridge_div_0 (.bri_div_start(pd_pulse_en), .rst_n(
        bri_dump_sw_0_reset_out), .clk_sys(GLA), .clk_dds(ddsclkout), 
        .load(top_code_0_bridge_load), .clk_4f_en(clk_4f_en), 
        .divcount({\top_code_0_scaleddsdiv_[5] , 
        \top_code_0_scaleddsdiv_[4] , \top_code_0_scaleddsdiv_[3] , 
        \top_code_0_scaleddsdiv_[2] , \top_code_0_scaleddsdiv_[1] , 
        \top_code_0_scaleddsdiv_[0] }));
    OR2 OR2_1 (.A(nsctrl_choice_0_dumpon_ctr), .B(net_40), .Y(OR2_1_Y));
    pd_pluse_top pd_pluse_top_0 (.dds(ddsclkout), .rst_n(net_27), 
        .pluse_start(pulse_start), .clk_sys(GLA), .pd_pluse_load(
        top_code_0_pd_pluse_load), .bb_ch(net_51), .tetw_pluse(
        bri_dump_sw_0_tetw_pluse), .en(pd_pulse_en), .pd_pluse_choice({
        \top_code_0_pd_pluse_choice_[3] , 
        \top_code_0_pd_pluse_choice_[2] , 
        \top_code_0_pd_pluse_choice_[1] , 
        \top_code_0_pd_pluse_choice_[0] }), .pd_pluse_data({
        \top_code_0_pd_pluse_data_[15] , 
        \top_code_0_pd_pluse_data_[14] , 
        \top_code_0_pd_pluse_data_[13] , 
        \top_code_0_pd_pluse_data_[12] , 
        \top_code_0_pd_pluse_data_[11] , 
        \top_code_0_pd_pluse_data_[10] , 
        \top_code_0_pd_pluse_data_[9] , \top_code_0_pd_pluse_data_[8] , 
        \top_code_0_pd_pluse_data_[7] , \top_code_0_pd_pluse_data_[6] , 
        \top_code_0_pd_pluse_data_[5] , \top_code_0_pd_pluse_data_[4] , 
        \top_code_0_pd_pluse_data_[3] , \top_code_0_pd_pluse_data_[2] , 
        \top_code_0_pd_pluse_data_[1] , \top_code_0_pd_pluse_data_[0] })
        );
    OR3 OR3_0 (.A(DUMP_OFF_1_dump_off), .B(DUMP_OFF_0_dump_off), .C(
        DUMP_0_dump_off), .Y(dumpoff));
    DUMP_ON DUMP_ON_0 (.dump_on(DUMP_ON_0_dump_on), .state_start(
        OR2_1_Y), .rst_n(OR2_2_Y), .clk_sys(GLA));
    CAL CAL_0 (.clk_sys(GLA), .rst_n(net_33), .cal_start(
        scanstate_0_calctrl), .clk_dds(ddsclkout), .cal(cal_out), 
        .cal_load(top_code_0_cal_load), .cal_para({
        \top_code_0_cal_data_[5] , \top_code_0_cal_data_[4] , 
        \top_code_0_cal_data_[3] , \top_code_0_cal_data_[2] , 
        \top_code_0_cal_data_[1] , \top_code_0_cal_data_[0] }));
    topctrlchange topctrlchange_0 (.rst_n(net_27), .clk_sys(GLA), 
        .interupt(interupt), .interin1(nsctrl_choice_0_intertodsp), 
        .interin2(scalestate_0_state_over_n), .interin3(
        plusestate_0_state_over_n), .rt_sw(rt_sw_net_1), .rt_swin1(
        nsctrl_choice_0_rt_sw), .rt_swin2(scalestate_0_rt_sw), 
        .rt_swin3(plusestate_0_rt_sw), .soft_dump(soft_dump_net_1), 
        .s_dumpin1(nsctrl_choice_0_soft_d), .s_dumpin2(
        scalestate_0_soft_d), .s_dumpin3(plusestate_0_soft_d), 
        .sw_acq1(sw_acq1), .sw_acq1in1(nsctrl_choice_0_sw_acq1), 
        .sw_acq1in2(scalestate_0_sw_acq1), .sw_acq1in3(
        plusestate_0_sw_acq1), .sw_acq2(sw_acq2), .sw_acq2in1(
        nsctrl_choice_0_sw_acq2), .sw_acq2in2(scalestate_0_sw_acq2), 
        .sw_acq2in3(plusestate_0_sw_acq2), .change({
        \top_code_0_change_[1] , \top_code_0_change_[0] }));
    DUMP_OFF DUMP_OFF_1 (.rst_n(nsctrl_choice_0_dumponoff_rst), 
        .state_start(nsctrl_choice_0_dumpoff_ctr), .clk_sys(GLA), 
        .dump_off(DUMP_OFF_1_dump_off));
    DUMP DUMP_0 (.rst_n(state1ms_choice_0_reset_out), .state_start(
        state1ms_choice_0_dump_start), .clk_sys(GLA), .dump_off(
        DUMP_0_dump_off), .dump_on(DUMP_0_dump_on), .dump_load(
        top_code_0_dumpload), .bri_cycle(state1ms_choice_0_bri_cycle), 
        .pluse_start(bri_div_start_0), .dump_choice({
        \top_code_0_dump_cho_0_[2] , \top_code_0_dump_cho_0_[1] , 
        \top_code_0_dump_cho_0_[0] }), .dump_para({
        \top_code_0_dumpdata_0_[11] , \top_code_0_dumpdata_0_[10] , 
        \top_code_0_dumpdata_0_[9] , \top_code_0_dumpdata_0_[8] , 
        \top_code_0_dumpdata_0_[7] , \top_code_0_dumpdata_0_[6] , 
        \top_code_0_dumpdata_0_[5] , \top_code_0_dumpdata_0_[4] , 
        \top_code_0_dumpdata_0_[3] , \top_code_0_dumpdata_0_[2] , 
        \top_code_0_dumpdata_0_[1] , \top_code_0_dumpdata_0_[0] }));
    ClockManagement ClockManagement_0 (.OCX40MHz(OCX40MHz), .GLA(GLA), 
        .rst_n(net_27), .start(top_code_0_sigrst), .timeup(sigtimeup), 
        .clock_10khz(ClockManagement_0_clock_10khz), .timer_para({
        \top_code_0_sigtimedata_[15] , \top_code_0_sigtimedata_[14] , 
        \top_code_0_sigtimedata_[13] , \top_code_0_sigtimedata_[12] , 
        \top_code_0_sigtimedata_[11] , \top_code_0_sigtimedata_[10] , 
        \top_code_0_sigtimedata_[9] , \top_code_0_sigtimedata_[8] , 
        \top_code_0_sigtimedata_[7] , \top_code_0_sigtimedata_[6] , 
        \top_code_0_sigtimedata_[5] , \top_code_0_sigtimedata_[4] , 
        \top_code_0_sigtimedata_[3] , \top_code_0_sigtimedata_[2] , 
        \top_code_0_sigtimedata_[1] , \top_code_0_sigtimedata_[0] }));
    Signal_Noise_Acq Signal_Noise_Acq_0 (.clk_sys(GLA), .clk_dds(
        ddsclkout), .acq_clk(Signal_Noise_Acq_0_acq_clk), .n_s_ctrl(
        top_code_0_n_s_ctrl), .n_reset(n_acq_change_0_n_rst_n), 
        .noise_load(top_code_0_n_load), .RAM_RDaddr_rst(
        top_code_0_RAM_Rd_rst), .RAM_RD_EN(top_code_0_n_rd_en), 
        .RAM_WT_EN(n_acq_change_0_n_acq_start), .XRD(XRD), 
        .signal_load(s_acq_change_0_s_load), .s_reset(
        s_acq_change_0_s_rst), .s_acq_en(scan_scale_sw_0_s_start), 
        .adcdata({ADC[11], ADC[10], ADC[9], ADC[8], ADC[7], ADC[6], 
        ADC[5], ADC[4], ADC[3], ADC[2], ADC[1], ADC[0]}), .dataout({
        \Signal_Noise_Acq_0_dataout_[15] , 
        \Signal_Noise_Acq_0_dataout_[14] , 
        \Signal_Noise_Acq_0_dataout_[13] , 
        \Signal_Noise_Acq_0_dataout_[12] , 
        \Signal_Noise_Acq_0_dataout_[11] , 
        \Signal_Noise_Acq_0_dataout_[10] , 
        \Signal_Noise_Acq_0_dataout_[9] , 
        \Signal_Noise_Acq_0_dataout_[8] , 
        \Signal_Noise_Acq_0_dataout_[7] , 
        \Signal_Noise_Acq_0_dataout_[6] , 
        \Signal_Noise_Acq_0_dataout_[5] , 
        \Signal_Noise_Acq_0_dataout_[4] , 
        \Signal_Noise_Acq_0_dataout_[3] , 
        \Signal_Noise_Acq_0_dataout_[2] , 
        \Signal_Noise_Acq_0_dataout_[1] , 
        \Signal_Noise_Acq_0_dataout_[0] }), .n_acqnum({
        \top_code_0_n_acqnum_2_[11] , \top_code_0_n_acqnum_2_[10] , 
        \top_code_0_n_acqnum_2_[9] , \top_code_0_n_acqnum_2_[8] , 
        \top_code_0_n_acqnum_2_[7] , \top_code_0_n_acqnum_2_[6] , 
        \top_code_0_n_acqnum_2_[5] , \top_code_0_n_acqnum_2_[4] , 
        \top_code_0_n_acqnum_2_[3] , \top_code_0_n_acqnum_2_[2] , 
        \top_code_0_n_acqnum_2_[1] , \top_code_0_n_acqnum_2_[0] }), 
        .n_divnum({\top_code_0_n_divnum_0_[9] , 
        \top_code_0_n_divnum_0_[8] , \top_code_0_n_divnum_0_[7] , 
        \top_code_0_n_divnum_0_[6] , \top_code_0_n_divnum_0_[5] , 
        \top_code_0_n_divnum_0_[4] , \top_code_0_n_divnum_0_[3] , 
        \top_code_0_n_divnum_0_[2] , \top_code_0_n_divnum_0_[1] , 
        \top_code_0_n_divnum_0_[0] }), .s_periodnum({
        \top_code_0_s_periodnum_[3] , \top_code_0_s_periodnum_[2] , 
        \top_code_0_s_periodnum_[1] , \top_code_0_s_periodnum_[0] }), 
        .stripnum({\s_acq_change_0_s_stripnum_[11] , 
        \s_acq_change_0_s_stripnum_[10] , 
        \s_acq_change_0_s_stripnum_[9] , 
        \s_acq_change_0_s_stripnum_[8] , 
        \s_acq_change_0_s_stripnum_[7] , 
        \s_acq_change_0_s_stripnum_[6] , 
        \s_acq_change_0_s_stripnum_[5] , 
        \s_acq_change_0_s_stripnum_[4] , 
        \s_acq_change_0_s_stripnum_[3] , 
        \s_acq_change_0_s_stripnum_[2] , 
        \s_acq_change_0_s_stripnum_[1] , 
        \s_acq_change_0_s_stripnum_[0] }), .acqnum({
        \s_acq_change_0_s_acqnum_[15] , \s_acq_change_0_s_acqnum_[14] , 
        \s_acq_change_0_s_acqnum_[13] , \s_acq_change_0_s_acqnum_[12] , 
        \s_acq_change_0_s_acqnum_[11] , \s_acq_change_0_s_acqnum_[10] , 
        \s_acq_change_0_s_acqnum_[9] , \s_acq_change_0_s_acqnum_[8] , 
        \s_acq_change_0_s_acqnum_[7] , \s_acq_change_0_s_acqnum_[6] , 
        \s_acq_change_0_s_acqnum_[5] , \s_acq_change_0_s_acqnum_[4] , 
        \s_acq_change_0_s_acqnum_[3] , \s_acq_change_0_s_acqnum_[2] , 
        \s_acq_change_0_s_acqnum_[1] , \s_acq_change_0_s_acqnum_[0] }), 
        .s_addchoice({\top_code_0_s_addchoice_[4] , 
        \top_code_0_s_addchoice_[3] , \top_code_0_s_addchoice_[2] , 
        \top_code_0_s_addchoice_[1] , \top_code_0_s_addchoice_[0] }));
    scalestate scalestate_0 (.clk_sys(GLA), .clken_p(
        timer_top_0_clk_en_scale), .rst_n(top_code_0_scale_rst), 
        .soft_d(scalestate_0_soft_d), .rt_sw(scalestate_0_rt_sw), 
        .sw_acq1(scalestate_0_sw_acq1), .sw_acq2(scalestate_0_sw_acq2), 
        .s_acq(scalestate_0_s_acq), .dds_conf(scalestate_0_dds_conf), 
        .load(top_code_0_scaleload), .pn_change(top_code_0_pn_change), 
        .inv_turn(top_code_0_inv_turn), .dump_start(
        scalestate_0_dump_start), .pluse_start(
        scalestate_0_pluse_start), .pn_out(scalestate_0_pn_out), 
        .bb_ch(net_51), .reset_out(net_45), .load_out(
        scalestate_0_load_out), .intertodsp(calcuinter), .state_over_n(
        scalestate_0_state_over_n), .dumpoff_ctr(
        scalestate_0_dumpoff_ctr), .off_test(scalestate_0_off_test), 
        .tetw_pluse(scalestate_0_tetw_pluse), .s_acq180(s_acq180), 
        .long_opentime(scalestate_0_long_opentime), .dump_sustain_ctrl(
        scalestate_0_dump_sustain_ctrl), .ne_le(scalestate_0_ne_le), 
        .timecount({\scalestate_0_timecount_[21] , 
        \scalestate_0_timecount_[20] , \scalestate_0_timecount_[19] , 
        \scalestate_0_timecount_[18] , \scalestate_0_timecount_[17] , 
        \scalestate_0_timecount_[16] , \scalestate_0_timecount_[15] , 
        \scalestate_0_timecount_[14] , \scalestate_0_timecount_[13] , 
        \scalestate_0_timecount_[12] , \scalestate_0_timecount_[11] , 
        \scalestate_0_timecount_[10] , \scalestate_0_timecount_[9] , 
        \scalestate_0_timecount_[8] , \scalestate_0_timecount_[7] , 
        \scalestate_0_timecount_[6] , \scalestate_0_timecount_[5] , 
        \scalestate_0_timecount_[4] , \scalestate_0_timecount_[3] , 
        \scalestate_0_timecount_[2] , \scalestate_0_timecount_[1] , 
        \scalestate_0_timecount_[0] }), .datain({
        \top_code_0_scaledatain_[15] , \top_code_0_scaledatain_[14] , 
        \top_code_0_scaledatain_[13] , \top_code_0_scaledatain_[12] , 
        \top_code_0_scaledatain_[11] , \top_code_0_scaledatain_[10] , 
        \top_code_0_scaledatain_[9] , \top_code_0_scaledatain_[8] , 
        \top_code_0_scaledatain_[7] , \top_code_0_scaledatain_[6] , 
        \top_code_0_scaledatain_[5] , \top_code_0_scaledatain_[4] , 
        \top_code_0_scaledatain_[3] , \top_code_0_scaledatain_[2] , 
        \top_code_0_scaledatain_[1] , \top_code_0_scaledatain_[0] }), 
        .loadchoice({\top_code_0_scalechoice_0_[4] , 
        \top_code_0_scalechoice_0_[3] , \top_code_0_scalechoice_0_[2] , 
        \top_code_0_scalechoice_0_[1] , \top_code_0_scalechoice_0_[0] })
        , .s_acqnum({\scalestate_0_s_acqnum_[15] , 
        \scalestate_0_s_acqnum_[14] , \scalestate_0_s_acqnum_[13] , 
        \scalestate_0_s_acqnum_[12] , \scalestate_0_s_acqnum_[11] , 
        \scalestate_0_s_acqnum_[10] , \scalestate_0_s_acqnum_[9] , 
        \scalestate_0_s_acqnum_[8] , \scalestate_0_s_acqnum_[7] , 
        \scalestate_0_s_acqnum_[6] , \scalestate_0_s_acqnum_[5] , 
        \scalestate_0_s_acqnum_[4] , \scalestate_0_s_acqnum_[3] , 
        \scalestate_0_s_acqnum_[2] , \scalestate_0_s_acqnum_[1] , 
        \scalestate_0_s_acqnum_[0] }), .strippluse({
        \scalestate_0_strippluse_[11] , \scalestate_0_strippluse_[10] , 
        \scalestate_0_strippluse_[9] , \scalestate_0_strippluse_[8] , 
        \scalestate_0_strippluse_[7] , \scalestate_0_strippluse_[6] , 
        \scalestate_0_strippluse_[5] , \scalestate_0_strippluse_[4] , 
        \scalestate_0_strippluse_[3] , \scalestate_0_strippluse_[2] , 
        \scalestate_0_strippluse_[1] , \scalestate_0_strippluse_[0] }));
    OR2 OR2_2 (.A(nsctrl_choice_0_dumponoff_rst), .B(net_40), .Y(
        OR2_2_Y));
    GPMI GPMI_0 (.dsp_reset(gpio), .rst_nr2(net_27), .clk(GLA), .xwe(
        xwe), .xzcs2(zcs2), .tri_ctrl(tri_ctrl), .code_en(
        GPMI_0_code_en), .xd({xd[15], xd[14], xd[13], xd[12], xd[11], 
        xd[10], xd[9], xd[8], xd[7], xd[6], xd[5], xd[4], xd[3], xd[2], 
        xd[1], xd[0]}), .datain({\Signal_Noise_Acq_0_dataout_[15] , 
        \Signal_Noise_Acq_0_dataout_[14] , 
        \Signal_Noise_Acq_0_dataout_[13] , 
        \Signal_Noise_Acq_0_dataout_[12] , 
        \Signal_Noise_Acq_0_dataout_[11] , 
        \Signal_Noise_Acq_0_dataout_[10] , 
        \Signal_Noise_Acq_0_dataout_[9] , 
        \Signal_Noise_Acq_0_dataout_[8] , 
        \Signal_Noise_Acq_0_dataout_[7] , 
        \Signal_Noise_Acq_0_dataout_[6] , 
        \Signal_Noise_Acq_0_dataout_[5] , 
        \Signal_Noise_Acq_0_dataout_[4] , 
        \Signal_Noise_Acq_0_dataout_[3] , 
        \Signal_Noise_Acq_0_dataout_[2] , 
        \Signal_Noise_Acq_0_dataout_[1] , 
        \Signal_Noise_Acq_0_dataout_[0] }), .dataout({
        \GPMI_0_dataout_[15] , \GPMI_0_dataout_[14] , 
        \GPMI_0_dataout_[13] , \GPMI_0_dataout_[12] , 
        \GPMI_0_dataout_[11] , \GPMI_0_dataout_[10] , 
        \GPMI_0_dataout_[9] , \GPMI_0_dataout_[8] , 
        \GPMI_0_dataout_[7] , \GPMI_0_dataout_[6] , 
        \GPMI_0_dataout_[5] , \GPMI_0_dataout_[4] , 
        \GPMI_0_dataout_[3] , \GPMI_0_dataout_[2] , 
        \GPMI_0_dataout_[1] , \GPMI_0_dataout_[0] }));
    
endmodule
