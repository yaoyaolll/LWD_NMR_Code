library verilog;
use verilog.vl_types.all;
entity n_pluse_acq is
    port(
        n_acq_change_0_n_acq_start: out    vl_logic;
        n_acq_change_0_n_rst_n: out    vl_logic;
        net_27          : in     vl_logic;
        noisestate_0_n_acq: in     vl_logic;
        plusestate_0_pluse_acq: in     vl_logic;
        top_code_0_pluse_noise_ctrl: in     vl_logic;
        top_code_0_noise_rst_0: in     vl_logic;
        top_code_0_pluse_rst: in     vl_logic;
        GLA             : in     vl_logic;
        n_acq_change_0_n_rst_n_0: out    vl_logic
    );
end n_pluse_acq;
