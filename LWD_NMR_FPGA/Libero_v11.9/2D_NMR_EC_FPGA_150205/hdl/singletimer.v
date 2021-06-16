// singletimer.v

module singletimer( 
             reset,     //��λ
             timeclk,   //��ʱ��ʱ��
             datain,    //��ʱ��������
             work,      //����״̬
             sigtimeup     //��ʱ���ж�
             );

input  reset;           //��λ
input  timeclk;         //��ʱ��ʱ��
input  [15:0] datain;   //��ʱ��������
input  work;            //����״̬


output sigtimeup;          //��ʱ���ж�

reg    sigtimeup;          //��ʱ���ж�
reg    [15:0] count;   //��ʱ��������


always @ (posedge reset or posedge timeclk)
   begin
           if(reset)                      //װ�ض�ʱʱ�估��λ
               begin
                     count <= 0;
                     sigtimeup <= 0;
               end    

           else
               begin                
                     if(!work)
                         begin
                               count <= count+1;
                               if(count >= datain)
                                  begin
                                        sigtimeup <= 1;
                                  end
                         end
               
               end              

   end

endmodule