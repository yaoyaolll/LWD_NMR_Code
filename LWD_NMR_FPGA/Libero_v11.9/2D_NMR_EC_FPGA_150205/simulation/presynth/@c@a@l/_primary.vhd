library verilog;
use verilog.vl_types.all;
entity CAL is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        cal_start       : in     vl_logic;
        clk_dds         : in     vl_logic;
        cal             : out    vl_logic;
        cal_load        : in     vl_logic;
        cal_para        : in     vl_logic_vector(5 downto 0)
    );
end CAL;
