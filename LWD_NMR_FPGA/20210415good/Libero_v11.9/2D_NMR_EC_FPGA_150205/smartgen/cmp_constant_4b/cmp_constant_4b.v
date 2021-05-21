`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module cmp_constant_4b(DataA,AEB);
input [3:0] DataA;
output  AEB;

    wire Temp_0_net, Temp_1_net, Vcc;
    
    VCC VCC_1_net(.Y(Vcc));
    AND3B AND3B_Temp_0_inst(.A(DataA[2]), .B(DataA[1]), .C(
        DataA[0]), .Y(Temp_0_net));
    NAND2 NAND2_AEB(.A(Temp_0_net), .B(Temp_1_net), .Y(AEB));
    AND2 AND2_Temp_1_inst(.A(Vcc), .B(DataA[3]), .Y(Temp_1_net));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:9.1.0.18
// ACTGENU_CALL:1
// BATCH:T
// FAM:ProASIC3
// OUTFORMAT:Verilog
// LPMTYPE:LPM_COMPARE
// LPM_HINT:PndgenCdec
// INSERT_PAD:NO
// INSERT_IOREG:NO
// GEN_BHV_VHDL_VAL:F
// GEN_BHV_VERILOG_VAL:F
// MGNTIMER:F
// MGNCMPL:T
// DESDIR:F:/Project/tmp/2DNMRECBP/Final_One/2D_NMR_EC_FPGA_150114/smartgen\cmp_constant_4b
// GEN_BEHV_MODULE:T
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// WIDTH:4
// B_VALUE:1001
// RADIX:BIN
// AEB_POLARITY:0

// _End_Comments_

