// qq_timer.v
module qq_timer(
             clk_sys,
             rst_n,
             statestart,
             stateover,
             count
            );
input clk_sys;
input rst_n;
input statestart;
input stateover;

output [4:0] count;

wire en;

reg [4:0] count;

assign en = statestart & stateover;

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