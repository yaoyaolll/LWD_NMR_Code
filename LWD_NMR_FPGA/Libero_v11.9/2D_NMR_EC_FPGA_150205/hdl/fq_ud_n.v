// fq_ud_n.v
module fq_ud_n(clk_100M,
                fq_ud_out,
                rst_n,
                fq_ud
                );

 input rst_n;
 input clk_100M;
 input fq_ud;

 output fq_ud_out;

 reg fq_ud_out;
 reg fq_ud_reg;


always @(negedge clk_100M)
    begin
        if(rst_n==0)
            fq_ud_reg<=0;
        else if(fq_ud==1)
            fq_ud_reg<=1;
        else
            fq_ud_reg<=0;
    end

always @(negedge clk_100M)
     begin
        if(rst_n==0)
            fq_ud_out<=0;
       else
            fq_ud_out<=fq_ud_reg;
    end

endmodule