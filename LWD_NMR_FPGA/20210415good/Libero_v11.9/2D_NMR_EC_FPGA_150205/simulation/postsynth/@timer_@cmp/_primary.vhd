library verilog;
use verilog.vl_types.all;
entity Timer_Cmp is
    port(
        dataout         : in     vl_logic_vector(21 downto 0);
        timedata        : in     vl_logic_vector(21 downto 0);
        cmp_result      : out    vl_logic
    );
end Timer_Cmp;
