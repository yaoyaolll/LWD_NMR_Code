library verilog;
use verilog.vl_types.all;
entity pd_pluse_coder is
    port(
        clk_sys         : in     vl_logic;
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        count           : in     vl_logic_vector(15 downto 0);
        pd_pluse_load   : in     vl_logic;
        pd_pluse_choice : in     vl_logic_vector(3 downto 0);
        pd_pluse_data   : in     vl_logic_vector(15 downto 0);
        pluse_start     : in     vl_logic;
        i               : out    vl_logic_vector(5 downto 0);
        bb_ch           : in     vl_logic;
        tetw_pluse      : in     vl_logic
    );
end pd_pluse_coder;
