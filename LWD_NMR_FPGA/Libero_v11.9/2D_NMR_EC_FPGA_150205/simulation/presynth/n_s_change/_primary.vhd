library verilog;
use verilog.vl_types.all;
entity n_s_change is
    port(
        n_s_ctrl        : in     vl_logic;
        adcdata         : in     vl_logic_vector(11 downto 0);
        n_adc           : out    vl_logic_vector(11 downto 0);
        s_adc           : out    vl_logic_vector(11 downto 0);
        dataout         : out    vl_logic_vector(15 downto 0);
        s_data          : in     vl_logic_vector(15 downto 0);
        n_data          : in     vl_logic_vector(15 downto 0);
        n_clk           : in     vl_logic;
        s_clk           : in     vl_logic;
        acq_clk         : out    vl_logic
    );
end n_s_change;
