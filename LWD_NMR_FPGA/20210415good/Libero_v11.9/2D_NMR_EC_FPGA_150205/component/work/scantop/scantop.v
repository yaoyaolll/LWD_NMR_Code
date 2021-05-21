`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module scantop(
       interrupt,
       scanstart,
       clk_sys,
       scanrst,
       scanload,
       scanchoice,
       sw_acq2,
       sw_acq1,
       dumpoff_ctr,
       dumpon_ctr,
       calctrl,
       dds_conf,
       rt_sw,
       soft_d,
       s_acq,
       datain
    );
output interrupt;
input  scanstart;
input  clk_sys;
input  scanrst;
input  scanload;
input  scanchoice;
output sw_acq2;
output sw_acq1;
output dumpoff_ctr;
output dumpon_ctr;
output calctrl;
output dds_conf;
output rt_sw;
output soft_d;
output s_acq;
input  [15:0] datain;

    wire \scanstate_0_timecount_[19] , \scanstate_0_timecount_[18] , 
        \scanstate_0_timecount_[17] , \scanstate_0_timecount_[16] , 
        \scanstate_0_timecount_[15] , \scanstate_0_timecount_[14] , 
        \scanstate_0_timecount_[13] , \scanstate_0_timecount_[12] , 
        \scanstate_0_timecount_[11] , \scanstate_0_timecount_[10] , 
        \scanstate_0_timecount_[9] , \scanstate_0_timecount_[8] , 
        \scanstate_0_timecount_[7] , \scanstate_0_timecount_[6] , 
        \scanstate_0_timecount_[5] , \scanstate_0_timecount_[4] , 
        \scanstate_0_timecount_[3] , \scanstate_0_timecount_[2] , 
        \scanstate_0_timecount_[1] , \scanstate_0_timecount_[0] , 
        timer_0_timeup, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(scanrst), .clk_sys(clk_sys), .work_n(
        timer_0_timeup), .state_start(scanstart), .state_over_n(
        interrupt), .timeup_n(timer_0_timeup), .datain({GND_net, 
        GND_net, \scanstate_0_timecount_[19] , 
        \scanstate_0_timecount_[18] , \scanstate_0_timecount_[17] , 
        \scanstate_0_timecount_[16] , \scanstate_0_timecount_[15] , 
        \scanstate_0_timecount_[14] , \scanstate_0_timecount_[13] , 
        \scanstate_0_timecount_[12] , \scanstate_0_timecount_[11] , 
        \scanstate_0_timecount_[10] , \scanstate_0_timecount_[9] , 
        \scanstate_0_timecount_[8] , \scanstate_0_timecount_[7] , 
        \scanstate_0_timecount_[6] , \scanstate_0_timecount_[5] , 
        \scanstate_0_timecount_[4] , \scanstate_0_timecount_[3] , 
        \scanstate_0_timecount_[2] , \scanstate_0_timecount_[1] , 
        \scanstate_0_timecount_[0] }));
    scanstate scanstate_0 (.clk_sys(clk_sys), .clken_p(timer_0_timeup), 
        .rst_n(scanrst), .dumpon_ctr(dumpon_ctr), .dumpoff_ctr(
        dumpoff_ctr), .soft_d(soft_d), .rt_sw(rt_sw), .sw_acq1(sw_acq1)
        , .sw_acq2(sw_acq2), .s_acq(s_acq), .dds_conf(dds_conf), 
        .calctrl(calctrl), .state_over_n(interrupt), .scanload(
        scanload), .scanchoice(scanchoice), .resetout(), .timecount({
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
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    
endmodule
