library verilog;
use verilog.vl_types.all;
entity add_reg_2 is
    port(
        datafive_0_a2   : in     vl_logic_vector(1 downto 1);
        ADC_c_5         : in     vl_logic;
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_11        : in     vl_logic;
        ADC_c_9         : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        ADC_c_7         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_2       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        un1_ten_choice_one_0_4_0: in     vl_logic;
        un1_ten_choice_one_0_4_1: in     vl_logic;
        un1_ten_choice_one_0_4_6: in     vl_logic;
        un1_ten_choice_one_0_4_8: in     vl_logic;
        addresult_3     : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_269           : in     vl_logic;
        N_260           : in     vl_logic;
        N_261           : in     vl_logic;
        ADD_32x32_fast_I222_Y_0_0_o2_3_m18_i_a7_1: in     vl_logic;
        N_269_0         : in     vl_logic
    );
end add_reg_2;
