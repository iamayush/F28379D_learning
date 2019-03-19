# invoke SourceDir generated makefile for blink_cpu01.p28FP
blink_cpu01.p28FP: .libraries,blink_cpu01.p28FP
.libraries,blink_cpu01.p28FP: package/cfg/blink_cpu01_p28FP.xdl
	$(MAKE) -f C:\ayush2\F28379D_Guide\F2837xD\Labs\blink\cpu01\ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\ayush2\F28379D_Guide\F2837xD\Labs\blink\cpu01\ccs/src/makefile.libs clean

