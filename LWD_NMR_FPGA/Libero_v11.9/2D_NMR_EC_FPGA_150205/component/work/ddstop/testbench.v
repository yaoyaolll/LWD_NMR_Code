//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Dec 07 16:44:30 2010
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
// Instantiate Unit Under Test:  ddstop
//////////////////////////////////////////////////////////////////////
ddstop ddstop_0 (
    // Inputs
    .dds_choice({1{1'b0}}),
    .dds_load({1{1'b0}}),
    .dds_reset(NSYSRESET),
    .dds_clken(SYSCLK),
    .dds_clk(SYSCLK),
    .dds_datain({16{1'b0}}),

    // Outputs
    .ddsfqud( ),
    .ddswclk( ),
    .ddsreset( ),
    .ddsdata( )

    // Inouts

);

endmodule

