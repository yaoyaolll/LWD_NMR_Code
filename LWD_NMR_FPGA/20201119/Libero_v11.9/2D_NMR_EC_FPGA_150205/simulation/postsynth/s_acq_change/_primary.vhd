library verilog;
use verilog.vl_types.all;
entity s_acq_change is
    port(
        s_acqnum_1      : in     vl_logic_vector(11 downto 0);
        s_acqnum_0      : in     vl_logic_vector(15 downto 0);
        strippluse      : in     vl_logic_vector(11 downto 0);
        change          : in     vl_logic_vector(1 downto 0);
        s_acqnum        : out    vl_logic_vector(15 downto 0);
        s_stripnum      : out    vl_logic_vector(11 downto 0);
        un1_top_code_0_3_0: in     vl_logic_vector(1 downto 0);
        s_acq_change_0_s_load: out    vl_logic;
        scalestate_0_load_out: in     vl_logic;
        top_code_0_s_load: in     vl_logic;
        net_45          : in     vl_logic;
        net_33_0        : in     vl_logic;
        net_27          : in     vl_logic;
        s_acq_change_0_s_rst: out    vl_logic;
        GLA             : in     vl_logic;
        s_acq_change_0_s_load_0: out    vl_logic
    );
end s_acq_change;
