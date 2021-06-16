library verilog;
use verilog.vl_types.all;
entity signal_acq is
    port(
        s_reset         : in     vl_logic;
        signal_load     : in     vl_logic;
        clk_sys         : in     vl_logic;
        Signal_acq_clk  : out    vl_logic;
        clk_dds         : in     vl_logic;
        s_acq_en        : in     vl_logic;
        acqnum          : in     vl_logic_vector(15 downto 0);
        stripnum        : in     vl_logic_vector(11 downto 0);
        s_periodnum     : in     vl_logic_vector(3 downto 0);
        signal_data     : out    vl_logic_vector(15 downto 0);
        s_addchoice     : in     vl_logic_vector(4 downto 0);
        s_ADC           : in     vl_logic_vector(11 downto 0)
    );
end signal_acq;
