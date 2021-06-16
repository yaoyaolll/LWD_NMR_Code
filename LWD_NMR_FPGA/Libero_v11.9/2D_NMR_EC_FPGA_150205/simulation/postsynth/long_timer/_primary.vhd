library verilog;
use verilog.vl_types.all;
entity long_timer is
    port(
        sigtimedata     : in     vl_logic_vector(15 downto 0);
        GLA             : in     vl_logic;
        top_code_0_sigrst: in     vl_logic;
        sigtimeup_c     : out    vl_logic;
        clk_5K          : in     vl_logic;
        net_27          : in     vl_logic
    );
end long_timer;
