///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: div_fre.v
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

module div_fre( clk_in, clk_5k );
input clk_in;
output clk_5k;

reg clk_5k;
reg [31:0] count;

always @(posedge clk_in)
begin
	if (count >= 500)
	begin
		clk_5k <= ~clk_5k;
		count <= 1;
	end
	else
	begin
		count <= count + 1;
	end
end

//<statements>

endmodule

