library verilog;
use verilog.vl_types.all;
entity necount_cmp_1 is
    port(
        NE_NUM          : in     vl_logic_vector(11 downto 0);
        necount         : in     vl_logic_vector(11 downto 0);
        necount_LE_NE_1 : out    vl_logic
    );
end necount_cmp_1;
