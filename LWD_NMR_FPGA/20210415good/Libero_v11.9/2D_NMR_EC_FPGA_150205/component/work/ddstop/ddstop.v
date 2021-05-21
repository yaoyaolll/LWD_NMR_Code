`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module ddstop(
       dds_choice,
       dds_load,
       ddsfqud,
       ddswclk,
       ddsreset,
       dds_reset,
       ddsdata,
       dds_clken,
       dds_clk,
       dds_datain
    );
input  dds_choice;
input  dds_load;
output ddsfqud;
output ddswclk;
output ddsreset;
input  dds_reset;
output ddsdata;
input  dds_clken;
input  dds_clk;
input  [15:0] dds_datain;

    wire AND2_0_Y, GND_net, VCC_net;
    
    ddsconfig ddsconfig_0 (.reset(dds_reset), .clk(AND2_0_Y), .ddswclk(
        ddswclk), .ddsreset(ddsreset), .ddsfqud(ddsfqud), .ddsdata(
        ddsdata), .load(dds_load), .choice(dds_choice), .datain({
        dds_datain[15], dds_datain[14], dds_datain[13], dds_datain[12], 
        dds_datain[11], dds_datain[10], dds_datain[9], dds_datain[8], 
        dds_datain[7], dds_datain[6], dds_datain[5], dds_datain[4], 
        dds_datain[3], dds_datain[2], dds_datain[1], dds_datain[0]}));
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    AND2 AND2_0 (.A(dds_clken), .B(dds_clk), .Y(AND2_0_Y));
    
endmodule
