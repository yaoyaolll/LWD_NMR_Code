library verilog;
use verilog.vl_types.all;
entity necount_inc is
    port(
        necount         : in     vl_logic_vector(11 downto 0);
        necount1        : out    vl_logic_vector(11 downto 1)
    );
end necount_inc;
