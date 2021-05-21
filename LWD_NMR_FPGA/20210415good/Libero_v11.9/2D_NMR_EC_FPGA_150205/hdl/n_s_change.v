// n_s_change.v

module n_s_change(
                  n_s_ctrl,
                  adcdata,
                  n_adc,
                  s_adc,                  
                  dataout,
                  s_data,
                  n_data,
                  n_clk,
                  s_clk,
                  acq_clk
                  );

input n_s_ctrl;

input [11:0] adcdata;
output [11:0] n_adc;
output [11:0] s_adc;

input [15:0] s_data;
input [15:0] n_data;
output [15:0] dataout;

input n_clk;
input s_clk;
output acq_clk;

assign n_adc = (n_s_ctrl)? adcdata:12'hzzz;
assign s_adc = (!n_s_ctrl)? adcdata:12'hzzz;

assign dataout = (n_s_ctrl)? n_data:s_data;
//assign dataout = (!n_s_ctrl)? s_data:16'hzzzz;

assign acq_clk = (n_s_ctrl)? n_clk:s_clk;
//assign acq_clk = (!n_s_ctrl)? s_clk:1'bz;

endmodule