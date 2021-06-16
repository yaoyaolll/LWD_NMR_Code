//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon Mar 17 21:23:47 2014
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
// Instantiate Unit Under Test:  STATE_1MS_TOP
//////////////////////////////////////////////////////////////////////
STATE_1MS_TOP STATE_1MS_TOP_0 (
    // Inputs
    .state_1ms_rst_n(NSYSRESET),
    .clk_sys(SYSCLK),
    .state_1ms_start({1{1'b0}}),
    .load({1{1'b0}}),
    .loadchoice({4{1'b0}}),
    .datain({16{1'b0}}),

    // Outputs
    .reset_out( ),
    .dump_start( ),
    .pluse_start( ),
    .bri_cycle( ),
    .rt_sw( ),
    .soft_dump( )

    // Inouts

);

endmodule

