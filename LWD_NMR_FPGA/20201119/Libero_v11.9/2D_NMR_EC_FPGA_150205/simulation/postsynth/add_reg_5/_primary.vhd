library verilog;
use verilog.vl_types.all;
entity add_reg_5 is
    port(
        ADC_c_3         : in     vl_logic;
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_5         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        ADC_c_6         : in     vl_logic;
        dataten_0_a2_0  : in     vl_logic;
        dataten_0_a2_1  : in     vl_logic;
        dataten_0_a2_3  : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_5       : in     vl_logic;
        ADC_c_0_4       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        ADC_c_0_7       : in     vl_logic;
        un1_ten_choice_one_0_9_0: in     vl_logic;
        un1_ten_choice_one_0_9_4: in     vl_logic;
        un1_ten_choice_one_0_9_7: in     vl_logic;
        un1_ten_choice_one_0_9_6: in     vl_logic;
        addresult       : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_262           : in     vl_logic;
        ADD_32x32_fast_I169_Y_0_o2_5_m12_i_a7_3_0: in     vl_logic;
        N_268           : in     vl_logic;
        N_263_i         : in     vl_logic
    );
end add_reg_5;
