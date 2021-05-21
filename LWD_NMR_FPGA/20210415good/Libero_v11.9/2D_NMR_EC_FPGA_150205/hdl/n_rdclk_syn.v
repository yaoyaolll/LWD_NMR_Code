// n_rdclk_syn.v
module n_rdclk_syn(
                   rst_n,
                   clk_sys,
                   clken,
                   xrd,
                   n_rdclk
                  );

input rst_n;
input clk_sys;
input clken;
input xrd;

output n_rdclk;

reg n_rdclk;
reg clk_reg1;
reg clk_reg2;

wire clk_wire;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             {clk_reg1,clk_reg2} <= 2'b0;
         else
             begin
                  clk_reg1 <= xrd;
                  clk_reg2 <= clk_reg1;
             end
    end

assign clk_wire = ~((~clk_reg1) & clk_reg2);//检测下降沿，并取反以配合后续模块

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             n_rdclk <= 1'b0;
         else
           if (clken == 1'b1)
             n_rdclk <= clk_wire;
           else
             n_rdclk <= 1'b0;
    end

endmodule