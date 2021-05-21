library verilog;
use verilog.vl_types.all;
entity cal_load is
    port(
        cal_data        : in     vl_logic_vector(5 downto 0);
        cal_para_out    : out    vl_logic_vector(5 downto 0);
        top_code_0_cal_load: in     vl_logic;
        GLA             : in     vl_logic
    );
end cal_load;
