`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module timer_top(
       clk_sys,
       rst_n,
       clk_en_scan,
       clk_en_st1ms,
       clk_en_pluse,
       clk_en_scale,
       clk_en_noise,
       datain_state_1ms,
       datain_pluse,
       datain_scale,
       datain_scan,
       datain_noise,
       start,
       state_over_in
    );
input  clk_sys;
input  rst_n;
output clk_en_scan;
output clk_en_st1ms;
output clk_en_pluse;
output clk_en_scale;
output clk_en_noise;
input  [19:0] datain_state_1ms;
input  [19:0] datain_pluse;
input  [21:0] datain_scale;
input  [19:0] datain_scan;
input  [19:0] datain_noise;
input  [4:0] start;
input  [3:0] state_over_in;

    wire \state_switch_0_dataout_[21] , \state_switch_0_dataout_[20] , 
        \state_switch_0_dataout_[19] , \state_switch_0_dataout_[18] , 
        \state_switch_0_dataout_[17] , \state_switch_0_dataout_[16] , 
        \state_switch_0_dataout_[15] , \state_switch_0_dataout_[14] , 
        \state_switch_0_dataout_[13] , \state_switch_0_dataout_[12] , 
        \state_switch_0_dataout_[11] , \state_switch_0_dataout_[10] , 
        \state_switch_0_dataout_[9] , \state_switch_0_dataout_[8] , 
        \state_switch_0_dataout_[7] , \state_switch_0_dataout_[6] , 
        \state_switch_0_dataout_[5] , \state_switch_0_dataout_[4] , 
        \state_switch_0_dataout_[3] , \state_switch_0_dataout_[2] , 
        \state_switch_0_dataout_[1] , \state_switch_0_dataout_[0] , 
        state_switch_0_state_over_n, state_switch_0_state_start, 
        timer_0_time_up, GND_net, VCC_net;
    
    timer timer_0 (.rst_n(rst_n), .clk_sys(clk_sys), .work_n(
        timer_0_time_up), .state_start(state_switch_0_state_start), 
        .state_over_n(state_switch_0_state_over_n), .time_up(
        timer_0_time_up), .datain({\state_switch_0_dataout_[21] , 
        \state_switch_0_dataout_[20] , \state_switch_0_dataout_[19] , 
        \state_switch_0_dataout_[18] , \state_switch_0_dataout_[17] , 
        \state_switch_0_dataout_[16] , \state_switch_0_dataout_[15] , 
        \state_switch_0_dataout_[14] , \state_switch_0_dataout_[13] , 
        \state_switch_0_dataout_[12] , \state_switch_0_dataout_[11] , 
        \state_switch_0_dataout_[10] , \state_switch_0_dataout_[9] , 
        \state_switch_0_dataout_[8] , \state_switch_0_dataout_[7] , 
        \state_switch_0_dataout_[6] , \state_switch_0_dataout_[5] , 
        \state_switch_0_dataout_[4] , \state_switch_0_dataout_[3] , 
        \state_switch_0_dataout_[2] , \state_switch_0_dataout_[1] , 
        \state_switch_0_dataout_[0] }));
    state_switch state_switch_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .time_up_in(timer_0_time_up), .state_start(
        state_switch_0_state_start), .state_over_n(
        state_switch_0_state_over_n), .clk_en_scale(clk_en_scale), 
        .clk_en_scan(clk_en_scan), .clk_en_noise(clk_en_noise), 
        .clk_en_pluse(clk_en_pluse), .clk_en_st1ms(clk_en_st1ms), 
        .start({start[4], start[3], start[2], start[1], start[0]}), 
        .state_over_in({state_over_in[3], state_over_in[2], 
        state_over_in[1], state_over_in[0]}), .datain_scale({
        datain_scale[21], datain_scale[20], datain_scale[19], 
        datain_scale[18], datain_scale[17], datain_scale[16], 
        datain_scale[15], datain_scale[14], datain_scale[13], 
        datain_scale[12], datain_scale[11], datain_scale[10], 
        datain_scale[9], datain_scale[8], datain_scale[7], 
        datain_scale[6], datain_scale[5], datain_scale[4], 
        datain_scale[3], datain_scale[2], datain_scale[1], 
        datain_scale[0]}), .datain_scan({datain_scan[19], 
        datain_scan[18], datain_scan[17], datain_scan[16], 
        datain_scan[15], datain_scan[14], datain_scan[13], 
        datain_scan[12], datain_scan[11], datain_scan[10], 
        datain_scan[9], datain_scan[8], datain_scan[7], datain_scan[6], 
        datain_scan[5], datain_scan[4], datain_scan[3], datain_scan[2], 
        datain_scan[1], datain_scan[0]}), .datain_noise({
        datain_noise[19], datain_noise[18], datain_noise[17], 
        datain_noise[16], datain_noise[15], datain_noise[14], 
        datain_noise[13], datain_noise[12], datain_noise[11], 
        datain_noise[10], datain_noise[9], datain_noise[8], 
        datain_noise[7], datain_noise[6], datain_noise[5], 
        datain_noise[4], datain_noise[3], datain_noise[2], 
        datain_noise[1], datain_noise[0]}), .datain_pluse({
        datain_pluse[19], datain_pluse[18], datain_pluse[17], 
        datain_pluse[16], datain_pluse[15], datain_pluse[14], 
        datain_pluse[13], datain_pluse[12], datain_pluse[11], 
        datain_pluse[10], datain_pluse[9], datain_pluse[8], 
        datain_pluse[7], datain_pluse[6], datain_pluse[5], 
        datain_pluse[4], datain_pluse[3], datain_pluse[2], 
        datain_pluse[1], datain_pluse[0]}), .datain_state_1ms({
        datain_state_1ms[19], datain_state_1ms[18], 
        datain_state_1ms[17], datain_state_1ms[16], 
        datain_state_1ms[15], datain_state_1ms[14], 
        datain_state_1ms[13], datain_state_1ms[12], 
        datain_state_1ms[11], datain_state_1ms[10], 
        datain_state_1ms[9], datain_state_1ms[8], datain_state_1ms[7], 
        datain_state_1ms[6], datain_state_1ms[5], datain_state_1ms[4], 
        datain_state_1ms[3], datain_state_1ms[2], datain_state_1ms[1], 
        datain_state_1ms[0]}), .dataout({\state_switch_0_dataout_[21] , 
        \state_switch_0_dataout_[20] , \state_switch_0_dataout_[19] , 
        \state_switch_0_dataout_[18] , \state_switch_0_dataout_[17] , 
        \state_switch_0_dataout_[16] , \state_switch_0_dataout_[15] , 
        \state_switch_0_dataout_[14] , \state_switch_0_dataout_[13] , 
        \state_switch_0_dataout_[12] , \state_switch_0_dataout_[11] , 
        \state_switch_0_dataout_[10] , \state_switch_0_dataout_[9] , 
        \state_switch_0_dataout_[8] , \state_switch_0_dataout_[7] , 
        \state_switch_0_dataout_[6] , \state_switch_0_dataout_[5] , 
        \state_switch_0_dataout_[4] , \state_switch_0_dataout_[3] , 
        \state_switch_0_dataout_[2] , \state_switch_0_dataout_[1] , 
        \state_switch_0_dataout_[0] }));
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    
endmodule
