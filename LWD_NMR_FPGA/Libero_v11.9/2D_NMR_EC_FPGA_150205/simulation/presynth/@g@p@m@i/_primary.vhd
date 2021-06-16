library verilog;
use verilog.vl_types.all;
entity GPMI is
    port(
        dsp_reset       : in     vl_logic;
        rst_nr2         : out    vl_logic;
        clk             : in     vl_logic;
        xwe             : in     vl_logic;
        xzcs2           : in     vl_logic;
        tri_ctrl        : in     vl_logic;
        code_en         : out    vl_logic;
        xd              : inout  vl_logic_vector(15 downto 0);
        datain          : in     vl_logic_vector(15 downto 0);
        dataout         : out    vl_logic_vector(15 downto 0)
    );
end GPMI;
