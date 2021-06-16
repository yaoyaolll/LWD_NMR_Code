library verilog;
use verilog.vl_types.all;
entity dump_state is
    port(
        i_9             : in     vl_logic_vector(0 downto 0);
        i_8             : in     vl_logic_vector(1 downto 1);
        i_5             : in     vl_logic_vector(3 downto 2);
        i_1             : in     vl_logic_vector(5 downto 4);
        i_0             : in     vl_logic_vector(8 downto 6);
        dump_state_0_off_start: out    vl_logic;
        GLA             : in     vl_logic;
        state1ms_choice_0_reset_out: in     vl_logic;
        dump_state_0_timer_start: out    vl_logic;
        dump_state_0_on_start: out    vl_logic
    );
end dump_state;
