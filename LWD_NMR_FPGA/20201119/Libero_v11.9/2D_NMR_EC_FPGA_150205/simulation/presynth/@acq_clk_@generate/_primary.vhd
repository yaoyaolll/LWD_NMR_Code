library verilog;
use verilog.vl_types.all;
entity Acq_clk_Generate is
    port(
        clk_sys         : in     vl_logic;
        n_en            : in     vl_logic;
        n_reset         : in     vl_logic;
        n_load          : in     vl_logic;
        s_reset         : in     vl_logic;
        s_acq           : in     vl_logic;
        ddsclkout       : in     vl_logic;
        s_load          : in     vl_logic;
        n_s_ctrl        : in     vl_logic;
        Acq_clk         : out    vl_logic;
        n_divnum        : in     vl_logic_vector(9 downto 0);
        stripnum        : in     vl_logic_vector(11 downto 0);
        acqnum          : in     vl_logic_vector(15 downto 0);
        periodnum       : in     vl_logic_vector(3 downto 0);
        n_acqnum        : in     vl_logic_vector(11 downto 0);
        Acq_en          : in     vl_logic
    );
end Acq_clk_Generate;
