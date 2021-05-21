`timescale 1 ns/100 ps
// Version: v11.9 SP6 11.9.6.7


module pllclk(
       POWERDOWN,
       CLKA,
       LOCK,
       GLA,
       GLB
    );
input  POWERDOWN;
input  CLKA;
output LOCK;
output GLA;
output GLB;

    wire VCC, GND;
    wire GND_power_net1;
    wire VCC_power_net1;
    assign GND = GND_power_net1;
    assign VCC = VCC_power_net1;
    
    PLL #( .VCOFREQUENCY(100.000) )  Core (.CLKA(CLKA), .EXTFB(GND), 
        .POWERDOWN(POWERDOWN), .GLA(GLA), .LOCK(LOCK), .GLB(GLB), .YB()
        , .GLC(), .YC(), .OADIV0(GND), .OADIV1(GND), .OADIV2(GND), 
        .OADIV3(GND), .OADIV4(GND), .OAMUX0(GND), .OAMUX1(GND), 
        .OAMUX2(VCC), .DLYGLA0(GND), .DLYGLA1(GND), .DLYGLA2(GND), 
        .DLYGLA3(GND), .DLYGLA4(GND), .OBDIV0(VCC), .OBDIV1(VCC), 
        .OBDIV2(GND), .OBDIV3(GND), .OBDIV4(VCC), .OBMUX0(GND), 
        .OBMUX1(VCC), .OBMUX2(GND), .DLYYB0(GND), .DLYYB1(GND), 
        .DLYYB2(GND), .DLYYB3(GND), .DLYYB4(GND), .DLYGLB0(GND), 
        .DLYGLB1(GND), .DLYGLB2(GND), .DLYGLB3(GND), .DLYGLB4(GND), 
        .OCDIV0(GND), .OCDIV1(GND), .OCDIV2(GND), .OCDIV3(GND), 
        .OCDIV4(GND), .OCMUX0(GND), .OCMUX1(GND), .OCMUX2(GND), 
        .DLYYC0(GND), .DLYYC1(GND), .DLYYC2(GND), .DLYYC3(GND), 
        .DLYYC4(GND), .DLYGLC0(GND), .DLYGLC1(GND), .DLYGLC2(GND), 
        .DLYGLC3(GND), .DLYGLC4(GND), .FINDIV0(GND), .FINDIV1(VCC), 
        .FINDIV2(GND), .FINDIV3(GND), .FINDIV4(VCC), .FINDIV5(GND), 
        .FINDIV6(GND), .FBDIV0(GND), .FBDIV1(VCC), .FBDIV2(GND), 
        .FBDIV3(GND), .FBDIV4(VCC), .FBDIV5(GND), .FBDIV6(GND), 
        .FBDLY0(GND), .FBDLY1(GND), .FBDLY2(GND), .FBDLY3(GND), 
        .FBDLY4(GND), .FBSEL0(VCC), .FBSEL1(GND), .XDLYSEL(GND), 
        .VCOSEL0(GND), .VCOSEL1(GND), .VCOSEL2(VCC));
    GND GND_power_inst1 (.Y(GND_power_net1));
    VCC VCC_power_inst1 (.Y(VCC_power_net1));
    
endmodule

// _Disclaimer: Please leave the following comments in the file, they are for internal purposes only._


// _GEN_File_Contents_

// Version:11.9.6.7
// ACTGENU_CALL:1
// BATCH:T
// FAM:PA3LC
// OUTFORMAT:Verilog
// LPMTYPE:LPM_PLL_STATIC
// LPM_HINT:NONE
// INSERT_PAD:NO
// INSERT_IOREG:NO
// GEN_BHV_VHDL_VAL:F
// GEN_BHV_VERILOG_VAL:F
// MGNTIMER:F
// MGNCMPL:T
// DESDIR:E:/LWD_NMR/Code/20201119/Libero_v11.9/2D_NMR_EC_FPGA_150205/smartgen\pllclk
// GEN_BEHV_MODULE:F
// SMARTGEN_DIE:IS8X8M2
// SMARTGEN_PACKAGE:pq208
// AGENIII_IS_SUBPROJECT_LIBERO:T
// FIN:100.000000
// CLKASRC:0
// FBDLY:1
// FBMUX:1
// XDLYSEL:0
// PRIMFREQ:100.000000
// PPHASESHIFT:0
// DLYAVAL:1
// OAMUX:4
// SEC1FREQ:5.000000
// UGLB:1
// UYB:0
// GLBDLYVAL:1
// YBDLYVAL:1
// S1PHASESHIFT:0
// OBMUX:2
// POWERDOWN_POLARITY:0
// LOCK_POLARITY:1
// LOCK_CTL:0
// VOLTAGE:1.5

// _End_Comments_

