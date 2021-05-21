library verilog;
use verilog.vl_types.all;
entity RAM is
    port(
        WD              : in     vl_logic_vector(11 downto 0);
        RD              : out    vl_logic_vector(11 downto 0);
        WEN             : in     vl_logic;
        REN             : in     vl_logic;
        WADDR           : in     vl_logic_vector(11 downto 0);
        RADDR           : in     vl_logic_vector(11 downto 0);
        WCLK            : in     vl_logic;
        RCLK            : in     vl_logic;
        RESET           : in     vl_logic
    );
end RAM;
