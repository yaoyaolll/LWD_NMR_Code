// dumpon.v


module dumpon(
                 reset,
                 clk,
                 dumpon
                 );
input clk;
input reset;

output dumpon;

reg dumpon;
reg [4:0] count;  

always @ (posedge clk)
    begin
         if(!reset)
            begin
                 count <= 0;
                 dumpon <=0;
            end

         else 
            begin
                if(count<=21)
                   begin
                        if(count==1)
                            begin
                                 dumpon <= 1;
                                 count<= count+1;
                            end

                        else if(count==20)
                            begin
                                 dumpon <= 0;
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