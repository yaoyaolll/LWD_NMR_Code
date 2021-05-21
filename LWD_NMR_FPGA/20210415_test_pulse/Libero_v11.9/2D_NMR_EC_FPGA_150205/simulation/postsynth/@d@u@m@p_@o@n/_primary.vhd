library verilog;
use verilog.vl_types.all;
entity DUMP_ON is
    port(
        OR2_1_Y         : in     vl_logic;
        OR2_2_Y         : in     vl_logic;
        DUMP_ON_0_dump_on: out    vl_logic;
        GLA             : in     vl_logic
    );
end DUMP_ON;
