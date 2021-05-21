library verilog;
use verilog.vl_types.all;
entity bridge_div is
    port(
        scaleddsdiv     : in     vl_logic_vector(5 downto 0);
        top_code_0_bridge_load: in     vl_logic;
        GLA             : in     vl_logic;
        bri_dump_sw_0_reset_out: in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        clk_4f_en       : out    vl_logic;
        pd_pulse_en_c   : in     vl_logic
    );
end bridge_div;
