library verilog;
use verilog.vl_types.all;
entity ten_choice_one is
    port(
        choice          : in     vl_logic_vector(3 downto 0);
        dataone         : out    vl_logic_vector(11 downto 0);
        datatwo         : out    vl_logic_vector(11 downto 0);
        datathree       : out    vl_logic_vector(11 downto 0);
        datafour        : out    vl_logic_vector(11 downto 0);
        datafive        : out    vl_logic_vector(11 downto 0);
        datasix         : out    vl_logic_vector(11 downto 0);
        dataseven       : out    vl_logic_vector(11 downto 0);
        dataeight       : out    vl_logic_vector(11 downto 0);
        datain          : in     vl_logic_vector(11 downto 0)
    );
end ten_choice_one;
