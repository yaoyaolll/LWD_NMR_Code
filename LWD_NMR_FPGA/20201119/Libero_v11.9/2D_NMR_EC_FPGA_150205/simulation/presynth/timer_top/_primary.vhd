library verilog;
use verilog.vl_types.all;
entity timer_top is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        clk_en_scan     : out    vl_logic;
        clk_en_st1ms    : out    vl_logic;
        clk_en_pluse    : out    vl_logic;
        clk_en_scale    : out    vl_logic;
        clk_en_noise    : out    vl_logic;
        datain_state_1ms: in     vl_logic_vector(19 downto 0);
        datain_pluse    : in     vl_logic_vector(19 downto 0);
        datain_scale    : in     vl_logic_vector(21 downto 0);
        datain_scan     : in     vl_logic_vector(19 downto 0);
        datain_noise    : in     vl_logic_vector(19 downto 0);
        start           : in     vl_logic_vector(4 downto 0);
        state_over_in   : in     vl_logic_vector(3 downto 0)
    );
end timer_top;
