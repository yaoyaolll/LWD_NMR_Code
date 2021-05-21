library verilog;
use verilog.vl_types.all;
entity bri_dump_sw is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic;
        pluse_start     : out    vl_logic;
        pluse_start1    : in     vl_logic;
        pluse_start2    : in     vl_logic;
        off_test        : out    vl_logic;
        off_test1       : in     vl_logic;
        off_test2       : in     vl_logic;
        dump_start      : out    vl_logic;
        dump_start1     : in     vl_logic;
        dump_start2     : in     vl_logic;
        phase_ctr       : out    vl_logic;
        phase_ctr1      : in     vl_logic;
        phase_ctr2      : in     vl_logic;
        reset_out       : out    vl_logic;
        reset_out1      : in     vl_logic;
        reset_out2      : in     vl_logic;
        dumpoff_ctr     : out    vl_logic;
        dumpoff_ctr1    : in     vl_logic;
        dumpoff_ctr2    : in     vl_logic;
        tetw_pluse      : out    vl_logic;
        tetw_pluse1     : in     vl_logic;
        tetw_pluse2     : in     vl_logic;
        turn_delay      : out    vl_logic;
        turn_delay1     : in     vl_logic;
        turn_delay2     : in     vl_logic
    );
end bri_dump_sw;
