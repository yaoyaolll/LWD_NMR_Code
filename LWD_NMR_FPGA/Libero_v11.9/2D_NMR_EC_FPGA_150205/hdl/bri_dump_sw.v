module bri_dump_sw(
                   rst_n,
                   clk_sys,
                   change,
                   pluse_start,
                   pluse_start1,
                   pluse_start2,
                   off_test,
                   off_test1,
                   off_test2,
                   dump_start,
                   dump_start1,
                   dump_start2,
                   phase_ctr,
                   phase_ctr1,
                   phase_ctr2,
                   reset_out,
                   reset_out1,
                   reset_out2,
                   dumpoff_ctr,
                   dumpoff_ctr1,
                   dumpoff_ctr2,
                   tetw_pluse,
                   tetw_pluse1,
                   tetw_pluse2,
                   turn_delay,
                   turn_delay1,
                   turn_delay2
                   );
input rst_n;
input clk_sys;
input change;

output turn_delay;
input turn_delay1;
input turn_delay2;
reg    turn_delay;

output tetw_pluse;
reg tetw_pluse;
input tetw_pluse1;
input tetw_pluse2;

output pluse_start;
input  pluse_start1;
input  pluse_start2;
reg    pluse_start;

output off_test;
input  off_test1;
input  off_test2;
reg    off_test;

output dump_start;
input  dump_start1;
input  dump_start2;
reg    dump_start;

output reset_out;
input  reset_out1;
input  reset_out2;
reg    reset_out;

output phase_ctr;
input  phase_ctr1;
input  phase_ctr2;
reg    phase_ctr;

output dumpoff_ctr;
input  dumpoff_ctr1;
input  dumpoff_ctr2;
reg    dumpoff_ctr;


always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  reset_out     <= 1'b0;
                  pluse_start   <= 1'b0;
                  dump_start    <= 1'b0;
                  phase_ctr     <= 1'b0;
                  dumpoff_ctr   <= 1'b0;
                  off_test      <= 1'b0;
                  tetw_pluse    <= 1'b0;
             end
         else
             begin
                  if (change == 1'b1)
                      begin
                           reset_out     <= reset_out1;
                           pluse_start   <= pluse_start1;
                           dump_start    <= dump_start1;
                           phase_ctr     <= phase_ctr1;
                           dumpoff_ctr   <= dumpoff_ctr1;
                           off_test      <= off_test1;
                           tetw_pluse    <= tetw_pluse1;
                           turn_delay    <= turn_delay1;
                      end
                  else
                      begin
                           reset_out     <= reset_out2;
                           pluse_start   <= pluse_start2;
                           dump_start    <= dump_start2;
                           phase_ctr     <= phase_ctr2;
                           dumpoff_ctr   <= dumpoff_ctr2;
                           off_test      <=off_test2;
                           tetw_pluse    <=tetw_pluse2;
                           turn_delay    <= turn_delay2;
                      end
             end
    end


endmodule