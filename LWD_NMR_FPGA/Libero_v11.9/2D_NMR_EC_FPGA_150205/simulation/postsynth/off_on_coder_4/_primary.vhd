library verilog;
use verilog.vl_types.all;
entity off_on_coder_4 is
    port(
        i_6             : out    vl_logic_vector(1 downto 1);
        i_7             : out    vl_logic_vector(0 downto 0);
        count_7         : in     vl_logic_vector(4 downto 0);
        GLA             : in     vl_logic;
        dump_state_0_on_start: in     vl_logic;
        state1ms_choice_0_reset_out: in     vl_logic
    );
end off_on_coder_4;
