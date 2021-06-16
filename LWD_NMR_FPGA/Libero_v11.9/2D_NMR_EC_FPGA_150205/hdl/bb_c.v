// bb_c.v


module bb_c(
                   change,
                   forward,
                   forward1,
                   forward2,
                   back,
                   back1,
                   back2,
                   df,
                   df1,
                   df2
                   );

input change;

output forward;
output back;
output df;

input forward1;
input forward2;
input back1;
input back2;
input df1;
input df2;

assign forward = (!change)? forward1:forward2;
assign back    = (!change)? back1:back2;
assign df      = (!change)? df1:df2;

endmodule