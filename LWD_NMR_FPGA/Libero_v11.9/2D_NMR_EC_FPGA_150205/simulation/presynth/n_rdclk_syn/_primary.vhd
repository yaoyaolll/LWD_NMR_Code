library verilog;
use verilog.vl_types.all;
entity n_rdclk_syn is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        clken           : in     vl_logic;
        xrd             : in     vl_logic;
        n_rdclk         : out    vl_logic
    );
end n_rdclk_syn;
