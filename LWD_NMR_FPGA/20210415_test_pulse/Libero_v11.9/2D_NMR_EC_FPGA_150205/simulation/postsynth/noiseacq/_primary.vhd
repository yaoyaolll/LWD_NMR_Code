library verilog;
use verilog.vl_types.all;
entity noiseacq is
    port(
        n_en            : in     vl_logic;
        rdclk           : in     vl_logic;
        rd_rst          : in     vl_logic;
        r_en            : in     vl_logic;
        wclkout         : out    vl_logic;
        dataout         : out    vl_logic_vector(15 downto 0);
        w_data          : in     vl_logic_vector(11 downto 0);
        addr            : out    vl_logic_vector(7 downto 0);
        addr_rd         : out    vl_logic_vector(7 downto 0);
        RESET           : in     vl_logic;
        divnum          : in     vl_logic_vector(9 downto 0);
        n_load          : in     vl_logic;
        acqnum          : in     vl_logic_vector(7 downto 0);
        clkin_100M      : in     vl_logic;
        Y               : out    vl_logic;
        clkout          : out    vl_logic;
        en              : out    vl_logic
    );
end noiseacq;
