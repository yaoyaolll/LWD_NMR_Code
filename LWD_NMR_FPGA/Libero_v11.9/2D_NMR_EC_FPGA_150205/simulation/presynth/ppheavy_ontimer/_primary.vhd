library verilog;
use verilog.vl_types.all;
entity ppheavy_ontimer is
    port(
        clk_10k         : in     vl_logic;
        rst_n           : in     vl_logic;
        rst_state       : in     vl_logic;
        ppheavy_en      : in     vl_logic;
        clk_sys         : in     vl_logic;
        start           : out    vl_logic
    );
end ppheavy_ontimer;
