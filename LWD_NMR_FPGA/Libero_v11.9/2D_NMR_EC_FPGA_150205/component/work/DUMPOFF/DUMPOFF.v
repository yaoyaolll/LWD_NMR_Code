`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module DUMPOFF(
       clk_sys,
       rst_n,
       state_start,
       dumpoff
    );
input  clk_sys;
input  rst_n;
input  state_start;
output dumpoff;

    wire \off_on_coder_0_i_[1] , \off_on_coder_0_i_[0] , 
        off_on_state_0_state_over, \off_on_timer_0_count_[4] , 
        \off_on_timer_0_count_[3] , \off_on_timer_0_count_[2] , 
        \off_on_timer_0_count_[1] , \off_on_timer_0_count_[0] , 
        GND_net, VCC_net;
    
    off_on_state off_on_state_0 (.clk_sys(clk_sys), .rst_n(rst_n), .i({
        \off_on_coder_0_i_[1] , \off_on_coder_0_i_[0] }), .off_on(
        dumpoff), .state_over(off_on_state_0_state_over));
    VCC VCC (.Y(VCC_net));
    off_on_coder off_on_coder_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .count({\off_on_timer_0_count_[4] , 
        \off_on_timer_0_count_[3] , \off_on_timer_0_count_[2] , 
        \off_on_timer_0_count_[1] , \off_on_timer_0_count_[0] }), .i({
        \off_on_coder_0_i_[1] , \off_on_coder_0_i_[0] }));
    GND GND (.Y(GND_net));
    off_on_timer off_on_timer_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .state_over(
        off_on_state_0_state_over), .count({\off_on_timer_0_count_[4] , 
        \off_on_timer_0_count_[3] , \off_on_timer_0_count_[2] , 
        \off_on_timer_0_count_[1] , \off_on_timer_0_count_[0] }));
    
endmodule
