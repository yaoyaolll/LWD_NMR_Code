// sd_acq_coder.v
module sd_sacq_coder(
                     clk_sys,
                     dds,
                     rst_n,
                     count,
                     sd_sacq_load,
                     sd_sacq_choice,
                     sd_sacq_data,                
                     state_start,
                     i,
                     bb_ch,
                     s_acq180,
                     long_opentime
                     );
input clk_sys;
input dds;
input rst_n;
input [21:0] count;
input sd_sacq_load;
input [3:0]sd_sacq_choice;
input [15:0]sd_sacq_data;
input state_start;
input bb_ch;
input s_acq180;
input long_opentime;

output reg[10:0] i;

reg [15:0] sd_sacq_data1;
reg [15:0] sd_sacq_data2;
reg [15:0] sd_sacq_data3;
reg [21:0] sd_sacq_data4;
reg [21:0] sd_sacq_data5;

/*新增延时参数  2014-09-22*/
reg [21:0] sd_sacq_data6;
reg [21:0] sd_sacq_data7;
/*=======================*/

reg [6:0] i_reg;



always @ (posedge clk_sys)
    begin
         if(sd_sacq_load == 1'b1)
             begin
                  case(sd_sacq_choice)
                      1:
                          begin
                               sd_sacq_data1 <= sd_sacq_data;
                          end
                      2:
                          begin
                               sd_sacq_data2 <= sd_sacq_data;
                          end
                      3:
                          begin
                               sd_sacq_data3 <= sd_sacq_data;
                          end
                     
                      4:
                          begin
                               sd_sacq_data4[15:0] <= sd_sacq_data;
                          end
                       
                      5:
                          begin
                               sd_sacq_data4[21:16] <= sd_sacq_data[5:0];
                          end
                      
                      6:
                          begin
                               sd_sacq_data5[15:0] <= sd_sacq_data;
                          end
                      
                      7:
                          begin
                               sd_sacq_data5[21:16] <= sd_sacq_data[5:0];
                          end
                      8:
                          begin
                               sd_sacq_data6[15:0] <= sd_sacq_data;    //新增参数data6
                          end
                      
                      9:
                          begin
                               sd_sacq_data6[21:16] <= sd_sacq_data[5:0];  //新增参数data6
                          end 

                      10:
                          begin
                               sd_sacq_data7[15:0] <= sd_sacq_data;       //新增参数data7
                          end
                      
                      11:
                          begin
                               sd_sacq_data7[21:16] <= sd_sacq_data[5:0]; //新增参数data7
                          end
                     
                  endcase

                        
            end
        else
            begin
                 sd_sacq_data1 <= sd_sacq_data1;
                 sd_sacq_data2 <= sd_sacq_data2;
                 sd_sacq_data3 <= sd_sacq_data3;               
                 sd_sacq_data4 <= sd_sacq_data4;            
                 sd_sacq_data5 <= sd_sacq_data5;
                 sd_sacq_data6 <= sd_sacq_data6;
                 sd_sacq_data7 <= sd_sacq_data7;
            end
    end


always @ (*)
    begin
         case (count)
             sd_sacq_data1:
                 i_reg = 7'b0000001;
             sd_sacq_data2:
                 i_reg = 7'b0000010;
             sd_sacq_data3:
                 i_reg = 7'b0000100;
             sd_sacq_data4:
                 i_reg = 7'b0001000;
             sd_sacq_data5:
                 i_reg = 7'b0010000;
             sd_sacq_data6:
                 i_reg = 7'b0100000;
             sd_sacq_data7:
                 i_reg = 7'b1000000;
             default:
                 i_reg = 7'b0000000;
         endcase
    end

always @ (posedge dds)
    begin
         if (rst_n == 1'b0)
             i <= 11'b00000000;
         else
             i <= {i_reg,long_opentime,s_acq180,bb_ch,state_start};
    end

endmodule