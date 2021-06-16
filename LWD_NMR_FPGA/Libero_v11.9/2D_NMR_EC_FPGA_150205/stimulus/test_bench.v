//////////////////////////////////////////////////////////////////////
// Created by Microsemi SmartDesign Mon May 17 15:07:34 2021
// Testbench Template
// This is a basic testbench that instantiates your design with basic 
// clock and reset pins connected.  If your design has special
// clock/reset or testbench driver requirements then you should 
// copy this file and modify it. 
//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: test_bench.v
// File history:
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <Description here>
//
// Targeted device: <Family::ProASIC3> <Die::A3P1000> <Package::208 PQFP>
// Author: <Name>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 

`timescale 1ns/100ps

module test_bench;

parameter SYSCLK_PERIOD = 10;// 100MHZ

reg SYSCLK;
reg NSYSRESET;

reg SOFT_D;
reg RT_SW;
reg SW1;
reg SW2;

wire outp; 

initial
begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b0;
	SOFT_D = 1'b0;
	RT_SW = 1'b0;
	SW1 = 1'b0;
	SW2 = 1'b0;
end

//////////////////////////////////////////////////////////////////////
// Reset Pulse
//////////////////////////////////////////////////////////////////////
initial
begin
    #(SYSCLK_PERIOD * 10 )
        NSYSRESET = 1'b1;
	#(SYSCLK_PERIOD * 10)
		SOFT_D = 1'b0;
		RT_SW = 1'b1;
		SW1 = 1'b1;
		SW2 = 1'b0;
end


//////////////////////////////////////////////////////////////////////
// Clock Driver
//////////////////////////////////////////////////////////////////////
always @(SYSCLK)
    #(SYSCLK_PERIOD / 2.0) SYSCLK <= !SYSCLK;


//////////////////////////////////////////////////////////////////////
// Instantiate Unit Under Test:  syn_md_combine
//////////////////////////////////////////////////////////////////////
syn_md_combine syn_md_combine_0 (
    // Inputs
    .soft_d(SOFT_D),
    .rt_sw(RT_SW),
    .sw1(SW1),
    .sw2(SW2),

    // Outputs
    .syn_md_temp( outp )

    // Inouts

);

endmodule

