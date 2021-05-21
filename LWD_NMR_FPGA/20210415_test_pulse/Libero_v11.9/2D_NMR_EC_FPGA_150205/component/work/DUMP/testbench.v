//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Apr 24 14:08:20 2012
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
// Instantiate Unit Under Test:  DUMP
//////////////////////////////////////////////////////////////////////
DUMP DUMP_0 (
    // Inputs
    .rst_n(NSYSRESET),
    .state_start({1{1'b0}}),
    .clk_sys(SYSCLK),
    .dump_load({1{1'b0}}),
    .bri_cycle({1{1'b0}}),
    .pluse_start({1{1'b0}}),
    .dump_choice({3{1'b0}}),
    .dump_para({12{1'b0}}),

    // Outputs
    .dump_off( ),
    .dump_on( )

    // Inouts

);

endmodule

