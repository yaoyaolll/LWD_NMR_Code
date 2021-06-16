library verilog;
use verilog.vl_types.all;
entity topctrlchange is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        change          : in     vl_logic_vector(1 downto 0);
        interupt        : out    vl_logic;
        interin1        : in     vl_logic;
        interin2        : in     vl_logic;
        interin3        : in     vl_logic;
        rt_sw           : out    vl_logic;
        rt_swin1        : in     vl_logic;
        rt_swin2        : in     vl_logic;
        rt_swin3        : in     vl_logic;
        soft_dump       : out    vl_logic;
        s_dumpin1       : in     vl_logic;
        s_dumpin2       : in     vl_logic;
        s_dumpin3       : in     vl_logic;
        sw_acq1         : out    vl_logic;
        sw_acq1in1      : in     vl_logic;
        sw_acq1in2      : in     vl_logic;
        sw_acq1in3      : in     vl_logic;
        sw_acq2         : out    vl_logic;
        sw_acq2in1      : in     vl_logic;
        sw_acq2in2      : in     vl_logic;
        sw_acq2in3      : in     vl_logic
    );
end topctrlchange;
