library verilog;
use verilog.vl_types.all;
entity off_on_timer is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        state_over      : in     vl_logic;
        count           : out    vl_logic_vector(4 downto 0)
    );
end off_on_timer;
