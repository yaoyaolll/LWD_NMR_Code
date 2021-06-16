// Q18_Q36.v

module Q18_Q36(
               reset,
               datain,
               load,
               clk,
               Q1Q8,
               Q3Q6
               );
input clk;
input reset;
input [15:0] datain;
input load;

output Q1Q8;
output Q3Q6;

reg Q1Q8;
reg Q3Q6;
reg [4:0] count;  
reg [15:0] widthdata;
reg [3:0] data1;
reg [5:0] data2;
reg [5:0] data3;

always @ (posedge load)
    begin
          widthdata <= datain;
          data1 <= 1+ widthdata[3:0];
          data2 <= 1+ widthdata[9:4];
          data3 <= 1+ widthdata[15:10];
    end


always @ (posedge clk)
    begin
         if(!reset)
             begin
                   count <= 1;
                   Q1Q8 <= 0;
                   Q3Q6 <= 0;
             end
         else 
             begin                   
                   if(count<=data3)
                     begin
                           case(count)
                                    1:
                                      begin
                                           Q1Q8 <= 1;
                                           count<= count+1;
                                      end
                                    data1:
                                      begin
                                           Q3Q6 <= 1;
                                           count<= count+1;
                                      end
                                    data2:
                                      begin
                                           Q3Q6 <= 0;
                                           count<= count+1;
                                      end
                                    data3:
                                      begin
                                           Q1Q8 <= 0;
                                           count<= count+1;
                                      end
                                    default:
                                      begin
                                           count<= count+1;
                                      end
                           endcase
                     end
                   
             end
    end

endmodule