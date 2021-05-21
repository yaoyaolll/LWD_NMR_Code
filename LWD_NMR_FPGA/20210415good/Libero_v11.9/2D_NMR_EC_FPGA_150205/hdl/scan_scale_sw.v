// scan_scale_sw.v
module scan_scale_sw(
                     rst_n,
                     dds,
                     change,                     
                     s_start,
                     s_startin1,
                     s_startin2                  
                     );

input rst_n;
input dds;
input [1:0] change;

output s_start;
input  s_startin1;
input  s_startin2;
reg    s_start;


always @ (posedge dds)
    begin
         if (rst_n == 1'b0)
             begin
                  s_start    <= 1'b0;
             end
         else
             begin
                  if (change == 2'b00)
                      begin
                           s_start    <= s_startin1;
                      end
                  else if (change == 2'b01)
                      begin                
                           s_start    <= s_startin2;
                      end
                  else
                      begin
                           s_start    <= s_start;

                      end
             end
    end

endmodule