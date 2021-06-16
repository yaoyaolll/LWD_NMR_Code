// bb_new.v


module bb_new(
              reset,
              clkin,
              load,
              halfdata,
              forward,
              back,
              dumpoff_ctrl
              );

input clkin;
input reset;
input load;
input [5:0] halfdata;

output forward;
output back;
output dumpoff_ctrl;

reg forward;
reg back;
reg dumpoff_ctrl;
reg [5:0] half_reg;
reg [5:0] count;


always @ (posedge load)
  begin
        half_reg <= halfdata;
  end

always @ (posedge reset or posedge clkin)
  begin
     if(reset)
        begin
              count <= 0;
              forward <= 0;
              back <= 0;
              dumpoff_ctrl <= 0;
        end     
     
     else
        begin
              if(count==0)
              begin
                 count<= count+1;
              end  
                     
              else
              begin

              if(count<=half_reg)
                 begin
                       count<= count+1;
                       if(count%8==1)
                          begin
                               forward <= 1;
                               back <= 0; 
                          end

                       else if(count%8==3)
                          begin
                               forward <= 0; 
                          end
                       else if(count%8==7)
                          begin
                               back<= 1; 
                               dumpoff_ctrl <= 0; 
                          end
                       else if(count%8==5)
                          begin
                               if(count==5)
                                 begin
                                      dumpoff_ctrl <= 1;   
                                 end
                          end
                 end

              else
                 begin
                     if(count==half_reg+1)
                          begin
                               forward <= 1;
                               back <= 0;
                               count <= half_reg+2;
                          end
                      else if(count==half_reg+2)
                          begin
                               forward <= 0;
                               count <= half_reg+3;                           
                          end
                      else if(count==half_reg+3)
                          begin
                               back <= 1;
                               count <= half_reg+4;                           
                          end
                      else if(count==half_reg+4)
                          begin
                               back <= 0;
                               count <= half_reg+1;                           
                          end
                 end
              end

              
        end 
  end



endmodule