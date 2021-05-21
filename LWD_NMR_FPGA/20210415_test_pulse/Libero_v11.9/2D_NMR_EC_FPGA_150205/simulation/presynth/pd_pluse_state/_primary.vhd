library verilog;
use verilog.vl_types.all;
entity pd_pluse_state is
    generic(
        IDLE            : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        S1              : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        S2              : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        S3              : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        S4              : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        S20             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        S21             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S22             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S50             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S51             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S52             : vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S53             : vl_logic_vector(12 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        S10             : vl_logic_vector(12 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        i               : in     vl_logic_vector(5 downto 0);
        en              : out    vl_logic;
        stateover       : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 1;
    attribute S1_mti_vect_attrib : integer;
    attribute S1_mti_vect_attrib of S1 : constant is 2;
    attribute S2_mti_vect_attrib : integer;
    attribute S2_mti_vect_attrib of S2 : constant is 4;
    attribute S3_mti_vect_attrib : integer;
    attribute S3_mti_vect_attrib of S3 : constant is 8;
    attribute S4_mti_vect_attrib : integer;
    attribute S4_mti_vect_attrib of S4 : constant is 16;
    attribute S20_mti_vect_attrib : integer;
    attribute S20_mti_vect_attrib of S20 : constant is 32;
    attribute S21_mti_vect_attrib : integer;
    attribute S21_mti_vect_attrib of S21 : constant is 64;
    attribute S22_mti_vect_attrib : integer;
    attribute S22_mti_vect_attrib of S22 : constant is 128;
    attribute S50_mti_vect_attrib : integer;
    attribute S50_mti_vect_attrib of S50 : constant is 256;
    attribute S51_mti_vect_attrib : integer;
    attribute S51_mti_vect_attrib of S51 : constant is 512;
    attribute S52_mti_vect_attrib : integer;
    attribute S52_mti_vect_attrib of S52 : constant is 1024;
    attribute S53_mti_vect_attrib : integer;
    attribute S53_mti_vect_attrib of S53 : constant is 2048;
    attribute S10_mti_vect_attrib : integer;
    attribute S10_mti_vect_attrib of S10 : constant is 4096;
end pd_pluse_state;
