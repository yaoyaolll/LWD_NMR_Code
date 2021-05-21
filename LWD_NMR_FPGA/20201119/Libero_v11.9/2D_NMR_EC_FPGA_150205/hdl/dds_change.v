// dds_change.v

module dds_change(
                  rst_n,
                  clk_sys,
                  change,
                  dds_rst,
                  ddsrstin1,
                  ddsrstin2,
                  ddsrstin3,
                  dds_conf,
                  dds_confin1,
                  dds_confin2,
                  dds_confin3
                 );

input rst_n;
input clk_sys;
input [1:0] change;


output dds_rst;
input  ddsrstin1;
input  ddsrstin2;
input  ddsrstin3;
reg dds_rst;

output dds_conf;
input  dds_confin1;
input  dds_confin2;
input  dds_confin3;
reg dds_conf;


always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  dds_rst   <= 1'b0;
                  dds_conf  <= 1'b0;
             end
         else
             begin
                  if (change == 2'b00)
                      begin
                           dds_rst   <= ddsrstin1;
                           dds_conf  <= dds_confin1;
                      end
                  else if (change == 2'b01)
                      begin
                           dds_rst   <= ddsrstin2;
                           dds_conf  <= dds_confin2;
                      end
                  else if (change == 2'b10)
                      begin
                           dds_rst   <= ddsrstin3;
                           dds_conf  <= dds_confin3;
                      end
                  else
                      begin
                           dds_rst   <= dds_rst;
                           dds_conf  <= dds_conf;
                      end
             end
    end

endmodule