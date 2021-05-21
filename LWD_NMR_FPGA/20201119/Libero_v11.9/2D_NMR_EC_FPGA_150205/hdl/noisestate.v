// noisestate.v

module noisestate(
                  clk_sys,          //扫频状态机时钟
                  clken_p,
                  rst_n,          //扫频状态机复位
                  dumpon_ctr,
                  dumpoff_ctr,
                  soft_d,           //SOFT_DUMP控制信号
                  rt_sw,            //RT_SW控制信号
                  sw_acq1,          //SW_ACQ1控制信号
                  sw_acq2,          //SW_ACQ2控制信号
                  timecount,        //定时器计数
                  n_acq,            //噪声采集控制
                  state_over_n,         //状态机结束
                  nload,
                  nchoice,
                  ndatain
                  );



parameter [7:0] IDLE        = 8'b00000001,
                INIT        = 8'b00000010,
                N_SOFTDUMP  = 8'b00000100,
                N_DECOPEN   = 8'b00001000,
                N_SWICHOPEN = 8'b00010000,
                N_ACQUITION = 8'b00100000,
                CUT_DECO    = 8'b01000000,
                STOP        = 8'b10000000;


input  clk_sys;            //状态机时钟
input  clken_p;
input  rst_n;            //状态机复位
input  nload;
input  nchoice;
input  [15:0] ndatain;

output dumpon_ctr;
output dumpoff_ctr;

output soft_d;             //SOFT_DUMP控制信号
output rt_sw;              //RT_SW控制信号
output sw_acq1;            //SW_ACQ1控制信号
output sw_acq2;            //SW_ACQ2控制信号
output [19:0] timecount;   //定时器计数
output n_acq;              //噪声采集控制
output state_over_n;          //状态机结束

reg dumpon_ctr;
reg dumpoff_ctr;

reg    soft_d;             //SOFT_DUMP控制信号
reg    rt_sw;              //RT_SW控制信号
reg    sw_acq1;            //SW_ACQ1控制信号
reg    sw_acq2;            //SW_ACQ2控制信号
reg    [19:0] timecount;   //定时器计数
reg    n_acq;              //噪声采集控制
reg    state_over_n;          //状态机结束
//reg    [9:0] noisestate;    //状态机状态信号
reg    [15:0] acqtime;
reg    [15:0] dectime;


always @ (posedge clk_sys)
    begin
         if(nload == 1'b1)
             begin
                  if(nchoice)
                      begin
                           dectime <= ndatain;
                      end
                  else
                      begin
                           acqtime <= ndatain;
                      end
            end
        else
            begin
                 dectime <= dectime;
                 acqtime <= acqtime;
            end
    end

reg[7:0] CS;
reg[7:0] NS;


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
                NS = N_SOFTDUMP;
             N_SOFTDUMP:                //DEC软泄放
                NS = N_DECOPEN;       
             N_DECOPEN:                 //DEC通道打开
                NS = N_SWICHOPEN;       
             N_SWICHOPEN:               //模拟开关通道打开
                NS = N_ACQUITION;       
             N_ACQUITION:               //噪声采集
                NS = CUT_DECO;          
             CUT_DECO:                  //DEC隔离，采集通道关闭 
                NS = STOP;          
             STOP:                      //结束                   
                NS = STOP; 
            default:
                NS = IDLE;
        endcase 
    end

always @ (posedge clk_sys)
    begin
        if(rst_n == 1'b0)
            begin
                timecount <= 1;      //定时器计数初始化
                dumpon_ctr <= 1'b0;
                dumpoff_ctr <= 1'b0;
                soft_d  <= 0;        //DEC通道隔离（DEC为DECOUPLE板简称）
                rt_sw   <= 0;       
                sw_acq1 <= 1;        //模拟开关采集通道关闭
                sw_acq2 <= 1;      
                n_acq    <= 0;       //噪声采集停止状态                             
                state_over_n <= 1;    //状态机工作
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 100;
                    N_SOFTDUMP:                   //DEC软泄放
                        begin
                            dumpon_ctr <= 1'b1;
                            soft_d  <= 1;        //软泄放
                            rt_sw   <= 1;       
                            sw_acq1 <= 1;        //采集通道关闭
                            sw_acq2 <= 1;                 
           
                            timecount <= 3000;    //定时时间
                        end  
                    N_DECOPEN:                      //DEC通道打开
                        begin
                            dumpon_ctr <= 1'b0;
                            soft_d  <= 0;        //DEC通道打开
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //采集通道关闭
                            sw_acq2 <= 1;                        
           
                            timecount <= dectime;            //定时时间
                        end           
                    N_SWICHOPEN:                    //模拟开关通道打开
                        begin
                            soft_d  <= 0;        //DEC通道打开
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //回波采集通道打开
                            sw_acq2 <= 0;

                            timecount <= 500;               //定时时间
                        end 
                    N_ACQUITION:                    //噪声采集
                        begin
                            soft_d  <= 0;        //DEC通道打开
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //回波采集通道打开
                            sw_acq2 <= 0;           
                            n_acq   <= 1;        //噪声采集

                            timecount <= acqtime;              //定时时间
                        end 
                    CUT_DECO:                       //DEC隔离，采集通道关闭 
                        begin
                            dumpoff_ctr <= 1'b1;
                            soft_d  <= 0;         //DEC通道隔离
                            rt_sw   <= 0;           
                            sw_acq1 <= 1;         //采集通道关闭
                            sw_acq2 <= 1;           
                            n_acq   <= 0;         //噪声采集停止

                            timecount <= 100;      //定时时间
                        end  

                    STOP:                          //结束   
                        begin
                            dumpoff_ctr <= 1'b0;
                            state_over_n <= 0;    //状态机结束
                        end  
                    default:
                        ;
               endcase
           end
    end

endmodule