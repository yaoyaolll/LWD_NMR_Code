`timescale 1 ns/100 ps
// Version: 9.1 SP5 9.1.5.1


module PLUSE(
       state_start,
       rst_n,
       phase,
       quar_delay,
       clk_sys,
       pluse_load,
       bri_cycle,
       Q1Q8,
       Q3Q6,
       Q4Q5,
       Q2Q7,
       clk_dds,
       clk_4f_en,
       down,
       up,
       qq_para,
       bri_para,
       turn_delay
    );
input  state_start;
input  rst_n;
input  phase;
input  quar_delay;
input  clk_sys;
input  pluse_load;
output bri_cycle;
output Q1Q8;
output Q3Q6;
output Q4Q5;
output Q2Q7;
input  clk_dds;
input  clk_4f_en;
output down;
output up;
input  [15:0] qq_para;
input  [7:0] bri_para;
input  turn_delay;

    wire bri_coder_0_half, \bri_coder_0_i_1_[4] , 
        \bri_coder_0_i_1_[3] , \bri_coder_0_i_1_[2] , 
        \bri_coder_0_i_1_[1] , \bri_coder_0_i_1_[0] , 
        \bri_qq_load_0_half_para_0_[7] , 
        \bri_qq_load_0_half_para_0_[6] , 
        \bri_qq_load_0_half_para_0_[5] , 
        \bri_qq_load_0_half_para_0_[4] , 
        \bri_qq_load_0_half_para_0_[3] , 
        \bri_qq_load_0_half_para_0_[2] , 
        \bri_qq_load_0_half_para_0_[1] , 
        \bri_qq_load_0_half_para_0_[0] , \bri_qq_load_0_qq_para1_[3] , 
        \bri_qq_load_0_qq_para1_[2] , \bri_qq_load_0_qq_para1_[1] , 
        \bri_qq_load_0_qq_para1_[0] , \bri_qq_load_0_qq_para2_[5] , 
        \bri_qq_load_0_qq_para2_[4] , \bri_qq_load_0_qq_para2_[3] , 
        \bri_qq_load_0_qq_para2_[2] , \bri_qq_load_0_qq_para2_[1] , 
        \bri_qq_load_0_qq_para2_[0] , \bri_qq_load_0_qq_para3_[5] , 
        \bri_qq_load_0_qq_para3_[4] , \bri_qq_load_0_qq_para3_[3] , 
        \bri_qq_load_0_qq_para3_[2] , \bri_qq_load_0_qq_para3_[1] , 
        \bri_qq_load_0_qq_para3_[0] , \bri_timer_0_count_[7] , 
        \bri_timer_0_count_[6] , \bri_timer_0_count_[5] , 
        \bri_timer_0_count_[4] , \bri_timer_0_count_[3] , 
        \bri_timer_0_count_[2] , \bri_timer_0_count_[1] , 
        \bri_timer_0_count_[0] , \qq_coder_0_i_[3] , 
        \qq_coder_0_i_[2] , \qq_coder_0_i_[1] , \qq_coder_0_i_[0] , 
        \qq_coder_1_i_[3] , \qq_coder_1_i_[2] , \qq_coder_1_i_[1] , 
        \qq_coder_1_i_[0] , qq_state_0_stateover, qq_state_1_stateover, 
        \qq_timer_0_count_[4] , \qq_timer_0_count_[3] , 
        \qq_timer_0_count_[2] , \qq_timer_0_count_[1] , 
        \qq_timer_0_count_[0] , \qq_timer_1_count_[4] , 
        \qq_timer_1_count_[3] , \qq_timer_1_count_[2] , 
        \qq_timer_1_count_[1] , \qq_timer_1_count_[0] , GND_net, 
        VCC_net;
    
    qq_state qq_state_0 (.clk_sys(clk_sys), .rst_n(rst_n), .Q1Q8_Q2Q7(
        Q1Q8), .Q3Q6_Q4Q5(Q3Q6), .stateover(qq_state_0_stateover), .i({
        \qq_coder_0_i_[3] , \qq_coder_0_i_[2] , \qq_coder_0_i_[1] , 
        \qq_coder_0_i_[0] }));
    qq_coder qq_coder_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(up), .count({\qq_timer_0_count_[4] , 
        \qq_timer_0_count_[3] , \qq_timer_0_count_[2] , 
        \qq_timer_0_count_[1] , \qq_timer_0_count_[0] }), .qq_para1({
        \bri_qq_load_0_qq_para1_[3] , \bri_qq_load_0_qq_para1_[2] , 
        \bri_qq_load_0_qq_para1_[1] , \bri_qq_load_0_qq_para1_[0] }), 
        .qq_para2({\bri_qq_load_0_qq_para2_[5] , 
        \bri_qq_load_0_qq_para2_[4] , \bri_qq_load_0_qq_para2_[3] , 
        \bri_qq_load_0_qq_para2_[2] , \bri_qq_load_0_qq_para2_[1] , 
        \bri_qq_load_0_qq_para2_[0] }), .qq_para3({
        \bri_qq_load_0_qq_para3_[5] , \bri_qq_load_0_qq_para3_[4] , 
        \bri_qq_load_0_qq_para3_[3] , \bri_qq_load_0_qq_para3_[2] , 
        \bri_qq_load_0_qq_para3_[1] , \bri_qq_load_0_qq_para3_[0] }), 
        .i({\qq_coder_0_i_[3] , \qq_coder_0_i_[2] , \qq_coder_0_i_[1] , 
        \qq_coder_0_i_[0] }));
    GND GND (.Y(GND_net));
    bri_timer bri_timer_0 (.clk_dds(clk_dds), .clk_4f_en(clk_4f_en), 
        .rst_n(rst_n), .state_start(state_start), .timer_stop(
        bri_coder_0_half), .count({\bri_timer_0_count_[7] , 
        \bri_timer_0_count_[6] , \bri_timer_0_count_[5] , 
        \bri_timer_0_count_[4] , \bri_timer_0_count_[3] , 
        \bri_timer_0_count_[2] , \bri_timer_0_count_[1] , 
        \bri_timer_0_count_[0] }));
    bri_coder bri_coder_0 (.clk_dds(clk_dds), .clk_4f_en(clk_4f_en), 
        .rst_n(rst_n), .state_start(state_start), .quar_delay(
        quar_delay), .phase(phase), .count({\bri_timer_0_count_[7] , 
        \bri_timer_0_count_[6] , \bri_timer_0_count_[5] , 
        \bri_timer_0_count_[4] , \bri_timer_0_count_[3] , 
        \bri_timer_0_count_[2] , \bri_timer_0_count_[1] , 
        \bri_timer_0_count_[0] }), .half_para({
        \bri_qq_load_0_half_para_0_[7] , 
        \bri_qq_load_0_half_para_0_[6] , 
        \bri_qq_load_0_half_para_0_[5] , 
        \bri_qq_load_0_half_para_0_[4] , 
        \bri_qq_load_0_half_para_0_[3] , 
        \bri_qq_load_0_half_para_0_[2] , 
        \bri_qq_load_0_half_para_0_[1] , 
        \bri_qq_load_0_half_para_0_[0] }), .half(bri_coder_0_half), 
        .bri_cycle(bri_cycle), .i({\bri_coder_0_i_1_[4] , 
        \bri_coder_0_i_1_[3] , \bri_coder_0_i_1_[2] , 
        \bri_coder_0_i_1_[1] , \bri_coder_0_i_1_[0] }), .turn_delay(
        turn_delay));
    VCC VCC (.Y(VCC_net));
    qq_state qq_state_1 (.clk_sys(clk_sys), .rst_n(rst_n), .Q1Q8_Q2Q7(
        Q2Q7), .Q3Q6_Q4Q5(Q4Q5), .stateover(qq_state_1_stateover), .i({
        \qq_coder_1_i_[3] , \qq_coder_1_i_[2] , \qq_coder_1_i_[1] , 
        \qq_coder_1_i_[0] }));
    qq_timer qq_timer_0 (.clk_sys(clk_sys), .rst_n(rst_n), .statestart(
        up), .stateover(qq_state_0_stateover), .count({
        \qq_timer_0_count_[4] , \qq_timer_0_count_[3] , 
        \qq_timer_0_count_[2] , \qq_timer_0_count_[1] , 
        \qq_timer_0_count_[0] }));
    qq_timer qq_timer_1 (.clk_sys(clk_sys), .rst_n(rst_n), .statestart(
        down), .stateover(qq_state_1_stateover), .count({
        \qq_timer_1_count_[4] , \qq_timer_1_count_[3] , 
        \qq_timer_1_count_[2] , \qq_timer_1_count_[1] , 
        \qq_timer_1_count_[0] }));
    qq_coder qq_coder_1 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(down), .count({\qq_timer_1_count_[4] , 
        \qq_timer_1_count_[3] , \qq_timer_1_count_[2] , 
        \qq_timer_1_count_[1] , \qq_timer_1_count_[0] }), .qq_para1({
        \bri_qq_load_0_qq_para1_[3] , \bri_qq_load_0_qq_para1_[2] , 
        \bri_qq_load_0_qq_para1_[1] , \bri_qq_load_0_qq_para1_[0] }), 
        .qq_para2({\bri_qq_load_0_qq_para2_[5] , 
        \bri_qq_load_0_qq_para2_[4] , \bri_qq_load_0_qq_para2_[3] , 
        \bri_qq_load_0_qq_para2_[2] , \bri_qq_load_0_qq_para2_[1] , 
        \bri_qq_load_0_qq_para2_[0] }), .qq_para3({
        \bri_qq_load_0_qq_para3_[5] , \bri_qq_load_0_qq_para3_[4] , 
        \bri_qq_load_0_qq_para3_[3] , \bri_qq_load_0_qq_para3_[2] , 
        \bri_qq_load_0_qq_para3_[1] , \bri_qq_load_0_qq_para3_[0] }), 
        .i({\qq_coder_1_i_[3] , \qq_coder_1_i_[2] , \qq_coder_1_i_[1] , 
        \qq_coder_1_i_[0] }));
    bri_state bri_state_0 (.clk_dds(clk_dds), .clk_4f_en(clk_4f_en), 
        .rst_n(rst_n), .i({\bri_coder_0_i_1_[4] , 
        \bri_coder_0_i_1_[3] , \bri_coder_0_i_1_[2] , 
        \bri_coder_0_i_1_[1] , \bri_coder_0_i_1_[0] }), .up(up), .down(
        down));
    bri_qq_load bri_qq_load_0 (.clk_sys(clk_sys), .pluse_load(
        pluse_load), .bri_para({bri_para[7], bri_para[6], bri_para[5], 
        bri_para[4], bri_para[3], bri_para[2], bri_para[1], 
        bri_para[0]}), .qq_para({qq_para[15], qq_para[14], qq_para[13], 
        qq_para[12], qq_para[11], qq_para[10], qq_para[9], qq_para[8], 
        qq_para[7], qq_para[6], qq_para[5], qq_para[4], qq_para[3], 
        qq_para[2], qq_para[1], qq_para[0]}), .half_para({
        \bri_qq_load_0_half_para_0_[7] , 
        \bri_qq_load_0_half_para_0_[6] , 
        \bri_qq_load_0_half_para_0_[5] , 
        \bri_qq_load_0_half_para_0_[4] , 
        \bri_qq_load_0_half_para_0_[3] , 
        \bri_qq_load_0_half_para_0_[2] , 
        \bri_qq_load_0_half_para_0_[1] , 
        \bri_qq_load_0_half_para_0_[0] }), .qq_para1({
        \bri_qq_load_0_qq_para1_[3] , \bri_qq_load_0_qq_para1_[2] , 
        \bri_qq_load_0_qq_para1_[1] , \bri_qq_load_0_qq_para1_[0] }), 
        .qq_para2({\bri_qq_load_0_qq_para2_[5] , 
        \bri_qq_load_0_qq_para2_[4] , \bri_qq_load_0_qq_para2_[3] , 
        \bri_qq_load_0_qq_para2_[2] , \bri_qq_load_0_qq_para2_[1] , 
        \bri_qq_load_0_qq_para2_[0] }), .qq_para3({
        \bri_qq_load_0_qq_para3_[5] , \bri_qq_load_0_qq_para3_[4] , 
        \bri_qq_load_0_qq_para3_[3] , \bri_qq_load_0_qq_para3_[2] , 
        \bri_qq_load_0_qq_para3_[1] , \bri_qq_load_0_qq_para3_[0] }));
    
endmodule
