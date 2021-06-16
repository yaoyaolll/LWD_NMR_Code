`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module PluseTop(
       pluserst,
       rt_sw,
       sw_acq1,
       sw_acq2,
       soft_d,
       dump_start,
       pluse_acq,
       plusestart,
       pluseload,
       pluseloadchoice,
       pluseinter,
       dds_config,
       pluse_start,
       dumpoff_ctr,
       clk_sys,
       tetw_pluse,
       offtest,
       plusedatain
    );
input  pluserst;
output rt_sw;
output sw_acq1;
output sw_acq2;
output soft_d;
output dump_start;
output pluse_acq;
input  plusestart;
input  pluseload;
input  pluseloadchoice;
output pluseinter;
output dds_config;
output pluse_start;
output dumpoff_ctr;
input  clk_sys;
output tetw_pluse;
output offtest;
input  [15:0] plusedatain;

    wire \plusestate_0_timecount_[19] , \plusestate_0_timecount_[18] , 
        \plusestate_0_timecount_[17] , \plusestate_0_timecount_[16] , 
        \plusestate_0_timecount_[15] , \plusestate_0_timecount_[14] , 
        \plusestate_0_timecount_[13] , \plusestate_0_timecount_[12] , 
        \plusestate_0_timecount_[11] , \plusestate_0_timecount_[10] , 
        \plusestate_0_timecount_[9] , \plusestate_0_timecount_[8] , 
        \plusestate_0_timecount_[7] , \plusestate_0_timecount_[6] , 
        \plusestate_0_timecount_[5] , \plusestate_0_timecount_[4] , 
        \plusestate_0_timecount_[3] , \plusestate_0_timecount_[2] , 
        \plusestate_0_timecount_[1] , \plusestate_0_timecount_[0] , 
        timer_0_timeup_n, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(pluserst), .clk_sys(clk_sys), .work_n(
        timer_0_timeup_n), .state_start(plusestart), .state_over_n(
        pluseinter), .timeup_n(timer_0_timeup_n), .datain({GND_net, 
        GND_net, \plusestate_0_timecount_[19] , 
        \plusestate_0_timecount_[18] , \plusestate_0_timecount_[17] , 
        \plusestate_0_timecount_[16] , \plusestate_0_timecount_[15] , 
        \plusestate_0_timecount_[14] , \plusestate_0_timecount_[13] , 
        \plusestate_0_timecount_[12] , \plusestate_0_timecount_[11] , 
        \plusestate_0_timecount_[10] , \plusestate_0_timecount_[9] , 
        \plusestate_0_timecount_[8] , \plusestate_0_timecount_[7] , 
        \plusestate_0_timecount_[6] , \plusestate_0_timecount_[5] , 
        \plusestate_0_timecount_[4] , \plusestate_0_timecount_[3] , 
        \plusestate_0_timecount_[2] , \plusestate_0_timecount_[1] , 
        \plusestate_0_timecount_[0] }));
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    plusestate plusestate_0 (.clk_sys(clk_sys), .clken_p(
        timer_0_timeup_n), .rst_n(pluserst), .soft_d(soft_d), .rt_sw(
        rt_sw), .sw_acq1(sw_acq1), .sw_acq2(sw_acq2), .pluse_acq(
        pluse_acq), .pluse_start(pluse_start), .off_test(offtest), 
        .load(pluseload), .loadchoice(pluseloadchoice), .dump_start(
        dump_start), .state_over_n(pluseinter), .dds_config(dds_config)
        , .dumpoff_ctr(dumpoff_ctr), .tetw_pluse(tetw_pluse), 
        .timecount({\plusestate_0_timecount_[19] , 
        \plusestate_0_timecount_[18] , \plusestate_0_timecount_[17] , 
        \plusestate_0_timecount_[16] , \plusestate_0_timecount_[15] , 
        \plusestate_0_timecount_[14] , \plusestate_0_timecount_[13] , 
        \plusestate_0_timecount_[12] , \plusestate_0_timecount_[11] , 
        \plusestate_0_timecount_[10] , \plusestate_0_timecount_[9] , 
        \plusestate_0_timecount_[8] , \plusestate_0_timecount_[7] , 
        \plusestate_0_timecount_[6] , \plusestate_0_timecount_[5] , 
        \plusestate_0_timecount_[4] , \plusestate_0_timecount_[3] , 
        \plusestate_0_timecount_[2] , \plusestate_0_timecount_[1] , 
        \plusestate_0_timecount_[0] }), .datain({plusedatain[15], 
        plusedatain[14], plusedatain[13], plusedatain[12], 
        plusedatain[11], plusedatain[10], plusedatain[9], 
        plusedatain[8], plusedatain[7], plusedatain[6], plusedatain[5], 
        plusedatain[4], plusedatain[3], plusedatain[2], plusedatain[1], 
        plusedatain[0]}));
    
endmodule
