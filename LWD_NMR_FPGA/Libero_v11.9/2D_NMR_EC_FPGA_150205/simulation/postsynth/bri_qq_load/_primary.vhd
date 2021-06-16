library verilog;
use verilog.vl_types.all;
entity bri_qq_load is
    port(
        halfdata        : in     vl_logic_vector(7 downto 0);
        half_para       : out    vl_logic_vector(7 downto 0);
        qq_para1        : out    vl_logic_vector(3 downto 0);
        qq_para2        : out    vl_logic_vector(5 downto 0);
        bri_datain      : in     vl_logic_vector(15 downto 0);
        qq_para3        : out    vl_logic_vector(5 downto 0);
        top_code_0_bridge_load_0: in     vl_logic;
        top_code_0_bridge_load: in     vl_logic;
        GLA             : in     vl_logic
    );
end bri_qq_load;
