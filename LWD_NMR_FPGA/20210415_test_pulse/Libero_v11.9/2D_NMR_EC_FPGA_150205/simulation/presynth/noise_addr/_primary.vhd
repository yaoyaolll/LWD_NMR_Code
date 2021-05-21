library verilog;
use verilog.vl_types.all;
entity noise_addr is
    port(
        clkin           : in     vl_logic;
        rst_n           : in     vl_logic;
        addr            : out    vl_logic_vector(11 downto 0)
    );
end noise_addr;
