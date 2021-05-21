library verilog;
use verilog.vl_types.all;
entity state1ms_choice is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic;
        pluse_start     : out    vl_logic;
        pluse_start1    : in     vl_logic;
        pluse_start2    : in     vl_logic;
        dump_start      : out    vl_logic;
        dump_start1     : in     vl_logic;
        dump_start2     : in     vl_logic;
        reset_out       : out    vl_logic;
        reset_out1      : in     vl_logic;
        reset_out2      : in     vl_logic;
        bri_cycle       : out    vl_logic;
        bri_cycle1      : in     vl_logic;
        bri_cycle2      : in     vl_logic;
        rt_sw           : out    vl_logic;
        rt_sw1          : in     vl_logic;
        rt_sw2          : in     vl_logic;
        soft_dump       : out    vl_logic;
        soft_dump1      : in     vl_logic;
        soft_dump2      : in     vl_logic
    );
end state1ms_choice;
