library verilog;
use verilog.vl_types.all;
entity dds_coder is
    port(
        i_2             : out    vl_logic_vector(3 downto 1);
        count_2         : in     vl_logic_vector(4 downto 0);
        count_0         : in     vl_logic_vector(7 downto 5);
        i_RNIV2B7       : out    vl_logic_vector(0 downto 0);
        GLA             : in     vl_logic;
        dds_change_0_dds_conf: in     vl_logic;
        dds_change_0_dds_rst: in     vl_logic
    );
end dds_coder;
