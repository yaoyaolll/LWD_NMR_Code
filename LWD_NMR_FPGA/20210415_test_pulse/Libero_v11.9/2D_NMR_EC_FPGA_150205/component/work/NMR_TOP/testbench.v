//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Thu Feb 05 17:06:25 2015
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
// Instantiate Unit Under Test:  NMR_TOP
//////////////////////////////////////////////////////////////////////
NMR_TOP NMR_TOP_0 (
    // Inputs
    .zcs2({1{1'b0}}),
    .xwe({1{1'b0}}),
    .OCX40MHz({1{1'b0}}),
    .ddsclkout(SYSCLK),
    .tri_ctrl({1{1'b0}}),
    .gpio({1{1'b0}}),
    .XRD({1{1'b0}}),
    .xa({19{1'b0}}),
    .ADC({12{1'b0}}),

    // Outputs
    .ddsfqud( ),
    .ddsreset( ),
    .ddswclk( ),
    .cal_out( ),
    .ddsdata( ),
    .interupt( ),
    .rt_sw( ),
    .soft_dump( ),
    .sw_acq1( ),
    .sw_acq2( ),
    .dumpon( ),
    .dumpoff( ),
    .Q1Q8( ),
    .Q3Q6( ),
    .Q4Q5( ),
    .Q2Q7( ),
    .calcuinter( ),
    .sigtimeup( ),
    .k1( ),
    .k2( ),
    .pulse_start( ),
    .pd_pulse_en( ),
    .Acq_clk( ),
    .sd_acq_en( ),
    .s_acq180( ),
    .GLA( ),
    .relayclose_on( ),

    // Inouts
    .xd( )

);

endmodule

