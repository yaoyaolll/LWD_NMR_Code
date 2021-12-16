// clk_div500.v
module clk_div500(
                  clk_5M,     
                  clk_sys,//ʱ������
                  rst_n,
                  clk_5K     //ʱ��������޸�Ϊ��1KHz
                 );

input clk_5M;
input clk_sys;
input rst_n;
output clk_5K;

reg clk_5K;

reg [11:0] count;

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
                  count   <= 12'b1;
                  clk_5K <= 1'b0;
             end
         else
             begin
                  if(clk_5M_en == 1'b1)
                    begin
                      if (clear_n == 1'b0)
                        begin
                           count   <= 12'b1;
                           clk_5K <= ~clk_5K;
                        end        
                      else
                        begin
                           count   <= count + 1;
                           clk_5K <= clk_5K;
                        end
                    end
                  else
                    begin
                      count   <= count;
                      clk_5K <= clk_5K;
                    end
             end
   end

always @ (count)
    begin
         if (count == 12'd2500)
             clear_n = 1'b0;
         else
             clear_n = 1'b1;
    end

endmodule