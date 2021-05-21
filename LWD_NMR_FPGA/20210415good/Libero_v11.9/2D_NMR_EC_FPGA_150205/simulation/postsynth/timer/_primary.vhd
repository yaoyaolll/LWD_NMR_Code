library verilog;
use verilog.vl_types.all;
entity timer is
    port(
        dataout         : in     vl_logic_vector(21 downto 0);
        GLA             : in     vl_logic;
        net_27          : in     vl_logic;
        timer_0_time_up : out    vl_logic;
        state_switch_0_state_over_n: in     vl_logic;
        state_switch_0_state_start: in     vl_logic
    );
end timer;
