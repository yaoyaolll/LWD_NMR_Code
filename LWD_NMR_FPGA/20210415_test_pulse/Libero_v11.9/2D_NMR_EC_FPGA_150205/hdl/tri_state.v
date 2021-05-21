// tri_state.v

module tri_state(
                 tri_ctrl,
                 zcs2,
                 xd,
                 dataout,
                 datain
                 );

inout [15:0] xd;

input [15:0] datain;
input tri_ctrl;
input zcs2;
output [15:0] dataout;

assign dataout = (!tri_ctrl)? xd:16'hzzzz;
assign xd = ((tri_ctrl==1)&&(zcs2==0))?datain:16'hzzzz;


endmodule