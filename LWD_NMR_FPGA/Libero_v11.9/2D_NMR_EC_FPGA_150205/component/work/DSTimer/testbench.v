//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Thu Jan 22 00:38:34 2015
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
// Instantiate Unit Under Test:  DSTimer
//////////////////////////////////////////////////////////////////////
DSTimer DSTimer_0 (
    // Inputs
    .clk_sys(SYSCLK),
    .dump_sustain({1{1'b0}}),
    .rst_n(NSYSRESET),
    .state_start({1{1'b0}}),
    .clk_10k(SYSCLK),
    .dump_sustain_data({4{1'b0}}),

    // Outputs
    .start( )

    // Inouts

);

endmodule

