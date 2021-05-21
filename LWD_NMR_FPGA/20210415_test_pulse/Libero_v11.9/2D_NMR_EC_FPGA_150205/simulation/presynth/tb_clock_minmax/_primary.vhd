library verilog;
use verilog.vl_types.all;
entity tb_clock_minmax is
    generic(
        initialize      : integer := 0
    );
    port(
        tb_status       : in     vl_logic_vector(1 downto 0);
        CLK             : out    vl_logic;
        offset_bits     : in     vl_logic_vector(63 downto 0);
        period_bits     : in     vl_logic_vector(63 downto 0);
        duty_bits       : in     vl_logic_vector(63 downto 0);
        minLH_bits      : in     vl_logic_vector(63 downto 0);
        maxLH_bits      : in     vl_logic_vector(63 downto 0);
        minHL_bits      : in     vl_logic_vector(63 downto 0);
        maxHL_bits      : in     vl_logic_vector(63 downto 0);
        jRise_bits      : in     vl_logic_vector(63 downto 0);
        jFall_bits      : in     vl_logic_vector(63 downto 0)
    );
end tb_clock_minmax;
