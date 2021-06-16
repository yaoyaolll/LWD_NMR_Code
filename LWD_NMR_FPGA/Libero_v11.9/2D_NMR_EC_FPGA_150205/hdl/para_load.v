// bri_qq_load.v
module bri_qq_load(
                   clk_sys,
                   pluse_load,
                   bri_para,
                   qq_para,
                   half_para,
                   qq_para1,
                   qq_para2,
                   qq_para3
                  );

input clk_sys;
input pluse_load;

input [7:0]  bri_para;
input [15:0] qq_para;

output [3:0] qq_para1;
output [5:0] qq_para2;
output [5:0] qq_para3;
output [7:0] half_para;

reg [3:0] qq_para1;
reg [5:0] qq_para2;
reg [5:0] qq_para3;
reg [7:0] half_para;

always @ (posedge clk_sys)
    begin
         if (pluse_load == 1'b1)
             begin
                  half_para <= bri_para;
                  qq_para1  <= qq_para[3:0];
                  qq_para2  <= qq_para[9:4];
                  qq_para3  <= qq_para[15:10];
             end
         else
             begin
                  half_para <= half_para;
                  qq_para1  <= qq_para1;
                  qq_para2  <= qq_para2;
                  qq_para3  <= qq_para3;
             end
    end

endmodule