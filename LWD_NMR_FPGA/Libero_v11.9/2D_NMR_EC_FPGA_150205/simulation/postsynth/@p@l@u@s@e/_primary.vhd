library verilog;
use verilog.vl_types.all;
entity PLUSE is
    port(
        bri_datain      : in     vl_logic_vector(15 downto 0);
        halfdata        : in     vl_logic_vector(7 downto 0);
        top_code_0_bridge_load: in     vl_logic;
        top_code_0_bridge_load_0: in     vl_logic;
        Q4Q5_c          : out    vl_logic;
        Q2Q7_c          : out    vl_logic;
        PLUSE_0_bri_cycle: out    vl_logic;
        bri_dump_sw_0_phase_ctr: in     vl_logic;
        net_51          : in     vl_logic;
        clk_4f_en       : in     vl_logic;
        pulse_start_c   : in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        bri_dump_sw_0_reset_out: in     vl_logic;
        bri_dump_sw_0_reset_out_0: in     vl_logic;
        Q3Q6_c          : out    vl_logic;
        Q1Q8_c          : out    vl_logic;
        GLA             : in     vl_logic
    );
end PLUSE;
