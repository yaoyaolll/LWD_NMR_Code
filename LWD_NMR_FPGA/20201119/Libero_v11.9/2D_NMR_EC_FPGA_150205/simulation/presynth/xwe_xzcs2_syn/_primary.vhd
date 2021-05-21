library verilog;
use verilog.vl_types.all;
entity xwe_xzcs2_syn is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        xwe             : in     vl_logic;
        xzcs2           : in     vl_logic;
        code_en         : out    vl_logic
    );
end xwe_xzcs2_syn;
