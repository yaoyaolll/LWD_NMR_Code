library verilog;
use verilog.vl_types.all;
entity noisestate is
    port(
        timecount_1     : out    vl_logic_vector(15 downto 0);
        noisedata       : in     vl_logic_vector(15 downto 0);
        GLA             : in     vl_logic;
        noisestate_0_soft_d: out    vl_logic;
        noisestate_0_sw_acq2: out    vl_logic;
        noisestate_0_rt_sw: out    vl_logic;
        noisestate_0_n_acq: out    vl_logic;
        top_code_0_nstatechoice: in     vl_logic;
        top_code_0_nstateload: in     vl_logic;
        noisestate_0_dumpoff_ctr: out    vl_logic;
        top_code_0_noise_rst: in     vl_logic;
        noisestate_0_dumpon_ctr: out    vl_logic;
        noisestate_0_state_over_n: out    vl_logic;
        top_code_0_noise_rst_0: in     vl_logic;
        timer_top_0_clk_en_noise: in     vl_logic
    );
end noisestate;
