library verilog;
use verilog.vl_types.all;
entity off_on_coder is
    port(
        i_3             : out    vl_logic_vector(1 downto 0);
        count_3         : in     vl_logic_vector(4 downto 0);
        GLA             : in     vl_logic;
        bri_dump_sw_0_dumpoff_ctr: in     vl_logic;
        bri_dump_sw_0_reset_out_0: in     vl_logic
    );
end off_on_coder;
