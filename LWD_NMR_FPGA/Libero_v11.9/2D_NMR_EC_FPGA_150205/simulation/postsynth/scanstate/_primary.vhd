library verilog;
use verilog.vl_types.all;
entity scanstate is
    port(
        timecount_1_0   : out    vl_logic_vector(15 downto 0);
        scandata        : in     vl_logic_vector(15 downto 0);
        GLA             : in     vl_logic;
        top_code_0_scanchoice: in     vl_logic;
        top_code_0_scanload: in     vl_logic;
        scanstate_0_calctrl: out    vl_logic;
        scanstate_0_soft_d: out    vl_logic;
        scanstate_0_dds_conf: out    vl_logic;
        net_33          : in     vl_logic;
        scanstate_0_state_over_n: out    vl_logic;
        scanstate_0_s_acq: out    vl_logic;
        scanstate_0_dumpoff_ctr: out    vl_logic;
        scanstate_0_rt_sw: out    vl_logic;
        scanstate_0_sw_acq2: out    vl_logic;
        net_33_0        : in     vl_logic;
        timer_top_0_clk_en_scan: in     vl_logic
    );
end scanstate;
