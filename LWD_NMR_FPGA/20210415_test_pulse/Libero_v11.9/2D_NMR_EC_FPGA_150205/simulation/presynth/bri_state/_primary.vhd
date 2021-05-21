library verilog;
use verilog.vl_types.all;
entity bri_state is
    generic(
        IDLE            : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S0              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        S00             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        S1              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        S10             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        S2              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        S20             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        S3              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S30             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S4              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S40             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S5              : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S50             : vl_logic_vector(13 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S6              : vl_logic_vector(13 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S60             : vl_logic_vector(13 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_dds         : in     vl_logic;
        clk_4f_en       : in     vl_logic;
        rst_n           : in     vl_logic;
        i               : in     vl_logic_vector(4 downto 0);
        up              : out    vl_logic;
        down            : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 0;
    attribute S0_mti_vect_attrib : integer;
    attribute S0_mti_vect_attrib of S0 : constant is 1;
    attribute S00_mti_vect_attrib : integer;
    attribute S00_mti_vect_attrib of S00 : constant is 2;
    attribute S1_mti_vect_attrib : integer;
    attribute S1_mti_vect_attrib of S1 : constant is 4;
    attribute S10_mti_vect_attrib : integer;
    attribute S10_mti_vect_attrib of S10 : constant is 8;
    attribute S2_mti_vect_attrib : integer;
    attribute S2_mti_vect_attrib of S2 : constant is 16;
    attribute S20_mti_vect_attrib : integer;
    attribute S20_mti_vect_attrib of S20 : constant is 32;
    attribute S3_mti_vect_attrib : integer;
    attribute S3_mti_vect_attrib of S3 : constant is 64;
    attribute S30_mti_vect_attrib : integer;
    attribute S30_mti_vect_attrib of S30 : constant is 128;
    attribute S4_mti_vect_attrib : integer;
    attribute S4_mti_vect_attrib of S4 : constant is 256;
    attribute S40_mti_vect_attrib : integer;
    attribute S40_mti_vect_attrib of S40 : constant is 512;
    attribute S5_mti_vect_attrib : integer;
    attribute S5_mti_vect_attrib of S5 : constant is 1024;
    attribute S50_mti_vect_attrib : integer;
    attribute S50_mti_vect_attrib of S50 : constant is 2048;
    attribute S6_mti_vect_attrib : integer;
    attribute S6_mti_vect_attrib of S6 : constant is 4096;
    attribute S60_mti_vect_attrib : integer;
    attribute S60_mti_vect_attrib of S60 : constant is 8192;
end bri_state;
