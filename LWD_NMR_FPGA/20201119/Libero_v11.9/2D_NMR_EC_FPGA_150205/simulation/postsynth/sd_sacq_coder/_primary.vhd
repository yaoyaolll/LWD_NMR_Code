library verilog;
use verilog.vl_types.all;
entity sd_sacq_coder is
    port(
        i               : out    vl_logic_vector(10 downto 4);
        i_3             : out    vl_logic_vector(3 downto 2);
        i_0_0_0         : in     vl_logic;
        i_4             : out    vl_logic_vector(1 downto 0);
        sd_sacq_data    : in     vl_logic_vector(15 downto 0);
        sd_sacq_choice  : in     vl_logic_vector(3 downto 0);
        count_4         : in     vl_logic_vector(4 downto 0);
        count_1         : in     vl_logic_vector(7 downto 5);
        count           : in     vl_logic_vector(21 downto 8);
        ddsclkout_c     : in     vl_logic;
        GLA             : in     vl_logic;
        scalestate_0_long_opentime: in     vl_logic;
        s_acq180_c      : in     vl_logic;
        top_code_0_sd_sacq_load: in     vl_logic;
        scalestate_0_s_acq: in     vl_logic;
        net_27          : in     vl_logic
    );
end sd_sacq_coder;
