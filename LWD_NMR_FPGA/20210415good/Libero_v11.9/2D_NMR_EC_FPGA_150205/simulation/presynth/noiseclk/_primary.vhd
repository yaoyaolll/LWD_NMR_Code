library verilog;
use verilog.vl_types.all;
entity noiseclk is
    port(
        clk_sys         : in     vl_logic;
        clken           : in     vl_logic;
        n_acq_en        : in     vl_logic;
        divnum          : in     vl_logic_vector(9 downto 0);
        rst_n           : in     vl_logic;
        load            : in     vl_logic;
        clkout          : out    vl_logic
    );
end noiseclk;
