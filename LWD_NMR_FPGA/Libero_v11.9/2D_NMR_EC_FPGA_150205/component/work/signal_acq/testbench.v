//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Wed May 14 08:38:51 2014
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
// Instantiate Unit Under Test:  signal_acq
//////////////////////////////////////////////////////////////////////
signal_acq signal_acq_0 (
    // Inputs
    .s_reset(NSYSRESET),
    .signal_load({1{1'b0}}),
    .clk_sys(SYSCLK),
    .clk_dds(SYSCLK),
    .s_acq_en({1{1'b0}}),
    .acqnum({16{1'b0}}),
    .stripnum({12{1'b0}}),
    .s_periodnum({4{1'b0}}),
    .s_addchoice({5{1'b0}}),
    .s_ADC({12{1'b0}}),

    // Outputs
    .Signal_acq_clk( ),
    .signal_data( )

    // Inouts

);

endmodule

