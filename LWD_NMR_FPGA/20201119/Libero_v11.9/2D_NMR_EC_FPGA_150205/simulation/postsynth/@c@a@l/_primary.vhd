library verilog;
use verilog.vl_types.all;
entity CAL is
    port(
        cal_data        : in     vl_logic_vector(5 downto 0);
        scanstate_0_calctrl: in     vl_logic;
        net_33          : in     vl_logic;
        cal_out_c       : out    vl_logic;
        ddsclkout_c     : in     vl_logic;
        GLA             : in     vl_logic;
        top_code_0_cal_load: in     vl_logic
    );
end CAL;
