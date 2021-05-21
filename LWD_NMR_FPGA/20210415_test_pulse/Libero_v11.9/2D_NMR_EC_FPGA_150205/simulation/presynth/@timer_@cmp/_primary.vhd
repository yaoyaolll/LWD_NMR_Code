library verilog;
use verilog.vl_types.all;
entity Timer_Cmp is
    port(
        DataA           : in     vl_logic_vector(21 downto 0);
        DataB           : in     vl_logic_vector(21 downto 0);
        AGB             : out    vl_logic
    );
end Timer_Cmp;
