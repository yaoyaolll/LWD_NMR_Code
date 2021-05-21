library verilog;
use verilog.vl_types.all;
entity long_timer is
    port(
        clk_5K          : in     vl_logic;
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        start           : in     vl_logic;
        work            : in     vl_logic;
        timer_para      : in     vl_logic_vector(15 downto 0);
        timeup          : out    vl_logic
    );
end long_timer;
