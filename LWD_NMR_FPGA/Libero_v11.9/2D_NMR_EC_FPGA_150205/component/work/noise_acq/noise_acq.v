`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module noise_acq(
       noise_load,
       n_reset,
       RAM_RDaddr_rst,
       Noise_acq_clk,
       RAM_WT_EN,
       RAM_RD_EN,
       XRD,
       clk_sys,
       n_acqnum,
       n_ADC,
       n_divnum,
       RAM_data
    );
input  noise_load;
input  n_reset;
input  RAM_RDaddr_rst;
output Noise_acq_clk;
input  RAM_WT_EN;
input  RAM_RD_EN;
input  XRD;
input  clk_sys;
input  [11:0] n_acqnum;
input  [11:0] n_ADC;
input  [9:0] n_divnum;
output [15:0] RAM_data;

    wire noiseclkctrl_0_en, \noise_addr_0_addr_[11] , 
        \noise_addr_0_addr_[10] , \noise_addr_0_addr_[9] , 
        \noise_addr_0_addr_[8] , \noise_addr_0_addr_[7] , 
        \noise_addr_0_addr_[6] , \noise_addr_0_addr_[5] , 
        \noise_addr_0_addr_[4] , \noise_addr_0_addr_[3] , 
        \noise_addr_0_addr_[2] , \noise_addr_0_addr_[1] , 
        \noise_addr_0_addr_[0] , \noise_addr_1_addr_[11] , 
        \noise_addr_1_addr_[10] , \noise_addr_1_addr_[9] , 
        \noise_addr_1_addr_[8] , \noise_addr_1_addr_[7] , 
        \noise_addr_1_addr_[6] , \noise_addr_1_addr_[5] , 
        \noise_addr_1_addr_[4] , \noise_addr_1_addr_[3] , 
        \noise_addr_1_addr_[2] , \noise_addr_1_addr_[1] , 
        \noise_addr_1_addr_[0] , n_rdclk_syn_0_n_rdclk, 
        \RAM_0_RD_[11] , \RAM_0_RD_[10] , \RAM_0_RD_[9] , 
        \RAM_0_RD_[8] , \RAM_0_RD_[7] , \RAM_0_RD_[6] , \RAM_0_RD_[5] , 
        \RAM_0_RD_[4] , \RAM_0_RD_[3] , \RAM_0_RD_[2] , \RAM_0_RD_[1] , 
        \RAM_0_RD_[0] , GND_net, VCC_net;
    
    n_rdclk_syn n_rdclk_syn_0 (.rst_n(n_reset), .clk_sys(clk_sys), 
        .clken(RAM_RD_EN), .xrd(XRD), .n_rdclk(n_rdclk_syn_0_n_rdclk));
    noise_addr noise_addr_0 (.clkin(Noise_acq_clk), .rst_n(n_reset), 
        .addr({\noise_addr_0_addr_[11] , \noise_addr_0_addr_[10] , 
        \noise_addr_0_addr_[9] , \noise_addr_0_addr_[8] , 
        \noise_addr_0_addr_[7] , \noise_addr_0_addr_[6] , 
        \noise_addr_0_addr_[5] , \noise_addr_0_addr_[4] , 
        \noise_addr_0_addr_[3] , \noise_addr_0_addr_[2] , 
        \noise_addr_0_addr_[1] , \noise_addr_0_addr_[0] }));
    VCC VCC (.Y(VCC_net));
    noiseclk noiseclk_0 (.clk_sys(clk_sys), .clken(noiseclkctrl_0_en), 
        .n_acq_en(RAM_WT_EN), .rst_n(n_reset), .load(noise_load), 
        .clkout(Noise_acq_clk), .divnum({n_divnum[9], n_divnum[8], 
        n_divnum[7], n_divnum[6], n_divnum[5], n_divnum[4], 
        n_divnum[3], n_divnum[2], n_divnum[1], n_divnum[0]}));
    noiseclkctrl noiseclkctrl_0 (.rst_n(n_reset), .clk_sys(clk_sys), 
        .load(noise_load), .en(noiseclkctrl_0_en), .clkin(
        Noise_acq_clk), .acqnum({n_acqnum[11], n_acqnum[10], 
        n_acqnum[9], n_acqnum[8], n_acqnum[7], n_acqnum[6], 
        n_acqnum[5], n_acqnum[4], n_acqnum[3], n_acqnum[2], 
        n_acqnum[1], n_acqnum[0]}));
    GND GND (.Y(GND_net));
    RAM RAM_0 (.WEN(RAM_WT_EN), .REN(RAM_RD_EN), .WCLK(Noise_acq_clk), 
        .RCLK(n_rdclk_syn_0_n_rdclk), .RESET(n_reset), .WD({n_ADC[11], 
        n_ADC[10], n_ADC[9], n_ADC[8], n_ADC[7], n_ADC[6], n_ADC[5], 
        n_ADC[4], n_ADC[3], n_ADC[2], n_ADC[1], n_ADC[0]}), .RD({
        \RAM_0_RD_[11] , \RAM_0_RD_[10] , \RAM_0_RD_[9] , 
        \RAM_0_RD_[8] , \RAM_0_RD_[7] , \RAM_0_RD_[6] , \RAM_0_RD_[5] , 
        \RAM_0_RD_[4] , \RAM_0_RD_[3] , \RAM_0_RD_[2] , \RAM_0_RD_[1] , 
        \RAM_0_RD_[0] }), .WADDR({\noise_addr_0_addr_[11] , 
        \noise_addr_0_addr_[10] , \noise_addr_0_addr_[9] , 
        \noise_addr_0_addr_[8] , \noise_addr_0_addr_[7] , 
        \noise_addr_0_addr_[6] , \noise_addr_0_addr_[5] , 
        \noise_addr_0_addr_[4] , \noise_addr_0_addr_[3] , 
        \noise_addr_0_addr_[2] , \noise_addr_0_addr_[1] , 
        \noise_addr_0_addr_[0] }), .RADDR({\noise_addr_1_addr_[11] , 
        \noise_addr_1_addr_[10] , \noise_addr_1_addr_[9] , 
        \noise_addr_1_addr_[8] , \noise_addr_1_addr_[7] , 
        \noise_addr_1_addr_[6] , \noise_addr_1_addr_[5] , 
        \noise_addr_1_addr_[4] , \noise_addr_1_addr_[3] , 
        \noise_addr_1_addr_[2] , \noise_addr_1_addr_[1] , 
        \noise_addr_1_addr_[0] }));
    link link_0 (.datain({GND_net, GND_net, GND_net, GND_net, 
        \RAM_0_RD_[11] , \RAM_0_RD_[10] , \RAM_0_RD_[9] , 
        \RAM_0_RD_[8] , \RAM_0_RD_[7] , \RAM_0_RD_[6] , \RAM_0_RD_[5] , 
        \RAM_0_RD_[4] , \RAM_0_RD_[3] , \RAM_0_RD_[2] , \RAM_0_RD_[1] , 
        \RAM_0_RD_[0] }), .dataout({RAM_data[15], RAM_data[14], 
        RAM_data[13], RAM_data[12], RAM_data[11], RAM_data[10], 
        RAM_data[9], RAM_data[8], RAM_data[7], RAM_data[6], 
        RAM_data[5], RAM_data[4], RAM_data[3], RAM_data[2], 
        RAM_data[1], RAM_data[0]}));
    noise_addr noise_addr_1 (.clkin(n_rdclk_syn_0_n_rdclk), .rst_n(
        RAM_RDaddr_rst), .addr({\noise_addr_1_addr_[11] , 
        \noise_addr_1_addr_[10] , \noise_addr_1_addr_[9] , 
        \noise_addr_1_addr_[8] , \noise_addr_1_addr_[7] , 
        \noise_addr_1_addr_[6] , \noise_addr_1_addr_[5] , 
        \noise_addr_1_addr_[4] , \noise_addr_1_addr_[3] , 
        \noise_addr_1_addr_[2] , \noise_addr_1_addr_[1] , 
        \noise_addr_1_addr_[0] }));
    
endmodule
