library verilog;
use verilog.vl_types.all;
entity necount_inc is
    port(
        DataA           : in     vl_logic_vector(11 downto 0);
        Sum             : out    vl_logic_vector(11 downto 0)
    );
end necount_inc;
