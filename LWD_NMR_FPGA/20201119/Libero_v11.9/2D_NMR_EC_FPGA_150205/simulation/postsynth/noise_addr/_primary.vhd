library verilog;
use verilog.vl_types.all;
entity noise_addr is
    port(
        addr_rd_c       : out    vl_logic_vector(7 downto 0);
        rd_rst_c        : in     vl_logic;
        AND2_1_Y        : in     vl_logic
    );
end noise_addr;
