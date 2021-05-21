library verilog;
use verilog.vl_types.all;
entity add_reg_1 is
    port(
        addrout         : in     vl_logic_vector(1 downto 0);
        ADC_c_0_d0      : in     vl_logic;
        ADC_c_5         : in     vl_logic;
        ADC_c_3         : in     vl_logic;
        ADC_c_4         : in     vl_logic;
        datafour_0_a2_9 : in     vl_logic;
        datafour_0_a2_2 : in     vl_logic;
        datafour_0_a2_1 : in     vl_logic;
        datafour_0_a2_6 : in     vl_logic;
        datafour_0_a2_8 : in     vl_logic;
        datafour_0_a2_0 : in     vl_logic;
        datafour_0_a2_5 : in     vl_logic;
        datafour_0_a2_7 : in     vl_logic;
        ADC_c_0_0       : in     vl_logic;
        ADC_c_0_1       : in     vl_logic;
        ADC_c_0_6       : in     vl_logic;
        ADC_c_0_3       : in     vl_logic;
        un1_ten_choice_one_0_3: in     vl_logic_vector(11 downto 11);
        addresult_4     : out    vl_logic_vector(31 downto 0);
        reset_c         : in     vl_logic;
        AND2_2_Y        : in     vl_logic;
        N_260           : in     vl_logic;
        N_260_0         : in     vl_logic;
        N_266           : in     vl_logic;
        N_276           : in     vl_logic
    );
end add_reg_1;
