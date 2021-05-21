`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module pd_pluse_inc(DataA,Sum,Cout);
input [15:0] DataA;
output [15:0] Sum;
output Cout;

    wire Rcout_16_net, inc_1_net, inc_2_net, Rcout_4_net, 
        Rcout_5_net, inc_5_net, Rcout_6_net, Rcout_7_net, 
        inc_8_net, Rcout_8_net, inc_10_net, incb_2_net, 
        Rcout_9_net, inc_12_net, Rcout_10_net, inc_14_net, 
        Rcout_11_net, inc_16_net, incb_5_net, inc_17_net, 
        Rcout_12_net, Rcout_13_net, inc_20_net, Rcout_14_net, 
        inc_22_net, Rcout_15_net, inc_24_net;
    
    INV INV_cout_16_inst(.A(Rcout_16_net), .Y(Cout));
    AND3 AND2_1_12_inst(.A(incb_2_net), .B(incb_5_net), .C(
        inc_10_net), .Y(inc_17_net));
    XOR2 UXOR2_12_inst(.A(Rcout_15_net), .B(DataA[15]), .Y(
        Sum[15]));
    AND3 AND2_12_inst(.A(DataA[9]), .B(DataA[10]), .C(DataA[11]), 
        .Y(inc_16_net));
    AND3 AND2_10_inst(.A(incb_2_net), .B(DataA[9]), .C(DataA[10]), 
        .Y(inc_14_net));
    XOR2 XOR2_1_5_inst(.A(Rcout_7_net), .B(DataA[7]), .Y(Sum[7]));
    XOR2 HOR2_10_inst(.A(Rcout_13_net), .B(DataA[13]), .Y(Sum[13])
        );
    AND3 AND2_1_8_inst(.A(inc_2_net), .B(inc_5_net), .C(inc_8_net)
        , .Y(Rcout_8_net));
    XOR2 FOR2_8_inst(.A(Rcout_10_net), .B(DataA[10]), .Y(Sum[10]));
    XOR2 XOR2_1_inst(.A(DataA[0]), .B(DataA[1]), .Y(Sum[1]));
    XOR2 POR2_9_inst(.A(Rcout_12_net), .B(DataA[12]), .Y(Sum[12]));
    AND3 AND2b_9_inst(.A(DataA[0]), .B(DataA[1]), .C(DataA[2]), 
        .Y(incb_2_net));
    AND3 AND2_1_7_inst(.A(inc_2_net), .B(inc_5_net), .C(DataA[6]), 
        .Y(Rcout_7_net));
    AND2 AND2_8_inst(.A(DataA[6]), .B(DataA[7]), .Y(inc_8_net));
    XOR2 XOR2_4_inst(.A(Rcout_5_net), .B(DataA[5]), .Y(Sum[5]));
    AND2 AND2_2_inst(.A(DataA[0]), .B(DataA[1]), .Y(inc_1_net));
    XOR2 XOR2_5_inst(.A(Rcout_6_net), .B(DataA[6]), .Y(Sum[6]));
    XOR2 XOR2_11_inst(.A(Rcout_14_net), .B(DataA[14]), .Y(Sum[14])
        );
    AND2 FND2_8_inst(.A(incb_2_net), .B(DataA[9]), .Y(inc_12_net));
    XOR2 XOR2_2_inst(.A(inc_2_net), .B(DataA[3]), .Y(Sum[3]));
    XOR2 XOR2_2_1_inst(.A(inc_1_net), .B(DataA[2]), .Y(Sum[2]));
    XOR2 XOR2_7_inst(.A(Rcout_9_net), .B(DataA[9]), .Y(Sum[9]));
    AND3 AND2_9_inst(.A(DataA[6]), .B(DataA[7]), .C(DataA[8]), .Y(
        inc_10_net));
    AND3 TND2_15_inst(.A(inc_16_net), .B(inc_17_net), .C(
        inc_22_net), .Y(Rcout_15_net));
    AND3 AND2b_12_inst(.A(DataA[3]), .B(DataA[4]), .C(DataA[5]), 
        .Y(incb_5_net));
    XOR2 XOR2_9_inst(.A(Rcout_11_net), .B(DataA[11]), .Y(Sum[11]));
    AND3 TAND2_15_inst(.A(DataA[12]), .B(DataA[13]), .C(DataA[14])
        , .Y(inc_22_net));
    AND3 VAND2_18_inst(.A(inc_17_net), .B(inc_24_net), .C(
        DataA[15]), .Y(Rcout_16_net));
    AND3 AND2_6_inst(.A(DataA[3]), .B(DataA[4]), .C(DataA[5]), .Y(
        inc_5_net));
    AND3 fAND2_8_inst(.A(incb_2_net), .B(inc_5_net), .C(
        inc_10_net), .Y(Rcout_9_net));
    AND3 AND2_11_inst(.A(inc_14_net), .B(inc_5_net), .C(
        inc_10_net), .Y(Rcout_11_net));
    AND3 FND2_9_inst(.A(inc_12_net), .B(inc_5_net), .C(inc_10_net)
        , .Y(Rcout_10_net));
    AND2 VAND2_17_inst(.A(inc_22_net), .B(inc_16_net), .Y(
        inc_24_net));
    AND3 AND2_15_inst(.A(inc_16_net), .B(inc_17_net), .C(
        inc_20_net), .Y(Rcout_14_net));
    AND2 AND2_13_inst(.A(inc_17_net), .B(inc_16_net), .Y(
        Rcout_12_net));
    XOR2 XOR2_3_inst(.A(Rcout_4_net), .B(DataA[4]), .Y(Sum[4]));
    AND2 AND2_14_inst(.A(DataA[12]), .B(DataA[13]), .Y(inc_20_net)
        );
    AND3 AND2_3_inst(.A(DataA[0]), .B(DataA[1]), .C(DataA[2]), .Y(
        inc_2_net));
    AND2 AND2_4_inst(.A(inc_2_net), .B(DataA[3]), .Y(Rcout_4_net));
    INV INV_0_inst(.A(DataA[0]), .Y(Sum[0]));
    AND3 HND2_13_inst(.A(inc_17_net), .B(inc_16_net), .C(
        DataA[12]), .Y(Rcout_13_net));
    AND2 AND2_7_inst(.A(inc_2_net), .B(inc_5_net), .Y(Rcout_6_net)
        );
    AND3 AND2_5_inst(.A(inc_2_net), .B(DataA[3]), .C(DataA[4]), 
        .Y(Rcout_5_net));
    XOR2 XOR2_6_inst(.A(Rcout_8_net), .B(DataA[8]), .Y(Sum[8]));
    
endmodule
