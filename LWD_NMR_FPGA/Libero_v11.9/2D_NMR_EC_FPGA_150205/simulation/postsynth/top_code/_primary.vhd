library verilog;
use verilog.vl_types.all;
entity top_code is
    port(
        plusedata       : out    vl_logic_vector(15 downto 0);
        s_acqnum_0      : out    vl_logic_vector(15 downto 0);
        s_addchoice     : out    vl_logic_vector(4 downto 0);
        s_periodnum     : out    vl_logic_vector(3 downto 0);
        scalechoice     : out    vl_logic_vector(4 downto 0);
        scaledatain     : out    vl_logic_vector(15 downto 0);
        scaleddsdiv     : out    vl_logic_vector(5 downto 0);
        scandata        : out    vl_logic_vector(15 downto 0);
        sd_sacq_choice  : out    vl_logic_vector(3 downto 0);
        sd_sacq_data    : out    vl_logic_vector(15 downto 0);
        sigtimedata     : out    vl_logic_vector(15 downto 0);
        state_1ms_data  : out    vl_logic_vector(15 downto 0);
        state_1ms_lc    : out    vl_logic_vector(3 downto 0);
        bri_datain      : out    vl_logic_vector(15 downto 0);
        cal_data        : out    vl_logic_vector(5 downto 0);
        change          : out    vl_logic_vector(1 downto 0);
        dds_configdata  : out    vl_logic_vector(15 downto 0);
        dump_cho        : out    vl_logic_vector(2 downto 0);
        dumpdata        : out    vl_logic_vector(11 downto 0);
        halfdata        : out    vl_logic_vector(7 downto 0);
        n_acqnum        : out    vl_logic_vector(11 downto 0);
        n_divnum        : out    vl_logic_vector(9 downto 0);
        noisedata       : out    vl_logic_vector(15 downto 0);
        pd_pluse_choice : out    vl_logic_vector(3 downto 0);
        pd_pluse_data   : out    vl_logic_vector(15 downto 0);
        un1_GPMI_0_1    : in     vl_logic_vector(15 downto 0);
        relayclose_on_c : out    vl_logic_vector(15 downto 0);
        xa_c_0_0        : in     vl_logic;
        xa_c_0_7        : in     vl_logic;
        xa_c            : in     vl_logic_vector(18 downto 0);
        un1_GPMI_0_1_0  : in     vl_logic_vector(2 downto 0);
        un1_top_code_0_3_0: out    vl_logic_vector(1 downto 0);
        net_33          : out    vl_logic;
        top_code_0_noise_rst: out    vl_logic;
        top_code_0_bridge_load: out    vl_logic;
        top_code_0_scale_start: out    vl_logic;
        top_code_0_pn_change: out    vl_logic;
        top_code_0_scanload: out    vl_logic;
        top_code_0_acqclken: out    vl_logic;
        top_code_0_state_1ms_rst_n: out    vl_logic;
        top_code_0_scaleload: out    vl_logic;
        top_code_0_scan_start: out    vl_logic;
        top_code_0_n_load: out    vl_logic;
        top_code_0_n_rd_en: out    vl_logic;
        top_code_0_n_s_ctrl: out    vl_logic;
        top_code_0_RAM_Rd_rst: out    vl_logic;
        top_code_0_noise_start: out    vl_logic;
        top_code_0_dds_choice: out    vl_logic;
        top_code_0_dumpload: out    vl_logic;
        top_code_0_pluseload: out    vl_logic;
        top_code_0_scanchoice: out    vl_logic;
        top_code_0_pluse_scale: out    vl_logic;
        top_code_0_state_1ms_load: out    vl_logic;
        top_code_0_sd_sacq_load: out    vl_logic;
        top_code_0_pd_pluse_load: out    vl_logic;
        top_code_0_nstateload: out    vl_logic;
        top_code_0_pluse_lc: out    vl_logic;
        top_code_0_sigrst: out    vl_logic;
        top_code_0_s_load: out    vl_logic;
        top_code_0_cal_load: out    vl_logic;
        top_code_0_nstatechoice: out    vl_logic;
        top_code_0_pluse_noise_ctrl: out    vl_logic;
        top_code_0_dump_sustain: out    vl_logic;
        k1_c            : out    vl_logic;
        k2_c            : out    vl_logic;
        top_code_0_pluse_rst: out    vl_logic;
        top_code_0_pluse_str: out    vl_logic;
        top_code_0_state_1ms_start: out    vl_logic;
        GPMI_0_code_en  : in     vl_logic;
        top_code_0_scale_rst: out    vl_logic;
        top_code_0_dds_load: out    vl_logic;
        top_code_0_n_s_ctrl_0: out    vl_logic;
        top_code_0_n_s_ctrl_1: out    vl_logic;
        top_code_0_state_1ms_rst_n_0: out    vl_logic;
        net_27          : in     vl_logic;
        top_code_0_bridge_load_0: out    vl_logic;
        net_33_0        : out    vl_logic;
        top_code_0_pluse_rst_0: out    vl_logic;
        GLA             : in     vl_logic;
        top_code_0_noise_rst_0: out    vl_logic
    );
end top_code;
