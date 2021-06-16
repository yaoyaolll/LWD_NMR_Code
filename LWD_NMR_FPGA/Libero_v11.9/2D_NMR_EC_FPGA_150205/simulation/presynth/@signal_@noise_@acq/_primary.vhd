library verilog;
use verilog.vl_types.all;
entity Signal_Noise_Acq is
    port(
        clk_sys         : in     vl_logic;
        clk_dds         : in     vl_logic;
        acq_clk         : out    vl_logic;
        n_s_ctrl        : in     vl_logic;
        n_reset         : in     vl_logic;
        noise_load      : in     vl_logic;
        RAM_RDaddr_rst  : in     vl_logic;
        RAM_RD_EN       : in     vl_logic;
        RAM_WT_EN       : in     vl_logic;
        XRD             : in     vl_logic;
        signal_load     : in     vl_logic;
        s_reset         : in     vl_logic;
        s_acq_en        : in     vl_logic;
        adcdata         : in     vl_logic_vector(11 downto 0);
        dataout         : out    vl_logic_vector(15 downto 0);
        n_acqnum        : in     vl_logic_vector(11 downto 0);
        n_divnum        : in     vl_logic_vector(9 downto 0);
        s_periodnum     : in     vl_logic_vector(3 downto 0);
        stripnum        : in     vl_logic_vector(11 downto 0);
        acqnum          : in     vl_logic_vector(15 downto 0);
        s_addchoice     : in     vl_logic_vector(4 downto 0)
    );
end Signal_Noise_Acq;
