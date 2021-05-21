library verilog;
use verilog.vl_types.all;
entity noise_addr_1 is
    port(
        addr_c          : out    vl_logic_vector(7 downto 0);
        RESET_c         : in     vl_logic;
        wclkout         : in     vl_logic
    );
end noise_addr_1;
