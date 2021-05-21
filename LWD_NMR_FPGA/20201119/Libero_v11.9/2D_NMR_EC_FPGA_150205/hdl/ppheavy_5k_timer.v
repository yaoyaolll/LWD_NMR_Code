// ppheavy_timer.v
module ppheavy_on_timer(
                    //clk_sys,
                    rst_n,
                    state_start,
                    start,
                    clk_10k
                   );

//input clk_sys;
input rst_n;
input state_start;

input clk_10k;

output start;
reg start;

reg [5:0] count;


//always @ (posedge clk_10k or  negedge rst_n)
always @ (posedge clk_10k)
    begin
         if (rst_n == 1'b0)
             count <= 6'b0;
         else
             begin
                  if (state_start == 1'b1)
                      count <= count + 1;
                 
                  else
                      count <= 0;
             end
    end
always @ (posedge clk_10k)
    begin
         if (rst_n == 1'b0)
             start <= 0;
         else
             begin
                  if (count==6'd20||count==6'd35)
                      start <= 1;
                 
                  else
                      start <= 0;
             end
    end
endmodule
