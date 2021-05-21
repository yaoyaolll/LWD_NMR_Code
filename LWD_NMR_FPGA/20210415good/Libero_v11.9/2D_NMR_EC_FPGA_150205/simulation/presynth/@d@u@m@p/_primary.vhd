library verilog;
use verilog.vl_types.all;
entity DUMP is
    port(
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        clk_sys         : in     vl_logic;
        dump_off        : out    vl_logic;
        dump_on         : out    vl_logic;
        dump_load       : in     vl_logic;
        bri_cycle       : in     vl_logic;
        pluse_start     : in     vl_logic;
        dump_choice     : in     vl_logic_vector(2 downto 0);
        dump_para       : in     vl_logic_vector(11 downto 0)
    );
end DUMP;
