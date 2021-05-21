library verilog;
use verilog.vl_types.all;
entity signalclkctrl is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        load            : in     vl_logic;
        acqnum          : in     vl_logic_vector(15 downto 0);
        stripnum        : in     vl_logic_vector(11 downto 0);
        periodnum       : in     vl_logic_vector(3 downto 0);
        entop           : out    vl_logic;
        clk_add         : out    vl_logic;
        clk_acq         : out    vl_logic;
        clkin           : in     vl_logic
    );
end signalclkctrl;
