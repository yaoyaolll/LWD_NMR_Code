`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module scaltop(
       sw_acq2,
       sw_acq1,
       soft_d,
       rt_sw,
       scalerst,
       scaleload,
       calcuinter,
       scalstart,
       dds_conf,
       s_acq,
       reset_out,
       load_out,
       pn_change,
       stateinter,
       dump_start,
       pluse_start,
       pn_out,
       dumpoff_ctr,
       bb_ch,
       clk_sys,
       tetw_pluse,
       offtest,
       s_acq180,
       ppheavy_test,
       scaledatain,
       strippluse,
       s_acqnum,
       scalechoice
    );
output sw_acq2;
output sw_acq1;
output soft_d;
output rt_sw;
input  scalerst;
input  scaleload;
output calcuinter;
input  scalstart;
output dds_conf;
output s_acq;
output reset_out;
output load_out;
input  pn_change;
output stateinter;
output dump_start;
output pluse_start;
output pn_out;
output dumpoff_ctr;
output bb_ch;
input  clk_sys;
output tetw_pluse;
output offtest;
output s_acq180;
output ppheavy_test;
input  [15:0] scaledatain;
output [11:0] strippluse;
output [15:0] s_acqnum;
input  [4:0] scalechoice;

    wire \scalestate_0_timecount_0_[21] , 
        \scalestate_0_timecount_0_[20] , 
        \scalestate_0_timecount_0_[19] , 
        \scalestate_0_timecount_0_[18] , 
        \scalestate_0_timecount_0_[17] , 
        \scalestate_0_timecount_0_[16] , 
        \scalestate_0_timecount_0_[15] , 
        \scalestate_0_timecount_0_[14] , 
        \scalestate_0_timecount_0_[13] , 
        \scalestate_0_timecount_0_[12] , 
        \scalestate_0_timecount_0_[11] , 
        \scalestate_0_timecount_0_[10] , 
        \scalestate_0_timecount_0_[9] , \scalestate_0_timecount_0_[8] , 
        \scalestate_0_timecount_0_[7] , \scalestate_0_timecount_0_[6] , 
        \scalestate_0_timecount_0_[5] , \scalestate_0_timecount_0_[4] , 
        \scalestate_0_timecount_0_[3] , \scalestate_0_timecount_0_[2] , 
        \scalestate_0_timecount_0_[1] , \scalestate_0_timecount_0_[0] , 
        timer_0_timeup_n, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(scalerst), .clk_sys(clk_sys), .work_n(
        timer_0_timeup_n), .state_start(scalstart), .state_over_n(
        stateinter), .timeup_n(timer_0_timeup_n), .datain({
        \scalestate_0_timecount_0_[21] , 
        \scalestate_0_timecount_0_[20] , 
        \scalestate_0_timecount_0_[19] , 
        \scalestate_0_timecount_0_[18] , 
        \scalestate_0_timecount_0_[17] , 
        \scalestate_0_timecount_0_[16] , 
        \scalestate_0_timecount_0_[15] , 
        \scalestate_0_timecount_0_[14] , 
        \scalestate_0_timecount_0_[13] , 
        \scalestate_0_timecount_0_[12] , 
        \scalestate_0_timecount_0_[11] , 
        \scalestate_0_timecount_0_[10] , 
        \scalestate_0_timecount_0_[9] , \scalestate_0_timecount_0_[8] , 
        \scalestate_0_timecount_0_[7] , \scalestate_0_timecount_0_[6] , 
        \scalestate_0_timecount_0_[5] , \scalestate_0_timecount_0_[4] , 
        \scalestate_0_timecount_0_[3] , \scalestate_0_timecount_0_[2] , 
        \scalestate_0_timecount_0_[1] , \scalestate_0_timecount_0_[0] })
        );
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    scalestate scalestate_0 (.clk_sys(clk_sys), .clken_p(
        timer_0_timeup_n), .rst_n(scalerst), .soft_d(soft_d), .rt_sw(
        rt_sw), .sw_acq1(sw_acq1), .sw_acq2(sw_acq2), .s_acq(s_acq), 
        .dds_conf(dds_conf), .load(scaleload), .pn_change(pn_change), 
        .dump_start(dump_start), .pluse_start(pluse_start), .pn_out(
        pn_out), .bb_ch(bb_ch), .reset_out(reset_out), .load_out(
        load_out), .intertodsp(calcuinter), .state_over_n(stateinter), 
        .dumpoff_ctr(dumpoff_ctr), .off_test(offtest), .tetw_pluse(
        tetw_pluse), .s_acq180(s_acq180), .ppheavy_test(ppheavy_test), 
        .timecount({\scalestate_0_timecount_0_[21] , 
        \scalestate_0_timecount_0_[20] , 
        \scalestate_0_timecount_0_[19] , 
        \scalestate_0_timecount_0_[18] , 
        \scalestate_0_timecount_0_[17] , 
        \scalestate_0_timecount_0_[16] , 
        \scalestate_0_timecount_0_[15] , 
        \scalestate_0_timecount_0_[14] , 
        \scalestate_0_timecount_0_[13] , 
        \scalestate_0_timecount_0_[12] , 
        \scalestate_0_timecount_0_[11] , 
        \scalestate_0_timecount_0_[10] , 
        \scalestate_0_timecount_0_[9] , \scalestate_0_timecount_0_[8] , 
        \scalestate_0_timecount_0_[7] , \scalestate_0_timecount_0_[6] , 
        \scalestate_0_timecount_0_[5] , \scalestate_0_timecount_0_[4] , 
        \scalestate_0_timecount_0_[3] , \scalestate_0_timecount_0_[2] , 
        \scalestate_0_timecount_0_[1] , \scalestate_0_timecount_0_[0] })
        , .datain({scaledatain[15], scaledatain[14], scaledatain[13], 
        scaledatain[12], scaledatain[11], scaledatain[10], 
        scaledatain[9], scaledatain[8], scaledatain[7], scaledatain[6], 
        scaledatain[5], scaledatain[4], scaledatain[3], scaledatain[2], 
        scaledatain[1], scaledatain[0]}), .loadchoice({scalechoice[4], 
        scalechoice[3], scalechoice[2], scalechoice[1], scalechoice[0]})
        , .s_acqnum({s_acqnum[15], s_acqnum[14], s_acqnum[13], 
        s_acqnum[12], s_acqnum[11], s_acqnum[10], s_acqnum[9], 
        s_acqnum[8], s_acqnum[7], s_acqnum[6], s_acqnum[5], 
        s_acqnum[4], s_acqnum[3], s_acqnum[2], s_acqnum[1], 
        s_acqnum[0]}), .strippluse({strippluse[11], strippluse[10], 
        strippluse[9], strippluse[8], strippluse[7], strippluse[6], 
        strippluse[5], strippluse[4], strippluse[3], strippluse[2], 
        strippluse[1], strippluse[0]}));
    
endmodule
