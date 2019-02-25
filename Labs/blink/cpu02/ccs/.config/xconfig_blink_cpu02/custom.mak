## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,28FP linker.cmd package/cfg/blink_cpu02_p28FP.o28FP

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/blink_cpu02_p28FP.xdl
	$(SED) 's"^\"\(package/cfg/blink_cpu02_p28FPcfg.cmd\)\"$""\"C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/.config/xconfig_blink_cpu02/\1\""' package/cfg/blink_cpu02_p28FP.xdl > $@
	-$(SETDATE) -r:max package/cfg/blink_cpu02_p28FP.h compiler.opt compiler.opt.defs
