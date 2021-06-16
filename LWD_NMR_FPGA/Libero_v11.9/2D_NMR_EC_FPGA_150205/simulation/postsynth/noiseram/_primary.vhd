library verilog;
use verilog.vl_types.all;
entity noiseram is
    port(
        w_data_c        : in     vl_logic_vector(11 downto 0);
        addr_c          : in     vl_logic_vector(7 downto 0);
        addr_rd_c       : in     vl_logic_vector(7 downto 0);
        dataout_c       : out    vl_logic_vector(11 downto 0);
        RESET_c         : in     vl_logic;
        r_en_c          : in     vl_logic;
        wclkout         : in     vl_logic;
        noiseram_VCC    : in     vl_logic;
        AND2_1_Y        : in     vl_logic;
        noiseram_GND    : in     vl_logic;
        n_en_c          : in     vl_logic
    );
end noiseram;
