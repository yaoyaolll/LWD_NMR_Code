library verilog;
use verilog.vl_types.all;
entity noise_addr_noise_addr_0_1 is
    port(
        addr            : out    vl_logic_vector(11 downto 0);
        top_code_0_RAM_Rd_rst: in     vl_logic;
        n_rdclk         : in     vl_logic
    );
end noise_addr_noise_addr_0_1;
