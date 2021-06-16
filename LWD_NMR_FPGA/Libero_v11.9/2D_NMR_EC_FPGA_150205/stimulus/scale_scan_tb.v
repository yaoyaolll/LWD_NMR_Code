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
        xa = 'h0060;               //Mode = 1
        xd_in = 16'd1;
              
      #50
        xa = 'h0061;               //��λscaletop
      #50
        xa = 'h0062;               //������λscaletop
      #50
        xa = 'h0064;               //�ر����
      #50
        xa = 'h0066;               //�ر����
      #50
        xa = 'h0068;               //�ر����
      #50
        xa = 'h006A;               //�ر����
/***************************װ������scale״̬������*********************************/
      #50
        xa = 'h006e;
        xd_in = 16'd0;
      #50
        xa = 'h006d;
        xd_in = 16'd3400;    //plusetime90
      #50
        xa = 'h0065;       //ʹ��load
      #50
        xa = 'h0066;       //ȡ��load
 
      #50
        xa = 'h006e;
        xd_in = 16'd1;
      #50
        xa = 'h006d;
        xd_in = 16'd5100;    //plusetime180
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd2;
      #50
        xa = 'h006d;
        xd_in = 16'd3140;    //dumptime
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load
 
      #50
        xa = 'h006e;
        xd_in = 16'd3;
      #50
        xa = 'h006d;
        xd_in = 16'd8000;    //s_dumptime
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd4;
      #50
        xa = 'h006d;
        xd_in = 16'd15000;    //cuttime90[15:0]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd5;
      #50
        xa = 'h006d;
        xd_in = 16'd0;     //cuttime90[21:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd6;
      #50
        xa = 'h006d;
        xd_in = 16'd25000;  //cuttime180[15:0]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd7;
      #50
        xa = 'h006d;
        xd_in = 16'd0;     //cuttime180[21:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd8;
      #50
        xa = 'h006d;
        xd_in = 16'd20000;    //opentime[15:0]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd9;
      #50
        xa = 'h006d;
        xd_in = 16'd0;      //opentime[19:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd10;
      #50
        xa = 'h006d;
        xd_in = 16'd2500;    //ACQTIME = 2500
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd11;
      #50
        xa = 'h006d;
        xd_in = 16'd3;    //NE_NUM = 20
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

/*------------------װ��-FunctionParts �ɼ���ز���-----------------*/
      #50
        xa = 'h006e;
        xd_in = 16'd12;
      #50
        xa = 'h006d;
        xd_in = 16'd48;    //ACQ90_NUM = 48  ��6���������ɼ�����48���㣬ɾȥǰ�棨30-6=24)*8=192����
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd13;
      #50
        xa = 'h006d;
        xd_in = 16'd88;    //ACQ180_NUM = 88 ��11���������ɼ�����88���㣬ɾȥǰ��(45-11)*8=272����
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd14;
      #50
        xa = 'h006d;
        xd_in = 16'd136;    //�ز��ɼ���������17����������ɼ����� 17*8 = 136
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd15;
      #50
        xa = 'h006d;
        xd_in = 16'd192;    //STRIPNUM90_NUM = 192
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load


      #50
        xa = 'h006e;
        xd_in = 16'd16;
      #50
        xa = 'h006d;
        xd_in = 16'd272;    //STRIPNUM180_NUM = 272
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

/********************************s_periodnum ����*********************************/

      #50
        xa = 'h0026;
        xd_in = 16'd8;   //read_scan_parameter������װ��
      #50
        xa = 'h0027;
        xd_in = 16'd1;   //scan_load = 1
      #50
        xa = 'h0028;
        xd_in = 16'd1;   //scan_load = 0

/*������������������-------------��DE parameters������������������������������������*/
      #50
        xa = 'h006e;
        xd_in = 16'd17;
      #50
        xa = 'h006d;
        xd_in = 16'd0;    //M_NUM = 0 ����CPMG����
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd18;
      #50
        xa = 'h006d;
        xd_in = 16'd50000;    //CUTTIME180_TEL[15:0] = 50000
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd19;
      #50
        xa = 'h006d;
        xd_in = 16'd0;    //CUTTIME180_TEL[21:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd20;
      #50
        xa = 'h006d;
        xd_in = 16'd20000;    //OPENTIME_TEL[15:0]  ����
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd21;
      #50
        xa = 'h006d;
        xd_in = 16'd0;    //OPENTIME_TEL[21:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd22;
      #50
        xa = 'h006d;
        xd_in = 16'd35000;    //CUTTIME180_Tini[15:0]  35000
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load

      #50
        xa = 'h006e;
        xd_in = 16'd23;
      #50
        xa = 'h006d;
        xd_in = 16'd0;    //CUTTIME180_Tini[21:16]
      #50
        xa = 'h0065;     //ʹ��load
      #50
        xa = 'h0066;     //ȡ��load


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

/*********************************װ��PAPS����*****************************/
     
      #50
        xa = 'h006b;  //pn_change = 1


/************************************���ؿ���***********************************/
      #50
        xa = 'h0060;     //Mode = 1
        xd_in = 16'd1;

/************************************����***********************************/
      #50
        xa = 'h0063;     //����
      #50
        xa = 'h009D;     //����  clk_en
      
      #1000000
      
      #50
        xa = 'h0064;     //�ر�״̬��
//*-----------------------------------------------�л���ɨƵģʽ------------------------------------------------*//
      #50
        xa = 'h0060;     //Mode = 2
        xd_in = 16'd2;

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
