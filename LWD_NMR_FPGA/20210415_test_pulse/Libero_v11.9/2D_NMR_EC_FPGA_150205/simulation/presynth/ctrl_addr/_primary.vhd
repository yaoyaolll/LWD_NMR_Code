library verilog;
use verilog.vl_types.all;
entity ctrl_addr is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        clk             : in     vl_logic;
        addrout         : out    vl_logic_vector(3 downto 0);
        datain          : in     vl_logic_vector(3 downto 0);
        load            : in     vl_logic
    );
end ctrl_addr;
