library verilog;
use verilog.vl_types.all;
entity bri_timer is
    port(
        clk_dds         : in     vl_logic;
        clk_4f_en       : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        timer_stop      : in     vl_logic;
        count           : out    vl_logic_vector(7 downto 0)
    );
end bri_timer;
