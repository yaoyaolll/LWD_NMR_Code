library verilog;
use verilog.vl_types.all;
entity dds_state is
    generic(
        PHASE_PARA      : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        IDLE            : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        RST1            : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        RST2            : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        MODE_SEL1       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        MODE_SEL2       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        PARA_LOAD1      : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        PARA_LOAD2      : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        UPDATE          : vl_logic_vector(7 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        OVER            : vl_logic_vector(7 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        dds_load        : in     vl_logic;
        dds_choice      : in     vl_logic;
        i               : in     vl_logic_vector(3 downto 0);
        dds_para        : in     vl_logic_vector(15 downto 0);
        reset           : out    vl_logic;
        w_clk           : out    vl_logic;
        fq_ud           : out    vl_logic;
        data            : out    vl_logic;
        state_over      : out    vl_logic
    );
    attribute PHASE_PARA_mti_vect_attrib : integer;
    attribute PHASE_PARA_mti_vect_attrib of PHASE_PARA : constant is 0;
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 0;
    attribute RST1_mti_vect_attrib : integer;
    attribute RST1_mti_vect_attrib of RST1 : constant is 1;
    attribute RST2_mti_vect_attrib : integer;
    attribute RST2_mti_vect_attrib of RST2 : constant is 2;
    attribute MODE_SEL1_mti_vect_attrib : integer;
    attribute MODE_SEL1_mti_vect_attrib of MODE_SEL1 : constant is 4;
    attribute MODE_SEL2_mti_vect_attrib : integer;
    attribute MODE_SEL2_mti_vect_attrib of MODE_SEL2 : constant is 8;
    attribute PARA_LOAD1_mti_vect_attrib : integer;
    attribute PARA_LOAD1_mti_vect_attrib of PARA_LOAD1 : constant is 16;
    attribute PARA_LOAD2_mti_vect_attrib : integer;
    attribute PARA_LOAD2_mti_vect_attrib of PARA_LOAD2 : constant is 32;
    attribute UPDATE_mti_vect_attrib : integer;
    attribute UPDATE_mti_vect_attrib of UPDATE : constant is 64;
    attribute OVER_mti_vect_attrib : integer;
    attribute OVER_mti_vect_attrib of OVER : constant is 128;
end dds_state;
