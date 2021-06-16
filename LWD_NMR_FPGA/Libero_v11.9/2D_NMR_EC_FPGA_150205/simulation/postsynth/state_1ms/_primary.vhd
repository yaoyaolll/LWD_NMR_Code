library verilog;
use verilog.vl_types.all;
entity state_1ms is
    port(
        state_1ms_data  : in     vl_logic_vector(15 downto 0);
        timecount_0     : out    vl_logic_vector(19 downto 0);
        state_1ms_lc    : in     vl_logic_vector(3 downto 0);
        GLA             : in     vl_logic;
        state_1ms_0_reset_out: out    vl_logic;
        top_code_0_state_1ms_rst_n: in     vl_logic;
        top_code_0_state_1ms_load: in     vl_logic;
        state_1ms_0_bri_cycle: out    vl_logic;
        state_1ms_0_pluse_start: out    vl_logic;
        state_1ms_0_rt_sw: out    vl_logic;
        state_1ms_0_soft_dump: out    vl_logic;
        state_1ms_0_dump_start: out    vl_logic;
        top_code_0_state_1ms_rst_n_0: in     vl_logic;
        timer_top_0_clk_en_st1ms: in     vl_logic
    );
end state_1ms;
