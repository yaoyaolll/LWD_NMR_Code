// ppheavy_on_timer.v
//---------------------------------------------------------------------------------
// Company: <Hust>
//
// File: <clk_add.v>
// File history:
//      <Revision 01>: <2013-05-20>: <Comments>
//      <Revision number>: <yy-dd-hh>: <Comments>
//      <Revision number>: <yy-dd-hh>: <Comments>
//
// Description: 
//
// < ppheavy 模式 _长计时>
//
// Targeted device: <ProASIC3> <A3P1000> <FBGA144>
// Author: <hust.md>
//
//---------------------------------------------------------------------------------
module ppheavy_on_timer_md(
                        // input ports
                        clk_sys,
                        rst_state,
                        rst_n,
                        clk_10k,
                        state_start,
                        //work,
                        
                        // output ports
                        start
                        );

	// input and output delcarations
	input clk_sys;
	input rst_state;
	input rst_n;
	input clk_10k;
	input state_start;
	
	output start;
	
	// reg and wire declaraions for input and output                
	reg start;
	
  // reg and wire in the RTL logic
  reg [5:0] cnt;
  
  reg clk_10k_reg1;
  reg clk_10k_reg2;
  
  wire clk_10k_en;
  
  //**********************************************************************************
  // RTL logic
  //**********************************************************************************
  
  always @(posedge clk_sys or negedge rst_n)
  	begin
  		if (!rst_n)
  			begin
  				clk_10k_reg1 <= 1'b0;
  				clk_10k_reg2 <= 1'b0;
  			end
  		else
  			begin
  				clk_10k_reg1 <= clk_10k;
  				clk_10k_reg2 <= clk_10k_reg1;
  			end
  	end  	        
  	
  assign clk_10k_en = (clk_10k_reg1 & (~clk_10k_reg2));
  
  always @(posedge clk_sys)
  	begin
  		if (clk_10k_en == 1'b1)
  			begin
  				if (rst_state == 1'b0)
  					cnt <= 6'b0;
  				else
  					begin
  						if (state_start == 1'b1)
  							cnt <= cnt + 1'b1;
  						else
  							cnt <= 6'b0;
  					end
  			end
  		else
  			begin
  				cnt <= cnt;
  			end
  	end
  
//always @(posedge clk_sys)
//	begin
//		if (rst_state == 1'b0)
//			begin
//				cnt <= 6'b0;
//			end
//	  else 
//	    begin
//	    	if(clk_10k_en == 1'b1)
//  				begin
//  					cnt <= cnt + 1'b1;
//  				end
//  		  else
//          begin
//            if (state_start == 1'b1) 
//	  		  	  begin
//	  		  		  cnt <= cnt;
//	  		  	  end
//            else
//              begin
//                cnt <= 6'b0;
//              end
//          end
//  		end
//	end   
  	
  always @(posedge clk_sys)
  	begin
  		if (clk_10k_en == 1'b1)
  			begin
          if (rst_state == 1'b0)
  					start <= 1'b0;
  				else
  					begin
  						if (cnt == 6'd20 || cnt == 6'd35)
  							start <= 1'b1;
  						else
  							start <= 1'b0;
  					end  				
  			end
  		else
  			begin
  				start <= 1'b0;
  			end
  	end
  	
//always @(posedge clk_sys)
//	begin
//		if (rst_state == 1'b0)
//			begin
//				start <= 1'b0;
//			end
//		else if (clk_10k_en == 1'b1)
//			begin
//				if (cnt == 6'd20 || cnt == 6'd35)
//					begin
//						start <= 1'b1;
//					end
//				else
//					begin
//						start <= 1'b0;
//					end
//			end
//	end
	                        

endmodule


//module ppheavy_on_timer(
//                    //clk_sys,
//                    rst_n,
//                    state_start,
//                    start,
//                    clk_10k
//                   );
//
////input clk_sys;
//input rst_n;
//input state_start;
//
//input clk_10k;
//
//output start;
//reg start;
//
//reg [5:0] count;
//
//
////always @ (posedge clk_10k or  negedge rst_n)
//always @ (posedge clk_10k)
//    begin
//         if (rst_n == 1'b0)
//             count <= 6'b0;
//         else
//             begin
//                  if (state_start == 1'b1)
//                      count <= count + 1;
//                 
//                  else
//                      count <= 0;
//             end
//    end
//always @ (posedge clk_10k)
//    begin
//         if (rst_n == 1'b0)
//             start <= 0;
//         else
//             begin
//                  if (count==6'd20||count==6'd35)
//                      start <= 1;
//                 
//                  else
//                      start <= 0;
//             end
//    end
//endmodule
//
