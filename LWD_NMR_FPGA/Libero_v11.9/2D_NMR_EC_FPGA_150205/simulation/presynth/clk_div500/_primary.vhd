library verilog;
use verilog.vl_types.all;
entity clk_div500 is
    port(
        clk_5M          : in     vl_logic;
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        clk_5K          : out    vl_logic
    );
end clk_div500;
