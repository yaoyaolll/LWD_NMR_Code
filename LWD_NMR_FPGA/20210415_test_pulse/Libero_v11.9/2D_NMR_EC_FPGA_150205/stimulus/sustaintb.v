// sustaintb.v
// dump_sustain_timer_tb.v
`timescale 1ns/1ns
module testbench;

reg clk_sys;
reg rst_n;
reg state_start;
reg [3:0]dump_sustain_data;
reg clk_10k;

initial
    begin
        rst_n = 1'b0;
        state_start = 1'b0;
        dump_sustain_data = 4'd0;
        clk_sys = 1'b0;
        clk_10k = 1'b0;
    end

initial
    begin
        #500000 rst_n = 1'b1;
                state_start = 1'b1;
                dump_sustain_data = 4'd6;
        #5000000
            state_start = 1'b0;
    end

always 
    #50000 clk_10k <= !clk_10k;
always 
    #5     clk_sys <= !clk_sys;


dump_sustain_timer dump_sustain_timer_0
(
.clk_sys(clk_sys),
.rst_n(rst_n),
.state_start(state_start),
.dump_sustain_data(dump_sustain_data),
.clk_10k(clk_10k),
.start(start)
);

endmodule