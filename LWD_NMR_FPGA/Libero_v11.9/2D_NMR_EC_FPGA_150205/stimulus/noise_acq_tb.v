// noise_acq_tb.v

`timescale 1ns/1ps

module testbench;

reg  noise_load;
reg  n_reset;
reg  RAM_RDaddr_rst;
reg  RAM_WT_EN;
reg  RAM_RD_EN;
reg  XRD;
reg  clk_sys;
reg  [11:0] n_acqnum;
reg  [11:0] n_ADC;
reg  [9:0] n_divnum;
wire [15:0] RAM_data;
wire Noise_acq_clk;


initial
    begin
        noise_load      = 1'b0;
        n_reset         = 1'b0;
        RAM_RDaddr_rst  = 1'b0;
        RAM_WT_EN       = 1'b0;
        RAM_RD_EN       = 1'b0;
        XRD             = 1'b0;
        clk_sys         = 1'b0;
        n_acqnum = 12'd0;
        n_ADC    = 12'd0;
        n_divnum  = 10'd0;
    end

always #5 clk_sys <= !clk_sys;

initial
    begin

        #50
        n_reset         = 1'b1;

        #50
        n_acqnum        = 12'd300;
        n_divnum        = 10'd330;
        noise_load      = 1'b1;

        #50
        noise_load      = 1'b0;

        #50
        RAM_WT_EN       = 1'b1;
        
        #100000
        RAM_RDaddr_rst  = 1'b1;

        #50
        RAM_RD_EN       = 1'b1;
        read;
    end

always @ (posedge Noise_acq_clk)
   n_ADC <= {$random % 4095}
  


noise_acq noise_acq_0
(
.noise_load(noise_load),
.n_reset(n_reset),
.RAM_RDaddr_rst(RAM_RDaddr_rst),
.RAM_WT_EN(RAM_WT_EN),
.RAM_RD_EN(RAM_RD_EN),
.XRD(XRD),
.clk_sys(clk_sys),
.n_acqnum(n_acqnum),
.n_ADC(n_ADC),
.n_divnum(n_divnum),
.RAM_data(RAM_data),
.Noise_acq_clk(Noise_acq_clk)
);

endmodule

task read;

    always #50 XRD <= !XRD;

endtask 