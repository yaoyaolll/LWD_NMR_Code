module top_code(
                input  rst_n,
                input  clk_sys,
                input  [18:0] xa,
                input  code_en,
                input  [15:0] xdata,

                output reg scan_rst,
                output reg scan_start,
                output reg noise_rst,
                output reg noise_start,
                output reg [15:0] dds_configdata,
                output reg dds_load,
                output reg dds_choice,
                output reg cal_load,
                output reg [5:0] cal_data,
                output reg [15:0] s_acqnum,
                output reg s_load,
                output reg [1:0] change,
                output reg scale_rst,
                output reg scale_start,
                output reg scaleload,
                output reg bridge_load,
                output reg pn_change,
                output reg dumpload,
                output reg [15:0] scaledatain,
                output reg [4:0] scalechoice,
                output reg [15:0] bri_datain,
                output reg [7:0] halfdata,
                output reg [2:0] dump_cho,
                output reg [11:0] dumpdata,
                output reg [5:0] scaleddsdiv,
                output reg pluse_noise_ctrl,
                output reg pluse_scale,
                output reg pluse_str,
                output reg pluse_rst,
                output reg [15:0] plusedata,
                output reg pluseload,
                output reg pluse_lc,
                output reg [15:0] relayclose_on,
                output reg [15:0] sigtimedata,
                output reg sigrst,
                output reg scanchoice,
                output reg scanload,
                output reg [15:0] scandata,
                output reg nstateload,
                output reg nstatechoice,
                output reg [15:0] noisedata,
                output reg acqclken,
                output reg k1,
                output reg k2,
                output reg state_1ms_rst_n,
                output reg state_1ms_start,
                output reg [3:0] state_1ms_lc,
                output reg state_1ms_load,
                output reg [15:0] state_1ms_data,
                output reg n_load,
                output reg n_s_ctrl,
                output reg [9:0] n_divnum ,
                output reg [3:0] s_periodnum,
                output reg [11:0] n_acqnum,
                output reg [3:0]sd_sacq_choice,
                output reg [15:0]sd_sacq_data,
                output reg sd_sacq_load,
                output reg [3:0]  pd_pluse_choice,
                output reg pd_pluse_load,
                output reg [15:0] pd_pluse_data,
                output reg RAM_Rd_rst,
                output reg n_rd_en,
                output reg [4:0] s_addchoice,
                output reg dump_sustain,
                output reg [3:0] dump_sustain_data,
                output reg inv_turn
                );

