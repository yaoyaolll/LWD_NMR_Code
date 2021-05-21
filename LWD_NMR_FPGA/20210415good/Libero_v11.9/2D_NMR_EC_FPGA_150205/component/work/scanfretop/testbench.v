//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon Sep 14 08:54:54 2009
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
    #(SYSCLK_PERIOD / 2) SYSCLK <= !SYSCLK;


//////////////////////////////////////////////////////////////////////
// Instantiate Unit Under Test:  scanfretop
//////////////////////////////////////////////////////////////////////
scanfretop scanfretop_0 (
    // Inputs
    .zcs2({1{1'b0}}),
    .xwe({1{1'b0}}),
    .CLKA(SYSCLK),
    .ddsclkin(SYSCLK),
    .rdclk(SYSCLK),
    .xa({19{1'b0}}),
    .w_data({12{1'b0}}),

    // Outputs
    .ddsfqud( ),
    .ddsreset( ),
    .ddswclk( ),
    .ddsdata( ),
    .sw_acq2( ),
    .sw_acq1( ),
    .rt_sw( ),
    .soft_d( ),
    .scanover( ),
    .calout( ),
    .clktodds( ),
    .n_acqclk( ),

    // Inouts
    .xd( )

);

endmodule

