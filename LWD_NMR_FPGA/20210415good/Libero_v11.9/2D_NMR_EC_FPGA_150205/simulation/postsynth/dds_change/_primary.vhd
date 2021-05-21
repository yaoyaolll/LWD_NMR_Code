library verilog;
use verilog.vl_types.all;
entity dds_change is
    port(
        un1_top_code_0_3_0: in     vl_logic_vector(1 downto 0);
        GLA             : in     vl_logic;
        top_code_0_pluse_rst: in     vl_logic;
        net_45          : in     vl_logic;
        net_33_0        : in     vl_logic;
        plusestate_0_dds_config: in     vl_logic;
        scalestate_0_dds_conf: in     vl_logic;
        scanstate_0_dds_conf: in     vl_logic;
        net_27          : in     vl_logic;
        dds_change_0_dds_conf: out    vl_logic;
        un1_change_2    : out    vl_logic;
        dds_change_0_dds_rst: out    vl_logic
    );
end dds_change;
