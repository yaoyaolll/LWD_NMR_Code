library verilog;
use verilog.vl_types.all;
entity PLUSE is
    port(
        state_start     : in     vl_logic;
        rst_n           : in     vl_logic;
        phase           : in     vl_logic;
        quar_delay      : in     vl_logic;
        clk_sys         : in     vl_logic;
        pluse_load      : in     vl_logic;
        bri_cycle       : out    vl_logic;
        Q1Q8            : out    vl_logic;
        Q3Q6            : out    vl_logic;
        Q4Q5            : out    vl_logic;
        Q2Q7            : out    vl_logic;
        clk_dds         : in     vl_logic;
        clk_4f_en       : in     vl_logic;
        down            : out    vl_logic;
        up              : out    vl_logic;
        qq_para         : in     vl_logic_vector(15 downto 0);
        bri_para        : in     vl_logic_vector(7 downto 0);
        turn_delay      : in     vl_logic
    );
end PLUSE;
