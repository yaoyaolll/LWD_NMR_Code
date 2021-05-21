// clk_10k.v

module clk_10k(
                  clk_5M,     
                  clk_sys,//时钟输入
                  rst_n,
                  clock_10khz     //时钟输出
                 );

input clk_5M;
input clk_sys;
input rst_n;
output clock_10khz;

reg clock_10khz;

reg [8:0] count;

reg clk_5M_reg1;
reg clk_5M_reg2;
wire clk_5M_en;

reg clear_n;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             {clk_5M_reg1,clk_5M_reg2} <= 2'b0;
         else
             begin
                  clk_5M_reg1 <= clk_5M;
                  clk_5M_reg2 <= clk_5M_reg1;
             end
    end

assign clk_5M_en = clk_5M_reg1 & (~clk_5M_reg2);

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  count   <= 9'b1;
                  clock_10khz <= 1'b0;
             end
         else
             begin
                  if(clk_5M_en == 1'b1)
                    begin
                      if (clear_n == 1'b0)
                        begin
                           count   <= 9'b1;
                           clock_10khz <= ~clock_10khz;
                        end        
                      else
                        begin
                           count   <= count + 1;
                           clock_10khz <= clock_10khz;
                        end
                    end
                  else
                    begin
                      count   <= count;
                      clock_10khz <= clock_10khz;
                    end
             end
   end

always @ (count)
    begin
         if (count == 9'd250)
             clear_n = 1'b0;
         else
             clear_n = 1'b1;
    end

endmodule