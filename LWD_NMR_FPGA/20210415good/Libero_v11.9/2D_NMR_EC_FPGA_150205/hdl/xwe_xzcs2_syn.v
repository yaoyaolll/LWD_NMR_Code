// xwe_xzcs2_syn.v
module xwe_xzcs2_syn(
                   rst_n,
                   clk_sys,
                   xwe,
                   xzcs2,
                   code_en
                  );

input rst_n;
input clk_sys;
input xwe;
input xzcs2;

output code_en;

reg code_en;

reg xwe_reg1;
reg xwe_reg2;
//reg xwe_reg3;

wire code_en_wire;

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             {xwe_reg1,xwe_reg2} <= 2'b0;
         else
             begin
                  xwe_reg1 <= xwe;
                  xwe_reg2 <= xwe_reg1;
                  //xwe_reg3 <= xwe_reg2;
             end
    end

//assign xwe_wire   = xwe_reg1 & (~xwe_reg2);//检测上降沿,为高一个clk_sys
//assign xzcs2_wire = ~xzcs2;//取反，方便后续使用

assign code_en_wire =  (~xzcs2) & xwe_reg1 & (~xwe_reg2);

always @ (posedge clk_sys)
    begin
         if (rst_n == 1'b0)
             code_en <= 1'b0;
         else
             code_en <= code_en_wire;
    end

endmodule