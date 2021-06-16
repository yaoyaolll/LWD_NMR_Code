library verilog;
use verilog.vl_types.all;
entity off_on_coder is
    generic(
        off_on_width    : vl_logic_vector(4 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        count           : in     vl_logic_vector(4 downto 0);
        i               : out    vl_logic_vector(1 downto 0)
    );
    attribute off_on_width_mti_vect_attrib : integer;
    attribute off_on_width_mti_vect_attrib of off_on_width : constant is 20;
end off_on_coder;
