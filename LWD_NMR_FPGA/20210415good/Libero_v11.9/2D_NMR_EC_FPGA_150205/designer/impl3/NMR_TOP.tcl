# Created by Microsemi Libero Software 11.9.6.7
# Tue May 18 11:23:11 2021

# (OPEN DESIGN)

open_design "NMR_TOP_1.adb"

# set default back-annotation base-name
set_defvar "BA_NAME" "NMR_TOP_ba"
set_defvar "IDE_DESIGNERVIEW_NAME" {Impl3}
set_defvar "IDE_DESIGNERVIEW_COUNT" "1"
set_defvar "IDE_DESIGNERVIEW_REV0" {Impl3}
set_defvar "IDE_DESIGNERVIEW_REVNUM0" "3"
set_defvar "IDE_DESIGNERVIEW_ROOTDIR" {E:\LWD_NMR\Code\LWD_NMR_FPGA\20210415good\Libero_v11.9\2D_NMR_EC_FPGA_150205\designer}
set_defvar "IDE_DESIGNERVIEW_LASTREV" "3"


# import of input files
import_source  \
-format "edif" -edif_flavor "GENERIC" -netlist_naming "VERILOG" {../../synthesis/NMR_TOP.edn} \
-format "pdc"  {..\..\component\work\NMR_TOP\NMR_TOP.pdc} \
-format "sdc"  {..\..\synthesis\NMR_TOP_sdc.sdc} \
-format "pdc"  {..\..\constraint\NMR_TOP_PIN_LOCKED.pdc} -merge_physical "yes" -merge_timing "no"
compile
report -type "status" {NMR_TOP_compile_report.txt}
report -type "pin" -listby "name" {NMR_TOP_report_pin_byname.txt}
report -type "pin" -listby "number" {NMR_TOP_report_pin_bynumber.txt}

save_design
