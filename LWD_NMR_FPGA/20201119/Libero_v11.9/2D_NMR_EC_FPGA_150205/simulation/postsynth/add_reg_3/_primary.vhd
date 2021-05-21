library verilog;
use verilog.vl_types.all;
entity add_reg_3 is
    port(
        ADC_c           : in     vl_logic_vector(8 downto 6);
        ADC_c_0_5       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_8       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        datasix_0_a2_0  : in     vl_logic_vector(7 downto 7);
        un1_ten_choice_one_0_5_0: in     vl_logic;
        un1_ten_choice_one_0_5_9: in     vl_logic;
        un1_ten_choice_one_0_5_7: in     vl_logic;
        addresult_2     : out    vl_logic_vector(31 downto 0);
        datasix_0_a2_0_d0: in     vl_logic;
        datasix_0_a2_4  : in     vl_logic;
        datasix_0_a2_3  : in     vl_logic;
        datasix_0_a2_1  : in     vl_logic;
        datasix_0_a2_5  : in     vl_logic;
        datasix_0_a2_6  : in     vl_logic;
        datasix_0_a2_10 : in     vl_logic;
        datasix_0_a2_8  : in     vl_logic;
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_275           : in     vl_logic;
        N_260           : in     vl_logic;
        ADD_32x32_fast_I169_Y_0_o2_5_m12_i_a7_3_0: out    vl_logic;
        N_262           : in     vl_logic;
        ADD_32x32_fast_I169_Y_0_o2_5_N_21: out    vl_logic;
        N_260_0         : in     vl_logic
    );
end add_reg_3;
