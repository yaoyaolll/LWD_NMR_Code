library verilog;
use verilog.vl_types.all;
entity dds_state is
    port(
        i_2             : in     vl_logic_vector(3 downto 1);
        dds_configdata  : in     vl_logic_vector(15 downto 0);
        i_RNIV2B7       : in     vl_logic_vector(0 downto 0);
        ddsreset_c      : out    vl_logic;
        ddsdata_c       : out    vl_logic;
        ddsfqud_c       : out    vl_logic;
        ddswclk_c       : out    vl_logic;
        GLA             : in     vl_logic;
        dds_change_0_dds_rst: in     vl_logic;
        dds_state_0_state_over: out    vl_logic;
        top_code_0_dds_choice: in     vl_logic;
        top_code_0_dds_load: in     vl_logic
    );
end dds_state;
