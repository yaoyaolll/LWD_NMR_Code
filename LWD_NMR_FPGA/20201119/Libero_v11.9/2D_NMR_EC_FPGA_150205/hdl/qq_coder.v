// qq_coder.v
module qq_coder(
             clk_sys,
             rst_n,
             state_start,
             count,
             qq_para1,
             qq_para2,
             qq_para3,
             i
            );
input clk_sys;
input rst_n;
input state_start;

input [4:0] count;
input [3:0] qq_para1;
input [5:0] qq_para2;
input [5:0] qq_para3;

output [3:0] i;

reg [2:0] i_reg;
reg [3:0] i;

always @ (count or qq_para1 or qq_para2 or qq_para3)
    begin
         case (count)
             qq_para3:
                 i_reg = 3'b100;
             qq_para2:
                 i_reg = 3'b010;
             qq_para1:
                 i_reg = 3'b001;
             default:
                 i_reg = 3'b000;
         endcase
    end

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             i <= 4'b0000;
         else
             i <= {i_reg,state_start};
    end

endmodule