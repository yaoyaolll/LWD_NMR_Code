//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Sun Dec 12 22:10:38 2010
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
// Instantiate Unit Under Test:  noiseacq
//////////////////////////////////////////////////////////////////////
noiseacq noiseacq_0 (
    // Inputs
    .n_en({1{1'b0}}),
    .n_rdclk(SYSCLK),
    .n_rd_en({1{1'b0}}),
    .n_reset(NSYSRESET),
    .n_load({1{1'b0}}),
    .clk_sys(SYSCLK),
    .n_rd_rst(NSYSRESET),
    .n_adcdata({12{1'b0}}),
    .n_divnum({10{1'b0}}),
    .n_acqnum({12{1'b0}}),

    // Outputs
    .n_acqclk( ),
    .n_dataout( )

    // Inouts

);

endmodule

