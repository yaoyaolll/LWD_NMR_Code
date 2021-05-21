`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module scanstatetop(
       dds_conf,
       calctrl,
       s_acq,
       timeclk,
       scanstart,
       scanrst,
       noiserst,
       noisestart,
       soft_d,
       sw_acq2,
       sw_acq1,
       intertodsp,
       rt_sw,
       n_s_change,
       ctrl,
       n_en,
       pluse_acq,
       scanload,
       scanchoice,
       nload,
       nchoice,
       resetout,
       dump_on,
       dump_off,
       datain,
       ndatain
    );
output dds_conf;
output calctrl;
output s_acq;
input  timeclk;
input  scanstart;
input  scanrst;
input  noiserst;
input  noisestart;
output soft_d;
output sw_acq2;
output sw_acq1;
output intertodsp;
output rt_sw;
input  n_s_change;
input  ctrl;
output n_en;
input  pluse_acq;
input  scanload;
input  scanchoice;
input  nload;
input  nchoice;
output resetout;
output dump_on;
output dump_off;
input  [15:0] datain;
input  [15:0] ndatain;

    wire AND3_0_Y, AND3_1_Y, dumpoff_ctr, dumpoff_ctr_0, dumpoff_ctr_1, 
        dumpon_ctr, dumpon_ctr_0, dumpon_ctr_1, INV_0_Y, INV_1_Y, 
        INV_2_Y, noisestate_0_n_acq, noisestate_0_rt_sw, 
        noisestate_0_soft_d, noisestate_0_stateover, 
        noisestate_0_sw_acq1, noisestate_0_sw_acq2, 
        \noisestate_0_timecount_[19] , \noisestate_0_timecount_[18] , 
        \noisestate_0_timecount_[17] , \noisestate_0_timecount_[16] , 
        \noisestate_0_timecount_[15] , \noisestate_0_timecount_[14] , 
        \noisestate_0_timecount_[13] , \noisestate_0_timecount_[12] , 
        \noisestate_0_timecount_[11] , \noisestate_0_timecount_[10] , 
        \noisestate_0_timecount_[9] , \noisestate_0_timecount_[8] , 
        \noisestate_0_timecount_[7] , \noisestate_0_timecount_[6] , 
        \noisestate_0_timecount_[5] , \noisestate_0_timecount_[4] , 
        \noisestate_0_timecount_[3] , \noisestate_0_timecount_[2] , 
        \noisestate_0_timecount_[1] , \noisestate_0_timecount_[0] , 
        nsctrl_choice_0_dumponoff_rst, scanstate_0_rt_sw, 
        scanstate_0_soft_d, scanstate_0_stateover, scanstate_0_sw_acq1, 
        scanstate_0_sw_acq2, \scanstate_0_timecount_[19] , 
        \scanstate_0_timecount_[18] , \scanstate_0_timecount_[17] , 
        \scanstate_0_timecount_[16] , \scanstate_0_timecount_[15] , 
        \scanstate_0_timecount_[14] , \scanstate_0_timecount_[13] , 
        \scanstate_0_timecount_[12] , \scanstate_0_timecount_[11] , 
        \scanstate_0_timecount_[10] , \scanstate_0_timecount_[9] , 
        \scanstate_0_timecount_[8] , \scanstate_0_timecount_[7] , 
        \scanstate_0_timecount_[6] , \scanstate_0_timecount_[5] , 
        \scanstate_0_timecount_[4] , \scanstate_0_timecount_[3] , 
        \scanstate_0_timecount_[2] , \scanstate_0_timecount_[1] , 
        \scanstate_0_timecount_[0] , timer_0_timeup, timer_1_timeup, 
        GND_net, VCC_net;
    
    GND GND (.Y(GND_net));
    INV INV_2 (.A(nsctrl_choice_0_dumponoff_rst), .Y(INV_2_Y));
    DUMP_OFF DUMP_OFF_0 (.rst_n(INV_2_Y), .state_start(dumpoff_ctr_1), 
        .clk_sys(timeclk), .dump_off(dump_off));
    timer timer_1 (.reset(noiserst), .timeclk(AND3_1_Y), .work(
        timer_1_timeup), .timeup(timer_1_timeup), .datain({
        \noisestate_0_timecount_[19] , \noisestate_0_timecount_[18] , 
        \noisestate_0_timecount_[17] , \noisestate_0_timecount_[16] , 
        \noisestate_0_timecount_[15] , \noisestate_0_timecount_[14] , 
        \noisestate_0_timecount_[13] , \noisestate_0_timecount_[12] , 
        \noisestate_0_timecount_[11] , \noisestate_0_timecount_[10] , 
        \noisestate_0_timecount_[9] , \noisestate_0_timecount_[8] , 
        \noisestate_0_timecount_[7] , \noisestate_0_timecount_[6] , 
        \noisestate_0_timecount_[5] , \noisestate_0_timecount_[4] , 
        \noisestate_0_timecount_[3] , \noisestate_0_timecount_[2] , 
        \noisestate_0_timecount_[1] , \noisestate_0_timecount_[0] }));
    nsctrl_choice nsctrl_choice_0 (.choice(n_s_change), .soft_d_s(
        scanstate_0_soft_d), .rt_sw_s(scanstate_0_rt_sw), .sw_acq1_s(
        scanstate_0_sw_acq1), .sw_acq2_s(scanstate_0_sw_acq2), 
        .inter_s(INV_0_Y), .dumpon_ctr_s(dumpon_ctr), .dumpoff_ctr_s(
        dumpoff_ctr), .dumponoff_rst_s(scanrst), .soft_d_n(
        noisestate_0_soft_d), .rt_sw_n(noisestate_0_rt_sw), .sw_acq1_n(
        noisestate_0_sw_acq1), .sw_acq2_n(noisestate_0_sw_acq2), 
        .inter_n(INV_1_Y), .dumpon_ctr_n(dumpon_ctr_0), .dumpoff_ctr_n(
        dumpoff_ctr_0), .dumponoff_rst_n(noiserst), .soft_d(soft_d), 
        .rt_sw(rt_sw), .sw_acq1(sw_acq1), .sw_acq2(sw_acq2), 
        .intertodsp(intertodsp), .dumpon_ctr(dumpon_ctr_1), 
        .dumpoff_ctr(dumpoff_ctr_1), .dumponoff_rst(
        nsctrl_choice_0_dumponoff_rst));
    VCC VCC (.Y(VCC_net));
    AND3 AND3_1 (.A(timeclk), .B(noisestart), .C(
        noisestate_0_stateover), .Y(AND3_1_Y));
    INV INV_1 (.A(noisestate_0_stateover), .Y(INV_1_Y));
    AND3 AND3_0 (.A(timeclk), .B(scanstart), .C(scanstate_0_stateover), 
        .Y(AND3_0_Y));
    scanstate scanstate_0 (.scanclk(timer_0_timeup), .scanrst(scanrst), 
        .dumpon_ctr(dumpon_ctr), .dumpoff_ctr(dumpoff_ctr), .soft_d(
        scanstate_0_soft_d), .rt_sw(scanstate_0_rt_sw), .sw_acq1(
        scanstate_0_sw_acq1), .sw_acq2(scanstate_0_sw_acq2), .s_acq(
        s_acq), .dds_conf(dds_conf), .calctrl(calctrl), .stateover(
        scanstate_0_stateover), .scanload(scanload), .scanchoice(
        scanchoice), .resetout(resetout), .timecount({
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
        .datain({datain[15], datain[14], datain[13], datain[12], 
        datain[11], datain[10], datain[9], datain[8], datain[7], 
        datain[6], datain[5], datain[4], datain[3], datain[2], 
        datain[1], datain[0]}));
    n_pluse_acq n_pluse_acq_0 (.ctrl(ctrl), .n_en(n_en), .n_acq(
        noisestate_0_n_acq), .pluse_acq(pluse_acq));
    INV INV_0 (.A(scanstate_0_stateover), .Y(INV_0_Y));
    noisestate noisestate_0 (.noiseclk(timer_1_timeup), .noiserst(
        noiserst), .dumpon_ctr(dumpon_ctr_0), .dumpoff_ctr(
        dumpoff_ctr_0), .soft_d(noisestate_0_soft_d), .rt_sw(
        noisestate_0_rt_sw), .sw_acq1(noisestate_0_sw_acq1), .sw_acq2(
        noisestate_0_sw_acq2), .n_acq(noisestate_0_n_acq), .stateover(
        noisestate_0_stateover), .nload(nload), .nchoice(nchoice), 
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
        \noisestate_0_timecount_[0] }), .ndatain({ndatain[15], 
        ndatain[14], ndatain[13], ndatain[12], ndatain[11], 
        ndatain[10], ndatain[9], ndatain[8], ndatain[7], ndatain[6], 
        ndatain[5], ndatain[4], ndatain[3], ndatain[2], ndatain[1], 
        ndatain[0]}));
    timer timer_0 (.reset(scanrst), .timeclk(AND3_0_Y), .work(
        timer_0_timeup), .timeup(timer_0_timeup), .datain({
        \scanstate_0_timecount_[19] , \scanstate_0_timecount_[18] , 
        \scanstate_0_timecount_[17] , \scanstate_0_timecount_[16] , 
        \scanstate_0_timecount_[15] , \scanstate_0_timecount_[14] , 
        \scanstate_0_timecount_[13] , \scanstate_0_timecount_[12] , 
        \scanstate_0_timecount_[11] , \scanstate_0_timecount_[10] , 
        \scanstate_0_timecount_[9] , \scanstate_0_timecount_[8] , 
        \scanstate_0_timecount_[7] , \scanstate_0_timecount_[6] , 
        \scanstate_0_timecount_[5] , \scanstate_0_timecount_[4] , 
        \scanstate_0_timecount_[3] , \scanstate_0_timecount_[2] , 
        \scanstate_0_timecount_[1] , \scanstate_0_timecount_[0] }));
    DUMP_ON DUMP_ON_0 (.dump_on(dump_on), .state_start(dumpon_ctr_1), 
        .rst_n(INV_2_Y), .clk_sys(timeclk));
    
endmodule
