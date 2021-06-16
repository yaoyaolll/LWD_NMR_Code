library verilog;
use verilog.vl_types.all;
entity state_1ms is
    generic(
        IDLE            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        INIT            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        INIT2           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        RESET           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        S1              : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        S2              : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        S3              : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S4              : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S5              : vl_logic_vector(9 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S6              : vl_logic_vector(9 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        clken_p         : in     vl_logic;
        rst_n           : in     vl_logic;
        load            : in     vl_logic;
        loadchoice      : in     vl_logic_vector(3 downto 0);
        datain          : in     vl_logic_vector(15 downto 0);
        reset_out       : out    vl_logic;
        dump_start      : out    vl_logic;
        pluse_start     : out    vl_logic;
        bri_cycle       : out    vl_logic;
        rt_sw           : out    vl_logic;
        soft_dump       : out    vl_logic;
        timecount       : out    vl_logic_vector(19 downto 0)
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 1;
    attribute INIT_mti_vect_attrib : integer;
    attribute INIT_mti_vect_attrib of INIT : constant is 2;
    attribute INIT2_mti_vect_attrib : integer;
    attribute INIT2_mti_vect_attrib of INIT2 : constant is 4;
    attribute RESET_mti_vect_attrib : integer;
    attribute RESET_mti_vect_attrib of RESET : constant is 8;
    attribute S1_mti_vect_attrib : integer;
    attribute S1_mti_vect_attrib of S1 : constant is 16;
    attribute S2_mti_vect_attrib : integer;
    attribute S2_mti_vect_attrib of S2 : constant is 32;
    attribute S3_mti_vect_attrib : integer;
    attribute S3_mti_vect_attrib of S3 : constant is 64;
    attribute S4_mti_vect_attrib : integer;
    attribute S4_mti_vect_attrib of S4 : constant is 128;
    attribute S5_mti_vect_attrib : integer;
    attribute S5_mti_vect_attrib of S5 : constant is 256;
    attribute S6_mti_vect_attrib : integer;
    attribute S6_mti_vect_attrib of S6 : constant is 512;
end state_1ms;
