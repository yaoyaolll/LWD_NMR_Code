`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module CAL(
       clk_sys,
       rst_n,
       cal_start,
       clk_dds,
       cal,
       cal_load,
       cal_para
    );
input  clk_sys;
input  rst_n;
input  cal_start;
input  clk_dds;
output cal;
input  cal_load;
input  [5:0] cal_para;

    wire \cal_load_0_cal_para_out_[5] , \cal_load_0_cal_para_out_[4] , 
        \cal_load_0_cal_para_out_[3] , \cal_load_0_cal_para_out_[2] , 
        \cal_load_0_cal_para_out_[1] , \cal_load_0_cal_para_out_[0] , 
        GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    cal_load cal_load_0 (.clk_sys(clk_sys), .cal_load(cal_load), 
        .cal_para({cal_para[5], cal_para[4], cal_para[3], cal_para[2], 
        cal_para[1], cal_para[0]}), .cal_para_out({
        \cal_load_0_cal_para_out_[5] , \cal_load_0_cal_para_out_[4] , 
        \cal_load_0_cal_para_out_[3] , \cal_load_0_cal_para_out_[2] , 
        \cal_load_0_cal_para_out_[1] , \cal_load_0_cal_para_out_[0] }));
    GND GND (.Y(GND_net));
    cal_div cal_div_0 (.clk_dds(clk_dds), .rst_n(rst_n), .cal_start(
        cal_start), .cal(cal), .cal_para({
        \cal_load_0_cal_para_out_[5] , \cal_load_0_cal_para_out_[4] , 
        \cal_load_0_cal_para_out_[3] , \cal_load_0_cal_para_out_[2] , 
        \cal_load_0_cal_para_out_[1] , \cal_load_0_cal_para_out_[0] }));
    
endmodule
