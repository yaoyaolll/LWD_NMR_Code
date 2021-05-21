// dds_timer.v
module dds_timer (
                  clk_sys,
                  rst_n,
                  state_start,
                  state_over,
                  count
                 );
input clk_sys;
input rst_n;
input state_start;
input state_over;

output [7:0] count;

reg [7:0] count;

wire en;

assign en = state_over & state_start;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             count <= 8'b0;
         else
             begin
                  if (en == 1'b1)
                      count <= count + 1;
                  else
                      count <= 8'b0;
             end
    end

endmodule