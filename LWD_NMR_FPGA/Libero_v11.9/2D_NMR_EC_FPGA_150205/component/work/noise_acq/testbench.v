//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Wed May 14 08:38:57 2014
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
// Instantiate Unit Under Test:  noise_acq
//////////////////////////////////////////////////////////////////////
noise_acq noise_acq_0 (
    // Inputs
    .noise_load({1{1'b0}}),
    .n_reset(NSYSRESET),
    .RAM_RDaddr_rst(NSYSRESET),
    .RAM_WT_EN({1{1'b0}}),
    .RAM_RD_EN({1{1'b0}}),
    .XRD({1{1'b0}}),
    .clk_sys(SYSCLK),
    .n_acqnum({12{1'b0}}),
    .n_ADC({12{1'b0}}),
    .n_divnum({10{1'b0}}),

    // Outputs
    .Noise_acq_clk( ),
    .RAM_data( )

    // Inouts

);

endmodule

