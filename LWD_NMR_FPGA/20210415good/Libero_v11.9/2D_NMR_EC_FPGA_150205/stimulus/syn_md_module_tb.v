///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: syn_md_module_tb.v
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

module syn_md_module_tb;

parameter SYSCLK_PERIOD = 10;// 100MHZ

reg SYSCLK;
reg NSYSRESET;
wire SYN_MD_OUT;

reg SOFT_D;
reg RT_SW;
reg SW1;
reg SW2;

initial
begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b1;
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
        NSYSRESET = 1'b0;
	#(SYSCLK_PERIOD)
		NSYSRESET = 1'b1;	// 产生一个复位信号
	#(25 )
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
// Instantiate Unit Under Test:  syn_md_module
//////////////////////////////////////////////////////////////////////
syn_md_module syn_md_module_0 (
    // Inputs
    .soft_d(SOFT_D),
    .rt_sw(RT_SW),
    .sw1(SW1),
    .sw2(SW2),
    .rst_n(NSYSRESET),
    .clkin(SYSCLK),

    // Outputs
    .syn_md_out( SYN_MD_OUT)

    // Inouts

);

endmodule

