module  pd_pluse_state(
                       dds,
                       rst_n,
                       i,
                       en,
                       stateover                  
                       );

input dds;
input rst_n;
input [5:0] i;

output stateover;
output en;

//output en1;
//output en2;

reg [12:0] ns;
reg [12:0] cs;

reg en1;
reg en2;
reg stateover;

reg en;
wire state_initial;

assign state_initial = rst_n & i[0];

//assign en=en1|en2;

parameter [12:0]  IDLE = 13'b0000000000001,
                 S1   =  13'b0000000000010,
                 S2   =  13'b0000000000100,
                 S3   =  13'b0000000001000,
                 S4   =  13'b0000000010000,
                
                 S20   = 13'b0000000100000,
                 S21   = 13'b0000001000000,
                 S22   = 13'b0000010000000,

                 S50   = 13'b0000100000000,
                 S51   = 13'b0001000000000,
                 S52   = 13'b0010000000000,
                 S53   = 13'b0100000000000,

                 S10   = 13'b1000000000000;


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
                      if (i[5] == 1'b1)
                          ns = S50;
                      else
                          ns = S51;
                  end
                 
                 
              S50:   
                 begin
                      if (i[0] == 1'b1)
                          ns = S1;
                      else
                          ns = S50;
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


             S20: 
                 begin
                     if (i[2] == 1'b1)
                          ns = S21;
                      else
                          ns = S20;
                 end
             S21: 
                 begin
                         if (i[4] == 1'b1)
                          ns = S22;
                      else
                          ns = S21;
                 end

             S51: 
                 begin
                         if (i[2] == 1'b1)
                          ns = S52;
                      else
                          ns = S51;
                 end
             S52: 
                 begin
                         if (i[3] == 1'b1)
                          ns = S53;
                         else
                          ns = S52;
                 end


            S4:
                 begin
                          ns = S10;
                 end
            S22:
                begin
                          ns = S10;
                 end
            S53:
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
                      S21:
                          {en1,en2} <= 2'b01;
                      S22:
                          {en1,en2} <= 2'b00;
                      
                      
                      S50:
                          {en1,en2} <= 2'b00;
                      S51:
                          {en1,en2} <= 2'b00;
                      S52:
                          {en1,en2} <= 2'b10;
                      S53:
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


always @ (posedge dds)
    begin
         if (state_initial == 1'b0)
             en <= 0;
         else
             en <= en1|en2;
    end

endmodule