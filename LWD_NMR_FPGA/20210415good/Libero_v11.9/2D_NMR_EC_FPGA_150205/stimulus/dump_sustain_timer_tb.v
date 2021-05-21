// dump_sustain_timer_tb.v
`timescale 100us/1us
module dump_sustain_timer_tb;
reg rst_n;
reg state_start;                  
reg clk_5k;
wire start;

initial
    begin
        rst_n = 1'b0;
        state_start = 1'b0;
        clk_5k = 1'b0;
    end

initial
    begin
        #3 
            rst_n = 1'b1;
            state_start = 1'b1;
    end

always 
    #1 clk_5k <= !clk_5k;

dump_sustain_timer dump_sustain_timer_0
(
.rst_n(rst_n),
.state_start(state_start),
.clk_5k(clk_5k),
.start(start)
);

endmodule