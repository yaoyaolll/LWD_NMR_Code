library verilog;
use verilog.vl_types.all;
entity pd_pluse_inc is
    port(
        count_2         : in     vl_logic_vector(7 downto 5);
        count_5         : in     vl_logic_vector(4 downto 0);
        count_0         : in     vl_logic_vector(15 downto 8);
        count1          : out    vl_logic_vector(15 downto 1)
    );
end pd_pluse_inc;
