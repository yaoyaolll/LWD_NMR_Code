library verilog;
use verilog.vl_types.all;
entity dump_state is
    generic(
        IDLE            : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S1              : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        S2              : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        S3              : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        S4              : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        S5              : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        S6              : vl_logic_vector(6 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        S7              : vl_logic_vector(6 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        i               : in     vl_logic_vector(8 downto 0);
        off_start       : out    vl_logic;
        on_start        : out    vl_logic;
        timer_start     : out    vl_logic
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
    attribute S5_mti_vect_attrib : integer;
    attribute S5_mti_vect_attrib of S5 : constant is 16;
    attribute S6_mti_vect_attrib : integer;
    attribute S6_mti_vect_attrib of S6 : constant is 32;
    attribute S7_mti_vect_attrib : integer;
    attribute S7_mti_vect_attrib of S7 : constant is 64;
end dump_state;
