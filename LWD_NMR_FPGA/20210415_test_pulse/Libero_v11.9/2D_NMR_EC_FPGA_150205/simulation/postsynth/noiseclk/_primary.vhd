library verilog;
use verilog.vl_types.all;
entity noiseclk is
    port(
        n_divnum        : in     vl_logic_vector(9 downto 0);
        top_code_0_n_load: in     vl_logic;
        GLA             : in     vl_logic;
        s_clk_div4_0_clkout: out    vl_logic;
        noiseclkctrl_0_en: in     vl_logic;
        n_acq_change_0_n_acq_start: in     vl_logic;
        n_acq_change_0_n_rst_n_0: in     vl_logic
    );
end noiseclk;
