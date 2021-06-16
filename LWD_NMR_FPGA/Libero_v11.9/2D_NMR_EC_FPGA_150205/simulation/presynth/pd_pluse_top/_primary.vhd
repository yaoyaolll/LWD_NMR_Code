library verilog;
use verilog.vl_types.all;
entity pd_pluse_top is
    port(
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        pluse_start     : in     vl_logic;
        clk_sys         : in     vl_logic;
        pd_pluse_load   : in     vl_logic;
        bb_ch           : in     vl_logic;
        tetw_pluse      : in     vl_logic;
        en              : out    vl_logic;
        pd_pluse_choice : in     vl_logic_vector(3 downto 0);
        pd_pluse_data   : in     vl_logic_vector(15 downto 0)
    );
end pd_pluse_top;
