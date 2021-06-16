// posi_nege.v

module posi_nege(
                 forward,
                 forwardin,
                 back,
                 backin,
                 pn_change
                 );
input pn_change;

output forward;
input forwardin;

output back;
input backin;

assign forward = (pn_change)? forwardin:backin;
assign back    = (pn_change)? backin:forwardin;


endmodule