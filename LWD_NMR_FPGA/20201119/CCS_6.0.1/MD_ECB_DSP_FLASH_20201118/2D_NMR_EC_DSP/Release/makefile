################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/DE_CPMG_Top.obj" \
"./source/DFT1T2DModeTop.obj" \
"./source/DSP281x_CodeStartBranch.obj" \
"./source/DSP281x_CpuTimers.obj" \
"./source/DSP281x_DefaultIsr.obj" \
"./source/DSP281x_GlobalVariableDefs.obj" \
"./source/DSP281x_PieCtrl.obj" \
"./source/DSP281x_PieVect.obj" \
"./source/DSP281x_SectionCopy.obj" \
"./source/DSP281x_SysCtrl.obj" \
"./source/DSP281x_usDelay.obj" \
"./source/FBW2FModeTop.obj" \
"./source/Gas6FreqTop.obj" \
"./source/Gas6_2ModeTop.obj" \
"./source/HRT1T22FModeTop.obj" \
"./source/MainInitial.obj" \
"./source/Mcbsp_interrupt.obj" \
"./source/Mcbspinitial.obj" \
"./source/MyFPGAFunctions.obj" \
"./source/MyFunctions.obj" \
"./source/MyVariables.obj" \
"./source/Oil3FreqTop.obj" \
"./source/P3D6FModeTop.obj" \
"./source/PP3FreqTop.obj" \
"./source/PP6FreqTop.obj" \
"./source/PPHOIL6FModeTop.obj" \
"./source/PPHOIL6F_2ModeTop.obj" \
"./source/PPLOIL6FModeTop.obj" \
"./source/PulseTop.obj" \
"./source/ScaleHoleTop.obj" \
"./source/ScanTop.obj" \
"./source/T1T2DModeTop.obj" \
"./source/T1T2ModeTop.obj" \
"./source/T2DModeTop.obj" \
"./source/TableHandle.obj" \
"./source/main.obj" \
"../lib/IQmath.lib" \
"../lib/rts2800_ml.lib" \
"../cmd/F2812_EzDSP_FLASH_lnk_new.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include lib/subdir_vars.mk
-include cmd/subdir_vars.mk
-include source/subdir_rules.mk
-include lib/subdir_rules.mk
-include cmd/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
2D_NMR_EC_DSP.out \

EXE_OUTPUTS__QUOTED += \
"2D_NMR_EC_DSP.out" \

BIN_OUTPUTS += \
2D_NMR_EC_DSP.hex \

BIN_OUTPUTS__QUOTED += \
"2D_NMR_EC_DSP.hex" \


# All Target
all: 2D_NMR_EC_DSP.out

# Tool invocations
2D_NMR_EC_DSP.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --diag_warning=225 --display_error_number --diag_wrap=off -z -m"2D_NMR_EC_DSP.map" --warn_sections -i"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/include" --reread_libs --display_error_number --diag_suppress=16002 --diag_wrap=off --xml_link_info="2D_NMR_EC_DSP_linkInfo.xml" --rom_model -o "2D_NMR_EC_DSP.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

2D_NMR_EC_DSP.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/bin/hex2000"  -o "2D_NMR_EC_DSP.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "source\DE_CPMG_Top.pp" "source\DFT1T2DModeTop.pp" "source\DSP281x_CpuTimers.pp" "source\DSP281x_DefaultIsr.pp" "source\DSP281x_GlobalVariableDefs.pp" "source\DSP281x_PieCtrl.pp" "source\DSP281x_PieVect.pp" "source\DSP281x_SysCtrl.pp" "source\FBW2FModeTop.pp" "source\Gas6FreqTop.pp" "source\Gas6_2ModeTop.pp" "source\HRT1T22FModeTop.pp" "source\MainInitial.pp" "source\Mcbsp_interrupt.pp" "source\Mcbspinitial.pp" "source\MyFPGAFunctions.pp" "source\MyFunctions.pp" "source\MyVariables.pp" "source\Oil3FreqTop.pp" "source\P3D6FModeTop.pp" "source\PP3FreqTop.pp" "source\PP6FreqTop.pp" "source\PPHOIL6FModeTop.pp" "source\PPHOIL6F_2ModeTop.pp" "source\PPLOIL6FModeTop.pp" "source\PulseTop.pp" "source\ScaleHoleTop.pp" "source\ScanTop.pp" "source\T1T2DModeTop.pp" "source\T1T2ModeTop.pp" "source\T2DModeTop.pp" "source\TableHandle.pp" "source\main.pp" 
	-$(RM) "source\DE_CPMG_Top.obj" "source\DFT1T2DModeTop.obj" "source\DSP281x_CodeStartBranch.obj" "source\DSP281x_CpuTimers.obj" "source\DSP281x_DefaultIsr.obj" "source\DSP281x_GlobalVariableDefs.obj" "source\DSP281x_PieCtrl.obj" "source\DSP281x_PieVect.obj" "source\DSP281x_SectionCopy.obj" "source\DSP281x_SysCtrl.obj" "source\DSP281x_usDelay.obj" "source\FBW2FModeTop.obj" "source\Gas6FreqTop.obj" "source\Gas6_2ModeTop.obj" "source\HRT1T22FModeTop.obj" "source\MainInitial.obj" "source\Mcbsp_interrupt.obj" "source\Mcbspinitial.obj" "source\MyFPGAFunctions.obj" "source\MyFunctions.obj" "source\MyVariables.obj" "source\Oil3FreqTop.obj" "source\P3D6FModeTop.obj" "source\PP3FreqTop.obj" "source\PP6FreqTop.obj" "source\PPHOIL6FModeTop.obj" "source\PPHOIL6F_2ModeTop.obj" "source\PPLOIL6FModeTop.obj" "source\PulseTop.obj" "source\ScaleHoleTop.obj" "source\ScanTop.obj" "source\T1T2DModeTop.obj" "source\T1T2ModeTop.obj" "source\T2DModeTop.obj" "source\TableHandle.obj" "source\main.obj" 
	-$(RM) "source\DSP281x_CodeStartBranch.pp" "source\DSP281x_SectionCopy.pp" "source\DSP281x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

