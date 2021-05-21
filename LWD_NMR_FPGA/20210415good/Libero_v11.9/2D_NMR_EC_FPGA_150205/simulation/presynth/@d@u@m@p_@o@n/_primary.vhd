library verilog;
use verilog.vl_types.all;
entity DUMP_ON is
    port(
        dump_on         : out    vl_logic;
        state_start     : in     vl_logic;
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic
    );
end DUMP_ON;
