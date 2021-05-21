library verilog;
use verilog.vl_types.all;
entity ClockManagement is
    port(
        sigtimedata     : in     vl_logic_vector(15 downto 0);
        OCX40MHz_c      : in     vl_logic;
        ClockManagement_GND: in     vl_logic;
        ClockManagement_VCC: in     vl_logic;
        net_27          : in     vl_logic;
        clk_5K          : out    vl_logic;
        sigtimeup_c     : out    vl_logic;
        top_code_0_sigrst: in     vl_logic;
        GLA             : out    vl_logic
    );
end ClockManagement;
