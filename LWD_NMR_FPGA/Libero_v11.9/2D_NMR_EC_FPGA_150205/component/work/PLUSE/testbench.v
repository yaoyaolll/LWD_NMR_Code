//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Sat Jan 31 22:13:54 2015
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
// Instantiate Unit Under Test:  PLUSE
//////////////////////////////////////////////////////////////////////
PLUSE PLUSE_0 (
    // Inputs
    .state_start({1{1'b0}}),
    .rst_n(NSYSRESET),
    .phase({1{1'b0}}),
    .quar_delay({1{1'b0}}),
    .clk_sys(SYSCLK),
    .pluse_load({1{1'b0}}),
    .clk_dds(SYSCLK),
    .clk_4f_en(SYSCLK),
    .qq_para({16{1'b0}}),
    .bri_para({8{1'b0}}),
    .turn_delay({1{1'b0}}),

    // Outputs
    .bri_cycle( ),
    .Q1Q8( ),
    .Q3Q6( ),
    .Q4Q5( ),
    .Q2Q7( ),
    .down( ),
    .up( )

    // Inouts

);

endmodule

