# Created by Microsemi Libero Software 11.9.6.7
# Thu Dec 16 11:26:19 2021

# (OPEN DESIGN)

open_design "NMR_TOP_1.adb"

# set default back-annotation base-name
set_defvar "BA_NAME" "NMR_TOP_ba"
set_defvar "IDE_DESIGNERVIEW_NAME" {Impl3}
set_defvar "IDE_DESIGNERVIEW_COUNT" "1"
set_defvar "IDE_DESIGNERVIEW_REV0" {Impl3}
set_defvar "IDE_DESIGNERVIEW_REVNUM0" "3"
set_defvar "IDE_DESIGNERVIEW_ROOTDIR" {E:\LWD_NMR\Code\20210907respository\LWD_NMR_FPGA\Libero_v11.9\2D_NMR_EC_FPGA_150205\designer}
set_defvar "IDE_DESIGNERVIEW_LASTREV" "3"

report -type "timing" -format "TEXT" -analysis "max" -print_summary "yes" -use_slack_threshold "no"                             -print_paths "yes" -max_paths 5 -max_expanded_paths 1                             -max_parallel_paths 1 -include_user_sets "no"                             -include_pin_to_pin "yes" -include_clock_domains "yes"                             -select_clock_domains "no" {NMR_TOP_maxdelay_timing_report.txt}
report -type "timing" -format "TEXT" -analysis "min" -print_summary "yes" -use_slack_threshold "no"                             -print_paths "yes" -max_paths 5 -max_expanded_paths 1                             -max_parallel_paths 1 -include_user_sets "no"                             -include_pin_to_pin "yes" -include_clock_domains "yes"                             -select_clock_domains "no" {NMR_TOP_mindelay_timing_report.txt}
report -type "timing_violations" -format "TEXT" -analysis "max" -use_slack_threshold "yes" -slack_threshold 0.00                               -limit_max_paths "yes" -max_paths 100 -max_expanded_paths 0                               -max_parallel_paths 1 {NMR_TOP_maxdelay_timingviolations_report.txt}
report -type "timing_violations" -format "TEXT" -analysis "min" -use_slack_threshold "yes" -slack_threshold 0.00                               -limit_max_paths "yes" -max_paths 100 -max_expanded_paths 0                               -max_parallel_paths 1 {NMR_TOP_mindelay_timingviolations_report.txt}

save_design
