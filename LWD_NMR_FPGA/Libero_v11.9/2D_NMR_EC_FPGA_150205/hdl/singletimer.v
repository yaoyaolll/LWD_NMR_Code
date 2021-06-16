// singletimer.v

module singletimer( 
             reset,     //复位
             timeclk,   //定时器时钟
             datain,    //定时数据输入
             work,      //工作状态
             sigtimeup     //定时器中断
             );

input  reset;           //复位
input  timeclk;         //定时器时钟
input  [15:0] datain;   //定时数据输入
input  work;            //工作状态


output sigtimeup;          //定时器中断

reg    sigtimeup;          //定时器中断
reg    [15:0] count;   //定时器计数器


always @ (posedge reset or posedge timeclk)
   begin
           if(reset)                      //装载定时时间及复位
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