//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Wed May 14 08:39:02 2014
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
// Instantiate Unit Under Test:  Signal_Noise_Acq
//////////////////////////////////////////////////////////////////////
Signal_Noise_Acq Signal_Noise_Acq_0 (
    // Inputs
    .clk_sys(SYSCLK),
    .clk_dds(SYSCLK),
    .n_s_ctrl({1{1'b0}}),
    .n_reset(NSYSRESET),
    .noise_load({1{1'b0}}),
    .RAM_RDaddr_rst(NSYSRESET),
    .RAM_RD_EN({1{1'b0}}),
    .RAM_WT_EN({1{1'b0}}),
    .XRD({1{1'b0}}),
    .signal_load({1{1'b0}}),
    .s_reset(NSYSRESET),
    .s_acq_en({1{1'b0}}),
    .adcdata({12{1'b0}}),
    .n_acqnum({12{1'b0}}),
    .n_divnum({10{1'b0}}),
    .s_periodnum({4{1'b0}}),
    .stripnum({12{1'b0}}),
    .acqnum({16{1'b0}}),
    .s_addchoice({5{1'b0}}),

    // Outputs
    .acq_clk( ),
    .dataout( )

    // Inouts

);

endmodule

