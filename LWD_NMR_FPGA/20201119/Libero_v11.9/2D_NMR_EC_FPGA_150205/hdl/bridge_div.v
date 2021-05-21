// bridge_div.v


module bridge_div(
                     bri_div_start,
                     rst_n,     //复位
                     clk_sys,
                     clk_dds,     //时钟输入
                     load,      //装载分频数据
                     divcount,  //分频数据
                     clk_4f_en     //时钟输出
                    );

input bri_div_start;
input rst_n;
input clk_sys;
input clk_dds;
input load;
input [5:0] divcount;

output clk_4f_en;

reg    clk_4f;
reg    [5:0] count;
reg    [2:0] datahalf;
reg    [5:0] dataall;

reg clear1_n;
reg clear2_n;

reg clk_4f_reg1;
reg clk_4f_reg2;

always @ (posedge clk_sys)
    begin
         if (load == 1'b1)
             begin
                  datahalf <= divcount[2:0];
                  dataall  <= divcount[5:3]+divcount[2:0];
             end
         else
             begin
                  datahalf <= datahalf;
                  dataall  <= dataall;
             end
   end

always @ (negedge rst_n or posedge clk_dds)
    begin
         if (rst_n == 1'b0)
             begin
                  count  <= 4'b1;
                  clk_4f <= 1'b0;
             end
         else
             begin
               if(bri_div_start == 1'b1)
                 begin
                  if (clear1_n == 1'b0)
                      begin
                           count  <= count + 1;
                           clk_4f <= ~clk_4f;
                      end
                  else if (clear2_n == 1'b0)
                      begin
                           count  <= 1'b1;
                           clk_4f <= ~clk_4f;
                      end
                  else
                      begin
                           count  <= count +1;
                           clk_4f <= clk_4f;
                      end
                 end
               else
                 begin
                      count  <= 4'b1;
                      clk_4f <= 1'b0;
                 end
             end
    end

always @ (count or datahalf or dataall)
    begin
         case (count)
             datahalf:
                 {clear2_n,clear1_n} = 2'b10;
             dataall:
                 {clear2_n,clear1_n} = 2'b01;
             default:
                 {clear2_n,clear1_n} = 2'b11;
         endcase
    end

always @ (negedge rst_n or posedge clk_dds)
    begin
         if (rst_n == 1'b0)
             {clk_4f_reg1,clk_4f_reg2} <= 2'b0;
         else
             begin
                  clk_4f_reg1 <= clk_4f;
                  clk_4f_reg2 <= clk_4f_reg1;
             end
    end

assign clk_4f_en = clk_4f_reg1 &(~clk_4f_reg2);

endmodule