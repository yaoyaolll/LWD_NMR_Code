################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
user/main.obj: ../user/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --include_path="D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="E:/CCSv6_Space/multi_dimen_ECB/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="user/main.pp" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


