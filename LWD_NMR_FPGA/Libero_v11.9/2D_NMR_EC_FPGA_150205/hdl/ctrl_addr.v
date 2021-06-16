// ctrl_addr.v

module ctrl_addr(
                 rst_n,
                 clk_sys,
                 clk,
                 addrout,
                 datain,
                 load
                 );
input rst_n;
input clk_sys;
input clk;
input [3:0] datain;
input load;

output [3:0] addrout;
reg [3:0] addrout;

reg [3:0] datareg;

always @ (posedge clk_sys)
 begin
     if (load == 1'b1)
      datareg <= datain;
     else
      datareg <= datareg;
 end

always @ (negedge rst_n or negedge clk)
  begin
        if (rst_n == 1'b0)
           begin
                 addrout <= 1;
           end
        else
           begin
                 if(addrout == datareg)
                     begin
                           addrout<=1; 
                     end
                 else
                     begin
                           addrout <= addrout +1;
                     end
           end
  end

endmodule