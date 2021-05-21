library verilog;
use verilog.vl_types.all;
entity pd_pluse_state is
    port(
        i_5             : in     vl_logic_vector(0 downto 0);
        i_0             : in     vl_logic_vector(5 downto 4);
        i_4             : in     vl_logic_vector(3 downto 1);
        pd_pulse_en_c   : out    vl_logic;
        ddsclkout_c     : in     vl_logic;
        pd_pluse_state_0_stateover: out    vl_logic;
        net_27          : in     vl_logic
    );
end pd_pluse_state;
