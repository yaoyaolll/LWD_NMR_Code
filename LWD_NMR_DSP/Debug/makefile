################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./config.asm/DSP281x_CodeStartBranch.obj" \
"./config.asm/DSP281x_usDelay.obj" \
"./source/CasingDetectTop.obj" \
"./source/CublicSplineAlogrithm.obj" \
"./source/DE_CPMG_Top.obj" \
"./source/DSP281x_CpuTimers.obj" \
"./source/DSP281x_DefaultIsr.obj" \
"./source/DSP281x_GlobalVariableDefs.obj" \
"./source/DSP281x_PieCtrl.obj" \
"./source/DSP281x_PieVect.obj" \
"./source/DSP281x_SysCtrl.obj" \
"./source/GaussFitAlogrithm.obj" \
"./source/MainInitial.obj" \
"./source/MyFPGAFunctions.obj" \
"./source/MyFunctions.obj" \
"./source/MyVariables.obj" \
"./source/PAPSTop.obj" \
"./source/PPDIFModeTop.obj" \
"./source/PPModeTop.obj" \
"./source/PPOFTWModeTop.obj" \
"./source/PPShortModeTop.obj" \
"./source/PPT1ModeTop.obj" \
"./source/PulseTop.obj" \
"./source/RelayCtrl.obj" \
"./source/SCIA_interrupt.obj" \
"./source/ScaleHoleTop.obj" \
"./source/ScanTop.obj" \
"./source/SingleOrderDeal.obj" \
"./source/StateCtrl.obj" \
"./source/TableHandle.obj" \
"./source/TuningModeTop.obj" \
"../cmd/F2812_EzDSP_FLASH_lnk_new.cmd" \
"../lib/IQmath.lib" \
"../lib/rts2800_ml.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include cmd/subdir_vars.mk
-include config.asm/subdir_vars.mk
-include lib/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include cmd/subdir_rules.mk
-include config.asm/subdir_rules.mk
-include lib/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
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
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"LWD_NMR_ECB.map" --warn_sections -i"D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/lib" -i"D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/include" --reread_libs --display_error_number --diag_suppress=16002 --diag_wrap=off --xml_link_info="LWD_NMR_ECB_linkInfo.xml" --rom_model -o "LWD_NMR_ECB.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

LWD_NMR_ECB.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"D:/CCSv10/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/hex2000" --diag_wrap=off -o "LWD_NMR_ECB.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "config.asm\DSP281x_CodeStartBranch.obj" "config.asm\DSP281x_usDelay.obj" "source\CasingDetectTop.obj" "source\CublicSplineAlogrithm.obj" "source\DE_CPMG_Top.obj" "source\DSP281x_CpuTimers.obj" "source\DSP281x_DefaultIsr.obj" "source\DSP281x_GlobalVariableDefs.obj" "source\DSP281x_PieCtrl.obj" "source\DSP281x_PieVect.obj" "source\DSP281x_SysCtrl.obj" "source\GaussFitAlogrithm.obj" "source\MainInitial.obj" "source\MyFPGAFunctions.obj" "source\MyFunctions.obj" "source\MyVariables.obj" "source\PAPSTop.obj" "source\PPDIFModeTop.obj" "source\PPModeTop.obj" "source\PPOFTWModeTop.obj" "source\PPShortModeTop.obj" "source\PPT1ModeTop.obj" "source\PulseTop.obj" "source\RelayCtrl.obj" "source\SCIA_interrupt.obj" "source\ScaleHoleTop.obj" "source\ScanTop.obj" "source\SingleOrderDeal.obj" "source\StateCtrl.obj" "source\TableHandle.obj" "source\TuningModeTop.obj" 
	-$(RM) "main.d" "source\CasingDetectTop.d" "source\CublicSplineAlogrithm.d" "source\DE_CPMG_Top.d" "source\DSP281x_CpuTimers.d" "source\DSP281x_DefaultIsr.d" "source\DSP281x_GlobalVariableDefs.d" "source\DSP281x_PieCtrl.d" "source\DSP281x_PieVect.d" "source\DSP281x_SysCtrl.d" "source\GaussFitAlogrithm.d" "source\MainInitial.d" "source\MyFPGAFunctions.d" "source\MyFunctions.d" "source\MyVariables.d" "source\PAPSTop.d" "source\PPDIFModeTop.d" "source\PPModeTop.d" "source\PPOFTWModeTop.d" "source\PPShortModeTop.d" "source\PPT1ModeTop.d" "source\PulseTop.d" "source\RelayCtrl.d" "source\SCIA_interrupt.d" "source\ScaleHoleTop.d" "source\ScanTop.d" "source\SingleOrderDeal.d" "source\StateCtrl.d" "source\TableHandle.d" "source\TuningModeTop.d" 
	-$(RM) "config.asm\DSP281x_CodeStartBranch.d" "config.asm\DSP281x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

