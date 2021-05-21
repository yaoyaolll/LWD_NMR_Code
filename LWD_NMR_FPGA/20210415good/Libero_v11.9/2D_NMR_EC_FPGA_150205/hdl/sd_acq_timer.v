// sd_acq_timer.v
module sd_sacq_timer(
                     dds,
                     rst_n,
                     stateover,
                     count,
                     s_acq1
                     //s_acq2
                     );
input dds;
input rst_n;
input stateover;
input s_acq1;
//input s_acq2;

output [21:0] count;

reg [21:0] count;

//reg [21:0] count1;

wire [21:0]count1;

wire s_acq = s_acq1&stateover;

always @(posedge dds or negedge rst_n)
  begin 
       if(!rst_n | !s_acq)
           count <= 0;        
       else
           begin
           count<=count1;
           end
        
  end


sd_sacq_inc sd_sacq_inc_0(count,count1,);

endmodule