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

# tda2xx EVM
ifeq ($(PLATFORM),tda2xx)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# tda2xx MC
ifeq ($(PLATFORM),tda2xx-mc)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# DRA7XX EVM
ifeq ($(PLATFORM),dra7xx)
 SOC = dra7xx
 SOCFAMILY = tda2xx
endif

# TDA3XX EVM
ifeq ($(PLATFORM),tda3xx)
 SOC = tda3xx
 SOCFAMILY = tda3xx
endif

# ti814x EVM
ifeq ($(PLATFORM),ti814x)
 SOC = ti814x
 SOCFAMILY = ti814x
endif

# TDA2XX EVM
ifeq ($(PLATFORM),tda2xx-evm)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2EX EVM
ifeq ($(PLATFORM),tda2ex)
 SOC = tda2ex
 SOCFAMILY = tda2xx
endif

# DRA7XX EVM
ifeq ($(PLATFORM),dra7xx-evm)
 SOC = dra7xx
 SOCFAMILY = tda2xx
endif

# TDA2XX Virtio SIM
ifeq ($(PLATFORM),tda2xx-virtio)
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2EX EVM
ifeq ($(PLATFORM),tda2ex-evm)
 SOC = tda2ex
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

# TDA3XX EVM
ifeq ($(PLATFORM),tda3xx-evm)
 SOC = tda3xx
 SOCFAMILY = tda3xx
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

# ti814x EVM
ifeq ($(PLATFORM),ti814x-evm)
 SOC = ti814x
 SOCFAMILY = ti814x
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

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
 ARCH = armv7a
endif

# DSP ; To do: change ISA to more meaningful value (c64x, c674x, etc)
ifeq ($(CORE),c674x)
 ISA = 674
 ARCH = c67x
endif

# DSP for tda2xx
ifeq ($(CORE),c66x)
 ISA = 66
 ARCH = c66x
endif

# a15host
ifeq ($(CORE),a15host)
 ISA = a15
 ARCH = armv7a
endif

# a15_0
ifeq ($(CORE),a15_0)
 ISA = a15
 ARCH = armv7a
endif

# EVE
ifeq ($(CORE),arp32_1)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_2)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_3)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_4)
 ISA = arp32
 ARCH = arp32
endif

#
# Derive XDC/ISA specific settings
#
ifeq ($(FORMAT),ELF)
  FORMAT_EXT = e
endif
# If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
#    in the filename extension of object/library/executable files
ifeq ($(ENDIAN),big)
  ENDIAN_EXT = e
endif

# In case of a15, a8
# for GCC Compiler ENDIAN_EXT suffixes by 'g'
# and FORMAT_EXT is null

ifeq ($(ISA),a15)
  FORMAT_EXT =
  ENDIAN_EXT = fg
endif

ifeq ($(ISA),a8)
  ifeq ($(TOOLCHAIN_a8),cgt)
    ifeq ($(FORMAT),ELF)
      FORMAT_EXT = e
    endif
    ifeq ($(ENDIAN),big)
      ENDIAN_EXT = ef
    else
	ENDIAN_EXT = f
    endif
  endif
  ifeq ($(TOOLCHAIN_a8),gcc)
	FORMAT_EXT =
	ENDIAN_EXT = fg
  endif
endif

# Define the file extensions
OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)

export SOC
export SOCFAMILY

# Nothing beyond this point
