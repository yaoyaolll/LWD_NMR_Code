// off_on_state.v
module off_on_state(
                    clk_sys,
                    rst_n,
                    i,
                    off_on,
                    state_over
                   );

input clk_sys;
input rst_n;
input [1:0] i;

output off_on;
output state_over;

reg [1:0] ns;
reg [1:0] cs;

reg off_on;
reg state_over;

parameter [1:0] IDLE = 2'b00,
                S1   = 2'b01,
                S2   = 2'b10;

wire en;

assign en = rst_n & i[0];

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             cs <= IDLE;
         else
             cs <= ns;
    end

always @ (cs or i)
    begin
         //ns = 2'bx;
         case (cs)
             IDLE:
                 begin
                      if (i[0] == 1'b1)
                          ns = S1;
                      else
                          ns = IDLE;
                 end
             S1:
                 begin
                      if (i[1] == 1'b1)
                          ns = S2;
                      else
                          ns = S1;
                 end
             S2:
                 begin
                      ns =S2;
                 end
             default:
                 ns = IDLE;
         endcase
    end

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             begin
                  off_on     <= 1'b0;
                  state_over <= 1'b1;
             end
         else
             begin
                  //off_on <= 1'b0;
                  case (ns)
                      IDLE:
                          off_on <= 1'b0;
                      S1:
                          off_on <= 1'b1;
                      S2:
                          begin
                               off_on     <= 1'b0;
                               state_over <= 1'b0;
                          end
                      default:
                          begin
                               off_on     <= 1'b0;
                               state_over <= 1'b0;
                          end
                  endcase
             end
    end

endmodule