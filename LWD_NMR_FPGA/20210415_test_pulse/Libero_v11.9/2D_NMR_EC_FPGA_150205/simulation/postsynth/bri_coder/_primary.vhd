library verilog;
use verilog.vl_types.all;
entity bri_coder is
    port(
        half_para       : in     vl_logic_vector(7 downto 0);
        i_0             : out    vl_logic_vector(3 downto 1);
        i_1             : out    vl_logic_vector(0 downto 0);
        count_0         : in     vl_logic_vector(4 downto 0);
        count           : in     vl_logic_vector(7 downto 5);
        net_51          : in     vl_logic;
        bri_dump_sw_0_phase_ctr: in     vl_logic;
        bri_dump_sw_0_reset_out: in     vl_logic;
        clk_4f_en       : in     vl_logic;
        pulse_start_c   : in     vl_logic;
        bri_dump_sw_0_reset_out_0: in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        bri_coder_0_half: out    vl_logic;
        PLUSE_0_bri_cycle: out    vl_logic
    );
end bri_coder;
