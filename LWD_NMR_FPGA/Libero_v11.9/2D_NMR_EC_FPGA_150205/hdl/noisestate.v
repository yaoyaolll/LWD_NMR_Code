// noisestate.v

module noisestate(
                  clk_sys,          //ɨƵ״̬��ʱ��
                  clken_p,
                  rst_n,          //ɨƵ״̬����λ
                  dumpon_ctr,
                  dumpoff_ctr,
                  soft_d,           //SOFT_DUMP�����ź�
                  rt_sw,            //RT_SW�����ź�
                  sw_acq1,          //SW_ACQ1�����ź�
                  sw_acq2,          //SW_ACQ2�����ź�
                  timecount,        //��ʱ������
                  n_acq,            //�����ɼ�����
                  state_over_n,         //״̬������
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


input  clk_sys;            //״̬��ʱ��
input  clken_p;
input  rst_n;            //״̬����λ
input  nload;
input  nchoice;
input  [15:0] ndatain;

output dumpon_ctr;
output dumpoff_ctr;

output soft_d;             //SOFT_DUMP�����ź�
output rt_sw;              //RT_SW�����ź�
output sw_acq1;            //SW_ACQ1�����ź�
output sw_acq2;            //SW_ACQ2�����ź�
output [19:0] timecount;   //��ʱ������
output n_acq;              //�����ɼ�����
output state_over_n;          //״̬������

reg dumpon_ctr;
reg dumpoff_ctr;

reg    soft_d;             //SOFT_DUMP�����ź�
reg    rt_sw;              //RT_SW�����ź�
reg    sw_acq1;            //SW_ACQ1�����ź�
reg    sw_acq2;            //SW_ACQ2�����ź�
reg    [19:0] timecount;   //��ʱ������
reg    n_acq;              //�����ɼ�����
reg    state_over_n;          //״̬������
//reg    [9:0] noisestate;    //״̬��״̬�ź�
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
             N_SOFTDUMP:                //DEC��й��
                NS = N_DECOPEN;       
             N_DECOPEN:                 //DECͨ����
                NS = N_SWICHOPEN;       
             N_SWICHOPEN:               //ģ�⿪��ͨ����
                NS = N_ACQUITION;       
             N_ACQUITION:               //�����ɼ�
                NS = CUT_DECO;          
             CUT_DECO:                  //DEC���룬�ɼ�ͨ���ر� 
                NS = STOP;          
             STOP:                      //����                   
                NS = STOP; 
            default:
                NS = IDLE;
        endcase 
    end

always @ (posedge clk_sys)
    begin
        if(rst_n == 1'b0)
            begin
                timecount <= 1;      //��ʱ��������ʼ��
                dumpon_ctr <= 1'b0;
                dumpoff_ctr <= 1'b0;
                soft_d  <= 0;        //DECͨ�����루DECΪDECOUPLE���ƣ�
                rt_sw   <= 0;       
                sw_acq1 <= 1;        //ģ�⿪�زɼ�ͨ���ر�
                sw_acq2 <= 1;      
                n_acq    <= 0;       //�����ɼ�ֹͣ״̬                             
                state_over_n <= 1;    //״̬������
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 100;
                    N_SOFTDUMP:                   //DEC��й��
                        begin
                            dumpon_ctr <= 1'b1;
                            soft_d  <= 1;        //��й��
                            rt_sw   <= 1;       
                            sw_acq1 <= 1;        //�ɼ�ͨ���ر�
                            sw_acq2 <= 1;                 
           
                            timecount <= 3000;    //��ʱʱ��
                        end  
                    N_DECOPEN:                      //DECͨ����
                        begin
                            dumpon_ctr <= 1'b0;
                            soft_d  <= 0;        //DECͨ����
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //�ɼ�ͨ���ر�
                            sw_acq2 <= 1;                        
           
                            timecount <= dectime;            //��ʱʱ��
                        end           
                    N_SWICHOPEN:                    //ģ�⿪��ͨ����
                        begin
                            soft_d  <= 0;        //DECͨ����
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //�ز��ɼ�ͨ����
                            sw_acq2 <= 0;

                            timecount <= 500;               //��ʱʱ��
                        end 
                    N_ACQUITION:                    //�����ɼ�
                        begin
                            soft_d  <= 0;        //DECͨ����
                            rt_sw   <= 1;           
                            sw_acq1 <= 1;        //�ز��ɼ�ͨ����
                            sw_acq2 <= 0;           
                            n_acq   <= 1;        //�����ɼ�

                            timecount <= acqtime;              //��ʱʱ��
                        end 
                    CUT_DECO:                       //DEC���룬�ɼ�ͨ���ر� 
                        begin
                            dumpoff_ctr <= 1'b1;
                            soft_d  <= 0;         //DECͨ������
                            rt_sw   <= 0;           
                            sw_acq1 <= 1;         //�ɼ�ͨ���ر�
                            sw_acq2 <= 1;           
                            n_acq   <= 0;         //�����ɼ�ֹͣ

                            timecount <= 100;      //��ʱʱ��
                        end  

                    STOP:                          //����   
                        begin
                            dumpoff_ctr <= 1'b0;
                            state_over_n <= 0;    //״̬������
                        end  
                    default:
                        ;
               endcase
           end
    end

endmodule