library verilog;
use verilog.vl_types.all;
entity cal_div is
    port(
        cal_para_out    : in     vl_logic_vector(5 downto 0);
        ddsclkout_c     : in     vl_logic;
        cal_out_c       : out    vl_logic;
        net_33          : in     vl_logic;
        scanstate_0_calctrl: in     vl_logic
    );
end cal_div;
