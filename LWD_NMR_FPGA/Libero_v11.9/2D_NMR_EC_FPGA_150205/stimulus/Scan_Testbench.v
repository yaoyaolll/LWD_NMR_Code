// Scan_Testbench.v
// Scan_Tbench.v

`timescale 1ns/1ps

module testbench;

reg  zcs2;
reg  xwe;
reg  clk;
reg  ddsclkout;
reg  tri_ctrl;
reg  reset;
reg  [18:0] xa;
reg code_en;
reg[11:0] ADC;
reg XRD;

wire  [15:0] xd;

//wire ddsfqud;
//wire ddsreset;
//wire ddswclk;
//wire ddsdata;

wire GLA;
wire rt_sw;
wire soft_dump;
wire sw_acq1;
wire sw_acq2;
wire pulse_start;
wire pd_pulse_en;
wire Q1Q8;
wire Q3Q6;
wire Q4Q5;
wire Q2Q7;
wire dumpon;
wire dumpoff;
wire calcuinter;
wire sigtimeup;
//wire k1;
//wire k2;
wire Acq_clk;
wire sd_acq_en;
wire s_acq180;
//wire relayclose_on;
wire cal_out;
wire interupt;



reg link;
reg [15:0] xd_in;
assign xd=link?xd_in:16'bzzzzzzzzzzzzzzzz;

initial
    begin
      zcs2 = 1'b0 ;              //0��Ч
      xwe = 1'b0;                //�����ؼ���·
      clk = 1'b0;
      ddsclkout = 1'b0;
      tri_ctrl = 1'b0;           //0��Ч
      reset = 1;
      link = 1;
      xa = 19'd0;
      xd_in = 16'd0;
      code_en = 1'b0;

      XRD = 1'b0;
      ADC = 12'd0;
    end

initial
    begin
      #500
        reset = 0;
      #500
        zcs2 = 1'b0 ;
        xwe = 1'b1;                //�����ؼ���·
        tri_ctrl = 1'b0;
        code_en = 1'b1;
      
      #50
        xa = 'h0008;               //��λscantop
      #50
        xa = 'h0009;               //��λ����scantop
      #50
        xa = 'h000B;               //�����ر�
      #50
        xa = 'h0096;               //��λ
      #50
        xa = 'h0068;               //��λ
      #50
        xa = 'h006A;               //��λ
/***************************װ������scan״̬������*********************************/
      #50
        xa = 'h0094;
        xd_in = 16'd0;
      #50
        xa = 'h0097;
        xd_in = 16'd7200;    //plusetime90
      #50
        xa = 'h0095;       //ʹ��load
      #50
        xa = 'h0096;       //ȡ��load

      #50
        xa = 'h0093;
        xd_in = 16'd0;
      #50
        xa = 'h0097;
        xd_in = 16'd21000;    //plusetime90
      #50
        xa = 'h0095;       //ʹ��load
      #50
        xa = 'h0096;       //ȡ��load



/*************************************װ��dump����*************************************/
      #50
        xa = 'h0071;
        xd_in = 16'd0;
      #50
        xa = 'h0072;
        xd_in = 16'd280;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

      #50
        xa = 'h0071;
        xd_in = 16'd1;
      #50
        xa = 'h0072;
        xd_in = 16'd380;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

      #50
        xa = 'h0071;
        xd_in = 16'd2;
      #50
        xa = 'h0072;
        xd_in = 16'd660;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

      #50
        xa = 'h0071;
        xd_in = 16'd3;
      #50
        xa = 'h0072;
        xd_in = 16'd760;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

      #50
        xa = 'h0071;
        xd_in = 16'd4;
      #50
        xa = 'h0072;
        xd_in = 16'd1040;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

      #50
        xa = 'h0071;
        xd_in = 16'd5;
      #50
        xa = 'h0072;
        xd_in = 16'd3040;    //
      #50
        xa = 'h0069;     //ʹ��load
      #50
        xa = 'h006A;     //ȡ��load

/*----------------CALģ���������--------------------------*/
      #50
        xa = 'h001A;
        xd_in = 16'd32;
      #50
        xa = 'h001B;     //ʹ��load
      #50
        xa = 'h001C;     //ȡ��load

/*****************************************************************/
      #50
        xa = 'h0060;     //Mode = 2     //Ϊ��װ��s_periodnum����.��Ҫ��ѡ��ɨƵͨ��
        xd_in = 16'd2;

      #50
        xa = 'h0026;
        xd_in = 16'd8;   //read_scan_parameter������װ��
      #50
        xa = 'h0027;
        xd_in = 16'd1;   //scan_load = 1
      #50
        xa = 'h0028;
        xd_in = 16'd1;   //scan_load = 0

      #50
        xa = 'h0025;                           //ɨƵs_acqnum�ɵ�ַ���봫��
        xd_in = 16'd136;
      #50
        xa = 'h0027;     //ʹ��load
      #50
        xa = 'h0028;     //ȡ��load

/************************************���ؿ���*******************************/
      #50
        xa = 'h0060;     //change = 2
        xd_in = 16'd2;
/************************************����***********************************/
      #50
        xa = 'h000A;     //����

      #50
        xa = 'h009D;     //����  clk_en
    end

always 
    #17.635 ddsclkout <= !ddsclkout;        //ddsʱ��886K
always 
    #12.5 clk <= !clk;

NMR_TOP NMR_TOP_0
(
.zcs2(zcs2),
.xwe(xwe),
.OCX40MHz(clk),
.GLA(GLA),
.ddsclkout(ddsclkout),
.tri_ctrl(tri_ctrl),
.gpio(reset),
.xa(xa),
.xd(xd),
.code_en(code_en),
.ADC(ADC),
.XRD(XRD),

//.ddsfqud(ddsfqud),
//.ddsreset(ddsreset),
//.ddswclk(ddswclk),
//.ddsdata(ddsdata),
.rt_sw(rt_sw),
.soft_dump(soft_dump),
.sw_acq1(sw_acq1),
.sw_acq2(sw_acq2),
.pulse_start(pulse_start),
.pd_pulse_en(pd_pulse_en),
.Q1Q8(Q1Q8),
.Q3Q6(Q3Q6),
.Q4Q5(Q4Q5),
.Q2Q7(Q2Q7),
.dumpon(dumpon),
.dumpoff(dumpoff),
.calcuinter(calcuinter),
.sigtimeup(sigtimeup),
//.k1(k1),
//.k2(k2),
.Acq_clk(Acq_clk),
.sd_acq_en(sd_acq_en),
.s_acq180(s_acq180),
//.relayclose_on(relayclose_on),
.cal_out(cal_out),
.interupt(interupt)
);

endmodule
