// Q_SW.v

module Q_SW(
            ctrl,
            Q1Q8_in,
            Q1Q8_out,
            Q2Q7_in,
            Q2Q7_out,
            Q3Q6_in,
            Q3Q6_out,
            Q4Q5_in,
            Q4Q5_out 
            );
input  ctrl;

input  Q1Q8_in;
output Q1Q8_out;

input  Q2Q7_in;
output Q2Q7_out;

input  Q3Q6_in;
output Q3Q6_out;

input  Q4Q5_in;
output Q4Q5_out;

assign Q1Q8_out  = (ctrl)? Q1Q8_in  : 0;
assign Q2Q7_out  = (ctrl)? Q2Q7_in  : 0;
assign Q3Q6_out  = (ctrl)? Q3Q6_in  : 0;
assign Q4Q5_out  = (ctrl)? Q4Q5_in  : 0;

endmodule