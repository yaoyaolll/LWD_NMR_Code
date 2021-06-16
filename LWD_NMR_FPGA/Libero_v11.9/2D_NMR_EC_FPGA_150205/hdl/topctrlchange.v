// topctrlchange.v

module topctrlchange(
                     rst_n,
                     clk_sys,
                     change,
                     interupt,
                     interin1,
                     interin2,
                     interin3,
                     rt_sw,
                     rt_swin1,
                     rt_swin2,
                     rt_swin3,
                     soft_dump,
                     s_dumpin1,
                     s_dumpin2,
                     s_dumpin3,
                     sw_acq1,
                     sw_acq1in1,
                     sw_acq1in2,
                     sw_acq1in3,
                     sw_acq2,
                     sw_acq2in1,
                     sw_acq2in2,
                     sw_acq2in3
                     );

input rst_n;
input clk_sys;
input [1:0] change;

output interupt;
input  interin1;
input  interin2;
input  interin3;
reg interupt;

output rt_sw;
input  rt_swin1;
input  rt_swin2;
input  rt_swin3;
reg rt_sw;

output soft_dump;
input  s_dumpin1;
input  s_dumpin2;
input  s_dumpin3;
reg soft_dump;

output sw_acq1;
input  sw_acq1in1;
input  sw_acq1in2;
input  sw_acq1in3;
reg sw_acq1;

output sw_acq2;
input  sw_acq2in1;
input  sw_acq2in2;
input  sw_acq2in3;
reg sw_acq2;


always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  interupt  <= 1'b0;
                  rt_sw     <= 1'b0;
                  soft_dump <= 1'b0;
                  sw_acq1   <= 1'b1;
                  sw_acq2   <= 1'b1;
             end
         else
             begin
                  if (change == 2'b00)
                      begin
                           interupt  <= ~interin1;
                           rt_sw     <= rt_swin1;
                           soft_dump <= s_dumpin1;
                           sw_acq1   <= sw_acq1in1;
                           sw_acq2   <= sw_acq2in1;
                      end
                  else if (change == 2'b01)
                      begin
                           interupt  <= ~interin2;
                           rt_sw     <= rt_swin2;
                           soft_dump <= s_dumpin2;
                           sw_acq1   <= sw_acq1in2;
                           sw_acq2   <= sw_acq2in2;
                      end
                  else if (change == 2'b10)
                      begin
                           interupt  <= ~interin3;
                           rt_sw     <= rt_swin3;
                           soft_dump <= s_dumpin3;
                           sw_acq1   <= sw_acq1in3;
                           sw_acq2   <= sw_acq2in3;
                      end
                  else
                      begin
                           interupt  <= interupt;
                           rt_sw     <= rt_sw;
                           soft_dump <= soft_dump;
                           sw_acq1   <= sw_acq1;
                           sw_acq2   <= sw_acq2;
                      end
             end
    end

endmodule