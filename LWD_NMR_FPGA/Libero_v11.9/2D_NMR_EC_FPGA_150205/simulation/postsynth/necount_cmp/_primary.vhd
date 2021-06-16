library verilog;
use verilog.vl_types.all;
entity necount_cmp is
    port(
        M_NUM           : in     vl_logic_vector(11 downto 0);
        necount         : in     vl_logic_vector(11 downto 0);
        necount_LE_M_1  : out    vl_logic
    );
end necount_cmp;
