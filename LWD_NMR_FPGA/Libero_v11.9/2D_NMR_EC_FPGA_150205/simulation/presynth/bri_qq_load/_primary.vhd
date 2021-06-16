library verilog;
use verilog.vl_types.all;
entity bri_qq_load is
    port(
        clk_sys         : in     vl_logic;
        pluse_load      : in     vl_logic;
        bri_para        : in     vl_logic_vector(7 downto 0);
        qq_para         : in     vl_logic_vector(15 downto 0);
        half_para       : out    vl_logic_vector(7 downto 0);
        qq_para1        : out    vl_logic_vector(3 downto 0);
        qq_para2        : out    vl_logic_vector(5 downto 0);
        qq_para3        : out    vl_logic_vector(5 downto 0)
    );
end bri_qq_load;
