library verilog;
use verilog.vl_types.all;
entity Acq_clk_noise is
    port(
        clk_sys         : in     vl_logic;
        n_en            : in     vl_logic;
        n_reset         : in     vl_logic;
        n_load          : in     vl_logic;
        acq_noise       : out    vl_logic;
        n_divnum        : in     vl_logic_vector(9 downto 0);
        n_acqnum        : in     vl_logic_vector(11 downto 0)
    );
end Acq_clk_noise;
