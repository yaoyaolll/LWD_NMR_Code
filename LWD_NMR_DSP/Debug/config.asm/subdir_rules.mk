################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
config.asm/%.obj: ../config.asm/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/include" --include_path="E:/LWD_NMR/Code/20210907respository/LWD_NMR_DSP/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="config.asm/$(basename $(<F)).d_raw" --obj_directory="config.asm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


