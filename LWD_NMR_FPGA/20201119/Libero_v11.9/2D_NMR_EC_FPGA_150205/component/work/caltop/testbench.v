//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Thu Aug 05 09:09:56 2010
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
// Instantiate Unit Under Test:  caltop
//////////////////////////////////////////////////////////////////////
caltop caltop_0 (
    // Inputs
    .cal_en({1{1'b0}}),
    .cal_load({1{1'b0}}),
    .cal_reset(NSYSRESET),
    .cal_clkin(SYSCLK),
    .cal_divcount({6{1'b0}}),

    // Outputs
    .cal_out( )

    // Inouts

);

endmodule

