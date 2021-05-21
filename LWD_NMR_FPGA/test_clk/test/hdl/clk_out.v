///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: clk_out.v
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

module clk_out( clk_in, clk_out );
input clk_in;
output clk_out;
reg clk_out;
reg [5:0] count;

always @(posedge clk_in)
begin
	if (count >= 9)
		count <= 0;
	else
		count <= count + 1;
end

always @(posedge clk_in)
begin
	if(count >= 9)
		clk_out = ~clk_out;
end
//<statements>

endmodule

