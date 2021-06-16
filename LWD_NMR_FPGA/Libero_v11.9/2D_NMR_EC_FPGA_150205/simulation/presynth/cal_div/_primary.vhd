library verilog;
use verilog.vl_types.all;
entity cal_div is
    port(
        clk_dds         : in     vl_logic;
        rst_n           : in     vl_logic;
        cal_start       : in     vl_logic;
        cal_para        : in     vl_logic_vector(5 downto 0);
        cal             : out    vl_logic
    );
end cal_div;
