library verilog;
use verilog.vl_types.all;
entity dump_coder is
    port(
        i_0             : out    vl_logic_vector(8 downto 6);
        i_1             : out    vl_logic_vector(5 downto 4);
        i_5             : out    vl_logic_vector(3 downto 2);
        i_8             : out    vl_logic_vector(1 downto 1);
        i_9             : out    vl_logic_vector(0 downto 0);
        count_3         : in     vl_logic_vector(7 downto 5);
        dump_cho        : in     vl_logic_vector(2 downto 0);
        dumpdata        : in     vl_logic_vector(11 downto 0);
        count_8         : in     vl_logic_vector(4 downto 0);
        count_1         : in     vl_logic_vector(11 downto 8);
        GLA             : in     vl_logic;
        bri_div_start_0 : in     vl_logic;
        state1ms_choice_0_bri_cycle: in     vl_logic;
        top_code_0_dumpload: in     vl_logic;
        state1ms_choice_0_dump_start: in     vl_logic;
        state1ms_choice_0_reset_out: in     vl_logic
    );
end dump_coder;
