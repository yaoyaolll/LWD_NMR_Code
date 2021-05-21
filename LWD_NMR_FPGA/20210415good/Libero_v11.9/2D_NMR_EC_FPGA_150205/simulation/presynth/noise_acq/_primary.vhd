library verilog;
use verilog.vl_types.all;
entity noise_acq is
    port(
        noise_load      : in     vl_logic;
        n_reset         : in     vl_logic;
        RAM_RDaddr_rst  : in     vl_logic;
        Noise_acq_clk   : out    vl_logic;
        RAM_WT_EN       : in     vl_logic;
        RAM_RD_EN       : in     vl_logic;
        XRD             : in     vl_logic;
        clk_sys         : in     vl_logic;
        n_acqnum        : in     vl_logic_vector(11 downto 0);
        n_ADC           : in     vl_logic_vector(11 downto 0);
        n_divnum        : in     vl_logic_vector(9 downto 0);
        RAM_data        : out    vl_logic_vector(15 downto 0)
    );
end noise_acq;
