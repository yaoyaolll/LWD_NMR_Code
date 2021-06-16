//noiseclk.v

module noiseclk(
                clk_sys,
                clken,
                n_acq_en,
                divnum,
                rst_n,
                load,
                clkout
                );
input clk_sys;
input clken;
input n_acq_en;
input rst_n;
input [9:0]divnum;
input load;

output clkout;


reg clkout;
reg [4:0] datahalf;
reg [4:0] dataall;
reg [4:0] count;

wire en;
assign en = clken & n_acq_en;

always @ (posedge clk_sys)
  begin
       if (load == 1'b1)
        begin
        datahalf <= divnum[4:0];
        dataall  <= divnum[9:5]+divnum[4:0];
        end
       else
        begin
        datahalf <= datahalf;   //datahalf = 10
        dataall  <= dataall;    //dataall  = 20
        end
  end



always @ (posedge clk_sys)
  begin
        if (rst_n == 1'b0)
           begin
                 count <= 1;
                 clkout <= 0;
           end
   
        else
           begin
             if (en == 1'b1)
               begin
                 if(count==datahalf) 
                     begin
                           clkout <= ~clkout;
                           count <= count + 1;          //dataall-datahalf = 高电平时间，调整占空比
                     end                                // 则噪声采样率为 1/20 = 50MHz
                 else if (count>=dataall)
                     begin
                           clkout <= ~clkout;
                           count <= 1;
                     end
                 else
                     begin
                           count <= count + 1;
                     end
               end
             else
               begin
                 count <= 1;
                 clkout <= 0;
               end
           end
  end


endmodule