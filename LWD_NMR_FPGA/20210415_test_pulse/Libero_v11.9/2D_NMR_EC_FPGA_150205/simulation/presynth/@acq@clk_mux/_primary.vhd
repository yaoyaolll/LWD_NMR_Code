library verilog;
use verilog.vl_types.all;
entity AcqClk_mux is
    port(
        Data0_port      : in     vl_logic;
        Data1_port      : in     vl_logic;
        Sel0            : in     vl_logic;
        Result          : out    vl_logic
    );
end AcqClk_mux;
