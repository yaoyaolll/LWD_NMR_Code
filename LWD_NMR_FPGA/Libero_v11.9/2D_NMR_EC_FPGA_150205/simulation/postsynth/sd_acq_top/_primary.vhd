library verilog;
use verilog.vl_types.all;
entity sd_acq_top is
    port(
        sd_sacq_choice  : in     vl_logic_vector(3 downto 0);
        sd_sacq_data    : in     vl_logic_vector(15 downto 0);
        i_4_1           : out    vl_logic;
        i_0_0           : in     vl_logic_vector(1 downto 1);
        sd_acq_en_c     : out    vl_logic;
        net_27          : in     vl_logic;
        scalestate_0_s_acq: in     vl_logic;
        top_code_0_sd_sacq_load: in     vl_logic;
        s_acq180_c      : in     vl_logic;
        scalestate_0_long_opentime: in     vl_logic;
        GLA             : in     vl_logic;
        ddsclkout_c     : in     vl_logic
    );
end sd_acq_top;
