# Filename: Makefile
#
# This file is the makefile for building PM LIB library.
#
#   Copyright (C) 2014 Texas Instruments Incorporated
#
#   All rights reserved. Property of Texas Instruments Incorporated.
#   Restricted rights to use, duplicate or disclose this code are
#   granted through contract.
#
#   The program may not be used without the written permission
#   of Texas Instruments Incorporated or against the terms and conditions
#   stipulated in the agreement under which this program has been
#   supplied.
#******************************************************************************

MODULE_NAME = starterware_pm_lib

SRCDIR = . $(SOCFAMILY)
INCDIR = . $(SOCFAMILY)

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config starterware_pm_hal
INCLUDE_INTERNAL_INTERFACES += starterware_pm_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += pmlib_sysconfig.c pmlib_clkrate.c pmlib_boardconfig.c pmlib_videopll_data.c pmlib_videopll.c
SRCS_a15_0 += pmlib_cpuidle_a15host.c
SRCS_a15host += pmlib_cpuidle_a15host.c
SRCS_m4 += pmlib_cpuidle_m4.c
SRCS_m4vpss += pmlib_cpuidle_m4.c
SRCS_c66x += pmlib_cpuidle_c66x.c
SRCS_arp32_1 += pmlib_cpuidle_arp32.c

ifeq ($(SOC),$(filter $(SOC), tda2xx dra7xx))
SRCS_COMMON +=  pmlib_clk_rate_data_tda2xx.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2ex dra72x))
SRCS_COMMON +=  pmlib_clk_rate_data_tda2ex.c
endif

ifeq ($(SOCFAMILY),tda3xx)
SRCS_COMMON +=  pmlib_clk_rate_data_tda3xx.c
endif

PACKAGE_SRCS_COMMON = .

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)


# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

SRCS_ASM_a15host += pmlib_cpuidle_utils_a15host.asm
SRCS_ASM_m4 += pmlib_cpuidle_utils_m4.asm

# For SDK build
SRCS_ASM_a15_0 += pmlib_cpuidle_utils_a15host.asm

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif

include $(ROOTDIR)/build/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
