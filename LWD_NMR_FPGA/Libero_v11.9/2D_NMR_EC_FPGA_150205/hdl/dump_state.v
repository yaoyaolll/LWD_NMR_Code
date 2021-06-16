// dump_state.v
module dump_state(
                  clk_sys,
                  rst_n,
                  i,
                  off_start,
                  on_start,
                  timer_start
                 );

input clk_sys;
input rst_n;
input [8:0] i;

output off_start;
output on_start;
output timer_start;

reg off_start;
reg on_start;
reg timer_start;

reg [6:0] ns;
reg [6:0] cs;

parameter [6:0] IDLE = 7'b0000000,
                S1   = 7'b0000001,
                S2   = 7'b0000010,
                S3   = 7'b0000100,
                S4   = 7'b0001000,
                S5   = 7'b0010000,
                S6   = 7'b0100000,
                S7   = 7'b1000000;

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
                      if (i[2] == 1'b1)
                          ns = S3;
                      else
                          ns = S2;
                 end
             S3:
                 begin
                      if (i[1] == 1'b0)
                          ns = S4;
                      else
                          ns = S3;
                 end
             S4:
                 begin
                      if (i[3] == 1'b1)
                          ns = S5;
                      else
                          ns = S4;
                 end
             S5:
                 begin
                      case (i[8:4])
                          5'b00001,5'b00100: ns = S6;
                          5'b10000:          ns = S7;
                          default:           ns = S5;
                      endcase
                 end
             S6:
                 begin
                      if ((i[5] == 1'b1) || (i[7] == 1'b1))
                          ns = S5;
                      else
                          ns = S6;
                 end
             S7:
                 ns = S7;
         default:
                 ns = IDLE;
         endcase
    end

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             begin
                  {off_start,on_start} <= 2'b00;
                  timer_start          <= 1'b0;
             end
         else
             begin
                  case (ns)
                      IDLE:
                          {off_start,on_start} <= 2'b00;
                      S1:
                          {off_start,on_start} <= 2'b10;
                      S2:
                          {off_start,on_start} <= 2'b00;
                      S3:
                          {off_start,on_start} <= 2'b10;
                      S4:
                          begin
                               {off_start,on_start} <= 2'b00;
                               timer_start          <= 1'b1;
                          end
                      S5:
                          {off_start,on_start} <= 2'b01;
                      S6:
                          {off_start,on_start} <= 2'b10;
                      S7:
                          begin
                               {off_start,on_start} <= 2'b00;
                               timer_start          <= 1'b0;
                          end
                  default:
                          begin
                               {off_start,on_start} <= 2'b00;
                               timer_start          <= 1'b0;
                          end
                  endcase
             end
    end

endmodule