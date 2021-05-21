// s_clk_div4.v

module s_clk_div4(
                    input rst_n,
                    input entop,
                    input s_acq_en,
                    input clk_dds,
                    output reg clkout
                    );

reg    count;

wire en;
assign en = entop & s_acq_en;

always @ (negedge rst_n or posedge clk_dds)
   begin
         if(rst_n == 1'b0)
             begin
                   count <= 0;
                   clkout <= 0;
             end

         else 
             begin
               if(en == 1'b1)
                 begin
                   if(count == 1)
                         begin
                               count <= 0;
                               clkout <= ~clkout;    //DDSÊ±ÖÓ4·ÖÆµ£¬À­Äª¶û8±¶À­Äª¶ûÆµÂÊ
                         end        
                   else
                         begin
                               count <= 1;
                         end
                 end
               else
                 begin
                     clkout <= 0;
                 end
             end 
   end

endmodule