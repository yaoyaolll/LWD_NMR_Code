library verilog;
use verilog.vl_types.all;
entity dds_change is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic_vector(1 downto 0);
        dds_rst         : out    vl_logic;
        ddsrstin1       : in     vl_logic;
        ddsrstin2       : in     vl_logic;
        ddsrstin3       : in     vl_logic;
        dds_conf        : out    vl_logic;
        dds_confin1     : in     vl_logic;
        dds_confin2     : in     vl_logic;
        dds_confin3     : in     vl_logic
    );
end dds_change;
