library verilog;
use verilog.vl_types.all;
entity RAM is
    port(
        un1_n_s_change_0: in     vl_logic_vector(11 downto 0);
        addr_0          : in     vl_logic_vector(11 downto 0);
        addr            : in     vl_logic_vector(11 downto 0);
        MX2_RD_8_inst   : out    vl_logic;
        MX2_RD_10_inst  : out    vl_logic;
        MX2_RD_3_inst   : out    vl_logic;
        MX2_RD_9_inst   : out    vl_logic;
        MX2_RD_1_inst   : out    vl_logic;
        top_code_0_n_rd_en: in     vl_logic;
        MX2_RD_11_inst  : out    vl_logic;
        MX2_RD_6_inst   : out    vl_logic;
        MX2_RD_7_inst   : out    vl_logic;
        n_acq_change_0_n_acq_start: in     vl_logic;
        MX2_RD_5_inst   : out    vl_logic;
        MX2_RD_4_inst   : out    vl_logic;
        s_clk_div4_0_clkout: in     vl_logic;
        RAM_VCC         : in     vl_logic;
        n_acq_change_0_n_rst_n_0: in     vl_logic;
        n_rdclk         : in     vl_logic;
        RAM_GND         : in     vl_logic;
        MX2_RD_2_inst   : out    vl_logic;
        MX2_RD_0_inst   : out    vl_logic
    );
end RAM;
