library verilog;
use verilog.vl_types.all;
entity scan_scale_sw is
    port(
        rst_n           : in     vl_logic;
        dds             : in     vl_logic;
        change          : in     vl_logic_vector(1 downto 0);
        s_start         : out    vl_logic;
        s_startin1      : in     vl_logic;
        s_startin2      : in     vl_logic
    );
end scan_scale_sw;
