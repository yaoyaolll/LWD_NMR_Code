`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module noisetop(
       clk_sys,
       noisestart,
       interrupt,
       nchoice,
       nload,
       noiserst,
       n_acq,
       rt_sw,
       sw_acq2,
       soft_d,
       sw_acq1,
       dumpoff_ctr,
       dumpon_ctr,
       ndatain
    );
input  clk_sys;
input  noisestart;
output interrupt;
input  nchoice;
input  nload;
input  noiserst;
output n_acq;
output rt_sw;
output sw_acq2;
output soft_d;
output sw_acq1;
output dumpoff_ctr;
output dumpon_ctr;
input  [15:0] ndatain;

    wire \noisestate_0_timecount_[19] , \noisestate_0_timecount_[18] , 
        \noisestate_0_timecount_[17] , \noisestate_0_timecount_[16] , 
        \noisestate_0_timecount_[15] , \noisestate_0_timecount_[14] , 
        \noisestate_0_timecount_[13] , \noisestate_0_timecount_[12] , 
        \noisestate_0_timecount_[11] , \noisestate_0_timecount_[10] , 
        \noisestate_0_timecount_[9] , \noisestate_0_timecount_[8] , 
        \noisestate_0_timecount_[7] , \noisestate_0_timecount_[6] , 
        \noisestate_0_timecount_[5] , \noisestate_0_timecount_[4] , 
        \noisestate_0_timecount_[3] , \noisestate_0_timecount_[2] , 
        \noisestate_0_timecount_[1] , \noisestate_0_timecount_[0] , 
        timer_0_timeup_n, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(noiserst), .clk_sys(clk_sys), .work_n(
        timer_0_timeup_n), .state_start(noisestart), .state_over_n(
        interrupt), .timeup_n(timer_0_timeup_n), .datain({GND_net, 
        GND_net, \noisestate_0_timecount_[19] , 
        \noisestate_0_timecount_[18] , \noisestate_0_timecount_[17] , 
        \noisestate_0_timecount_[16] , \noisestate_0_timecount_[15] , 
        \noisestate_0_timecount_[14] , \noisestate_0_timecount_[13] , 
        \noisestate_0_timecount_[12] , \noisestate_0_timecount_[11] , 
        \noisestate_0_timecount_[10] , \noisestate_0_timecount_[9] , 
        \noisestate_0_timecount_[8] , \noisestate_0_timecount_[7] , 
        \noisestate_0_timecount_[6] , \noisestate_0_timecount_[5] , 
        \noisestate_0_timecount_[4] , \noisestate_0_timecount_[3] , 
        \noisestate_0_timecount_[2] , \noisestate_0_timecount_[1] , 
        \noisestate_0_timecount_[0] }));
    VCC VCC (.Y(VCC_net));
    noisestate noisestate_0 (.clk_sys(clk_sys), .clken_p(
        timer_0_timeup_n), .rst_n(noiserst), .dumpon_ctr(dumpon_ctr), 
        .dumpoff_ctr(dumpoff_ctr), .soft_d(soft_d), .rt_sw(rt_sw), 
        .sw_acq1(sw_acq1), .sw_acq2(sw_acq2), .n_acq(n_acq), 
        .state_over_n(interrupt), .nload(nload), .nchoice(nchoice), 
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
    GND GND (.Y(GND_net));
    
endmodule
