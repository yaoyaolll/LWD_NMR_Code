library verilog;
use verilog.vl_types.all;
entity Signal_Noise_Acq is
    port(
        dataout_0       : out    vl_logic_vector(15 downto 0);
        n_divnum        : in     vl_logic_vector(9 downto 0);
        n_acqnum        : in     vl_logic_vector(11 downto 0);
        s_addchoice     : in     vl_logic_vector(4 downto 0);
        s_acqnum        : in     vl_logic_vector(15 downto 0);
        s_periodnum     : in     vl_logic_vector(3 downto 0);
        s_stripnum      : in     vl_logic_vector(11 downto 0);
        ADC_c           : in     vl_logic_vector(11 downto 0);
        Signal_Noise_Acq_0_acq_clk: out    vl_logic;
        XRD_c           : in     vl_logic;
        n_acq_change_0_n_rst_n_0: in     vl_logic;
        top_code_0_n_rd_en: in     vl_logic;
        n_acq_change_0_n_rst_n: in     vl_logic;
        top_code_0_n_load: in     vl_logic;
        n_acq_change_0_n_acq_start: in     vl_logic;
        Signal_Noise_Acq_VCC: in     vl_logic;
        Signal_Noise_Acq_GND: in     vl_logic;
        top_code_0_RAM_Rd_rst: in     vl_logic;
        s_acq_change_0_s_rst: in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        scan_scale_sw_0_s_start: in     vl_logic;
        s_acq_change_0_s_load_0: in     vl_logic;
        s_acq_change_0_s_load: in     vl_logic;
        GLA             : in     vl_logic;
        top_code_0_n_s_ctrl: in     vl_logic;
        top_code_0_n_s_ctrl_1: in     vl_logic;
        top_code_0_n_s_ctrl_0: in     vl_logic
    );
end Signal_Noise_Acq;
