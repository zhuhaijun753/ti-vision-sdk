# Filename: Makefile
#
# This file is the makefile for building SBL Multicore Mailbox App Image
# Binaries.
#
#   Copyright (C) 2015 Texas Instruments Incorporated
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

APP_NAME = sbl_multicore_mbx_1

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2ex tda3xx))
SRCDIR = $(SOC)/
INCDIR = $(SOC)/
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sys_config starterware_hal uartConsole utils_platform

# List all the components required by the application
COMP_LIST_COMMON = uartConsole sys_config starterware_hal utils_platform

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),tda2xx)
SRCS_a15host=main_mpu_cpu1.c
SRCS_m4 = main_ipu1_cpu1.c
SRCS_c66x = main_dsp2.c
else ifeq ($(SOC),tda2ex)
SRCS_m4 = sbl_mbx_ipu1_cpu1.c
else ifeq ($(SOC),tda3xx)
SRCS_m4 = sbl_mbx_ipu1_cpu1.c
SRCS_c66x = sbl_mbx_dsp2.c
endif

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(SOC),tda2xx)
ifeq ($(CORE),a15host)
 LNKCMD_FILE = $(SOC)/lnk_mpu_cpu1.cmd
endif
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2ex tda3xx))
ifeq ($(CORE),m4)
 LNKCMD_FILE = $(SOC)/lnk_ipu1_cpu1.cmd
endif
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda3xx))
ifeq ($(CORE),c66x)
 LNKCMD_FILE = $(SOC)/lnk_dsp2.cmd
endif
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
# SRCS_<core/SoC/platform-name> =
# CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
# and need not be explicitly specified here

# Nothing beyond this point
