library verilog;
use verilog.vl_types.all;
entity noiseclkctrl is
    port(
        n_acqnum        : in     vl_logic_vector(11 downto 0);
        top_code_0_n_load: in     vl_logic;
        GLA             : in     vl_logic;
        n_acq_change_0_n_rst_n: in     vl_logic;
        s_clk_div4_0_clkout: in     vl_logic;
        noiseclkctrl_0_en: out    vl_logic
    );
end noiseclkctrl;
