library verilog;
use verilog.vl_types.all;
entity necount_equal is
    port(
        DataA           : in     vl_logic_vector(11 downto 0);
        DataB           : in     vl_logic_vector(11 downto 0);
        AEB             : out    vl_logic
    );
end necount_equal;
