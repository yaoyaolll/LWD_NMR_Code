library verilog;
use verilog.vl_types.all;
entity add_reg is
    port(
        clk             : in     vl_logic;
        addin           : in     vl_logic_vector(11 downto 0);
        addresult       : out    vl_logic_vector(19 downto 0);
        rst_n           : in     vl_logic
    );
end add_reg;
