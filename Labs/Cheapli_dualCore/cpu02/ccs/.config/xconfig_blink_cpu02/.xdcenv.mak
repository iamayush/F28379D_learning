#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/CCStudio_v8/bios_6_70_01_03/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/.config
override XDCROOT = C:/CCStudio_v8/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/CCStudio_v8/bios_6_70_01_03/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/ayush2/F28379D_Guide/F2837xD/Labs/blink/cpu02/ccs/.config;C:/CCStudio_v8/xdctools_3_32_00_06_core/packages;..
HOSTOS = Windows
endif
