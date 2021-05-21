library verilog;
use verilog.vl_types.all;
entity dump_timer is
    port(
        count_1         : out    vl_logic_vector(11 downto 8);
        count_8         : out    vl_logic_vector(4 downto 0);
        count_3         : out    vl_logic_vector(7 downto 5);
        GLA             : in     vl_logic;
        state1ms_choice_0_reset_out: in     vl_logic;
        dump_state_0_timer_start: in     vl_logic;
        state1ms_choice_0_dump_start: in     vl_logic
    );
end dump_timer;
