library verilog;
use verilog.vl_types.all;
entity DDS is
    port(
        dds_configdata  : in     vl_logic_vector(15 downto 0);
        top_code_0_dds_load: in     vl_logic;
        top_code_0_dds_choice: in     vl_logic;
        ddswclk_c       : out    vl_logic;
        ddsfqud_c       : out    vl_logic;
        ddsdata_c       : out    vl_logic;
        ddsreset_c      : out    vl_logic;
        dds_change_0_dds_conf: in     vl_logic;
        dds_change_0_dds_rst: in     vl_logic;
        GLA             : in     vl_logic
    );
end DDS;
