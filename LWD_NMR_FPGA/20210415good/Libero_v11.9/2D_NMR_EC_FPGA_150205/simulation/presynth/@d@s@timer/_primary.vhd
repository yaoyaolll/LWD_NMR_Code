library verilog;
use verilog.vl_types.all;
entity DSTimer is
    port(
        clk_sys         : in     vl_logic;
        dump_sustain    : in     vl_logic;
        rst_n           : in     vl_logic;
        start           : out    vl_logic;
        state_start     : in     vl_logic;
        clk_10k         : in     vl_logic;
        dump_sustain_data: in     vl_logic_vector(3 downto 0)
    );
end DSTimer;
