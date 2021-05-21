///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <Name>
//
// File: <timer.v>
// File history:
//      <Revision number>: <2014-03-14>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <Description here>
//
// Targeted device: <Family> <Die> <Package>
// Author: <Name>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 



module timer( 
             rst_n,     //��λ
             clk_sys,   //��ʱ��ʱ��
             datain,    //��ʱ��������
             work_n,      //����״̬
             state_start,
             state_over_n,
             time_up   //��ʱ���ж�
             );

input  rst_n;           //��λ
input  clk_sys;         //��ʱ��ʱ��
input  [21:0] datain;   //��ʱ��������
input  work_n;            //����״̬
input  state_start;
input  state_over_n;

output time_up;          //��ʱ���ж�

reg    time_up;          //��ʱ���ж�
reg    [21:0] timedata; //��ʱ��������
//wire   [21:0] timedata1;
wire   cmp_result;
wire   [21:0] datain; 
wire   en;
wire   rst_n_w;

assign en      = state_start & state_over_n;
assign rst_n_w = rst_n       & !work_n;

always @ (posedge clk_sys)
    begin
         if (rst_n_w == 1'b0)
             begin
                  timedata <= 22'b1;
                  time_up <=  1'b0;
             end    
         else
             begin                
                  if (en == 1'b1)
                      begin
                           timedata <= timedata + 1'b1;
                           time_up <= cmp_result;
                      end
                  else
                      begin
                           timedata <= 22'b1;
                           time_up <=  1'b0;
                      end
             end              

    end


//Timer_Inc Timer_Inc_0(timedata,timedata1);
Timer_Cmp Timer_Cmp_0(timedata,datain,cmp_result);

endmodule  


/*
module timer( 
             rst_n,     //��λ
             clk_sys,   //��ʱ��ʱ��
             datain,    //��ʱ��������
             work_n,      //����״̬
             state_start,
             state_over_n,
             time_up     //��ʱ���ж�
             );

input  rst_n;           //��λ
input  clk_sys;         //��ʱ��ʱ��
input  [21:0] datain;   //��ʱ��������
input  work_n;            //����״̬
input  state_start;
input  state_over_n;

output time_up;          //��ʱ���ж�

reg    time_up;          //��ʱ���ж�
reg    [21:0] timedata; //��ʱ��������

reg clear_n;

wire en;
wire rst_n_w;

assign en      = state_start & state_over_n;
assign rst_n_w = rst_n       & !work_n;

always @ (posedge clk_sys)
    begin
         if (rst_n_w == 1'b0)
             begin
                  timedata <= 22'b0;
                  time_up <=  1'b0;
             end    
         else
             begin                
                  if (en == 1'b1)
                      begin
                           timedata <= timedata + 1;
                           time_up <= clear_n;
                      end
                  else
                      begin
                           timedata <= 22'b0;
                           time_up <=  1'b0;
                      end
             end              

    end


always @ (timedata or datain)
    begin
         if (timedata == datain)
             clear_n = 1'b1;
         else
             clear_n = 1'b0;
    end

endmodule

*/