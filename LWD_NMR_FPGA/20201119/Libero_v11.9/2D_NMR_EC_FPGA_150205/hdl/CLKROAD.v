// clkroad.v

module clkroad(
               clkin,
               clkout,
               ctrl
               );
input clkin;
input ctrl;

output clkout;

assign clkout = (ctrl)?clkin:1'bz;

endmodule