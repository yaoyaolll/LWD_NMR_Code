// TestBench_Pulse.v
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
        xa = 'h0086;               //��λplusetop
      #50
        xa = 'h0087;               //��λ����plusetop
/**------------------***��λscaleģ�飬bbch�ź�*****------------------**/
      #50
        xa = 'h0061;               //��λscaletop
      #50
        xa = 'h0062;               //������λscaletop
/**-------------------------------------------------------------------**/
      #50
        xa = 'h0085;               //noise�����ر�
      #50
        xa = 'h0089;               //noise ����װ�عر�
      #50
        xa = 'h0068;               //bridge_load��λ
      #50
        xa = 'h006A;               //dump_load��λ
/***************************װ������scan״̬������*********************************/
      #50
        xa = 'h008B;
        xd_in = 16'd0;
      #50
        xa = 'h008C;
        xd_in = 16'd10000;    //plusetime90
      #50
        xa = 'h0088;       //ʹ��load
      #50
        xa = 'h0089;       //ȡ��load

      #50
        xa = 'h008A;
        xd_in = 16'd0;
      #50
        xa = 'h008C;
        xd_in = 16'd3140;    //plusetime90
      #50
        xa = 'h0088;       //ʹ��load
      #50
        xa = 'h0089;       //ȡ��load



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
/********************************װ��pd_pluse_top����*******************************/
      #50
        xa = 'h00A4;
        xd_in = 16'd1;  
      #50
        xa = 'h00A5;
        xd_in = 16'd136; //
      #50
        xa = 'h00A6;     //ʹ��load
      #50
        xa = 'h00A7;     //ȡ��load

      #50
        xa = 'h00A4;
        xd_in = 16'd2;   
      #50
        xa = 'h00A5;
        xd_in = 16'd1100; 
      #50
        xa = 'h00A6;     //ʹ��load
      #50
        xa = 'h00A7;     //ȡ��load

      #50
        xa = 'h00A4;
        xd_in = 16'd3;   
      #50
        xa = 'h00A5;
        xd_in = 16'd1582; 
      #50
        xa = 'h00A6;     //ʹ��load
      #50
        xa = 'h00A7;     //ȡ��load


/*******************************SD ģ���������**********************************/
      #50
        xa = 'h0074;
        xd_in = 16'd1;  
      #50
        xa = 'h0075;
        xd_in = 16'd139; //   SD����1
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd2;  
      #50
        xa = 'h0075;
        xd_in = 16'd1103; //   SD����2
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd3;  
      #50
        xa = 'h0075;
        xd_in = 16'd1585; //   SD����3
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd4;  
      #50
        xa = 'h0075;
        xd_in = 16'd9777; //   SD����4
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd5;  
      #50
        xa = 'h0075;
        xd_in = 16'd0; //   SD����5
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd6;  
      #50
        xa = 'h0075;
        xd_in = 16'd10377; //   SD����6
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

      #50
        xa = 'h0074;
        xd_in = 16'd7;  
      #50
        xa = 'h0075;
        xd_in = 16'd0; //   SD����7
      #50
        xa = 'h0076;     //ʹ��load
      #50
        xa = 'h0077;     //ȡ��load

/******************************װ��bridge_div PLUSE����*******************************/

      #50
        xa = 'h006F;
        xd_in = 16'd20725;    //PLUSE ģ�� ȷ�� Q1Q8 �� Q3Q6 ������ 20
      #50
        xa = 'h0067;     //ʹ��load
      #50
        xa = 'h0068;     //ȡ��load

      #50
        xa = 'h0070;
        xd_in = 16'd32;    //32 ������Ƶ������� 32/8=4
      #50
        xa = 'h0067;     //ʹ��load
      #50
        xa = 'h0068;     //ȡ��load

      #50
        xa = 'h0073;
        xd_in = 16'd36;    //36 0x100100 = 36 bridge_div ģ�����
      #50
        xa = 'h0067;     //ʹ��load
      #50
        xa = 'h0068;     //ȡ��load

/****************************functionparts ����*********************************/
      #50
        xa = 'h0023;
        xd_in = 16'd300;
      #50
        xa = 'h0021;     //ʹ��load
      #50
        xa = 'h0022;     //ȡ��load

      #50
        xa = 'h0024;
        xd_in = 16'd330;
      #50
        xa = 'h0021;     //ʹ��load
      #50
        xa = 'h0022;     //ȡ��load

/************************************phase����***********************************/
      #50
        xa = 'h006b;  //pn_change = 1

/************************************���ؿ���***********************************/
      #50
        xa = 'h0033;      //state_1ms-start = 0 ;     
        xd_in = 16'd0;

      #50
        xa = 'h0083;     //pluse_scale = 0;   
        xd_in = 16'd0;

      #50
        xa = 'h0004;       //n_s_ctrl = 1 
        xd_in = 16'd0;


      #50
        xa = 'h0081;       //pluse_noise_ctrl = 0 
        xd_in = 16'd0;

      #50
        xa = 'h0060;       //change = 2;  
        xd_in = 16'd2;

/************************************����***********************************/
      #50
        xa = 'h0084;     //����
      #50
        xa = 'h009D;     //����  clk_en
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