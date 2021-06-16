library verilog;
use verilog.vl_types.all;
entity pd_pluse_timer is
    port(
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        stateover       : in     vl_logic;
        count           : out    vl_logic_vector(15 downto 0);
        pluse_start     : in     vl_logic
    );
end pd_pluse_timer;
