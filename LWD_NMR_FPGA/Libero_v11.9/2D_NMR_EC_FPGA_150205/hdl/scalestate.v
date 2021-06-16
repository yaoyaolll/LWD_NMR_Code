///////////////////////////////////////////////////////////////////////////////////////////////////
// Company: <HUST>
//
// File: scalestate.v
// File history:
//      <Revision number>: <2014-03-13>: <Comments>
//      <Revision number>: <Date>: <Comments>
//      <Revision number>: <Date>: <Comments>
//
// Description: 
//
// <三段式状态机、实现DE序列>
//
// Targeted device: <ProASIC3> <A3P1000> <PQFGP>
// Author: <HUST>
//
/////////////////////////////////////////////////////////////////////////////////////////////////// 

module scalestate(
                  clk_sys,         //刻度状态机时钟
                  clken_p,
                  rst_n,         //刻度状态机复位
                  soft_d,           //SOFT_DUMP控制信号
                  rt_sw,            //RT_SW控制信号
                  sw_acq1,          //SW_ACQ1控制信号
                  sw_acq2,          //SW_ACQ2控制信号
                  timecount,        //定时器计数
                  s_acq,            //信号采集控制
                  dds_conf,          //dds配置控制
                  datain,
                  load,
                  loadchoice,
                  pn_change,
                  inv_turn,
                  dump_start,
                  pluse_start,
                  pn_out,
                  bb_ch,
                  reset_out,
                  load_out,
                  s_acqnum,
                  intertodsp,
                  state_over_n,
                  strippluse,
                  dumpoff_ctr,
                  off_test,
                  tetw_pluse,
                  s_acq180,
                  long_opentime,
                  dump_sustain_ctrl,
                  ne_le             
                 );

parameter[20:0]   IDLE         = 21'b000000000000000000000,     
                  INI_RST1     = 21'b000000000000000000001,
                  INI_RST2     = 21'b000000000000000000010,
                  START        = 21'b000000000000000000100,
                  PLUSE90      = 21'b000000000000000001000,
                  DUMP90       = 21'b000000000000000010000,
                  SOFT_DUMP90  = 21'b000000000000000100000,
                  CUT_DEC90    = 21'b000000000000001000000,
                  RESET        = 21'b000000000000010000000,
                  DDSCONF      = 21'b000000000000100000000,
                  PLUSE180     = 21'b000000000001000000000,
                  DUMP180      = 21'b000000000010000000000,
                  SOFT_DUMP180 = 21'b000000000100000000000,
                  OPEN_DEC     = 21'b000000001000000000000,
                  OPEN_SWITCH  = 21'b000000010000000000000,
                  ECHO_ACQ     = 21'b000000100000000000000,
                  CUT_DEC180   = 21'b000001000000000000000,
                  JUMP         = 21'b000010000000000000000,
                  STOP         = 21'b000100000000000000000,         
                  START_TEST   = 21'b001000000000000000000,
                  DDSCONF_TEST = 21'b010000000000000000000, 
                  CUT_DECI90   = 21'b100000000000000000000;        

input  clk_sys;          //刻度状态机时钟
input  clken_p;
input  rst_n;            //刻度状态机复位
input  [15:0] datain;
input  load;
input  [4:0] loadchoice;
input  pn_change;
input  inv_turn;

output soft_d;             //SOFT_DUMP控制信号
output rt_sw;              //RT_SW控制信号
output sw_acq1;            //SW_ACQ1控制信号
output sw_acq2;            //SW_ACQ2控制信号
output [21:0] timecount;   //定时器计数
output s_acq;              //信号采集控制
output dds_conf;           //dds配置控制
output dump_start;
output pluse_start;
output reset_out;
output load_out;
output [15:0] s_acqnum;
output intertodsp;
output state_over_n;
output pn_out;
output [11:0] strippluse;
output off_test;
output tetw_pluse;
output s_acq180;
output dumpoff_ctr;
output bb_ch;
output ne_le;

wire ne_le;

output reg long_opentime;
output reg dump_sustain_ctrl;


