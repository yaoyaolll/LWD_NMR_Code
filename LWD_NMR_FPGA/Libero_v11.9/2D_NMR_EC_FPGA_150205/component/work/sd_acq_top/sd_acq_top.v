`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module sd_acq_top(
       dds,
       rst_n,
       s_acq1,
       clk_sys,
       sd_sacq_load,
       bb_ch,
       s_acq180,
       en,
       long_opentime,
       sd_sacq_choice,
       sd_sacq_data
    );
input  dds;
input  rst_n;
input  s_acq1;
input  clk_sys;
input  sd_sacq_load;
input  bb_ch;
input  s_acq180;
output en;
input  long_opentime;
input  [3:0] sd_sacq_choice;
input  [15:0] sd_sacq_data;

    wire \sd_sacq_coder_0_i_3_[10] , \sd_sacq_coder_0_i_3_[9] , 
        \sd_sacq_coder_0_i_3_[8] , \sd_sacq_coder_0_i_3_[7] , 
        \sd_sacq_coder_0_i_3_[6] , \sd_sacq_coder_0_i_3_[5] , 
        \sd_sacq_coder_0_i_3_[4] , \sd_sacq_coder_0_i_3_[3] , 
        \sd_sacq_coder_0_i_3_[2] , \sd_sacq_coder_0_i_3_[1] , 
        \sd_sacq_coder_0_i_3_[0] , sd_sacq_state_0_stateover, 
        \sd_sacq_timer_0_count_0_[21] , \sd_sacq_timer_0_count_0_[20] , 
        \sd_sacq_timer_0_count_0_[19] , \sd_sacq_timer_0_count_0_[18] , 
        \sd_sacq_timer_0_count_0_[17] , \sd_sacq_timer_0_count_0_[16] , 
        \sd_sacq_timer_0_count_0_[15] , \sd_sacq_timer_0_count_0_[14] , 
        \sd_sacq_timer_0_count_0_[13] , \sd_sacq_timer_0_count_0_[12] , 
        \sd_sacq_timer_0_count_0_[11] , \sd_sacq_timer_0_count_0_[10] , 
        \sd_sacq_timer_0_count_0_[9] , \sd_sacq_timer_0_count_0_[8] , 
        \sd_sacq_timer_0_count_0_[7] , \sd_sacq_timer_0_count_0_[6] , 
        \sd_sacq_timer_0_count_0_[5] , \sd_sacq_timer_0_count_0_[4] , 
        \sd_sacq_timer_0_count_0_[3] , \sd_sacq_timer_0_count_0_[2] , 
        \sd_sacq_timer_0_count_0_[1] , \sd_sacq_timer_0_count_0_[0] , 
        GND_net, VCC_net;
    
    sd_sacq_coder sd_sacq_coder_0 (.clk_sys(clk_sys), .dds(dds), 
        .rst_n(rst_n), .sd_sacq_load(sd_sacq_load), .state_start(
        s_acq1), .bb_ch(bb_ch), .s_acq180(s_acq180), .long_opentime(
        long_opentime), .count({\sd_sacq_timer_0_count_0_[21] , 
        \sd_sacq_timer_0_count_0_[20] , \sd_sacq_timer_0_count_0_[19] , 
        \sd_sacq_timer_0_count_0_[18] , \sd_sacq_timer_0_count_0_[17] , 
        \sd_sacq_timer_0_count_0_[16] , \sd_sacq_timer_0_count_0_[15] , 
        \sd_sacq_timer_0_count_0_[14] , \sd_sacq_timer_0_count_0_[13] , 
        \sd_sacq_timer_0_count_0_[12] , \sd_sacq_timer_0_count_0_[11] , 
        \sd_sacq_timer_0_count_0_[10] , \sd_sacq_timer_0_count_0_[9] , 
        \sd_sacq_timer_0_count_0_[8] , \sd_sacq_timer_0_count_0_[7] , 
        \sd_sacq_timer_0_count_0_[6] , \sd_sacq_timer_0_count_0_[5] , 
        \sd_sacq_timer_0_count_0_[4] , \sd_sacq_timer_0_count_0_[3] , 
        \sd_sacq_timer_0_count_0_[2] , \sd_sacq_timer_0_count_0_[1] , 
        \sd_sacq_timer_0_count_0_[0] }), .sd_sacq_choice({
        sd_sacq_choice[3], sd_sacq_choice[2], sd_sacq_choice[1], 
        sd_sacq_choice[0]}), .sd_sacq_data({sd_sacq_data[15], 
        sd_sacq_data[14], sd_sacq_data[13], sd_sacq_data[12], 
        sd_sacq_data[11], sd_sacq_data[10], sd_sacq_data[9], 
        sd_sacq_data[8], sd_sacq_data[7], sd_sacq_data[6], 
        sd_sacq_data[5], sd_sacq_data[4], sd_sacq_data[3], 
        sd_sacq_data[2], sd_sacq_data[1], sd_sacq_data[0]}), .i({
        \sd_sacq_coder_0_i_3_[10] , \sd_sacq_coder_0_i_3_[9] , 
        \sd_sacq_coder_0_i_3_[8] , \sd_sacq_coder_0_i_3_[7] , 
        \sd_sacq_coder_0_i_3_[6] , \sd_sacq_coder_0_i_3_[5] , 
        \sd_sacq_coder_0_i_3_[4] , \sd_sacq_coder_0_i_3_[3] , 
        \sd_sacq_coder_0_i_3_[2] , \sd_sacq_coder_0_i_3_[1] , 
        \sd_sacq_coder_0_i_3_[0] }));
    VCC VCC (.Y(VCC_net));
    sd_sacq_state sd_sacq_state_0 (.dds(dds), .rst_n(rst_n), .en(en), 
        .stateover(sd_sacq_state_0_stateover), .i({
        \sd_sacq_coder_0_i_3_[10] , \sd_sacq_coder_0_i_3_[9] , 
        \sd_sacq_coder_0_i_3_[8] , \sd_sacq_coder_0_i_3_[7] , 
        \sd_sacq_coder_0_i_3_[6] , \sd_sacq_coder_0_i_3_[5] , 
        \sd_sacq_coder_0_i_3_[4] , \sd_sacq_coder_0_i_3_[3] , 
        \sd_sacq_coder_0_i_3_[2] , \sd_sacq_coder_0_i_3_[1] , 
        \sd_sacq_coder_0_i_3_[0] }));
    sd_sacq_timer sd_sacq_timer_0 (.dds(dds), .rst_n(rst_n), 
        .stateover(sd_sacq_state_0_stateover), .s_acq1(s_acq1), .count({
        \sd_sacq_timer_0_count_0_[21] , \sd_sacq_timer_0_count_0_[20] , 
        \sd_sacq_timer_0_count_0_[19] , \sd_sacq_timer_0_count_0_[18] , 
        \sd_sacq_timer_0_count_0_[17] , \sd_sacq_timer_0_count_0_[16] , 
        \sd_sacq_timer_0_count_0_[15] , \sd_sacq_timer_0_count_0_[14] , 
        \sd_sacq_timer_0_count_0_[13] , \sd_sacq_timer_0_count_0_[12] , 
        \sd_sacq_timer_0_count_0_[11] , \sd_sacq_timer_0_count_0_[10] , 
        \sd_sacq_timer_0_count_0_[9] , \sd_sacq_timer_0_count_0_[8] , 
        \sd_sacq_timer_0_count_0_[7] , \sd_sacq_timer_0_count_0_[6] , 
        \sd_sacq_timer_0_count_0_[5] , \sd_sacq_timer_0_count_0_[4] , 
        \sd_sacq_timer_0_count_0_[3] , \sd_sacq_timer_0_count_0_[2] , 
        \sd_sacq_timer_0_count_0_[1] , \sd_sacq_timer_0_count_0_[0] }));
    GND GND (.Y(GND_net));
    
endmodule
