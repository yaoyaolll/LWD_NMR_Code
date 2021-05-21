// off_on_coder.v
module off_on_coder(
                    clk_sys,
                    rst_n,
                    state_start,
                    count,
                    i
                   );

input clk_sys;
input rst_n;
input state_start;
input [4:0] count;

output [1:0] i;

reg i_reg;
reg [1:0] i;

parameter [4:0] off_on_width = 5'd20;

always @ (count)
    begin
         case (count)
             off_on_width:
                 i_reg = 1'b1;
             default:
                 i_reg = 1'b0;
         endcase
    end

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             i <= 2'b0;
         else
             i <= {i_reg,state_start};
    end

endmodule