library verilog;
use verilog.vl_types.all;
entity signalclkctrl is
    port(
        s_acqnum        : in     vl_logic_vector(15 downto 0);
        s_periodnum     : in     vl_logic_vector(3 downto 0);
        s_stripnum      : in     vl_logic_vector(11 downto 0);
        s_acq_change_0_s_load_0: in     vl_logic;
        s_acq_change_0_s_load: in     vl_logic;
        GLA             : in     vl_logic;
        s_acq_change_0_s_rst: in     vl_logic;
        signalclkctrl_0_entop: out    vl_logic;
        signal_acq_0_Signal_acq_clk: out    vl_logic;
        clkout          : in     vl_logic;
        signalclkctrl_0_clk_add: out    vl_logic
    );
end signalclkctrl;
