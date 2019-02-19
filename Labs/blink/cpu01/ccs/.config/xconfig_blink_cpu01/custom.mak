## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,28L linker.cmd package/cfg/blink_cpu01_p28L.o28L

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/blink_cpu01_p28L.xdl
	$(SED) 's"^\"\(package/cfg/blink_cpu01_p28Lcfg.cmd\)\"$""\"C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu01/ccs/.config/xconfig_blink_cpu01/\1\""' package/cfg/blink_cpu01_p28L.xdl > $@
	-$(SETDATE) -r:max package/cfg/blink_cpu01_p28L.h compiler.opt compiler.opt.defs
