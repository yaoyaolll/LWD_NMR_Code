// state1ms_dump_choice.v
module state1ms_choice(
                       rst_n,
                       clk_sys,
                       change,
                       pluse_start,
                       pluse_start1,
                       pluse_start2,
                       dump_start,
                       dump_start1,
                       dump_start2,
                       reset_out,
                       reset_out1,
                       reset_out2,
                       bri_cycle,
                       bri_cycle1,
                       bri_cycle2,
                       rt_sw,
                       rt_sw1,
                       rt_sw2,
                       soft_dump,
                       soft_dump1,
                       soft_dump2
                       );
input rst_n;
input clk_sys;
input change;

output pluse_start;
input  pluse_start1;
input  pluse_start2;
reg    pluse_start;

output dump_start;
input  dump_start1;
input  dump_start2;
reg    dump_start;

output reset_out;
input  reset_out1;
input  reset_out2;
reg    reset_out;

output bri_cycle;
input  bri_cycle1;
input  bri_cycle2;
reg    bri_cycle;

output rt_sw;
input  rt_sw1;
input  rt_sw2;
reg rt_sw;

output soft_dump;
input  soft_dump1;
input  soft_dump2;
reg soft_dump;


always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             begin
                  reset_out     <= 1'b0;
                  bri_cycle     <= 1'b0;
                  pluse_start   <= 1'b0;
                  dump_start    <= 1'b0;
             end
         else
             begin
                  if (change == 1'b1)
                      begin
                           reset_out     <= reset_out1;
                           bri_cycle     <= bri_cycle1;
                           pluse_start   <= pluse_start1;
                           dump_start    <= dump_start1;
                           rt_sw         <= rt_sw1;
                           soft_dump     <= soft_dump1;
                      end
                  else
                      begin
                           reset_out     <= reset_out2;
                           bri_cycle     <= bri_cycle2;
                           pluse_start   <= pluse_start2;
                           dump_start    <= dump_start2;
                           rt_sw         <= rt_sw2;
                           soft_dump     <= soft_dump2;
                      end
             end
    end


endmodule