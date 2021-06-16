# Synopsys, Inc. constraint file
# C:/Users/dell/Desktop/WorkFolder/2D_NMR_EC_FPGA_150131/constraint/NMR_TOP_syn.sdc
# Written on Thu Feb 05 17:06:43 2015
# by Synplify Pro, E-2010.09A-1 Scope Editor

#
# Collections
#

#
# Clocks
#
define_clock  -comment {Actual Freq = 100MHz}   {n:ClockManagement_0.pllclk_0.GLA} -name {n:ClockManagement_0.pllclk_0.GLA}  -freq 110 -clockgroup 100MHz
define_clock  -comment {Actual Max Freq <= 32MHz}   {ddsclkout} -name {ddsclkout}  -freq 40 -clockgroup 32MHz
define_clock  -comment {Actual Freq = clk_dds/4 <= 8MHz}   {n:Signal_Noise_Acq_0.signal_acq_0.signalclkctrl_0.clk_add} -name {n:Signal_Noise_Acq_0.signal_acq_0.signalclkctrl_0.clk_add}  -freq 10 -clockgroup 8MHz
define_clock  -comment {Actual Freq = clk_dds/4 <= 8MHz}   {n:Signal_Noise_Acq_0.signal_acq_0.s_clk_div4_0.clkout} -name {n:Signal_Noise_Acq_0.signal_acq_0.s_clk_div4_0.clkout}  -freq 20 -clockgroup 8MHz
define_clock  -comment {Actual Freq = 50MHz}   {n:Signal_Noise_Acq_0.noise_acq_0.noiseclk_0.clkout} -name {n:Signal_Noise_Acq_0.noise_acq_0.noiseclk_0.clkout}  -freq 20 -clockgroup 50MHz
define_clock  -comment {Actual Freq generate from DSP rd}   {n:Signal_Noise_Acq_0.noise_acq_0.n_rdclk_syn_0.n_rdclk} -name {n:Signal_Noise_Acq_0.noise_acq_0.n_rdclk_syn_0.n_rdclk}  -freq 20 -clockgroup DSP
define_clock -disable  -comment {Actual Freq = 5kHz}   {n:ClockManagement_0.clk_5k_0.clk_5k} -name {n:ClockManagement_0.clk_5k_0.clk_5k}  -period 2000 -clockgroup 1MHz
define_clock  -comment {Actual Freq = 10kHz}   {n:ClockManagement_0.clk_10k_0.clock_10khz} -name {n:ClockManagement_0.clk_10k_0.clock_10khz}  -freq 1 -clockgroup 1MHz

#
# Clock to Clock
#

#
# Inputs/Outputs
#
define_input_delay -disable      -default -improve 0.00 -route 0.00
define_output_delay -disable     -default -improve 0.00 -route 0.00
define_input_delay -disable      {zcs2} -improve 0.00 -route 0.00
define_input_delay -disable      {xwe} -improve 0.00 -route 0.00
define_output_delay -disable     {ddsfqud} -improve 0.00 -route 0.00
define_output_delay -disable     {ddsreset} -improve 0.00 -route 0.00
define_output_delay -disable     {ddswclk} -improve 0.00 -route 0.00
define_output_delay -disable     {cal_out} -improve 0.00 -route 0.00
define_output_delay -disable     {ddsdata} -improve 0.00 -route 0.00
define_input_delay -disable      {OCX40MHz} -improve 0.00 -route 0.00
define_input_delay -disable      {ddsclkout} -improve 0.00 -route 0.00
define_output_delay -disable     {interupt} -improve 0.00 -route 0.00
define_output_delay -disable     {rt_sw} -improve 0.00 -route 0.00
define_output_delay -disable     {soft_dump} -improve 0.00 -route 0.00
define_output_delay -disable     {sw_acq1} -improve 0.00 -route 0.00
define_output_delay -disable     {sw_acq2} -improve 0.00 -route 0.00
define_output_delay -disable     {dumpon} -improve 0.00 -route 0.00
define_output_delay -disable     {dumpoff} -improve 0.00 -route 0.00
define_output_delay -disable     {Q1Q8} -improve 0.00 -route 0.00
define_output_delay -disable     {Q3Q6} -improve 0.00 -route 0.00
define_output_delay -disable     {Q4Q5} -improve 0.00 -route 0.00
define_output_delay -disable     {Q2Q7} -improve 0.00 -route 0.00
define_output_delay -disable     {calcuinter} -improve 0.00 -route 0.00
define_input_delay -disable      {tri_ctrl} -improve 0.00 -route 0.00
define_output_delay -disable     {sigtimeup} -improve 0.00 -route 0.00
define_output_delay -disable     {k1} -improve 0.00 -route 0.00
define_output_delay -disable     {k2} -improve 0.00 -route 0.00
define_input_delay -disable      {gpio} -improve 0.00 -route 0.00
define_output_delay -disable     {pulse_start} -improve 0.00 -route 0.00
define_output_delay -disable     {pd_pulse_en} -improve 0.00 -route 0.00
define_input_delay -disable      {XRD} -improve 0.00 -route 0.00
define_output_delay -disable     {Acq_clk} -improve 0.00 -route 0.00
define_output_delay -disable     {sd_acq_en} -improve 0.00 -route 0.00
define_output_delay -disable     {s_acq180} -improve 0.00 -route 0.00
define_input_delay -disable      {xa[18:0]} -improve 0.00 -route 0.00
define_input_delay -disable      {xd[15:0]} -improve 0.00 -route 0.00
define_output_delay -disable     {xd[15:0]} -improve 0.00 -route 0.00
define_output_delay -disable     {relayclose_on[15:0]} -improve 0.00 -route 0.00
define_input_delay -disable      {ADC[11:0]} -improve 0.00 -route 0.00

