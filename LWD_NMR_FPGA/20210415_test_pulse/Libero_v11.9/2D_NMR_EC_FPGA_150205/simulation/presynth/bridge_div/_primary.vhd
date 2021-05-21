library verilog;
use verilog.vl_types.all;
entity bridge_div is
    port(
        bri_div_start   : in     vl_logic;
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        clk_dds         : in     vl_logic;
        load            : in     vl_logic;
        divcount        : in     vl_logic_vector(5 downto 0);
        clk_4f_en       : out    vl_logic
    );
end bridge_div;
