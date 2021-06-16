// cal_div.v
module cal_div(
               clk_dds,
               rst_n,
               cal_start,
               cal_para,
               cal
              );
input clk_dds;
input rst_n;
input cal_start;
input [5:0] cal_para;

output cal;

reg cal;

reg clear_n;
reg [5:0] count;

always @ (posedge clk_dds)
    begin
         if (rst_n == 1'b0)
             begin
                  count <= 6'b1;
                  cal   <= 1'b0;
             end
         else
             begin
                  if (cal_start == 1'b1)
                      begin
                           if (clear_n == 1'b0)
                               begin
                                    count <= 6'b1;
                                    cal   <= ~cal;
                               end
                           else
                               begin
                                    count <= count + 1;
                                    cal <= cal;
                               end
                      end
                  else
                      begin
                           count <= 6'b1;
                           cal <= 1'b0;
                      end
             end
    end

always @ (count or cal_para)
    begin
         if (count == cal_para)//¸Ä½ø
             clear_n = 1'b0;
         else
             clear_n = 1'b1;
    end

endmodule