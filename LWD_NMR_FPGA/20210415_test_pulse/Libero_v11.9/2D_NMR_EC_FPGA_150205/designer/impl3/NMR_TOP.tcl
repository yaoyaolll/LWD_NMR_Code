# Created by Microsemi Libero Software 11.9.6.7
# Thu Apr 15 11:14:57 2021

# (OPEN DESIGN)

open_design "NMR_TOP_1.adb"

# set default back-annotation base-name
set_defvar "BA_NAME" "NMR_TOP_ba"
set_defvar "IDE_DESIGNERVIEW_NAME" {Impl3}
set_defvar "IDE_DESIGNERVIEW_COUNT" "1"
set_defvar "IDE_DESIGNERVIEW_REV0" {Impl3}
set_defvar "IDE_DESIGNERVIEW_REVNUM0" "3"
set_defvar "IDE_DESIGNERVIEW_ROOTDIR" {E:\LWD_NMR\Code\LWD_NMR_FPGA\20210415_test_pulse\Libero_v11.9\2D_NMR_EC_FPGA_150205\designer}
set_defvar "IDE_DESIGNERVIEW_LASTREV" "3"


layout -timing_driven
report -type "status" {NMR_TOP_place_and_route_report.txt}
report -type "globalnet" {NMR_TOP_globalnet_report.txt}
report -type "globalusage" {NMR_TOP_globalusage_report.txt}
report -type "iobank" {NMR_TOP_iobank_report.txt}
report -type "pin" -listby "name" {NMR_TOP_report_pin_byname.txt}
report -type "pin" -listby "number" {NMR_TOP_report_pin_bynumber.txt}

save_design
