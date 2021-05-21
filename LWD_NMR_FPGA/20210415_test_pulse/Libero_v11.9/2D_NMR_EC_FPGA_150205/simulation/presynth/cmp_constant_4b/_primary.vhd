library verilog;
use verilog.vl_types.all;
entity cmp_constant_4b is
    port(
        DataA           : in     vl_logic_vector(3 downto 0);
        AEB             : out    vl_logic
    );
end cmp_constant_4b;
