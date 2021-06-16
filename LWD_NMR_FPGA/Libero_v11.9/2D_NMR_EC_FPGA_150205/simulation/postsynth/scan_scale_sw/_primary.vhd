library verilog;
use verilog.vl_types.all;
entity scan_scale_sw is
    port(
        change          : in     vl_logic_vector(1 downto 1);
        un1_top_code_0_3_0: in     vl_logic_vector(0 downto 0);
        ddsclkout_c     : in     vl_logic;
        net_27          : in     vl_logic;
        scan_scale_sw_0_s_start: out    vl_logic;
        sd_acq_en_c     : in     vl_logic;
        scanstate_0_s_acq: in     vl_logic
    );
end scan_scale_sw;
