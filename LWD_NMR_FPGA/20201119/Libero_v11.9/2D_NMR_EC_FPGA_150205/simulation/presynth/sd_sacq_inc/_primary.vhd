library verilog;
use verilog.vl_types.all;
entity sd_sacq_inc is
    port(
        DataA           : in     vl_logic_vector(21 downto 0);
        Sum             : out    vl_logic_vector(21 downto 0);
        Cout            : out    vl_logic
    );
end sd_sacq_inc;
