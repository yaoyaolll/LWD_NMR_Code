// pd_pluse_timer.v
module pd_pluse_timer(
                      dds,
                      rst_n,
                      stateover,
                      count,
                      pluse_start                         
                     );
input dds;
input rst_n;
input stateover;
input pluse_start;

output [15:0] count;

reg [15:0] count;

wire [15:0]count1;

wire start_over=pluse_start&stateover;
/*
always @(posedge dds or negedge rst_n)
  begin 
       if(rst_n==0)
           count <= 0;        
       else if(start_over==1)
           count<=count+1;
       else
           count<=0;
  end
*/

always @(posedge dds or negedge rst_n)
  begin 
       if(!rst_n | !start_over)
           count <= 0;        
       else
           begin
           count<=count1;
           end
        
  end


pd_pluse_inc pd_pluse_inc_0(count,count1,);

endmodule
