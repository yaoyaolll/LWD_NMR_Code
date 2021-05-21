// nsctrl_choice.v

module nsctrl_choice(
                     rst_n,
                     clk_sys,
                     change,
                     soft_d_s,           //SOFT_DUMP控制信号
                     rt_sw_s,            //RT_SW控制信号
                     sw_acq1_s,          //SW_ACQ1控制信号
                     sw_acq2_s,          //SW_ACQ2控制信号
                     inter_s,
                     dumpon_ctr_s,
                     dumpoff_ctr_s,
                     dumponoff_rst_s,
                     soft_d_n,           //SOFT_DUMP控制信号
                     rt_sw_n,            //RT_SW控制信号
                     sw_acq1_n,          //SW_ACQ1控制信号
                     sw_acq2_n,          //SW_ACQ2控制信号
                     inter_n,
                     dumpon_ctr_n,
                     dumpoff_ctr_n,
                     dumponoff_rst_n,
                     soft_d,           //SOFT_DUMP控制信号
                     rt_sw,            //RT_SW控制信号
                     sw_acq1,          //SW_ACQ1控制信号
                     sw_acq2,          //SW_ACQ2控制信号
                     intertodsp,
                     dumpon_ctr,
                     dumpoff_ctr,
                     dumponoff_rst
                     );
input rst_n;
input clk_sys;
input change;

input soft_d_s;
input rt_sw_s;
input sw_acq1_s;
input sw_acq2_s;
input dumpon_ctr_s;
input dumpoff_ctr_s;
input dumponoff_rst_s;
input inter_s;
input soft_d_n;           
input rt_sw_n;            
input sw_acq1_n;          
input sw_acq2_n;          
input inter_n;
input dumpon_ctr_n;
input dumpoff_ctr_n;
input dumponoff_rst_n;

output soft_d;          
output rt_sw;           
output sw_acq1;          
output sw_acq2;         
output intertodsp;
output dumpon_ctr;
output dumpoff_ctr;
output dumponoff_rst;

reg soft_d;          
reg rt_sw;           
reg sw_acq1;          
reg sw_acq2;         
reg intertodsp;
reg dumpon_ctr;
reg dumpoff_ctr;
reg dumponoff_rst;


always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  soft_d        <= 1'b0;
                  rt_sw         <= 1'b0;
                  sw_acq1       <= 1'b1;
                  sw_acq2       <= 1'b1;
                  intertodsp    <= 1'b0;
                  dumpon_ctr    <= 1'b0;
                  dumpoff_ctr   <= 1'b0;
                  dumponoff_rst <= 1'b0;
             end
         else
             begin
                  if (change == 1'b1)
                      begin
                           soft_d        <= soft_d_n;
                           rt_sw         <= rt_sw_n;
                           sw_acq1       <= sw_acq1_n;
                           sw_acq2       <= sw_acq2_n;
                           intertodsp    <= inter_n;
                           dumpon_ctr    <= dumpon_ctr_n;
                           dumpoff_ctr   <= dumpoff_ctr_n;
                           dumponoff_rst <= dumponoff_rst_n;
                      end
                  else
                      begin
                           soft_d        <= soft_d_s;
                           rt_sw         <= rt_sw_s;
                           sw_acq1       <= sw_acq1_s;
                           sw_acq2       <= sw_acq2_s;
                           intertodsp    <= inter_s;
                           dumpon_ctr    <= dumpon_ctr_s;
                           dumpoff_ctr   <= dumpoff_ctr_s;
                           dumponoff_rst <= dumponoff_rst_s;
                      end
             end
    end

endmodule