//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Tue May 18 11:09:26 2021
// Version: v11.9 SP6 11.9.6.7
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// syn_md_module
module syn_md_module(
    // Inputs
    clkin,
    rst_n,
    rt_sw,
    soft_d,
    sw1,
    sw2,
    // Outputs
    syn_md_out,
    syn_md_tmp
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  clkin;
input  rst_n;
input  rt_sw;
input  soft_d;
input  sw1;
input  sw2;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output syn_md_out;
output syn_md_tmp;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   clkin;
wire   rst_n;
wire   rt_sw;
wire   soft_d;
wire   sw1;
wire   sw2;
wire   syn_md_edge_detect_0_syn_md_out_en;
wire   syn_md_out_net_0;
wire   syn_md_tmp_net_0;
wire   syn_md_out_net_1;
wire   syn_md_tmp_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign syn_md_out_net_1 = syn_md_out_net_0;
assign syn_md_out       = syn_md_out_net_1;
assign syn_md_tmp_net_1 = syn_md_tmp_net_0;
assign syn_md_tmp       = syn_md_tmp_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------syn_md
syn_md syn_md_0(
        // Inputs
        .clkin         ( clkin ),
        .syn_md_out_en ( syn_md_edge_detect_0_syn_md_out_en ),
        .rst_n         ( rst_n ),
        // Outputs
        .syn_md_out    ( syn_md_out_net_0 ) 
        );

//--------syn_md_combine
syn_md_combine syn_md_combine_0(
        // Inputs
        .soft_d      ( soft_d ),
        .rt_sw       ( rt_sw ),
        .sw1         ( sw1 ),
        .sw2         ( sw2 ),
        // Outputs
        .syn_md_temp ( syn_md_tmp_net_0 ) 
        );

//--------syn_md_edge_detect
syn_md_edge_detect syn_md_edge_detect_0(
        // Inputs
        .syn_md_temp   ( syn_md_tmp_net_0 ),
        .rst_n         ( rst_n ),
        .clkin         ( clkin ),
        // Outputs
        .syn_md_out_en ( syn_md_edge_detect_0_syn_md_out_en ) 
        );


endmodule
