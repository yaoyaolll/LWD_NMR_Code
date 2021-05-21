//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Mar 18 09:51:29 2014
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
// Instantiate Unit Under Test:  DDS
//////////////////////////////////////////////////////////////////////
DDS DDS_0 (
    // Inputs
    .dds_load({1{1'b0}}),
    .dds_choice({1{1'b0}}),
    .clk_sys(SYSCLK),
    .rst_n(NSYSRESET),
    .state_start({1{1'b0}}),
    .dds_para({16{1'b0}}),

    // Outputs
    .reset( ),
    .fq_ud( ),
    .w_clk( ),
    .data( )

    // Inouts

);

endmodule