#
# Registers
#
define_reg_output_delay          {scalestate_0.CS[11]} -improve 0.1

#
# Delay Paths
#

#
# Attributes
#
define_global_attribute  {syn_global_buffer} {9}
define_attribute {top_code_0.noise_start} {syn_allow_retiming} {1}
define_attribute {top_code_0.scan_start} {syn_allow_retiming} {1}
define_attribute {top_code_0.state_1ms_start} {syn_allow_retiming} {1}
define_attribute {top_code_0.pluse_str} {syn_allow_retiming} {1}
define_attribute {scalestate_0.timecount[21:0]} {syn_allow_retiming} {1}
define_attribute {top_code_0.scale_start} {syn_allow_retiming} {1}
define_attribute {i:GPMI_0.xwe_xzcs2_syn_0.code_en} {syn_allow_retiming} {1}

#
# I/O Standards
#
define_io_standard -disable      -default_input -delay_type input
define_io_standard -disable      -default_output -delay_type output
define_io_standard -disable      -default_bidir -delay_type bidir
define_io_standard -disable      {zcs2} -delay_type input
define_io_standard -disable      {xwe} -delay_type input
define_io_standard -disable      {ddsfqud} -delay_type output
define_io_standard -disable      {ddsreset} -delay_type output
define_io_standard -disable      {ddswclk} -delay_type output
define_io_standard -disable      {cal_out} -delay_type output
define_io_standard -disable      {ddsdata} -delay_type output
define_io_standard -disable      {OCX40MHz} -delay_type input
define_io_standard -disable      {ddsclkout} -delay_type input
define_io_standard -disable      {interupt} -delay_type output
define_io_standard -disable      {rt_sw} -delay_type output
define_io_standard -disable      {soft_dump} -delay_type output
define_io_standard -disable      {sw_acq1} -delay_type output
define_io_standard -disable      {sw_acq2} -delay_type output
define_io_standard -disable      {dumpon} -delay_type output
define_io_standard -disable      {dumpoff} -delay_type output
define_io_standard -disable      {Q1Q8} -delay_type output
define_io_standard -disable      {Q3Q6} -delay_type output
define_io_standard -disable      {Q4Q5} -delay_type output
define_io_standard -disable      {Q2Q7} -delay_type output
define_io_standard -disable      {calcuinter} -delay_type output
define_io_standard -disable      {tri_ctrl} -delay_type input
define_io_standard -disable      {sigtimeup} -delay_type output
define_io_standard -disable      {k1} -delay_type output
define_io_standard -disable      {k2} -delay_type output
define_io_standard -disable      {gpio} -delay_type input
define_io_standard -disable      {pulse_start} -delay_type output
define_io_standard -disable      {pd_pulse_en} -delay_type output
define_io_standard -disable      {XRD} -delay_type input
define_io_standard -disable      {Acq_clk} -delay_type output
define_io_standard -disable      {sd_acq_en} -delay_type output
define_io_standard -disable      {s_acq180} -delay_type output
define_io_standard -disable      {xa[18:0]} -delay_type input
define_io_standard -disable      {xd[15:0]} -delay_type bidir
define_io_standard -disable      {relayclose_on[15:0]} -delay_type output
define_io_standard -disable      {ADC[11:0]} -delay_type input

#
# Compile Points
#

#
# Other
#
