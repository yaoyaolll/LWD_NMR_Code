library verilog;
use verilog.vl_types.all;
entity state1ms_choice is
    port(
        state1ms_choice_0_bri_cycle: out    vl_logic;
        state1ms_choice_0_dump_start: out    vl_logic;
        bri_div_start_0 : out    vl_logic;
        state1ms_choice_0_reset_out: out    vl_logic;
        rt_sw_c         : out    vl_logic;
        GLA             : in     vl_logic;
        soft_dump_c     : out    vl_logic;
        state_1ms_0_soft_dump: in     vl_logic;
        soft_dump_net_1 : in     vl_logic;
        state_1ms_0_rt_sw: in     vl_logic;
        rt_sw_net_1     : in     vl_logic;
        state_1ms_0_reset_out: in     vl_logic;
        bri_dump_sw_0_reset_out_0: in     vl_logic;
        state_1ms_0_pluse_start: in     vl_logic;
        bri_dump_sw_0_off_test: in     vl_logic;
        state_1ms_0_dump_start: in     vl_logic;
        bri_dump_sw_0_dump_start: in     vl_logic;
        top_code_0_state_1ms_start: in     vl_logic;
        state_1ms_0_bri_cycle: in     vl_logic;
        PLUSE_0_bri_cycle: in     vl_logic;
        net_27          : in     vl_logic
    );
end state1ms_choice;
