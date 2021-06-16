library verilog;
use verilog.vl_types.all;
entity pd_pluse_coder is
    port(
        i_0             : out    vl_logic_vector(5 downto 4);
        i_4             : out    vl_logic_vector(3 downto 2);
        i_5             : out    vl_logic_vector(0 downto 0);
        pd_pluse_data   : in     vl_logic_vector(15 downto 0);
        i_0_0_0         : out    vl_logic;
        pd_pluse_choice : in     vl_logic_vector(3 downto 0);
        count_0         : in     vl_logic_vector(15 downto 8);
        count_2         : in     vl_logic_vector(7 downto 5);
        count_5         : in     vl_logic_vector(4 downto 0);
        ddsclkout_c     : in     vl_logic;
        GLA             : in     vl_logic;
        bri_dump_sw_0_tetw_pluse: in     vl_logic;
        net_51          : in     vl_logic;
        pulse_start_c   : in     vl_logic;
        top_code_0_pd_pluse_load: in     vl_logic;
        net_27          : in     vl_logic
    );
end pd_pluse_coder;
