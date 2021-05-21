library verilog;
use verilog.vl_types.all;
entity stimulus is
    port(
        state_1ms_rst_n : out    vl_logic;
        clk_sys         : out    vl_logic;
        state_1ms_start : out    vl_logic;
        reset_out       : in     vl_logic;
        dump_start      : in     vl_logic;
        pluse_start     : in     vl_logic;
        bri_cycle       : in     vl_logic;
        rt_sw           : in     vl_logic;
        soft_dump       : in     vl_logic;
        timeup_n        : in     vl_logic;
        timecount       : in     vl_logic_vector(19 downto 0)
    );
end stimulus;
