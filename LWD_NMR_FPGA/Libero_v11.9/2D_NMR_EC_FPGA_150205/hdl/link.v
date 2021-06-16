// link.v

module link(
                  datain,
                  dataout
                  );
input [15:0] datain;

output [15:0] dataout;
wire [15:0] dataout;

assign dataout[15:0] = datain[15:0];


endmodule