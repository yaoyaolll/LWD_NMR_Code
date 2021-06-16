library verilog;
use verilog.vl_types.all;
entity add_reg_9 is
    port(
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_9         : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        ADC_c_3         : in     vl_logic;
        ADC_c_7         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_7       : in     vl_logic;
        un1_ten_choice_one_0_7: in     vl_logic_vector(11 downto 10);
        dataeight_0_a2_1: in     vl_logic;
        dataeight_0_a2_0: in     vl_logic;
        dataeight_0_a2_7: in     vl_logic;
        dataeight_0_a2_4: in     vl_logic;
        dataeight_0_a2_6: in     vl_logic;
        dataeight_0_a2_5: in     vl_logic;
        addresult_1     : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_273           : in     vl_logic;
        d_m5_e_0        : out    vl_logic;
        d_m5_e_1        : out    vl_logic;
        d_m5_e_2_0      : in     vl_logic;
        N_273_0         : in     vl_logic
    );
end add_reg_9;
