library verilog;
use verilog.vl_types.all;
entity bri_timer is
    port(
        count           : out    vl_logic_vector(7 downto 5);
        count_0         : out    vl_logic_vector(4 downto 0);
        bri_dump_sw_0_reset_out: in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        bri_coder_0_half: in     vl_logic;
        pulse_start_c   : in     vl_logic;
        clk_4f_en       : in     vl_logic
    );
end bri_timer;
