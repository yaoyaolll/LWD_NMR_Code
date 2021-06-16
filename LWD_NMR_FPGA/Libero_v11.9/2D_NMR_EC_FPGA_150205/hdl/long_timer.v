// long_timer.v

module long_timer( 
                  clk_5K,    
                  clk_sys,//输入时钟
                  rst_n,     //复位
                  start,
                  work,      //工作状态
                  timer_para, //定时数据输入
                  timeup     //定时器中断
                 );

input  clk_5K;         //定时器时钟
input  clk_sys;
input  rst_n;           //复位
input  start;
input  work;            //工作状态
input  [15:0] timer_para;   //定时数据输入

output timeup;          //定时器中断

reg timeup;          //定时器中断
reg [15:0] count;   //定时器计数器

reg clk_5K_reg1;
reg clk_5K_reg2;
wire clk_5K_en;

reg clear_n;

wire en;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             {clk_5K_reg1,clk_5K_reg2} <= 2'b0;
         else
             begin
                  clk_5K_reg1 <= clk_5K;
                  clk_5K_reg2 <= clk_5K_reg1;
             end
    end

assign clk_5K_en = (clk_5K_reg1 & (~clk_5K_reg2)) & (~work);

assign en = rst_n & start;

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)                  
             begin
                  count  <= 16'b0;
                  timeup <= 1'b0;
             end    
         else
             begin                
                  if (clk_5K_en == 1'b1)
                      begin
                           count <= count + 1;
                           if(clear_n == 1'b0)
                               timeup <= 1'b1;
                           else
                               timeup <= timeup;
                      end
               
             end              

   end

always @ (count or timer_para)
    begin
         if (count == timer_para)
             clear_n = 1'b0;
         else
             clear_n = 1'b1;
    end

endmodule