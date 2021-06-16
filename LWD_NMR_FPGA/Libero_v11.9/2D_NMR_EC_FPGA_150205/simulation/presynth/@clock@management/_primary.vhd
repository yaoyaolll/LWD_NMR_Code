library verilog;
use verilog.vl_types.all;
entity ClockManagement is
    port(
        OCX40MHz        : in     vl_logic;
        GLA             : out    vl_logic;
        rst_n           : in     vl_logic;
        start           : in     vl_logic;
        timeup          : out    vl_logic;
        clock_10khz     : out    vl_logic;
        timer_para      : in     vl_logic_vector(15 downto 0)
    );
end ClockManagement;
