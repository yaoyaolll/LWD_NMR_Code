library verilog;
use verilog.vl_types.all;
entity dump_coder is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        pluse_start     : in     vl_logic;
        bri_cycle       : in     vl_logic;
        dump_load       : in     vl_logic;
        dump_choice     : in     vl_logic_vector(2 downto 0);
        dump_para       : in     vl_logic_vector(11 downto 0);
        count           : in     vl_logic_vector(11 downto 0);
        i               : out    vl_logic_vector(8 downto 0)
    );
end dump_coder;
