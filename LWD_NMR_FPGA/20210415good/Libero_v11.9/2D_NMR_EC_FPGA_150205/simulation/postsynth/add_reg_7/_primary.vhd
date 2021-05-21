library verilog;
use verilog.vl_types.all;
entity add_reg_7 is
    port(
        addrout         : in     vl_logic_vector(3 downto 2);
        datanine_0_a2_0 : in     vl_logic;
        datanine_0_a2_2 : in     vl_logic;
        ADC_c_5         : in     vl_logic;
        ADC_c_2         : in     vl_logic;
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_8         : in     vl_logic;
        ADC_c_9         : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        ADC_c_3         : in     vl_logic;
        ADC_c_7         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        un1_ten_choice_one_0_8_3: in     vl_logic;
        un1_ten_choice_one_0_8_0: in     vl_logic;
        un1_ten_choice_one_0_8_4: in     vl_logic;
        addresult_0     : out    vl_logic_vector(31 downto 0);
        ADC_c_0_9       : in     vl_logic;
        ADC_c_0_5       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_7       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        ADD_32x32_fast_I222_Y_0_0_o2_3_m18_i_a7_1: out    vl_logic;
        N_261           : in     vl_logic;
        N_271           : in     vl_logic;
        N_263_i         : in     vl_logic
    );
end add_reg_7;
