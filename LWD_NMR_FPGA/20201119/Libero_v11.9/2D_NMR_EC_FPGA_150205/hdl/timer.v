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
             rst_n,     //复位
             clk_sys,   //定时器时钟
             datain,    //定时数据输入
             work_n,      //工作状态
             state_start,
             state_over_n,
             time_up   //定时器中断
             );

input  rst_n;           //复位
input  clk_sys;         //定时器时钟
input  [21:0] datain;   //定时数据输入
input  work_n;            //工作状态
input  state_start;
input  state_over_n;

output time_up;          //定时器中断

reg    time_up;          //定时器中断
reg    [21:0] timedata; //定时器计数器
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
             rst_n,     //复位
             clk_sys,   //定时器时钟
             datain,    //定时数据输入
             work_n,      //工作状态
             state_start,
             state_over_n,
             time_up     //定时器中断
             );

input  rst_n;           //复位
input  clk_sys;         //定时器时钟
input  [21:0] datain;   //定时数据输入
input  work_n;            //工作状态
input  state_start;
input  state_over_n;

output time_up;          //定时器中断

reg    time_up;          //定时器中断
reg    [21:0] timedata; //定时器计数器

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