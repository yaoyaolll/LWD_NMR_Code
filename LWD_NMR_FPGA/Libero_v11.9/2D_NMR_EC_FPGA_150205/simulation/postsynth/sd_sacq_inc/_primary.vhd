library verilog;
use verilog.vl_types.all;
entity sd_sacq_inc is
    port(
        count_1         : in     vl_logic_vector(7 downto 5);
        count           : in     vl_logic_vector(21 downto 8);
        count_4         : in     vl_logic_vector(4 downto 0);
        count1          : out    vl_logic_vector(21 downto 1)
    );
end sd_sacq_inc;
