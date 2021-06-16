library verilog;
use verilog.vl_types.all;
entity bri_state is
    port(
        i_1             : in     vl_logic_vector(0 downto 0);
        i_0             : in     vl_logic_vector(3 downto 1);
        down            : out    vl_logic;
        ddsclkout_c     : in     vl_logic;
        up              : out    vl_logic;
        bri_dump_sw_0_reset_out_0: in     vl_logic;
        clk_4f_en       : in     vl_logic
    );
end bri_state;
