library verilog;
use verilog.vl_types.all;
entity n_rdclk_syn is
    port(
        n_rdclk         : out    vl_logic;
        GLA             : in     vl_logic;
        XRD_c           : in     vl_logic;
        n_acq_change_0_n_rst_n_0: in     vl_logic;
        top_code_0_n_rd_en: in     vl_logic
    );
end n_rdclk_syn;
