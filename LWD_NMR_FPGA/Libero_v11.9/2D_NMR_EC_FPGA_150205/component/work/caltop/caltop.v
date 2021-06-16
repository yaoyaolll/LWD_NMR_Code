`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module caltop(
       cal_en,
       cal_out,
       cal_load,
       cal_reset,
       cal_clkin,
       cal_divcount
    );
input  cal_en;
output cal_out;
input  cal_load;
input  cal_reset;
input  cal_clkin;
input  [5:0] cal_divcount;

    wire cal_ddsdivide_0_clkout, GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    AND2 AND2_0 (.A(cal_ddsdivide_0_clkout), .B(cal_en), .Y(cal_out));
    cal_ddsdivide cal_ddsdivide_0 (.reset(cal_reset), .clkin(cal_clkin)
        , .load(cal_load), .clkout(cal_ddsdivide_0_clkout), .divcount({
        cal_divcount[5], cal_divcount[4], cal_divcount[3], 
        cal_divcount[2], cal_divcount[1], cal_divcount[0]}));
    
endmodule
