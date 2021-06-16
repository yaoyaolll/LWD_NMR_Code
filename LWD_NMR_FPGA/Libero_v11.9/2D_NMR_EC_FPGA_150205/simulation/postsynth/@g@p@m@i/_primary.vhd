library verilog;
use verilog.vl_types.all;
entity GPMI is
    port(
        GPMI_VCC        : in     vl_logic;
        xd_1            : out    vl_logic;
        tri_ctrl_c      : in     vl_logic;
        zcs2_c          : in     vl_logic;
        net_27          : out    vl_logic;
        xwe_c           : in     vl_logic;
        GPMI_0_code_en  : out    vl_logic;
        GLA             : in     vl_logic;
        gpio_c          : in     vl_logic
    );
end GPMI;
