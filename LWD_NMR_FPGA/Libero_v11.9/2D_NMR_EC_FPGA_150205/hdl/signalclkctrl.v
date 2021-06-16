// signalclkctrl.v

module signalclkctrl(
                    rst_n,
                    clk_sys,
                    load,
                    acqnum,
                    stripnum,
                    periodnum,
                    entop,
                    //enadd,
                    //enclk,
                    clk_add,
                    clk_acq,
                    clkin
                    //clkin1,
                    //clkin2
                    );

input rst_n;
input clk_sys;
input load;
input [15:0] acqnum;
input [11:0] stripnum;
input [3:0] periodnum;
//input clkin1;
//input clkin2;
input clkin;

output entop;
//output enadd;
//output enclk;
output clk_add;
output clk_acq;

reg entop;
reg enadd;
reg enclk;
//reg clk_add;
//reg clk_acq;
reg [15:0] count;
reg [15:0] data;
reg [3:0] perioddata;
reg [11:0] stripdata;


//wire clkin=clkin|clkin2;

always @ (posedge clk_sys)
  begin
       if (load == 1'b1)
        begin
            data <= acqnum;
            perioddata <= periodnum;
            stripdata <= stripnum;
        end
       else
        begin
            data <= data;
            perioddata <= perioddata;
            stripdata <= stripdata;
        end
  end

always @ (negedge rst_n or posedge clkin)
  begin
        if (rst_n == 1'b0)
           begin
                 count <= 1;
                 entop <= 1;
                 enadd <= 0;
                 enclk <= 0;
           end
        
        else
           begin
                 if(count == stripnum+1)
                   begin
                         enclk <= 1;
                         count <= count + 1;
                   end
                 else if(count == stripnum+perioddata+1)
                   begin
                         enadd <= 1;
                         count <= count + 1;
                   end

                 else if(count >= stripnum+data)
                   begin
                         entop <= 0;
                   end

                 else 
                   begin
                         count <= count + 1;
                   end
           end
  end


assign clk_add = enadd & clkin;
assign clk_acq = enclk & clkin;
/*
always @ (posedge reset or posedge clkin)
    begin
         if (reset)
             clk_add <= 1'b0;
         else
             begin
                  if (enadd == 1'b1)
                      clk_add <= clkin;
                  else
                      clk_add <= 1'b0;
             end
    end

always @ (posedge reset or posedge clkin)
    begin
         if (reset)
             clk_acq <= 1'b0;
         else
             begin
                  if (enclk == 1'b1)
                      clk_acq <= clkin;
                  else
                      clk_acq <= 1'b0;
             end
    end
*/
endmodule