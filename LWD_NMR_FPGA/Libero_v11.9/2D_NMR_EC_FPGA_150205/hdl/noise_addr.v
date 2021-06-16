// noise_addr.v

module noise_addr(
                 clkin,
                 rst_n,
                 addr 
                 );

input clkin;
input rst_n;

output [11:0] addr;

reg [11:0] addr;

always @ (negedge rst_n or negedge clkin)
   begin
         if (rst_n == 1'b0)
             begin
                   addr <= 0;
             end
          
         else 
             begin
                   addr <= addr + 1;
             end

   end

endmodule