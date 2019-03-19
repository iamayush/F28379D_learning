# invoke SourceDir generated makefile for blink_cpu02.p28FP
blink_cpu02.p28FP: .libraries,blink_cpu02.p28FP
.libraries,blink_cpu02.p28FP: package/cfg/blink_cpu02_p28FP.xdl
	$(MAKE) -f C:\ayush2\F28379D_Guide\F2837xD\Labs\blink\cpu02\ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\ayush2\F28379D_Guide\F2837xD\Labs\blink\cpu02\ccs/src/makefile.libs clean

