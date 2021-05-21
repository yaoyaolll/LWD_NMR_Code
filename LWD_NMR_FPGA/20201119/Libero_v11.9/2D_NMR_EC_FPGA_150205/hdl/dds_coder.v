// dds_coder.v
module dds_coder(
                 clk_sys,
                 rst_n,
                 state_start,
                 count,
                 i
                );

input clk_sys;
input rst_n;
input state_start;
input [7:0] count;

output [3:0] i;

reg [2:0] i_reg;
reg [3:0] i;

parameter [7:0] rst_para1 = 8'd10,
                rst_para2 = 8'd14,
                over_para = 8'd96;
                //over_para = 8'd98;

always @ (count)
    begin
         case (count)
             rst_para1:
                 i_reg = 3'b001;
             rst_para2:
                 i_reg = 3'b010;
             over_para:
                 i_reg = 3'b100;
             default:
                 i_reg = 3'b000;
        endcase
    end

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             i <= 4'b0;
         else
             i <= {i_reg, state_start};
    end

endmodule