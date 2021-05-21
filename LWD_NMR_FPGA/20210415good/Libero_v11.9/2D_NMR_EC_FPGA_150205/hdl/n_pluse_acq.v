// n_pluse_acq.v

module n_pluse_acq(
                   rst_n,
                   clk_sys,
                   change,
                   n_acq_startin1,
                   n_acq_startin2,
                   n_acq_start,
                   n_rstin1_n,
                   n_rstin2_n,
                   n_rst_n
                   );
input rst_n;
input clk_sys;
input change;

input  n_acq_startin1;
input  n_acq_startin2; 
input  n_rstin1_n;
input  n_rstin2_n;

output n_acq_start;
output n_rst_n;

reg n_acq_start;
reg n_rst_n;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  n_acq_start <= 1'b0;
                  n_rst_n     <= 1'b0;
             end
         else
             begin
                  if (change == 1'b1)
                      begin
                           n_acq_start <= n_acq_startin1;
                           n_rst_n     <= n_rstin1_n;
                      end
                  else
                      begin
                           n_acq_start <= n_acq_startin2;
                           n_rst_n     <= n_rstin2_n;
                      end
             end
    end

endmodule