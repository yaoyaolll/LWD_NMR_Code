`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module STATE_1MS_TOP(
       state_1ms_rst_n,
       clk_sys,
       state_1ms_start,
       reset_out,
       dump_start,
       pluse_start,
       bri_cycle,
       rt_sw,
       soft_dump,
       load,
       loadchoice,
       datain
    );
input  state_1ms_rst_n;
input  clk_sys;
input  state_1ms_start;
output reset_out;
output dump_start;
output pluse_start;
output bri_cycle;
output rt_sw;
output soft_dump;
input  load;
input  [3:0] loadchoice;
input  [15:0] datain;

    wire \state_1ms_0_timecount_[19] , \state_1ms_0_timecount_[18] , 
        \state_1ms_0_timecount_[17] , \state_1ms_0_timecount_[16] , 
        \state_1ms_0_timecount_[15] , \state_1ms_0_timecount_[14] , 
        \state_1ms_0_timecount_[13] , \state_1ms_0_timecount_[12] , 
        \state_1ms_0_timecount_[11] , \state_1ms_0_timecount_[10] , 
        \state_1ms_0_timecount_[9] , \state_1ms_0_timecount_[8] , 
        \state_1ms_0_timecount_[7] , \state_1ms_0_timecount_[6] , 
        \state_1ms_0_timecount_[5] , \state_1ms_0_timecount_[4] , 
        \state_1ms_0_timecount_[3] , \state_1ms_0_timecount_[2] , 
        \state_1ms_0_timecount_[1] , \state_1ms_0_timecount_[0] , 
        timeup_n, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(state_1ms_rst_n), .clk_sys(clk_sys), .datain({
        GND_net, GND_net, \state_1ms_0_timecount_[19] , 
        \state_1ms_0_timecount_[18] , \state_1ms_0_timecount_[17] , 
        \state_1ms_0_timecount_[16] , \state_1ms_0_timecount_[15] , 
        \state_1ms_0_timecount_[14] , \state_1ms_0_timecount_[13] , 
        \state_1ms_0_timecount_[12] , \state_1ms_0_timecount_[11] , 
        \state_1ms_0_timecount_[10] , \state_1ms_0_timecount_[9] , 
        \state_1ms_0_timecount_[8] , \state_1ms_0_timecount_[7] , 
        \state_1ms_0_timecount_[6] , \state_1ms_0_timecount_[5] , 
        \state_1ms_0_timecount_[4] , \state_1ms_0_timecount_[3] , 
        \state_1ms_0_timecount_[2] , \state_1ms_0_timecount_[1] , 
        \state_1ms_0_timecount_[0] }), .work_n(timeup_n), .state_start(
        state_1ms_start), .state_over_n(VCC_net), .timeup_n(timeup_n));
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    state_1ms state_1ms_0 (.clk_sys(clk_sys), .clken_p(timeup_n), 
        .rst_n(state_1ms_rst_n), .load(load), .loadchoice({
        loadchoice[3], loadchoice[2], loadchoice[1], loadchoice[0]}), 
        .datain({datain[15], datain[14], datain[13], datain[12], 
        datain[11], datain[10], datain[9], datain[8], datain[7], 
        datain[6], datain[5], datain[4], datain[3], datain[2], 
        datain[1], datain[0]}), .reset_out(reset_out), .dump_start(
        dump_start), .pluse_start(pluse_start), .bri_cycle(bri_cycle), 
        .rt_sw(rt_sw), .soft_dump(soft_dump), .timecount({
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
    
endmodule
