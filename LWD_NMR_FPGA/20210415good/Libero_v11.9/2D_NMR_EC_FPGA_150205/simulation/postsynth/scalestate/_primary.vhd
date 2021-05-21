library verilog;
use verilog.vl_types.all;
entity scalestate is
    port(
        timecount       : out    vl_logic_vector(21 downto 0);
        scaledatain     : in     vl_logic_vector(15 downto 0);
        strippluse      : out    vl_logic_vector(11 downto 0);
        s_acqnum_1      : out    vl_logic_vector(11 downto 0);
        scalechoice     : in     vl_logic_vector(4 downto 0);
        net_45          : out    vl_logic;
        timer_top_0_clk_en_scale: in     vl_logic;
        scalestate_0_dump_start: out    vl_logic;
        scalestate_0_soft_d: out    vl_logic;
        scalestate_0_rt_sw: out    vl_logic;
        net_51          : out    vl_logic;
        scalestate_0_long_opentime: out    vl_logic;
        scalestate_0_s_acq: out    vl_logic;
        scalestate_0_pluse_start: out    vl_logic;
        s_acq180_c      : out    vl_logic;
        scalestate_0_tetw_pluse: out    vl_logic;
        scalestate_0_dumpoff_ctr: out    vl_logic;
        top_code_0_pn_change: in     vl_logic;
        scalestate_0_dump_sustain_ctrl: out    vl_logic;
        scalestate_0_dds_conf: out    vl_logic;
        calcuinter_c    : out    vl_logic;
        scalestate_0_off_test: out    vl_logic;
        scalestate_0_load_out: out    vl_logic;
        scalestate_0_pn_out: out    vl_logic;
        scalestate_0_sw_acq1: out    vl_logic;
        scalestate_0_sw_acq2: out    vl_logic;
        top_code_0_scaleload: in     vl_logic;
        timer_top_0_clk_en_scale_0: in     vl_logic;
        top_code_0_scale_rst: in     vl_logic;
        GLA             : in     vl_logic
    );
end scalestate;
