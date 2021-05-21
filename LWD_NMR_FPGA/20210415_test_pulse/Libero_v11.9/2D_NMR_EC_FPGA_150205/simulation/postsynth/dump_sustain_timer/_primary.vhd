library verilog;
use verilog.vl_types.all;
entity dump_sustain_timer is
    port(
        dump_sustain_timer_0_start: out    vl_logic;
        clk_5K          : in     vl_logic;
        AND2_1_Y        : in     vl_logic;
        scalestate_0_dump_sustain_ctrl: in     vl_logic
    );
end dump_sustain_timer;
