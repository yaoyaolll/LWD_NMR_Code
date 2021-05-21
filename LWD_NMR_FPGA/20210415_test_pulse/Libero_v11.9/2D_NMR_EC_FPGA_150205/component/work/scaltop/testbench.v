//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Tue Mar 18 09:32:16 2014
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
// Instantiate Unit Under Test:  scaltop
//////////////////////////////////////////////////////////////////////
scaltop scaltop_0 (
    // Inputs
    .scalerst(NSYSRESET),
    .scaleload({1{1'b0}}),
    .scalstart({1{1'b0}}),
    .pn_change({1{1'b0}}),
    .clk_sys(SYSCLK),
    .scaledatain({16{1'b0}}),
    .scalechoice({5{1'b0}}),

    // Outputs
    .sw_acq2( ),
    .sw_acq1( ),
    .soft_d( ),
    .rt_sw( ),
    .calcuinter( ),
    .dds_conf( ),
    .s_acq( ),
    .reset_out( ),
    .load_out( ),
    .stateinter( ),
    .dump_start( ),
    .pluse_start( ),
    .pn_out( ),
    .dumpoff_ctr( ),
    .bb_ch( ),
    .tetw_pluse( ),
    .offtest( ),
    .s_acq180( ),
    .ppheavy_test( ),
    .strippluse( ),
    .s_acqnum( )

    // Inouts

);

endmodule

