// scanstate.v

module scanstate(
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
                 s_acq,            //信号采集控制
                 dds_conf,         //dds配置控制
                 calctrl,          //cal信号输出控制
                 state_over_n,         //状态机结束
                 scanload,
                 datain,
                 scanchoice,
                 resetout
                 );

parameter [7:0] IDLE        = 8'b00000001,
                INIT        = 8'b00000010,
                S_SOFTDUMP  = 8'b00000100,
                S_DECOPEN   = 8'b00001000,
                S_SWICHOPEN = 8'b00010000,
                S_ACQUITION = 8'b00100000,
                CUT_DECO    = 8'b01000000,
                STOP        = 8'b10000000;


input  clk_sys;            //扫频状态机时钟
input  clken_p;
input  rst_n;            //扫频状态机复位
input  [15:0] datain;
input  scanload;
input  scanchoice;

output dumpon_ctr;
output dumpoff_ctr;

output soft_d;             //SOFT_DUMP控制信号
output rt_sw;              //RT_SW控制信号
output sw_acq1;            //SW_ACQ1控制信号
output sw_acq2;            //SW_ACQ2控制信号
output [19:0] timecount;   //定时器计数
output s_acq;              //信号采集控制
output dds_conf;           //dds配置控制
output calctrl;            //cal信号输出控制
output state_over_n;          //状态机结束
output resetout;

reg dumpon_ctr;
reg dumpoff_ctr;

reg    soft_d;             //SOFT_DUMP控制信号
reg    rt_sw;              //RT_SW控制信号
reg    sw_acq1;            //SW_ACQ1控制信号
reg    sw_acq2;            //SW_ACQ2控制信号
reg    [19:0] timecount;   //定时器计数
reg    s_acq;              //信号采集控制
reg    dds_conf;           //dds配置控制
reg    calctrl;            //cal信号输出控制
reg    state_over_n;          //状态机结束

reg    [15:0] acqtime;
reg    [15:0] dectime;
reg    resetout;

always @ (posedge clk_sys)
    begin
         if(scanload == 1'b1)
             begin
                  if(scanchoice)
                      begin
                           dectime <= datain;   //choice = 1 
                      end
                  else
                      begin
                           acqtime <= datain;
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
                NS = S_SOFTDUMP;
            S_SOFTDUMP:
                NS = S_DECOPEN;
            S_DECOPEN:
                NS = S_SWICHOPEN;
            S_SWICHOPEN:
                NS = S_ACQUITION;
            S_ACQUITION:
                NS = CUT_DECO;
            CUT_DECO:
                NS = STOP;
            STOP:
                NS = STOP;
            default:
                NS = IDLE;
        endcase 
    end

always @ (posedge clk_sys)
    begin
        if(rst_n == 1'b0)
            begin
                timecount <= 1;           //定时器计数初始化
                dumpon_ctr <= 1'b0;
                dumpoff_ctr <= 1'b0;
                soft_d  <= 0;         //DEC通道隔离（DEC为DECOUPLE板简称）
                rt_sw   <= 0;       
                sw_acq1 <= 1;         //模拟开关采集通道关闭
                sw_acq2 <= 1;      
                s_acq    <= 0;        //信号采集停止状态
                dds_conf <= 0;        //dds配置停止状态
                calctrl  <= 0;        //cal信号不输出             
                state_over_n <= 1;    //状态机工作
                resetout <= 0;
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 100;
                    S_SOFTDUMP:                     //DEC软泄放  
                         begin                             
                             dumpon_ctr <= 1'b1;
                             soft_d  <= 1;      //软泄放
                             rt_sw   <= 1;       
                             sw_acq1 <= 1;      //采集通道关闭
                             sw_acq2 <= 1;
                             dds_conf <= 1;     //dds配置启动
                            
                             timecount <= 3000;            //定时时间
                          end
                    S_DECOPEN:                      //DEC通道打开同时配置dds?
                          begin
                             dumpon_ctr <= 1'b0;
                             soft_d  <= 0;      //DEC通道打开
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //采集通道关闭
                             sw_acq2 <= 1;
                             dds_conf <= 0;     //dds配置关闭
                             calctrl  <= 1;     //cal信号输出 
                             resetout <= 0;

                             timecount <= dectime;            //定时时间                             
                          end
                    S_SWICHOPEN:                    //模拟开关通道打开
                          begin
                             soft_d  <= 0;      //DEC通道打开
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //回波采集通道打开
                             sw_acq2 <= 0;
                             resetout <= 1;

                             timecount <= 500;               //定时时间
                          end
                    S_ACQUITION:                    //信号采集
                          begin
                             soft_d  <= 0;      //DEC通道打开
                             rt_sw   <= 1;       
                            // sw_acq1 <= 1;      //回波采集通道打开
                             sw_acq2 <= 0;
                             s_acq   <= 1;     //信号采集启动

                             timecount <= acqtime;
                          end         
                    CUT_DECO:                       //DEC隔离，采集通道关闭 
                          begin
                             dumpoff_ctr <= 1'b1;
                             soft_d  <= 0;      //DEC通道隔离
                             rt_sw   <= 0;       
                            // sw_acq1 <= 1;      //采集通道关闭
                             sw_acq2 <= 1;
                             calctrl <= 0;     //cal信号不输出  

                             timecount <= 100;      //定时时间
                          end  
                    STOP:                           //结束   
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