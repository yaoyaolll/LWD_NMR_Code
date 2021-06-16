library verilog;
use verilog.vl_types.all;
entity add_reg is
    port(
        dataseven_0_a2_1: in     vl_logic;
        dataseven_0_a2_6: in     vl_logic;
        dataseven_0_a2_0: in     vl_logic;
        ADC_c_3         : in     vl_logic;
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        ADC_c_8         : in     vl_logic;
        ADC_c_7         : in     vl_logic;
        ADC_c_5         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_5       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_7       : in     vl_logic;
        un1_ten_choice_one_0_6: in     vl_logic_vector(11 downto 10);
        addresult_8     : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_260           : in     vl_logic;
        N_272           : in     vl_logic;
        N_260_0         : in     vl_logic;
        ADD_32x32_fast_I131_Y_0_o2_3_m12_i_a7_3_0: in     vl_logic;
        ADD_32x32_fast_I131_Y_0_o2_3_N_21: in     vl_logic;
        N_265           : in     vl_logic;
        N_272_0         : in     vl_logic
    );
end add_reg;
