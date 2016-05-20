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
#     4. Profile needs to change (debug/release/prod_release)
#     5. Build option changes (xdc/make/full)
#

# Global options

# Build - Allowed values = full | xdc | make
#         This "builds" packages based on the setting:
#                 full - build both XDC and make (all the packages/components)
#                 xdc  - build and configure only XDC packages
#                 make - build only make based components and link everything
# NOTE: BUILD need not be defined at all, which case it behaves like it is set
#       to "full". This is to ensure backward compatibility.
BUILD = full

# Endianness : Allowed values = little | big
ENDIAN = little

# Format : Allowed values = COFF | ELF
FORMAT = ELF

# Platform memory: available external memory
PLATFORM_MEM = 1024M

#
# Platform specific
#
CFLAGS_GLOBAL_tda2xx-mc = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2xx-evm = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_dra7xx-evm = -DDRA7XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2ex-evm = -DTDA2EX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_ti814x-evm = -DTI814X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda3xx-evm = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2xx-virtio = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_VIRTIO
CFLAGS_GLOBAL_tda2xx-sim = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_SIM
CFLAGS_GLOBAL_tda2xx-zebu = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_ZEBU
CFLAGS_GLOBAL_tda3xx-sim = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_SIM
CFLAGS_GLOBAL_tda3xx-zebu = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_ZEBU
CFLAGS_GLOBAL_ti8149-evm = -DTI8149_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_ti811x-evm = -DTI811X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI

#
# Core specific options - Cores of tda2xx, tda3xx, ti814x, ti8149 and ti811x
#

# m3video - Ducati - Core 0 (Cortex-M3)
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m3video = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m3video = -x --zero_init=on

# m3vpss - Ducati - Core 1 (Cortex-M3)
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m3vpss = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m3vpss = -x --zero_init=on

# m4video - Benelli - Core 1 (Cortex-M4)
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m4video = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m4video = -x --zero_init=on

# m4vpss - Benneli - Core 0 (Cortex-M4)
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m4vpss = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m4vpss = -x --zero_init=on

# a8host - Cortex-A8

# Profile: Allowed values = debug
PROFILE_a8host = debug
CFLAGS_GLOBAL_a8host = -c -x c -Wunused -Wall -g
LNKFLAGS_GLOBAL_a8host =

# a15host - Cortex-A15

# Profile: Allowed values = debug
PROFILE_a15_0 = debug
CFLAGS_GLOBAL_a15_0 =
LNKFLAGS_GLOBAL_a15_0 =

# dsp - IMPLEMENTED
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_c6xdsp =
LNKFLAGS_GLOBAL_c6xdsp = -x

# dsp - IMPLEMENTED for tda2xx
# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_c66xdsp =
LNKFLAGS_GLOBAL_c66xdsp = -x

# Nothing beyond this point
