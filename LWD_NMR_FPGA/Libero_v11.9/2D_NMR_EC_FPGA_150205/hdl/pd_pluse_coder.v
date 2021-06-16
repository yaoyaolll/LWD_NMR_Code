module pd_pluse_coder(
                      clk_sys,
                      dds,
                      rst_n,
                      count,
                      pd_pluse_load,
                      pd_pluse_choice,
                      pd_pluse_data,
                      pluse_start,
                      i,
                      bb_ch,
                      tetw_pluse
                      );
input clk_sys;
input dds;
input rst_n;
input [15:0] count;
input pd_pluse_load;
input [3:0]pd_pluse_choice;
input [15:0]pd_pluse_data;
input pluse_start;
input bb_ch;
input tetw_pluse;

output [5:0] i;

reg [15:0] pd_pluse_data1;
reg [15:0] pd_pluse_data2;
reg [15:0] pd_pluse_data3;

reg [2:0] i_reg;
reg [5:0] i;

always @ (posedge clk_sys)
    begin
         if(pd_pluse_load == 1'b1)
             begin
                  case(pd_pluse_choice)
                      1:
                          begin
                               pd_pluse_data1 <= pd_pluse_data;
                          end
                      2:
                          begin
                               pd_pluse_data2 <= pd_pluse_data;
                          end
                      3:
                          begin
                               pd_pluse_data3 <= pd_pluse_data;
                          end

                  endcase

                        
            end
        else
            begin
                 pd_pluse_data1 <= pd_pluse_data1;
                 pd_pluse_data2 <= pd_pluse_data2;
                 pd_pluse_data3 <= pd_pluse_data3;
            end
    end


//always @ (count or pd_pluse_data1 or pd_pluse_data2 or pd_pluse_data3 or pd_pluse_data4 or pd_pluse_data5 or pd_pluse_data6)
   always @ (count or pd_pluse_data1 or pd_pluse_data2 or pd_pluse_data3 ) 
    begin
         case (count)
             pd_pluse_data1:
                 i_reg = 3'b001;
             pd_pluse_data2:
                 i_reg = 3'b010;
             pd_pluse_data3:
                 i_reg = 3'b100;                
             default:
                 i_reg = 3'b000;
         endcase
    end

always @ (posedge dds)
    begin
         if (rst_n == 1'b0)
             i <= 6'b000000;
         else
             i <= {tetw_pluse,i_reg,bb_ch,pluse_start};
    end

endmodule