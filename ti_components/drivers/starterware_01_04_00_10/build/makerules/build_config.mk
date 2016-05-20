#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: build_config.mk
#
# Build configuration make file - This file contains all the options that are
#                                 frequently changed
#
# This file changes when:
#     1. format needs to change (eg: COFF/ELF)
#     2. Endian-ness needs to change (little/big)
#     3. global compiler and linker options need to change (one entry for each
#                                                           core)
#     4. Profile needs to change (debug/release)
#

# Global options

# Endianness : Allowed values = little | big
ENDIAN = little

# Format : Allowed values = COFF | ELF
FORMAT = ELF

#
# Core specific options - Cores of tda2xx, tda3xx, ti814x, ti8149 and ti811x
#

# Default Profile
# Supported Values: debug | release
ifeq ($(PROFILE), )
  PROFILE := release
endif

# Set Core Profile depending on PROFILE value
ifeq ($(PROFILE_$(CORE)), )
  PROFILE_$(CORE) := $(PROFILE)
endif

# m3video - Ducati - Core 0 (Cortex-M3)
CFLAGS_GLOBAL_m3video = -g -ms
LNKFLAGS_GLOBAL_m3video = -x --zero_init=on

# m3vpss - Ducati - Core 1 (Cortex-M3)
CFLAGS_GLOBAL_m3vpss = -g -ms
LNKFLAGS_GLOBAL_m3vpss = -x --zero_init=on

# m4 - IPU Core (Cortex-M4)
CFLAGS_GLOBAL_m4 = -g -ms
LNKFLAGS_GLOBAL_m4 = -x --zero_init=on

# m4video - Benelli - Core 0 (Cortex-M4)
CFLAGS_GLOBAL_m4video = -g -ms
LNKFLAGS_GLOBAL_m4video = -x --zero_init=on

# m4vpss - Benelli - Core 1 (Cortex-M4)
CFLAGS_GLOBAL_m4vpss = -g -ms
LNKFLAGS_GLOBAL_m4vpss = -x --zero_init=on

# a8host - Cortex-A8
CFLAGS_GLOBAL_a8host = -g
LNKFLAGS_GLOBAL_a8host =

# dsp - C674 DSP
CFLAGS_GLOBAL_c674x =
LNKFLAGS_GLOBAL_c674x = -x --zero_init=on --retain=_vectors

# dsp - C66 DSP
CFLAGS_GLOBAL_c66x =
LNKFLAGS_GLOBAL_c66x = -x --zero_init=on --retain=_vectors

# a15host - Cortex-A15
CFLAGS_GLOBAL_a15host =
LNKFLAGS_GLOBAL_a15host =

# a15_0 - Cortex-A15
CFLAGS_GLOBAL_a15_0 =
LNKFLAGS_GLOBAL_a15_0 =

# arp32_1 - EVE
CFLAGS_GLOBAL_arp32_1 =
LNKFLAGS_GLOBAL_arp32_1 =

# arp32_2 - EVE
CFLAGS_GLOBAL_arp32_2 =
LNKFLAGS_GLOBAL_arp32_2 =

# arp32_3 - EVE
CFLAGS_GLOBAL_arp32_3 =
LNKFLAGS_GLOBAL_arp32_3 =

# arp32_4 - EVE
CFLAGS_GLOBAL_arp32_4 =
LNKFLAGS_GLOBAL_arp32_4 =

############################################
# Configurable parameters

# Default platform
# Supported values: ti814x, tda2xx, dra7xx, tda2ex, tda3xx, tda2xx-sim, tda2xx-evm, dra7xx-evm, tda2ex-evm, tda3xx-sim, tda3xx-zebu, tda3xx-evm
ifeq ($(PLATFORM), )
  PLATFORM := ti814x
endif

#VPS specific parameters
# Default PACKAGE_SELECT build flag
# Supported values: all, vps-hal-only, vps-vip-only, vps-vpe-only, vps-dss-only, vps-vip-dss, vps-vip-vpe
ifeq ($(PACKAGE_SELECT), )
  PACKAGE_SELECT := all
endif

# Default klockwork build flag, yes or no
ifeq ($(KW_BUILD), )
  KW_BUILD := no
endif

# Default C++ build flag, yes or no
ifeq ($(CPLUSPLUS_BUILD), )
  CPLUSPLUS_BUILD := no
endif

# Default TOOLCHAIN_a8 build option, gcc or cgt option
ifeq ($(TOOLCHAIN_a8), )
  TOOLCHAIN_a8 := cgt
endif

STARTERWARE_BUILD_ENV := yes

export PLATFORM
export CORE
export PROFILE_$(CORE)
export PACKAGE_SELECT
export KW_BUILD
export CPLUSPLUS_BUILD
export STARTERWARE_BUILD_ENV
export TOOLCHAIN_a8

# Nothing beyond this point