reg dumpoff_ctr;
reg    bb_ch;
reg    soft_d;             //SOFT_DUMP控制信号
reg    rt_sw;              //RT_SW控制信号
reg    sw_acq1;            //SW_ACQ1控制信号
reg    sw_acq2;            //SW_ACQ2控制信号
reg    [21:0] timecount;   //定时器计数
reg    s_acq;              //信号采集控制
reg    dds_conf;           //dds配置控制
reg    dump_start;
reg    pluse_start;
reg    reset_out;
reg    load_out;
reg    [15:0] s_acqnum;
reg    intertodsp;
reg    state_over_n;
reg    pn_out;
reg    [11:0] strippluse;
reg    off_test; 
reg    tetw_pluse;
reg    s_acq180;

reg    [15:0] PLUSETIME90;
reg    [15:0] PLUSETIME180;
reg    [15:0] DUMPTIME;
reg    [15:0] S_DUMPTIME;
reg    [21:0] CUTTIME90;
reg    [19:0] CUTTIME180;
reg    [19:0] OPENTIME;
reg    [15:0] ACQTIME;
reg    [10:0] NE_NUM;
reg    [11:0] ACQ90_NUM;
reg    [11:0] ACQ180_NUM;
reg    [11:0] ACQECHO_NUM;
reg    [11:0] STRIPNUM90_NUM;
reg    [11:0] STRIPNUM180_NUM;

//新增参数
reg    [10:0] M_NUM;
reg    [21:0] CUTTIME180_Tini;
reg    [21:0] CUTTIME180_TEL;
reg    [21:0] OPENTIME_TEL;
reg    [21:0] CUTTIMEI90;
reg    [20:0] CS;
reg    [20:0] NS;

reg    [10:0] necount;
wire   [10:0] necount1;

reg    necount_LE_M;
reg    necount_LE_NE;
wire   necount_LE_M_1;
wire   necount_LE_NE_1;

reg fst_lst_pulse;
reg M_pulse;

