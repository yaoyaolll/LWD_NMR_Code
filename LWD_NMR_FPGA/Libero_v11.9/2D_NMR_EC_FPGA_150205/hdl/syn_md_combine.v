///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: syn_md_combine.v
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

module syn_md_combine( soft_d, rt_sw, sw1, sw2, syn_md_temp );
input soft_d;
input rt_sw;
input sw1;
input sw2;
output syn_md_temp;

assign syn_md_temp = (~soft_d) & (rt_sw) & (sw1) & (~sw2);

//<statements>

endmodule

