################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/CCStudio_v5.5/ccsv5/tools/compiler/c2000_6.2.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./blink_cpu02.obj" \
"./F2837xD_usDelay.obj" \
"./F2837xD_SysCtrl.obj" \
"./F2837xD_PieVect.obj" \
"./F2837xD_PieCtrl.obj" \
"./F2837xD_Ipc.obj" \
"./F2837xD_Gpio.obj" \
"./F2837xD_GlobalVariableDefs.obj" \
"./F2837xD_DefaultISR.obj" \
"./F2837xD_CodeStartBranch.obj" \
-l"rts2800_fpu32.lib" \
-l"2837x_RAM_lnk_cpu2.cmd" \
-l"F2837x_Headers_nonBIOS_cpu2.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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

# All Target
all: blink_cpu02.out

# Tool invocations
blink_cpu02.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/CCStudio_v5.5/ccsv5/tools/compiler/c2000_6.2.4/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --define=CPU2 --diag_warning=225 --display_error_number -z -m"blink_cpu02.map" --warn_sections -i"C:/CCStudio_v5.5/ccsv5/tools/compiler/c2000_6.2.4/lib" -i"C:/CCStudio_v5.5/ccsv5/tools/compiler/c2000_6.2.4/include" -i"C:/Dan/F28377/F2837xD_common/cmd" -i"C:/Dan/F28377/F2837xD_headers/cmd" --reread_libs --display_error_number --xml_link_info="blink_cpu02_linkInfo.xml" --rom_model -o "blink_cpu02.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QUOTED) "blink_cpu02.out"
	-$(RM) "F2837xD_DefaultISR.pp" "F2837xD_GlobalVariableDefs.pp" "F2837xD_Gpio.pp" "F2837xD_Ipc.pp" "F2837xD_PieCtrl.pp" "F2837xD_PieVect.pp" "F2837xD_SysCtrl.pp" "blink_cpu02.pp" 
	-$(RM) "F2837xD_CodeStartBranch.obj" "F2837xD_DefaultISR.obj" "F2837xD_GlobalVariableDefs.obj" "F2837xD_Gpio.obj" "F2837xD_Ipc.obj" "F2837xD_PieCtrl.obj" "F2837xD_PieVect.obj" "F2837xD_SysCtrl.obj" "F2837xD_usDelay.obj" "blink_cpu02.obj" 
	-$(RM) "F2837xD_CodeStartBranch.pp" "F2837xD_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

