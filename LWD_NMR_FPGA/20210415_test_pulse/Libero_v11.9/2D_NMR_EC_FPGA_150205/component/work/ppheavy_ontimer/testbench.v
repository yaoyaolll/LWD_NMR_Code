//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon May 20 17:07:58 2013
// Testbench Template
// This is a basic testbench that instantiates your design with basic 
// clock and reset pins connected.  If your design has special
// clock/reset or testbench driver requirements then you should 
// copy this file and modify it. 
//////////////////////////////////////////////////////////////////////

`timescale 1ns/100ps

module testbench;

parameter SYSCLK_PERIOD = 100; // 10MHz

reg SYSCLK;
reg NSYSRESET;

initial
begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b0;
end

//////////////////////////////////////////////////////////////////////
// Reset Pulse
//////////////////////////////////////////////////////////////////////
initial
begin
    #(SYSCLK_PERIOD * 10 )
        NSYSRESET = 1'b1;
end


//////////////////////////////////////////////////////////////////////
// 10MHz Clock Driver
//////////////////////////////////////////////////////////////////////
always @(SYSCLK)
    #(SYSCLK_PERIOD / 2.0) SYSCLK <= !SYSCLK;


//////////////////////////////////////////////////////////////////////
// Instantiate Unit Under Test:  ppheavy_ontimer
//////////////////////////////////////////////////////////////////////
ppheavy_ontimer ppheavy_ontimer_0 (
    // Inputs
    .clk_10k(SYSCLK),
    .rst_n(NSYSRESET),
    .rst_state(NSYSRESET),
    .ppheavy_en({1{1'b0}}),
    .clk_sys(SYSCLK),

    // Outputs
    .start( )

    // Inouts

);

endmodule

