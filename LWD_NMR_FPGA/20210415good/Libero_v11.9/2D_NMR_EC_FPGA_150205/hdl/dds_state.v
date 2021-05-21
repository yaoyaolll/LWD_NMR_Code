// dds_state.v
module dds_state (
                  clk_sys,
                  rst_n,
                  dds_load,
                  dds_choice,
                  i,
                  dds_para,
                  reset,
                  w_clk,
                  fq_ud,
                  data,
                  state_over
                 );

input clk_sys;
input rst_n;
input dds_load;
input dds_choice;
input [3:0] i;
input [15:0] dds_para;

output reset;
output w_clk;
output fq_ud;
output data;
output state_over;

reg reset;
reg w_clk;
reg fq_ud;
reg data;
reg state_over;

reg reset_reg;
reg w_clk_reg;
reg fq_ud_reg;

reg [7:0] cs;
reg [7:0] ns;

reg [40:0] para;
reg [40:0] para_reg;//测量体中要重复装载para，故用para_reg保存最初的值

parameter [7:0] PHASE_PARA = 8'h00;

parameter [7:0] IDLE       = 8'b00000000,
                RST1       = 8'b00000001,
                RST2       = 8'b00000010,
                MODE_SEL1  = 8'b00000100,
                MODE_SEL2  = 8'b00001000,
                PARA_LOAD1 = 8'b00010000,
                PARA_LOAD2 = 8'b00100000,
                UPDATE     = 8'b01000000,
                OVER       = 8'b10000000;

wire en;

assign en = rst_n & i[0];

always @ (posedge clk_sys)
    begin
         if (dds_load == 1'b1)
             begin
                  if (dds_choice == 1'b0)
                      begin
                           para[16:0]      <= {dds_para[15:0],1'b0};
                           para_reg[16:0]  <= {dds_para[15:0],1'b0};
                      end
                  else
                      begin
                           para[40:17]     <= {PHASE_PARA,dds_para[15:0]};
                           para_reg[40:17] <= {PHASE_PARA,dds_para[15:0]};
                      end
             end
         else
             begin//写频率字之前选择串行方式时，w_clk_reg为高一次，故此处para最低位增加一位0
                  if (i[0] == 1'b1)
                      begin
                           if (w_clk_reg == 1'b1)
                               para <= para >> 1;
                           else
                               para <= para;
                      end
                  else
                      para <= para_reg;
             end
    end

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             cs <= IDLE;
         else
             cs <= ns;
    end

always @ (cs or i)
    begin
         case (cs)
             IDLE:
                 begin
                      if (i[0] == 1'b1)
                          ns = RST1;
                      else
                          ns = IDLE;
                 end
             RST1:
                 begin
                      if (i[1] == 1'b1)
                          ns = RST2;
                      else
                          ns = RST1;
                 end
             RST2:
                 begin
                      if (i[2] == 1'b1)
                          ns = MODE_SEL1;
                      else
                          ns = RST2;
                 end
             MODE_SEL1:
                 ns = MODE_SEL2;
             MODE_SEL2:
                 ns = PARA_LOAD1;
             PARA_LOAD1:
                 ns = PARA_LOAD2;
             PARA_LOAD2:
                 begin
                      if (i[3] == 1'b1)
                          ns = UPDATE;
                      else
                          ns = PARA_LOAD1;
                 end
             UPDATE:
                 ns = OVER;
             OVER:
                 ns = OVER;
             default:
                 ns = IDLE; 
         endcase         
    end

always @ (posedge clk_sys)
    begin
         if (en == 1'b0)
             begin
                  {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0;
                  state_over <= 1'b1;
             end
         else
             begin
                  case (ns)
                      IDLE:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0;
                      RST1:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b1000;
                      RST2:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0000;
                      MODE_SEL1:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0100;
                      MODE_SEL2:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0010;
                      PARA_LOAD1:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= {3'b000,para[0]};
                      PARA_LOAD2:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= {3'b010,para[0]};
                      UPDATE:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0010;
                      OVER:
                          begin
                               {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0000;
                               state_over <= 1'b0;
                          end
                      default:
                          {reset_reg,w_clk_reg,fq_ud_reg,data} <= 4'b0;
                  endcase
             end
    end

always @ (posedge clk_sys)
    begin//控制信号晚于数据一个时钟，保证数据稳定时再装载
         if (en == 1'b0)
             {reset,w_clk,fq_ud} <= 3'b0;
         else
             {reset,w_clk,fq_ud} <= {reset_reg,w_clk_reg,fq_ud_reg};
    end

endmodule