//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Mar 18 09:31:56 2014
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
// Instantiate Unit Under Test:  noisetop
//////////////////////////////////////////////////////////////////////
noisetop noisetop_0 (
    // Inputs
    .clk_sys(SYSCLK),
    .noisestart({1{1'b0}}),
    .nchoice({1{1'b0}}),
    .nload({1{1'b0}}),
    .noiserst(NSYSRESET),
    .ndatain({16{1'b0}}),

    // Outputs
    .interrupt( ),
    .n_acq( ),
    .rt_sw( ),
    .sw_acq2( ),
    .soft_d( ),
    .sw_acq1( ),
    .dumpoff_ctr( ),
    .dumpon_ctr( )

    // Inouts

);

endmodule

