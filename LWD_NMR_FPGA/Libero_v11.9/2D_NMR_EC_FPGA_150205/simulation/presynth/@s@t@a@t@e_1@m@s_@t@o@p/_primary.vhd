library verilog;
use verilog.vl_types.all;
entity STATE_1MS_TOP is
    port(
        state_1ms_rst_n : in     vl_logic;
        clk_sys         : in     vl_logic;
        state_1ms_start : in     vl_logic;
        reset_out       : out    vl_logic;
        dump_start      : out    vl_logic;
        pluse_start     : out    vl_logic;
        bri_cycle       : out    vl_logic;
        rt_sw           : out    vl_logic;
        soft_dump       : out    vl_logic;
        timeup_n        : out    vl_logic;
        timecount       : out    vl_logic_vector(19 downto 0)
    );
end STATE_1MS_TOP;
