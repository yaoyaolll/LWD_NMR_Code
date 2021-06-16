library verilog;
use verilog.vl_types.all;
entity sd_sacq_timer is
    port(
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        stateover       : in     vl_logic;
        count           : out    vl_logic_vector(21 downto 0);
        s_acq1          : in     vl_logic
    );
end sd_sacq_timer;
