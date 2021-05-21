//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Wed Dec 08 11:13:31 2010
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
// Instantiate Unit Under Test:  scanstatetop
//////////////////////////////////////////////////////////////////////
scanstatetop scanstatetop_0 (
    // Inputs
    .timeclk(SYSCLK),
    .scanstart({1{1'b0}}),
    .scanrst(NSYSRESET),
    .noiserst(NSYSRESET),
    .noisestart({1{1'b0}}),
    .n_s_change({1{1'b0}}),
    .ctrl({1{1'b0}}),
    .pluse_acq({1{1'b0}}),
    .scanload({1{1'b0}}),
    .scanchoice({1{1'b0}}),
    .nload({1{1'b0}}),
    .nchoice({1{1'b0}}),
    .datain({16{1'b0}}),
    .ndatain({16{1'b0}}),

    // Outputs
    .dds_conf( ),
    .calctrl( ),
    .s_acq( ),
    .soft_d( ),
    .sw_acq2( ),
    .sw_acq1( ),
    .intertodsp( ),
    .rt_sw( ),
    .n_en( ),
    .resetout( ),
    .dump_on( ),
    .dump_off( )

    // Inouts

);

endmodule

