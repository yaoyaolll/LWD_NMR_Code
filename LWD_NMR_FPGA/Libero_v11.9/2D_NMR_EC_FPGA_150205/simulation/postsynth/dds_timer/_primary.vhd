library verilog;
use verilog.vl_types.all;
entity dds_timer is
    port(
        count_2         : out    vl_logic_vector(4 downto 0);
        count_0         : out    vl_logic_vector(7 downto 5);
        GLA             : in     vl_logic;
        dds_change_0_dds_rst: in     vl_logic;
        dds_change_0_dds_conf: in     vl_logic;
        dds_state_0_state_over: in     vl_logic
    );
end dds_timer;
