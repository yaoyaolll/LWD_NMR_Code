// sd_acq_state.v
module  sd_sacq_state(
                      dds,
                      rst_n,
                      i,
                      en,
                      stateover
                      );

input dds;
input rst_n;
input [10:0] i;

output stateover;
output en;

reg [14:0] ns;
reg [14:0] cs;
reg stateover;

reg en1;
reg en2;

wire en;
wire state_initial;

assign state_initial = rst_n & i[0];

assign en=en1|en2;

parameter [14:0] IDLE = 15'b000000000000000,
                 S1   = 15'b000000000000001,
                 S2   = 15'b000000000000010,
                 S3   = 15'b000000000000100,
                 S4   = 15'b000000000001000,                
                 S20   =15'b000000000010000,

                 S30   =15'b000000000100000,
                 S31   =15'b000000001000000,
                 S32   =15'b000000010000000,

                 S40   =15'b000000100000000,
                 S41   =15'b000001000000000,
                 S42   =15'b000010000000000,

                 S50   =15'b000100000000000,
                 S51   =15'b001000000000000,
                 S52   =15'b010000000000000,

                 S10   =15'b100000000000000;


always @ (posedge dds)
    begin
         if (state_initial == 1'b0)
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
                      if (i[1] == 1'b0)
                          ns = S2;
                      else
                          ns = S20;
                 end
             S2:
                 begin
                      if (i[4] == 1'b1)
                          ns = S3;
                      else
                          ns = S2;
                 end
             S20: 
                 begin
                      if (i[2] == 1'b1)
                          ns = S30;
                      else if(i[3] == 1'b0)
                               ns = S40;
                           else
                               ns = S50;
                 end
             S3:
                 begin
                      if (i[5] == 1'b1)
                          ns = S4;
                      else
                          ns = S3;
                 end
             S30: 
                 begin
                      if (i[4] == 1'b1)
                          ns = S31;
                      else
                          ns = S30;
                 end
             S31: 
                 begin
                      if (i[6] == 1'b1)
                          ns = S32;
                      else
                          ns = S31;
                 end   
             S32:
                 begin
                      if(i[2]==1)    //必须等到s_acq180 变为低时才跳转
                          ns = S32;
                      else
                          ns = S20;
                 end                  
             S40: 
                 begin
                         if (i[7] == 1'b1)
                          ns = S41;
                      else
                          ns = S40;
                 end
             S41: 
                 begin
                         if (i[8] == 1'b1)
                          ns = S42;
                      else
                          ns = S41;
                 end  
             S42:
                 begin
                          ns = S10;
                 end         
             S4:
                 begin
                          ns = S10;
                 end
             S50: 
                 begin
                      if (i[9] == 1'b1)
                          ns = S51;
                      else
                          ns = S50;
                 end
             S51: 
                 begin
                      if (i[10] == 1'b1)
                          ns = S52;
                      else
                          ns = S51;
                 end  
             S52:
                 begin
                          ns = S10;
                 end         

             S10:
                 begin
                          ns = S10;
                 end
             default:
                 ns = IDLE;
         endcase
    end

always @ (posedge dds)
    begin
         if (state_initial == 1'b0)
             begin//复位之后stateover无效，rst_n为高后timer开始计时，状态机启动，状态机结束后stateover有效，timer停止计时
                  {en1,en2} <= 2'b00;
                  stateover             <= 1'b1;
             end
         else
             begin
                  case (ns)
                      IDLE:
                          {en1,en2} <= 2'b00;
                      S1:
                          {en1,en2} <= 2'b00;
                      
                      S2:
                          {en1,en2} <= 2'b00;
                      S3:
                          {en1,en2} <= 2'b10;
                      S4:
                          {en1,en2} <= 2'b00;
                       
                      
                      S20:
                          {en1,en2} <= 2'b00;


                      S30:
                          {en1,en2} <= 2'b00;
                      S31:
                          {en1,en2} <= 2'b01;
                      S32:
                          {en1,en2} <= 2'b00;
                      
                      
                      S40:
                          {en1,en2} <= 2'b00;
                      S41:
                          {en1,en2} <= 2'b01;
                      S42:
                          {en1,en2} <= 2'b00;

                      S50:
                          {en1,en2} <= 2'b00;
                      S51:
                          {en1,en2} <= 2'b01;
                      S52:
                          {en1,en2} <= 2'b00;

                      S10:
                          begin//S4跳到自身，故可以不输出stateover信号，但为停止计数器还是用了stateover
                               {en1,en2} <= 2'b00;
                                stateover <= 1'b0;
                          end
                      

                      default:
                          begin
                               {en1,en2} <= 2'b00;
                               stateover <= 1'b0;
                          end
                  endcase
             end
    end

endmodule