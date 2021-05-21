library verilog;
use verilog.vl_types.all;
entity s_clk_div4 is
    port(
        s_acq_change_0_s_rst: in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        clkout          : out    vl_logic;
        scan_scale_sw_0_s_start: in     vl_logic;
        signalclkctrl_0_entop: in     vl_logic
    );
end s_clk_div4;