always@(posedge clk_sys)
  begin
      if (rst_n == 1'b0)        
        begin
              scan_rst <= 1;
              noise_rst <= 1;
              scale_rst <= 1;
              pluse_rst <= 1;
              state_1ms_rst_n <= 1;

              scan_start <= 0;
              noise_start <= 0;
              scale_start <= 0;
              pluse_str <= 0;
              state_1ms_start <= 0;
              relayclose_on <= 0;
              k1 <= 0;
              k2 <= 0;
              dump_sustain <= 0;
              inv_turn <= 0;
        end
              
      else
        begin
           if(code_en == 1'b1)
                 case(xa)
                 'h0031:                       
                             state_1ms_rst_n <= 0;                     
                 'h0032:                   
                             state_1ms_rst_n <= 1;                      
                 'h0033:                   
                             state_1ms_start <= 0;
                 'h0034:   
                         begin                  
                             state_1ms_start <= 1;
                             scale_start     <= 0;
                             scan_start      <= 0;
                             noise_start     <= 0;
                             pluse_str       <= 0;
                         end                      
                 'h0035:                            
                             state_1ms_load <= 0;
                 'h0036:                            
                             state_1ms_load <= 1;
                 'h0037:                            
                             state_1ms_lc <= xdata[3:0];
                 'h0038:                            
                             state_1ms_data <= xdata;
                     
                /*-----读取数据控制------*/
                 'h0004:                            
                             n_s_ctrl <= 1;                
                 'h0005:                                                
                             n_s_ctrl <= 0;

                 /*-----复位信号------*/
                 /*
                 'h0006:                            
                            reset_out <= 0;                        
                 'h0007:                                                 
                            reset_out <= 1;                 
                  */

                 /*-----扫频复位信号------*/
                 'h0008:                                             
                            scan_rst <= 0;
                 'h0009:                            
                            scan_rst <= 1;

                 /*-----扫频启动信号------*/
                 'h000a:                           
                         begin                  
                             state_1ms_start <= 0;
                             scale_start     <= 0;
                             scan_start      <= 1;
                             noise_start     <= 0;
                             pluse_str       <= 0;
                         end  
                 'h000b:                            
                            scan_start <= 0;

                     
                 /*-----噪声复位信号------*/
                 'h000c:                           
                            noise_rst <= 0;
                 'h000d:                            
                            noise_rst <= 1;
                     
                 /*-----噪声启动信号------*/
                 'h000e:                           
                         begin                  
                             state_1ms_start <= 0;
                             scale_start     <= 0;
                             scan_start      <= 0;
                             noise_start     <= 1;
                             pluse_str       <= 0;
                         end  
                 'h000f:                            
                            noise_start <= 0;

                 /*-----dds频率字------*/
                 'h0015:                           
                            dds_configdata <= xdata;
                     
                 /*-----dds频率字装载------*/
                 'h0016:                            
                             dds_load <= 1;
                 'h0017:                                                
                             dds_load <= 0;
                     
                 /*-----dds频率字高位低位选择------*/
                 'h0018:                            
                             dds_choice <= 1;
                 'h0019:                                                 
                             dds_choice <= 0;
                     
                 /*-----cal分频字------*/
                 'h001A:                                             
                             cal_data <= xdata[5:0];
                     
                 /*-----cal分频字装载------*/
                 'h001B:                                                
                             cal_load <= 1;
                 'h001C:                            
                             cal_load <= 0;
                 'h001D:                            
                             RAM_Rd_rst <= 0;
                 'h001E:                            
                             RAM_Rd_rst <= 1;
                 'h001F:                            
                             n_rd_en <= 1;
                 'h0020:                            
                             n_rd_en <= 0;
                     
                 /*-----noise_ram寄存器装载------*/
                 'h0021:                            
                             n_load <= 1;
                 'h0022:                            
                             n_load <= 0;
                     
                /*-----noise采集数据个数------*/
                 'h0023:                                             
                             n_acqnum <= xdata[11:0]; 

                /*-----noise采集时钟分频数------*/
                 'h0024:                            
                             n_divnum <= xdata[9:0];   
                     
                /*------总采集点数-----*/
                 'h0025:                            
                             s_acqnum <= xdata[15:0];      
                     
                /*------一个周期采样点数-----*/
                 'h0026:                                             
                             s_periodnum <= xdata[3:0];
                     
                /*-----信号采集寄存器装载------*/
                 'h0027:                            
                             s_load <= 1;                     
                 'h0028:                            
                             s_load <= 0;
                 'h0029:                            
                             s_addchoice <= xdata[4:0];

                     
               /*-----继电器1闭合------*/
                 'h0040:                            
                             relayclose_on <= xdata[15:0];
     
               /*-----控制通路选择------*/
                 'h0060:                            
                             change <= xdata[1:0];
                       
               /*-----scale复位------*/
                 'h0061:                            
                             scale_rst <= 0;
                 'h0062:                            
                             scale_rst <= 1;
                       
               /*-----scale启动------*/
                 'h0063:                            
                         begin                  
                             state_1ms_start <= 0;
                             scale_start     <= 1;
                             scan_start      <= 0;
                             noise_start     <= 0;
                             pluse_str       <= 0;
                         end  
                 'h0064:                            
                             scale_start <= 0;
                       
               /*-----scale装载------*/
                 'h0065:                            
                            scaleload <= 1;
                 'h0066:                            
                            scaleload <= 0;
                       
               /*-----bridge装载------*/
                 'h0067:                            
                            bridge_load <= 1;
                 'h0068:                            
                            bridge_load <= 0;
                       
               /*-----dump装载------*/
                 'h0069:                            
                            dumpload <= 1;
                 'h006a:                            
                            dumpload <= 0;
                       
               /*-----正反相选择------*/
                 'h006b:                            
                            pn_change <= 1;
                 'h006c:                            
                            pn_change <= 0;
                       
               /*-----scale状态机数据------*/
                 'h006d:                            
                     
                            scaledatain <= xdata;
                       
               /*-----scale状态机数据选择------*/
                 'h006e:                            
                            scalechoice <= xdata[4:0];

               /*-----bridge宽度数据------*/
                 'h006f:                            
                            bri_datain <= xdata;
                       
               /*-----半激励数据------*/
                 'h0070:                            
                            halfdata <= xdata;
                       
               /*-----dump数据选择------*/
                 'h0071:                            
                            dump_cho <= xdata[2:0];
                       
               /*-----dump数据------*/
                 'h0072:                            
                            dumpdata <= xdata[11:0];
                       
               /*-----scaledds分频数据------*/
                 'h0073:                            
                            scaleddsdiv <= xdata[5:0];
                 'h0074:
                            sd_sacq_choice<= xdata[3:0];               
                 'h0075:                  
                            sd_sacq_data <= xdata[15:0];                  
                 'h0076:
                            sd_sacq_load<= 1;
                 'h0077:
                            sd_sacq_load<= 0;
                 'h00A4:
                            pd_pluse_choice<= xdata[3:0];
                 'h00A5:
                            pd_pluse_data <= xdata[15:0];
                 'h00A6:
                            pd_pluse_load<= 1;
                 'h00A7:
                            pd_pluse_load<= 0;
                     
               /*-----pluse_noise采样选择------*/
                 'h0080:                            
                            pluse_noise_ctrl <= 1;
                 'h0081:                            
                            pluse_noise_ctrl <= 0;
                     
               /*-----pluse_scale激励泄放控制选择------*/
                 'h0082:                            
                            pluse_scale <= 1;
                 'h0083:                            
                            pluse_scale <= 0;
                      
               /*-----pluse激励启动------*/
                 'h0084:                            
                         begin                  
                             state_1ms_start <= 0;
                             scale_start     <= 0;
                             scan_start      <= 0;
                             noise_start     <= 0;
                             pluse_str       <= 1;
                         end  
                 'h0085:                            
                             pluse_str <= 0;
                      
               /*-----pluse激励复位------*/
                 'h0086:                            
                             pluse_rst <= 0;
                 'h0087:                                                 
                             pluse_rst <= 1;
                       
               /*-----pluse激励数据装载------*/
                 'h0088:                                                 
                             pluseload <= 1;                 
                 'h0089:                                                 
                             pluseload <= 0;
                       
               /*-----pluse激励数据装载选择------*/
                 'h008a:                            
                             pluse_lc <= 1;
                 'h008b:                            
                             pluse_lc <= 0;
                       
               /*-----pluse激励数据------*/
                 'h008c:                            
                            plusedata <= xdata;
                     
               /*-----定时器数据------*/
                 'h0090:                            
                            sigtimedata <= xdata;
                      
               /*-----定时器启动------*/
                 'h0091:                            
                             sigrst <= 1;
                 'h0092:                            
                             sigrst <= 0;

               /*-----扫频状态机数据选择------*/
                 'h0093:                           
                            scanchoice <= 1;
                 'h0094:                            
                            scanchoice <= 0;

               /*-----扫频状态机数据转载------*/
                 'h0095:                           
                            scanload <= 1;
                 'h0096:                            
                            scanload <= 0;
                     
                 /*-----扫频状态机数据------*/
                 'h0097:                           
                            scandata <= xdata;

                 /*-----noise状态机数据选择------*/
                 'h0098:                           
                            nstatechoice <= 1;
                 'h0099:                            
                            nstatechoice <= 0;

                 /*-----noise状态机数据转载------*/
                 'h009A:                           
                            nstateload <= 1;
                 'h009B:                            
                            nstateload <= 0;
                     
                 /*-----噪声状态机数据------*/
                 'h009C:                           
                            noisedata <= xdata;

                 /*-----noise状态机数据转载------*/
                 'h009D:                           
                            acqclken <= 1;
                 'h009E:                            
                            acqclken <= 0;
                     
                 /*-----k1------*/
                 'h00A0:                           
                            k1 <= 1;
                 'h00A1:                            
                            k1 <= 0;
                     
                 /*-----k2------*/
                 'h00A2:                           
                            k2 <= 1;
                 'h00A3:                            
                            k2 <= 0;
                            
                 /*-----dump_sustain,主泄放通道持续打开------*/
                 'h00A8:                           
                            dump_sustain <= 1;
                 'h00A9:                            
                            dump_sustain <= 0;   
                 'h00AA:                            
                            dump_sustain_data <= xdata[3:0];  
                 'h00AB:
                            inv_turn <= 1;
                 'h00AC:
                            inv_turn <= 0;                                                                                                  
              endcase
        end
  end


endmodule


        