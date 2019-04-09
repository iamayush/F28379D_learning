################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F2837xD_CodeStartBranch.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_CodeStartBranch.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_GlobalVariableDefs.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_GlobalVariableDefs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Gpio_forBIOS.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_Gpio_forBIOS.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_Gpio_forBIOS.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Ipc.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_Ipc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_Ipc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_SysCtrl.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/source/F2837xD_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_SysCtrl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_usDelay.obj: C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v100/F2837xD_common/source/F2837xD_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_usDelay.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

blink_cpu02.obj: C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/blink_cpu02.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="blink_cpu02.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1453768337:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1453768337-inproc

build-1453768337-inproc: ../blink_cpu02.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/CCStudio_v8/xdctools_3_50_05_12_core/xs" --xdcpath="C:/CCStudio_v8/bios_6_70_01_03/packages;C:/CCStudio_v8/ccsv8/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.C28_float -p ti.platforms.tms320x28:TMS320F28379D -r debug -c "C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1453768337 ../blink_cpu02.cfg
configPkg/compiler.opt: build-1453768337
configPkg/: build-1453768337

f28377sCoecsl.obj: C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/f28377sCoecsl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="f28377sCoecsl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f28377sSerial.obj: C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/f28377sSerial.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/src/F28377sHeaders" --include_path="C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_headers/include" --include_path="C:/CCStudio_v8/controlSUITE/device_support/F2837xD/v140/F2837xD_common/include" --advice:performance=all --define=CPU2 --define=SYSBIOS --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="f28377sSerial.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


