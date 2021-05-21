library verilog;
use verilog.vl_types.all;
entity sd_acq_top is
    port(
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        s_acq1          : in     vl_logic;
        clk_sys         : in     vl_logic;
        sd_sacq_load    : in     vl_logic;
        bb_ch           : in     vl_logic;
        s_acq180        : in     vl_logic;
        en              : out    vl_logic;
        long_opentime   : in     vl_logic;
        sd_sacq_choice  : in     vl_logic_vector(3 downto 0);
        sd_sacq_data    : in     vl_logic_vector(15 downto 0)
    );
end sd_acq_top;
