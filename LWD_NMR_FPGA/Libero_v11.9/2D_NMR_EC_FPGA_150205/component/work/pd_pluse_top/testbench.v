//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Sat Jan 31 21:27:22 2015
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
// Instantiate Unit Under Test:  pd_pluse_top
//////////////////////////////////////////////////////////////////////
pd_pluse_top pd_pluse_top_0 (
    // Inputs
    .dds({1{1'b0}}),
    .rst_n(NSYSRESET),
    .pluse_start({1{1'b0}}),
    .clk_sys(SYSCLK),
    .pd_pluse_load({1{1'b0}}),
    .bb_ch({1{1'b0}}),
    .tetw_pluse({1{1'b0}}),
    .pd_pluse_choice({4{1'b0}}),
    .pd_pluse_data({16{1'b0}}),

    // Outputs
    .en( )

    // Inouts

);

endmodule

