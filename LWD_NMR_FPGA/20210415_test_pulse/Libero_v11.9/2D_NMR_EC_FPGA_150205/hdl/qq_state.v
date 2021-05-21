// qq_state.v
module  qq_state(
                 clk_sys,
                 rst_n,
                 i,
                 Q1Q8_Q2Q7,
                 Q3Q6_Q4Q5,
                 stateover
                );

input clk_sys;
input rst_n;

input [3:0] i;

output Q1Q8_Q2Q7;
output Q3Q6_Q4Q5;

output stateover;

reg [3:0] ns;
reg [3:0] cs;

reg Q1Q8_Q2Q7;
reg Q3Q6_Q4Q5;

reg stateover;

wire en;

assign en = rst_n & i[0];

parameter [3:0]  IDLE = 4'b0000,
                 S1   = 4'b0001,
                 S2   = 4'b0010,
                 S3   = 4'b0100,
                 S4   = 4'b1000;

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             cs <= IDLE;
         else
             cs <= ns;
    end

always @ (cs or i)
    begin
         //ns = 4'bx;
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
                      if (i[3] == 1'b1)
                          ns = S4;
                      else
                          ns = S3;
                 end
             S4: 
                 begin
                      ns = S4;
                 end
             default:
                 ns = IDLE;
         endcase
    end

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             begin//复位之后stateover无效，rst_n为高后timer开始计时，状态机启动，状态机结束后stateover有效，timer停止计时
                  {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b00;
                  stateover             <= 1'b1;
             end
         else
             begin
                  //{Q1Q8,Q3Q6} <= 2'b00;
                  case (ns)
                      IDLE:
                          {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b00;
                      S1:
                          {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b10;
                      S2:
                          {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b11;
                      S3:
                          {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b10;
                      S4:
                          begin//S4跳到自身，故可以不输出stateover信号，但为停止计数器还是用了stateover
                               {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b00;
                               stateover             <= 1'b0;
                          end
                      default:
                          begin
                               {Q1Q8_Q2Q7,Q3Q6_Q4Q5} <= 2'b00;
                               stateover             <= 1'b0;
                          end
                  endcase
             end
    end

endmodule