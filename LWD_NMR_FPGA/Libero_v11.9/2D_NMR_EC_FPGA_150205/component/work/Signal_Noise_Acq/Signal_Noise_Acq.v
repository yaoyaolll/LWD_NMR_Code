`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module Signal_Noise_Acq(
       clk_sys,
       clk_dds,
       acq_clk,
       n_s_ctrl,
       n_reset,
       noise_load,
       RAM_RDaddr_rst,
       RAM_RD_EN,
       RAM_WT_EN,
       XRD,
       signal_load,
       s_reset,
       s_acq_en,
       adcdata,
       dataout,
       n_acqnum,
       n_divnum,
       s_periodnum,
       stripnum,
       acqnum,
       s_addchoice
    );
input  clk_sys;
input  clk_dds;
output acq_clk;
input  n_s_ctrl;
input  n_reset;
input  noise_load;
input  RAM_RDaddr_rst;
input  RAM_RD_EN;
input  RAM_WT_EN;
input  XRD;
input  signal_load;
input  s_reset;
input  s_acq_en;
input  [11:0] adcdata;
output [15:0] dataout;
input  [11:0] n_acqnum;
input  [9:0] n_divnum;
input  [3:0] s_periodnum;
input  [11:0] stripnum;
input  [15:0] acqnum;
input  [4:0] s_addchoice;

    wire noise_acq_0_Noise_acq_clk, \noise_acq_0_RAM_data_[15] , 
        \noise_acq_0_RAM_data_[14] , \noise_acq_0_RAM_data_[13] , 
        \noise_acq_0_RAM_data_[12] , \noise_acq_0_RAM_data_[11] , 
        \noise_acq_0_RAM_data_[10] , \noise_acq_0_RAM_data_[9] , 
        \noise_acq_0_RAM_data_[8] , \noise_acq_0_RAM_data_[7] , 
        \noise_acq_0_RAM_data_[6] , \noise_acq_0_RAM_data_[5] , 
        \noise_acq_0_RAM_data_[4] , \noise_acq_0_RAM_data_[3] , 
        \noise_acq_0_RAM_data_[2] , \noise_acq_0_RAM_data_[1] , 
        \noise_acq_0_RAM_data_[0] , \n_s_change_0_n_adc_[11] , 
        \n_s_change_0_n_adc_[10] , \n_s_change_0_n_adc_[9] , 
        \n_s_change_0_n_adc_[8] , \n_s_change_0_n_adc_[7] , 
        \n_s_change_0_n_adc_[6] , \n_s_change_0_n_adc_[5] , 
        \n_s_change_0_n_adc_[4] , \n_s_change_0_n_adc_[3] , 
        \n_s_change_0_n_adc_[2] , \n_s_change_0_n_adc_[1] , 
        \n_s_change_0_n_adc_[0] , \n_s_change_0_s_adc_[11] , 
        \n_s_change_0_s_adc_[10] , \n_s_change_0_s_adc_[9] , 
        \n_s_change_0_s_adc_[8] , \n_s_change_0_s_adc_[7] , 
        \n_s_change_0_s_adc_[6] , \n_s_change_0_s_adc_[5] , 
        \n_s_change_0_s_adc_[4] , \n_s_change_0_s_adc_[3] , 
        \n_s_change_0_s_adc_[2] , \n_s_change_0_s_adc_[1] , 
        \n_s_change_0_s_adc_[0] , signal_acq_0_Signal_acq_clk, 
        \signal_acq_0_signal_data_[15] , 
        \signal_acq_0_signal_data_[14] , 
        \signal_acq_0_signal_data_[13] , 
        \signal_acq_0_signal_data_[12] , 
        \signal_acq_0_signal_data_[11] , 
        \signal_acq_0_signal_data_[10] , 
        \signal_acq_0_signal_data_[9] , \signal_acq_0_signal_data_[8] , 
        \signal_acq_0_signal_data_[7] , \signal_acq_0_signal_data_[6] , 
        \signal_acq_0_signal_data_[5] , \signal_acq_0_signal_data_[4] , 
        \signal_acq_0_signal_data_[3] , \signal_acq_0_signal_data_[2] , 
        \signal_acq_0_signal_data_[1] , \signal_acq_0_signal_data_[0] , 
        GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    signal_acq signal_acq_0 (.s_reset(s_reset), .signal_load(
        signal_load), .clk_sys(clk_sys), .Signal_acq_clk(
        signal_acq_0_Signal_acq_clk), .clk_dds(clk_dds), .s_acq_en(
        s_acq_en), .acqnum({acqnum[15], acqnum[14], acqnum[13], 
        acqnum[12], acqnum[11], acqnum[10], acqnum[9], acqnum[8], 
        acqnum[7], acqnum[6], acqnum[5], acqnum[4], acqnum[3], 
        acqnum[2], acqnum[1], acqnum[0]}), .stripnum({stripnum[11], 
        stripnum[10], stripnum[9], stripnum[8], stripnum[7], 
        stripnum[6], stripnum[5], stripnum[4], stripnum[3], 
        stripnum[2], stripnum[1], stripnum[0]}), .s_periodnum({
        s_periodnum[3], s_periodnum[2], s_periodnum[1], s_periodnum[0]})
        , .signal_data({\signal_acq_0_signal_data_[15] , 
        \signal_acq_0_signal_data_[14] , 
        \signal_acq_0_signal_data_[13] , 
        \signal_acq_0_signal_data_[12] , 
        \signal_acq_0_signal_data_[11] , 
        \signal_acq_0_signal_data_[10] , 
        \signal_acq_0_signal_data_[9] , \signal_acq_0_signal_data_[8] , 
        \signal_acq_0_signal_data_[7] , \signal_acq_0_signal_data_[6] , 
        \signal_acq_0_signal_data_[5] , \signal_acq_0_signal_data_[4] , 
        \signal_acq_0_signal_data_[3] , \signal_acq_0_signal_data_[2] , 
        \signal_acq_0_signal_data_[1] , \signal_acq_0_signal_data_[0] })
        , .s_addchoice({s_addchoice[4], s_addchoice[3], s_addchoice[2], 
        s_addchoice[1], s_addchoice[0]}), .s_ADC({
        \n_s_change_0_s_adc_[11] , \n_s_change_0_s_adc_[10] , 
        \n_s_change_0_s_adc_[9] , \n_s_change_0_s_adc_[8] , 
        \n_s_change_0_s_adc_[7] , \n_s_change_0_s_adc_[6] , 
        \n_s_change_0_s_adc_[5] , \n_s_change_0_s_adc_[4] , 
        \n_s_change_0_s_adc_[3] , \n_s_change_0_s_adc_[2] , 
        \n_s_change_0_s_adc_[1] , \n_s_change_0_s_adc_[0] }));
    noise_acq noise_acq_0 (.noise_load(noise_load), .n_reset(n_reset), 
        .RAM_RDaddr_rst(RAM_RDaddr_rst), .Noise_acq_clk(
        noise_acq_0_Noise_acq_clk), .RAM_WT_EN(RAM_WT_EN), .RAM_RD_EN(
        RAM_RD_EN), .XRD(XRD), .clk_sys(clk_sys), .n_acqnum({
        n_acqnum[11], n_acqnum[10], n_acqnum[9], n_acqnum[8], 
        n_acqnum[7], n_acqnum[6], n_acqnum[5], n_acqnum[4], 
        n_acqnum[3], n_acqnum[2], n_acqnum[1], n_acqnum[0]}), .n_ADC({
        \n_s_change_0_n_adc_[11] , \n_s_change_0_n_adc_[10] , 
        \n_s_change_0_n_adc_[9] , \n_s_change_0_n_adc_[8] , 
        \n_s_change_0_n_adc_[7] , \n_s_change_0_n_adc_[6] , 
        \n_s_change_0_n_adc_[5] , \n_s_change_0_n_adc_[4] , 
        \n_s_change_0_n_adc_[3] , \n_s_change_0_n_adc_[2] , 
        \n_s_change_0_n_adc_[1] , \n_s_change_0_n_adc_[0] }), 
        .n_divnum({n_divnum[9], n_divnum[8], n_divnum[7], n_divnum[6], 
        n_divnum[5], n_divnum[4], n_divnum[3], n_divnum[2], 
        n_divnum[1], n_divnum[0]}), .RAM_data({
        \noise_acq_0_RAM_data_[15] , \noise_acq_0_RAM_data_[14] , 
        \noise_acq_0_RAM_data_[13] , \noise_acq_0_RAM_data_[12] , 
        \noise_acq_0_RAM_data_[11] , \noise_acq_0_RAM_data_[10] , 
        \noise_acq_0_RAM_data_[9] , \noise_acq_0_RAM_data_[8] , 
        \noise_acq_0_RAM_data_[7] , \noise_acq_0_RAM_data_[6] , 
        \noise_acq_0_RAM_data_[5] , \noise_acq_0_RAM_data_[4] , 
        \noise_acq_0_RAM_data_[3] , \noise_acq_0_RAM_data_[2] , 
        \noise_acq_0_RAM_data_[1] , \noise_acq_0_RAM_data_[0] }));
    GND GND (.Y(GND_net));
    n_s_change n_s_change_0 (.n_s_ctrl(n_s_ctrl), .n_clk(
        noise_acq_0_Noise_acq_clk), .s_clk(signal_acq_0_Signal_acq_clk)
        , .acq_clk(acq_clk), .adcdata({adcdata[11], adcdata[10], 
        adcdata[9], adcdata[8], adcdata[7], adcdata[6], adcdata[5], 
        adcdata[4], adcdata[3], adcdata[2], adcdata[1], adcdata[0]}), 
        .n_adc({\n_s_change_0_n_adc_[11] , \n_s_change_0_n_adc_[10] , 
        \n_s_change_0_n_adc_[9] , \n_s_change_0_n_adc_[8] , 
        \n_s_change_0_n_adc_[7] , \n_s_change_0_n_adc_[6] , 
        \n_s_change_0_n_adc_[5] , \n_s_change_0_n_adc_[4] , 
        \n_s_change_0_n_adc_[3] , \n_s_change_0_n_adc_[2] , 
        \n_s_change_0_n_adc_[1] , \n_s_change_0_n_adc_[0] }), .s_adc({
        \n_s_change_0_s_adc_[11] , \n_s_change_0_s_adc_[10] , 
        \n_s_change_0_s_adc_[9] , \n_s_change_0_s_adc_[8] , 
        \n_s_change_0_s_adc_[7] , \n_s_change_0_s_adc_[6] , 
        \n_s_change_0_s_adc_[5] , \n_s_change_0_s_adc_[4] , 
        \n_s_change_0_s_adc_[3] , \n_s_change_0_s_adc_[2] , 
        \n_s_change_0_s_adc_[1] , \n_s_change_0_s_adc_[0] }), .dataout({
        dataout[15], dataout[14], dataout[13], dataout[12], 
        dataout[11], dataout[10], dataout[9], dataout[8], dataout[7], 
        dataout[6], dataout[5], dataout[4], dataout[3], dataout[2], 
        dataout[1], dataout[0]}), .s_data({
        \signal_acq_0_signal_data_[15] , 
        \signal_acq_0_signal_data_[14] , 
        \signal_acq_0_signal_data_[13] , 
        \signal_acq_0_signal_data_[12] , 
        \signal_acq_0_signal_data_[11] , 
        \signal_acq_0_signal_data_[10] , 
        \signal_acq_0_signal_data_[9] , \signal_acq_0_signal_data_[8] , 
        \signal_acq_0_signal_data_[7] , \signal_acq_0_signal_data_[6] , 
        \signal_acq_0_signal_data_[5] , \signal_acq_0_signal_data_[4] , 
        \signal_acq_0_signal_data_[3] , \signal_acq_0_signal_data_[2] , 
        \signal_acq_0_signal_data_[1] , \signal_acq_0_signal_data_[0] })
        , .n_data({\noise_acq_0_RAM_data_[15] , 
        \noise_acq_0_RAM_data_[14] , \noise_acq_0_RAM_data_[13] , 
        \noise_acq_0_RAM_data_[12] , \noise_acq_0_RAM_data_[11] , 
        \noise_acq_0_RAM_data_[10] , \noise_acq_0_RAM_data_[9] , 
        \noise_acq_0_RAM_data_[8] , \noise_acq_0_RAM_data_[7] , 
        \noise_acq_0_RAM_data_[6] , \noise_acq_0_RAM_data_[5] , 
        \noise_acq_0_RAM_data_[4] , \noise_acq_0_RAM_data_[3] , 
        \noise_acq_0_RAM_data_[2] , \noise_acq_0_RAM_data_[1] , 
        \noise_acq_0_RAM_data_[0] }));
    
endmodule
