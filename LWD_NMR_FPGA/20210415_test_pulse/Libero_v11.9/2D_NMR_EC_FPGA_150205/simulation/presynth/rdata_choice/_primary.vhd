library verilog;
use verilog.vl_types.all;
entity rdata_choice is
    port(
        dataone         : in     vl_logic_vector(19 downto 0);
        datatwo         : in     vl_logic_vector(19 downto 0);
        datathree       : in     vl_logic_vector(19 downto 0);
        datafour        : in     vl_logic_vector(19 downto 0);
        datafive        : in     vl_logic_vector(19 downto 0);
        datasix         : in     vl_logic_vector(19 downto 0);
        dataseven       : in     vl_logic_vector(19 downto 0);
        dataeight       : in     vl_logic_vector(19 downto 0);
        dataout         : out    vl_logic_vector(15 downto 0);
        choice          : in     vl_logic_vector(4 downto 0)
    );
end rdata_choice;