always @ (posedge clk_sys)
    begin
         if (load == 1'b1)
             begin
                  case(loadchoice)
                      0:
                          begin
                               PLUSETIME90 <= datain; 
                          end
                      1:
                          begin
                               PLUSETIME180 <= datain; 
                          end
                      2:
                          begin
                               DUMPTIME <= datain; 
                          end
                      3:
                          begin
                               S_DUMPTIME <= datain; 
                          end
                      4:
                          begin
                               CUTTIME90[15:0] <= datain; 
                          end
                      5:
                          begin
                               CUTTIME90[21:16] <= datain[5:0]; 
                          end
                      6:
                          begin
                               CUTTIME180[15:0] <= datain; 
                          end
                      7:
                          begin
                               CUTTIME180[19:16] <= datain[3:0]; 
                          end
                      8:
                          begin
                               OPENTIME[15:0] <= datain; 
                          end
                      9:
                          begin
                               OPENTIME[19:16] <= datain[3:0]; 
                          end
                      10:
                          begin
                               ACQTIME <= datain; 
                          end                  
                      11:
                          begin
                               NE_NUM <= datain[10:0]; 
                          end                  
                      12:
                          begin
                               ACQ90_NUM <= datain[11:0]; 
                          end                  
                      13:
                          begin
                               ACQ180_NUM <= datain[11:0]; 
                          end                  
                      14:
                          begin
                               ACQECHO_NUM <= datain[11:0]; 
                          end                  
                      15:
                          begin
                               STRIPNUM90_NUM <= datain[11:0]; 
                          end                  
                      16:
                          begin
                               STRIPNUM180_NUM <= datain[11:0]; 
                          end
/***********************************新增二维DE序列参数************************************/
                      17:
                          begin
                               M_NUM <= datain[10:0];
                          end
                      18:
                          begin
                               CUTTIME180_TEL[15:0] <= datain;
                          end
                      19:
                          begin
                               CUTTIME180_TEL[21:16] <= datain[5:0];
                          end
                      20:
                          begin
                               OPENTIME_TEL[15:0] <= datain;
                          end
                      21:
                          begin
                               OPENTIME_TEL[21:16] <= datain[5:0];
                          end 
                      22:
                          begin
                                CUTTIME180_Tini[15:0] <= datain;
                          end
                      23:
                          begin
                               CUTTIME180_Tini[21:16] <= datain[5:0];
                          end 
                      24:
                          begin
                               CUTTIMEI90[15:0] <= datain; 
                          end
                      25:
                          begin
                               CUTTIMEI90[21:16] <= datain[5:0]; 
                          end                     
                  endcase
             end
         else
             begin
                  PLUSETIME90       <= PLUSETIME90; 
                  PLUSETIME180      <= PLUSETIME180; 
                  DUMPTIME          <= DUMPTIME; 
                  S_DUMPTIME        <= S_DUMPTIME; 
                  CUTTIME90[15:0]   <= CUTTIME90[15:0]; 
                  CUTTIME90[21:16]  <= CUTTIME90[21:16]; 
                  CUTTIME180[15:0]  <= CUTTIME180[15:0]; 
                  CUTTIME180[19:16] <= CUTTIME180[19:16]; 
                  OPENTIME[15:0]    <= OPENTIME[15:0]; 
                  OPENTIME[19:16]   <=  OPENTIME[19:16]; 
                  ACQTIME           <= ACQTIME; 
                  NE_NUM            <= NE_NUM; 
                  ACQ90_NUM         <= ACQ90_NUM; 
                  ACQ180_NUM        <= ACQ180_NUM; 
                  ACQECHO_NUM       <= ACQECHO_NUM; 
                  STRIPNUM90_NUM    <= STRIPNUM90_NUM; 
                  STRIPNUM180_NUM   <= STRIPNUM180_NUM; 
                  //新增参数
                  M_NUM                 <= M_NUM;   //前部分回波个数
                  CUTTIME180_TEL[15:0]  <= CUTTIME180_TEL[15:0]; 
                  CUTTIME180_TEL[21:16] <= CUTTIME180_TEL[21:16]; 
                  OPENTIME_TEL[15:0]    <= OPENTIME_TEL[15:0];    
                  OPENTIME_TEL[21:16]   <= OPENTIME_TEL[21:16]; 
                  CUTTIME180_Tini[15:0] <= CUTTIME180_Tini[15:0];   //最后一个长TEL180°脉冲发射后的关断时间
                  CUTTIME180_Tini[21:16]<= CUTTIME180_Tini[21:16];
                  CUTTIMEI90[15:0]   <= CUTTIMEI90[15:0]; 
                  CUTTIMEI90[21:16]  <= CUTTIMEI90[21:16];
             end
    end

always @ (posedge clk_sys)
   if(!rst_n) 
       CS <= IDLE;
   else 
       if(clken_p)      
           CS <= NS;

always @ (CS or necount_LE_NE or inv_turn)
    begin
        case(CS)
            IDLE:  
                NS = INI_RST1;
            CUT_DECI90:
                NS = INI_RST2;
            INI_RST1: 
                NS = INI_RST2;
            INI_RST2:
                NS = START;
            START:       
                NS = START_TEST;
            START_TEST:
                NS = PLUSE90;
            PLUSE90:
                NS = DUMP90;
            DUMP90:
                NS = SOFT_DUMP90;
            SOFT_DUMP90:
                NS = CUT_DEC90;
            CUT_DEC90:
                if(necount_LE_NE)
                    NS = RESET;
                else
                    NS = STOP;
            RESET:
                NS = DDSCONF;
            DDSCONF:
                NS = DDSCONF_TEST; 
            DDSCONF_TEST:
                NS = PLUSE180;
            PLUSE180:
                NS = DUMP180;
            DUMP180:
                NS = SOFT_DUMP180;
            SOFT_DUMP180:
                if (necount_LE_NE)
                    NS = OPEN_DEC;
                else
                    NS = CUT_DECI90;
            OPEN_DEC:
                NS = OPEN_SWITCH;
            OPEN_SWITCH:
                NS = ECHO_ACQ;
            ECHO_ACQ:
                NS = CUT_DEC180;   
            CUT_DEC180:
                NS = JUMP;
            JUMP:
                if(necount_LE_NE || inv_turn)
                    NS = RESET;
                else
                    NS = STOP;
            STOP:
                NS = STOP;
            default:
                NS = IDLE;
        endcase  
    end

always @ (posedge clk_sys)
    begin
        if(!rst_n)
            begin
                timecount     <= 50;    //定时器计数初始化  
                soft_d        <= 0;      //DEC通道隔离（DEC为DECOUPLE板简称）
                rt_sw         <= 0;       
                sw_acq1       <= 1;      //模拟开关采集通道关闭
                sw_acq2       <= 1;      
                s_acq         <= 0;     //信号采集停止状态
                s_acq180      <= 0;
                bb_ch         <= 0;
                pluse_start   <= 0;
                reset_out     <= 0;
                load_out      <= 0;
                pn_out        <= 0;
                dds_conf      <= 0;     //dds配置停止状态
                off_test      <= 0;
                dump_start    <= 0;
                dumpoff_ctr   <= 0;
                intertodsp    <= 0; 
                state_over_n  <= 1;   
                tetw_pluse    <= 1;
                long_opentime <= 0;
                dump_sustain_ctrl <= 0;

                necount <= 1;
                s_acqnum <= 0;
                strippluse <= 0;
                fst_lst_pulse <= 1;
                M_pulse <= 0;
            end        
        else 
            if(clken_p)
                case(NS)
                   IDLE:
                       ;
                   INI_RST1:
                       begin
                           reset_out <= 0;
 //                          if(pn_change==1)
 //                              begin
 //                                  pn_out <= 1;
 //                              end
 //                          else
 //                              begin
 //                                  pn_out <= 0;
 //                              end

                           timecount <= 90;
                       end
                   CUT_DECI90:
                       begin
                           soft_d  <= 0;      
                           rt_sw   <= 0;
                           //s_acq   <= 0; 
                           //dumpoff_ctr <= inv_turn;      
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           reset_out <= 0;              
          
                           timecount <= CUTTIMEI90;
                        end
                   INI_RST2:
                       begin
                           reset_out <= 1;
                           pn_out <= pn_change;
                           s_acqnum <= ACQ90_NUM;
                           strippluse <= STRIPNUM90_NUM;

                           timecount <= 200;
                       end
                   START:
                       begin
                           dump_start <= 1;          
                           soft_d  <= 1;      
                           rt_sw   <= 0;       
                           sw_acq1 <= 0;      
                           sw_acq2 <= 1;
                           dds_conf <= 1;     //dds配置启动
                           load_out  <= 1;
                           bb_ch <= 0;

                           timecount <= 30; 
                       end
                   START_TEST:
                       begin
                           dump_start <= 1;          
                           soft_d  <= 1;      
                           rt_sw   <= 0;       
                           sw_acq1 <= 0;      
                           sw_acq2 <= 1;
                           pluse_start <= 1;
                           dds_conf <= 1;     //dds配置启动
                           load_out  <= 1;
                           bb_ch <= 0;
                           s_acq <= 1;

                           timecount <= 570;
                       end
                   PLUSE90:
                       begin 
                           dds_conf <= 0;     //dds配置停止
                           load_out  <= 0;
                           off_test <=1'b1;

                           timecount <= PLUSETIME90; 
                       end
                   DUMP90:
                       begin
                           pluse_start <= 1'b0;          
                           soft_d  <= 1;      
                           rt_sw   <= 0;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           dump_start <= 1;
                           s_acq <= 0;            //信号采集控制
                           intertodsp <= 1;
                           off_test <= 1'b0;

                           timecount <= DUMPTIME; 
                       end
                   SOFT_DUMP90:
                       begin
                           dump_start <= 0;
                           soft_d  <= 1;      
                           rt_sw   <= 1;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           intertodsp <= 0;

                           timecount <= S_DUMPTIME;
                       end
                   CUT_DEC90:
                       begin
                           soft_d  <= 0;      
                           rt_sw   <= 0;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           reset_out <= 0;              
          
                           timecount <= CUTTIME90;
                        end
                   RESET:
                       begin
                           reset_out <= 1;                
                           if(fst_lst_pulse)
                               begin
                                   s_acqnum <= ACQ180_NUM;
                                   strippluse <= STRIPNUM180_NUM; 
                               end
                           pn_out <= 1;

                           timecount <= 200;
                       end
                   DDSCONF:
                       begin 
                           dump_start <= 1;  
                           soft_d  <= 1;  
                           rt_sw   <= 0;       
                           if(fst_lst_pulse)
                               begin  
                                   sw_acq1 <= 0;      
                                   sw_acq2 <= 1;
                               end            
                           dds_conf <= 1;     //dds配置启动
                           load_out  <= 1;
                           bb_ch <= 1;         
                           if(necount_LE_M)
                               long_opentime <= 1;
                           else  
                               long_opentime <= 0;

                           timecount <= 30;
                       end
                   DDSCONF_TEST:
                       begin 
                           dump_start <= 1;
                           soft_d  <= 1;      
                           rt_sw   <= 0;       
                           if(fst_lst_pulse)
                               begin  
                                   sw_acq1 <= 0;      
                                   sw_acq2 <= 1;
                                   s_acq180 <= 1;
                               end    
                           pluse_start <= 1;                        
                           dds_conf <= 1;     //dds配置启动
                           load_out  <= 1;
                           bb_ch <= 1; 
                           s_acq <= 1;            
          
                           timecount <= 570;
                       end
                   PLUSE180:
                       begin
                      //   pluse_start <= 1'b1; 
                           dds_conf <= 0;     //dds配置启动
                           load_out  <= 0;
                           off_test<=1'b1;

                           timecount <= PLUSETIME180;
                       end
                   DUMP180:
                       begin
                           pluse_start <= 0;
                           soft_d  <= 1;      
                           rt_sw   <= 0;          
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;          
                           dump_start <= 1;
                    //     s_acq <= 0;            //信号采集控制
                           off_test<= 0;
                           s_acq180 <= 0;
                           if(fst_lst_pulse)
                               begin
                                   intertodsp <= 1;
                               end                 
          
                           timecount <= DUMPTIME;
                       end
                   SOFT_DUMP180:
                       begin 
                           dump_start <= 0;
                           soft_d  <= 1;      
                           rt_sw   <= 1;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           intertodsp <= 0;
                           reset_out <= 0;
                           s_acqnum <= ACQECHO_NUM;
                           strippluse <= 0; 
                           dump_sustain_ctrl <= 1;
                            if (necount_LE_NE)
                                timecount <= S_DUMPTIME;
                            else
                                timecount <= 4000;
                       end
                  OPEN_DEC:
                       begin
                           soft_d  <= 0;      
                           rt_sw   <= 1;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 0;
                           reset_out <= 1;
                           load_out  <= 1;

                           if(necount_LE_M)
                               timecount <= OPENTIME_TEL;
                           else  
                               timecount <= OPENTIME;
                       end 
                   OPEN_SWITCH:
                       begin  
                           soft_d  <= 0;      
                           rt_sw   <= 1;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 0;
                           reset_out <= 1;
                           load_out  <= 1;
                           necount <= necount1;
                           dump_sustain_ctrl <= 0; 

                           timecount <= 200;
                       end
                   ECHO_ACQ:
                       begin
                           load_out  <= 0;
                           //s_acq <= 1;                         
                                 
                           timecount <= ACQTIME;
                       end

                   CUT_DEC180:
                       begin 
                           soft_d  <= 0;      
                           rt_sw   <= 0;       
                           sw_acq1 <= 1;      
                           sw_acq2 <= 1;
                           s_acq <= 0; 
                           intertodsp <= 1;

                           if(necount_LE_M)
                               timecount <= CUTTIME180_TEL;
                           else 
                               if(M_pulse)  
                                   timecount <= CUTTIME180_Tini;
                               else          
                                   timecount <= CUTTIME180;
                       end
                   JUMP:
                       begin
                           intertodsp <= 0;
                           reset_out <= 0;  
                           if(necount == NE_NUM)
                               fst_lst_pulse <= 1;
                           else
                               fst_lst_pulse <= 0; 
                           if(necount == M_NUM)
                               M_pulse <= 1;
                           else
                               M_pulse <= 0;                            

                           timecount <= 100;
                       end
                   STOP:
                       begin    
                           reset_out <= 1;              //不复位DUMP_OFF模块
                           dumpoff_ctr <= 1;           //序列完后主泄放断开，DUMP_OFF模块                               
                           state_over_n <= 0;    
                           tetw_pluse <=0;          
                       end
                   default:
                           ;
               endcase
    end

necount_inc necount_inc_0(necount,necount1);
necount_cmp necount_cmp_0(necount,M_NUM,necount_LE_M_1);
necount_cmp necount_cmp_1(necount,NE_NUM,necount_LE_NE_1);

always @(posedge clk_sys) 
    begin
        if(!rst_n)
            begin
                necount_LE_M <= 0;
                necount_LE_NE <=0;
            end
        else
            begin
                necount_LE_M <= necount_LE_M_1;    
                necount_LE_NE <= necount_LE_NE_1;
            end
    end
assign ne_le=necount_LE_NE;

endmodule

