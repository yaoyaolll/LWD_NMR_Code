//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Dec 16 11:20:55 2021
// Version: v11.9 SP6 11.9.6.7
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// ClockManagement
module ClockManagement(
    // Inputs
    OCX40MHz,
    rst_n,
    start,
    timer_para,
    // Outputs
    GLA,
    clock_10khz,
    timeup
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input         OCX40MHz;
input         rst_n;
input         start;
input  [15:0] timer_para;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output        GLA;
output        clock_10khz;
output        timeup;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire          clk_div500_0_clk_5K;
wire          OCX40MHz;
wire          clock_10khz_net_0;
wire          GLA_net_0;
wire          pllclk_0_GLB;
wire          rst_n;
wire          start;
wire   [15:0] timer_para;
wire          timeup_net_0;
wire          GLA_net_1;
wire          timeup_net_1;
wire          clock_10khz_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          VCC_net;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net = 1'b1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign GLA_net_1         = GLA_net_0;
assign GLA               = GLA_net_1;
assign timeup_net_1      = timeup_net_0;
assign timeup            = timeup_net_1;
assign clock_10khz_net_1 = clock_10khz_net_0;
assign clock_10khz       = clock_10khz_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------clk_10k
clk_10k clk_10k_0(
        // Inputs
        .clk_5M      ( pllclk_0_GLB ),
        .clk_sys     ( GLA_net_0 ),
        .rst_n       ( rst_n ),
        // Outputs
        .clock_10khz ( clock_10khz_net_0 ) 
        );

//--------clk_div500
clk_div500 clk_div500_0(
        // Inputs
        .clk_5M  ( pllclk_0_GLB ),
        .clk_sys ( GLA_net_0 ),
        .rst_n   ( rst_n ),
        // Outputs
        .clk_5K  ( clk_div500_0_clk_5K ) 
        );

//--------long_timer
long_timer long_timer_0(
        // Inputs
        .clk_5K     ( clk_div500_0_clk_5K ),
        .clk_sys    ( GLA_net_0 ),
        .rst_n      ( rst_n ),
        .start      ( start ),
        .work       ( timeup_net_0 ),
        .timer_para ( timer_para ),
        // Outputs
        .timeup     ( timeup_net_0 ) 
        );

//--------pllclk
pllclk pllclk_0(
        // Inputs
        .POWERDOWN ( VCC_net ),
        .CLKA      ( OCX40MHz ),
        // Outputs
        .LOCK      (  ),
        .GLA       ( GLA_net_0 ),
        .GLB       ( pllclk_0_GLB ) 
        );


endmodule
