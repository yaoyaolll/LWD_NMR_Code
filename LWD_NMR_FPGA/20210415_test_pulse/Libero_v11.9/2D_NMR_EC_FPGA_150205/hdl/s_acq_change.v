// s_acq_change.v

module s_acq_change(
                     rst_n,
                     clk_sys,
                     change,
                     s_load,
                     s_loadin1,
                     s_loadin2,
                     s_rst,
                     s_rstin1,
                     s_rstin2,
                     //s_start,
                     //s_startin1,
                     //s_startin2,
                     s_acqnum,
                     s_acqnumin1,
                     s_acqnumin2,
                     s_stripnum,
                     s_stripnumin1,
                     s_stripnumin2
                     );

input rst_n;
input clk_sys;
input [1:0] change;

output s_load;
input  s_loadin1;
input  s_loadin2;
reg    s_load;

output s_rst;
input  s_rstin1;
input  s_rstin2;
reg    s_rst;

//output s_start;
//input  s_startin1;
//input  s_startin2;
//reg    s_start;

output [15:0] s_acqnum;
input  [15:0] s_acqnumin1;
input  [15:0] s_acqnumin2;
reg    [15:0] s_acqnum;

output [11:0] s_stripnum;
input  [11:0] s_stripnumin1;
input  [11:0] s_stripnumin2;
reg    [11:0] s_stripnum;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  s_load     <= 1'b0;
                  s_rst      <= 1'b0;
                  //s_start    <= 1'b0;
                  s_acqnum   <= 16'b0;
                  s_stripnum <= 12'b0;
             end
         else
             begin
                  if (change == 2'b00)
                      begin
                           s_load     <= s_loadin1;
                           s_rst      <= s_rstin1;
                           //s_start    <= s_startin1;
                           s_acqnum   <= s_acqnumin1;
                           s_stripnum <= s_stripnumin1;
                      end
                  else if (change == 2'b01)
                      begin
                           s_load     <= s_loadin2;
                           s_rst      <= s_rstin2;
                           //s_start    <= s_startin2;
                           s_acqnum   <= s_acqnumin2;
                           s_stripnum <= s_stripnumin2;
                      end
                  else
                      begin
                           s_load     <= s_load;
                           s_rst      <= s_rst;
                           //s_start    <= s_start;
                           s_acqnum   <= s_acqnum;
                           s_stripnum <= s_stripnum;
                      end
             end
    end

endmodule