library verilog;
use verilog.vl_types.all;
entity Acq_clk_signal is
    port(
        s_reset         : in     vl_logic;
        clk_sys         : in     vl_logic;
        s_acq           : in     vl_logic;
        ddsclkout       : in     vl_logic;
        s_load          : in     vl_logic;
        clk_add         : out    vl_logic;
        clk_acq         : out    vl_logic;
        stripnum        : in     vl_logic_vector(11 downto 0);
        acqnum          : in     vl_logic_vector(15 downto 0);
        periodnum       : in     vl_logic_vector(3 downto 0)
    );
end Acq_clk_signal;
