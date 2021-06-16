library verilog;
use verilog.vl_types.all;
entity DUMP is
    port(
        dumpdata        : in     vl_logic_vector(11 downto 0);
        dump_cho        : in     vl_logic_vector(2 downto 0);
        state1ms_choice_0_dump_start: in     vl_logic;
        top_code_0_dumpload: in     vl_logic;
        state1ms_choice_0_bri_cycle: in     vl_logic;
        bri_div_start_0 : in     vl_logic;
        DUMP_0_dump_off : out    vl_logic;
        DUMP_0_dump_on  : out    vl_logic;
        state1ms_choice_0_reset_out: in     vl_logic;
        GLA             : in     vl_logic
    );
end DUMP;
