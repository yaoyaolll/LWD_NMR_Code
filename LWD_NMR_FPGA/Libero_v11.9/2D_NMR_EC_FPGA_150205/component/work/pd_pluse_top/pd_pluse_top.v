`timescale 1 ns/100 ps
// Version: 9.1 SP5 9.1.5.1


module pd_pluse_top(
       dds,
       rst_n,
       pluse_start,
       clk_sys,
       pd_pluse_load,
       bb_ch,
       tetw_pluse,
       en,
       pd_pluse_choice,
       pd_pluse_data
    );
input  dds;
input  rst_n;
input  pluse_start;
input  clk_sys;
input  pd_pluse_load;
input  bb_ch;
input  tetw_pluse;
output en;
input  [3:0] pd_pluse_choice;
input  [15:0] pd_pluse_data;

    wire \pd_pluse_coder_0_i_5_[5] , \pd_pluse_coder_0_i_5_[4] , 
        \pd_pluse_coder_0_i_5_[3] , \pd_pluse_coder_0_i_5_[2] , 
        \pd_pluse_coder_0_i_5_[1] , \pd_pluse_coder_0_i_5_[0] , 
        pd_pluse_state_0_stateover, \pd_pluse_timer_0_count_[15] , 
        \pd_pluse_timer_0_count_[14] , \pd_pluse_timer_0_count_[13] , 
        \pd_pluse_timer_0_count_[12] , \pd_pluse_timer_0_count_[11] , 
        \pd_pluse_timer_0_count_[10] , \pd_pluse_timer_0_count_[9] , 
        \pd_pluse_timer_0_count_[8] , \pd_pluse_timer_0_count_[7] , 
        \pd_pluse_timer_0_count_[6] , \pd_pluse_timer_0_count_[5] , 
        \pd_pluse_timer_0_count_[4] , \pd_pluse_timer_0_count_[3] , 
        \pd_pluse_timer_0_count_[2] , \pd_pluse_timer_0_count_[1] , 
        \pd_pluse_timer_0_count_[0] , GND_net, VCC_net;
    
    pd_pluse_coder pd_pluse_coder_0 (.clk_sys(clk_sys), .dds(dds), 
        .rst_n(rst_n), .pd_pluse_load(pd_pluse_load), .pluse_start(
        pluse_start), .bb_ch(bb_ch), .tetw_pluse(tetw_pluse), .count({
        \pd_pluse_timer_0_count_[15] , \pd_pluse_timer_0_count_[14] , 
        \pd_pluse_timer_0_count_[13] , \pd_pluse_timer_0_count_[12] , 
        \pd_pluse_timer_0_count_[11] , \pd_pluse_timer_0_count_[10] , 
        \pd_pluse_timer_0_count_[9] , \pd_pluse_timer_0_count_[8] , 
        \pd_pluse_timer_0_count_[7] , \pd_pluse_timer_0_count_[6] , 
        \pd_pluse_timer_0_count_[5] , \pd_pluse_timer_0_count_[4] , 
        \pd_pluse_timer_0_count_[3] , \pd_pluse_timer_0_count_[2] , 
        \pd_pluse_timer_0_count_[1] , \pd_pluse_timer_0_count_[0] }), 
        .pd_pluse_choice({pd_pluse_choice[3], pd_pluse_choice[2], 
        pd_pluse_choice[1], pd_pluse_choice[0]}), .pd_pluse_data({
        pd_pluse_data[15], pd_pluse_data[14], pd_pluse_data[13], 
        pd_pluse_data[12], pd_pluse_data[11], pd_pluse_data[10], 
        pd_pluse_data[9], pd_pluse_data[8], pd_pluse_data[7], 
        pd_pluse_data[6], pd_pluse_data[5], pd_pluse_data[4], 
        pd_pluse_data[3], pd_pluse_data[2], pd_pluse_data[1], 
        pd_pluse_data[0]}), .i({\pd_pluse_coder_0_i_5_[5] , 
        \pd_pluse_coder_0_i_5_[4] , \pd_pluse_coder_0_i_5_[3] , 
        \pd_pluse_coder_0_i_5_[2] , \pd_pluse_coder_0_i_5_[1] , 
        \pd_pluse_coder_0_i_5_[0] }));
    VCC VCC (.Y(VCC_net));
    pd_pluse_state pd_pluse_state_0 (.dds(dds), .rst_n(rst_n), .en(en), 
        .stateover(pd_pluse_state_0_stateover), .i({
        \pd_pluse_coder_0_i_5_[5] , \pd_pluse_coder_0_i_5_[4] , 
        \pd_pluse_coder_0_i_5_[3] , \pd_pluse_coder_0_i_5_[2] , 
        \pd_pluse_coder_0_i_5_[1] , \pd_pluse_coder_0_i_5_[0] }));
    pd_pluse_timer pd_pluse_timer_0 (.dds(dds), .rst_n(rst_n), 
        .stateover(pd_pluse_state_0_stateover), .pluse_start(
        pluse_start), .count({\pd_pluse_timer_0_count_[15] , 
        \pd_pluse_timer_0_count_[14] , \pd_pluse_timer_0_count_[13] , 
        \pd_pluse_timer_0_count_[12] , \pd_pluse_timer_0_count_[11] , 
        \pd_pluse_timer_0_count_[10] , \pd_pluse_timer_0_count_[9] , 
        \pd_pluse_timer_0_count_[8] , \pd_pluse_timer_0_count_[7] , 
        \pd_pluse_timer_0_count_[6] , \pd_pluse_timer_0_count_[5] , 
        \pd_pluse_timer_0_count_[4] , \pd_pluse_timer_0_count_[3] , 
        \pd_pluse_timer_0_count_[2] , \pd_pluse_timer_0_count_[1] , 
        \pd_pluse_timer_0_count_[0] }));
    GND GND (.Y(GND_net));
    
endmodule
