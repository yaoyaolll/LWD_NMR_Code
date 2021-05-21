// scanstate.v

module scanstate(
                 clk_sys,          //É¨Æµ×´Ì¬»úÊ±ÖÓ
                 clken_p,
                 rst_n,          //É¨Æµ×´Ì¬»ú¸´Î»
                 dumpon_ctr,
                 dumpoff_ctr,
                 soft_d,           //SOFT_DUMP¿ØÖÆĞÅºÅ
                 rt_sw,            //RT_SW¿ØÖÆĞÅºÅ
                 sw_acq1,          //SW_ACQ1¿ØÖÆĞÅºÅ
                 sw_acq2,          //SW_ACQ2¿ØÖÆĞÅºÅ
                 timecount,        //¶¨Ê±Æ÷¼ÆÊı
                 s_acq,            //ĞÅºÅ²É¼¯¿ØÖÆ
                 dds_conf,         //ddsÅäÖÃ¿ØÖÆ
                 calctrl,          //calĞÅºÅÊä³ö¿ØÖÆ
                 state_over_n,         //×´Ì¬»ú½áÊø
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


input  clk_sys;            //É¨Æµ×´Ì¬»úÊ±ÖÓ
input  clken_p;
input  rst_n;            //É¨Æµ×´Ì¬»ú¸´Î»
input  [15:0] datain;
input  scanload;
input  scanchoice;

output dumpon_ctr;
output dumpoff_ctr;

output soft_d;             //SOFT_DUMP¿ØÖÆĞÅºÅ
output rt_sw;              //RT_SW¿ØÖÆĞÅºÅ
output sw_acq1;            //SW_ACQ1¿ØÖÆĞÅºÅ
output sw_acq2;            //SW_ACQ2¿ØÖÆĞÅºÅ
output [19:0] timecount;   //¶¨Ê±Æ÷¼ÆÊı
output s_acq;              //ĞÅºÅ²É¼¯¿ØÖÆ
output dds_conf;           //ddsÅäÖÃ¿ØÖÆ
output calctrl;            //calĞÅºÅÊä³ö¿ØÖÆ
output state_over_n;          //×´Ì¬»ú½áÊø
output resetout;

reg dumpon_ctr;
reg dumpoff_ctr;

reg    soft_d;             //SOFT_DUMP¿ØÖÆĞÅºÅ
reg    rt_sw;              //RT_SW¿ØÖÆĞÅºÅ
reg    sw_acq1;            //SW_ACQ1¿ØÖÆĞÅºÅ
reg    sw_acq2;            //SW_ACQ2¿ØÖÆĞÅºÅ
reg    [19:0] timecount;   //¶¨Ê±Æ÷¼ÆÊı
reg    s_acq;              //ĞÅºÅ²É¼¯¿ØÖÆ
reg    dds_conf;           //ddsÅäÖÃ¿ØÖÆ
reg    calctrl;            //calĞÅºÅÊä³ö¿ØÖÆ
reg    state_over_n;          //×´Ì¬»ú½áÊø

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
                timecount <= 1;           //¶¨Ê±Æ÷¼ÆÊı³õÊ¼»¯
                dumpon_ctr <= 1'b0;
                dumpoff_ctr <= 1'b0;
                soft_d  <= 0;         //DECÍ¨µÀ¸ôÀë£¨DECÎªDECOUPLE°å¼ò³Æ£©
                rt_sw   <= 0;       
                sw_acq1 <= 1;         //Ä£Äâ¿ª¹Ø²É¼¯Í¨µÀ¹Ø±Õ
                sw_acq2 <= 1;      
                s_acq    <= 0;        //ĞÅºÅ²É¼¯Í£Ö¹×´Ì¬
                dds_conf <= 0;        //ddsÅäÖÃÍ£Ö¹×´Ì¬
                calctrl  <= 0;        //calĞÅºÅ²»Êä³ö             
                state_over_n <= 1;    //×´Ì¬»ú¹¤×÷
                resetout <= 0;
            end        
        else
            begin
                case(NS)
                    IDLE:  
                        ; 
                    INIT:            
                        timecount <= 100;
                    S_SOFTDUMP:                     //DECÈíĞ¹·Å  
                         begin                             
                             dumpon_ctr <= 1'b1;
                             soft_d  <= 1;      //ÈíĞ¹·Å
                             rt_sw   <= 1;       
                             sw_acq1 <= 1;      //²É¼¯Í¨µÀ¹Ø±Õ
                             sw_acq2 <= 1;
                             dds_conf <= 1;     //ddsÅäÖÃÆô¶¯
                            
                             timecount <= 3000;            //¶¨Ê±Ê±¼ä
                          end
                    S_DECOPEN:                      //DECÍ¨µÀ´ò¿ªÍ¬Ê±ÅäÖÃdds©
                          begin
                             dumpon_ctr <= 1'b0;
                             soft_d  <= 0;      //DECÍ¨µÀ´ò¿ª
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //²É¼¯Í¨µÀ¹Ø±Õ
                             sw_acq2 <= 1;
                             dds_conf <= 0;     //ddsÅäÖÃ¹Ø±Õ
                             calctrl  <= 1;     //calĞÅºÅÊä³ö 
                             resetout <= 0;

                             timecount <= dectime;            //¶¨Ê±Ê±¼ä                             
                          end
                    S_SWICHOPEN:                    //Ä£Äâ¿ª¹ØÍ¨µÀ´ò¿ª
                          begin
                             soft_d  <= 0;      //DECÍ¨µÀ´ò¿ª
                             rt_sw   <= 1;       
                           //  sw_acq1 <= 1;      //»Ø²¨²É¼¯Í¨µÀ´ò¿ª
                             sw_acq2 <= 0;
                             resetout <= 1;

                             timecount <= 500;               //¶¨Ê±Ê±¼ä
                          end
                    S_ACQUITION:                    //ĞÅºÅ²É¼¯
                          begin
                             soft_d  <= 0;      //DECÍ¨µÀ´ò¿ª
                             rt_sw   <= 1;       
                            // sw_acq1 <= 1;      //»Ø²¨²É¼¯Í¨µÀ´ò¿ª
                             sw_acq2 <= 0;
                             s_acq   <= 1;     //ĞÅºÅ²É¼¯Æô¶¯

                             timecount <= acqtime;
                          end         
                    CUT_DECO:                       //DEC¸ôÀë£¬²É¼¯Í¨µÀ¹Ø±Õ 
                          begin
                             dumpoff_ctr <= 1'b1;
                             soft_d  <= 0;      //DECÍ¨µÀ¸ôÀë
                             rt_sw   <= 0;       
                            // sw_acq1 <= 1;      //²É¼¯Í¨µÀ¹Ø±Õ
                             sw_acq2 <= 1;
                             calctrl <= 0;     //calĞÅºÅ²»Êä³ö  

                             timecount <= 100;      //¶¨Ê±Ê±¼ä
                          end  
                    STOP:                           //½áÊø   
                          begin
                             dumpoff_ctr <= 1'b0;
                             state_over_n <= 0;    //×´Ì¬»ú½áÊø
                          end  
                   default:
                        ;
               endcase
           end
    end

endmodule