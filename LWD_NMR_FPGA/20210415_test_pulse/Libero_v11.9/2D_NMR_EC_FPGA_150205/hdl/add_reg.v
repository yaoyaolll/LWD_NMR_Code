// add_reg.v

module add_reg(
               clk,
               addin,
               addresult,
               rst_n
               );

input  clk;
input  rst_n;
input  [11:0] addin;

output [19:0] addresult;

reg    [19:0] addresult;


always @ (negedge rst_n or posedge clk)
   begin
         if (rst_n == 1'b0)
             begin
                   addresult <= 0;
             end

         else
             begin
                   addresult <= addresult + addin;
             end
   end

endmodule