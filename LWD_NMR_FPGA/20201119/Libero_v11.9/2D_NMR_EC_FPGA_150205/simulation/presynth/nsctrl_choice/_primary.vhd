library verilog;
use verilog.vl_types.all;
entity nsctrl_choice is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic;
        soft_d_s        : in     vl_logic;
        rt_sw_s         : in     vl_logic;
        sw_acq1_s       : in     vl_logic;
        sw_acq2_s       : in     vl_logic;
        inter_s         : in     vl_logic;
        dumpon_ctr_s    : in     vl_logic;
        dumpoff_ctr_s   : in     vl_logic;
        dumponoff_rst_s : in     vl_logic;
        soft_d_n        : in     vl_logic;
        rt_sw_n         : in     vl_logic;
        sw_acq1_n       : in     vl_logic;
        sw_acq2_n       : in     vl_logic;
        inter_n         : in     vl_logic;
        dumpon_ctr_n    : in     vl_logic;
        dumpoff_ctr_n   : in     vl_logic;
        dumponoff_rst_n : in     vl_logic;
        soft_d          : out    vl_logic;
        rt_sw           : out    vl_logic;
        sw_acq1         : out    vl_logic;
        sw_acq2         : out    vl_logic;
        intertodsp      : out    vl_logic;
        dumpon_ctr      : out    vl_logic;
        dumpoff_ctr     : out    vl_logic;
        dumponoff_rst   : out    vl_logic
    );
end nsctrl_choice;
