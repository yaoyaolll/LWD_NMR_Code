`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module Timer_Inc(DataA,Sum);
input [21:0] DataA;
output [21:0] Sum;

    wire inc_1_net, inc_2_net, Rcout_4_net, Rcout_5_net, 
        inc_5_net, Rcout_6_net, Rcout_7_net, inc_8_net, 
        Rcout_8_net, inc_10_net, incb_2_net, Rcout_9_net, 
        inc_12_net, Rcout_10_net, inc_14_net, Rcout_11_net, 
        inc_16_net, incb_5_net, inc_17_net, Rcout_12_net, 
        Rcout_13_net, inc_20_net, Rcout_14_net, inc_22_net, 
        Rcout_15_net, inc_24_net, Rcout_16_net, inc1_25_net, 
        Rcout_17_net, inc_27_net, incb_16_net, inc_28_net, 
        incb_17_net, Rcout_18_net, Rcout_19_net, inc_31_net, 
        Rcout_20_net, inc_33_net, Rcout_21_net;
    
    XOR2 QXOR2_16_inst(.A(Rcout_20_net), .B(DataA[20]), .Y(
        Sum[20]));
    AND3 AND2_1_12_inst(.A(incb_2_net), .B(incb_5_net), .C(
        inc_10_net), .Y(inc_17_net));
    AND3 SAND2_27_inst(.A(DataA[18]), .B(DataA[19]), .C(DataA[20])
        , .Y(inc_33_net));
    AND3 SAND2_28_inst(.A(incb_17_net), .B(inc_28_net), .C(
        inc_33_net), .Y(Rcout_21_net));
    AND2 QAND2_25_inst(.A(DataA[18]), .B(DataA[19]), .Y(
        inc_31_net));
    XOR2 SXOR2_17_inst(.A(Rcout_21_net), .B(DataA[21]), .Y(
        Sum[21]));
    XOR2 OXOR2_15_inst(.A(Rcout_19_net), .B(DataA[19]), .Y(
        Sum[19]));
    AND3 AND2_6_inst(.A(DataA[3]), .B(DataA[4]), .C(DataA[5]), .Y(
        inc_5_net));
    XOR2 HOR2_10_inst(.A(Rcout_13_net), .B(DataA[13]), .Y(Sum[13])
        );
    AND3 YAND2BB_21_inst(.A(DataA[9]), .B(DataA[10]), .C(
        DataA[11]), .Y(incb_16_net));
    AND3 QAND2_26_inst(.A(incb_17_net), .B(inc_28_net), .C(
        inc_31_net), .Y(Rcout_20_net));
    AND3 AND2_10_inst(.A(incb_2_net), .B(DataA[9]), .C(DataA[10]), 
        .Y(inc_14_net));
    XOR2 XOR2_5_inst(.A(Rcout_6_net), .B(DataA[6]), .Y(Sum[6]));
    AND3 AND2_15_inst(.A(inc_16_net), .B(inc_17_net), .C(
        inc_20_net), .Y(Rcout_14_net));
    XOR2 XOR2_2_inst(.A(inc_2_net), .B(DataA[3]), .Y(Sum[3]));
    XOR2 XOR2_6_inst(.A(Rcout_8_net), .B(DataA[8]), .Y(Sum[8]));
    XOR2 XOR2_4_inst(.A(Rcout_5_net), .B(DataA[5]), .Y(Sum[5]));
    XOR2 PXOR2_13_inst(.A(Rcout_17_net), .B(DataA[17]), .Y(
        Sum[17]));
    AND3 AND2_1_7_inst(.A(inc_2_net), .B(inc_5_net), .C(DataA[6]), 
        .Y(Rcout_7_net));
    AND3 FND2_9_inst(.A(inc_12_net), .B(inc_5_net), .C(inc_10_net)
        , .Y(Rcout_10_net));
    AND3 AND2b_9_inst(.A(DataA[0]), .B(DataA[1]), .C(DataA[2]), 
        .Y(incb_2_net));
    AND2 VAND2_17_inst(.A(inc_22_net), .B(inc_16_net), .Y(
        inc_24_net));
    XOR2 POR2_9_inst(.A(Rcout_12_net), .B(DataA[12]), .Y(Sum[12]));
    AND3 VAND2_18_inst(.A(inc_17_net), .B(inc_24_net), .C(
        DataA[15]), .Y(Rcout_16_net));
    AND2 AND2_14_inst(.A(DataA[12]), .B(DataA[13]), .Y(inc_20_net)
        );
    XOR2 XOR2_11_inst(.A(Rcout_14_net), .B(DataA[14]), .Y(Sum[14])
        );
    AND2 AND2_13_inst(.A(inc_17_net), .B(inc_16_net), .Y(
        Rcout_12_net));
    AND3 AND2_11_inst(.A(inc_14_net), .B(inc_5_net), .C(
        inc_10_net), .Y(Rcout_11_net));
    XOR2 XOR2_9_inst(.A(Rcout_11_net), .B(DataA[11]), .Y(Sum[11]));
    XOR2 YXOR2_14_inst(.A(Rcout_18_net), .B(DataA[18]), .Y(
        Sum[18]));
    XOR2 UXOR2_12_inst(.A(Rcout_15_net), .B(DataA[15]), .Y(
        Sum[15]));
    AND3 YAND2_21_inst(.A(DataA[15]), .B(DataA[16]), .C(DataA[17])
        , .Y(inc_27_net));
    AND3 TND2_15_inst(.A(inc_16_net), .B(inc_17_net), .C(
        inc_22_net), .Y(Rcout_15_net));
    XOR2 XOR2_1_inst(.A(DataA[0]), .B(DataA[1]), .Y(Sum[1]));
    AND3 AND2_9_inst(.A(DataA[6]), .B(DataA[7]), .C(DataA[8]), .Y(
        inc_10_net));
    AND3 AND2b_12_inst(.A(DataA[3]), .B(DataA[4]), .C(DataA[5]), 
        .Y(incb_5_net));
    AND3 PAND2_19_inst(.A(inc_22_net), .B(inc_16_net), .C(
        DataA[16]), .Y(inc1_25_net));
    XOR2 FOR2_8_inst(.A(Rcout_10_net), .B(DataA[10]), .Y(Sum[10]));
    XOR2 XOR2_7_inst(.A(Rcout_9_net), .B(DataA[9]), .Y(Sum[9]));
    AND3 TAND2_15_inst(.A(DataA[12]), .B(DataA[13]), .C(DataA[14])
        , .Y(inc_22_net));
    AND3 HND2_13_inst(.A(inc_17_net), .B(inc_16_net), .C(
        DataA[12]), .Y(Rcout_13_net));
    AND2 FND2_8_inst(.A(incb_2_net), .B(DataA[9]), .Y(inc_12_net));
    AND3 YAND2B_22_inst(.A(incb_2_net), .B(incb_5_net), .C(
        inc_10_net), .Y(incb_17_net));
    XOR2 XOR2_2_1_inst(.A(inc_1_net), .B(DataA[2]), .Y(Sum[2]));
    AND3 fAND2_8_inst(.A(incb_2_net), .B(inc_5_net), .C(
        inc_10_net), .Y(Rcout_9_net));
    AND3 OAND2_24_inst(.A(incb_17_net), .B(inc_28_net), .C(
        DataA[18]), .Y(Rcout_19_net));
    AND3 YAND2_22_inst(.A(incb_16_net), .B(inc_22_net), .C(
        inc_27_net), .Y(inc_28_net));
    AND2 YAND2_23_inst(.A(incb_17_net), .B(inc_28_net), .Y(
        Rcout_18_net));
    AND3 AND2_12_inst(.A(DataA[9]), .B(DataA[10]), .C(DataA[11]), 
        .Y(inc_16_net));
    AND3 PAND2_20_inst(.A(inc_17_net), .B(inc1_25_net), .C(
        DataA[15]), .Y(Rcout_17_net));
    XOR2 XOR2_1_5_inst(.A(Rcout_7_net), .B(DataA[7]), .Y(Sum[7]));
    INV INV_0_inst(.A(DataA[0]), .Y(Sum[0]));
    AND3 AND2_1_8_inst(.A(inc_2_net), .B(inc_5_net), .C(inc_8_net)
        , .Y(Rcout_8_net));
    AND2 AND2_2_inst(.A(DataA[0]), .B(DataA[1]), .Y(inc_1_net));
    AND2 AND2_8_inst(.A(DataA[6]), .B(DataA[7]), .Y(inc_8_net));
    XOR2 VXOR2_13_inst(.A(Rcout_16_net), .B(DataA[16]), .Y(
        Sum[16]));
    AND3 AND2_5_inst(.A(inc_2_net), .B(DataA[3]), .C(DataA[4]), 
        .Y(Rcout_5_net));
    AND2 AND2_4_inst(.A(inc_2_net), .B(DataA[3]), .Y(Rcout_4_net));
    AND3 AND2_3_inst(.A(DataA[0]), .B(DataA[1]), .C(DataA[2]), .Y(
        inc_2_net));
    AND2 AND2_7_inst(.A(inc_2_net), .B(inc_5_net), .Y(Rcout_6_net)
        );
    XOR2 XOR2_3_inst(.A(Rcout_4_net), .B(DataA[4]), .Y(Sum[4]));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:9.1.0.18
// ACTGENU_CALL:1
// BATCH:T
// FAM:ProASIC3
// OUTFORMAT:Verilog
// LPMTYPE:LPM_ADD_SUB
// LPM_HINT:FINC
// INSERT_PAD:NO
// INSERT_IOREG:NO
// GEN_BHV_VHDL_VAL:F
// GEN_BHV_VERILOG_VAL:F
// MGNTIMER:F
// MGNCMPL:T
// DESDIR:D:/E/2D_FPGA_DSP_prjs/2D_NMR_EC_FPGA/2D_NMR_EC_FPGA_PQFP208_0414/smartgen\Timer_Inc
// GEN_BEHV_MODULE:T
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// CO_POLARITY:2
// WIDTH:22
// DEBUG:0

// _End_Comments_

