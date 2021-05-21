library verilog;
use verilog.vl_types.all;
entity pd_pluse_inc is
    port(
        DataA           : in     vl_logic_vector(15 downto 0);
        Sum             : out    vl_logic_vector(15 downto 0);
        Cout            : out    vl_logic
    );
end pd_pluse_inc;
