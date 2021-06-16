// n_rd_addr.v

module n_rd_addr(
                 clkin,
                 rst_n,
                 addr 
                 );

input clkin;
input rst_n;

output [11:0] addr;

reg [11:0] addr;

always @ (posedge rst_n or negedge clkin)
   begin
         if(rst_n == 1'b1)
             begin
                   addr <= 0;
             end
          
         else 
             begin
                   addr <= addr + 1;
             end

   end

endmodule