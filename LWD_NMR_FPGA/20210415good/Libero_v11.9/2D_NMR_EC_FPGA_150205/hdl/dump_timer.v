// dump_timer.v
module dump_timer(
                  clk_sys,
                  rst_n,
                  state_start,
                  timer_start,
                  count
                 );

input clk_sys;
input rst_n;
input state_start;
input timer_start;

output [11:0] count;

reg [11:0] count;

wire en;

assign en = state_start & timer_start;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             count <= 12'b0;
         else
             begin
                  if (en == 1'b1)
                      count <= count + 1;
                  else
                      count <= 12'b0;
             end
    end

endmodule