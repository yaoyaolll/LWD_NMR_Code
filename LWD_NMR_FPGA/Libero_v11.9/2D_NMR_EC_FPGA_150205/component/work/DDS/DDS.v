`timescale 1 ns/100 ps
// Version: 9.1 9.1.0.18


module DDS(
       dds_load,
       dds_choice,
       clk_sys,
       rst_n,
       state_start,
       reset,
       fq_ud,
       w_clk,
       data,
       dds_para
    );
input  dds_load;
input  dds_choice;
input  clk_sys;
input  rst_n;
input  state_start;
output reset;
output fq_ud;
output w_clk;
output data;
input  [15:0] dds_para;

    wire \dds_coder_0_i_[3] , \dds_coder_0_i_[2] , \dds_coder_0_i_[1] , 
        \dds_coder_0_i_[0] , dds_state_0_state_over, 
        \dds_timer_0_count_[7] , \dds_timer_0_count_[6] , 
        \dds_timer_0_count_[5] , \dds_timer_0_count_[4] , 
        \dds_timer_0_count_[3] , \dds_timer_0_count_[2] , 
        \dds_timer_0_count_[1] , \dds_timer_0_count_[0] , GND_net, 
        VCC_net;
    
    VCC VCC (.Y(VCC_net));
    GND GND (.Y(GND_net));
    dds_timer dds_timer_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .state_over(dds_state_0_state_over), 
        .count({\dds_timer_0_count_[7] , \dds_timer_0_count_[6] , 
        \dds_timer_0_count_[5] , \dds_timer_0_count_[4] , 
        \dds_timer_0_count_[3] , \dds_timer_0_count_[2] , 
        \dds_timer_0_count_[1] , \dds_timer_0_count_[0] }));
    dds_state dds_state_0 (.clk_sys(clk_sys), .rst_n(rst_n), .dds_load(
        dds_load), .dds_choice(dds_choice), .reset(reset), .w_clk(
        w_clk), .fq_ud(fq_ud), .data(data), .state_over(
        dds_state_0_state_over), .i({\dds_coder_0_i_[3] , 
        \dds_coder_0_i_[2] , \dds_coder_0_i_[1] , \dds_coder_0_i_[0] })
        , .dds_para({dds_para[15], dds_para[14], dds_para[13], 
        dds_para[12], dds_para[11], dds_para[10], dds_para[9], 
        dds_para[8], dds_para[7], dds_para[6], dds_para[5], 
        dds_para[4], dds_para[3], dds_para[2], dds_para[1], 
        dds_para[0]}));
    dds_coder dds_coder_0 (.clk_sys(clk_sys), .rst_n(rst_n), 
        .state_start(state_start), .count({\dds_timer_0_count_[7] , 
        \dds_timer_0_count_[6] , \dds_timer_0_count_[5] , 
        \dds_timer_0_count_[4] , \dds_timer_0_count_[3] , 
        \dds_timer_0_count_[2] , \dds_timer_0_count_[1] , 
        \dds_timer_0_count_[0] }), .i({\dds_coder_0_i_[3] , 
        \dds_coder_0_i_[2] , \dds_coder_0_i_[1] , \dds_coder_0_i_[0] })
        );
    
endmodule
