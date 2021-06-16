// clk_5k.v
module clk_5k(
                  clk_10k,     
                  //clk_sys,//时钟输入
                  rst_n,
                  clk_5k     //时钟输出
                 );

input clk_10k;
//input clk_sys;
input rst_n;
output clk_5k;

reg clk_5k;
/*
reg clk_10k_reg1;
reg clk_10k_reg2;
wire clk_10k_en;
*/
/*
always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             {clk_10k_reg1,clk_10k_reg2} <= 2'b0;
         else
             begin
                  clk_10k_reg1 <= clk_10k;
                  clk_10k_reg2 <= clk_10k_reg1;
             end
    end

assign clk_10k_en = clk_10k_reg1 & (~clk_10k_reg2);
*/
always @ (posedge clk_10k)
    begin
         if (rst_n == 1'b0)
             begin
                  clk_5k  <= 1'b0;
             end
         else
            begin
                clk_5k <= ~clk_5k;
            end
   end
endmodule