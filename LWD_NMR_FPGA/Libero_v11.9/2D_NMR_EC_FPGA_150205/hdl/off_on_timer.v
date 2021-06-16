// off_on_timer.v
module off_on_timer(
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

output [4:0] count;

reg [4:0] count;

wire en;

assign en = state_start & state_over;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             count <= 5'b0;
         else
             begin
                  if (en == 1'b1)
                      count <= count + 1;
                  else
                      count <= 5'b0;
             end
    end

endmodule
