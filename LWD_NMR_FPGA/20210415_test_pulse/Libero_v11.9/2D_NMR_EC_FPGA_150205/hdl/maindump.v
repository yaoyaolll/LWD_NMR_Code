// maindump.v

module maindump(
                clkin,
                reset,
                load,
                datain,
                choice,
                dumpon_str,
                dumpoff_str,
                over
                );

input clkin;
input reset;
input load;
input [15:0] datain;
input [1:0] choice;

output dumpon_str;
output dumpoff_str;
output over;

reg dumpon_str;
reg dumpoff_str;
reg over;

reg [11:0] w_time;
reg [11:0] one_dump;
reg [11:0] l_dump;
reg [13:0] count;

always @ (posedge load)
   begin
        case(choice)
               0:
                 begin
                      one_dump <= datain[11:0]; 
                 end              
               1:
                 begin
                      w_time <= datain[11:0]; 
                 end
               2:
                 begin
                      l_dump <= datain[11:0]; 
                 end
        endcase
   end

always @ (posedge reset or posedge clkin)
   begin
         if(reset)
             begin
                  count <= 0;
                  dumpon_str <= 0;
                  dumpoff_str <= 0;
                  over <= 1;
             end
         
         else
             begin
                  count <= count +1;
                  case(count)
                     w_time:
                            begin
                                 dumpon_str <= 1;
                            end  
                     one_dump:
                            begin
                                 dumpon_str <= 0;
                                 dumpoff_str <= 1;
                            end  
                     w_time+one_dump:
                            begin
                                 dumpon_str <= 1;
                                 dumpoff_str <= 0;
                            end   
                     one_dump+one_dump:
                            begin
                                 dumpon_str <= 0;
                                 dumpoff_str <= 1;
                            end   
                     w_time+one_dump+one_dump:
                            begin
                                 dumpon_str <= 1;
                                 dumpoff_str <= 0;
                            end   
                     l_dump:
                            begin
                                 dumpon_str <= 0;
                                 dumpoff_str <= 0;
                                 over <= 0;
                            end  
                  endcase  
             end
   end

endmodule