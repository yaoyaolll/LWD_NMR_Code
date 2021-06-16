`timescale 1 ns/100 ps
// Version: 9.1 SP5 9.1.5.1


module necount_cmp(DataA,DataB,ALEB);
input [10:0] DataA, DataB;
output  ALEB;

    wire AND3_0_Y, AO1_0_Y, AO1_1_Y, AND3_2_Y, NAND3A_0_Y, 
        NAND3A_4_Y, OR2A_1_Y, AO1C_0_Y, NOR3A_2_Y, OR2A_4_Y, 
        NAND3A_5_Y, OR2A_0_Y, AO1C_2_Y, NOR3A_0_Y, OR2A_5_Y, 
        NAND3A_2_Y, XNOR2_0_Y, XNOR2_9_Y, XNOR2_7_Y, AND2_0_Y, 
        NOR3_0_Y, NAND3A_1_Y, OR2A_2_Y, AO1C_1_Y, NOR3A_1_Y, 
        OR2A_3_Y, NAND3A_3_Y, OA1A_0_Y, AND2A_0_Y, OA1C_0_Y, 
        XNOR2_2_Y, XNOR2_1_Y, XNOR2_8_Y, XNOR2_5_Y, XNOR2_3_Y, 
        XNOR2_6_Y, XNOR2_4_Y, AND3_1_Y;
    
    AO1C AO1C_2(.A(DataA[4]), .B(DataB[4]), .C(DataA[3]), .Y(
        AO1C_2_Y));
    AND3 AND3_2(.A(XNOR2_0_Y), .B(XNOR2_9_Y), .C(XNOR2_7_Y), .Y(
        AND3_2_Y));
    NOR3 NOR3_0(.A(OA1A_0_Y), .B(AND2A_0_Y), .C(OA1C_0_Y), .Y(
        NOR3_0_Y));
    NOR3A NOR3A_1(.A(OR2A_2_Y), .B(AO1C_1_Y), .C(DataB[6]), .Y(
        NOR3A_1_Y));
    AND2 AND2_0(.A(XNOR2_2_Y), .B(XNOR2_1_Y), .Y(AND2_0_Y));
    NOR3A NOR3A_0(.A(OR2A_0_Y), .B(AO1C_2_Y), .C(DataB[3]), .Y(
        NOR3A_0_Y));
    XNOR2 XNOR2_3(.A(DataA[8]), .B(DataB[8]), .Y(XNOR2_3_Y));
    NOR3A NOR3A_2(.A(OR2A_1_Y), .B(AO1C_0_Y), .C(DataB[0]), .Y(
        NOR3A_2_Y));
    XNOR2 XNOR2_5(.A(DataA[7]), .B(DataB[7]), .Y(XNOR2_5_Y));
    NAND3A NAND3A_5(.A(DataB[1]), .B(DataA[1]), .C(OR2A_1_Y), .Y(
        NAND3A_5_Y));
    NAND3A NAND3A_2(.A(DataB[4]), .B(DataA[4]), .C(OR2A_0_Y), .Y(
        NAND3A_2_Y));
    AOI1 AOI1_ALEB(.A(AND3_0_Y), .B(AO1_1_Y), .C(AO1_0_Y), .Y(
        ALEB));
    AO1C AO1C_0(.A(DataA[1]), .B(DataB[1]), .C(DataA[0]), .Y(
        AO1C_0_Y));
    OR2A OR2A_5(.A(DataA[5]), .B(DataB[5]), .Y(OR2A_5_Y));
    AND3 AND3_0(.A(AND3_1_Y), .B(XNOR2_6_Y), .C(XNOR2_4_Y), .Y(
        AND3_0_Y));
    NAND3A NAND3A_3(.A(DataB[7]), .B(DataA[7]), .C(OR2A_2_Y), .Y(
        NAND3A_3_Y));
    OR2A OR2A_0(.A(DataB[5]), .B(DataA[5]), .Y(OR2A_0_Y));
    AND3 AND3_1(.A(XNOR2_8_Y), .B(XNOR2_5_Y), .C(XNOR2_3_Y), .Y(
        AND3_1_Y));
    XNOR2 XNOR2_8(.A(DataA[6]), .B(DataB[6]), .Y(XNOR2_8_Y));
    NAND3A NAND3A_1(.A(NOR3A_1_Y), .B(OR2A_3_Y), .C(NAND3A_3_Y), 
        .Y(NAND3A_1_Y));
    XNOR2 XNOR2_4(.A(DataA[10]), .B(DataB[10]), .Y(XNOR2_4_Y));
    AO1 AO1_1(.A(AND3_2_Y), .B(NAND3A_4_Y), .C(NAND3A_0_Y), .Y(
        AO1_1_Y));
    XNOR2 XNOR2_9(.A(DataB[4]), .B(DataA[4]), .Y(XNOR2_9_Y));
    AO1C AO1C_1(.A(DataA[7]), .B(DataB[7]), .C(DataA[6]), .Y(
        AO1C_1_Y));
    OR2A OR2A_3(.A(DataA[8]), .B(DataB[8]), .Y(OR2A_3_Y));
    XNOR2 XNOR2_0(.A(DataB[3]), .B(DataA[3]), .Y(XNOR2_0_Y));
    XNOR2 XNOR2_2(.A(DataB[9]), .B(DataA[9]), .Y(XNOR2_2_Y));
    OR2A OR2A_2(.A(DataB[8]), .B(DataA[8]), .Y(OR2A_2_Y));
    NAND3A NAND3A_0(.A(NOR3A_0_Y), .B(OR2A_5_Y), .C(NAND3A_2_Y), 
        .Y(NAND3A_0_Y));
    AO1 AO1_0(.A(AND2_0_Y), .B(NAND3A_1_Y), .C(NOR3_0_Y), .Y(
        AO1_0_Y));
    XNOR2 XNOR2_7(.A(DataB[5]), .B(DataA[5]), .Y(XNOR2_7_Y));
    OA1C OA1C_0(.A(DataA[9]), .B(DataB[9]), .C(DataA[10]), .Y(
        OA1C_0_Y));
    OR2A OR2A_1(.A(DataB[2]), .B(DataA[2]), .Y(OR2A_1_Y));
    AND2A AND2A_0(.A(DataA[10]), .B(DataB[10]), .Y(AND2A_0_Y));
    XNOR2 XNOR2_6(.A(DataA[9]), .B(DataB[9]), .Y(XNOR2_6_Y));
    XNOR2 XNOR2_1(.A(DataB[10]), .B(DataA[10]), .Y(XNOR2_1_Y));
    OR2A OR2A_4(.A(DataA[2]), .B(DataB[2]), .Y(OR2A_4_Y));
    NAND3A NAND3A_4(.A(NOR3A_2_Y), .B(OR2A_4_Y), .C(NAND3A_5_Y), 
        .Y(NAND3A_4_Y));
    OA1A OA1A_0(.A(DataA[9]), .B(DataB[9]), .C(DataB[10]), .Y(
        OA1A_0_Y));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:9.1.5.1
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
// DESDIR:C:/Users/Administrator/Desktop/2D_NMR_EC_FPGA_150130/smartgen\necount_cmp
// GEN_BEHV_MODULE:T
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// WIDTH:11
// REPRESENTATION:UNSIGNED
// GEQRHS_POLARITY:1
// ALEB_POLARITY:1

// _End_Comments_

