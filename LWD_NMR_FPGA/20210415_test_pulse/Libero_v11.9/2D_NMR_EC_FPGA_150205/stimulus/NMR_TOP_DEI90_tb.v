// NMR_TOP_DEI90_tb.v
//This stimulus file is a test for DE.
/*
  Parameter:
  TES   |TEL   |MN  |freq    |Pulse 90 width|Ne    |
  --------------------------------------------------
  0.5ms |8ms   |2   |886kHz  |36us          |1002  |
*/
`timescale 1ns/100ps

module testbench;

//in and inout port 
wire [15:0] xd;

reg OCX40MHz;

reg tri_ctrl;
reg [18:0] xa;
reg [11:0] ADC;

reg reset;
reg ddsclkout;
reg XRD;
reg zcs2;
reg xwe;

//out port
wire soft_dump;
wire sw_acq1;
wire sw_acq2;
wire cal_out;

wire calcuinter;
wire ddsdata;
wire ddsfqud;
wire ddsreset;
wire ddswclk;

wire dumpon;
wire dumpoff;

wire GLA;
wire interupt;
wire k1;
wire k2;

wire pd_pulse_en;
wire pulse_start;

wire Q1Q8;
wire Q3Q6;
wire Q4Q5;
wire Q2Q7;

wire Acq_clk;
wire rt_sw;
wire s_acq180;
wire sd_acq_en;
wire sigtimeup;

wire [15:0] relayclose_on;

reg link;
reg [15:0] xd_in;
assign xd=link?xd_in:16'bzzzzzzzzzzzzzzzz;

initial
    begin
      zcs2 = 1'b0 ;              //0有效
      xwe = 1'b0;                //上升沿检测电路
      OCX40MHz = 1'b0;
      ddsclkout = 1'b0;
      tri_ctrl = 1'b0;           //0有效
      reset = 0;
      link = 1;
      xa = 19'd0;
      xd_in = 16'd0;

      XRD = 1'b1;
      ADC = 12'd0;
    end

initial
    begin
      #5000
        reset = 1;
      #500
        reset = 0;
		
//Select Scale Channel
	  #20
	    xa = 'h0060;
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0005;
		//xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
	  #20
	    xa = 'h0082;
		//xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0033;     //state_1ms_choice开关
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
		
//复位scaletop
		
      #20
        xa = 'h0064;  
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;			
      #20
        xa = 'h0061;  
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;			
      #20
        xa = 'h0062;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
/*
		#20
        xa = 'h0066;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0068;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;			
 */
		
//Load dump parameters
	  #20
	    xa = 'h0071;
		xd_in = 16'd0;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd280;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
		
	  #20
	    xa = 'h0071;
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd380;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;			
		
	  #20
	    xa = 'h0071;
		xd_in = 16'd2;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd660;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

	  #20
	    xa = 'h0071;
		xd_in = 16'd3;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd760;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
		
	  #20
	    xa = 'h0071;
		xd_in = 16'd4;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd1040;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

	  #20
	    xa = 'h0071;
		xd_in = 16'd5;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0072;
		xd_in = 16'd3040;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0069;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006A;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
		
//Load inout-bridge parameters		
	  #20
	    xa = 'h006F;
		xd_in = 16'd20725;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
	  #20
	    xa = 'h0068;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0067;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0068;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		

	  #20
	    xa = 'h0070;
		xd_in = 16'd32;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0067;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0068;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

	  #20
	    xa = 'h0073;
		xd_in = 16'd36;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0067;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0068;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

//Load dds parameters		
	  #20
	    xa = 'h0019;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0015; 
		xd_in = 16'd50247;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0017;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0016;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0017;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
	  #20
	    xa = 'h0018;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0015; 
		xd_in = 16'd18580;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0016;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0017;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

//Load signal parameters		
      #20
        xa = 'h0026; 
		xd_in = 16'd8;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0028;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0027;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0028;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
		
//Load pd parameters		
      #20
        xa = 'h00A4; 
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h00A5; 
		xd_in = 16'd136;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A7;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A6;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A7;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h00A4; 
		xd_in = 16'd2;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h00A5; 
		xd_in = 16'd1157;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A6;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A7;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h00A4; 
		xd_in = 16'd3;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h00A5; 
		xd_in = 16'd1667;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A6;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A7;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
//Load sd parameters		
      #20
        xa = 'h0074; 
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd139;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h0074; 
		xd_in = 16'd2;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd1160;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h0074; 
		xd_in = 16'd3;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd1670;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h0074; 
		xd_in = 16'd4;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd8402;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h0074; 
		xd_in = 16'd5;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd0;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h0074; 
		xd_in = 16'd6;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd9002;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h0074; 
		xd_in = 16'd7;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd0;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h0074; 
		xd_in = 16'd8;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd49186;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h0074; 
		xd_in = 16'd9;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
		
      #20
        xa = 'h0074; 
		xd_in = 16'd10;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd49786;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
      #20
        xa = 'h0074; 
		xd_in = 16'd11;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0075; 
		xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0076;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0077;   
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;		
		
//Load scale parameters
      #20
        xa = 'h006E;
        xd_in = 16'd0;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006D;
        xd_in = 16'd3600;    //plusetime90
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;       //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;       //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;       //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
 
      #20
        xa = 'h006E;
        xd_in = 16'd1;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006D;
        xd_in = 16'd5400;    //plusetime180
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;       //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;       //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006E;
        xd_in = 16'd2;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006D;
        xd_in = 16'd3140;    //dumptime
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
 
      #20
        xa = 'h006E;
        xd_in = 16'd3;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006D;
        xd_in = 16'd8000;    //s_dumptime
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd4;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd55689;    //cuttime90[15:0]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd5;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd5;     //cuttime90[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd6;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd18028;  //cuttime180[15:0]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd7;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd0;     //cuttime180[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd8;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd12295;    //opentime[15:0]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd9;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd0;      //opentime[19:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd10;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd2117;    //ACQTIME = 2500
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd11;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd10;    //NE_NUM = 10
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd12;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd48;    //ACQ90_NUM = 48  按6个脉冲来采集，公48个点，删去前面（30-6=24)*8=192个点
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd13;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd88;    //ACQ180_NUM = 88 按11个脉冲来采集，公88个点，删去前面(45-11)*8=272个点
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #50
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #50
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd14;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd136;    //回波采集个数，俺17个脉冲个数采集，公 17*8 = 136
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd15;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd200;    //STRIPNUM90_NUM = 192
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;


      #20
        xa = 'h006e;
        xd_in = 16'd16;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd288;    //STRIPNUM180_NUM = 272
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd17;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd2;    //M_NUM = 0 发射CPMG脉冲
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

      #20
        xa = 'h006e;
        xd_in = 16'd18;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h006d;
        xd_in = 16'd65348;    //CUTTIME180_TEL[15:0] = 50000
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	

      #20
        xa = 'h006e;
        xd_in = 16'd19;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd5;    //CUTTIME180_TEL[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
		
      #20
        xa = 'h006e;
        xd_in = 16'd20;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd59615;    //OPENTIME_TEL[15:0]  不变
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;			
		
      #20
        xa = 'h006e;
        xd_in = 16'd21;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd5;    //OPENTIME_TEL[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	

      #20
        xa = 'h006e;
        xd_in = 16'd22;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd18028;    //CUTTIME180_Tini[15:0]  35000
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	

      #20
        xa = 'h006e;
        xd_in = 16'd23;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd0;    //CUTTIME180_Tini[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	

      #20
        xa = 'h006e;
        xd_in = 16'd24;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd6969;    //CUTTIMEI90[15:0]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

     #20
        xa = 'h006e;
        xd_in = 16'd25;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h006d;
        xd_in = 16'd0;    //CUTTIMEI90[21:16]
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0065;     //使能load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
      #20
        xa = 'h0066;     //取消load
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;

//Load phase parameter
      #20
        xa = 'h006c;  //pn_change = 1
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
	
//Load dump_sustain_timer parameter
      #20
        xa = 'h00AA;  
        xd_in = 16'd5;
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;
      #20
        xa = 'h00A8;  
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0; 
 //inv_turn enable      
      #20
        xa = 'h00Ab;  
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;             	
//Enable acquisition clock
      #20
        xa = 'h009D;  
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
		
//Start
      #20
        xa = 'h0063;     //启动	
	  #20
	    xwe = 1'b1;
	  #20
	    xwe = 1'b0;	
    end

always 
    #17.635 ddsclkout <= !ddsclkout; // 设置工作频率886KHz，dds时钟28.352MHz
always 
    #12.5 OCX40MHz <= !OCX40MHz;

NMR_TOP NMR_TOP_0
(
//in and inout port 
.xd(xd),

.OCX40MHz(OCX40MHz),

.tri_ctrl(tri_ctrl),
.xa(xa),
.ADC(ADC),

.gpio(reset),
.ddsclkout(ddsclkout),
.XRD(XRD),
.zcs2(zcs2),
.xwe(xwe),

//out port
.soft_dump(soft_dump),
.sw_acq1(sw_acq1),
.sw_acq2(sw_acq2),
.cal_out(cal_out),

.calcuinter(calcuinter),
.ddsdata(ddsdata),
.ddsfqud(ddsfqud),
.ddsreset(ddsreset),
.ddswclk(ddswclk),

.dumpon(dumpon),
.dumpoff(dumpoff),

.GLA(GLA),
.interupt(interupt),
.k1(k1),
.k2(k2),

.pd_pulse_en(pd_pulse_en),
.pulse_start(pulse_start),

.Q1Q8(Q1Q8),
.Q3Q6(Q3Q6),
.Q4Q5(Q4Q5),
.Q2Q7(Q2Q7),

.Acq_clk(Acq_clk),
.rt_sw(rt_sw),
.s_acq180(s_acq180),
.sd_acq_en(sd_acq_en),
.sigtimeup(sigtimeup),

.relayclose_on(relayclose_on)
);

endmodule