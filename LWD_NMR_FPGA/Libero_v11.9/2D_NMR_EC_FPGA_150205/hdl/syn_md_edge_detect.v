///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: syn_md_edge_detect.v
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

//`timescale <time_units> / <precision>

module syn_md_edge_detect( syn_md_temp, rst_n, clkin, syn_md_out_en );

input clkin;
input syn_md_temp;
input rst_n;
output syn_md_out_en;

reg sig_r0, sig_r1;

always @ (posedge clkin or negedge rst_n)
	if (!rst_n)
	begin
		sig_r0 <= 1'b0;
		sig_r1 <= 1'b0;
	end
	else
	begin
		sig_r0 <= syn_md_temp;
		sig_r1 <= sig_r0;
	end

assign syn_md_out_en = (~sig_r1) & (sig_r0);				// 上升沿检测

//<statements>

endmodule

