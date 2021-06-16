library verilog;
use verilog.vl_types.all;
entity qq_timer is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        statestart      : in     vl_logic;
        stateover       : in     vl_logic;
        count           : out    vl_logic_vector(4 downto 0)
    );
end qq_timer;
