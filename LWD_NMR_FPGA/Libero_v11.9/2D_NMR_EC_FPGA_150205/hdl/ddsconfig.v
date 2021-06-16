// ddsconfig.v

module ddsconfig(
                 reset,     //复位
                 clk,       //时钟
                 ddswclk,   //dds写
                 ddsreset,  //dds复位
                 ddsfqud,   //dds控制
                 ddsdata,   //dds数据
                 datain,    //dds控制字输入
                 load,      //读取数据
                 choice     //高低位选择
                 );

parameter S1  = 13'b0000000000001,
          D1  = 13'b0000000000010,
          S2  = 13'b0000000000100,
          D2  = 13'b0000000001000,
          S3  = 13'b0000000010000,
          S4  = 13'b0000000100000,
          S5  = 13'b0000001000000,
          S6  = 13'b0000010000000,
          S7  = 13'b0000100000000,
          S8  = 13'b0001000000000,
          S9  = 13'b0010000000000,
          S10 = 13'b0100000000000,
          S11 = 13'b1000000000000;


input  reset;
input  choice;
input  load;
input  [15:0] datain;
input  clk;

output ddswclk;
output ddsreset;
output ddsdata;
output ddsfqud;

reg    ddswclk;
reg    ddsreset;
reg    ddsdata;
reg    ddsfqud;

reg    [39:0] datareg;
reg    [12:0] state;
reg    [5:0] i;
reg    [7:0] da;
reg    [5:0] db;



always @ (posedge load)                  //读取dds频率控制字
  begin
        if(choice==0)
             begin
                   datareg[15:0] <= datain[15:0];
             end
        else
             begin
                   datareg[31:16] <= datain[15:0];
             end
  end


always @ (posedge reset or posedge clk)   //配置dds
  begin
        if(reset)                         //复位
             begin
                   state <= S1;
                   ddswclk <= 0;
                   ddsreset <= 0;
                   ddsdata <= 0;
                   ddsfqud <= 0;
                   datareg[39:32] <= 0;
                   i <=0;
                   da <= 0;
                   db <= 0;
             end

      else
             begin
                  case(state)              
                       S1:                           //dds复位
                          begin
                                ddsreset <= 1;
                                state <= D1;
                          end

                       D1:                          
                          begin
                                if(da<99)
                                    begin
                                          da <= da+1;
                                          state <= D1; 
                                    end

                                else if(da>=99)
                                    begin
                                          state <= S2; 
                                    end
                          end


                       S2:
                          begin
                                ddsreset <= 0;
                                state <= D2;
                          end

                       D2:                          
                          begin
                                if(db<49)
                                    begin
                                          db <= db+1;
                                          state <= D2; 
                                    end

                                else if(db>=49)
                                    begin
                                          state <= S3; 
                                    end
                          end

                       S3:                           //选择串行模式
                          begin
                                ddswclk <= 1;
                                state <= S4;
                          end

                       S4:
                          begin
                                ddswclk <= 0;
                                state <= S5;
                          end

                       S5:
                          begin
                                ddsfqud <= 1;
                                state <= S6;
                          end

                       S6:
                          begin
                                ddsfqud <= 0;
                                state <= S7;
                          end

                       S7:                           //写频率字
                          begin
                                ddsdata <= datareg[i];
                                ddswclk <= 0;
                                state <= S8;                      
                          end

                       S8:
                          begin
                                ddswclk <= 1;
                                if(i<39)
                                    begin
                                          i <= i+1;
                                          state <= S7; 
                                    end

                                else if(i>=39)
                                    begin
                                          state <= S9; 
                                    end
                          end

                       S9:
                          begin
                                ddswclk <= 0;
                                state <= S10; 
                          end

                       S10:
                          begin
                                ddsfqud <= 1;                   
                                state <= S11;
                          end

                       S11:
                          begin
                                ddsfqud <= 0;                   
                                state <= S11;
                          end

                       default: state <= S11;

                    endcase

             end
  end


endmodule