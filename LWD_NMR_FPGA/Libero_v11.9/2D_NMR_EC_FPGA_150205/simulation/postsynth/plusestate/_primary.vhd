library verilog;
use verilog.vl_types.all;
entity plusestate is
    port(
        timecount_1_1   : out    vl_logic_vector(15 downto 0);
        plusedata       : in     vl_logic_vector(15 downto 0);
        GLA             : in     vl_logic;
        plusestate_0_off_test: out    vl_logic;
        plusestate_0_sw_acq1: out    vl_logic;
        plusestate_0_pluse_acq: out    vl_logic;
        plusestate_0_dds_config: out    vl_logic;
        plusestate_0_state_over_n: out    vl_logic;
        top_code_0_pluse_rst: in     vl_logic;
        top_code_0_pluse_lc: in     vl_logic;
        top_code_0_pluseload: in     vl_logic;
        plusestate_0_tetw_pluse: out    vl_logic;
        timer_top_0_clk_en_pluse: in     vl_logic;
        plusestate_0_soft_d: out    vl_logic;
        top_code_0_pluse_rst_0: in     vl_logic
    );
end plusestate;
