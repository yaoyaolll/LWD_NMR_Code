library verilog;
use verilog.vl_types.all;
entity timer_top is
    port(
        timecount_1_0   : in     vl_logic_vector(15 downto 0);
        timecount_1_1   : in     vl_logic_vector(15 downto 0);
        timecount       : in     vl_logic_vector(21 downto 0);
        timecount_0     : in     vl_logic_vector(19 downto 0);
        timecount_1     : in     vl_logic_vector(15 downto 0);
        timer_top_0_clk_en_scale_0: out    vl_logic;
        plusestate_0_state_over_n: in     vl_logic;
        top_code_0_scan_start: in     vl_logic;
        top_code_0_noise_start: in     vl_logic;
        top_code_0_scale_start: in     vl_logic;
        top_code_0_state_1ms_start: in     vl_logic;
        scanstate_0_state_over_n: in     vl_logic;
        noisestate_0_state_over_n: in     vl_logic;
        scalestate_0_tetw_pluse: in     vl_logic;
        top_code_0_pluse_str: in     vl_logic;
        timer_top_0_clk_en_st1ms: out    vl_logic;
        timer_top_0_clk_en_scan: out    vl_logic;
        timer_top_0_clk_en_scale: out    vl_logic;
        timer_top_0_clk_en_pluse: out    vl_logic;
        timer_top_0_clk_en_noise: out    vl_logic;
        net_27          : in     vl_logic;
        GLA             : in     vl_logic
    );
end timer_top;
