library verilog;
use verilog.vl_types.all;
entity pllclk is
    port(
        POWERDOWN       : in     vl_logic;
        CLKA            : in     vl_logic;
        LOCK            : out    vl_logic;
        GLA             : out    vl_logic;
        GLB             : out    vl_logic
    );
end pllclk;
