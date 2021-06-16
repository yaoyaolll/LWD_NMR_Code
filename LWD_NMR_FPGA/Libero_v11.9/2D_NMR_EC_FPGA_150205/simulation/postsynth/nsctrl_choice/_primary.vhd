library verilog;
use verilog.vl_types.all;
entity nsctrl_choice is
    port(
        nsctrl_choice_0_dumpoff_ctr: out    vl_logic;
        nsctrl_choice_0_dumpon_ctr: out    vl_logic;
        nsctrl_choice_0_dumponoff_rst: out    vl_logic;
        nsctrl_choice_0_intertodsp: out    vl_logic;
        nsctrl_choice_0_rt_sw: out    vl_logic;
        nsctrl_choice_0_soft_d: out    vl_logic;
        GLA             : in     vl_logic;
        nsctrl_choice_0_sw_acq2: out    vl_logic;
        noisestate_0_sw_acq2: in     vl_logic;
        scanstate_0_sw_acq2: in     vl_logic;
        top_code_0_n_s_ctrl: in     vl_logic;
        noisestate_0_rt_sw: in     vl_logic;
        scanstate_0_rt_sw: in     vl_logic;
        noisestate_0_dumpon_ctr: in     vl_logic;
        scanstate_0_dds_conf: in     vl_logic;
        top_code_0_n_s_ctrl_1: in     vl_logic;
        noisestate_0_soft_d: in     vl_logic;
        scanstate_0_soft_d: in     vl_logic;
        noisestate_0_state_over_n: in     vl_logic;
        scanstate_0_state_over_n: in     vl_logic;
        top_code_0_noise_rst_0: in     vl_logic;
        net_33_0        : in     vl_logic;
        top_code_0_n_s_ctrl_0: in     vl_logic;
        noisestate_0_dumpoff_ctr: in     vl_logic;
        scanstate_0_dumpoff_ctr: in     vl_logic;
        net_27          : in     vl_logic
    );
end nsctrl_choice;
