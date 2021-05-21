library verilog;
use verilog.vl_types.all;
entity dump_sustain_timer is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        start           : out    vl_logic;
        dump_sustain_data: in     vl_logic_vector(3 downto 0);
        load            : in     vl_logic;
        clk_10k         : in     vl_logic
    );
end dump_sustain_timer;
