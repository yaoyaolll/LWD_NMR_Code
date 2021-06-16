// dump_sustain_timer.v
module dump_sustain_timer(
                    clk_sys,
                    rst_n,
                    state_start,
                    start,
                    dump_sustain_data,
                    load,
                    clk_10k
                   );

input clk_sys;
input rst_n;
input state_start;
input [3:0]dump_sustain_data;
input load;
input clk_10k;

output start;
reg start;

reg [3:0] count;
reg [3:0] data;

wire clr_cnt_p;

assign enable=rst_n&state_start;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
            data  <= 4'd0;
         else
            if (load==1'b1)
                begin
                    data <= dump_sustain_data;
                end
            else
                begin
                    data <= data;
                end
    end

always @ (posedge clk_10k)
    begin
         if ((enable & clr_cnt_p)==1'b0)
            begin
               count <= 4'd0;
             end
         else
            begin
                count <= count + 1;                 
            end
    end

always @ (posedge clk_10k)
    begin
         if (enable == 1'b0)
             begin
                 start <= 0;
             end
         else
             if(count == data)
                 start <= 1;
             else
                 start <= 0;
    end
cmp_constant_4b cmp_constant_4b_0(count,clr_cnt_p);
endmodule
