library verilog;
use verilog.vl_types.all;
entity s_acq_change is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic_vector(1 downto 0);
        s_load          : out    vl_logic;
        s_loadin1       : in     vl_logic;
        s_loadin2       : in     vl_logic;
        s_rst           : out    vl_logic;
        s_rstin1        : in     vl_logic;
        s_rstin2        : in     vl_logic;
        s_acqnum        : out    vl_logic_vector(15 downto 0);
        s_acqnumin1     : in     vl_logic_vector(15 downto 0);
        s_acqnumin2     : in     vl_logic_vector(15 downto 0);
        s_stripnum      : out    vl_logic_vector(11 downto 0);
        s_stripnumin1   : in     vl_logic_vector(11 downto 0);
        s_stripnumin2   : in     vl_logic_vector(11 downto 0)
    );
end s_acq_change;
