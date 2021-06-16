library verilog;
use verilog.vl_types.all;
entity dds_coder is
    generic(
        rst_para1       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0);
        rst_para2       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi1, Hi1, Hi0);
        over_para       : vl_logic_vector(7 downto 0) := (Hi0, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        count           : in     vl_logic_vector(7 downto 0);
        i               : out    vl_logic_vector(3 downto 0)
    );
    attribute rst_para1_mti_vect_attrib : integer;
    attribute rst_para1_mti_vect_attrib of rst_para1 : constant is 10;
    attribute rst_para2_mti_vect_attrib : integer;
    attribute rst_para2_mti_vect_attrib of rst_para2 : constant is 14;
    attribute over_para_mti_vect_attrib : integer;
    attribute over_para_mti_vect_attrib of over_para : constant is 96;
end dds_coder;
