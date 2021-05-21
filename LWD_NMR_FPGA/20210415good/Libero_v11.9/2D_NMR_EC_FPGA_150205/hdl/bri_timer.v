// bri_timer.v
module bri_timer(
                 clk_dds,
                 clk_4f_en,
                 rst_n,
                 state_start,
                 //clk_2f,
                 timer_stop,
                 count
                );
input clk_dds;
input clk_4f_en;//ʱ��Ϊ4������Ƶ��
input rst_n;
input state_start;
input timer_stop;

//output clk_2f;
output [7:0] count;

//reg clk_2f; 
reg [7:0] count;
/*
always @ (negedge rst_n or posedge clk_4f)
    begin
         if (rst_n == 1'b0)
             clk_2f <= 1'b1;
         else
             clk_2f <= ~clk_2f;
    end
*/
wire clken;

assign clken = clk_4f_en & state_start & (~timer_stop);

always @ (negedge rst_n or posedge clk_dds)
    begin
         if (rst_n == 1'b0)
             count <= 8'b0;
         else
             begin
                  if (clken == 1'b1)

                      count <= count + 1;
                  else
                      count <= count;
//pluse_acq����ʱ�����������count���㣬�ʼƵ���ʱֹͣ�����㣬�������ȶ���״̬��Ϊѭ��״̬����half�ź�һֱ�������ùʲ�������
             end
    end

endmodule