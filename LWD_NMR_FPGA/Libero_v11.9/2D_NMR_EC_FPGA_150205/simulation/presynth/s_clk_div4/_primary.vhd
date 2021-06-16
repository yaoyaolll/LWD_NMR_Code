library verilog;
use verilog.vl_types.all;
entity s_clk_div4 is
    port(
        rst_n           : in     vl_logic;
        entop           : in     vl_logic;
        s_acq_en        : in     vl_logic;
        clk_dds         : in     vl_logic;
        clkout          : out    vl_logic
    );
end s_clk_div4;
