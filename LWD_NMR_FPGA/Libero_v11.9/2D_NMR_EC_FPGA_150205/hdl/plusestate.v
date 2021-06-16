module plusestate(
                  clk_sys,
                  clken_p,        
                  rst_n,        
                  soft_d,           //SOFT_DUMP控制信号
                  rt_sw,            //RT_SW控制信号
                  sw_acq1,          //SW_ACQ1控制信号
                  sw_acq2,          //SW_ACQ2控制信号
                  timecount,
                  pluse_acq,            //信号采集控制
                  pluse_start,
                  off_test,
                  datain,
                  load,
                  loadchoice,
                  //dumpoff_ctrl,
                  dump_start,
                  //doff_start,
                  state_over_n,
                  //reset_out,
                  dds_config,
                  //QQEN
                  dumpoff_ctr,
                  tetw_pluse
                 );

parameter [9:0] IDLE     = 10'b0000000001,
                INIT     = 10'b0000000010,
                INIT2    = 10'b0000000100,
                CONFIG   = 10'b0000001000,
                START    = 10'b0000010000,
                PLUSE    = 10'b0000100000,
                DUMP     = 10'b0001000000,
                STOP     = 10'b0010000000,
                INI_TEST = 10'b0100000000,
                START_test=10'b1000000000;


input  clk_sys;            //刻度状态机时钟
input  clken_p;
input  rst_n;            //刻度状态机复位
input  [15:0] datain;
input  load;
input  loadchoice;

output soft_d;             //SOFT_DUMP控制信号
output rt_sw;              //RT_SW控制信号
output sw_acq1;            //SW_ACQ1控制信号
output sw_acq2;            //SW_ACQ2控制信号
output [19:0] timecount;   //定时器计数
output pluse_acq;              //信号采集控制
output pluse_start;
output dump_start;
output state_over_n;
//output reset_out;
output  dds_config;
output dumpoff_ctr;
output off_test;
output tetw_pluse;

reg    soft_d;             //SOFT_DUMP控制信号
reg    rt_sw;              //RT_SW控制信号
reg    sw_acq1;            //SW_ACQ1控制信号
reg    sw_acq2;            //SW_ACQ2控制信号
reg    [19:0] timecount;   //定时器计数
reg    pluse_acq;              //信号采集控制
reg    pluse_start;
reg    dump_start;
reg    state_over_n;
//reg    reset_out;
reg    dds_config;

reg    off_test;
reg    tetw_pluse;

//reg    [7:0] plusestate;    //状态机状态信号

reg    [15:0] PLUSETIME;
reg    [15:0] DUMPTIME;
reg    dumpoff_ctr;

always @ (posedge clk_sys)
    begin
         if(load == 1'b1) 
             begin
                  case(loadchoice)
                      0:
                          begin
                               PLUSETIME <= datain; 
                          end
                      1:
                          begin
                               DUMPTIME  <= datain; 
                          end

                  endcase
             end
         else
             begin
                  PLUSETIME <= PLUSETIME;
                  DUMPTIME  <= DUMPTIME;
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
            INIT2:                //DEC软泄放
               NS = INI_TEST;       
            INI_TEST:                 //DEC通道打开
               NS = CONFIG;       
            CONFIG:               //模拟开关通道打开
               NS = START;       
            START:               //噪声采集
               NS = START_test;          
            START_test:                  //DEC隔离，采集通道关闭 
               NS = PLUSE;        
            PLUSE:
               NS = DUMP;
            DUMP:
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
                timecount <= 1;
                soft_d  <= 0;      //DEC通道隔离（DEC为DECOUPLE板简称）
                rt_sw   <= 0;       
                sw_acq1 <= 1;      //模拟开关采集通道关闭
                sw_acq2 <= 1;      
                pluse_acq  <= 0;     //信号采集停止状态
                pluse_start <= 0;
                dump_start <= 0;
                //reset_out <= 0;
                dds_config <= 0;
                state_over_n <= 1;   
                dumpoff_ctr <= 0; 
                off_test <= 0; 
                tetw_pluse <= 0;   
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
                            timecount <= 100;  
                        end  
                    INI_TEST:                    
                        begin
           
                            timecount <= 100;           
                        end           
                    CONFIG:                  
                        begin
                            //reset_out <= 1;         
                            //dds_config <= 1;  
                            sw_acq1 <= 0;     //激励采集打开  
                            sw_acq2 <= 1;         
        
                            timecount <= 400;   
                        end 
                    START:                
                        begin
                            soft_d  <= 1;     //采集通道软泄放准备 
                            rt_sw   <= 0;  
                            sw_acq1 <= 0;     //激励采集打开  
                            sw_acq2 <= 1;
                            dump_start <= 1;                
                            //dds_config <= 0; 
                            dds_config <= 1;
                            pluse_acq <= 1;            //信号采集控制

                            timecount <= 30;  
                        end 
                    START_test:                     
                        begin
                            //reset_out <= 1; 
                            soft_d  <= 1;     //采集通道软泄放准备 
                            rt_sw   <= 0;  
                            sw_acq1 <= 0;     //激励采集打开  
                            sw_acq2 <= 1;
                            dump_start <= 1;                
                            //dds_config <= 0;
                            dds_config <= 1;
                            pluse_start <= 1;
                            off_test <= 1;
                            pluse_acq <= 1;            //信号采集控制
 
                            timecount <= 168;                          
                        end  
                    PLUSE:
                        begin
                            // reset_out <= 0; 
                            //pluse_start <= 1;                
                            pluse_acq <= 1;            //信号采集控制
                            //off_test <= 1;
                            dds_config <= 0;

                            timecount <= PLUSETIME;
                        end 
                    DUMP:
                        begin
                            // reset_out <= 1; 
                            pluse_start <= 0; 
                            off_test <= 0;                
                            soft_d  <= 1;      
                            rt_sw   <= 0;       
                            dump_start <= 1;

                            timecount <= DUMPTIME;
                        end 
                    STOP:                        
                        begin
                            //reset_out <= 0;                               
                            dump_start <= 0;
                            dumpoff_ctr <= 1;
                            soft_d  <= 0;      //DEC通道隔离（DEC为DECOUPLE板简称）
                            rt_sw   <= 0;       
                            sw_acq1 <= 1;      //模拟开关采集通道关闭
                            sw_acq2 <= 1;   
                            pluse_acq <= 0;            //信号采集控制
                            dump_start <= 0;
                            state_over_n <= 0;   
                            tetw_pluse <= 1;
                        end  
                    default:
                        ;
               endcase
           end
    end

endmodule