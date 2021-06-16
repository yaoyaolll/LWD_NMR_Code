library verilog;
use verilog.vl_types.all;
entity timer is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        datain          : in     vl_logic_vector(21 downto 0);
        work_n          : in     vl_logic;
        state_start     : in     vl_logic;
        state_over_n    : in     vl_logic;
        time_up         : out    vl_logic
    );
end timer;
