library verilog;
use verilog.vl_types.all;
entity pllclk is
    port(
        pllclk_VCC      : in     vl_logic;
        pllclk_GND      : in     vl_logic;
        OCX40MHz_c      : in     vl_logic;
        pllclk_0_GLB    : out    vl_logic;
        GLA             : out    vl_logic
    );
end pllclk;
