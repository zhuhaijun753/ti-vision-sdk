#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: platform.mk
#
# Platforms make file - Platform/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new platform/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOC from PLATFORM
#

# TDA2XX MC
ifeq ($(PLATFORM),tda2xx-mc)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2XX EVM
ifeq ($(PLATFORM),tda2xx-evm)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2XX Interposer EVM
ifeq ($(PLATFORM),tda2xx-interposer)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# DRA7XX EVM
ifeq ($(PLATFORM),dra7xx-evm)
 SOC = dra7xx
 SOCFAMILY = tda2xx
endif

# TDA2EX EVM
ifeq ($(PLATFORM),tda2ex-evm)
 SOC = tda2ex
 SOCFAMILY = tda2xx
endif

# TDA3XX EVM
ifeq ($(PLATFORM),tda3xx-evm)
 SOC = tda3xx
 SOCFAMILY = tda3xx
endif

# ti814x EVM
ifeq ($(PLATFORM),ti814x-evm)
 SOC = ti814x
 SOCFAMILY = ti814x
endif

# TDA2XX Virtio SIM
ifeq ($(PLATFORM),tda2xx-virtio)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2XX SIM
ifeq ($(PLATFORM),tda2xx-sim)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2XX Zebu
ifeq ($(PLATFORM),tda2xx-zebu)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA3XX SIM
ifeq ($(PLATFORM),tda3xx-sim)
 SOC = tda3xx
 SOCFAMILY = tda3xx
endif

# TDA3XX Zebu
ifeq ($(PLATFORM),tda3xx-zebu)
 SOC = tda3xx
 SOCFAMILY = tda3xx
endif

# ti8149 EVM
ifeq ($(PLATFORM),ti8149-evm)
 SOC = ti8149
 SOCFAMILY = ti8149
endif

# ti811x (J5ECO) EVM
ifeq ($(PLATFORM),ti811x-evm)
 SOC = ti811x
 SOCFAMILY = ti811x
endif

# omap5430 EVM
ifeq ($(PLATFORM),omap5430-evm)
 SOC = omap5430
 SOCFAMILY = omap5430
endif

# Derive Target/ISA from CORE

# m3vpss
ifeq ($(CORE),m3vpss)
 ISA = m3
 ARCH = armv7m
endif

# m3video
ifeq ($(CORE),m3video)
 ISA = m3
 ARCH = armv7m
endif

# Added to support the core type defined by starterware to build QSPI drivers.
# This should be removed once starterware cleaned-up with proper core naming convention
# m4
ifeq ($(CORE),m4)
 ISA = m4
 ARCH = armv7m
endif

# m4vpss
ifeq ($(CORE),m4vpss)
 ISA = m4
 ARCH = armv7m
endif

# m4video
ifeq ($(CORE),m4video)
 ISA = m4
 ARCH = armv7m
endif

# ipu1_0
ifeq ($(CORE),ipu1_0)
 ISA = m4
 ARCH = armv7m
endif

# ipu1_1
ifeq ($(CORE),ipu1_1)
 ISA = m4
 ARCH = armv7m
endif

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
 ARCH = armv7a
endif

# DSP ; To do: change ISA to more meaningful value (c64x, c674x, etc)
ifeq ($(CORE),c6xdsp)
 ISA = 674
 ARCH = c67x
endif

# DSP for tda2xx
ifeq ($(CORE),c66x)
 ISA = 66
 ARCH = c66x
endif

# DSP for tda2xx
ifeq ($(CORE),c66xdsp)
 ISA = 66
 ARCH = c66x
endif

# a15_0
ifeq ($(CORE),a15_0)
 ISA = a15
 ARCH = armv7a
endif

#
# Derive XDC/ISA specific settings
#

ifeq ($(ISA),m3)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M3
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M3
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),m3video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti814x)
    ifeq ($(CORE),m3video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti8149)
    ifeq ($(CORE),m3video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti811x)
    ifeq ($(CORE),m3video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif

ifeq ($(ISA),m4)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M4
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M4
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX"
    else
      PLATFORM_XDC = "ti.platforms.evmDRA7XX"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_1"
    else
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_0"
    endif
  endif

  ifeq ($(SOCFAMILY),ti814x)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti8149)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti811x)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),omap5430)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.sdp5430"
    else
      PLATFORM_XDC = "ti.platforms.sdp5430"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif

ifeq ($(ISA),a8)
  TARGET_XDC = gnu.targets.arm.GCArmv5T
  PLATFORM_XDC = "host.platforms.arm"

  # Define the file extensions
  OBJEXT = ov5T
  LIBEXT = av5T
  EXEEXT = xv5T
  ASMEXT = sv5T
endif


#########DSP Support for TI81xx############


ifeq ($(ISA),674)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C674
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C674
  endif

  ifeq ($(SOCFAMILY),ti814x)
    ifeq ($(CORE),c6xdsp)
      PLATFORM_XDC = "ti.platforms.evmDM8148"
    else
      PLATFORM_XDC = "ti.platforms.evmDM8148"
    endif
  endif

  ifeq ($(SOCFAMILY),ti8149)
    ifeq ($(CORE),c6xdsp)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  ifeq ($(SOCFAMILY),ti811x)
    ifeq ($(CORE),c6xdsp)
      PLATFORM_XDC = "ti.platforms.evmTI814X:core0"
    else
      PLATFORM_XDC = "ti.platforms.evmTI814X:core1"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif



####################################



#########DSP Support for tda2xx############

ifeq ($(ISA),a15)
  TARGET_XDC = gnu.targets.arm.A15F
  PLATFORM_XDC = "ti.platforms.evmDRA7XX:Cortex_A15"

  ENDIAN_EXT = fg
  FORMAT_EXT =

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif

ifeq ($(ISA),66)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C66
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C66
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),c66xdsp)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX"
    else
      PLATFORM_XDC = "ti.platforms.evmDRA7XX"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),c66xdsp)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX"
    else
      PLATFORM_XDC = "ti.platforms.evmTDA3XX"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif



####################################






ifeq (sim,$(findstring sim,$(PLATFORM)))
  OMX_PLATFORM = sim
endif

ifeq ($(CORE),m3vpss)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"VPSS-M3\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),m3video)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"VIDEO-M3\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),m4vpss)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"VPSS-M4\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),m4video)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"VIDEO-M4\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),a8host)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"HOST\\\", tiler: \\\"NullTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif

ifeq ($(CORE),a15_0)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"A15-0\\\", platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif

ifeq ($(CORE),c6xdsp)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"HOST\\\", tiler: \\\"NullTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif

ifeq ($(CORE),c66xdsp)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"HOST\\\", tiler: \\\"NullTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif

export SOC
export SOCFAMILY

# Nothing beyond this point
