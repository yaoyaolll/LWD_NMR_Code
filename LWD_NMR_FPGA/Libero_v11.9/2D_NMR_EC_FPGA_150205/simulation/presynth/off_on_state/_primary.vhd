library verilog;
use verilog.vl_types.all;
entity off_on_state is
    generic(
        IDLE            : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        S1              : vl_logic_vector(1 downto 0) := (Hi0, Hi1);
        S2              : vl_logic_vector(1 downto 0) := (Hi1, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        i               : in     vl_logic_vector(1 downto 0);
        off_on          : out    vl_logic;
        state_over      : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 0;
    attribute S1_mti_vect_attrib : integer;
    attribute S1_mti_vect_attrib of S1 : constant is 1;
    attribute S2_mti_vect_attrib : integer;
    attribute S2_mti_vect_attrib of S2 : constant is 2;
end off_on_state;
