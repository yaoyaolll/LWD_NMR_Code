// cal_load.v
module cal_load(
                clk_sys,
                cal_load,
                cal_para,
                cal_para_out
               );
input clk_sys;

input cal_load;
input [5:0] cal_para;

output [5:0] cal_para_out;

reg [5:0] cal_para_out;

always @ (posedge clk_sys)
    begin
         if (cal_load == 1'b1)
             cal_para_out <= cal_para;
         else
             cal_para_out <= cal_para_out;
    end

endmodule