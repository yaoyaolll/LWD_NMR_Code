// ten_choice_one.v

module ten_choice_one( 
                      choice,
                      dataone,
                      datatwo,
                      datathree,
                      datafour,
                      datafive,
                      datasix,
                      dataseven,
                      dataeight,
                      //datanine
                      //dataten,
                      datain
                      );

input [3:0] choice;
input [11:0] datain;

output [11:0] dataone;
output [11:0] datatwo;
output [11:0] datathree;
output [11:0] datafour;
output [11:0] datafive;
output [11:0] datasix;
output [11:0] dataseven;
output [11:0] dataeight;
//output [11:0] datanine;
//output [11:0] dataten;

assign dataone   = (choice==4'b0001)? datain:12'h000;
assign datatwo   = (choice==4'b0010)? datain:12'h000;
assign datathree = (choice==4'b0011)? datain:12'h000;
assign datafour  = (choice==4'b0100)? datain:12'h000;
assign datafive  = (choice==4'b0101)? datain:12'h000;
assign datasix   = (choice==4'b0110)? datain:12'h000;
assign dataseven = (choice==4'b0111)? datain:12'h000;
assign dataeight = (choice==4'b1000)? datain:12'h000;
//assign datanine  = (choice==4'b1001)? datain:12'h000;
//assign dataten   = (choice==4'b1010)? datain:12'h000;

endmodule