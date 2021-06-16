library verilog;
use verilog.vl_types.all;
entity necount_cmp is
    port(
        DataA           : in     vl_logic_vector(10 downto 0);
        DataB           : in     vl_logic_vector(10 downto 0);
        ALEB            : out    vl_logic
    );
end necount_cmp;
