library verilog;
use verilog.vl_types.all;
entity noiseclkctrl is
    port(
        rst_n           : in     vl_logic;
        clk_sys         : in     vl_logic;
        load            : in     vl_logic;
        acqnum          : in     vl_logic_vector(11 downto 0);
        en              : out    vl_logic;
        clkin           : in     vl_logic
    );
end noiseclkctrl;
