`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module RAM(WD,RD,WEN,REN,WADDR,RADDR,WCLK,RCLK,RESET);
input [11:0] WD;
output [11:0] RD;
input  WEN, REN;
input [11:0] WADDR, RADDR;
input WCLK, RCLK, RESET;

    wire WEAP, WEBP, ADDRA_FF2_0_net, ADDRA_FF2_1_net, 
        ADDRA_FF2_2_net, ADDRA_FF2_3_net, ADDRB_FF2_0_net, 
        ADDRB_FF2_1_net, ADDRB_FF2_2_net, ADDRB_FF2_3_net, 
        ENABLE_ADDRA_0_net, ENABLE_ADDRA_1_net, 
        ENABLE_ADDRA_2_net, ENABLE_ADDRA_3_net, 
        ENABLE_ADDRA_4_net, ENABLE_ADDRA_5_net, 
        ENABLE_ADDRA_6_net, ENABLE_ADDRA_7_net, 
        ENABLE_ADDRA_8_net, ENABLE_ADDRA_9_net, 
        ENABLE_ADDRA_10_net, ENABLE_ADDRA_11_net, 
        ENABLE_ADDRA_12_net, ENABLE_ADDRA_13_net, 
        ENABLE_ADDRA_14_net, ENABLE_ADDRA_15_net, 
        ENABLE_ADDRB_0_net, ENABLE_ADDRB_1_net, 
        ENABLE_ADDRB_2_net, ENABLE_ADDRB_3_net, 
        ENABLE_ADDRB_4_net, ENABLE_ADDRB_5_net, 
        ENABLE_ADDRB_6_net, ENABLE_ADDRB_7_net, 
        ENABLE_ADDRB_8_net, ENABLE_ADDRB_9_net, 
        ENABLE_ADDRB_10_net, ENABLE_ADDRB_11_net, 
        ENABLE_ADDRB_12_net, ENABLE_ADDRB_13_net, 
        ENABLE_ADDRB_14_net, ENABLE_ADDRB_15_net, BLKA_EN_0_net, 
        BLKB_EN_0_net, BLKA_EN_1_net, BLKB_EN_1_net, 
        BLKA_EN_2_net, BLKB_EN_2_net, BLKA_EN_3_net, 
        BLKB_EN_3_net, BLKA_EN_4_net, BLKB_EN_4_net, 
        BLKA_EN_5_net, BLKB_EN_5_net, BLKA_EN_6_net, 
        BLKB_EN_6_net, BLKA_EN_7_net, BLKB_EN_7_net, 
        BLKA_EN_8_net, BLKB_EN_8_net, BLKA_EN_9_net, 
        BLKB_EN_9_net, BLKA_EN_10_net, BLKB_EN_10_net, 
        BLKA_EN_11_net, BLKB_EN_11_net, BLKA_EN_12_net, 
        BLKB_EN_12_net, BLKA_EN_13_net, BLKB_EN_13_net, 
        BLKA_EN_14_net, BLKB_EN_14_net, BLKA_EN_15_net, 
        BLKB_EN_15_net, QX_TEMPR0_0_net, QX_TEMPR0_1_net, 
        QX_TEMPR0_2_net, QX_TEMPR0_3_net, QX_TEMPR0_4_net, 
        QX_TEMPR0_5_net, QX_TEMPR0_6_net, QX_TEMPR0_7_net, 
        QX_TEMPR0_8_net, QX_TEMPR0_9_net, QX_TEMPR0_10_net, 
        QX_TEMPR0_11_net, QX_TEMPR1_0_net, QX_TEMPR1_1_net, 
        QX_TEMPR1_2_net, QX_TEMPR1_3_net, QX_TEMPR1_4_net, 
        QX_TEMPR1_5_net, QX_TEMPR1_6_net, QX_TEMPR1_7_net, 
        QX_TEMPR1_8_net, QX_TEMPR1_9_net, QX_TEMPR1_10_net, 
        QX_TEMPR1_11_net, QX_TEMPR2_0_net, QX_TEMPR2_1_net, 
        QX_TEMPR2_2_net, QX_TEMPR2_3_net, QX_TEMPR2_4_net, 
        QX_TEMPR2_5_net, QX_TEMPR2_6_net, QX_TEMPR2_7_net, 
        QX_TEMPR2_8_net, QX_TEMPR2_9_net, QX_TEMPR2_10_net, 
        QX_TEMPR2_11_net, QX_TEMPR3_0_net, QX_TEMPR3_1_net, 
        QX_TEMPR3_2_net, QX_TEMPR3_3_net, QX_TEMPR3_4_net, 
        QX_TEMPR3_5_net, QX_TEMPR3_6_net, QX_TEMPR3_7_net, 
        QX_TEMPR3_8_net, QX_TEMPR3_9_net, QX_TEMPR3_10_net, 
        QX_TEMPR3_11_net, QX_TEMPR4_0_net, QX_TEMPR4_1_net, 
        QX_TEMPR4_2_net, QX_TEMPR4_3_net, QX_TEMPR4_4_net, 
        QX_TEMPR4_5_net, QX_TEMPR4_6_net, QX_TEMPR4_7_net, 
        QX_TEMPR4_8_net, QX_TEMPR4_9_net, QX_TEMPR4_10_net, 
        QX_TEMPR4_11_net, QX_TEMPR5_0_net, QX_TEMPR5_1_net, 
        QX_TEMPR5_2_net, QX_TEMPR5_3_net, QX_TEMPR5_4_net, 
        QX_TEMPR5_5_net, QX_TEMPR5_6_net, QX_TEMPR5_7_net, 
        QX_TEMPR5_8_net, QX_TEMPR5_9_net, QX_TEMPR5_10_net, 
        QX_TEMPR5_11_net, QX_TEMPR6_0_net, QX_TEMPR6_1_net, 
        QX_TEMPR6_2_net, QX_TEMPR6_3_net, QX_TEMPR6_4_net, 
        QX_TEMPR6_5_net, QX_TEMPR6_6_net, QX_TEMPR6_7_net, 
        QX_TEMPR6_8_net, QX_TEMPR6_9_net, QX_TEMPR6_10_net, 
        QX_TEMPR6_11_net, QX_TEMPR7_0_net, QX_TEMPR7_1_net, 
        QX_TEMPR7_2_net, QX_TEMPR7_3_net, QX_TEMPR7_4_net, 
        QX_TEMPR7_5_net, QX_TEMPR7_6_net, QX_TEMPR7_7_net, 
        QX_TEMPR7_8_net, QX_TEMPR7_9_net, QX_TEMPR7_10_net, 
        QX_TEMPR7_11_net, QX_TEMPR8_0_net, QX_TEMPR8_1_net, 
        QX_TEMPR8_2_net, QX_TEMPR8_3_net, QX_TEMPR8_4_net, 
        QX_TEMPR8_5_net, QX_TEMPR8_6_net, QX_TEMPR8_7_net, 
        QX_TEMPR8_8_net, QX_TEMPR8_9_net, QX_TEMPR8_10_net, 
        QX_TEMPR8_11_net, QX_TEMPR9_0_net, QX_TEMPR9_1_net, 
        QX_TEMPR9_2_net, QX_TEMPR9_3_net, QX_TEMPR9_4_net, 
        QX_TEMPR9_5_net, QX_TEMPR9_6_net, QX_TEMPR9_7_net, 
        QX_TEMPR9_8_net, QX_TEMPR9_9_net, QX_TEMPR9_10_net, 
        QX_TEMPR9_11_net, QX_TEMPR10_0_net, QX_TEMPR10_1_net, 
        QX_TEMPR10_2_net, QX_TEMPR10_3_net, QX_TEMPR10_4_net, 
        QX_TEMPR10_5_net, QX_TEMPR10_6_net, QX_TEMPR10_7_net, 
        QX_TEMPR10_8_net, QX_TEMPR10_9_net, QX_TEMPR10_10_net, 
        QX_TEMPR10_11_net, QX_TEMPR11_0_net, QX_TEMPR11_1_net, 
        QX_TEMPR11_2_net, QX_TEMPR11_3_net, QX_TEMPR11_4_net, 
        QX_TEMPR11_5_net, QX_TEMPR11_6_net, QX_TEMPR11_7_net, 
        QX_TEMPR11_8_net, QX_TEMPR11_9_net, QX_TEMPR11_10_net, 
        QX_TEMPR11_11_net, QX_TEMPR12_0_net, QX_TEMPR12_1_net, 
        QX_TEMPR12_2_net, QX_TEMPR12_3_net, QX_TEMPR12_4_net, 
        QX_TEMPR12_5_net, QX_TEMPR12_6_net, QX_TEMPR12_7_net, 
        QX_TEMPR12_8_net, QX_TEMPR12_9_net, QX_TEMPR12_10_net, 
        QX_TEMPR12_11_net, QX_TEMPR13_0_net, QX_TEMPR13_1_net, 
        QX_TEMPR13_2_net, QX_TEMPR13_3_net, QX_TEMPR13_4_net, 
        QX_TEMPR13_5_net, QX_TEMPR13_6_net, QX_TEMPR13_7_net, 
        QX_TEMPR13_8_net, QX_TEMPR13_9_net, QX_TEMPR13_10_net, 
        QX_TEMPR13_11_net, QX_TEMPR14_0_net, QX_TEMPR14_1_net, 
        QX_TEMPR14_2_net, QX_TEMPR14_3_net, QX_TEMPR14_4_net, 
        QX_TEMPR14_5_net, QX_TEMPR14_6_net, QX_TEMPR14_7_net, 
        QX_TEMPR14_8_net, QX_TEMPR14_9_net, QX_TEMPR14_10_net, 
        QX_TEMPR14_11_net, QX_TEMPR15_0_net, QX_TEMPR15_1_net, 
        QX_TEMPR15_2_net, QX_TEMPR15_3_net, QX_TEMPR15_4_net, 
        QX_TEMPR15_5_net, QX_TEMPR15_6_net, QX_TEMPR15_7_net, 
        QX_TEMPR15_8_net, QX_TEMPR15_9_net, QX_TEMPR15_10_net, 
        QX_TEMPR15_11_net, NOR2_2_Y, AND2A_2_Y, AND2A_4_Y, 
        AND2_2_Y, NOR2_1_Y, AND2A_0_Y, AND2A_1_Y, AND2_1_Y, 
        BUFF_11_Y, BUFF_2_Y, BUFF_13_Y, BUFF_14_Y, BUFF_12_Y, 
        BUFF_4_Y, BUFF_1_Y, BUFF_6_Y, BUFF_7_Y, BUFF_3_Y, 
        BUFF_16_Y, BUFF_8_Y, BUFF_18_Y, BUFF_5_Y, BUFF_15_Y, 
        BUFF_17_Y, BUFF_10_Y, BUFF_0_Y, BUFF_9_Y, MX2_4_Y, 
        MX2_104_Y, MX2_145_Y, MX2_97_Y, MX2_50_Y, MX2_153_Y, 
        MX2_70_Y, MX2_32_Y, MX2_22_Y, MX2_111_Y, MX2_162_Y, 
        MX2_105_Y, MX2_123_Y, MX2_74_Y, MX2_42_Y, MX2_37_Y, 
        MX2_36_Y, MX2_107_Y, MX2_66_Y, MX2_15_Y, MX2_112_Y, 
        MX2_77_Y, MX2_88_Y, MX2_1_Y, MX2_163_Y, MX2_157_Y, 
        MX2_24_Y, MX2_121_Y, MX2_59_Y, MX2_120_Y, MX2_103_Y, 
        MX2_91_Y, MX2_30_Y, MX2_156_Y, MX2_54_Y, MX2_152_Y, 
        MX2_13_Y, MX2_71_Y, MX2_102_Y, MX2_65_Y, MX2_90_Y, 
        MX2_38_Y, MX2_75_Y, MX2_127_Y, MX2_149_Y, MX2_138_Y, 
        MX2_68_Y, MX2_19_Y, MX2_99_Y, MX2_35_Y, MX2_62_Y, 
        MX2_117_Y, MX2_26_Y, MX2_109_Y, MX2_133_Y, MX2_85_Y, 
        MX2_67_Y, MX2_151_Y, MX2_73_Y, MX2_21_Y, MX2_122_Y, 
        MX2_69_Y, MX2_141_Y, MX2_118_Y, MX2_55_Y, MX2_43_Y, 
        MX2_61_Y, MX2_39_Y, MX2_53_Y, MX2_8_Y, MX2_3_Y, MX2_167_Y, 
        MX2_16_Y, MX2_86_Y, MX2_44_Y, MX2_23_Y, MX2_126_Y, 
        MX2_81_Y, MX2_128_Y, MX2_47_Y, MX2_135_Y, MX2_28_Y, 
        MX2_18_Y, MX2_96_Y, MX2_110_Y, MX2_25_Y, MX2_14_Y, 
        MX2_147_Y, MX2_140_Y, MX2_0_Y, MX2_159_Y, MX2_48_Y, 
        MX2_12_Y, MX2_144_Y, MX2_113_Y, MX2_136_Y, MX2_160_Y, 
        MX2_106_Y, MX2_20_Y, MX2_52_Y, MX2_40_Y, MX2_92_Y, 
        MX2_89_Y, MX2_125_Y, MX2_63_Y, MX2_87_Y, MX2_137_Y, 
        MX2_7_Y, MX2_124_Y, MX2_2_Y, MX2_29_Y, MX2_134_Y, 
        MX2_129_Y, MX2_17_Y, MX2_94_Y, MX2_142_Y, MX2_130_Y, 
        MX2_49_Y, MX2_10_Y, MX2_139_Y, MX2_45_Y, MX2_56_Y, 
        MX2_84_Y, MX2_46_Y, MX2_78_Y, MX2_31_Y, MX2_150_Y, 
        MX2_95_Y, MX2_98_Y, MX2_27_Y, MX2_116_Y, MX2_131_Y, 
        MX2_72_Y, MX2_143_Y, MX2_101_Y, MX2_60_Y, MX2_76_Y, 
        MX2_51_Y, MX2_83_Y, MX2_33_Y, MX2_80_Y, MX2_166_Y, 
        MX2_158_Y, MX2_9_Y, MX2_154_Y, MX2_119_Y, MX2_57_Y, 
        MX2_58_Y, MX2_93_Y, MX2_41_Y, MX2_11_Y, MX2_5_Y, 
        MX2_164_Y, MX2_79_Y, MX2_64_Y, MX2_114_Y, MX2_148_Y, 
        MX2_6_Y, MX2_165_Y, MX2_146_Y, MX2_100_Y, MX2_34_Y, 
        MX2_155_Y, MX2_115_Y, MX2_161_Y, MX2_108_Y, MX2_132_Y, 
        MX2_82_Y, NOR2_0_Y, AND2A_6_Y, AND2A_7_Y, AND2_0_Y, 
        NOR2_3_Y, AND2A_3_Y, AND2A_5_Y, AND2_3_Y, VCC, GND;
    
    VCC VCC_1_net(.Y(VCC));
    GND GND_1_net(.Y(GND));
    MX2 MX2_52(.A(QX_TEMPR2_4_net), .B(QX_TEMPR3_4_net), .S(
        BUFF_14_Y), .Y(MX2_52_Y));
    NAND2 NAND2_ENABLE_ADDRB_9_inst(.A(AND2A_6_Y), .B(AND2A_5_Y), 
        .Y(ENABLE_ADDRB_9_net));
    OR2 ORB_GATE_0_inst(.A(ENABLE_ADDRB_0_net), .B(WEBP), .Y(
        BLKB_EN_0_net));
    MX2 MX2_123(.A(QX_TEMPR12_9_net), .B(QX_TEMPR13_9_net), .S(
        BUFF_6_Y), .Y(MX2_123_Y));
    AND2 AND2_2(.A(WADDR[9]), .B(WADDR[8]), .Y(AND2_2_Y));
    NAND2 NAND2_ENABLE_ADDRB_14_inst(.A(AND2A_7_Y), .B(AND2_3_Y), 
        .Y(ENABLE_ADDRB_14_net));
    NOR2 NOR2_2(.A(WADDR[9]), .B(WADDR[8]), .Y(NOR2_2_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R5C0.mem") )  RAM_R5C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_5_net), .WEN(BLKA_EN_5_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR5_11_net), .RD10(
        QX_TEMPR5_10_net), .RD9(QX_TEMPR5_9_net), .RD8(
        QX_TEMPR5_8_net), .RD7(QX_TEMPR5_7_net), .RD6(
        QX_TEMPR5_6_net), .RD5(QX_TEMPR5_5_net), .RD4(
        QX_TEMPR5_4_net), .RD3(QX_TEMPR5_3_net), .RD2(
        QX_TEMPR5_2_net), .RD1(QX_TEMPR5_1_net), .RD0(
        QX_TEMPR5_0_net));
    MX2 MX2_80(.A(QX_TEMPR0_11_net), .B(QX_TEMPR1_11_net), .S(
        BUFF_7_Y), .Y(MX2_80_Y));
    MX2 MX2_132(.A(QX_TEMPR12_0_net), .B(QX_TEMPR13_0_net), .S(
        BUFF_11_Y), .Y(MX2_132_Y));
    OR2 ORA_GATE_14_inst(.A(ENABLE_ADDRA_14_net), .B(WEAP), .Y(
        BLKA_EN_14_net));
    BUFF BUFF_10(.A(ADDRB_FF2_2_net), .Y(BUFF_10_Y));
    OR2 ORA_GATE_12_inst(.A(ENABLE_ADDRA_12_net), .B(WEAP), .Y(
        BLKA_EN_12_net));
    MX2 MX2_121(.A(QX_TEMPR14_6_net), .B(QX_TEMPR15_6_net), .S(
        BUFF_4_Y), .Y(MX2_121_Y));
    MX2 MX2_17(.A(QX_TEMPR2_1_net), .B(QX_TEMPR3_1_net), .S(
        BUFF_11_Y), .Y(MX2_17_Y));
    MX2 MX2_166(.A(QX_TEMPR2_11_net), .B(QX_TEMPR3_11_net), .S(
        BUFF_7_Y), .Y(MX2_166_Y));
    MX2 MX2_58(.A(MX2_11_Y), .B(MX2_5_Y), .S(BUFF_10_Y), .Y(
        MX2_58_Y));
    MX2 MX2_49(.A(QX_TEMPR4_1_net), .B(QX_TEMPR5_1_net), .S(
        BUFF_11_Y), .Y(MX2_49_Y));
    BUFF BUFF_8(.A(ADDRB_FF2_1_net), .Y(BUFF_8_Y));
    MX2 MX2_RD_8_inst(.A(MX2_30_Y), .B(MX2_152_Y), .S(BUFF_9_Y), 
        .Y(RD[8]));
    MX2 MX2_RD_10_inst(.A(MX2_44_Y), .B(MX2_81_Y), .S(BUFF_9_Y), 
        .Y(RD[10]));
    MX2 MX2_21(.A(MX2_69_Y), .B(MX2_141_Y), .S(BUFF_3_Y), .Y(
        MX2_21_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R0C0.mem") )  RAM_R0C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_0_net), .WEN(BLKA_EN_0_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR0_11_net), .RD10(
        QX_TEMPR0_10_net), .RD9(QX_TEMPR0_9_net), .RD8(
        QX_TEMPR0_8_net), .RD7(QX_TEMPR0_7_net), .RD6(
        QX_TEMPR0_6_net), .RD5(QX_TEMPR0_5_net), .RD4(
        QX_TEMPR0_4_net), .RD3(QX_TEMPR0_3_net), .RD2(
        QX_TEMPR0_2_net), .RD1(QX_TEMPR0_1_net), .RD0(
        QX_TEMPR0_0_net));
    AND2A AND2A_7(.A(RADDR[8]), .B(RADDR[9]), .Y(AND2A_7_Y));
    NAND2 NAND2_ENABLE_ADDRB_13_inst(.A(AND2A_6_Y), .B(AND2_3_Y), 
        .Y(ENABLE_ADDRB_13_net));
    OR2 ORA_GATE_7_inst(.A(ENABLE_ADDRA_7_net), .B(WEAP), .Y(
        BLKA_EN_7_net));
    MX2 MX2_44(.A(MX2_16_Y), .B(MX2_86_Y), .S(BUFF_10_Y), .Y(
        MX2_44_Y));
    MX2 MX2_136(.A(MX2_160_Y), .B(MX2_106_Y), .S(BUFF_8_Y), .Y(
        MX2_136_Y));
    MX2 MX2_56(.A(QX_TEMPR10_1_net), .B(QX_TEMPR11_1_net), .S(
        BUFF_2_Y), .Y(MX2_56_Y));
    MX2 MX2_163(.A(MX2_88_Y), .B(MX2_1_Y), .S(BUFF_8_Y), .Y(
        MX2_163_Y));
    AND2 AND2_1(.A(WADDR[11]), .B(WADDR[10]), .Y(AND2_1_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R12C0.mem") )  RAM_R12C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_12_net), .WEN(BLKA_EN_12_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR12_11_net), 
        .RD10(QX_TEMPR12_10_net), .RD9(QX_TEMPR12_9_net), .RD8(
        QX_TEMPR12_8_net), .RD7(QX_TEMPR12_7_net), .RD6(
        QX_TEMPR12_6_net), .RD5(QX_TEMPR12_5_net), .RD4(
        QX_TEMPR12_4_net), .RD3(QX_TEMPR12_3_net), .RD2(
        QX_TEMPR12_2_net), .RD1(QX_TEMPR12_1_net), .RD0(
        QX_TEMPR12_0_net));
    RAM512X18 #( .MEMORYFILE("RAM_R4C0.mem") )  RAM_R4C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_4_net), .WEN(BLKA_EN_4_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR4_11_net), .RD10(
        QX_TEMPR4_10_net), .RD9(QX_TEMPR4_9_net), .RD8(
        QX_TEMPR4_8_net), .RD7(QX_TEMPR4_7_net), .RD6(
        QX_TEMPR4_6_net), .RD5(QX_TEMPR4_5_net), .RD4(
        QX_TEMPR4_4_net), .RD3(QX_TEMPR4_3_net), .RD2(
        QX_TEMPR4_2_net), .RD1(QX_TEMPR4_1_net), .RD0(
        QX_TEMPR4_0_net));
    AND2A AND2A_1(.A(WADDR[10]), .B(WADDR[11]), .Y(AND2A_1_Y));
    MX2 MX2_RD_3_inst(.A(MX2_68_Y), .B(MX2_35_Y), .S(BUFF_0_Y), 
        .Y(RD[3]));
    MX2 MX2_5(.A(MX2_164_Y), .B(MX2_79_Y), .S(BUFF_5_Y), .Y(
        MX2_5_Y));
    MX2 MX2_53(.A(QX_TEMPR12_2_net), .B(QX_TEMPR13_2_net), .S(
        BUFF_13_Y), .Y(MX2_53_Y));
    OR2 ORB_GATE_4_inst(.A(ENABLE_ADDRB_4_net), .B(WEBP), .Y(
        BLKB_EN_4_net));
    MX2 MX2_25(.A(QX_TEMPR2_5_net), .B(QX_TEMPR3_5_net), .S(
        BUFF_14_Y), .Y(MX2_25_Y));
    MX2 MX2_161(.A(MX2_155_Y), .B(MX2_115_Y), .S(BUFF_3_Y), .Y(
        MX2_161_Y));
    AND2A AND2A_5(.A(RADDR[10]), .B(RADDR[11]), .Y(AND2A_5_Y));
    MX2 MX2_133(.A(QX_TEMPR12_3_net), .B(QX_TEMPR13_3_net), .S(
        BUFF_13_Y), .Y(MX2_133_Y));
    OR2 ORB_GATE_14_inst(.A(ENABLE_ADDRB_14_net), .B(WEBP), .Y(
        BLKB_EN_14_net));
    MX2 MX2_RD_9_inst(.A(MX2_50_Y), .B(MX2_32_Y), .S(BUFF_9_Y), 
        .Y(RD[9]));
    BUFF BUFF_2(.A(ADDRB_FF2_0_net), .Y(BUFF_2_Y));
    MX2 MX2_148(.A(MX2_64_Y), .B(MX2_114_Y), .S(BUFF_3_Y), .Y(
        MX2_148_Y));
    OR2 ORA_GATE_15_inst(.A(ENABLE_ADDRA_15_net), .B(WEAP), .Y(
        BLKA_EN_15_net));
    MX2 MX2_115(.A(QX_TEMPR10_0_net), .B(QX_TEMPR11_0_net), .S(
        BUFF_11_Y), .Y(MX2_115_Y));
    MX2 MX2_RD_1_inst(.A(MX2_130_Y), .B(MX2_139_Y), .S(BUFF_0_Y), 
        .Y(RD[1]));
    MX2 MX2_147(.A(MX2_0_Y), .B(MX2_159_Y), .S(BUFF_8_Y), .Y(
        MX2_147_Y));
    MX2 MX2_61(.A(MX2_55_Y), .B(MX2_43_Y), .S(BUFF_16_Y), .Y(
        MX2_61_Y));
    MX2 MX2_82(.A(QX_TEMPR14_0_net), .B(QX_TEMPR15_0_net), .S(
        BUFF_11_Y), .Y(MX2_82_Y));
    MX2 MX2_131(.A(QX_TEMPR4_7_net), .B(QX_TEMPR5_7_net), .S(
        BUFF_4_Y), .Y(MX2_131_Y));
    NOR2 NOR2_3(.A(RADDR[11]), .B(RADDR[10]), .Y(NOR2_3_Y));
    NAND2 NAND2_ENABLE_ADDRA_0_inst(.A(NOR2_2_Y), .B(NOR2_1_Y), 
        .Y(ENABLE_ADDRA_0_net));
    MX2 MX2_57(.A(QX_TEMPR6_11_net), .B(QX_TEMPR7_11_net), .S(
        BUFF_7_Y), .Y(MX2_57_Y));
    DFN1 AFF1_3_inst(.D(WADDR[11]), .CLK(WCLK), .Q(
        ADDRA_FF2_3_net));
    MX2 MX2_71(.A(QX_TEMPR10_8_net), .B(QX_TEMPR11_8_net), .S(
        BUFF_1_Y), .Y(MX2_71_Y));
    INV WEBUBBLEB(.A(REN), .Y(WEBP));
    OR2 ORB_GATE_9_inst(.A(ENABLE_ADDRB_9_net), .B(WEBP), .Y(
        BLKB_EN_9_net));
    MX2 MX2_20(.A(QX_TEMPR0_4_net), .B(QX_TEMPR1_4_net), .S(
        BUFF_13_Y), .Y(MX2_20_Y));
    MX2 MX2_19(.A(QX_TEMPR4_3_net), .B(QX_TEMPR5_3_net), .S(
        BUFF_13_Y), .Y(MX2_19_Y));
    MX2 MX2_RD_11_inst(.A(MX2_154_Y), .B(MX2_58_Y), .S(BUFF_9_Y), 
        .Y(RD[11]));
    OR2 ORA_GATE_1_inst(.A(ENABLE_ADDRA_1_net), .B(WEAP), .Y(
        BLKA_EN_1_net));
    MX2 MX2_88(.A(QX_TEMPR8_6_net), .B(QX_TEMPR9_6_net), .S(
        BUFF_12_Y), .Y(MX2_88_Y));
    MX2 MX2_31(.A(QX_TEMPR14_1_net), .B(QX_TEMPR15_1_net), .S(
        BUFF_2_Y), .Y(MX2_31_Y));
    NAND2 NAND2_ENABLE_ADDRB_12_inst(.A(NOR2_0_Y), .B(AND2_3_Y), 
        .Y(ENABLE_ADDRB_12_net));
    MX2 MX2_155(.A(QX_TEMPR8_0_net), .B(QX_TEMPR9_0_net), .S(
        BUFF_11_Y), .Y(MX2_155_Y));
    MX2 MX2_14(.A(MX2_110_Y), .B(MX2_25_Y), .S(BUFF_8_Y), .Y(
        MX2_14_Y));
    NAND2 NAND2_ENABLE_ADDRA_11_inst(.A(AND2_2_Y), .B(AND2A_1_Y), 
        .Y(ENABLE_ADDRA_11_net));
    MX2 MX2_65(.A(MX2_90_Y), .B(MX2_38_Y), .S(BUFF_18_Y), .Y(
        MX2_65_Y));
    OR2 ORB_GATE_12_inst(.A(ENABLE_ADDRB_12_net), .B(WEBP), .Y(
        BLKB_EN_12_net));
    NAND2 NAND2_ENABLE_ADDRA_15_inst(.A(AND2_2_Y), .B(AND2_1_Y), 
        .Y(ENABLE_ADDRA_15_net));
    MX2 MX2_91(.A(MX2_156_Y), .B(MX2_54_Y), .S(BUFF_18_Y), .Y(
        MX2_91_Y));
    MX2 MX2_75(.A(QX_TEMPR0_3_net), .B(QX_TEMPR1_3_net), .S(
        BUFF_13_Y), .Y(MX2_75_Y));
    OR2 ORB_GATE_15_inst(.A(ENABLE_ADDRB_15_net), .B(WEBP), .Y(
        BLKB_EN_15_net));
    RAM512X18 #( .MEMORYFILE("RAM_R9C0.mem") )  RAM_R9C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_9_net), .WEN(BLKA_EN_9_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR9_11_net), .RD10(
        QX_TEMPR9_10_net), .RD9(QX_TEMPR9_9_net), .RD8(
        QX_TEMPR9_8_net), .RD7(QX_TEMPR9_7_net), .RD6(
        QX_TEMPR9_6_net), .RD5(QX_TEMPR9_5_net), .RD4(
        QX_TEMPR9_4_net), .RD3(QX_TEMPR9_3_net), .RD2(
        QX_TEMPR9_2_net), .RD1(QX_TEMPR9_1_net), .RD0(
        QX_TEMPR9_0_net));
    BUFF BUFF_14(.A(ADDRB_FF2_0_net), .Y(BUFF_14_Y));
    MX2 MX2_86(.A(MX2_23_Y), .B(MX2_126_Y), .S(BUFF_5_Y), .Y(
        MX2_86_Y));
    MX2 MX2_142(.A(MX2_49_Y), .B(MX2_10_Y), .S(BUFF_3_Y), .Y(
        MX2_142_Y));
    NOR2 NOR2_0(.A(RADDR[9]), .B(RADDR[8]), .Y(NOR2_0_Y));
    NAND2 NAND2_ENABLE_ADDRA_10_inst(.A(AND2A_4_Y), .B(AND2A_1_Y), 
        .Y(ENABLE_ADDRA_10_net));
    MX2 MX2_35(.A(MX2_26_Y), .B(MX2_109_Y), .S(BUFF_15_Y), .Y(
        MX2_35_Y));
    OR2 ORA_GATE_3_inst(.A(ENABLE_ADDRA_3_net), .B(WEAP), .Y(
        BLKA_EN_3_net));
    NAND2 NAND2_ENABLE_ADDRA_1_inst(.A(AND2A_2_Y), .B(NOR2_1_Y), 
        .Y(ENABLE_ADDRA_1_net));
    MX2 MX2_105(.A(MX2_123_Y), .B(MX2_74_Y), .S(BUFF_5_Y), .Y(
        MX2_105_Y));
    MX2 MX2_8(.A(QX_TEMPR14_2_net), .B(QX_TEMPR15_2_net), .S(
        BUFF_13_Y), .Y(MX2_8_Y));
    MX2 MX2_60(.A(QX_TEMPR10_7_net), .B(QX_TEMPR11_7_net), .S(
        BUFF_4_Y), .Y(MX2_60_Y));
    MX2 MX2_83(.A(QX_TEMPR12_7_net), .B(QX_TEMPR13_7_net), .S(
        BUFF_4_Y), .Y(MX2_83_Y));
    MX2 MX2_114(.A(QX_TEMPR2_0_net), .B(QX_TEMPR3_0_net), .S(
        BUFF_11_Y), .Y(MX2_114_Y));
    MX2 MX2_110(.A(QX_TEMPR0_5_net), .B(QX_TEMPR1_5_net), .S(
        BUFF_14_Y), .Y(MX2_110_Y));
    MX2 MX2_RD_6_inst(.A(MX2_66_Y), .B(MX2_77_Y), .S(BUFF_9_Y), 
        .Y(RD[6]));
    MX2 MX2_119(.A(QX_TEMPR4_11_net), .B(QX_TEMPR5_11_net), .S(
        BUFF_7_Y), .Y(MX2_119_Y));
    MX2 MX2_95(.A(QX_TEMPR2_7_net), .B(QX_TEMPR3_7_net), .S(
        BUFF_4_Y), .Y(MX2_95_Y));
    NAND2 NAND2_ENABLE_ADDRA_7_inst(.A(AND2_2_Y), .B(AND2A_0_Y), 
        .Y(ENABLE_ADDRA_7_net));
    AND2 AND2_3(.A(RADDR[11]), .B(RADDR[10]), .Y(AND2_3_Y));
    MX2 MX2_70(.A(QX_TEMPR6_9_net), .B(QX_TEMPR7_9_net), .S(
        BUFF_1_Y), .Y(MX2_70_Y));
    MX2 MX2_146(.A(QX_TEMPR4_0_net), .B(QX_TEMPR5_0_net), .S(
        BUFF_11_Y), .Y(MX2_146_Y));
    MX2 MX2_59(.A(QX_TEMPR0_8_net), .B(QX_TEMPR1_8_net), .S(
        BUFF_4_Y), .Y(MX2_59_Y));
    BUFF BUFF_5(.A(ADDRB_FF2_1_net), .Y(BUFF_5_Y));
    MX2 MX2_30(.A(MX2_103_Y), .B(MX2_91_Y), .S(BUFF_10_Y), .Y(
        MX2_30_Y));
    MX2 MX2_22(.A(QX_TEMPR8_9_net), .B(QX_TEMPR9_9_net), .S(
        BUFF_6_Y), .Y(MX2_22_Y));
    MX2 MX2_87(.A(MX2_124_Y), .B(MX2_2_Y), .S(BUFF_17_Y), .Y(
        MX2_87_Y));
    MX2 MX2_RD_7_inst(.A(MX2_116_Y), .B(MX2_143_Y), .S(BUFF_9_Y), 
        .Y(RD[7]));
    OR2 ORA_GATE_5_inst(.A(ENABLE_ADDRA_5_net), .B(WEAP), .Y(
        BLKA_EN_5_net));
    MX2 MX2_154(.A(MX2_158_Y), .B(MX2_9_Y), .S(BUFF_10_Y), .Y(
        MX2_154_Y));
    NAND2 NAND2_ENABLE_ADDRB_2_inst(.A(AND2A_7_Y), .B(NOR2_3_Y), 
        .Y(ENABLE_ADDRB_2_net));
    OR2 ORA_GATE_2_inst(.A(ENABLE_ADDRA_2_net), .B(WEAP), .Y(
        BLKA_EN_2_net));
    MX2 MX2_150(.A(QX_TEMPR0_7_net), .B(QX_TEMPR1_7_net), .S(
        BUFF_4_Y), .Y(MX2_150_Y));
    MX2 MX2_90(.A(QX_TEMPR12_8_net), .B(QX_TEMPR13_8_net), .S(
        BUFF_1_Y), .Y(MX2_90_Y));
    NOR2 NOR2_1(.A(WADDR[11]), .B(WADDR[10]), .Y(NOR2_1_Y));
    MX2 MX2_54(.A(QX_TEMPR6_8_net), .B(QX_TEMPR7_8_net), .S(
        BUFF_1_Y), .Y(MX2_54_Y));
    MX2 MX2_159(.A(QX_TEMPR6_5_net), .B(QX_TEMPR7_5_net), .S(
        BUFF_14_Y), .Y(MX2_159_Y));
    MX2 MX2_0(.A(QX_TEMPR4_5_net), .B(QX_TEMPR5_5_net), .S(
        BUFF_14_Y), .Y(MX2_0_Y));
    MX2 MX2_143(.A(MX2_76_Y), .B(MX2_51_Y), .S(BUFF_17_Y), .Y(
        MX2_143_Y));
    OR2 ORA_GATE_0_inst(.A(ENABLE_ADDRA_0_net), .B(WEAP), .Y(
        BLKA_EN_0_net));
    MX2 MX2_41(.A(QX_TEMPR10_11_net), .B(QX_TEMPR11_11_net), .S(
        BUFF_7_Y), .Y(MX2_41_Y));
    MX2 MX2_28(.A(MX2_18_Y), .B(MX2_96_Y), .S(BUFF_5_Y), .Y(
        MX2_28_Y));
    DFN1 BFF1_2_inst(.D(RADDR[10]), .CLK(RCLK), .Q(
        ADDRB_FF2_2_net));
    MX2 MX2_141(.A(QX_TEMPR6_2_net), .B(QX_TEMPR7_2_net), .S(
        BUFF_2_Y), .Y(MX2_141_Y));
    MX2 MX2_104(.A(QX_TEMPR2_9_net), .B(QX_TEMPR3_9_net), .S(
        BUFF_1_Y), .Y(MX2_104_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R2C0.mem") )  RAM_R2C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_2_net), .WEN(BLKA_EN_2_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR2_11_net), .RD10(
        QX_TEMPR2_10_net), .RD9(QX_TEMPR2_9_net), .RD8(
        QX_TEMPR2_8_net), .RD7(QX_TEMPR2_7_net), .RD6(
        QX_TEMPR2_6_net), .RD5(QX_TEMPR2_5_net), .RD4(
        QX_TEMPR2_4_net), .RD3(QX_TEMPR2_3_net), .RD2(
        QX_TEMPR2_2_net), .RD1(QX_TEMPR2_1_net), .RD0(
        QX_TEMPR2_0_net));
    MX2 MX2_100(.A(QX_TEMPR6_0_net), .B(QX_TEMPR7_0_net), .S(
        BUFF_11_Y), .Y(MX2_100_Y));
    MX2 MX2_109(.A(MX2_133_Y), .B(MX2_85_Y), .S(BUFF_16_Y), .Y(
        MX2_109_Y));
    MX2 MX2_26(.A(MX2_62_Y), .B(MX2_117_Y), .S(BUFF_16_Y), .Y(
        MX2_26_Y));
    AND2A AND2A_2(.A(WADDR[9]), .B(WADDR[8]), .Y(AND2A_2_Y));
    MX2 MX2_125(.A(QX_TEMPR4_4_net), .B(QX_TEMPR5_4_net), .S(
        BUFF_14_Y), .Y(MX2_125_Y));
    MX2 MX2_62(.A(QX_TEMPR8_3_net), .B(QX_TEMPR9_3_net), .S(
        BUFF_13_Y), .Y(MX2_62_Y));
    MX2 MX2_45(.A(QX_TEMPR8_1_net), .B(QX_TEMPR9_1_net), .S(
        BUFF_2_Y), .Y(MX2_45_Y));
    MX2 MX2_118(.A(MX2_61_Y), .B(MX2_39_Y), .S(BUFF_15_Y), .Y(
        MX2_118_Y));
    OR2 ORB_GATE_13_inst(.A(ENABLE_ADDRB_13_net), .B(WEBP), .Y(
        BLKB_EN_13_net));
    MX2 MX2_2(.A(MX2_29_Y), .B(MX2_134_Y), .S(BUFF_16_Y), .Y(
        MX2_2_Y));
    MX2 MX2_72(.A(QX_TEMPR6_7_net), .B(QX_TEMPR7_7_net), .S(
        BUFF_4_Y), .Y(MX2_72_Y));
    MX2 MX2_23(.A(QX_TEMPR4_10_net), .B(QX_TEMPR5_10_net), .S(
        BUFF_6_Y), .Y(MX2_23_Y));
    NAND2 NAND2_ENABLE_ADDRA_8_inst(.A(NOR2_2_Y), .B(AND2A_1_Y), 
        .Y(ENABLE_ADDRA_8_net));
    MX2 MX2_117(.A(QX_TEMPR10_3_net), .B(QX_TEMPR11_3_net), .S(
        BUFF_13_Y), .Y(MX2_117_Y));
    OR2 ORB_GATE_6_inst(.A(ENABLE_ADDRB_6_net), .B(WEBP), .Y(
        BLKB_EN_6_net));
    BUFF BUFF_12(.A(ADDRB_FF2_0_net), .Y(BUFF_12_Y));
    NAND2 NAND2_ENABLE_ADDRB_6_inst(.A(AND2A_7_Y), .B(AND2A_3_Y), 
        .Y(ENABLE_ADDRB_6_net));
    AND2A AND2A_4(.A(WADDR[8]), .B(WADDR[9]), .Y(AND2A_4_Y));
    MX2 MX2_68(.A(MX2_149_Y), .B(MX2_138_Y), .S(BUFF_15_Y), .Y(
        MX2_68_Y));
    MX2 MX2_32(.A(MX2_162_Y), .B(MX2_105_Y), .S(BUFF_10_Y), .Y(
        MX2_32_Y));
    MX2 MX2_89(.A(MX2_40_Y), .B(MX2_92_Y), .S(BUFF_17_Y), .Y(
        MX2_89_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R14C0.mem") )  RAM_R14C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_14_net), .WEN(BLKA_EN_14_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR14_11_net), 
        .RD10(QX_TEMPR14_10_net), .RD9(QX_TEMPR14_9_net), .RD8(
        QX_TEMPR14_8_net), .RD7(QX_TEMPR14_7_net), .RD6(
        QX_TEMPR14_6_net), .RD5(QX_TEMPR14_5_net), .RD4(
        QX_TEMPR14_4_net), .RD3(QX_TEMPR14_3_net), .RD2(
        QX_TEMPR14_2_net), .RD1(QX_TEMPR14_1_net), .RD0(
        QX_TEMPR14_0_net));
    DFN1 BFF1_0_inst(.D(RADDR[8]), .CLK(RCLK), .Q(ADDRB_FF2_0_net)
        );
    OR2 ORA_GATE_4_inst(.A(ENABLE_ADDRA_4_net), .B(WEAP), .Y(
        BLKA_EN_4_net));
    MX2 MX2_78(.A(QX_TEMPR12_1_net), .B(QX_TEMPR13_1_net), .S(
        BUFF_2_Y), .Y(MX2_78_Y));
    BUFF BUFF_0(.A(ADDRB_FF2_3_net), .Y(BUFF_0_Y));
    DFN1 BFF1_1_inst(.D(RADDR[9]), .CLK(RCLK), .Q(ADDRB_FF2_1_net)
        );
    MX2 MX2_40(.A(MX2_20_Y), .B(MX2_52_Y), .S(BUFF_16_Y), .Y(
        MX2_40_Y));
    MX2 MX2_92(.A(MX2_125_Y), .B(MX2_63_Y), .S(BUFF_16_Y), .Y(
        MX2_92_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R8C0.mem") )  RAM_R8C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_8_net), .WEN(BLKA_EN_8_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR8_11_net), .RD10(
        QX_TEMPR8_10_net), .RD9(QX_TEMPR8_9_net), .RD8(
        QX_TEMPR8_8_net), .RD7(QX_TEMPR8_7_net), .RD6(
        QX_TEMPR8_6_net), .RD5(QX_TEMPR8_5_net), .RD4(
        QX_TEMPR8_4_net), .RD3(QX_TEMPR8_3_net), .RD2(
        QX_TEMPR8_2_net), .RD1(QX_TEMPR8_1_net), .RD0(
        QX_TEMPR8_0_net));
    MX2 MX2_158(.A(MX2_80_Y), .B(MX2_166_Y), .S(BUFF_5_Y), .Y(
        MX2_158_Y));
    NAND2 NAND2_ENABLE_ADDRB_11_inst(.A(AND2_0_Y), .B(AND2A_5_Y), 
        .Y(ENABLE_ADDRB_11_net));
    INV WEBUBBLEA(.A(WEN), .Y(WEAP));
    MX2 MX2_165(.A(MX2_148_Y), .B(MX2_6_Y), .S(BUFF_15_Y), .Y(
        MX2_165_Y));
    OR2 ORB_GATE_8_inst(.A(ENABLE_ADDRB_8_net), .B(WEBP), .Y(
        BLKB_EN_8_net));
    MX2 MX2_27(.A(MX2_131_Y), .B(MX2_72_Y), .S(BUFF_8_Y), .Y(
        MX2_27_Y));
    MX2 MX2_66(.A(MX2_36_Y), .B(MX2_107_Y), .S(BUFF_17_Y), .Y(
        MX2_66_Y));
    NAND2 NAND2_ENABLE_ADDRB_15_inst(.A(AND2_0_Y), .B(AND2_3_Y), 
        .Y(ENABLE_ADDRB_15_net));
    MX2 MX2_84(.A(MX2_45_Y), .B(MX2_56_Y), .S(BUFF_3_Y), .Y(
        MX2_84_Y));
    MX2 MX2_11(.A(MX2_93_Y), .B(MX2_41_Y), .S(BUFF_5_Y), .Y(
        MX2_11_Y));
    MX2 MX2_157(.A(MX2_24_Y), .B(MX2_121_Y), .S(BUFF_8_Y), .Y(
        MX2_157_Y));
    MX2 MX2_38(.A(QX_TEMPR14_8_net), .B(QX_TEMPR15_8_net), .S(
        BUFF_1_Y), .Y(MX2_38_Y));
    MX2 MX2_76(.A(MX2_101_Y), .B(MX2_60_Y), .S(BUFF_18_Y), .Y(
        MX2_76_Y));
    OR2 ORA_GATE_9_inst(.A(ENABLE_ADDRA_9_net), .B(WEAP), .Y(
        BLKA_EN_9_net));
    MX2 MX2_6(.A(MX2_146_Y), .B(MX2_100_Y), .S(BUFF_3_Y), .Y(
        MX2_6_Y));
    NAND2 NAND2_ENABLE_ADDRB_7_inst(.A(AND2_0_Y), .B(AND2A_3_Y), 
        .Y(ENABLE_ADDRB_7_net));
    MX2 MX2_135(.A(MX2_128_Y), .B(MX2_47_Y), .S(BUFF_5_Y), .Y(
        MX2_135_Y));
    MX2 MX2_112(.A(QX_TEMPR6_6_net), .B(QX_TEMPR7_6_net), .S(
        BUFF_12_Y), .Y(MX2_112_Y));
    MX2 MX2_98(.A(MX2_150_Y), .B(MX2_95_Y), .S(BUFF_8_Y), .Y(
        MX2_98_Y));
    MX2 MX2_63(.A(QX_TEMPR6_4_net), .B(QX_TEMPR7_4_net), .S(
        BUFF_14_Y), .Y(MX2_63_Y));
    NAND2 NAND2_ENABLE_ADDRB_10_inst(.A(AND2A_7_Y), .B(AND2A_5_Y), 
        .Y(ENABLE_ADDRB_10_net));
    OR2 ORB_GATE_11_inst(.A(ENABLE_ADDRB_11_net), .B(WEBP), .Y(
        BLKB_EN_11_net));
    MX2 MX2_124(.A(MX2_137_Y), .B(MX2_7_Y), .S(BUFF_16_Y), .Y(
        MX2_124_Y));
    MX2 MX2_RD_5_inst(.A(MX2_140_Y), .B(MX2_48_Y), .S(BUFF_0_Y), 
        .Y(RD[5]));
    MX2 MX2_120(.A(QX_TEMPR2_8_net), .B(QX_TEMPR3_8_net), .S(
        BUFF_4_Y), .Y(MX2_120_Y));
    MX2 MX2_36(.A(MX2_42_Y), .B(MX2_37_Y), .S(BUFF_8_Y), .Y(
        MX2_36_Y));
    MX2 MX2_129(.A(QX_TEMPR0_1_net), .B(QX_TEMPR1_1_net), .S(
        BUFF_11_Y), .Y(MX2_129_Y));
    MX2 MX2_108(.A(MX2_132_Y), .B(MX2_82_Y), .S(BUFF_3_Y), .Y(
        MX2_108_Y));
    NAND2 NAND2_ENABLE_ADDRB_4_inst(.A(NOR2_0_Y), .B(AND2A_3_Y), 
        .Y(ENABLE_ADDRB_4_net));
    MX2 MX2_7(.A(QX_TEMPR10_4_net), .B(QX_TEMPR11_4_net), .S(
        BUFF_14_Y), .Y(MX2_7_Y));
    AND2A AND2A_3(.A(RADDR[11]), .B(RADDR[10]), .Y(AND2A_3_Y));
    MX2 MX2_73(.A(MX2_67_Y), .B(MX2_151_Y), .S(BUFF_3_Y), .Y(
        MX2_73_Y));
    BUFF BUFF_9(.A(ADDRB_FF2_3_net), .Y(BUFF_9_Y));
    AND2A AND2A_6(.A(RADDR[9]), .B(RADDR[8]), .Y(AND2A_6_Y));
    MX2 MX2_107(.A(MX2_15_Y), .B(MX2_112_Y), .S(BUFF_8_Y), .Y(
        MX2_107_Y));
    MX2 MX2_15(.A(QX_TEMPR4_6_net), .B(QX_TEMPR5_6_net), .S(
        BUFF_12_Y), .Y(MX2_15_Y));
    MX2 MX2_96(.A(QX_TEMPR14_10_net), .B(QX_TEMPR15_10_net), .S(
        BUFF_7_Y), .Y(MX2_96_Y));
    NAND2 NAND2_ENABLE_ADDRA_6_inst(.A(AND2A_4_Y), .B(AND2A_0_Y), 
        .Y(ENABLE_ADDRA_6_net));
    MX2 MX2_3(.A(QX_TEMPR0_10_net), .B(QX_TEMPR1_10_net), .S(
        BUFF_6_Y), .Y(MX2_3_Y));
    MX2 MX2_33(.A(QX_TEMPR14_7_net), .B(QX_TEMPR15_7_net), .S(
        BUFF_4_Y), .Y(MX2_33_Y));
    MX2 MX2_67(.A(QX_TEMPR0_2_net), .B(QX_TEMPR1_2_net), .S(
        BUFF_2_Y), .Y(MX2_67_Y));
    MX2 MX2_152(.A(MX2_102_Y), .B(MX2_65_Y), .S(BUFF_10_Y), .Y(
        MX2_152_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R13C0.mem") )  RAM_R13C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_13_net), .WEN(BLKA_EN_13_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR13_11_net), 
        .RD10(QX_TEMPR13_10_net), .RD9(QX_TEMPR13_9_net), .RD8(
        QX_TEMPR13_8_net), .RD7(QX_TEMPR13_7_net), .RD6(
        QX_TEMPR13_6_net), .RD5(QX_TEMPR13_5_net), .RD4(
        QX_TEMPR13_4_net), .RD3(QX_TEMPR13_3_net), .RD2(
        QX_TEMPR13_2_net), .RD1(QX_TEMPR13_1_net), .RD0(
        QX_TEMPR13_0_net));
    MX2 MX2_116(.A(MX2_98_Y), .B(MX2_27_Y), .S(BUFF_17_Y), .Y(
        MX2_116_Y));
    BUFF BUFF_6(.A(ADDRB_FF2_0_net), .Y(BUFF_6_Y));
    BUFF BUFF_7(.A(ADDRB_FF2_0_net), .Y(BUFF_7_Y));
    MX2 MX2_9(.A(MX2_119_Y), .B(MX2_57_Y), .S(BUFF_5_Y), .Y(
        MX2_9_Y));
    MX2 MX2_93(.A(QX_TEMPR8_11_net), .B(QX_TEMPR9_11_net), .S(
        BUFF_7_Y), .Y(MX2_93_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R11C0.mem") )  RAM_R11C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_11_net), .WEN(BLKA_EN_11_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR11_11_net), 
        .RD10(QX_TEMPR11_10_net), .RD9(QX_TEMPR11_9_net), .RD8(
        QX_TEMPR11_8_net), .RD7(QX_TEMPR11_7_net), .RD6(
        QX_TEMPR11_6_net), .RD5(QX_TEMPR11_5_net), .RD4(
        QX_TEMPR11_4_net), .RD3(QX_TEMPR11_3_net), .RD2(
        QX_TEMPR11_2_net), .RD1(QX_TEMPR11_1_net), .RD0(
        QX_TEMPR11_0_net));
    NAND2 NAND2_ENABLE_ADDRB_0_inst(.A(NOR2_0_Y), .B(NOR2_3_Y), 
        .Y(ENABLE_ADDRB_0_net));
    MX2 MX2_77(.A(MX2_163_Y), .B(MX2_157_Y), .S(BUFF_17_Y), .Y(
        MX2_77_Y));
    AND2A AND2A_0(.A(WADDR[11]), .B(WADDR[10]), .Y(AND2A_0_Y));
    BUFF BUFF_16(.A(ADDRB_FF2_1_net), .Y(BUFF_16_Y));
    OR2 ORB_GATE_7_inst(.A(ENABLE_ADDRB_7_net), .B(WEBP), .Y(
        BLKB_EN_7_net));
    MX2 MX2_10(.A(QX_TEMPR6_1_net), .B(QX_TEMPR7_1_net), .S(
        BUFF_2_Y), .Y(MX2_10_Y));
    MX2 MX2_164(.A(QX_TEMPR12_11_net), .B(QX_TEMPR13_11_net), .S(
        BUFF_7_Y), .Y(MX2_164_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R15C0.mem") )  RAM_R15C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_15_net), .WEN(BLKA_EN_15_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR15_11_net), 
        .RD10(QX_TEMPR15_10_net), .RD9(QX_TEMPR15_9_net), .RD8(
        QX_TEMPR15_8_net), .RD7(QX_TEMPR15_7_net), .RD6(
        QX_TEMPR15_6_net), .RD5(QX_TEMPR15_5_net), .RD4(
        QX_TEMPR15_4_net), .RD3(QX_TEMPR15_3_net), .RD2(
        QX_TEMPR15_2_net), .RD1(QX_TEMPR15_1_net), .RD0(
        QX_TEMPR15_0_net));
    MX2 MX2_160(.A(QX_TEMPR12_5_net), .B(QX_TEMPR13_5_net), .S(
        BUFF_12_Y), .Y(MX2_160_Y));
    BUFF BUFF_17(.A(ADDRB_FF2_2_net), .Y(BUFF_17_Y));
    NAND2 NAND2_ENABLE_ADDRA_14_inst(.A(AND2A_4_Y), .B(AND2_1_Y), 
        .Y(ENABLE_ADDRA_14_net));
    MX2 MX2_42(.A(QX_TEMPR0_6_net), .B(QX_TEMPR1_6_net), .S(
        BUFF_12_Y), .Y(MX2_42_Y));
    MX2 MX2_51(.A(MX2_83_Y), .B(MX2_33_Y), .S(BUFF_18_Y), .Y(
        MX2_51_Y));
    MX2 MX2_29(.A(QX_TEMPR12_4_net), .B(QX_TEMPR13_4_net), .S(
        BUFF_14_Y), .Y(MX2_29_Y));
    MX2 MX2_37(.A(QX_TEMPR2_6_net), .B(QX_TEMPR3_6_net), .S(
        BUFF_12_Y), .Y(MX2_37_Y));
    MX2 MX2_113(.A(MX2_12_Y), .B(MX2_144_Y), .S(BUFF_8_Y), .Y(
        MX2_113_Y));
    MX2 MX2_102(.A(MX2_13_Y), .B(MX2_71_Y), .S(BUFF_18_Y), .Y(
        MX2_102_Y));
    AND2 AND2_0(.A(RADDR[9]), .B(RADDR[8]), .Y(AND2_0_Y));
    MX2 MX2_156(.A(QX_TEMPR4_8_net), .B(QX_TEMPR5_8_net), .S(
        BUFF_1_Y), .Y(MX2_156_Y));
    MX2 MX2_134(.A(QX_TEMPR14_4_net), .B(QX_TEMPR15_4_net), .S(
        BUFF_14_Y), .Y(MX2_134_Y));
    BUFF BUFF_3(.A(ADDRB_FF2_1_net), .Y(BUFF_3_Y));
    MX2 MX2_97(.A(MX2_153_Y), .B(MX2_70_Y), .S(BUFF_18_Y), .Y(
        MX2_97_Y));
    MX2 MX2_130(.A(MX2_94_Y), .B(MX2_142_Y), .S(BUFF_15_Y), .Y(
        MX2_130_Y));
    MX2 MX2_139(.A(MX2_84_Y), .B(MX2_46_Y), .S(BUFF_15_Y), .Y(
        MX2_139_Y));
    NAND2 NAND2_ENABLE_ADDRB_5_inst(.A(AND2A_6_Y), .B(AND2A_3_Y), 
        .Y(ENABLE_ADDRB_5_net));
    MX2 MX2_24(.A(QX_TEMPR12_6_net), .B(QX_TEMPR13_6_net), .S(
        BUFF_12_Y), .Y(MX2_24_Y));
    OR2 ORA_GATE_10_inst(.A(ENABLE_ADDRA_10_net), .B(WEAP), .Y(
        BLKA_EN_10_net));
    MX2 MX2_111(.A(QX_TEMPR10_9_net), .B(QX_TEMPR11_9_net), .S(
        BUFF_6_Y), .Y(MX2_111_Y));
    MX2 MX2_48(.A(MX2_113_Y), .B(MX2_136_Y), .S(BUFF_17_Y), .Y(
        MX2_48_Y));
    NAND2 NAND2_ENABLE_ADDRA_13_inst(.A(AND2A_2_Y), .B(AND2_1_Y), 
        .Y(ENABLE_ADDRA_13_net));
    NAND2 NAND2_ENABLE_ADDRA_2_inst(.A(AND2A_4_Y), .B(NOR2_1_Y), 
        .Y(ENABLE_ADDRA_2_net));
    MX2 MX2_128(.A(QX_TEMPR8_10_net), .B(QX_TEMPR9_10_net), .S(
        BUFF_6_Y), .Y(MX2_128_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R1C0.mem") )  RAM_R1C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_1_net), .WEN(BLKA_EN_1_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR1_11_net), .RD10(
        QX_TEMPR1_10_net), .RD9(QX_TEMPR1_9_net), .RD8(
        QX_TEMPR1_8_net), .RD7(QX_TEMPR1_7_net), .RD6(
        QX_TEMPR1_6_net), .RD5(QX_TEMPR1_5_net), .RD4(
        QX_TEMPR1_4_net), .RD3(QX_TEMPR1_3_net), .RD2(
        QX_TEMPR1_2_net), .RD1(QX_TEMPR1_1_net), .RD0(
        QX_TEMPR1_0_net));
    MX2 MX2_55(.A(QX_TEMPR8_2_net), .B(QX_TEMPR9_2_net), .S(
        BUFF_2_Y), .Y(MX2_55_Y));
    MX2 MX2_153(.A(QX_TEMPR4_9_net), .B(QX_TEMPR5_9_net), .S(
        BUFF_1_Y), .Y(MX2_153_Y));
    OR2 ORA_GATE_11_inst(.A(ENABLE_ADDRA_11_net), .B(WEAP), .Y(
        BLKA_EN_11_net));
    NAND2 NAND2_ENABLE_ADDRB_1_inst(.A(AND2A_6_Y), .B(NOR2_3_Y), 
        .Y(ENABLE_ADDRB_1_net));
    MX2 MX2_127(.A(QX_TEMPR2_3_net), .B(QX_TEMPR3_3_net), .S(
        BUFF_13_Y), .Y(MX2_127_Y));
    MX2 MX2_46(.A(MX2_78_Y), .B(MX2_31_Y), .S(BUFF_3_Y), .Y(
        MX2_46_Y));
    DFN1 BFF1_3_inst(.D(RADDR[11]), .CLK(RCLK), .Q(
        ADDRB_FF2_3_net));
    MX2 MX2_106(.A(QX_TEMPR14_5_net), .B(QX_TEMPR15_5_net), .S(
        BUFF_12_Y), .Y(MX2_106_Y));
    BUFF BUFF_15(.A(ADDRB_FF2_2_net), .Y(BUFF_15_Y));
    MX2 MX2_69(.A(QX_TEMPR4_2_net), .B(QX_TEMPR5_2_net), .S(
        BUFF_2_Y), .Y(MX2_69_Y));
    BUFF BUFF_4(.A(ADDRB_FF2_0_net), .Y(BUFF_4_Y));
    MX2 MX2_151(.A(QX_TEMPR2_2_net), .B(QX_TEMPR3_2_net), .S(
        BUFF_2_Y), .Y(MX2_151_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R6C0.mem") )  RAM_R6C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_6_net), .WEN(BLKA_EN_6_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR6_11_net), .RD10(
        QX_TEMPR6_10_net), .RD9(QX_TEMPR6_9_net), .RD8(
        QX_TEMPR6_8_net), .RD7(QX_TEMPR6_7_net), .RD6(
        QX_TEMPR6_6_net), .RD5(QX_TEMPR6_5_net), .RD4(
        QX_TEMPR6_4_net), .RD3(QX_TEMPR6_3_net), .RD2(
        QX_TEMPR6_2_net), .RD1(QX_TEMPR6_1_net), .RD0(
        QX_TEMPR6_0_net));
    NAND2 NAND2_ENABLE_ADDRA_9_inst(.A(AND2A_2_Y), .B(AND2A_1_Y), 
        .Y(ENABLE_ADDRA_9_net));
    DFN1 AFF1_2_inst(.D(WADDR[10]), .CLK(WCLK), .Q(
        ADDRA_FF2_2_net));
    NAND2 NAND2_ENABLE_ADDRA_4_inst(.A(NOR2_2_Y), .B(AND2A_0_Y), 
        .Y(ENABLE_ADDRA_4_net));
    OR2 ORB_GATE_1_inst(.A(ENABLE_ADDRB_1_net), .B(WEBP), .Y(
        BLKB_EN_1_net));
    MX2 MX2_4(.A(QX_TEMPR0_9_net), .B(QX_TEMPR1_9_net), .S(
        BUFF_1_Y), .Y(MX2_4_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R3C0.mem") )  RAM_R3C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_3_net), .WEN(BLKA_EN_3_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR3_11_net), .RD10(
        QX_TEMPR3_10_net), .RD9(QX_TEMPR3_9_net), .RD8(
        QX_TEMPR3_8_net), .RD7(QX_TEMPR3_7_net), .RD6(
        QX_TEMPR3_6_net), .RD5(QX_TEMPR3_5_net), .RD4(
        QX_TEMPR3_4_net), .RD3(QX_TEMPR3_3_net), .RD2(
        QX_TEMPR3_2_net), .RD1(QX_TEMPR3_1_net), .RD0(
        QX_TEMPR3_0_net));
    MX2 MX2_79(.A(QX_TEMPR14_11_net), .B(QX_TEMPR15_11_net), .S(
        BUFF_7_Y), .Y(MX2_79_Y));
    MX2 MX2_43(.A(QX_TEMPR10_2_net), .B(QX_TEMPR11_2_net), .S(
        BUFF_2_Y), .Y(MX2_43_Y));
    BUFF BUFF_13(.A(ADDRB_FF2_0_net), .Y(BUFF_13_Y));
    MX2 MX2_50(.A(MX2_145_Y), .B(MX2_97_Y), .S(BUFF_10_Y), .Y(
        MX2_50_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R10C0.mem") )  RAM_R10C0(
        .RADDR8(GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), 
        .RADDR5(RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), 
        .RADDR2(RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), 
        .WADDR8(GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), 
        .WADDR5(WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), 
        .WADDR2(WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), 
        .WD17(GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND)
        , .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_10_net), .WEN(BLKA_EN_10_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR10_11_net), 
        .RD10(QX_TEMPR10_10_net), .RD9(QX_TEMPR10_9_net), .RD8(
        QX_TEMPR10_8_net), .RD7(QX_TEMPR10_7_net), .RD6(
        QX_TEMPR10_6_net), .RD5(QX_TEMPR10_5_net), .RD4(
        QX_TEMPR10_4_net), .RD3(QX_TEMPR10_3_net), .RD2(
        QX_TEMPR10_2_net), .RD1(QX_TEMPR10_1_net), .RD0(
        QX_TEMPR10_0_net));
    MX2 MX2_145(.A(MX2_4_Y), .B(MX2_104_Y), .S(BUFF_18_Y), .Y(
        MX2_145_Y));
    MX2 MX2_103(.A(MX2_59_Y), .B(MX2_120_Y), .S(BUFF_18_Y), .Y(
        MX2_103_Y));
    NAND2 NAND2_ENABLE_ADDRB_8_inst(.A(NOR2_0_Y), .B(AND2A_5_Y), 
        .Y(ENABLE_ADDRB_8_net));
    MX2 MX2_64(.A(QX_TEMPR0_0_net), .B(QX_TEMPR1_0_net), .S(
        BUFF_11_Y), .Y(MX2_64_Y));
    MX2 MX2_12(.A(QX_TEMPR8_5_net), .B(QX_TEMPR9_5_net), .S(
        BUFF_12_Y), .Y(MX2_12_Y));
    MX2 MX2_39(.A(MX2_53_Y), .B(MX2_8_Y), .S(BUFF_16_Y), .Y(
        MX2_39_Y));
    MX2 MX2_74(.A(QX_TEMPR14_9_net), .B(QX_TEMPR15_9_net), .S(
        BUFF_6_Y), .Y(MX2_74_Y));
    MX2 MX2_167(.A(QX_TEMPR2_10_net), .B(QX_TEMPR3_10_net), .S(
        BUFF_6_Y), .Y(MX2_167_Y));
    MX2 MX2_RD_4_inst(.A(MX2_89_Y), .B(MX2_87_Y), .S(BUFF_0_Y), 
        .Y(RD[4]));
    MX2 MX2_81(.A(MX2_135_Y), .B(MX2_28_Y), .S(BUFF_10_Y), .Y(
        MX2_81_Y));
    MX2 MX2_101(.A(QX_TEMPR8_7_net), .B(QX_TEMPR9_7_net), .S(
        BUFF_4_Y), .Y(MX2_101_Y));
    MX2 MX2_122(.A(MX2_73_Y), .B(MX2_21_Y), .S(BUFF_15_Y), .Y(
        MX2_122_Y));
    NAND2 NAND2_ENABLE_ADDRA_3_inst(.A(AND2_2_Y), .B(NOR2_1_Y), 
        .Y(ENABLE_ADDRA_3_net));
    NAND2 NAND2_ENABLE_ADDRB_3_inst(.A(AND2_0_Y), .B(NOR2_3_Y), 
        .Y(ENABLE_ADDRB_3_net));
    OR2 ORA_GATE_6_inst(.A(ENABLE_ADDRA_6_net), .B(WEAP), .Y(
        BLKA_EN_6_net));
    MX2 MX2_99(.A(QX_TEMPR6_3_net), .B(QX_TEMPR7_3_net), .S(
        BUFF_13_Y), .Y(MX2_99_Y));
    MX2 MX2_47(.A(QX_TEMPR10_10_net), .B(QX_TEMPR11_10_net), .S(
        BUFF_6_Y), .Y(MX2_47_Y));
    NAND2 NAND2_ENABLE_ADDRA_5_inst(.A(AND2A_2_Y), .B(AND2A_0_Y), 
        .Y(ENABLE_ADDRA_5_net));
    MX2 MX2_34(.A(MX2_161_Y), .B(MX2_108_Y), .S(BUFF_15_Y), .Y(
        MX2_34_Y));
    OR2 ORB_GATE_3_inst(.A(ENABLE_ADDRB_3_net), .B(WEBP), .Y(
        BLKB_EN_3_net));
    MX2 MX2_138(.A(MX2_19_Y), .B(MX2_99_Y), .S(BUFF_16_Y), .Y(
        MX2_138_Y));
    MX2 MX2_18(.A(QX_TEMPR12_10_net), .B(QX_TEMPR13_10_net), .S(
        BUFF_7_Y), .Y(MX2_18_Y));
    RAM512X18 #( .MEMORYFILE("RAM_R7C0.mem") )  RAM_R7C0(.RADDR8(
        GND), .RADDR7(RADDR[7]), .RADDR6(RADDR[6]), .RADDR5(
        RADDR[5]), .RADDR4(RADDR[4]), .RADDR3(RADDR[3]), .RADDR2(
        RADDR[2]), .RADDR1(RADDR[1]), .RADDR0(RADDR[0]), .WADDR8(
        GND), .WADDR7(WADDR[7]), .WADDR6(WADDR[6]), .WADDR5(
        WADDR[5]), .WADDR4(WADDR[4]), .WADDR3(WADDR[3]), .WADDR2(
        WADDR[2]), .WADDR1(WADDR[1]), .WADDR0(WADDR[0]), .WD17(
        GND), .WD16(GND), .WD15(GND), .WD14(GND), .WD13(GND), 
        .WD12(GND), .WD11(WD[11]), .WD10(WD[10]), .WD9(WD[9]), 
        .WD8(WD[8]), .WD7(WD[7]), .WD6(WD[6]), .WD5(WD[5]), .WD4(
        WD[4]), .WD3(WD[3]), .WD2(WD[2]), .WD1(WD[1]), .WD0(WD[0])
        , .RW0(GND), .RW1(VCC), .WW0(GND), .WW1(VCC), .PIPE(GND), 
        .REN(BLKB_EN_7_net), .WEN(BLKA_EN_7_net), .RCLK(RCLK), 
        .WCLK(WCLK), .RESET(RESET), .RD17(), .RD16(), .RD15(), 
        .RD14(), .RD13(), .RD12(), .RD11(QX_TEMPR7_11_net), .RD10(
        QX_TEMPR7_10_net), .RD9(QX_TEMPR7_9_net), .RD8(
        QX_TEMPR7_8_net), .RD7(QX_TEMPR7_7_net), .RD6(
        QX_TEMPR7_6_net), .RD5(QX_TEMPR7_5_net), .RD4(
        QX_TEMPR7_4_net), .RD3(QX_TEMPR7_3_net), .RD2(
        QX_TEMPR7_2_net), .RD1(QX_TEMPR7_1_net), .RD0(
        QX_TEMPR7_0_net));
    BUFF BUFF_11(.A(ADDRB_FF2_0_net), .Y(BUFF_11_Y));
    MX2 MX2_137(.A(QX_TEMPR8_4_net), .B(QX_TEMPR9_4_net), .S(
        BUFF_14_Y), .Y(MX2_137_Y));
    OR2 ORA_GATE_13_inst(.A(ENABLE_ADDRA_13_net), .B(WEAP), .Y(
        BLKA_EN_13_net));
    DFN1 AFF1_0_inst(.D(WADDR[8]), .CLK(WCLK), .Q(ADDRA_FF2_0_net)
        );
    NAND2 NAND2_ENABLE_ADDRA_12_inst(.A(NOR2_2_Y), .B(AND2_1_Y), 
        .Y(ENABLE_ADDRA_12_net));
    MX2 MX2_94(.A(MX2_129_Y), .B(MX2_17_Y), .S(BUFF_3_Y), .Y(
        MX2_94_Y));
    MX2 MX2_RD_2_inst(.A(MX2_122_Y), .B(MX2_118_Y), .S(BUFF_0_Y), 
        .Y(RD[2]));
    DFN1 AFF1_1_inst(.D(WADDR[9]), .CLK(WCLK), .Q(ADDRA_FF2_1_net)
        );
    MX2 MX2_RD_0_inst(.A(MX2_165_Y), .B(MX2_34_Y), .S(BUFF_0_Y), 
        .Y(RD[0]));
    MX2 MX2_16(.A(MX2_3_Y), .B(MX2_167_Y), .S(BUFF_5_Y), .Y(
        MX2_16_Y));
    OR2 ORA_GATE_8_inst(.A(ENABLE_ADDRA_8_net), .B(WEAP), .Y(
        BLKA_EN_8_net));
    MX2 MX2_85(.A(QX_TEMPR14_3_net), .B(QX_TEMPR15_3_net), .S(
        BUFF_13_Y), .Y(MX2_85_Y));
    BUFF BUFF_18(.A(ADDRB_FF2_1_net), .Y(BUFF_18_Y));
    OR2 ORB_GATE_10_inst(.A(ENABLE_ADDRB_10_net), .B(WEBP), .Y(
        BLKB_EN_10_net));
    MX2 MX2_126(.A(QX_TEMPR6_10_net), .B(QX_TEMPR7_10_net), .S(
        BUFF_6_Y), .Y(MX2_126_Y));
    BUFF BUFF_1(.A(ADDRB_FF2_0_net), .Y(BUFF_1_Y));
    MX2 MX2_162(.A(MX2_22_Y), .B(MX2_111_Y), .S(BUFF_18_Y), .Y(
        MX2_162_Y));
    MX2 MX2_1(.A(QX_TEMPR10_6_net), .B(QX_TEMPR11_6_net), .S(
        BUFF_12_Y), .Y(MX2_1_Y));
    OR2 ORB_GATE_5_inst(.A(ENABLE_ADDRB_5_net), .B(WEBP), .Y(
        BLKB_EN_5_net));
    MX2 MX2_13(.A(QX_TEMPR8_8_net), .B(QX_TEMPR9_8_net), .S(
        BUFF_1_Y), .Y(MX2_13_Y));
    OR2 ORB_GATE_2_inst(.A(ENABLE_ADDRB_2_net), .B(WEBP), .Y(
        BLKB_EN_2_net));
    MX2 MX2_144(.A(QX_TEMPR10_5_net), .B(QX_TEMPR11_5_net), .S(
        BUFF_12_Y), .Y(MX2_144_Y));
    MX2 MX2_140(.A(MX2_14_Y), .B(MX2_147_Y), .S(BUFF_17_Y), .Y(
        MX2_140_Y));
    MX2 MX2_149(.A(MX2_75_Y), .B(MX2_127_Y), .S(BUFF_16_Y), .Y(
        MX2_149_Y));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:9.1.0.18
// ACTGENU_CALL:1
// BATCH:T
// FAM:ProASIC3
// OUTFORMAT:Verilog
// LPMTYPE:LPM_RAM
// LPM_HINT:TWO
// INSERT_PAD:NO
// INSERT_IOREG:NO
// GEN_BHV_VHDL_VAL:F
// GEN_BHV_VERILOG_VAL:F
// MGNTIMER:F
// MGNCMPL:T
// DESDIR:E:/E/Documents/2D_FPGA_DSP_prjs/2D_NMR_EC_FPGA/2D_FPGA_0509/2D_NMR_EC_FPGA_0509/smartgen\RAM
// GEN_BEHV_MODULE:T
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// WWIDTH:12
// WDEPTH:4096
// RWIDTH:12
// RDEPTH:4096
// CLKS:2
// RESET_PN:RESET
// RESET_POLARITY:0
// INIT_RAM:T
// DEFAULT_WORD:0x000
// CASCADE:1
// WCLK_EDGE:RISE
// RCLK_EDGE:RISE
// WCLOCK_PN:WCLK
// RCLOCK_PN:RCLK
// PMODE2:0
// DATA_IN_PN:WD
// WADDRESS_PN:WADDR
// WE_PN:WEN
// DATA_OUT_PN:RD
// RADDRESS_PN:RADDR
// RE_PN:REN
// WE_POLARITY:1
// RE_POLARITY:1
// PTYPE:1

// _End_Comments_

