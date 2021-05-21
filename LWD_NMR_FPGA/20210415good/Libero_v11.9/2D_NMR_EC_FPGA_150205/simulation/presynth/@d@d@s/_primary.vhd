library verilog;
use verilog.vl_types.all;
entity DDS is
    port(
        dds_load        : in     vl_logic;
        dds_choice      : in     vl_logic;
        clk_sys         : in     vl_logic;
        rst_n           : in     vl_logic;
        state_start     : in     vl_logic;
        reset           : out    vl_logic;
        fq_ud           : out    vl_logic;
        w_clk           : out    vl_logic;
        data            : out    vl_logic;
        dds_para        : in     vl_logic_vector(15 downto 0)
    );
end DDS;
