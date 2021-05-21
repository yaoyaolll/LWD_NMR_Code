library verilog;
use verilog.vl_types.all;
entity off_on_coder_2 is
    port(
        un1_off_on_coder_0: out    vl_logic_vector(1 downto 0);
        un1_off_on_timer_0: in     vl_logic_vector(4 downto 0);
        GLA             : in     vl_logic;
        nsctrl_choice_0_dumpoff_ctr: in     vl_logic;
        nsctrl_choice_0_dumponoff_rst: in     vl_logic
    );
end off_on_coder_2;
