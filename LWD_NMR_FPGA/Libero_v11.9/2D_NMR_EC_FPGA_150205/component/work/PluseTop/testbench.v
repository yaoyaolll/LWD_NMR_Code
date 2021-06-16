//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Mar 18 09:32:34 2014
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
// Instantiate Unit Under Test:  PluseTop
//////////////////////////////////////////////////////////////////////
PluseTop PluseTop_0 (
    // Inputs
    .pluserst(NSYSRESET),
    .plusestart({1{1'b0}}),
    .pluseload({1{1'b0}}),
    .pluseloadchoice({1{1'b0}}),
    .clk_sys(SYSCLK),
    .plusedatain({16{1'b0}}),

    // Outputs
    .rt_sw( ),
    .sw_acq1( ),
    .sw_acq2( ),
    .soft_d( ),
    .dump_start( ),
    .pluse_acq( ),
    .pluseinter( ),
    .dds_config( ),
    .pluse_start( ),
    .dumpoff_ctr( ),
    .tetw_pluse( ),
    .offtest( )

    // Inouts

);

endmodule

