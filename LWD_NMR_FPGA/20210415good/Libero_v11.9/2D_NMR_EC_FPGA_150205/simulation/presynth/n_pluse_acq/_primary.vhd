library verilog;
use verilog.vl_types.all;
entity n_pluse_acq is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic;
        n_acq_startin1  : in     vl_logic;
        n_acq_startin2  : in     vl_logic;
        n_acq_start     : out    vl_logic;
        n_rstin1_n      : in     vl_logic;
        n_rstin2_n      : in     vl_logic;
        n_rst_n         : out    vl_logic
    );
end n_pluse_acq;
