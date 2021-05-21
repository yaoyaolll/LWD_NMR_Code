library verilog;
use verilog.vl_types.all;
entity bri_coder is
    port(
        clk_dds         : in     vl_logic;
        clk_4f_en       : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        quar_delay      : in     vl_logic;
        phase           : in     vl_logic;
        count           : in     vl_logic_vector(7 downto 0);
        half_para       : in     vl_logic_vector(7 downto 0);
        half            : out    vl_logic;
        bri_cycle       : out    vl_logic;
        i               : out    vl_logic_vector(4 downto 0);
        turn_delay      : in     vl_logic
    );
end bri_coder;
