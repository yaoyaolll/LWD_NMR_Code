// doff_change.v

module doff_change(
                   change,
                   dumpoff,
                   dumpoffin0,
                   dumpoffin1,
                   dumpoffin2
                   );

input [1:0] change;

input dumpoffin0;
input dumpoffin1;
input dumpoffin2;

output dumpoff;

assign dumpoff = (change==0)? dumpoffin0:1'bz;
assign dumpoff = (change==1)? dumpoffin1:1'bz;
assign dumpoff = (change==2)? dumpoffin2:1'bz;

endmodule