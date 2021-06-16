// noiseclkctrl.v

module noiseclkctrl(
                    rst_n,
                    clk_sys,
                    load,
                    acqnum,
                    en,
                    clkin
                    );

input rst_n;
input clk_sys;
input load;
input [11:0] acqnum;
input clkin;

output en;

reg en;
reg [11:0] count;
reg [11:0] data;

always @ (posedge clk_sys)
  begin
       if (load == 1'b1)
           data <= acqnum;
       else
           data <= data;
  end

always @ (negedge rst_n or posedge clkin)  //clkin ÔëÉù²ÉÑùÂÊ 50MHz
  begin
        if (rst_n == 1'b0)
           begin
                 count <= 1;
                 en <= 1;
           end
        
        else
           begin
                 if(count >= data)
                   begin
                         en <= 0;
                   end
                 else
                   begin
                         count <= count + 1;
                   end
           end
  end

endmodule