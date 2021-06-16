library verilog;
use verilog.vl_types.all;
entity plusestate is
    generic(
        IDLE            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        INIT            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        INIT2           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        CONFIG          : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        START           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        PLUSE           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        DUMP            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        STOP            : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        INI_TEST        : vl_logic_vector(9 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        START_test      : vl_logic_vector(9 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        clken_p         : in     vl_logic;
        rst_n           : in     vl_logic;
        soft_d          : out    vl_logic;
        rt_sw           : out    vl_logic;
        sw_acq1         : out    vl_logic;
        sw_acq2         : out    vl_logic;
        timecount       : out    vl_logic_vector(19 downto 0);
        pluse_acq       : out    vl_logic;
        pluse_start     : out    vl_logic;
        off_test        : out    vl_logic;
        datain          : in     vl_logic_vector(15 downto 0);
        load            : in     vl_logic;
        loadchoice      : in     vl_logic;
        dump_start      : out    vl_logic;
        state_over_n    : out    vl_logic;
        dds_config      : out    vl_logic;
        dumpoff_ctr     : out    vl_logic;
        tetw_pluse      : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 1;
    attribute INIT_mti_vect_attrib : integer;
    attribute INIT_mti_vect_attrib of INIT : constant is 2;
    attribute INIT2_mti_vect_attrib : integer;
    attribute INIT2_mti_vect_attrib of INIT2 : constant is 4;
    attribute CONFIG_mti_vect_attrib : integer;
    attribute CONFIG_mti_vect_attrib of CONFIG : constant is 8;
    attribute START_mti_vect_attrib : integer;
    attribute START_mti_vect_attrib of START : constant is 16;
    attribute PLUSE_mti_vect_attrib : integer;
    attribute PLUSE_mti_vect_attrib of PLUSE : constant is 32;
    attribute DUMP_mti_vect_attrib : integer;
    attribute DUMP_mti_vect_attrib of DUMP : constant is 64;
    attribute STOP_mti_vect_attrib : integer;
    attribute STOP_mti_vect_attrib of STOP : constant is 128;
    attribute INI_TEST_mti_vect_attrib : integer;
    attribute INI_TEST_mti_vect_attrib of INI_TEST : constant is 256;
    attribute START_test_mti_vect_attrib : integer;
    attribute START_test_mti_vect_attrib of START_test : constant is 512;
end plusestate;
