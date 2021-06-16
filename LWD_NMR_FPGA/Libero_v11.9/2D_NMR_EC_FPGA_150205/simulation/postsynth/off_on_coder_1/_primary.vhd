library verilog;
use verilog.vl_types.all;
entity off_on_coder_1 is
    port(
        i_5             : out    vl_logic_vector(1 downto 1);
        i_6             : out    vl_logic_vector(0 downto 0);
        count_6         : in     vl_logic_vector(4 downto 0);
        GLA             : in     vl_logic;
        OR2_1_Y         : in     vl_logic;
        OR2_2_Y         : in     vl_logic
    );
end off_on_coder_1;
