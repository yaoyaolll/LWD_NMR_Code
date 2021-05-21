`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module DSTimer(
       clk_sys,
       dump_sustain,
       rst_n,
       start,
       state_start,
       clk_10k,
       dump_sustain_data
    );
input  clk_sys;
input  dump_sustain;
input  rst_n;
output start;
input  state_start;
input  clk_10k;
input  [3:0] dump_sustain_data;

    wire AND2_0_Y, DFI0_1_QN, net_0, GND_net, VCC_net;
    
    dump_sustain_timer dump_sustain_timer_0 (.clk_sys(clk_sys), .rst_n(
        rst_n), .state_start(state_start), .start(start), .load(
        AND2_0_Y), .clk_10k(clk_10k), .dump_sustain_data({
        dump_sustain_data[3], dump_sustain_data[2], 
        dump_sustain_data[1], dump_sustain_data[0]}));
    VCC VCC (.Y(VCC_net));
    DFN0 DFN0_0 (.D(dump_sustain), .CLK(clk_sys), .Q(net_0));
    GND GND (.Y(GND_net));
    DFI0 DFI0_1 (.D(net_0), .CLK(clk_sys), .QN(DFI0_1_QN));
    AND2 AND2_0 (.A(net_0), .B(DFI0_1_QN), .Y(AND2_0_Y));
    
endmodule
