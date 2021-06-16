library verilog;
use verilog.vl_types.all;
entity qq_state is
    generic(
        IDLE            : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        S1              : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi1);
        S2              : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi1, Hi0);
        S3              : vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi0);
        S4              : vl_logic_vector(3 downto 0) := (Hi1, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        i               : in     vl_logic_vector(3 downto 0);
        Q1Q8_Q2Q7       : out    vl_logic;
        Q3Q6_Q4Q5       : out    vl_logic;
        stateover       : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 0;
    attribute S1_mti_vect_attrib : integer;
    attribute S1_mti_vect_attrib of S1 : constant is 1;
    attribute S2_mti_vect_attrib : integer;
    attribute S2_mti_vect_attrib of S2 : constant is 2;
    attribute S3_mti_vect_attrib : integer;
    attribute S3_mti_vect_attrib of S3 : constant is 4;
    attribute S4_mti_vect_attrib : integer;
    attribute S4_mti_vect_attrib of S4 : constant is 8;
end qq_state;
