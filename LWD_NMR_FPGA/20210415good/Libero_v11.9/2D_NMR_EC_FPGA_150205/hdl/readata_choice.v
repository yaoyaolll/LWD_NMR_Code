// rdata_choice.v

module rdata_choice(
                    dataone,
                    datatwo,
                    datathree,
                    datafour,
                    datafive,
                    datasix,
                    dataseven,
                    dataeight,
                    //datanine,
                    //dataten,
                    dataout,
                    choice
                    );

input [19:0] dataone;
input [19:0] datatwo;
input [19:0] datathree;
input [19:0] datafour;
input [19:0] datafive;
input [19:0] datasix;
input [19:0] dataseven;
input [19:0] dataeight;
//input [19:0] datanine;
//input [19:0] dataten;
input [4:0]  choice;
output [15:0] dataout;

assign dataout  = (choice==5'b00001)? dataone[15:0]:16'hzzzz;
assign dataout  = (choice==5'b00010)? {12'h000,dataone[19:16]}:16'hzzzz;

assign dataout  = (choice==5'b00011)? datatwo[15:0]:16'hzzzz;
assign dataout  = (choice==5'b00100)? {12'h000,datatwo[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b00101)? datathree[15:0]:16'hzzzz;
assign dataout  = (choice==5'b00110)? {12'h000,datathree[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b00111)? datafour[15:0]:16'hzzzz;
assign dataout  = (choice==5'b01000)? {12'h000,datafour[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b01001)? datafive[15:0]:16'hzzzz;
assign dataout  = (choice==5'b01010)? {12'h000,datafive[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b01011)? datasix[15:0]:16'hzzzz;
assign dataout  = (choice==5'b01100)? {12'h000,datasix[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b01101)? dataseven[15:0]:16'hzzzz;
assign dataout  = (choice==5'b01110)? {12'h000,dataseven[19:16]}:16'hzzzz;


assign dataout  = (choice==5'b01111)? dataeight[15:0]:16'hzzzz;
assign dataout  = (choice==5'b10000)? {12'h000,dataeight[19:16]}:16'hzzzz;


//assign dataout  = (choice==5'b10001)? datanine[15:0]:16'hzzzz;
//assign dataout  = (choice==5'b10010)? {12'h000,datanine[19:16]}:16'hzzzz;


//assign dataout  = (choice==5'b10011)? dataten[15:0]:16'hzzzz;
//assign dataout  = (choice==5'b10100)? {12'h000,dataten[19:16]}:16'hzzzz;



endmodule