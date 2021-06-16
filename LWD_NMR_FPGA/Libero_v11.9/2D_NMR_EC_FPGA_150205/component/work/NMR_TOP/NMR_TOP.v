//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Fri Jun 04 09:24:11 2021
// Version: v11.9 SP6 11.9.6.7
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// NMR_TOP
module NMR_TOP(
    // Inputs
    ADC,
    OCX40MHz,
    XRD,
    ddsclkout,
    gpio,
    tri_ctrl,
    xa,
    xwe,
    zcs2,
    // Outputs
    Acq_clk,
    GLA,
    Q1Q8,
    Q2Q7,
    Q3Q6,
    Q4Q5,
    cal_out,
    calcuinter,
    ddsdata,
    ddsfqud,
    ddsreset,
    ddswclk,
    dumpoff,
    dumpon,
    interupt,
    k1,
    k2,
    pd_pulse_en,
    pulse_start,
    relay_close,
    relay_on,
    rt_sw,
    s_acq180,
    sd_acq_en,
    sigtimeup,
    soft_dump,
    sw_acq1,
    sw_acq2,
    syn_md_out,
    syn_md_tmp,
    // Inouts
    xd
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  [11:0] ADC;
input         OCX40MHz;
input         XRD;
input         ddsclkout;
input         gpio;
input         tri_ctrl;
input  [18:0] xa;
input         xwe;
input         zcs2;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output        Acq_clk;
output        GLA;
output        Q1Q8;
output        Q2Q7;
output        Q3Q6;
output        Q4Q5;
output        cal_out;
output        calcuinter;
output        ddsdata;
output        ddsfqud;
output        ddsreset;
output        ddswclk;
output        dumpoff;
output        dumpon;
output        interupt;
output        k1;
output        k2;
output        pd_pulse_en;
output        pulse_start;
output [9:0]  relay_close;
output [9:0]  relay_on;
output        rt_sw;
output        s_acq180;
output        sd_acq_en;
output        sigtimeup;
output        soft_dump;
output        sw_acq1;
output        sw_acq2;
output        syn_md_out;
output        syn_md_tmp;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  [15:0] xd;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire          Acq_clk_net_0;
wire   [11:0] ADC;
wire          bri_div_start_0;
wire          bri_dump_sw_0_dump_start;
wire          bri_dump_sw_0_dumpoff_ctr;
wire          bri_dump_sw_0_off_test;
wire          bri_dump_sw_0_phase_ctr;
wire          bri_dump_sw_0_reset_out;
wire          bri_dump_sw_0_tetw_pluse;
wire          bri_dump_sw_0_turn_delay;
wire          bri_start;
wire          cal_out_0;
wire          calcuinter_net_0;
wire          clk_4f_en;
wire          clk_4f_en_3;
wire          OCX40MHz;
wire          ClockManagement_0_clock_10khz;
wire          dds_change_0_dds_conf;
wire          dds_change_0_dds_rst;
wire          ddsclkout;
wire          ddsdata_0;
wire          ddsfqud_0;
wire          ddsreset_0;
wire          ddswclk_0;
wire          DUMP_0_dump_off;
wire          DUMP_0_dump_on;
wire          DUMP_OFF_0_dump_off;
wire          DUMP_OFF_1_dump_off;
wire          DUMP_ON_0_dump_on;
wire          dumpoff_0;
wire          dumpon_net_0;
wire          en;
wire          GLA_net_0;
wire          gpio;
wire          GPMI_0_code_en;
wire   [15:0] GPMI_0_dataout;
wire          interupt_net_0;
wire          k1_net_0;
wire          k2_net_0;
wire          n_acq_change_0_n_acq_start;
wire          n_acq_change_0_n_rst_n;
wire          net_27;
wire          net_33;
wire          net_40;
wire          net_45;
wire          net_51;
wire          noisestate_0_dumpoff_ctr;
wire          noisestate_0_dumpon_ctr;
wire          noisestate_0_n_acq;
wire          noisestate_0_rt_sw;
wire          noisestate_0_soft_d;
wire          noisestate_0_state_over_n;
wire          noisestate_0_sw_acq1;
wire          noisestate_0_sw_acq2;
wire   [19:0] noisestate_0_timecount;
wire          nsctrl_choice_0_dumpoff_ctr;
wire          nsctrl_choice_0_dumpon_ctr;
wire          nsctrl_choice_0_dumponoff_rst;
wire          nsctrl_choice_0_intertodsp;
wire          nsctrl_choice_0_rt_sw;
wire          nsctrl_choice_0_soft_d;
wire          nsctrl_choice_0_sw_acq1;
wire          nsctrl_choice_0_sw_acq2;
wire          OR2_1_Y;
wire          OR2_2_Y;
wire          PLUSE_0_bri_cycle;
wire          plusestate_0_dds_config;
wire          plusestate_0_dump_start;
wire          plusestate_0_dumpoff_ctr;
wire          plusestate_0_off_test;
wire          plusestate_0_pluse_acq;
wire          plusestate_0_pluse_start;
wire          plusestate_0_rt_sw;
wire          plusestate_0_soft_d;
wire          plusestate_0_state_over_n;
wire          plusestate_0_sw_acq1;
wire          plusestate_0_sw_acq2;
wire          plusestate_0_tetw_pluse;
wire   [19:0] plusestate_0_timecount;
wire          Q1Q8_0;
wire          Q2Q7_0;
wire          Q3Q6_0;
wire          Q4Q5_0;
wire   [9:0]  relay_close_net_0;
wire   [9:0]  relay_on_net_0;
wire          rt_sw_net_0;
wire          rt_sw_0;
wire          s_acq180_net_0;
wire   [15:0] s_acq_change_0_s_acqnum;
wire          s_acq_change_0_s_load;
wire          s_acq_change_0_s_rst;
wire   [11:0] s_acq_change_0_s_stripnum;
wire          scalestate_0_dds_conf;
wire          scalestate_0_dump_start;
wire          scalestate_0_dump_sustain_ctrl;
wire          scalestate_0_dumpoff_ctr;
wire          scalestate_0_load_out;
wire          scalestate_0_long_opentime;
wire          scalestate_0_ne_le;
wire          scalestate_0_off_test;
wire          scalestate_0_pluse_start;
wire          scalestate_0_pn_out;
wire          scalestate_0_rt_sw;
wire          scalestate_0_s_acq;
wire   [15:0] scalestate_0_s_acqnum;
wire          scalestate_0_soft_d;
wire          scalestate_0_state_over_n;
wire   [11:0] scalestate_0_strippluse;
wire          scalestate_0_sw_acq1;
wire          scalestate_0_sw_acq2;
wire          scalestate_0_tetw_pluse;
wire   [21:0] scalestate_0_timecount;
wire          scan_scale_sw_0_s_start;
wire          scanstate_0_calctrl;
wire          scanstate_0_dds_conf;
wire          scanstate_0_dumpoff_ctr;
wire          scanstate_0_dumpon_ctr;
wire          scanstate_0_rt_sw;
wire          scanstate_0_s_acq;
wire          scanstate_0_soft_d;
wire          scanstate_0_state_over_n;
wire          scanstate_0_sw_acq1;
wire          scanstate_0_sw_acq2;
wire   [19:0] scanstate_0_timecount;
wire          Signal_Noise_Acq_0_acq_clk;
wire   [15:0] Signal_Noise_Acq_0_dataout;
wire          sigtimeup_net_0;
wire          soft_dump_net_0;
wire          soft_dump_0;
wire          state1ms_choice_0_bri_cycle;
wire          state1ms_choice_0_dump_start;
wire          state1ms_choice_0_reset_out;
wire          state_1ms_0_bri_cycle;
wire          state_1ms_0_dump_start;
wire          state_1ms_0_pluse_start;
wire          state_1ms_0_reset_out;
wire          state_1ms_0_rt_sw;
wire          state_1ms_0_soft_dump;
wire   [19:0] state_1ms_0_timecount;
wire          sw_acq1_net_0;
wire          sw_acq2_net_0;
wire          syn_md_out_net_0;
wire          syn_md_tmp_net_0;
wire          timer_top_0_clk_en_noise;
wire          timer_top_0_clk_en_pluse;
wire          timer_top_0_clk_en_scale;
wire          timer_top_0_clk_en_scan;
wire          timer_top_0_clk_en_st1ms;
wire          top_code_0_acqclken;
wire   [15:0] top_code_0_bri_datain;
wire          top_code_0_bridge_load;
wire   [5:0]  top_code_0_cal_data;
wire          top_code_0_cal_load;
wire   [1:0]  top_code_0_change;
wire          top_code_0_dds_choice;
wire   [15:0] top_code_0_dds_configdata;
wire          top_code_0_dds_load;
wire   [2:0]  top_code_0_dump_cho_0;
wire          top_code_0_dump_sustain;
wire   [3:0]  top_code_0_dump_sustain_data;
wire   [11:0] top_code_0_dumpdata_0;
wire          top_code_0_dumpload;
wire   [7:0]  top_code_0_halfdata_0;
wire          top_code_0_inv_turn;
wire   [11:0] top_code_0_n_acqnum_2;
wire   [9:0]  top_code_0_n_divnum_0;
wire          top_code_0_n_load;
wire          top_code_0_n_rd_en;
wire          top_code_0_n_s_ctrl;
wire          top_code_0_noise_rst;
wire          top_code_0_noise_start;
wire   [15:0] top_code_0_noisedata;
wire          top_code_0_nstatechoice;
wire          top_code_0_nstateload;
wire   [3:0]  top_code_0_pd_pluse_choice;
wire   [15:0] top_code_0_pd_pluse_data;
wire          top_code_0_pd_pluse_load;
wire          top_code_0_pluse_lc;
wire          top_code_0_pluse_noise_ctrl;
wire          top_code_0_pluse_rst;
wire          top_code_0_pluse_scale;
wire          top_code_0_pluse_str;
wire   [15:0] top_code_0_plusedata;
wire          top_code_0_pluseload;
wire          top_code_0_pn_change;
wire          top_code_0_RAM_Rd_rst;
wire   [15:0] top_code_0_s_acqnum_2;
wire   [4:0]  top_code_0_s_addchoice;
wire          top_code_0_s_load;
wire   [3:0]  top_code_0_s_periodnum;
wire          top_code_0_scale_rst;
wire          top_code_0_scale_start;
wire   [4:0]  top_code_0_scalechoice_0;
wire   [15:0] top_code_0_scaledatain;
wire   [5:0]  top_code_0_scaleddsdiv;
wire          top_code_0_scaleload;
wire          top_code_0_scan_start;
wire          top_code_0_scanchoice;
wire   [15:0] top_code_0_scandata;
wire          top_code_0_scanload;
wire   [3:0]  top_code_0_sd_sacq_choice;
wire   [15:0] top_code_0_sd_sacq_data;
wire          top_code_0_sd_sacq_load;
wire          top_code_0_sigrst;
wire   [15:0] top_code_0_sigtimedata;
wire   [15:0] top_code_0_state_1ms_data;
wire   [3:0]  top_code_0_state_1ms_lc;
wire          top_code_0_state_1ms_load;
wire          top_code_0_state_1ms_rst_n;
wire          top_code_0_state_1ms_start;
wire          tri_ctrl;
wire   [18:0] xa;
wire   [15:0] xd;
wire          XRD;
wire          xwe;
wire          zcs2;
wire          ddsfqud_0_net_0;
wire          ddsreset_0_net_0;
wire          ddswclk_0_net_0;
wire          cal_out_0_net_0;
wire          ddsdata_0_net_0;
wire          interupt_net_1;
wire          rt_sw_0_net_0;
wire          soft_dump_0_net_0;
wire          sw_acq1_net_1;
wire          sw_acq2_net_1;
wire          dumpon_net_1;
wire          dumpoff_0_net_0;
wire          Q1Q8_0_net_0;
wire          Q3Q6_0_net_0;
wire          Q4Q5_0_net_0;
wire          Q2Q7_0_net_0;
wire          calcuinter_net_1;
wire          sigtimeup_net_1;
wire          k1_net_1;
wire          k2_net_1;
wire          bri_start_net_0;
wire          clk_4f_en_3_net_0;
wire          Acq_clk_net_1;
wire          en_net_0;
wire          s_acq180_net_1;
wire          GLA_net_1;
wire          syn_md_out_net_1;
wire          syn_md_tmp_net_1;
wire   [9:0]  relay_on_net_1;
wire   [9:0]  relay_close_net_1;
wire   [4:0]  start_net_0;
wire   [3:0]  state_over_in_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          VCC_net;
wire   [11:0] s_stripnumin1_const_net_0;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net                   = 1'b1;
assign s_stripnumin1_const_net_0 = 12'h000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign ddsfqud_0_net_0   = ddsfqud_0;
assign ddsfqud           = ddsfqud_0_net_0;
assign ddsreset_0_net_0  = ddsreset_0;
assign ddsreset          = ddsreset_0_net_0;
assign ddswclk_0_net_0   = ddswclk_0;
assign ddswclk           = ddswclk_0_net_0;
assign cal_out_0_net_0   = cal_out_0;
assign cal_out           = cal_out_0_net_0;
assign ddsdata_0_net_0   = ddsdata_0;
assign ddsdata           = ddsdata_0_net_0;
assign interupt_net_1    = interupt_net_0;
assign interupt          = interupt_net_1;
assign rt_sw_0_net_0     = rt_sw_0;
assign rt_sw             = rt_sw_0_net_0;
assign soft_dump_0_net_0 = soft_dump_0;
assign soft_dump         = soft_dump_0_net_0;
assign sw_acq1_net_1     = sw_acq1_net_0;
assign sw_acq1           = sw_acq1_net_1;
assign sw_acq2_net_1     = sw_acq2_net_0;
assign sw_acq2           = sw_acq2_net_1;
assign dumpon_net_1      = dumpon_net_0;
assign dumpon            = dumpon_net_1;
assign dumpoff_0_net_0   = dumpoff_0;
assign dumpoff           = dumpoff_0_net_0;
assign Q1Q8_0_net_0      = Q1Q8_0;
assign Q1Q8              = Q1Q8_0_net_0;
assign Q3Q6_0_net_0      = Q3Q6_0;
assign Q3Q6              = Q3Q6_0_net_0;
assign Q4Q5_0_net_0      = Q4Q5_0;
assign Q4Q5              = Q4Q5_0_net_0;
assign Q2Q7_0_net_0      = Q2Q7_0;
assign Q2Q7              = Q2Q7_0_net_0;
assign calcuinter_net_1  = calcuinter_net_0;
assign calcuinter        = calcuinter_net_1;
assign sigtimeup_net_1   = sigtimeup_net_0;
assign sigtimeup         = sigtimeup_net_1;
assign k1_net_1          = k1_net_0;
assign k1                = k1_net_1;
assign k2_net_1          = k2_net_0;
assign k2                = k2_net_1;
assign bri_start_net_0   = bri_start;
assign pulse_start       = bri_start_net_0;
assign clk_4f_en_3_net_0 = clk_4f_en_3;
assign pd_pulse_en       = clk_4f_en_3_net_0;
assign Acq_clk_net_1     = Acq_clk_net_0;
assign Acq_clk           = Acq_clk_net_1;
assign en_net_0          = en;
assign sd_acq_en         = en_net_0;
assign s_acq180_net_1    = s_acq180_net_0;
assign s_acq180          = s_acq180_net_1;
assign GLA_net_1         = GLA_net_0;
assign GLA               = GLA_net_1;
assign syn_md_out_net_1  = syn_md_out_net_0;
assign syn_md_out        = syn_md_out_net_1;
assign syn_md_tmp_net_1  = syn_md_tmp_net_0;
assign syn_md_tmp        = syn_md_tmp_net_1;
assign relay_on_net_1    = relay_on_net_0;
assign relay_on[9:0]     = relay_on_net_1;
assign relay_close_net_1 = relay_close_net_0;
assign relay_close[9:0]  = relay_close_net_1;
//--------------------------------------------------------------------
// Concatenation assignments
//--------------------------------------------------------------------
assign start_net_0         = { top_code_0_state_1ms_start , top_code_0_pluse_str , top_code_0_noise_start , top_code_0_scan_start , top_code_0_scale_start };
assign state_over_in_net_0 = { plusestate_0_state_over_n , noisestate_0_state_over_n , scanstate_0_state_over_n , scalestate_0_state_over_n };
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------AND2
AND2 AND2_0(
        // Inputs
        .A ( Signal_Noise_Acq_0_acq_clk ),
        .B ( top_code_0_acqclken ),
        // Outputs
        .Y ( Acq_clk_net_0 ) 
        );

//--------bri_dump_sw
bri_dump_sw bri_dump_sw_0(
        // Inputs
        .rst_n        ( net_27 ),
        .clk_sys      ( GLA_net_0 ),
        .change       ( top_code_0_pluse_scale ),
        .pluse_start1 ( scalestate_0_pluse_start ),
        .pluse_start2 ( plusestate_0_pluse_start ),
        .off_test1    ( scalestate_0_off_test ),
        .off_test2    ( plusestate_0_off_test ),
        .dump_start1  ( scalestate_0_dump_start ),
        .dump_start2  ( plusestate_0_dump_start ),
        .phase_ctr1   ( scalestate_0_pn_out ),
        .phase_ctr2   ( top_code_0_pn_change ),
        .reset_out1   ( net_45 ),
        .reset_out2   ( top_code_0_pluse_rst ),
        .dumpoff_ctr1 ( scalestate_0_dumpoff_ctr ),
        .dumpoff_ctr2 ( plusestate_0_dumpoff_ctr ),
        .tetw_pluse1  ( scalestate_0_tetw_pluse ),
        .tetw_pluse2  ( plusestate_0_tetw_pluse ),
        .turn_delay1  ( scalestate_0_ne_le ),
        .turn_delay2  ( VCC_net ),
        // Outputs
        .pluse_start  ( bri_start ),
        .off_test     ( bri_dump_sw_0_off_test ),
        .dump_start   ( bri_dump_sw_0_dump_start ),
        .phase_ctr    ( bri_dump_sw_0_phase_ctr ),
        .reset_out    ( bri_dump_sw_0_reset_out ),
        .dumpoff_ctr  ( bri_dump_sw_0_dumpoff_ctr ),
        .tetw_pluse   ( bri_dump_sw_0_tetw_pluse ),
        .turn_delay   ( bri_dump_sw_0_turn_delay ) 
        );

//--------bridge_div
bridge_div bridge_div_0(
        // Inputs
        .bri_div_start ( clk_4f_en_3 ),
        .rst_n         ( bri_dump_sw_0_reset_out ),
        .clk_sys       ( GLA_net_0 ),
        .clk_dds       ( ddsclkout ),
        .load          ( top_code_0_bridge_load ),
        .divcount      ( top_code_0_scaleddsdiv ),
        // Outputs
        .clk_4f_en     ( clk_4f_en ) 
        );

//--------CAL
CAL CAL_0(
        // Inputs
        .clk_sys   ( GLA_net_0 ),
        .rst_n     ( net_33 ),
        .cal_start ( scanstate_0_calctrl ),
        .clk_dds   ( ddsclkout ),
        .cal_load  ( top_code_0_cal_load ),
        .cal_para  ( top_code_0_cal_data ),
        // Outputs
        .cal       ( cal_out_0 ) 
        );

//--------ClockManagement
ClockManagement ClockManagement_0(
        // Inputs
        .OCX40MHz    ( OCX40MHz ),
        .rst_n       ( net_27 ),
        .start       ( top_code_0_sigrst ),
        .timer_para  ( top_code_0_sigtimedata ),
        // Outputs
        .GLA         ( GLA_net_0 ),
        .timeup      ( sigtimeup_net_0 ),
        .clock_10khz ( ClockManagement_0_clock_10khz ) 
        );

//--------DDS
DDS DDS_0(
        // Inputs
        .dds_load    ( top_code_0_dds_load ),
        .dds_choice  ( top_code_0_dds_choice ),
        .clk_sys     ( GLA_net_0 ),
        .rst_n       ( dds_change_0_dds_rst ),
        .state_start ( dds_change_0_dds_conf ),
        .dds_para    ( top_code_0_dds_configdata ),
        // Outputs
        .reset       ( ddsreset_0 ),
        .fq_ud       ( ddsfqud_0 ),
        .w_clk       ( ddswclk_0 ),
        .data        ( ddsdata_0 ) 
        );

//--------dds_change
dds_change dds_change_0(
        // Inputs
        .rst_n       ( net_27 ),
        .clk_sys     ( GLA_net_0 ),
        .ddsrstin1   ( net_33 ),
        .ddsrstin2   ( net_45 ),
        .ddsrstin3   ( top_code_0_pluse_rst ),
        .dds_confin1 ( scanstate_0_dds_conf ),
        .dds_confin2 ( scalestate_0_dds_conf ),
        .dds_confin3 ( plusestate_0_dds_config ),
        .change      ( top_code_0_change ),
        // Outputs
        .dds_rst     ( dds_change_0_dds_rst ),
        .dds_conf    ( dds_change_0_dds_conf ) 
        );

//--------DSTimer
DSTimer DSTimer_0(
        // Inputs
        .clk_sys           ( GLA_net_0 ),
        .dump_sustain      ( top_code_0_dump_sustain ),
        .rst_n             ( top_code_0_dump_sustain ),
        .state_start       ( scalestate_0_dump_sustain_ctrl ),
        .clk_10k           ( ClockManagement_0_clock_10khz ),
        .dump_sustain_data ( top_code_0_dump_sustain_data ),
        // Outputs
        .start             ( net_40 ) 
        );

//--------DUMP
DUMP DUMP_0(
        // Inputs
        .rst_n       ( state1ms_choice_0_reset_out ),
        .state_start ( state1ms_choice_0_dump_start ),
        .clk_sys     ( GLA_net_0 ),
        .dump_load   ( top_code_0_dumpload ),
        .bri_cycle   ( state1ms_choice_0_bri_cycle ),
        .pluse_start ( bri_div_start_0 ),
        .dump_choice ( top_code_0_dump_cho_0 ),
        .dump_para   ( top_code_0_dumpdata_0 ),
        // Outputs
        .dump_off    ( DUMP_0_dump_off ),
        .dump_on     ( DUMP_0_dump_on ) 
        );

//--------DUMP_OFF
DUMP_OFF DUMP_OFF_0(
        // Inputs
        .rst_n       ( bri_dump_sw_0_reset_out ),
        .state_start ( bri_dump_sw_0_dumpoff_ctr ),
        .clk_sys     ( GLA_net_0 ),
        // Outputs
        .dump_off    ( DUMP_OFF_0_dump_off ) 
        );

//--------DUMP_OFF
DUMP_OFF DUMP_OFF_1(
        // Inputs
        .rst_n       ( nsctrl_choice_0_dumponoff_rst ),
        .state_start ( nsctrl_choice_0_dumpoff_ctr ),
        .clk_sys     ( GLA_net_0 ),
        // Outputs
        .dump_off    ( DUMP_OFF_1_dump_off ) 
        );

//--------DUMP_ON
DUMP_ON DUMP_ON_0(
        // Inputs
        .state_start ( OR2_1_Y ),
        .rst_n       ( OR2_2_Y ),
        .clk_sys     ( GLA_net_0 ),
        // Outputs
        .dump_on     ( DUMP_ON_0_dump_on ) 
        );

//--------GPMI
GPMI GPMI_0(
        // Inputs
        .dsp_reset ( gpio ),
        .clk       ( GLA_net_0 ),
        .xwe       ( xwe ),
        .xzcs2     ( zcs2 ),
        .tri_ctrl  ( tri_ctrl ),
        .datain    ( Signal_Noise_Acq_0_dataout ),
        // Outputs
        .rst_nr2   ( net_27 ),
        .code_en   ( GPMI_0_code_en ),
        .dataout   ( GPMI_0_dataout ),
        // Inouts
        .xd        ( xd ) 
        );

//--------n_pluse_acq
n_pluse_acq n_acq_change_0(
        // Inputs
        .rst_n          ( net_27 ),
        .clk_sys        ( GLA_net_0 ),
        .change         ( top_code_0_pluse_noise_ctrl ),
        .n_acq_startin1 ( noisestate_0_n_acq ),
        .n_acq_startin2 ( plusestate_0_pluse_acq ),
        .n_rstin1_n     ( top_code_0_noise_rst ),
        .n_rstin2_n     ( top_code_0_pluse_rst ),
        // Outputs
        .n_acq_start    ( n_acq_change_0_n_acq_start ),
        .n_rst_n        ( n_acq_change_0_n_rst_n ) 
        );

//--------noisestate
noisestate noisestate_0(
        // Inputs
        .clk_sys      ( GLA_net_0 ),
        .clken_p      ( timer_top_0_clk_en_noise ),
        .rst_n        ( top_code_0_noise_rst ),
        .nload        ( top_code_0_nstateload ),
        .nchoice      ( top_code_0_nstatechoice ),
        .ndatain      ( top_code_0_noisedata ),
        // Outputs
        .dumpon_ctr   ( noisestate_0_dumpon_ctr ),
        .dumpoff_ctr  ( noisestate_0_dumpoff_ctr ),
        .soft_d       ( noisestate_0_soft_d ),
        .rt_sw        ( noisestate_0_rt_sw ),
        .sw_acq1      ( noisestate_0_sw_acq1 ),
        .sw_acq2      ( noisestate_0_sw_acq2 ),
        .n_acq        ( noisestate_0_n_acq ),
        .state_over_n ( noisestate_0_state_over_n ),
        .timecount    ( noisestate_0_timecount ) 
        );

//--------nsctrl_choice
nsctrl_choice nsctrl_choice_0(
        // Inputs
        .rst_n           ( net_27 ),
        .clk_sys         ( GLA_net_0 ),
        .change          ( top_code_0_n_s_ctrl ),
        .soft_d_s        ( scanstate_0_soft_d ),
        .rt_sw_s         ( scanstate_0_rt_sw ),
        .sw_acq1_s       ( scanstate_0_sw_acq1 ),
        .sw_acq2_s       ( scanstate_0_sw_acq2 ),
        .inter_s         ( scanstate_0_state_over_n ),
        .dumpon_ctr_s    ( scanstate_0_dumpon_ctr ),
        .dumpoff_ctr_s   ( scanstate_0_dumpoff_ctr ),
        .dumponoff_rst_s ( net_33 ),
        .soft_d_n        ( noisestate_0_soft_d ),
        .rt_sw_n         ( noisestate_0_rt_sw ),
        .sw_acq1_n       ( noisestate_0_sw_acq1 ),
        .sw_acq2_n       ( noisestate_0_sw_acq2 ),
        .inter_n         ( noisestate_0_state_over_n ),
        .dumpon_ctr_n    ( noisestate_0_dumpon_ctr ),
        .dumpoff_ctr_n   ( noisestate_0_dumpoff_ctr ),
        .dumponoff_rst_n ( top_code_0_noise_rst ),
        // Outputs
        .soft_d          ( nsctrl_choice_0_soft_d ),
        .rt_sw           ( nsctrl_choice_0_rt_sw ),
        .sw_acq1         ( nsctrl_choice_0_sw_acq1 ),
        .sw_acq2         ( nsctrl_choice_0_sw_acq2 ),
        .intertodsp      ( nsctrl_choice_0_intertodsp ),
        .dumpon_ctr      ( nsctrl_choice_0_dumpon_ctr ),
        .dumpoff_ctr     ( nsctrl_choice_0_dumpoff_ctr ),
        .dumponoff_rst   ( nsctrl_choice_0_dumponoff_rst ) 
        );

//--------OR2
OR2 OR2_0(
        // Inputs
        .A ( DUMP_0_dump_on ),
        .B ( DUMP_ON_0_dump_on ),
        // Outputs
        .Y ( dumpon_net_0 ) 
        );

//--------OR2
OR2 OR2_1(
        // Inputs
        .A ( nsctrl_choice_0_dumpon_ctr ),
        .B ( net_40 ),
        // Outputs
        .Y ( OR2_1_Y ) 
        );

//--------OR2
OR2 OR2_2(
        // Inputs
        .A ( nsctrl_choice_0_dumponoff_rst ),
        .B ( net_40 ),
        // Outputs
        .Y ( OR2_2_Y ) 
        );

//--------OR3
OR3 OR3_0(
        // Inputs
        .A ( DUMP_OFF_1_dump_off ),
        .B ( DUMP_OFF_0_dump_off ),
        .C ( DUMP_0_dump_off ),
        // Outputs
        .Y ( dumpoff_0 ) 
        );

//--------pd_pluse_top
pd_pluse_top pd_pluse_top_0(
        // Inputs
        .dds             ( ddsclkout ),
        .rst_n           ( net_27 ),
        .pluse_start     ( bri_start ),
        .clk_sys         ( GLA_net_0 ),
        .pd_pluse_load   ( top_code_0_pd_pluse_load ),
        .bb_ch           ( net_51 ),
        .tetw_pluse      ( bri_dump_sw_0_tetw_pluse ),
        .pd_pluse_choice ( top_code_0_pd_pluse_choice ),
        .pd_pluse_data   ( top_code_0_pd_pluse_data ),
        // Outputs
        .en              ( clk_4f_en_3 ) 
        );

//--------PLUSE
PLUSE PLUSE_0(
        // Inputs
        .state_start ( bri_start ),
        .rst_n       ( bri_dump_sw_0_reset_out ),
        .phase       ( bri_dump_sw_0_phase_ctr ),
        .quar_delay  ( net_51 ),
        .clk_sys     ( GLA_net_0 ),
        .pluse_load  ( top_code_0_bridge_load ),
        .clk_dds     ( ddsclkout ),
        .clk_4f_en   ( clk_4f_en ),
        .turn_delay  ( bri_dump_sw_0_turn_delay ),
        .qq_para     ( top_code_0_bri_datain ),
        .bri_para    ( top_code_0_halfdata_0 ),
        // Outputs
        .bri_cycle   ( PLUSE_0_bri_cycle ),
        .Q1Q8        ( Q1Q8_0 ),
        .Q3Q6        ( Q3Q6_0 ),
        .Q4Q5        ( Q4Q5_0 ),
        .Q2Q7        ( Q2Q7_0 ),
        .down        (  ),
        .up          (  ) 
        );

//--------plusestate
plusestate plusestate_0(
        // Inputs
        .clk_sys      ( GLA_net_0 ),
        .clken_p      ( timer_top_0_clk_en_pluse ),
        .rst_n        ( top_code_0_pluse_rst ),
        .load         ( top_code_0_pluseload ),
        .loadchoice   ( top_code_0_pluse_lc ),
        .datain       ( top_code_0_plusedata ),
        // Outputs
        .soft_d       ( plusestate_0_soft_d ),
        .rt_sw        ( plusestate_0_rt_sw ),
        .sw_acq1      ( plusestate_0_sw_acq1 ),
        .sw_acq2      ( plusestate_0_sw_acq2 ),
        .pluse_acq    ( plusestate_0_pluse_acq ),
        .pluse_start  ( plusestate_0_pluse_start ),
        .off_test     ( plusestate_0_off_test ),
        .dump_start   ( plusestate_0_dump_start ),
        .state_over_n ( plusestate_0_state_over_n ),
        .dds_config   ( plusestate_0_dds_config ),
        .dumpoff_ctr  ( plusestate_0_dumpoff_ctr ),
        .tetw_pluse   ( plusestate_0_tetw_pluse ),
        .timecount    ( plusestate_0_timecount ) 
        );

//--------s_acq_change
s_acq_change s_acq_change_0(
        // Inputs
        .rst_n         ( net_27 ),
        .clk_sys       ( GLA_net_0 ),
        .s_loadin1     ( top_code_0_s_load ),
        .s_loadin2     ( scalestate_0_load_out ),
        .s_rstin1      ( net_33 ),
        .s_rstin2      ( net_45 ),
        .change        ( top_code_0_change ),
        .s_acqnumin1   ( top_code_0_s_acqnum_2 ),
        .s_acqnumin2   ( scalestate_0_s_acqnum ),
        .s_stripnumin1 ( s_stripnumin1_const_net_0 ),
        .s_stripnumin2 ( scalestate_0_strippluse ),
        // Outputs
        .s_load        ( s_acq_change_0_s_load ),
        .s_rst         ( s_acq_change_0_s_rst ),
        .s_acqnum      ( s_acq_change_0_s_acqnum ),
        .s_stripnum    ( s_acq_change_0_s_stripnum ) 
        );

//--------scalestate
scalestate scalestate_0(
        // Inputs
        .clk_sys           ( GLA_net_0 ),
        .clken_p           ( timer_top_0_clk_en_scale ),
        .rst_n             ( top_code_0_scale_rst ),
        .load              ( top_code_0_scaleload ),
        .pn_change         ( top_code_0_pn_change ),
        .inv_turn          ( top_code_0_inv_turn ),
        .datain            ( top_code_0_scaledatain ),
        .loadchoice        ( top_code_0_scalechoice_0 ),
        // Outputs
        .soft_d            ( scalestate_0_soft_d ),
        .rt_sw             ( scalestate_0_rt_sw ),
        .sw_acq1           ( scalestate_0_sw_acq1 ),
        .sw_acq2           ( scalestate_0_sw_acq2 ),
        .s_acq             ( scalestate_0_s_acq ),
        .dds_conf          ( scalestate_0_dds_conf ),
        .dump_start        ( scalestate_0_dump_start ),
        .pluse_start       ( scalestate_0_pluse_start ),
        .pn_out            ( scalestate_0_pn_out ),
        .bb_ch             ( net_51 ),
        .reset_out         ( net_45 ),
        .load_out          ( scalestate_0_load_out ),
        .intertodsp        ( calcuinter_net_0 ),
        .state_over_n      ( scalestate_0_state_over_n ),
        .dumpoff_ctr       ( scalestate_0_dumpoff_ctr ),
        .off_test          ( scalestate_0_off_test ),
        .tetw_pluse        ( scalestate_0_tetw_pluse ),
        .s_acq180          ( s_acq180_net_0 ),
        .long_opentime     ( scalestate_0_long_opentime ),
        .dump_sustain_ctrl ( scalestate_0_dump_sustain_ctrl ),
        .ne_le             ( scalestate_0_ne_le ),
        .timecount         ( scalestate_0_timecount ),
        .s_acqnum          ( scalestate_0_s_acqnum ),
        .strippluse        ( scalestate_0_strippluse ) 
        );

//--------scan_scale_sw
scan_scale_sw scan_scale_sw_0(
        // Inputs
        .rst_n      ( net_27 ),
        .dds        ( ddsclkout ),
        .s_startin1 ( scanstate_0_s_acq ),
        .s_startin2 ( en ),
        .change     ( top_code_0_change ),
        // Outputs
        .s_start    ( scan_scale_sw_0_s_start ) 
        );

//--------scanstate
scanstate scanstate_0(
        // Inputs
        .clk_sys      ( GLA_net_0 ),
        .clken_p      ( timer_top_0_clk_en_scan ),
        .rst_n        ( net_33 ),
        .scanload     ( top_code_0_scanload ),
        .scanchoice   ( top_code_0_scanchoice ),
        .datain       ( top_code_0_scandata ),
        // Outputs
        .dumpon_ctr   ( scanstate_0_dumpon_ctr ),
        .dumpoff_ctr  ( scanstate_0_dumpoff_ctr ),
        .soft_d       ( scanstate_0_soft_d ),
        .rt_sw        ( scanstate_0_rt_sw ),
        .sw_acq1      ( scanstate_0_sw_acq1 ),
        .sw_acq2      ( scanstate_0_sw_acq2 ),
        .s_acq        ( scanstate_0_s_acq ),
        .dds_conf     ( scanstate_0_dds_conf ),
        .calctrl      ( scanstate_0_calctrl ),
        .state_over_n ( scanstate_0_state_over_n ),
        .resetout     (  ),
        .timecount    ( scanstate_0_timecount ) 
        );

//--------sd_acq_top
sd_acq_top sd_acq_top_0(
        // Inputs
        .dds            ( ddsclkout ),
        .rst_n          ( net_27 ),
        .s_acq1         ( scalestate_0_s_acq ),
        .clk_sys        ( GLA_net_0 ),
        .sd_sacq_load   ( top_code_0_sd_sacq_load ),
        .bb_ch          ( net_51 ),
        .s_acq180       ( s_acq180_net_0 ),
        .long_opentime  ( scalestate_0_long_opentime ),
        .sd_sacq_choice ( top_code_0_sd_sacq_choice ),
        .sd_sacq_data   ( top_code_0_sd_sacq_data ),
        // Outputs
        .en             ( en ) 
        );

//--------Signal_Noise_Acq
Signal_Noise_Acq Signal_Noise_Acq_0(
        // Inputs
        .clk_sys        ( GLA_net_0 ),
        .clk_dds        ( ddsclkout ),
        .n_s_ctrl       ( top_code_0_n_s_ctrl ),
        .n_reset        ( n_acq_change_0_n_rst_n ),
        .noise_load     ( top_code_0_n_load ),
        .RAM_RDaddr_rst ( top_code_0_RAM_Rd_rst ),
        .RAM_RD_EN      ( top_code_0_n_rd_en ),
        .RAM_WT_EN      ( n_acq_change_0_n_acq_start ),
        .XRD            ( XRD ),
        .signal_load    ( s_acq_change_0_s_load ),
        .s_reset        ( s_acq_change_0_s_rst ),
        .s_acq_en       ( scan_scale_sw_0_s_start ),
        .adcdata        ( ADC ),
        .n_acqnum       ( top_code_0_n_acqnum_2 ),
        .n_divnum       ( top_code_0_n_divnum_0 ),
        .s_periodnum    ( top_code_0_s_periodnum ),
        .stripnum       ( s_acq_change_0_s_stripnum ),
        .acqnum         ( s_acq_change_0_s_acqnum ),
        .s_addchoice    ( top_code_0_s_addchoice ),
        // Outputs
        .acq_clk        ( Signal_Noise_Acq_0_acq_clk ),
        .dataout        ( Signal_Noise_Acq_0_dataout ) 
        );

//--------state1ms_choice
state1ms_choice state1ms_choice_0(
        // Inputs
        .rst_n        ( net_27 ),
        .clk_sys      ( GLA_net_0 ),
        .change       ( top_code_0_state_1ms_start ),
        .pluse_start1 ( state_1ms_0_pluse_start ),
        .pluse_start2 ( bri_dump_sw_0_off_test ),
        .dump_start1  ( state_1ms_0_dump_start ),
        .dump_start2  ( bri_dump_sw_0_dump_start ),
        .reset_out1   ( state_1ms_0_reset_out ),
        .reset_out2   ( bri_dump_sw_0_reset_out ),
        .bri_cycle1   ( state_1ms_0_bri_cycle ),
        .bri_cycle2   ( PLUSE_0_bri_cycle ),
        .rt_sw1       ( state_1ms_0_rt_sw ),
        .rt_sw2       ( rt_sw_net_0 ),
        .soft_dump1   ( state_1ms_0_soft_dump ),
        .soft_dump2   ( soft_dump_net_0 ),
        // Outputs
        .pluse_start  ( bri_div_start_0 ),
        .dump_start   ( state1ms_choice_0_dump_start ),
        .reset_out    ( state1ms_choice_0_reset_out ),
        .bri_cycle    ( state1ms_choice_0_bri_cycle ),
        .rt_sw        ( rt_sw_0 ),
        .soft_dump    ( soft_dump_0 ) 
        );

//--------state_1ms
state_1ms state_1ms_0(
        // Inputs
        .clk_sys     ( GLA_net_0 ),
        .clken_p     ( timer_top_0_clk_en_st1ms ),
        .rst_n       ( top_code_0_state_1ms_rst_n ),
        .load        ( top_code_0_state_1ms_load ),
        .loadchoice  ( top_code_0_state_1ms_lc ),
        .datain      ( top_code_0_state_1ms_data ),
        // Outputs
        .reset_out   ( state_1ms_0_reset_out ),
        .dump_start  ( state_1ms_0_dump_start ),
        .pluse_start ( state_1ms_0_pluse_start ),
        .bri_cycle   ( state_1ms_0_bri_cycle ),
        .rt_sw       ( state_1ms_0_rt_sw ),
        .soft_dump   ( state_1ms_0_soft_dump ),
        .timecount   ( state_1ms_0_timecount ) 
        );

//--------syn_md_module
syn_md_module syn_md_module_1(
        // Inputs
        .soft_d     ( scalestate_0_soft_d ),
        .rt_sw      ( scalestate_0_rt_sw ),
        .sw1        ( scalestate_0_sw_acq1 ),
        .sw2        ( scalestate_0_sw_acq2 ),
        .rst_n      ( top_code_0_scale_rst ),
        .clkin      ( GLA_net_0 ),
        // Outputs
        .syn_md_out ( syn_md_out_net_0 ),
        .syn_md_tmp ( syn_md_tmp_net_0 ) 
        );

//--------timer_top
timer_top timer_top_0(
        // Inputs
        .clk_sys          ( GLA_net_0 ),
        .rst_n            ( net_27 ),
        .datain_state_1ms ( state_1ms_0_timecount ),
        .datain_pluse     ( plusestate_0_timecount ),
        .datain_scale     ( scalestate_0_timecount ),
        .datain_scan      ( scanstate_0_timecount ),
        .datain_noise     ( noisestate_0_timecount ),
        .start            ( start_net_0 ),
        .state_over_in    ( state_over_in_net_0 ),
        // Outputs
        .clk_en_scan      ( timer_top_0_clk_en_scan ),
        .clk_en_st1ms     ( timer_top_0_clk_en_st1ms ),
        .clk_en_pluse     ( timer_top_0_clk_en_pluse ),
        .clk_en_scale     ( timer_top_0_clk_en_scale ),
        .clk_en_noise     ( timer_top_0_clk_en_noise ) 
        );

//--------top_code
top_code top_code_0(
        // Inputs
        .rst_n             ( net_27 ),
        .clk_sys           ( GLA_net_0 ),
        .code_en           ( GPMI_0_code_en ),
        .xa                ( xa ),
        .xdata             ( GPMI_0_dataout ),
        // Outputs
        .scan_rst          ( net_33 ),
        .scan_start        ( top_code_0_scan_start ),
        .noise_rst         ( top_code_0_noise_rst ),
        .noise_start       ( top_code_0_noise_start ),
        .dds_load          ( top_code_0_dds_load ),
        .dds_choice        ( top_code_0_dds_choice ),
        .cal_load          ( top_code_0_cal_load ),
        .s_load            ( top_code_0_s_load ),
        .scale_rst         ( top_code_0_scale_rst ),
        .scale_start       ( top_code_0_scale_start ),
        .scaleload         ( top_code_0_scaleload ),
        .bridge_load       ( top_code_0_bridge_load ),
        .pn_change         ( top_code_0_pn_change ),
        .dumpload          ( top_code_0_dumpload ),
        .pluse_noise_ctrl  ( top_code_0_pluse_noise_ctrl ),
        .pluse_scale       ( top_code_0_pluse_scale ),
        .pluse_str         ( top_code_0_pluse_str ),
        .pluse_rst         ( top_code_0_pluse_rst ),
        .pluseload         ( top_code_0_pluseload ),
        .pluse_lc          ( top_code_0_pluse_lc ),
        .sigrst            ( top_code_0_sigrst ),
        .scanchoice        ( top_code_0_scanchoice ),
        .scanload          ( top_code_0_scanload ),
        .nstateload        ( top_code_0_nstateload ),
        .nstatechoice      ( top_code_0_nstatechoice ),
        .acqclken          ( top_code_0_acqclken ),
        .k1                ( k1_net_0 ),
        .k2                ( k2_net_0 ),
        .state_1ms_rst_n   ( top_code_0_state_1ms_rst_n ),
        .state_1ms_start   ( top_code_0_state_1ms_start ),
        .state_1ms_load    ( top_code_0_state_1ms_load ),
        .n_load            ( top_code_0_n_load ),
        .n_s_ctrl          ( top_code_0_n_s_ctrl ),
        .sd_sacq_load      ( top_code_0_sd_sacq_load ),
        .pd_pluse_load     ( top_code_0_pd_pluse_load ),
        .RAM_Rd_rst        ( top_code_0_RAM_Rd_rst ),
        .n_rd_en           ( top_code_0_n_rd_en ),
        .dump_sustain      ( top_code_0_dump_sustain ),
        .inv_turn          ( top_code_0_inv_turn ),
        .dds_configdata    ( top_code_0_dds_configdata ),
        .cal_data          ( top_code_0_cal_data ),
        .s_acqnum          ( top_code_0_s_acqnum_2 ),
        .change            ( top_code_0_change ),
        .scaledatain       ( top_code_0_scaledatain ),
        .scalechoice       ( top_code_0_scalechoice_0 ),
        .bri_datain        ( top_code_0_bri_datain ),
        .halfdata          ( top_code_0_halfdata_0 ),
        .dump_cho          ( top_code_0_dump_cho_0 ),
        .dumpdata          ( top_code_0_dumpdata_0 ),
        .scaleddsdiv       ( top_code_0_scaleddsdiv ),
        .plusedata         ( top_code_0_plusedata ),
        .relay_on          ( relay_on_net_0 ),
        .relay_close       ( relay_close_net_0 ),
        .sigtimedata       ( top_code_0_sigtimedata ),
        .scandata          ( top_code_0_scandata ),
        .noisedata         ( top_code_0_noisedata ),
        .state_1ms_lc      ( top_code_0_state_1ms_lc ),
        .state_1ms_data    ( top_code_0_state_1ms_data ),
        .n_divnum          ( top_code_0_n_divnum_0 ),
        .s_periodnum       ( top_code_0_s_periodnum ),
        .n_acqnum          ( top_code_0_n_acqnum_2 ),
        .sd_sacq_choice    ( top_code_0_sd_sacq_choice ),
        .sd_sacq_data      ( top_code_0_sd_sacq_data ),
        .pd_pluse_choice   ( top_code_0_pd_pluse_choice ),
        .pd_pluse_data     ( top_code_0_pd_pluse_data ),
        .s_addchoice       ( top_code_0_s_addchoice ),
        .dump_sustain_data ( top_code_0_dump_sustain_data ) 
        );

//--------topctrlchange
topctrlchange topctrlchange_0(
        // Inputs
        .rst_n      ( net_27 ),
        .clk_sys    ( GLA_net_0 ),
        .interin1   ( nsctrl_choice_0_intertodsp ),
        .interin2   ( scalestate_0_state_over_n ),
        .interin3   ( plusestate_0_state_over_n ),
        .rt_swin1   ( nsctrl_choice_0_rt_sw ),
        .rt_swin2   ( scalestate_0_rt_sw ),
        .rt_swin3   ( plusestate_0_rt_sw ),
        .s_dumpin1  ( nsctrl_choice_0_soft_d ),
        .s_dumpin2  ( scalestate_0_soft_d ),
        .s_dumpin3  ( plusestate_0_soft_d ),
        .sw_acq1in1 ( nsctrl_choice_0_sw_acq1 ),
        .sw_acq1in2 ( scalestate_0_sw_acq1 ),
        .sw_acq1in3 ( plusestate_0_sw_acq1 ),
        .sw_acq2in1 ( nsctrl_choice_0_sw_acq2 ),
        .sw_acq2in2 ( scalestate_0_sw_acq2 ),
        .sw_acq2in3 ( plusestate_0_sw_acq2 ),
        .change     ( top_code_0_change ),
        // Outputs
        .interupt   ( interupt_net_0 ),
        .rt_sw      ( rt_sw_net_0 ),
        .soft_dump  ( soft_dump_net_0 ),
        .sw_acq1    ( sw_acq1_net_0 ),
        .sw_acq2    ( sw_acq2_net_0 ) 
        );


endmodule
