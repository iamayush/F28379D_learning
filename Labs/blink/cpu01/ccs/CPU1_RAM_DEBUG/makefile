################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/CCStudio_v8/ccsv8/tools/compiler/c2000_6.2.11

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./F2837xD_CodeStartBranch.obj" \
"./F2837xD_DefaultISR.obj" \
"./F2837xD_GlobalVariableDefsforBIOS.obj" \
"./F2837xD_Gpio_forBIOS.obj" \
"./F2837xD_Ipc.obj" \
"./F2837xD_Ipc_Driver_Util.obj" \
"./F2837xD_SysCtrl.obj" \
"./F2837xD_usDelay.obj" \
"./blink_cpu01.obj" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32.lib \
-l2837x_RAM_lnk_cpu1.cmd \
-lF2837x_Headers_nonBIOS_cpu1.cmd \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
blink_cpu01.out \

EXE_OUTPUTS__QUOTED += \
"blink_cpu01.out" \


# All Target
all: blink_cpu01.out

# Tool invocations
blink_cpu01.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/CCStudio_v8/ccsv8/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --define=CPU1 --diag_warning=225 --display_error_number -z -m"blink_cpu01.map" --warn_sections -i"C:/CCStudio_v8/ccsv8/tools/compiler/c2000_6.2.11/lib" -i"C:/CCStudio_v8/ccsv8/tools/compiler/c2000_6.2.11/include" -i"C:/ayush2/F28379D_Guide/F2837xD/F2837xD_common/cmd" -i"C:/ayush2/F28379D_Guide/F2837xD/F2837xD_headers/cmd" --reread_libs --display_error_number --xml_link_info="blink_cpu01_linkInfo.xml" --rom_model -o "blink_cpu01.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_CMDS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_OPTS__QUOTED)
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "F2837xD_CodeStartBranch.obj" "F2837xD_DefaultISR.obj" "F2837xD_GlobalVariableDefsforBIOS.obj" "F2837xD_Gpio_forBIOS.obj" "F2837xD_Ipc.obj" "F2837xD_Ipc_Driver_Util.obj" "F2837xD_SysCtrl.obj" "F2837xD_usDelay.obj" "blink_cpu01.obj" 
	-$(RM) "F2837xD_DefaultISR.d" "F2837xD_GlobalVariableDefsforBIOS.d" "F2837xD_Gpio_forBIOS.d" "F2837xD_Ipc.d" "F2837xD_Ipc_Driver_Util.d" "F2837xD_SysCtrl.d" "blink_cpu01.d" 
	-$(RM) "F2837xD_CodeStartBranch.d" "F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

