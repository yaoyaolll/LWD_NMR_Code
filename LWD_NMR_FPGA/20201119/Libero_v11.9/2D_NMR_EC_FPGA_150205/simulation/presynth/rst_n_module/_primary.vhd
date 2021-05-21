library verilog;
use verilog.vl_types.all;
entity rst_n_module is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        rst_nr2         : out    vl_logic
    );
end rst_n_module;
