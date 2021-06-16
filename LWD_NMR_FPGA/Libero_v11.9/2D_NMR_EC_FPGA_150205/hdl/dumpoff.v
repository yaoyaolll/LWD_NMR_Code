// dumpoff.v

module dumpoff(
                 reset,
                 clk,
                 dumpoff
                 );
input clk;
input reset;

output dumpoff;

reg dumpoff;
reg [4:0] count;  

always @ (posedge clk)
    begin
         if(!reset)
            begin
                 count <= 0;
                 dumpoff <=0;
            end

         else 
            begin
                if(count<=21)
                   begin
                        if(count==1)
                            begin
                                 dumpoff <= 1;
                                 count<= count+1;
                            end

                        else if(count==20)
                            begin
                                 dumpoff <= 0;
                                 count<= count+1;
                            end
                        else
                            begin
                                 count<= count+1;
                            end
                   end
                else
                  begin
                        count <= count;
                  end
                   
            end
    end

endmodule