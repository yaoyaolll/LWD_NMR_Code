library verilog;
use verilog.vl_types.all;
entity cal_load is
    port(
        clk_sys         : in     vl_logic;
        cal_load        : in     vl_logic;
        cal_para        : in     vl_logic_vector(5 downto 0);
        cal_para_out    : out    vl_logic_vector(5 downto 0)
    );
end cal_load;
