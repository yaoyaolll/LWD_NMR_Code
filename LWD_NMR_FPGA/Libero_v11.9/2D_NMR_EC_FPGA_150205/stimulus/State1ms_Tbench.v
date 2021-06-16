
//NoiseAcq.v

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
        xa = 'h0031;               //��λstate1ms
      #50
        xa = 'h0032;               //��λ����state1ms
      #50
        xa = 'h0033;               //state1ms�����ر�
      #50
        xa = 'h0035;               //state1ms����װ�عر�
      #50
        xa = 'h0068;               //bridge_load��λ
      #50
        xa = 'h006A;               //dump_load��λ
/***************************װ������noise״̬������*********************************/
      #50
        xa = 'h0037;
        xd_in = 16'd0;
      #50
        xa = 'h0038;
        xd_in = 16'd100;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load


      #50
        xa = 'h0037;
        xd_in = 16'd1;
      #50
        xa = 'h0038;
        xd_in = 16'd1000;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load


      #50
        xa = 'h0037;
        xd_in = 16'd2;
      #50
        xa = 'h0038;
        xd_in = 16'd1800;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load


      #50
        xa = 'h0037;
        xd_in = 16'd3;
      #50
        xa = 'h0038;
        xd_in = 16'd3000;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load



      #50
        xa = 'h0037;
        xd_in = 16'd4;
      #50
        xa = 'h0038;
        xd_in = 16'd28464;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load


      #50
        xa = 'h0037;
        xd_in = 16'd5;
      #50
        xa = 'h0038;
        xd_in = 16'd1;    //plusetime90
      #50
        xa = 'h0036;       //ʹ��load
      #50
        xa = 'h0035;       //ȡ��load

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


/************************************���ؿ���***********************************/
      #50
        xa = 'h0060;     //Mode = 10000
        xd_in = 16'd16;
/************************************����***********************************/
      #50
        xa = 'h0034;     //����
      #90000
        xa = 'h0034;     //����
    end

always 
    #17.635 ddsclkout <= !ddsclkout; // ���ù���Ƶ��886KHz��ddsʱ��28.352MHz
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
