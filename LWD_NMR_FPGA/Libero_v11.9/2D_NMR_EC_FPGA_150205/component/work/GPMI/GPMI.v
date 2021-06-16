`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module GPMI(
       dsp_reset,
       rst_nr2,
       clk,
       xwe,
       xzcs2,
       tri_ctrl,
       code_en,
       xd,
       datain,
       dataout
    );
input  dsp_reset;
output rst_nr2;
input  clk;
input  xwe;
input  xzcs2;
input  tri_ctrl;
output code_en;
inout  [15:0] xd;
input  [15:0] datain;
output [15:0] dataout;

    wire INV_0_Y, GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    INV INV_0 (.A(dsp_reset), .Y(INV_0_Y));
    GND GND (.Y(GND_net));
    xwe_xzcs2_syn xwe_xzcs2_syn_0 (.rst_n(rst_nr2), .clk_sys(clk), 
        .xwe(xwe), .xzcs2(xzcs2), .code_en(code_en));
    tri_state tri_state_0 (.tri_ctrl(tri_ctrl), .zcs2(xzcs2), .xd({
        xd[15], xd[14], xd[13], xd[12], xd[11], xd[10], xd[9], xd[8], 
        xd[7], xd[6], xd[5], xd[4], xd[3], xd[2], xd[1], xd[0]}), 
        .dataout({dataout[15], dataout[14], dataout[13], dataout[12], 
        dataout[11], dataout[10], dataout[9], dataout[8], dataout[7], 
        dataout[6], dataout[5], dataout[4], dataout[3], dataout[2], 
        dataout[1], dataout[0]}), .datain({datain[15], datain[14], 
        datain[13], datain[12], datain[11], datain[10], datain[9], 
        datain[8], datain[7], datain[6], datain[5], datain[4], 
        datain[3], datain[2], datain[1], datain[0]}));
    rst_n_module rst_n_module_0 (.clk(clk), .rst_n(INV_0_Y), .rst_nr2(
        rst_nr2));
    
endmodule
