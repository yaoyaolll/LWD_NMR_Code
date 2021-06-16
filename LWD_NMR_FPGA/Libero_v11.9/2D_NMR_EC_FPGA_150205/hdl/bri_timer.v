// bri_timer.v
module bri_timer(
                 clk_dds,
                 clk_4f_en,
                 rst_n,
                 state_start,
                 //clk_2f,
                 timer_stop,
                 count
                );
input clk_dds;
input clk_4f_en;//时钟为4倍工作频率
input rst_n;
input state_start;
input timer_stop;

//output clk_2f;
output [7:0] count;

//reg clk_2f; 
reg [7:0] count;
/*
always @ (negedge rst_n or posedge clk_4f)
    begin
         if (rst_n == 1'b0)
             clk_2f <= 1'b1;
         else
             clk_2f <= ~clk_2f;
    end
*/
wire clken;

assign clken = clk_4f_en & state_start & (~timer_stop);

always @ (negedge rst_n or posedge clk_dds)
    begin
         if (rst_n == 1'b0)
             count <= 8'b0;
         else
             begin
                  if (clken == 1'b1)

                      count <= count + 1;
                  else
                      count <= count;
//pluse_acq激励时间过长，导致count归零，故计到此时停止或清零，但内外侨顶层状态机为循环状态机，half信号一直在起作用故不能清零
             end
    end

endmodule