`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module ppheavy_ontimer(
       clk_10k,
       rst_n,
       rst_state,
       ppheavy_en,
       clk_sys,
       start
    );
input  clk_10k;
input  rst_n;
input  rst_state;
input  ppheavy_en;
input  clk_sys;
output start;

    wire AND2_0_Y, GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    ppheavy_on_timer_md ppheavy_on_timer_md_0 (.clk_sys(clk_sys), 
        .rst_state(rst_state), .rst_n(rst_n), .clk_10k(clk_10k), 
        .state_start(AND2_0_Y), .start(start));
    GND GND (.Y(GND_net));
    AND2 AND2_0 (.A(rst_state), .B(ppheavy_en), .Y(AND2_0_Y));
    
endmodule
