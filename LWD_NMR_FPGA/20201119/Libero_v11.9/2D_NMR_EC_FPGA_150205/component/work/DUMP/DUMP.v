`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module DUMP(
       rst_n,
       state_start,
       clk_sys,
       dump_off,
       dump_on,
       dump_load,
       bri_cycle,
       pluse_start,
       dump_choice,
       dump_para
    );
input  rst_n;
input  state_start;
input  clk_sys;
output dump_off;
output dump_on;
input  dump_load;
input  bri_cycle;
input  pluse_start;
input  [2:0] dump_choice;
input  [11:0] dump_para;

    wire \dump_coder_0_i_[8] , \dump_coder_0_i_[7] , 
        \dump_coder_0_i_[6] , \dump_coder_0_i_[5] , 
        \dump_coder_0_i_[4] , \dump_coder_0_i_[3] , 
        \dump_coder_0_i_[2] , \dump_coder_0_i_[1] , 
        \dump_coder_0_i_[0] , dump_state_0_off_start, 
        dump_state_0_on_start, dump_state_0_timer_start, 
        \dump_timer_0_count_[11] , \dump_timer_0_count_[10] , 
        \dump_timer_0_count_[9] , \dump_timer_0_count_[8] , 
        \dump_timer_0_count_[7] , \dump_timer_0_count_[6] , 
        \dump_timer_0_count_[5] , \dump_timer_0_count_[4] , 
        \dump_timer_0_count_[3] , \dump_timer_0_count_[2] , 
        \dump_timer_0_count_[1] , \dump_timer_0_count_[0] , 
        \off_on_coder_0_i_[1] , \off_on_coder_0_i_[0] , 
        \off_on_coder_1_i_[1] , \off_on_coder_1_i_[0] , 
        off_on_state_0_state_over, off_on_state_1_state_over, 
        \off_on_timer_0_count_[4] , \off_on_timer_0_count_[3] , 
        \off_on_timer_0_count_[2] , \off_on_timer_0_count_[1] , 
        \off_on_timer_0_count_[0] , \off_on_timer_1_count_[4] , 
        \off_on_timer_1_count_[3] , \off_on_timer_1_count_[2] , 
        \off_on_timer_1_count_[1] , \off_on_timer_1_count_[0] , 
        GND_net, VCC_net;
    
    off_on_timer off_on_timer_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(dump_state_0_off_start), .state_over(
        off_on_state_0_state_over), .count({\off_on_timer_0_count_[4] , 
        \off_on_timer_0_count_[3] , \off_on_timer_0_count_[2] , 
        \off_on_timer_0_count_[1] , \off_on_timer_0_count_[0] }));
    GND GND (.Y(GND_net));
    dump_state dump_state_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .off_start(dump_state_0_off_start), .on_start(
        dump_state_0_on_start), .timer_start(dump_state_0_timer_start), 
        .i({\dump_coder_0_i_[8] , \dump_coder_0_i_[7] , 
        \dump_coder_0_i_[6] , \dump_coder_0_i_[5] , 
        \dump_coder_0_i_[4] , \dump_coder_0_i_[3] , 
        \dump_coder_0_i_[2] , \dump_coder_0_i_[1] , 
        \dump_coder_0_i_[0] }));
    off_on_coder off_on_coder_1 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(dump_state_0_off_start), .count({
        \off_on_timer_0_count_[4] , \off_on_timer_0_count_[3] , 
        \off_on_timer_0_count_[2] , \off_on_timer_0_count_[1] , 
        \off_on_timer_0_count_[0] }), .i({\off_on_coder_1_i_[1] , 
        \off_on_coder_1_i_[0] }));
    off_on_state off_on_state_1 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .off_on(dump_on), .state_over(off_on_state_1_state_over), .i({
        \off_on_coder_0_i_[1] , \off_on_coder_0_i_[0] }));
    VCC VCC (.Y(VCC_net));
    off_on_state off_on_state_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .off_on(dump_off), .state_over(off_on_state_0_state_over), .i({
        \off_on_coder_1_i_[1] , \off_on_coder_1_i_[0] }));
    dump_coder dump_coder_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .pluse_start(pluse_start), 
        .bri_cycle(bri_cycle), .dump_load(dump_load), .dump_choice({
        dump_choice[2], dump_choice[1], dump_choice[0]}), .dump_para({
        dump_para[11], dump_para[10], dump_para[9], dump_para[8], 
        dump_para[7], dump_para[6], dump_para[5], dump_para[4], 
        dump_para[3], dump_para[2], dump_para[1], dump_para[0]}), 
        .count({\dump_timer_0_count_[11] , \dump_timer_0_count_[10] , 
        \dump_timer_0_count_[9] , \dump_timer_0_count_[8] , 
        \dump_timer_0_count_[7] , \dump_timer_0_count_[6] , 
        \dump_timer_0_count_[5] , \dump_timer_0_count_[4] , 
        \dump_timer_0_count_[3] , \dump_timer_0_count_[2] , 
        \dump_timer_0_count_[1] , \dump_timer_0_count_[0] }), .i({
        \dump_coder_0_i_[8] , \dump_coder_0_i_[7] , 
        \dump_coder_0_i_[6] , \dump_coder_0_i_[5] , 
        \dump_coder_0_i_[4] , \dump_coder_0_i_[3] , 
        \dump_coder_0_i_[2] , \dump_coder_0_i_[1] , 
        \dump_coder_0_i_[0] }));
    dump_timer dump_timer_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .timer_start(
        dump_state_0_timer_start), .count({\dump_timer_0_count_[11] , 
        \dump_timer_0_count_[10] , \dump_timer_0_count_[9] , 
        \dump_timer_0_count_[8] , \dump_timer_0_count_[7] , 
        \dump_timer_0_count_[6] , \dump_timer_0_count_[5] , 
        \dump_timer_0_count_[4] , \dump_timer_0_count_[3] , 
        \dump_timer_0_count_[2] , \dump_timer_0_count_[1] , 
        \dump_timer_0_count_[0] }));
    off_on_timer off_on_timer_1 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(dump_state_0_on_start), .state_over(
        off_on_state_1_state_over), .count({\off_on_timer_1_count_[4] , 
        \off_on_timer_1_count_[3] , \off_on_timer_1_count_[2] , 
        \off_on_timer_1_count_[1] , \off_on_timer_1_count_[0] }));
    off_on_coder off_on_coder_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(dump_state_0_on_start), .count({
        \off_on_timer_1_count_[4] , \off_on_timer_1_count_[3] , 
        \off_on_timer_1_count_[2] , \off_on_timer_1_count_[1] , 
        \off_on_timer_1_count_[0] }), .i({\off_on_coder_0_i_[1] , 
        \off_on_coder_0_i_[0] }));
    
endmodule
