library verilog;
use verilog.vl_types.all;
entity pd_pluse_top is
    port(
        i_4_0           : in     vl_logic;
        pd_pluse_choice : in     vl_logic_vector(3 downto 0);
        i_0_0           : out    vl_logic_vector(1 downto 1);
        pd_pluse_data   : in     vl_logic_vector(15 downto 0);
        pd_pulse_en_c   : out    vl_logic;
        net_27          : in     vl_logic;
        top_code_0_pd_pluse_load: in     vl_logic;
        pulse_start_c   : in     vl_logic;
        net_51          : in     vl_logic;
        bri_dump_sw_0_tetw_pluse: in     vl_logic;
        GLA             : in     vl_logic;
        ddsclkout_c     : in     vl_logic
    );
end pd_pluse_top;
