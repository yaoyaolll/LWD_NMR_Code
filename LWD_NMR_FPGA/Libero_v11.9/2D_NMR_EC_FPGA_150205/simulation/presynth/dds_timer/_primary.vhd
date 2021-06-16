library verilog;
use verilog.vl_types.all;
entity dds_timer is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        state_over      : in     vl_logic;
        count           : out    vl_logic_vector(7 downto 0)
    );
end dds_timer;
