################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./source/CasingDetectTop.obj" \
"./source/DE_CPMG_Top.obj" \
"./source/DSP281x_CpuTimers.obj" \
"./source/DSP281x_DefaultIsr.obj" \
"./source/DSP281x_GlobalVariableDefs.obj" \
"./source/DSP281x_PieCtrl.obj" \
"./source/DSP281x_PieVect.obj" \
"./source/DSP281x_SysCtrl.obj" \
"./source/MainInitial.obj" \
"./source/MyFPGAFunctions.obj" \
"./source/MyFunctions.obj" \
"./source/MyVariables.obj" \
"./source/PPDIFModeTop.obj" \
"./source/PPModeTop.obj" \
"./source/PPOFTWModeTop.obj" \
"./source/PPShortModeTop.obj" \
"./source/PPT1ModeTop.obj" \
"./source/PulseTop.obj" \
"./source/SCIA_interrupt.obj" \
"./source/ScaleHoleTop.obj" \
"./source/ScanTop.obj" \
"./source/TableHandle.obj" \
"../lib/IQmath.lib" \
"../lib/rts2800_ml.lib" \
"../cmd/F2812_EzDSP_RAM_lnk_new.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include lib/subdir_vars.mk
-include cmd/subdir_vars.mk
-include subdir_rules.mk
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
LWD_NMR_ECB.out \

EXE_OUTPUTS__QUOTED += \
"LWD_NMR_ECB.out" \

BIN_OUTPUTS += \
LWD_NMR_ECB.hex \

BIN_OUTPUTS__QUOTED += \
"LWD_NMR_ECB.hex" \


# All Target
all: LWD_NMR_ECB.out

# Tool invocations
LWD_NMR_ECB.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"LWD_NMR_ECB.map" --warn_sections -i"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/include" --reread_libs --display_error_number --diag_suppress=16002 --diag_wrap=off --xml_link_info="LWD_NMR_ECB_linkInfo.xml" --rom_model -o "LWD_NMR_ECB.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

LWD_NMR_ECB.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/CCSv6/ccsv6/tools/compiler/c2000_6.2.7/bin/hex2000"  -o "LWD_NMR_ECB.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "source\CasingDetectTop.pp" "source\DE_CPMG_Top.pp" "source\DSP281x_CpuTimers.pp" "source\DSP281x_DefaultIsr.pp" "source\DSP281x_GlobalVariableDefs.pp" "source\DSP281x_PieCtrl.pp" "source\DSP281x_PieVect.pp" "source\DSP281x_SysCtrl.pp" "source\MainInitial.pp" "source\MyFPGAFunctions.pp" "source\MyFunctions.pp" "source\MyVariables.pp" "source\PPDIFModeTop.pp" "source\PPModeTop.pp" "source\PPOFTWModeTop.pp" "source\PPShortModeTop.pp" "source\PPT1ModeTop.pp" "source\PulseTop.pp" "source\SCIA_interrupt.pp" "source\ScaleHoleTop.pp" "source\ScanTop.pp" "source\TableHandle.pp" 
	-$(RM) "main.obj" "source\CasingDetectTop.obj" "source\DE_CPMG_Top.obj" "source\DSP281x_CpuTimers.obj" "source\DSP281x_DefaultIsr.obj" "source\DSP281x_GlobalVariableDefs.obj" "source\DSP281x_PieCtrl.obj" "source\DSP281x_PieVect.obj" "source\DSP281x_SysCtrl.obj" "source\MainInitial.obj" "source\MyFPGAFunctions.obj" "source\MyFunctions.obj" "source\MyVariables.obj" "source\PPDIFModeTop.obj" "source\PPModeTop.obj" "source\PPOFTWModeTop.obj" "source\PPShortModeTop.obj" "source\PPT1ModeTop.obj" "source\PulseTop.obj" "source\SCIA_interrupt.obj" "source\ScaleHoleTop.obj" "source\ScanTop.obj" "source\TableHandle.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

