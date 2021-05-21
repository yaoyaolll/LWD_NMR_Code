`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module ClockManagement(
       OCX40MHz,
       GLA,
       rst_n,
       start,
       timeup,
       clock_10khz,
       timer_para
    );
input  OCX40MHz;
output GLA;
input  rst_n;
input  start;
output timeup;
output clock_10khz;
input  [15:0] timer_para;

    wire clk_div500_0_clk_5K, pllclk_0_GLB, GND_net, VCC_net;
    
    long_timer long_timer_0 (.clk_5K(clk_div500_0_clk_5K), .clk_sys(
        GLA), .rst_n(rst_n), .start(start), .work(timeup), .timeup(
        timeup), .timer_para({timer_para[15], timer_para[14], 
        timer_para[13], timer_para[12], timer_para[11], timer_para[10], 
        timer_para[9], timer_para[8], timer_para[7], timer_para[6], 
        timer_para[5], timer_para[4], timer_para[3], timer_para[2], 
        timer_para[1], timer_para[0]}));
    clk_div500 clk_div500_0 (.clk_5M(pllclk_0_GLB), .clk_sys(GLA), 
        .rst_n(rst_n), .clk_5K(clk_div500_0_clk_5K));
    VCC VCC (.Y(VCC_net));
    pllclk pllclk_0 (.POWERDOWN(VCC_net), .CLKA(OCX40MHz), .LOCK(), 
        .GLA(GLA), .GLB(pllclk_0_GLB));
    GND GND (.Y(GND_net));
    clk_10k clk_10k_0 (.clk_5M(pllclk_0_GLB), .clk_sys(GLA), .rst_n(
        rst_n), .clock_10khz(clock_10khz));
    
endmodule
