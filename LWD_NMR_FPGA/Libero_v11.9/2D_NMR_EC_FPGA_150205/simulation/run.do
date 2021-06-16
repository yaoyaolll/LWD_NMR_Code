quietly set ACTELLIBNAME ProASIC3
quietly set PROJECT_DIR "E:/LWD_NMR/Code/LWD_NMR_FPGA/20210415good/Libero_v11.9/2D_NMR_EC_FPGA_150205"

if {[file exists presynth/_info]} {
   echo "INFO: Simulation library presynth already exists"
} else {
   file delete -force presynth 
   vlib presynth
}
vmap presynth presynth
vmap proasic3 "D:/Libero_Soc11.9/Designer/lib/modelsim/precompiled/vlog/proasic3"

vlog -vlog01compat -work presynth "${PROJECT_DIR}/hdl/syn_md.v"
vlog -vlog01compat -work presynth "${PROJECT_DIR}/hdl/syn_md_combine.v"
vlog -vlog01compat -work presynth "${PROJECT_DIR}/hdl/syn_md_edge_detect.v"
vlog -vlog01compat -work presynth "${PROJECT_DIR}/component/work/syn_md_module/syn_md_module.v"
vlog "+incdir+${PROJECT_DIR}/stimulus" -vlog01compat -work presynth "${PROJECT_DIR}/stimulus/syn_md_module_tb.v"

vsim -L proasic3 -L presynth  -t 1ps presynth.syn_md_module_tb
add wave /syn_md_module_tb/*
run 0
