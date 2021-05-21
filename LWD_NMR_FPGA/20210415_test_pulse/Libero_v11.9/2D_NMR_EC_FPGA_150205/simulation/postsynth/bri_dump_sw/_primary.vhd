library verilog;
use verilog.vl_types.all;
entity bri_dump_sw is
    port(
        bri_dump_sw_0_dump_start: out    vl_logic;
        bri_dump_sw_0_dumpoff_ctr: out    vl_logic;
        bri_dump_sw_0_off_test: out    vl_logic;
        bri_dump_sw_0_phase_ctr: out    vl_logic;
        pulse_start_c   : out    vl_logic;
        bri_dump_sw_0_reset_out: out    vl_logic;
        bri_dump_sw_0_tetw_pluse: out    vl_logic;
        net_45          : in     vl_logic;
        top_code_0_pluse_rst: in     vl_logic;
        scalestate_0_tetw_pluse: in     vl_logic;
        scalestate_0_pluse_start: in     vl_logic;
        scalestate_0_pn_out: in     vl_logic;
        top_code_0_pn_change: in     vl_logic;
        scalestate_0_off_test: in     vl_logic;
        plusestate_0_off_test: in     vl_logic;
        scalestate_0_dumpoff_ctr: in     vl_logic;
        plusestate_0_tetw_pluse: in     vl_logic;
        top_code_0_pluse_scale: in     vl_logic;
        scalestate_0_dump_start: in     vl_logic;
        plusestate_0_soft_d: in     vl_logic;
        net_27          : in     vl_logic;
        GLA             : in     vl_logic;
        bri_dump_sw_0_reset_out_0: out    vl_logic
    );
end bri_dump_sw;
