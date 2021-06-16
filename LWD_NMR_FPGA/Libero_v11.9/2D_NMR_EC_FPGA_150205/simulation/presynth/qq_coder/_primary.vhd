library verilog;
use verilog.vl_types.all;
entity qq_coder is
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        count           : in     vl_logic_vector(4 downto 0);
        qq_para1        : in     vl_logic_vector(3 downto 0);
        qq_para2        : in     vl_logic_vector(5 downto 0);
        qq_para3        : in     vl_logic_vector(5 downto 0);
        i               : out    vl_logic_vector(3 downto 0)
    );
end qq_coder;
