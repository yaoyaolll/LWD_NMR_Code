library verilog;
use verilog.vl_types.all;
entity pd_pluse_timer is
    port(
        count_0         : out    vl_logic_vector(15 downto 8);
        count_2         : out    vl_logic_vector(7 downto 5);
        count_5         : out    vl_logic_vector(4 downto 0);
        net_27          : in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        pulse_start_c   : in     vl_logic;
        pd_pluse_state_0_stateover: in     vl_logic
    );
end pd_pluse_timer;
