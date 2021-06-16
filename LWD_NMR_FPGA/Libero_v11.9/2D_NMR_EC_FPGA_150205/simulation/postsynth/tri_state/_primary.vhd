library verilog;
use verilog.vl_types.all;
entity tri_state is
    port(
        zcs2_c          : in     vl_logic;
        tri_ctrl_c      : in     vl_logic;
        xd_1            : out    vl_logic
    );
end tri_state;
