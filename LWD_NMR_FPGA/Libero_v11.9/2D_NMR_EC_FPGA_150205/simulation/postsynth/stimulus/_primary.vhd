library verilog;
use verilog.vl_types.all;
entity stimulus is
    port(
        rst_n           : out    vl_logic;
        clk_sys         : out    vl_logic;
        xrd             : out    vl_logic;
        n_rdclk         : in     vl_logic
    );
end stimulus;
