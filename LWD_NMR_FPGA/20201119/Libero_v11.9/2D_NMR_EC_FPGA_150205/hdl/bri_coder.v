// bri_coder.v
module bri_coder(
                 clk_dds,
                 clk_4f_en,
                 rst_n,
                 state_start,
                 quar_delay,
                 phase,
                 count,
                 half_para,
                 half,
                 bri_cycle,
                 i,
                 turn_delay
                );
input clk_dds;
input clk_4f_en;
input rst_n;
input state_start;
input quar_delay;//1/4延时标志
input phase;//相位标志

input [7:0] count;
input [7:0] half_para;
input turn_delay;

output half;
output bri_cycle;
output [4:0] i;

reg half;//半频激励标志
reg bri_cycle;
reg [4:0] i;

always @ (count or half_para)
    begin
         if (count > half_para)
             {half,bri_cycle} = 2'b10;
         else if (count > 8'd5)
             {half,bri_cycle} = 2'b01;
         else
             {half,bri_cycle} = 2'b00;
    end

always @ (negedge rst_n or posedge clk_dds)//将quar_delay,phase，半频标志，启动标志同步化
    begin
         if (rst_n == 1'b0)
             i <= 5'b0;
         else
             begin
                  if (clk_4f_en == 1'b1)
                      i <= {turn_delay,quar_delay,phase,half,state_start};
                  else
                      i <= i;
             end
    end
//assign i = {quar_delay,phase,1'b0,1'b1};

endmodule