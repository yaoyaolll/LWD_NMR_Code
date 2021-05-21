// dump_coder.v
module dump_coder(
                  clk_sys,
                  rst_n,
                  state_start,
                  pluse_start,
                  bri_cycle,
                  dump_load,
                  dump_choice,
                  dump_para,
                  count,
                  i
                 );

input clk_sys;
input rst_n;
input state_start;
input pluse_start;
input bri_cycle;
input dump_load;

input [2:0]  dump_choice;
input [11:0] dump_para;


input [11:0] count;

output [8:0] i;

reg [5:0] i_reg;
reg [8:0] i;

reg [11:0] para1;
reg [11:0] para2;
reg [11:0] para3;
reg [11:0] para4;
reg [11:0] para5;
reg [11:0] para6;

always @ (posedge clk_sys)
    begin
         if (dump_load == 1'b1)
             begin
                  case (dump_choice)
                      3'b000:
                          para1 <= dump_para;
                      3'b001:
                          para2 <= dump_para;
                      3'b010:
                          para3 <= dump_para;
                      3'b011:
                          para4 <= dump_para;
                      3'b100:
                          para5 <= dump_para;
                      3'b101:
                          para6 <= dump_para;
                      default:
                          begin
                               para1 <= 12'b0;
                               para2 <= 12'b0;
                               para3 <= 12'b0;
                               para4 <= 12'b0;
                               para5 <= 12'b0;
                               para6 <= 12'b0;
                          end
                  endcase
             end
         else
             begin
                  para1 <= para1;
                  para2 <= para2;
                  para3 <= para3;
                  para4 <= para4;
                  para5 <= para5;
                  para6 <= para6;
             end
    end

always @ (count or para1 or para2 or para3 or para4 or para5 or para6)
    begin
         //i_reg = 6'b0;
         case (count)
             para6:
                 i_reg = 6'b100000;
             para5:
                 i_reg = 6'b010000;
             para4:
                 i_reg = 6'b001000;
             para3:
                 i_reg = 6'b000100;
             para2:
                 i_reg = 6'b000010;
             para1:
                 i_reg = 6'b000001;
             default:
                 i_reg = 6'b0;
         endcase
    end

always @ (posedge clk_sys) 
    begin
         if (rst_n == 1'b0)
             i <= 9'b0;
         else
             i <= {i_reg,bri_cycle,pluse_start,state_start};
    end

endmodule