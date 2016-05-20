# Filename: Makefile
#
# This file is the makefile for building PM HAL library.
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

MODULE_NAME = starterware_pm_hal

SRCDIR = . $(SOCFAMILY) common
INCDIR = . $(SOCFAMILY) common

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal utils_platform uartConsole
INCLUDE_INTERNAL_INTERFACES = starterware_pm_hal

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON +=  pmhal_vm.c                                                     \
                hw_pmhal_vmdata.c                                              \
                hw_pmhal_data.c                                                \
                hw_pmhal_data_names.c                                          \
                pmhal_pmic.c                                                   \
                pmhal_pmicComm.c                                               \
                pmhal_mm.c                                                     \
                pmhal_prm_int.c                                                \
                pmhal_bgap.c                                                   \
                hw_pmhal_bgap_data.c                                           \
                pmhal_pdm.c                                                    \
                pmhal_rm.c                                                     \
                pmhal_sd.c                                                     \
                pmhal_cm.c                                                     \
                hw_pmhal_bgap_common_data.c                                    \
                hw_pmhal_prmdata.c                                             \
                pm_utils.c                                                     \
                hw_pmhal_clocktree_data.c                                      \
                pmhal_prcm_stats.c                                             \
                pmhal_clocktree.c


ifeq ($(SOCFAMILY),tda3xx)
SRCS_COMMON +=  pmhal_tps65917.c                                               \
                pmhal_l8731.c
endif

ifeq ($(SOCFAMILY),tda2xx)
SRCS_COMMON +=  pmhal_videopll.c                                               \
                hw_pmhal_videopll_data.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx dra7xx))
SRCS_COMMON += pmhal_tps659039.c
endif

ifeq ($(SOC),$(filter $(SOC), tda2ex dra72x))
SRCS_COMMON += pmhal_tps65917.c
endif

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

LNKCMD_FILE =

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

SRCS_a15host += pmhal_mpu_lprm.c
SRCS_a15_0 += pmhal_mpu_lprm.c

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point