library verilog;
use verilog.vl_types.all;
entity scanstate is
    generic(
        IDLE            : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        INIT            : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        S_SOFTDUMP      : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        S_DECOPEN       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        S_SWICHOPEN     : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        S_ACQUITION     : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        CUT_DECO        : vl_logic_vector(7 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        STOP            : vl_logic_vector(7 downto 0) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        clken_p         : in     vl_logic;
        rst_n           : in     vl_logic;
        dumpon_ctr      : out    vl_logic;
        dumpoff_ctr     : out    vl_logic;
        soft_d          : out    vl_logic;
        rt_sw           : out    vl_logic;
        sw_acq1         : out    vl_logic;
        sw_acq2         : out    vl_logic;
        timecount       : out    vl_logic_vector(19 downto 0);
        s_acq           : out    vl_logic;
        dds_conf        : out    vl_logic;
        calctrl         : out    vl_logic;
        state_over_n    : out    vl_logic;
        scanload        : in     vl_logic;
        datain          : in     vl_logic_vector(15 downto 0);
        scanchoice      : in     vl_logic;
        resetout        : out    vl_logic
    );
    attribute IDLE_mti_vect_attrib : integer;
    attribute IDLE_mti_vect_attrib of IDLE : constant is 1;
    attribute INIT_mti_vect_attrib : integer;
    attribute INIT_mti_vect_attrib of INIT : constant is 2;
    attribute S_SOFTDUMP_mti_vect_attrib : integer;
    attribute S_SOFTDUMP_mti_vect_attrib of S_SOFTDUMP : constant is 4;
    attribute S_DECOPEN_mti_vect_attrib : integer;
    attribute S_DECOPEN_mti_vect_attrib of S_DECOPEN : constant is 8;
    attribute S_SWICHOPEN_mti_vect_attrib : integer;
    attribute S_SWICHOPEN_mti_vect_attrib of S_SWICHOPEN : constant is 16;
    attribute S_ACQUITION_mti_vect_attrib : integer;
    attribute S_ACQUITION_mti_vect_attrib of S_ACQUITION : constant is 32;
    attribute CUT_DECO_mti_vect_attrib : integer;
    attribute CUT_DECO_mti_vect_attrib of CUT_DECO : constant is 64;
    attribute STOP_mti_vect_attrib : integer;
    attribute STOP_mti_vect_attrib of STOP : constant is 128;
end scanstate;
