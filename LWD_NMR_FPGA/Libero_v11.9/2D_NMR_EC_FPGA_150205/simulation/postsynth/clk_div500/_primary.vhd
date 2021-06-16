library verilog;
use verilog.vl_types.all;
entity clk_div500 is
    port(
        GLA             : in     vl_logic;
        pllclk_0_GLB    : in     vl_logic;
        net_27          : in     vl_logic;
        clk_5K          : out    vl_logic
    );
end clk_div500;
