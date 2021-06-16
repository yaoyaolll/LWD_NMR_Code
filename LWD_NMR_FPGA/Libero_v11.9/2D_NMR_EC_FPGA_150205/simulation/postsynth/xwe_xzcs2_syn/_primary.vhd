library verilog;
use verilog.vl_types.all;
entity xwe_xzcs2_syn is
    port(
        GLA             : in     vl_logic;
        GPMI_0_code_en  : out    vl_logic;
        xwe_c           : in     vl_logic;
        net_27          : in     vl_logic;
        zcs2_c          : in     vl_logic
    );
end xwe_xzcs2_syn;
