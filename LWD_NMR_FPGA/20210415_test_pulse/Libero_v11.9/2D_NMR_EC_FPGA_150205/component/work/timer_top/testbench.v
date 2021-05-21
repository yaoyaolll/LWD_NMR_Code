//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Wed Apr 16 15:30:40 2014
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
// Instantiate Unit Under Test:  timer_top
//////////////////////////////////////////////////////////////////////
timer_top timer_top_0 (
    // Inputs
    .clk_sys(SYSCLK),
    .rst_n(NSYSRESET),
    .datain_state_1ms({20{1'b0}}),
    .datain_pluse({20{1'b0}}),
    .datain_scale({22{1'b0}}),
    .datain_scan({20{1'b0}}),
    .datain_noise({20{1'b0}}),
    .start({5{1'b0}}),
    .state_over_in({4{1'b0}}),

    // Outputs
    .clk_en_scan( ),
    .clk_en_st1ms( ),
    .clk_en_pluse( ),
    .clk_en_scale( ),
    .clk_en_noise( )

    // Inouts

);

endmodule

