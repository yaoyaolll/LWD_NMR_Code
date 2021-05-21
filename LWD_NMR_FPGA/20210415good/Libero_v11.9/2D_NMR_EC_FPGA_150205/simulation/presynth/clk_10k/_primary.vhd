library verilog;
use verilog.vl_types.all;
entity clk_10k is
    port(
        clk_5M          : in     vl_logic;
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        clock_10khz     : out    vl_logic
    );
end clk_10k;
