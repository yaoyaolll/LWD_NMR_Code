library verilog;
use verilog.vl_types.all;
entity sd_sacq_state is
    port(
        i_3             : in     vl_logic_vector(3 downto 2);
        i_4             : in     vl_logic_vector(1 downto 0);
        i               : in     vl_logic_vector(10 downto 4);
        ddsclkout_c     : in     vl_logic;
        sd_acq_en_c     : out    vl_logic;
        sd_sacq_state_0_stateover: out    vl_logic;
        net_27          : in     vl_logic
    );
end sd_sacq_state;
