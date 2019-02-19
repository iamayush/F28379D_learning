#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/CCStudio_v5.5/bios_6_37_01_24/packages;C:/CCStudio_v5.5/ccsv5/ccs_base;C:/Dan/F28377/AddSYSBIOStoCexamples/blink/cpu02/ccs/.config
override XDCROOT = C:/CCStudio_v5.5/xdctools_3_25_05_94
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/CCStudio_v5.5/bios_6_37_01_24/packages;C:/CCStudio_v5.5/ccsv5/ccs_base;C:/Dan/F28377/AddSYSBIOStoCexamples/blink/cpu02/ccs/.config;C:/CCStudio_v5.5/xdctools_3_25_05_94/packages;..
HOSTOS = Windows
endif
