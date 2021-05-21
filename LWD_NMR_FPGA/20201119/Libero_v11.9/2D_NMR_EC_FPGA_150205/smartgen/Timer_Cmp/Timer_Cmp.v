`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module Timer_Cmp(DataA,DataB,AGB);
input [21:0] DataA, DataB;
output  AGB;

    wire AND2_0_Y, AO1_1_Y, AO1_2_Y, AND3_5_Y, AO1_0_Y, AO1_4_Y, 
        AND3_2_Y, NAND3A_5_Y, NAND3A_9_Y, OR2A_2_Y, AO1C_1_Y, 
        NOR3A_3_Y, OR2A_4_Y, NAND3A_10_Y, OR2A_10_Y, AO1C_9_Y, 
        NOR3A_4_Y, OR2A_0_Y, NAND3A_4_Y, XNOR2_3_Y, XNOR2_10_Y, 
        XNOR2_18_Y, AND3_7_Y, NAND3A_6_Y, NAND3A_2_Y, OR2A_5_Y, 
        AO1C_7_Y, NOR3A_1_Y, OR2A_1_Y, NAND3A_3_Y, OR2A_12_Y, 
        AO1C_2_Y, NOR3A_0_Y, OR2A_13_Y, NAND3A_11_Y, XNOR2_0_Y, 
        XNOR2_6_Y, XNOR2_16_Y, XNOR2_1_Y, XNOR2_28_Y, XNOR2_22_Y, 
        XNOR2_8_Y, XNOR2_27_Y, XNOR2_13_Y, AND3_8_Y, AND2_2_Y, 
        AND2_1_Y, AO1D_0_Y, AO1_3_Y, AND3_4_Y, NAND3A_8_Y, 
        NAND3A_1_Y, OR2A_8_Y, AO1C_3_Y, NOR3A_5_Y, OR2A_3_Y, 
        NAND3A_7_Y, OR2A_7_Y, AO1C_6_Y, NOR3A_2_Y, OR2A_11_Y, 
        NAND3A_0_Y, XNOR2_19_Y, XNOR2_23_Y, XNOR2_2_Y, OR2A_6_Y, 
        AO1C_10_Y, AO1C_4_Y, OR2A_9_Y, AO1C_5_Y, NOR2A_0_Y, 
        AO1C_0_Y, AO1C_8_Y, XNOR2_7_Y, XNOR2_4_Y, XNOR2_26_Y, 
        XNOR2_15_Y, AND3_9_Y, XNOR2_24_Y, XNOR2_12_Y, XNOR2_9_Y, 
        XNOR2_21_Y, XNOR2_11_Y, XNOR2_17_Y, XNOR2_14_Y, 
        XNOR2_20_Y, XNOR2_5_Y, XNOR2_25_Y, AND3_6_Y, AND3_1_Y, 
        AND3_0_Y, AND3_3_Y;
    
    OR2A OR2A_1(.A(DataA[8]), .B(DataB[8]), .Y(OR2A_1_Y));
    OR2A OR2A_10(.A(DataB[5]), .B(DataA[5]), .Y(OR2A_10_Y));
    XNOR2 XNOR2_3(.A(DataB[3]), .B(DataA[3]), .Y(XNOR2_3_Y));
    AND3 AND3_5(.A(XNOR2_8_Y), .B(AND3_8_Y), .C(AND2_2_Y), .Y(
        AND3_5_Y));
    NAND3A NAND3A_2(.A(NOR3A_1_Y), .B(OR2A_1_Y), .C(NAND3A_3_Y), 
        .Y(NAND3A_2_Y));
    NAND3A NAND3A_6(.A(NOR3A_0_Y), .B(OR2A_13_Y), .C(NAND3A_11_Y), 
        .Y(NAND3A_6_Y));
    NOR3A NOR3A_1(.A(OR2A_5_Y), .B(AO1C_7_Y), .C(DataB[6]), .Y(
        NOR3A_1_Y));
    AND3 AND3_2(.A(XNOR2_3_Y), .B(XNOR2_10_Y), .C(XNOR2_18_Y), .Y(
        AND3_2_Y));
    AO1C AO1C_3(.A(DataA[13]), .B(DataB[13]), .C(DataA[12]), .Y(
        AO1C_3_Y));
    AND2 AND2_0(.A(AND3_1_Y), .B(XNOR2_25_Y), .Y(AND2_0_Y));
    XNOR2 XNOR2_12(.A(DataB[13]), .B(DataA[13]), .Y(XNOR2_12_Y));
    NOR3A NOR3A_2(.A(OR2A_7_Y), .B(AO1C_6_Y), .C(DataB[15]), .Y(
        NOR3A_2_Y));
    NAND3A NAND3A_8(.A(NOR3A_2_Y), .B(OR2A_11_Y), .C(NAND3A_0_Y), 
        .Y(NAND3A_8_Y));
    AO1 AO1_1(.A(AND2_1_Y), .B(AO1_3_Y), .C(AO1D_0_Y), .Y(AO1_1_Y)
        );
    AND3 AND3_9(.A(XNOR2_7_Y), .B(XNOR2_4_Y), .C(XNOR2_26_Y), .Y(
        AND3_9_Y));
    AO1 AO1_4(.A(AND3_2_Y), .B(NAND3A_9_Y), .C(NAND3A_5_Y), .Y(
        AO1_4_Y));
    XNOR2 XNOR2_22(.A(DataB[8]), .B(DataA[8]), .Y(XNOR2_22_Y));
    NAND3A NAND3A_9(.A(NOR3A_3_Y), .B(OR2A_4_Y), .C(NAND3A_10_Y), 
        .Y(NAND3A_9_Y));
    AO1D AO1D_0(.A(AO1C_4_Y), .B(AO1C_5_Y), .C(AO1C_8_Y), .Y(
        AO1D_0_Y));
    AND2 AND2_2(.A(XNOR2_27_Y), .B(XNOR2_13_Y), .Y(AND2_2_Y));
    NAND3A NAND3A_11(.A(DataB[10]), .B(DataA[10]), .C(OR2A_12_Y), 
        .Y(NAND3A_11_Y));
    AO1C AO1C_6(.A(DataA[16]), .B(DataB[16]), .C(DataA[15]), .Y(
        AO1C_6_Y));
    NAND3A NAND3A_4(.A(DataB[4]), .B(DataA[4]), .C(OR2A_10_Y), .Y(
        NAND3A_4_Y));
    AND3 AND3_7(.A(XNOR2_0_Y), .B(XNOR2_6_Y), .C(XNOR2_16_Y), .Y(
        AND3_7_Y));
    AND3 AND3_6(.A(XNOR2_24_Y), .B(XNOR2_12_Y), .C(XNOR2_9_Y), .Y(
        AND3_6_Y));
    AND2 AND2_1(.A(AND3_9_Y), .B(XNOR2_15_Y), .Y(AND2_1_Y));
    XNOR2 XNOR2_18(.A(DataB[5]), .B(DataA[5]), .Y(XNOR2_18_Y));
    XNOR2 XNOR2_9(.A(DataB[14]), .B(DataA[14]), .Y(XNOR2_9_Y));
    OR2A OR2A_12(.A(DataB[11]), .B(DataA[11]), .Y(OR2A_12_Y));
    AO1C AO1C_5(.A(DataA[20]), .B(DataB[20]), .C(OR2A_9_Y), .Y(
        AO1C_5_Y));
    OR2A OR2A_9(.A(DataB[19]), .B(DataA[19]), .Y(OR2A_9_Y));
    AND3 AND3_0(.A(XNOR2_14_Y), .B(XNOR2_20_Y), .C(XNOR2_5_Y), .Y(
        AND3_0_Y));
    NAND3A NAND3A_1(.A(NOR3A_5_Y), .B(OR2A_3_Y), .C(NAND3A_7_Y), 
        .Y(NAND3A_1_Y));
    AND3 AND3_8(.A(XNOR2_1_Y), .B(XNOR2_28_Y), .C(XNOR2_22_Y), .Y(
        AND3_8_Y));
    OR2A OR2A_3(.A(DataA[14]), .B(DataB[14]), .Y(OR2A_3_Y));
    AO1C AO1C_0(.A(DataA[21]), .B(DataB[21]), .C(NOR2A_0_Y), .Y(
        AO1C_0_Y));
    XNOR2 XNOR2_4(.A(DataB[19]), .B(DataA[19]), .Y(XNOR2_4_Y));
    OR2A OR2A_6(.A(DataA[19]), .B(DataB[19]), .Y(OR2A_6_Y));
    XNOR2 XNOR2_28(.A(DataB[7]), .B(DataA[7]), .Y(XNOR2_28_Y));
    AO1 AO1_AGB(.A(AND2_0_Y), .B(AO1_2_Y), .C(AO1_1_Y), .Y(AGB));
    XNOR2 XNOR2_1(.A(DataB[6]), .B(DataA[6]), .Y(XNOR2_1_Y));
    NOR3A NOR3A_4(.A(OR2A_10_Y), .B(AO1C_9_Y), .C(DataB[3]), .Y(
        NOR3A_4_Y));
    XNOR2 XNOR2_8(.A(DataB[9]), .B(DataA[9]), .Y(XNOR2_8_Y));
    XNOR2 XNOR2_5(.A(DataB[20]), .B(DataA[20]), .Y(XNOR2_5_Y));
    XNOR2 XNOR2_16(.A(DataB[11]), .B(DataA[11]), .Y(XNOR2_16_Y));
    XNOR2 XNOR2_15(.A(DataB[21]), .B(DataA[21]), .Y(XNOR2_15_Y));
    AO1 AO1_3(.A(AND3_4_Y), .B(NAND3A_1_Y), .C(NAND3A_8_Y), .Y(
        AO1_3_Y));
    OR2A OR2A_7(.A(DataB[17]), .B(DataA[17]), .Y(OR2A_7_Y));
    XNOR2 XNOR2_6(.A(DataB[10]), .B(DataA[10]), .Y(XNOR2_6_Y));
    XNOR2 XNOR2_10(.A(DataB[4]), .B(DataA[4]), .Y(XNOR2_10_Y));
    NOR3A NOR3A_0(.A(OR2A_12_Y), .B(AO1C_2_Y), .C(DataB[9]), .Y(
        NOR3A_0_Y));
    NAND3A NAND3A_10(.A(DataB[1]), .B(DataA[1]), .C(OR2A_2_Y), .Y(
        NAND3A_10_Y));
    NAND3A NAND3A_3(.A(DataB[7]), .B(DataA[7]), .C(OR2A_5_Y), .Y(
        NAND3A_3_Y));
    XNOR2 XNOR2_14(.A(DataB[18]), .B(DataA[18]), .Y(XNOR2_14_Y));
    XNOR2 XNOR2_2(.A(DataB[17]), .B(DataA[17]), .Y(XNOR2_2_Y));
    XNOR2 XNOR2_17(.A(DataB[17]), .B(DataA[17]), .Y(XNOR2_17_Y));
    AO1C AO1C_9(.A(DataA[4]), .B(DataB[4]), .C(DataA[3]), .Y(
        AO1C_9_Y));
    XNOR2 XNOR2_13(.A(DataB[11]), .B(DataA[11]), .Y(XNOR2_13_Y));
    AO1 AO1_2(.A(AND3_5_Y), .B(AO1_4_Y), .C(AO1_0_Y), .Y(AO1_2_Y));
    OR2A OR2A_13(.A(DataA[11]), .B(DataB[11]), .Y(OR2A_13_Y));
    XNOR2 XNOR2_26(.A(DataB[20]), .B(DataA[20]), .Y(XNOR2_26_Y));
    XNOR2 XNOR2_25(.A(DataB[21]), .B(DataA[21]), .Y(XNOR2_25_Y));
    NAND3A NAND3A_5(.A(NOR3A_4_Y), .B(OR2A_0_Y), .C(NAND3A_4_Y), 
        .Y(NAND3A_5_Y));
    AND3 AND3_3(.A(XNOR2_21_Y), .B(XNOR2_11_Y), .C(XNOR2_17_Y), 
        .Y(AND3_3_Y));
    NOR2A NOR2A_0(.A(DataA[20]), .B(DataB[20]), .Y(NOR2A_0_Y));
    XNOR2 XNOR2_20(.A(DataB[19]), .B(DataA[19]), .Y(XNOR2_20_Y));
    XNOR2 XNOR2_19(.A(DataB[15]), .B(DataA[15]), .Y(XNOR2_19_Y));
    XNOR2 XNOR2_24(.A(DataB[12]), .B(DataA[12]), .Y(XNOR2_24_Y));
    AND3 AND3_1(.A(AND3_0_Y), .B(AND3_6_Y), .C(AND3_3_Y), .Y(
        AND3_1_Y));
    XNOR2 XNOR2_27(.A(DataB[10]), .B(DataA[10]), .Y(XNOR2_27_Y));
    NOR3A NOR3A_5(.A(OR2A_8_Y), .B(AO1C_3_Y), .C(DataB[12]), .Y(
        NOR3A_5_Y));
    XNOR2 XNOR2_23(.A(DataB[16]), .B(DataA[16]), .Y(XNOR2_23_Y));
    NAND3A NAND3A_7(.A(DataB[13]), .B(DataA[13]), .C(OR2A_8_Y), 
        .Y(NAND3A_7_Y));
    OR2A OR2A_8(.A(DataB[14]), .B(DataA[14]), .Y(OR2A_8_Y));
    OR2A OR2A_11(.A(DataA[17]), .B(DataB[17]), .Y(OR2A_11_Y));
    OR2A OR2A_4(.A(DataA[2]), .B(DataB[2]), .Y(OR2A_4_Y));
    AO1C AO1C_8(.A(DataB[21]), .B(DataA[21]), .C(AO1C_0_Y), .Y(
        AO1C_8_Y));
    OR2A OR2A_0(.A(DataA[5]), .B(DataB[5]), .Y(OR2A_0_Y));
    AO1C AO1C_1(.A(DataA[1]), .B(DataB[1]), .C(DataA[0]), .Y(
        AO1C_1_Y));
    XNOR2 XNOR2_11(.A(DataB[16]), .B(DataA[16]), .Y(XNOR2_11_Y));
    AO1C AO1C_7(.A(DataA[7]), .B(DataB[7]), .C(DataA[6]), .Y(
        AO1C_7_Y));
    XNOR2 XNOR2_0(.A(DataB[9]), .B(DataA[9]), .Y(XNOR2_0_Y));
    OR2A OR2A_2(.A(DataB[2]), .B(DataA[2]), .Y(OR2A_2_Y));
    AO1C AO1C_2(.A(DataA[10]), .B(DataB[10]), .C(DataA[9]), .Y(
        AO1C_2_Y));
    OR2A OR2A_5(.A(DataB[8]), .B(DataA[8]), .Y(OR2A_5_Y));
    AO1 AO1_0(.A(AND3_7_Y), .B(NAND3A_2_Y), .C(NAND3A_6_Y), .Y(
        AO1_0_Y));
    AO1C AO1C_10(.A(DataB[18]), .B(DataA[18]), .C(OR2A_6_Y), .Y(
        AO1C_10_Y));
    NOR3A NOR3A_3(.A(OR2A_2_Y), .B(AO1C_1_Y), .C(DataB[0]), .Y(
        NOR3A_3_Y));
    XNOR2 XNOR2_21(.A(DataB[15]), .B(DataA[15]), .Y(XNOR2_21_Y));
    AND3 AND3_4(.A(XNOR2_19_Y), .B(XNOR2_23_Y), .C(XNOR2_2_Y), .Y(
        AND3_4_Y));
    NAND3A NAND3A_0(.A(DataB[16]), .B(DataA[16]), .C(OR2A_7_Y), 
        .Y(NAND3A_0_Y));
    XNOR2 XNOR2_7(.A(DataB[18]), .B(DataA[18]), .Y(XNOR2_7_Y));
    AO1C AO1C_4(.A(DataA[21]), .B(DataB[21]), .C(AO1C_10_Y), .Y(
        AO1C_4_Y));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:9.1.0.18
// ACTGENU_CALL:1
// BATCH:T
// FAM:ProASIC3
// OUTFORMAT:Verilog
// LPMTYPE:LPM_COMPARE
// LPM_HINT:MAGCOMP
// INSERT_PAD:NO
// INSERT_IOREG:NO
// GEN_BHV_VHDL_VAL:F
// GEN_BHV_VERILOG_VAL:F
// MGNTIMER:F
// MGNCMPL:T
// DESDIR:D:/E/2D_FPGA_DSP_prjs/2D_NMR_EC_FPGA/2D_NMR_EC_FPGA_PQFP208_0414/smartgen\Timer_Cmp
// GEN_BEHV_MODULE:T
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// WIDTH:22
// REPRESENTATION:UNSIGNED
// GEQRHS_POLARITY:1
// AGB_POLARITY:1

// _End_Comments_

