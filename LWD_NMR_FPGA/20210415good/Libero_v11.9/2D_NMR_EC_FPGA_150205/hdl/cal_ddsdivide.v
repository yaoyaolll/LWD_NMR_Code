// cal_ddsdivide.v

module cal_ddsdivide(
                     reset,     //复位
                     clkin,     //时钟输入
                     load,      //装载分频数据
                     divcount,  //分频数据
                     clkout     //时钟输出
                    );

input reset;
input clkin;
input load;
input [5:0] divcount;

output clkout;

reg    clkout;
reg    [5:0] count;
reg    [5:0] datainreg;

always @ (posedge load)
   begin
         datainreg <= divcount;
   end

always @ (posedge reset or posedge clkin)
   begin
         if(reset)
             begin
                   count <= 1;
                   clkout <= 0;
             end

         else 
             begin
                   if(count >= datainreg)
                         begin
                               count <= 1;
                               clkout <= ~clkout;
                         end        
                   else
                         begin
                               count <= count+1;
                         end
             end 
   end

endmodule