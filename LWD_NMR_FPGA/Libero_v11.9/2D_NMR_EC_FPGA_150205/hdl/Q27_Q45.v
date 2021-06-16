// Q27_Q45.v

module Q27_Q45(
               reset,
               datain,
               load,
               clk,
               Q2Q7,
               Q4Q5
               );
input clk;
input reset;
input [15:0] datain;
input load;

output Q2Q7;
output Q4Q5;

reg Q2Q7;
reg Q4Q5;
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
                   Q2Q7 <= 0;
                   Q4Q5 <= 0;
             end
         else 
             begin
                   
                   if(count<=data3)
                     begin
                           case(count)
                                    1:
                                      begin
                                           Q2Q7 <= 1;
                                           count<= count+1;
                                      end
                                    data1:
                                      begin
                                           Q4Q5 <= 1;
                                           count<= count+1;
                                      end
                                    data2:
                                      begin
                                           Q4Q5 <= 0;
                                           count<= count+1;
                                      end
                                    data3:
                                      begin
                                           Q2Q7 <= 0;
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