///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: syn_md.v
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

module syn_md( clkin, syn_md_out_en, rst_n, syn_md_out );

input clkin;
input syn_md_out_en;
input rst_n;

output reg syn_md_out;

reg [3:0] count;

always @(posedge clkin)
begin
	if (!rst_n)
	begin
		syn_md_out <= 1'b0;
		count <= 1'b0;
	end
	else
		if (syn_md_out_en)
		begin
			count <= 4'b1111;
			syn_md_out <= 1'b1;
		end
		else
			if (count > 4'b0000)
				count <= count - 1'b1;
			else
				syn_md_out <= 1'b0;
end

//<statements>

endmodule

