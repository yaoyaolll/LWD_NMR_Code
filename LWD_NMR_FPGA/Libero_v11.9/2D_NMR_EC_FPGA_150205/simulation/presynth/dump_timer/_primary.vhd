library verilog;
use verilog.vl_types.all;
entity dump_timer is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        timer_start     : in     vl_logic;
        count           : out    vl_logic_vector(11 downto 0)
    );
end dump_timer;
