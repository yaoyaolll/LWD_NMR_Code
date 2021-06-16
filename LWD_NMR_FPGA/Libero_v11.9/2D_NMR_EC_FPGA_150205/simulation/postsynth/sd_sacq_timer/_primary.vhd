library verilog;
use verilog.vl_types.all;
entity sd_sacq_timer is
    port(
        count           : out    vl_logic_vector(21 downto 8);
        count_1         : out    vl_logic_vector(7 downto 5);
        count_4         : out    vl_logic_vector(4 downto 0);
        net_27          : in     vl_logic;
        ddsclkout_c     : in     vl_logic;
        sd_sacq_state_0_stateover: in     vl_logic;
        scalestate_0_s_acq: in     vl_logic
    );
end sd_sacq_timer;
