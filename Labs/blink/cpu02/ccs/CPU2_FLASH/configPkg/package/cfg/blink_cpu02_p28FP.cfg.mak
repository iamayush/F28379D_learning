# invoke SourceDir generated makefile for blink_cpu02.p28FP
blink_cpu02.p28FP: .libraries,blink_cpu02.p28FP
.libraries,blink_cpu02.p28FP: package/cfg/blink_cpu02_p28FP.xdl
	$(MAKE) -f C:\Dan\F28377\AddSYSBIOStoCexamples\blink\cpu02\ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\Dan\F28377\AddSYSBIOStoCexamples\blink\cpu02\ccs/src/makefile.libs clean

