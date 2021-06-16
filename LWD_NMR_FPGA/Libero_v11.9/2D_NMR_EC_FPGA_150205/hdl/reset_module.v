// reset_module.v
//---------------------------------------------------------------------------------
// Company: <Hust>
//
// File: <clk_add.v>
// File history:
//      <Revision 01>: <2013-05-10>: <Comments>
//      <Revision number>: <yy-dd-hh>: <Comments>
//      <Revision number>: <yy-dd-hh>: <Comments>
//
// Description: 
//
// <-------------�첽��λ��ͬ���ͷŵ�˫�����·
//  �Ƚ����ͬ����λ��λ����Դ�������⣬�ֽ�����첽��λ��
//    ѹ��̬���⣬�����˼���ǽ��첽�ź�ͬ����***/>
//
// Targeted device: <ProASIC3> <A3P1000> <FBGA144>
// Author: <hust.md>
//
//---------------------------------------------------------------------------------

module rst_n_module(
                    // input ports
                    clk,
                    rst_n,

                    // output ports
                    rst_nr2
                    );
  // input and output declarations
  input clk;
  input rst_n;

  output rst_nr2;
  
  // reg and wire declaraions for input and output
  reg rst_nr2;

  // reg and wire in the RTL logic
  reg rst_nr1;

  //**********************************************************************************
  // RTL logic
  //**********************************************************************************
  always @(posedge clk or negedge rst_n)
    begin
      if(!rst_n) 
        begin
          rst_nr1<=1'b0;
        end
      else  
      	begin
      		rst_nr1<=1;
      	end
    end

  always @(posedge clk or negedge rst_n)
    begin
      if (!rst_n) 
        begin
      	  rst_nr2<=1'b0;
      	end
      else  
      	begin
      		rst_nr2<=rst_nr1;
      	end
    end

endmodule