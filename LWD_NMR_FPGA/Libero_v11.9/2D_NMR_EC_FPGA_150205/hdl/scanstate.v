// scanstate.v

module scanstate(
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
                 s_acq,            //�źŲɼ�����
                 dds_conf,         //dds���ÿ���
                 calctrl,          //cal�ź��������
                 state_over_n,         //״̬������
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


input  clk_sys;            //ɨƵ״̬��ʱ��
input  clken_p;
input  rst_n;            //ɨƵ״̬����λ
input  [15:0] datain;
input  scanload;
input  scanchoice;

output dumpon_ctr;
output dumpoff_ctr;

output soft_d;             //SOFT_DUMP�����ź�
output rt_sw;              //RT_SW�����ź�
output sw_acq1;            //SW_ACQ1�����ź�
output sw_acq2;            //SW_ACQ2�����ź�
output [19:0] timecount;   //��ʱ������
output s_acq;              //�źŲɼ�����
output dds_conf;           //dds���ÿ���
output calctrl;            //cal�ź��������
output state_over_n;          //״̬������
output resetout;

reg dumpon_ctr;
reg dumpoff_ctr;

reg    soft_d;             //SOFT_DUMP�����ź�
reg    rt_sw;              //RT_SW�����ź�
reg    sw_acq1;            //SW_ACQ1�����ź�
reg    sw_acq2;            //SW_ACQ2�����ź�
reg    [19:0] timecount;   //��ʱ������
reg    s_acq;              //�źŲɼ�����
reg    dds_conf;           //dds���ÿ���
reg    calctrl;            //cal�ź��������
reg    state_over_n;          //״̬������

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
                timecount <= 1;           //��ʱ��������ʼ��
                dumpon_ctr <= 1'b0;
                dumpoff_ctr <= 1'b0;
                soft_d  <= 0;         //DECͨ�����루DECΪDECOUPLE���ƣ�
                rt_sw   <= 0;       
                sw_acq1 <= 1;         //ģ�⿪�زɼ�ͨ���ر�
                sw_acq2 <= 1;      
                s_acq    <= 0;        //�źŲɼ�ֹͣ״̬
                dds_conf <= 0;        //dds����ֹͣ״̬
                calctrl  <= 0;        //cal�źŲ����             
                state_over_n <= 1;    //״̬������
                resetout <= 0;
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 100;
                    S_SOFTDUMP:                     //DEC��й��  
                         begin                             
                             dumpon_ctr <= 1'b1;
                             soft_d  <= 1;      //��й��
                             rt_sw   <= 1;       
                             sw_acq1 <= 1;      //�ɼ�ͨ���ر�
                             sw_acq2 <= 1;
                             dds_conf <= 1;     //dds��������
                            
                             timecount <= 3000;            //��ʱʱ��
                          end
                    S_DECOPEN:                      //DECͨ����ͬʱ����dds�
                          begin
                             dumpon_ctr <= 1'b0;
                             soft_d  <= 0;      //DECͨ����
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //�ɼ�ͨ���ر�
                             sw_acq2 <= 1;
                             dds_conf <= 0;     //dds���ùر�
                             calctrl  <= 1;     //cal�ź���� 
                             resetout <= 0;

                             timecount <= dectime;            //��ʱʱ��                             
                          end
                    S_SWICHOPEN:                    //ģ�⿪��ͨ����
                          begin
                             soft_d  <= 0;      //DECͨ����
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //�ز��ɼ�ͨ����
                             sw_acq2 <= 0;
                             resetout <= 1;

                             timecount <= 500;               //��ʱʱ��
                          end
                    S_ACQUITION:                    //�źŲɼ�
                          begin
                             soft_d  <= 0;      //DECͨ����
                             rt_sw   <= 1;       
                            // sw_acq1 <= 1;      //�ز��ɼ�ͨ����
                             sw_acq2 <= 0;
                             s_acq   <= 1;     //�źŲɼ�����

                             timecount <= acqtime;
                          end         
                    CUT_DECO:                       //DEC���룬�ɼ�ͨ���ر� 
                          begin
                             dumpoff_ctr <= 1'b1;
                             soft_d  <= 0;      //DECͨ������
                             rt_sw   <= 0;       
                            // sw_acq1 <= 1;      //�ɼ�ͨ���ر�
                             sw_acq2 <= 1;
                             calctrl <= 0;     //cal�źŲ����  

                             timecount <= 100;      //��ʱʱ��
                          end  
                    STOP:                           //����   
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