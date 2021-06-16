// state_switch.v

module state_switch(
                   clk_sys,
                   rst_n,
                   time_up_in,
                   start,
                   state_over_in,
                   datain_scale,
                   datain_scan,
                   datain_noise,
                   datain_pluse,
                   datain_state_1ms,
                   dataout,
                   state_start,
                   state_over_n,
                   clk_en_scale,
                   clk_en_scan,
                   clk_en_noise,
                   clk_en_pluse,
                   clk_en_st1ms
                   );
input clk_sys;
input rst_n;
input time_up_in;
input[4:0] start;

input[3:0] state_over_in;


input[21:0] datain_scale;
input[19:0] datain_scan;
input[19:0] datain_noise;
input[19:0] datain_pluse;
input[19:0] datain_state_1ms;


output reg state_start;
output reg [21:0] dataout;
output reg state_over_n;
output reg clk_en_scale;
output reg clk_en_scan;
output reg clk_en_noise;
output reg clk_en_pluse;
output reg clk_en_st1ms;




always@(posedge clk_sys)
  begin
    if(!rst_n)
        begin
            state_over_n <= 1'b1;
            dataout <= 22'd0;
        end
    else
        begin
            case(start)
                5'b00001:
                    begin
                        state_over_n <= state_over_in[0];
                        dataout <= datain_scale;
                    end
                5'b00010:
                    begin
                        state_over_n <= state_over_in[1];
                        dataout <= datain_scan;
                    end
                5'b00100:
                    begin
                        state_over_n <= state_over_in[2];
                        dataout <= datain_noise;
                    end
                5'b01000:
                    begin
                        state_over_n <= state_over_in[3];
                        dataout <= datain_pluse;
                    end
                5'b10000:
                    begin
                        state_over_n <= 1'b1;
                        dataout <= datain_state_1ms;
                    end
                default:
                    begin
                        state_over_n <= 1'b1;
                        dataout <= 22'd0;               
                    end
             endcase       
        end
  end

always@(posedge clk_sys)
  begin
    if(!rst_n)
        state_start <= 1'b0;
    else
        if(start==5'd1|start==5'd2|start==5'd4|start==5'd8|start==5'd16)
            state_start <= 1'b1;
        else
            state_start <= 1'b0;
  end



always@(posedge clk_sys)
  begin
    if(!rst_n)
        begin
            clk_en_scale <= 1'b0;
            clk_en_scan  <= 1'b0;
            clk_en_noise <= 1'b0;
            clk_en_pluse <= 1'b0;
            clk_en_st1ms <= 1'b0;
        end
    else
        begin
            if(start[0])
                clk_en_scale <= time_up_in;
            else
                clk_en_scale <= 1'b0;
            if(start[1])
                clk_en_scan <= time_up_in;
            else
                clk_en_scan <= 1'b0;
            if(start[2])
                clk_en_noise <= time_up_in;
            else
                clk_en_noise <= 1'b0;
            if(start[3])
                clk_en_pluse <= time_up_in;
            else
                clk_en_pluse <= 1'b0;
            if(start[4])
                clk_en_st1ms <= time_up_in;
            else
                clk_en_st1ms <= 1'b0;
        end
  end

endmodule