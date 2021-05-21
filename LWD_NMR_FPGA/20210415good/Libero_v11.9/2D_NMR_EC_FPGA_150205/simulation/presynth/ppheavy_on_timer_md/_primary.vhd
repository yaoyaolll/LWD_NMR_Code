library verilog;
use verilog.vl_types.all;
entity ppheavy_on_timer_md is
    port(
        clk_sys         : in     vl_logic;
        rst_state       : in     vl_logic;
        rst_n           : in     vl_logic;
        clk_10k         : in     vl_logic;
        state_start     : in     vl_logic;
        start           : out    vl_logic
    );
end ppheavy_on_timer_md;
