// clk_div10.v

module clk_div10(
                     clkin,     //时钟输入
                     clkout     //时钟输出
                    );

input clkin;

output clkout;

reg    clkout;
reg    [2:0] count;


always @ (posedge clkin)
   begin
                   if(count >= 5)
                         begin
                               count <= 1;
                               clkout <= ~clkout;
                         end        
                   else
                         begin
                               count <= count+1;
                         end
   end

endmodule