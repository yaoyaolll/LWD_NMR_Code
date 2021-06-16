library verilog;
use verilog.vl_types.all;
entity tri_state is
    port(
        tri_ctrl        : in     vl_logic;
        zcs2            : in     vl_logic;
        xd              : inout  vl_logic_vector(15 downto 0);
        dataout         : out    vl_logic_vector(15 downto 0);
        datain          : in     vl_logic_vector(15 downto 0)
    );
end tri_state;
