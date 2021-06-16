//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Mar 18 09:31:43 2014
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
// Instantiate Unit Under Test:  scantop
//////////////////////////////////////////////////////////////////////
scantop scantop_0 (
    // Inputs
    .scanstart({1{1'b0}}),
    .clk_sys(SYSCLK),
    .scanrst(NSYSRESET),
    .scanload({1{1'b0}}),
    .scanchoice({1{1'b0}}),
    .datain({16{1'b0}}),

    // Outputs
    .interrupt( ),
    .sw_acq2( ),
    .sw_acq1( ),
    .dumpoff_ctr( ),
    .dumpon_ctr( ),
    .calctrl( ),
    .dds_conf( ),
    .rt_sw( ),
    .soft_d( ),
    .s_acq( )

    // Inouts

);

endmodule

