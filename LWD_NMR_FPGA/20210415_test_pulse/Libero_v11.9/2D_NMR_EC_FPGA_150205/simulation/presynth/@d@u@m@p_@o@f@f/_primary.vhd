library verilog;
use verilog.vl_types.all;
entity DUMP_OFF is
    port(
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        clk_sys         : in     vl_logic;
        dump_off        : out    vl_logic
    );
end DUMP_OFF;
