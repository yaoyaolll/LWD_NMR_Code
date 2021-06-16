`timescale 1 ns/100 ps
// Version: 9.0 9.0.0.15


module noiseacq(
       n_en,
       n_rdclk,
       n_rd_en,
       n_acqclk,
       n_reset,
       n_load,
       clk_sys,
       n_rd_rst,
       n_dataout,
       n_adcdata,
       n_divnum,
       n_acqnum
    );
input  n_en;
input  n_rdclk;
input  n_rd_en;
output n_acqclk;
input  n_reset;
input  n_load;
input  clk_sys;
input  n_rd_rst;
output [15:0] n_dataout;
input  [11:0] n_adcdata;
input  [9:0] n_divnum;
input  [11:0] n_acqnum;

    wire noiseclkctrl_0_en, \noiseram_0_RD_[11] , \noiseram_0_RD_[10] , 
        \noiseram_0_RD_[9] , \noiseram_0_RD_[8] , \noiseram_0_RD_[7] , 
        \noiseram_0_RD_[6] , \noiseram_0_RD_[5] , \noiseram_0_RD_[4] , 
        \noiseram_0_RD_[3] , \noiseram_0_RD_[2] , \noiseram_0_RD_[1] , 
        \noiseram_0_RD_[0] , \noise_addr_0_addr_0_[11] , 
        \noise_addr_0_addr_0_[10] , \noise_addr_0_addr_0_[9] , 
        \noise_addr_0_addr_0_[8] , \noise_addr_0_addr_0_[7] , 
        \noise_addr_0_addr_0_[6] , \noise_addr_0_addr_0_[5] , 
        \noise_addr_0_addr_0_[4] , \noise_addr_0_addr_0_[3] , 
        \noise_addr_0_addr_0_[2] , \noise_addr_0_addr_0_[1] , 
        \noise_addr_0_addr_0_[0] , \noise_addr_1_addr_0_[11] , 
        \noise_addr_1_addr_0_[10] , \noise_addr_1_addr_0_[9] , 
        \noise_addr_1_addr_0_[8] , \noise_addr_1_addr_0_[7] , 
        \noise_addr_1_addr_0_[6] , \noise_addr_1_addr_0_[5] , 
        \noise_addr_1_addr_0_[4] , \noise_addr_1_addr_0_[3] , 
        \noise_addr_1_addr_0_[2] , \noise_addr_1_addr_0_[1] , 
        \noise_addr_1_addr_0_[0] , n_rdclk_syn_0_n_rdclk, GND_net, 
        VCC_net;
    
    n_rdclk_syn n_rdclk_syn_0 (.rst_n(n_reset), .clk_sys(clk_sys), 
        .clken(n_rd_en), .xrd(n_rdclk), .n_rdclk(n_rdclk_syn_0_n_rdclk)
        );
    noise_addr noise_addr_0 (.clkin(n_acqclk), .rst_n(n_reset), .addr({
        \noise_addr_0_addr_0_[11] , \noise_addr_0_addr_0_[10] , 
        \noise_addr_0_addr_0_[9] , \noise_addr_0_addr_0_[8] , 
        \noise_addr_0_addr_0_[7] , \noise_addr_0_addr_0_[6] , 
        \noise_addr_0_addr_0_[5] , \noise_addr_0_addr_0_[4] , 
        \noise_addr_0_addr_0_[3] , \noise_addr_0_addr_0_[2] , 
        \noise_addr_0_addr_0_[1] , \noise_addr_0_addr_0_[0] }));
    VCC VCC (.Y(VCC_net));
    noiseram noiseram_0 (.WEN(n_en), .REN(n_rd_en), .WCLK(n_acqclk), 
        .RCLK(n_rdclk_syn_0_n_rdclk), .RESET(n_reset), .WD({
        n_adcdata[11], n_adcdata[10], n_adcdata[9], n_adcdata[8], 
        n_adcdata[7], n_adcdata[6], n_adcdata[5], n_adcdata[4], 
        n_adcdata[3], n_adcdata[2], n_adcdata[1], n_adcdata[0]}), .RD({
        \noiseram_0_RD_[11] , \noiseram_0_RD_[10] , 
        \noiseram_0_RD_[9] , \noiseram_0_RD_[8] , \noiseram_0_RD_[7] , 
        \noiseram_0_RD_[6] , \noiseram_0_RD_[5] , \noiseram_0_RD_[4] , 
        \noiseram_0_RD_[3] , \noiseram_0_RD_[2] , \noiseram_0_RD_[1] , 
        \noiseram_0_RD_[0] }), .WADDR({\noise_addr_0_addr_0_[11] , 
        \noise_addr_0_addr_0_[10] , \noise_addr_0_addr_0_[9] , 
        \noise_addr_0_addr_0_[8] , \noise_addr_0_addr_0_[7] , 
        \noise_addr_0_addr_0_[6] , \noise_addr_0_addr_0_[5] , 
        \noise_addr_0_addr_0_[4] , \noise_addr_0_addr_0_[3] , 
        \noise_addr_0_addr_0_[2] , \noise_addr_0_addr_0_[1] , 
        \noise_addr_0_addr_0_[0] }), .RADDR({
        \noise_addr_1_addr_0_[11] , \noise_addr_1_addr_0_[10] , 
        \noise_addr_1_addr_0_[9] , \noise_addr_1_addr_0_[8] , 
        \noise_addr_1_addr_0_[7] , \noise_addr_1_addr_0_[6] , 
        \noise_addr_1_addr_0_[5] , \noise_addr_1_addr_0_[4] , 
        \noise_addr_1_addr_0_[3] , \noise_addr_1_addr_0_[2] , 
        \noise_addr_1_addr_0_[1] , \noise_addr_1_addr_0_[0] }));
    noiseclk noiseclk_0 (.clk_sys(clk_sys), .clken(noiseclkctrl_0_en), 
        .n_acq(n_en), .rst_n(n_reset), .load(n_load), .clkout(n_acqclk)
        , .divnum({n_divnum[9], n_divnum[8], n_divnum[7], n_divnum[6], 
        n_divnum[5], n_divnum[4], n_divnum[3], n_divnum[2], 
        n_divnum[1], n_divnum[0]}));
    noiseclkctrl noiseclkctrl_0 (.rst_n(n_reset), .clk_sys(clk_sys), 
        .load(n_load), .en(noiseclkctrl_0_en), .clkin(n_acqclk), 
        .acqnum({n_acqnum[11], n_acqnum[10], n_acqnum[9], n_acqnum[8], 
        n_acqnum[7], n_acqnum[6], n_acqnum[5], n_acqnum[4], 
        n_acqnum[3], n_acqnum[2], n_acqnum[1], n_acqnum[0]}));
    GND GND (.Y(GND_net));
    link link_0 (.datain({GND_net, GND_net, GND_net, GND_net, 
        \noiseram_0_RD_[11] , \noiseram_0_RD_[10] , 
        \noiseram_0_RD_[9] , \noiseram_0_RD_[8] , \noiseram_0_RD_[7] , 
        \noiseram_0_RD_[6] , \noiseram_0_RD_[5] , \noiseram_0_RD_[4] , 
        \noiseram_0_RD_[3] , \noiseram_0_RD_[2] , \noiseram_0_RD_[1] , 
        \noiseram_0_RD_[0] }), .dataout({n_dataout[15], n_dataout[14], 
        n_dataout[13], n_dataout[12], n_dataout[11], n_dataout[10], 
        n_dataout[9], n_dataout[8], n_dataout[7], n_dataout[6], 
        n_dataout[5], n_dataout[4], n_dataout[3], n_dataout[2], 
        n_dataout[1], n_dataout[0]}));
    noise_addr noise_addr_1 (.clkin(n_rdclk_syn_0_n_rdclk), .rst_n(
        n_rd_rst), .addr({\noise_addr_1_addr_0_[11] , 
        \noise_addr_1_addr_0_[10] , \noise_addr_1_addr_0_[9] , 
        \noise_addr_1_addr_0_[8] , \noise_addr_1_addr_0_[7] , 
        \noise_addr_1_addr_0_[6] , \noise_addr_1_addr_0_[5] , 
        \noise_addr_1_addr_0_[4] , \noise_addr_1_addr_0_[3] , 
        \noise_addr_1_addr_0_[2] , \noise_addr_1_addr_0_[1] , 
        \noise_addr_1_addr_0_[0] }));
    
endmodule
