library verilog;
use verilog.vl_types.all;
entity add_reg_8 is
    port(
        datathree_0_a2  : in     vl_logic_vector(1 downto 1);
        un1_ten_choice_one_0_2_0: in     vl_logic;
        un1_ten_choice_one_0_2_5: in     vl_logic;
        un1_ten_choice_one_0_2_4: in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_5       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_7       : in     vl_logic;
        ADC_c_0_9       : in     vl_logic;
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_9         : in     vl_logic;
        ADC_c_2         : in     vl_logic;
        ADC_c_11        : in     vl_logic;
        ADC_c_5         : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        ADC_c_10        : in     vl_logic;
        addresult_5     : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_267           : in     vl_logic;
        ADD_32x32_fast_I131_Y_0_o2_3_N_21: out    vl_logic;
        N_264           : in     vl_logic;
        ADD_32x32_fast_I169_Y_0_o2_5_m12_i_a7_3_0: in     vl_logic;
        N_265           : in     vl_logic;
        ADD_32x32_fast_I131_Y_0_o2_3_m12_i_a7_3_0: out    vl_logic;
        ADD_32x32_fast_I169_Y_0_o2_5_N_21: in     vl_logic;
        N_267_0         : in     vl_logic
    );
end add_reg_8;
