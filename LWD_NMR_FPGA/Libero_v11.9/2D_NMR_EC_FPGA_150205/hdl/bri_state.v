// bri_state.v
module  bri_state(
                  clk_dds,
                  clk_4f_en,
                  rst_n,
                  //clk_2f,
                  i,
                  up,
                  down
                 );

input clk_dds;
input clk_4f_en;
input rst_n;
//input clk_2f;

input [4:0] i;

output up;
output down;

reg up;
reg down;

reg [13:0] ns;
reg [13:0] cs;

parameter [13:0] IDLE = 14'b00000000000000,
                 S0   = 14'b00000000000001,
                 S00  = 14'b00000000000010,
                 S1   = 14'b00000000000100,
                 S10  = 14'b00000000001000,
                 S2   = 14'b00000000010000,
                 S20  = 14'b00000000100000,
                 S3   = 14'b00000001000000,
                 S30  = 14'b00000010000000,
                 S4   = 14'b00000100000000,
                 S40  = 14'b00001000000000,
                 S5   = 14'b00010000000000,
                 S50  = 14'b00100000000000,
                 S6   = 14'b01000000000000,
                 S60  = 14'b10000000000000;
wire en;

assign en = rst_n & i[0];

always @ (negedge en or posedge clk_dds)
    begin
         if (en == 1'b0)
             cs <= IDLE;
         else
             begin
                  if (clk_4f_en == 1'b1)
                      cs <= ns;
                  else
                      cs <= cs;
             end
    end
always @ (cs or i)
    begin
         //ns = 4'bx;
         case (cs)
             IDLE:
                 begin
                      if (i[0] == 1'b1)
                          begin//启动后首先判断90°或180°激励
                               if (i[3] == 1'b0)
                                   begin//................90
                                       if (i[4] == 1'b1)
                                           begin
                                               if(i[2] == 1'b0)
                                                   ns = S1;//....90正相
                                               else
                                                   ns = S4;
                                            end
                                        else
                                            ns = S00;
                                   end
                               else
                                   ns = S0;//............180
                          end
                      else
                          ns = IDLE;
                 end
             S00:
                 ns = S0;
             S0:
                 begin
                      if(i[2] == 1'b0)
                          ns = S1;//....180正相
                      else
                          ns = S4;
                 end
             S1:
                 ns = S10;
             S10:
                 begin//判断是否处于半频激励时间
                      if ((i[2] == 1'b0) && (i[1] == 1'b0))
                          ns = S2;//正相半频
                      else
                          ns = S4;//正相全频或反相半频
                 end
             S2:
                 ns = S20;
             S20:
                 ns = S3;
             S3:
                 ns = S30;
             S30:
                 ns = S4;
             S4:
                 ns = S40;
             S40:
                 begin//判断是否处于半频激励时间
                      if ((i[2] == 1'b1) && (i[1] == 1'b0))
                          ns = S5;//反相半频
                      else
                          ns = S1;//反相全频或正相半频
                 end
             S5:
                 ns = S50;
             S50:
                 ns = S6;
             S6:
                 ns = S60;
             S60:
                 ns = S1;
             default:
                 ns = IDLE;
         endcase
    end

always @ (negedge en or posedge clk_dds)
    begin
         if (en == 1'b0)
             {up,down} <= 2'b00;
         else
             begin
                  if (clk_4f_en == 1'b1)
                      begin
                           case (ns)
                               IDLE:
                                   {up,down} <= 2'b00;
                               S1,S10:
                                   {up,down} <= 2'b10;
                               S0,S00,S2,S20,S3,S30,S5,S50,S6,S60:
                                   {up,down} <= 2'b00;
                               S4,S40:
                                   {up,down} <= 2'b01;
                               default:
                                   {up,down} <= 2'b00;
                           endcase
                      end
                  else
                      {up,down} <= {up,down};
             end
    end

endmodule