//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon Sep 22 15:34:42 2014
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
// Instantiate Unit Under Test:  sd_acq_top
//////////////////////////////////////////////////////////////////////
sd_acq_top sd_acq_top_0 (
    // Inputs
    .dds({1{1'b0}}),
    .rst_n(NSYSRESET),
    .s_acq1({1{1'b0}}),
    .clk_sys(SYSCLK),
    .sd_sacq_load({1{1'b0}}),
    .bb_ch({1{1'b0}}),
    .s_acq180({1{1'b0}}),
    .long_opentime({1{1'b0}}),
    .sd_sacq_choice({4{1'b0}}),
    .sd_sacq_data({16{1'b0}}),

    // Outputs
    .en( )

    // Inouts

);

endmodule

