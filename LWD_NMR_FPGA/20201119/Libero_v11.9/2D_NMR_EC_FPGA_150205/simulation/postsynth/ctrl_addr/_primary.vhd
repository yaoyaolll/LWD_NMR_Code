library verilog;
use verilog.vl_types.all;
entity ctrl_addr is
    port(
        s_periodnum     : in     vl_logic_vector(3 downto 0);
        addrout         : out    vl_logic_vector(3 downto 0);
        s_acq_change_0_s_load_0: in     vl_logic;
        GLA             : in     vl_logic;
        s_acq_change_0_s_rst: in     vl_logic;
        signalclkctrl_0_clk_add: in     vl_logic
    );
end ctrl_addr;
