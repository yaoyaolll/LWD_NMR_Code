`timescale 1 ns/100 ps
// Version: 8.4 8.4.0.33


module scanfretop(
       zcs2,
       xwe,
       CLKA,
       ddsfqud,
       ddsreset,
       ddswclk,
       ddsdata,
       sw_acq2,
       sw_acq1,
       rt_sw,
       soft_d,
       scanover,
       ddsclkin,
       calout,
       clktodds,
       n_acqclk,
       rdclk,
       xa,
       w_data,
       xd
    );
input  zcs2;
input  xwe;
input  CLKA;
output ddsfqud;
output ddsreset;
output ddswclk;
output ddsdata;
output sw_acq2;
output sw_acq1;
output rt_sw;
output soft_d;
output scanover;
input  ddsclkin;
output calout;
output clktodds;
output n_acqclk;
input  rdclk;
input  [18:0] xa;
input  [11:0] w_data;
inout  [15:0] xd;

    wire \scancode_0_acqnum_0_[9] , \scancode_0_acqnum_0_[8] , 
        \scancode_0_acqnum_0_[7] , \scancode_0_acqnum_0_[6] , 
        \scancode_0_acqnum_0_[5] , \scancode_0_acqnum_0_[4] , 
        \scancode_0_acqnum_0_[3] , \scancode_0_acqnum_0_[2] , 
        \scancode_0_acqnum_0_[1] , \scancode_0_acqnum_0_[0] , 
        \scancode_0_addchoice_[4] , \scancode_0_addchoice_[3] , 
        \scancode_0_addchoice_[2] , \scancode_0_addchoice_[1] , 
        \scancode_0_addchoice_[0] , \scancode_0_caldata_[5] , 
        \scancode_0_caldata_[4] , \scancode_0_caldata_[3] , 
        \scancode_0_caldata_[2] , \scancode_0_caldata_[1] , 
        \scancode_0_caldata_[0] , scancode_0_calload, 
        scancode_0_ddschoice, \scancode_0_ddsconfigdata_[15] , 
        \scancode_0_ddsconfigdata_[14] , 
        \scancode_0_ddsconfigdata_[13] , 
        \scancode_0_ddsconfigdata_[12] , 
        \scancode_0_ddsconfigdata_[11] , 
        \scancode_0_ddsconfigdata_[10] , 
        \scancode_0_ddsconfigdata_[9] , \scancode_0_ddsconfigdata_[8] , 
        \scancode_0_ddsconfigdata_[7] , \scancode_0_ddsconfigdata_[6] , 
        \scancode_0_ddsconfigdata_[5] , \scancode_0_ddsconfigdata_[4] , 
        \scancode_0_ddsconfigdata_[3] , \scancode_0_ddsconfigdata_[2] , 
        \scancode_0_ddsconfigdata_[1] , \scancode_0_ddsconfigdata_[0] , 
        scancode_0_ddsload, \scancode_0_n_acqnum_[7] , 
        \scancode_0_n_acqnum_[6] , \scancode_0_n_acqnum_[5] , 
        \scancode_0_n_acqnum_[4] , \scancode_0_n_acqnum_[3] , 
        \scancode_0_n_acqnum_[2] , \scancode_0_n_acqnum_[1] , 
        \scancode_0_n_acqnum_[0] , \scancode_0_n_divnum_[9] , 
        \scancode_0_n_divnum_[8] , \scancode_0_n_divnum_[7] , 
        \scancode_0_n_divnum_[6] , \scancode_0_n_divnum_[5] , 
        \scancode_0_n_divnum_[4] , \scancode_0_n_divnum_[3] , 
        \scancode_0_n_divnum_[2] , \scancode_0_n_divnum_[1] , 
        \scancode_0_n_divnum_[0] , scancode_0_n_load, 
        scancode_0_n_rd_en, scancode_0_n_rd_rst, 
        \scancode_0_periodnum_[3] , \scancode_0_periodnum_[2] , 
        \scancode_0_periodnum_[1] , \scancode_0_periodnum_[0] , 
        scancode_0_resetout, scancode_0_scanstart, scancode_0_s_load, 
        scancode_0_tri_state, scanstatetop_0_calctrl, 
        scanstatetop_0_dds_conf, scanstatetop_0_n_acq, 
        scanstatetop_0_s_acq, \signal_acq_0_adddataout_[15] , 
        \signal_acq_0_adddataout_[14] , \signal_acq_0_adddataout_[13] , 
        \signal_acq_0_adddataout_[12] , \signal_acq_0_adddataout_[11] , 
        \signal_acq_0_adddataout_[10] , \signal_acq_0_adddataout_[9] , 
        \signal_acq_0_adddataout_[8] , \signal_acq_0_adddataout_[7] , 
        \signal_acq_0_adddataout_[6] , \signal_acq_0_adddataout_[5] , 
        \signal_acq_0_adddataout_[4] , \signal_acq_0_adddataout_[3] , 
        \signal_acq_0_adddataout_[2] , \signal_acq_0_adddataout_[1] , 
        \signal_acq_0_adddataout_[0] , \tri_state_0_dataout_[15] , 
        \tri_state_0_dataout_[14] , \tri_state_0_dataout_[13] , 
        \tri_state_0_dataout_[12] , \tri_state_0_dataout_[11] , 
        \tri_state_0_dataout_[10] , \tri_state_0_dataout_[9] , 
        \tri_state_0_dataout_[8] , \tri_state_0_dataout_[7] , 
        \tri_state_0_dataout_[6] , \tri_state_0_dataout_[5] , 
        \tri_state_0_dataout_[4] , \tri_state_0_dataout_[3] , 
        \tri_state_0_dataout_[2] , \tri_state_0_dataout_[1] , 
        \tri_state_0_dataout_[0] , GND_net, VCC_net;
    
    VCC VCC (.Y(VCC_net));
    noiseacq noiseacq_0 (.n_en(scanstatetop_0_n_acq), .rdclk(rdclk), 
        .rd_rst(scancode_0_n_rd_rst), .r_en(scancode_0_n_rd_en), 
        .n_acqclk(), .RESET(scancode_0_resetout), .n_load(
        scancode_0_n_load), .clkin_100M(clktodds), .dataout({nc0, nc1, 
        nc2, nc3, nc4, nc5, nc6, nc7, nc8, nc9, nc10, nc11, nc12, nc13, 
        nc14, nc15}), .w_data({w_data[11], w_data[10], w_data[9], 
        w_data[8], w_data[7], w_data[6], w_data[5], w_data[4], 
        w_data[3], w_data[2], w_data[1], w_data[0]}), .divnum({
        \scancode_0_n_divnum_[9] , \scancode_0_n_divnum_[8] , 
        \scancode_0_n_divnum_[7] , \scancode_0_n_divnum_[6] , 
        \scancode_0_n_divnum_[5] , \scancode_0_n_divnum_[4] , 
        \scancode_0_n_divnum_[3] , \scancode_0_n_divnum_[2] , 
        \scancode_0_n_divnum_[1] , \scancode_0_n_divnum_[0] }), 
        .acqnum({\scancode_0_n_acqnum_[7] , \scancode_0_n_acqnum_[6] , 
        \scancode_0_n_acqnum_[5] , \scancode_0_n_acqnum_[4] , 
        \scancode_0_n_acqnum_[3] , \scancode_0_n_acqnum_[2] , 
        \scancode_0_n_acqnum_[1] , \scancode_0_n_acqnum_[0] }));
    ddstop ddstop_0 (.choice(scancode_0_ddschoice), .load(
        scancode_0_ddsload), .ddsfqud(ddsfqud), .ddswclk(ddswclk), 
        .ddsreset(ddsreset), .reset(scancode_0_resetout), .ddsdata(
        ddsdata), .clken(scanstatetop_0_dds_conf), .clk(clktodds), 
        .datain({\scancode_0_ddsconfigdata_[15] , 
        \scancode_0_ddsconfigdata_[14] , 
        \scancode_0_ddsconfigdata_[13] , 
        \scancode_0_ddsconfigdata_[12] , 
        \scancode_0_ddsconfigdata_[11] , 
        \scancode_0_ddsconfigdata_[10] , 
        \scancode_0_ddsconfigdata_[9] , \scancode_0_ddsconfigdata_[8] , 
        \scancode_0_ddsconfigdata_[7] , \scancode_0_ddsconfigdata_[6] , 
        \scancode_0_ddsconfigdata_[5] , \scancode_0_ddsconfigdata_[4] , 
        \scancode_0_ddsconfigdata_[3] , \scancode_0_ddsconfigdata_[2] , 
        \scancode_0_ddsconfigdata_[1] , \scancode_0_ddsconfigdata_[0] })
        );
    signal_acq signal_acq_0 (.reset(scancode_0_resetout), .load(
        scancode_0_s_load), .s_acq(scanstatetop_0_s_acq), .ddsclkout(
        ddsclkin), .sig_acq(n_acqclk), .periodnum({
        \scancode_0_periodnum_[3] , \scancode_0_periodnum_[2] , 
        \scancode_0_periodnum_[1] , \scancode_0_periodnum_[0] }), .ADC({
        w_data[11], w_data[10], w_data[9], w_data[8], w_data[7], 
        w_data[6], w_data[5], w_data[4], w_data[3], w_data[2], 
        w_data[1], w_data[0]}), .adddchoice({
        \scancode_0_addchoice_[4] , \scancode_0_addchoice_[3] , 
        \scancode_0_addchoice_[2] , \scancode_0_addchoice_[1] , 
        \scancode_0_addchoice_[0] }), .adddataout({
        \signal_acq_0_adddataout_[15] , \signal_acq_0_adddataout_[14] , 
        \signal_acq_0_adddataout_[13] , \signal_acq_0_adddataout_[12] , 
        \signal_acq_0_adddataout_[11] , \signal_acq_0_adddataout_[10] , 
        \signal_acq_0_adddataout_[9] , \signal_acq_0_adddataout_[8] , 
        \signal_acq_0_adddataout_[7] , \signal_acq_0_adddataout_[6] , 
        \signal_acq_0_adddataout_[5] , \signal_acq_0_adddataout_[4] , 
        \signal_acq_0_adddataout_[3] , \signal_acq_0_adddataout_[2] , 
        \signal_acq_0_adddataout_[1] , \signal_acq_0_adddataout_[0] }), 
        .acqnum({\scancode_0_acqnum_0_[9] , \scancode_0_acqnum_0_[8] , 
        \scancode_0_acqnum_0_[7] , \scancode_0_acqnum_0_[6] , 
        \scancode_0_acqnum_0_[5] , \scancode_0_acqnum_0_[4] , 
        \scancode_0_acqnum_0_[3] , \scancode_0_acqnum_0_[2] , 
        \scancode_0_acqnum_0_[1] , \scancode_0_acqnum_0_[0] }));
    scancode scancode_0 (.zcs2(zcs2), .xwe(xwe), .tri_state(
        scancode_0_tri_state), .resetout(scancode_0_resetout), 
        .scanstart(scancode_0_scanstart), .ddsload(scancode_0_ddsload), 
        .ddschoice(scancode_0_ddschoice), .calload(scancode_0_calload), 
        .n_rd_rst(scancode_0_n_rd_rst), .n_rd_en(scancode_0_n_rd_en), 
        .n_load(scancode_0_n_load), .s_load(scancode_0_s_load), .xa({
        xa[18], xa[17], xa[16], xa[15], xa[14], xa[13], xa[12], xa[11], 
        xa[10], xa[9], xa[8], xa[7], xa[6], xa[5], xa[4], xa[3], xa[2], 
        xa[1], xa[0]}), .xdata({\tri_state_0_dataout_[15] , 
        \tri_state_0_dataout_[14] , \tri_state_0_dataout_[13] , 
        \tri_state_0_dataout_[12] , \tri_state_0_dataout_[11] , 
        \tri_state_0_dataout_[10] , \tri_state_0_dataout_[9] , 
        \tri_state_0_dataout_[8] , \tri_state_0_dataout_[7] , 
        \tri_state_0_dataout_[6] , \tri_state_0_dataout_[5] , 
        \tri_state_0_dataout_[4] , \tri_state_0_dataout_[3] , 
        \tri_state_0_dataout_[2] , \tri_state_0_dataout_[1] , 
        \tri_state_0_dataout_[0] }), .ddsconfigdata({
        \scancode_0_ddsconfigdata_[15] , 
        \scancode_0_ddsconfigdata_[14] , 
        \scancode_0_ddsconfigdata_[13] , 
        \scancode_0_ddsconfigdata_[12] , 
        \scancode_0_ddsconfigdata_[11] , 
        \scancode_0_ddsconfigdata_[10] , 
        \scancode_0_ddsconfigdata_[9] , \scancode_0_ddsconfigdata_[8] , 
        \scancode_0_ddsconfigdata_[7] , \scancode_0_ddsconfigdata_[6] , 
        \scancode_0_ddsconfigdata_[5] , \scancode_0_ddsconfigdata_[4] , 
        \scancode_0_ddsconfigdata_[3] , \scancode_0_ddsconfigdata_[2] , 
        \scancode_0_ddsconfigdata_[1] , \scancode_0_ddsconfigdata_[0] })
        , .caldata({\scancode_0_caldata_[5] , \scancode_0_caldata_[4] , 
        \scancode_0_caldata_[3] , \scancode_0_caldata_[2] , 
        \scancode_0_caldata_[1] , \scancode_0_caldata_[0] }), 
        .n_acqnum({\scancode_0_n_acqnum_[7] , 
        \scancode_0_n_acqnum_[6] , \scancode_0_n_acqnum_[5] , 
        \scancode_0_n_acqnum_[4] , \scancode_0_n_acqnum_[3] , 
        \scancode_0_n_acqnum_[2] , \scancode_0_n_acqnum_[1] , 
        \scancode_0_n_acqnum_[0] }), .n_divnum({
        \scancode_0_n_divnum_[9] , \scancode_0_n_divnum_[8] , 
        \scancode_0_n_divnum_[7] , \scancode_0_n_divnum_[6] , 
        \scancode_0_n_divnum_[5] , \scancode_0_n_divnum_[4] , 
        \scancode_0_n_divnum_[3] , \scancode_0_n_divnum_[2] , 
        \scancode_0_n_divnum_[1] , \scancode_0_n_divnum_[0] }), 
        .acqnum({\scancode_0_acqnum_0_[9] , \scancode_0_acqnum_0_[8] , 
        \scancode_0_acqnum_0_[7] , \scancode_0_acqnum_0_[6] , 
        \scancode_0_acqnum_0_[5] , \scancode_0_acqnum_0_[4] , 
        \scancode_0_acqnum_0_[3] , \scancode_0_acqnum_0_[2] , 
        \scancode_0_acqnum_0_[1] , \scancode_0_acqnum_0_[0] }), 
        .periodnum({\scancode_0_periodnum_[3] , 
        \scancode_0_periodnum_[2] , \scancode_0_periodnum_[1] , 
        \scancode_0_periodnum_[0] }), .addchoice({
        \scancode_0_addchoice_[4] , \scancode_0_addchoice_[3] , 
        \scancode_0_addchoice_[2] , \scancode_0_addchoice_[1] , 
        \scancode_0_addchoice_[0] }));
    pllclk pllclk_0 (.POWERDOWN(VCC_net), .CLKA(CLKA), .LOCK(), .GLA(
        clktodds));
    GND GND (.Y(GND_net));
    tri_state tri_state_0 (.ctrl(scancode_0_tri_state), .xd({xd[15], 
        xd[14], xd[13], xd[12], xd[11], xd[10], xd[9], xd[8], xd[7], 
        xd[6], xd[5], xd[4], xd[3], xd[2], xd[1], xd[0]}), .dataout({
        \tri_state_0_dataout_[15] , \tri_state_0_dataout_[14] , 
        \tri_state_0_dataout_[13] , \tri_state_0_dataout_[12] , 
        \tri_state_0_dataout_[11] , \tri_state_0_dataout_[10] , 
        \tri_state_0_dataout_[9] , \tri_state_0_dataout_[8] , 
        \tri_state_0_dataout_[7] , \tri_state_0_dataout_[6] , 
        \tri_state_0_dataout_[5] , \tri_state_0_dataout_[4] , 
        \tri_state_0_dataout_[3] , \tri_state_0_dataout_[2] , 
        \tri_state_0_dataout_[1] , \tri_state_0_dataout_[0] }), 
        .datain({\signal_acq_0_adddataout_[15] , 
        \signal_acq_0_adddataout_[14] , \signal_acq_0_adddataout_[13] , 
        \signal_acq_0_adddataout_[12] , \signal_acq_0_adddataout_[11] , 
        \signal_acq_0_adddataout_[10] , \signal_acq_0_adddataout_[9] , 
        \signal_acq_0_adddataout_[8] , \signal_acq_0_adddataout_[7] , 
        \signal_acq_0_adddataout_[6] , \signal_acq_0_adddataout_[5] , 
        \signal_acq_0_adddataout_[4] , \signal_acq_0_adddataout_[3] , 
        \signal_acq_0_adddataout_[2] , \signal_acq_0_adddataout_[1] , 
        \signal_acq_0_adddataout_[0] }));
    scanstatetop scanstatetop_0 (.reset(scancode_0_resetout), .soft_d(
        soft_d), .sw_acq1(sw_acq1), .sw_acq2(sw_acq2), .rt_sw(rt_sw), 
        .n_acq(scanstatetop_0_n_acq), .dds_conf(
        scanstatetop_0_dds_conf), .calctrl(scanstatetop_0_calctrl), 
        .s_acq(scanstatetop_0_s_acq), .timeclk(clktodds), .scanstart(
        scancode_0_scanstart), .scanover(scanover));
    caltop caltop_0 (.calen(scanstatetop_0_calctrl), .calout(calout), 
        .load(scancode_0_calload), .reset(scancode_0_resetout), .clkin(
        ddsclkin), .divcount({\scancode_0_caldata_[5] , 
        \scancode_0_caldata_[4] , \scancode_0_caldata_[3] , 
        \scancode_0_caldata_[2] , \scancode_0_caldata_[1] , 
        \scancode_0_caldata_[0] }));
    
endmodule
