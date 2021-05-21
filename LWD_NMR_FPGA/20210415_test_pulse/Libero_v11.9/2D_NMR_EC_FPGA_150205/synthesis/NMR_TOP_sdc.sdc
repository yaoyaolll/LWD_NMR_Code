# Top Level Design Parameters

# Clocks

create_clock -name {ClockManagement_0.pllclk_0.GLA} -period 9.090900 -waveform {0.000000 4.545400} ClockManagement_0/pllclk_0/Core:GLA
create_clock -name {ddsclkout} -period 25.000000 -waveform {0.000000 12.500000} ddsclkout
create_clock -name {Signal_Noise_Acq_0.signal_acq_0.signalclkctrl_0.clk_add} -period 100.000000 -waveform {0.000000 50.000000} Signal_Noise_Acq_0/signal_acq_0/signalclkctrl_0/enadd_RNIH9JE_0:Y
create_clock -name {Signal_Noise_Acq_0.signal_acq_0.s_clk_div4_0.clkout} -period 50.000000 -waveform {0.000000 25.000000} Signal_Noise_Acq_0/signal_acq_0/s_clk_div4_0/clkout:Q
create_clock -name {Signal_Noise_Acq_0.noise_acq_0.noiseclk_0.clkout} -period 50.000000 -waveform {0.000000 25.000000} Signal_Noise_Acq_0/noise_acq_0/noiseclk_0/clkout:Q
create_clock -name {Signal_Noise_Acq_0.noise_acq_0.n_rdclk_syn_0.n_rdclk} -period 50.000000 -waveform {0.000000 25.000000} Signal_Noise_Acq_0/noise_acq_0/n_rdclk_syn_0/n_rdclk:Q
create_clock -name {ClockManagement_0.clk_10k_0.clock_10khz} -period 1000.000000 -waveform {0.000000 500.000000} ClockManagement_0/clk_10k_0/clock_10khz:Q

# False Paths Between Clocks


# False Path Constraints


# Maximum Delay Constraints


# Multicycle Constraints


# Virtual Clocks
# Output Load Constraints
# Driving Cell Constraints
# Wire Loads
# set_wire_load_mode top

# Other Constraints
