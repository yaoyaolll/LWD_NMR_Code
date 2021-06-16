// state_1ms.v

module state_1ms(
                  clk_sys,
                  clken_p,        
                  rst_n,
                  load,
                  loadchoice,  
                  datain,
                  reset_out,
                  dump_start,
                  pluse_start,
                  bri_cycle,
                  rt_sw,
                  soft_dump,
                  timecount      //定时器计数
                 );

input  clk_sys;            //刻度状态机时钟
input  clken_p;
input  rst_n;            //刻度状态机复位
input  load;
input  [3:0] loadchoice;
input  [15:0] datain;

output reset_out;
output dump_start;
output pluse_start;
output bri_cycle;
output soft_dump;             //SOFT_DUMP控制信号
output rt_sw;              //RT_SW控制信号
output [19:0] timecount;   //定时器计数

reg reset_out;
reg dump_start;
reg pluse_start;
reg bri_cycle;
reg soft_dump;             //SOFT_DUMP控制信号
reg rt_sw;              //RT_SW控制信号
reg [19:0] timecount;   //定时器计数

parameter [9:0] IDLE   = 10'b0000000001,
                INIT   = 10'b0000000010,
                INIT2  = 10'b0000000100,
                RESET  = 10'b0000001000,
                S1     = 10'b0000010000,
                S2     = 10'b0000100000,
                S3     = 10'b0001000000,
                S4     = 10'b0010000000,
                S5     = 10'b0100000000,
                S6     = 10'b1000000000;
/*
parameter [19:0] PLUSECYCLE = 100,
                 PLUSETIME  = 100,
                 M_DUMPTIME = 3100,
                 S_DUMPTIME = 2700,
                 CUTTIME    = 94000;
*/

reg [19:0] PLUSECYCLE;
reg [19:0] PLUSETIME;
reg [19:0] M_DUMPTIME;
reg [19:0] S_DUMPTIME;
reg [19:0] CUTTIME;

always @ (posedge clk_sys)
    begin
         if(load == 1'b1) 
             begin
                  case(loadchoice)
                      0:
                          begin
                               PLUSECYCLE <= datain; 
                          end
                      1:
                          begin
                               PLUSETIME  <= datain; 
                          end
                      2:
                          begin
                               M_DUMPTIME <= datain; 
                          end
                      3:
                          begin
                               S_DUMPTIME  <= datain; 
                          end
                      4:
                          begin
                               CUTTIME[15:0] <= datain; 
                          end
                      5:
                          begin
                               CUTTIME[19:16] <= datain[3:0]; 
                          end
                 endcase
             end
         else
             begin
                  PLUSECYCLE <= PLUSECYCLE;
                  PLUSETIME  <= PLUSETIME;
                  M_DUMPTIME <= M_DUMPTIME;
                  S_DUMPTIME <= S_DUMPTIME;
                  CUTTIME    <= CUTTIME;
             end
    end

reg[9:0] CS;
reg[9:0] NS;


always @ (posedge clk_sys)
   if(rst_n == 1'b0) 
       CS <= IDLE;
   else       
       if(clken_p)
           CS <= NS;

always @ (CS)
    begin
        case(CS)
            IDLE: 
                NS = INIT; 
            INIT:           
                NS = INIT2;
            INIT2:
                NS = RESET;
            RESET:
                NS = S1;
            S1:
                NS = S2;
            S2:
                NS = S3;
            S3:
                NS = S4;
            S4:
                NS = S5;
            S5:
                NS = S6;
            S6:
                NS = IDLE;
            default:
                NS = IDLE;
        endcase 
    end

always @ (posedge clk_sys)
    begin
        if(rst_n == 1'b0)
            begin
                reset_out   <= 0;
                dump_start  <= 0;
                pluse_start <= 0;
                bri_cycle   <= 0;  
                soft_dump   <= 0;      
                rt_sw       <= 0;  
                timecount   <= 1;    //定时器计数初始化 
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 10;
                    INIT2:
                        begin                     
                            reset_out   <= 0;
                            dump_start  <= 0;
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 0;      
                            rt_sw       <= 0;  
                 
                            timecount   <= 100;    
                        end
                    RESET:
                        begin
                            reset_out   <= 1;//底层模块复位结束
                            dump_start  <= 0;
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 0;      
                            rt_sw       <= 0;  
                 
                            timecount   <= 100; 
                        end
                    S1:
                        begin
                            reset_out   <= 1;
                            dump_start  <= 1;//输出第一个dumpoff
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 1;      
                            rt_sw       <= 0;  
                   
                            timecount   <= 100;
                        end
                    S2:
                        begin 
                            reset_out   <= 1;
                            dump_start  <= 1;
                            pluse_start <= 1;//用于维持dump状态机
                            bri_cycle   <= 0;  
                            soft_dump   <= 1;      
                            rt_sw       <= 0;  
                   
                            timecount   <= PLUSECYCLE;
                        end
                    S3:
                        begin 
                            reset_out   <= 1;
                            dump_start  <= 1;
                            pluse_start <= 1;
                            bri_cycle   <= 1;//输出第二个dumpoff  
                            soft_dump   <= 1;      
                            rt_sw       <= 0;  
                 
                            timecount   <= PLUSETIME;
                        end
                    S4:
                        begin 
                            reset_out   <= 1;
                            dump_start  <= 1;
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 1;      
                            rt_sw       <= 0;  
                  
                            timecount   <= M_DUMPTIME;
                        end
                    S5:
                        begin 
                            reset_out   <= 1;
                            dump_start  <= 0;
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 1;
                            rt_sw       <= 1;  
                   
                            timecount   <= S_DUMPTIME;
                        end
                    S6:
                        begin 
                            reset_out   <= 1;
                            dump_start  <= 0;
                            pluse_start <= 0;
                            bri_cycle   <= 0;  
                            soft_dump   <= 0;      
                            rt_sw       <= 0;  
                   
                            timecount   <= CUTTIME;
                        end
                    default:
                        ;
               endcase
           end
    end

endmodule