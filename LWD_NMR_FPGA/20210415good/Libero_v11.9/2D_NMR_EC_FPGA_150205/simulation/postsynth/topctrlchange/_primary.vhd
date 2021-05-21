library verilog;
use verilog.vl_types.all;
entity topctrlchange is
    port(
        change          : in     vl_logic_vector(1 downto 0);
        GLA             : in     vl_logic;
        plusestate_0_sw_acq1: in     vl_logic;
        scalestate_0_sw_acq1: in     vl_logic;
        plusestate_0_state_over_n: in     vl_logic;
        scalestate_0_tetw_pluse: in     vl_logic;
        nsctrl_choice_0_intertodsp: in     vl_logic;
        scalestate_0_sw_acq2: in     vl_logic;
        nsctrl_choice_0_sw_acq2: in     vl_logic;
        plusestate_0_soft_d: in     vl_logic;
        scalestate_0_soft_d: in     vl_logic;
        nsctrl_choice_0_soft_d: in     vl_logic;
        scalestate_0_rt_sw: in     vl_logic;
        nsctrl_choice_0_rt_sw: in     vl_logic;
        net_27          : in     vl_logic;
        rt_sw_net_1     : out    vl_logic;
        soft_dump_net_1 : out    vl_logic;
        sw_acq1_c       : out    vl_logic;
        sw_acq2_c       : out    vl_logic;
        un1_change_2    : in     vl_logic;
        interupt_c      : out    vl_logic
    );
end topctrlchange;
