library verilog;
use verilog.vl_types.all;
entity state_switch is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        time_up_in      : in     vl_logic;
        start           : in     vl_logic_vector(4 downto 0);
        state_over_in   : in     vl_logic_vector(3 downto 0);
        datain_scale    : in     vl_logic_vector(21 downto 0);
        datain_scan     : in     vl_logic_vector(19 downto 0);
        datain_noise    : in     vl_logic_vector(19 downto 0);
        datain_pluse    : in     vl_logic_vector(19 downto 0);
        datain_state_1ms: in     vl_logic_vector(19 downto 0);
        dataout         : out    vl_logic_vector(21 downto 0);
        state_start     : out    vl_logic;
        state_over_n    : out    vl_logic;
        clk_en_scale    : out    vl_logic;
        clk_en_scan     : out    vl_logic;
        clk_en_noise    : out    vl_logic;
        clk_en_pluse    : out    vl_logic;
        clk_en_st1ms    : out    vl_logic
    );
end state_switch;
