library verilog;
use verilog.vl_types.all;
entity sd_sacq_coder is
    port(
        clk_sys         : in     vl_logic;
        dds             : in     vl_logic;
        rst_n           : in     vl_logic;
        count           : in     vl_logic_vector(21 downto 0);
        sd_sacq_load    : in     vl_logic;
        sd_sacq_choice  : in     vl_logic_vector(3 downto 0);
        sd_sacq_data    : in     vl_logic_vector(15 downto 0);
        state_start     : in     vl_logic;
        i               : out    vl_logic_vector(10 downto 0);
        bb_ch           : in     vl_logic;
        s_acq180        : in     vl_logic;
        long_opentime   : in     vl_logic
    );
end sd_sacq_coder;
