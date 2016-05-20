# Filename: Makefile
#
# This file is the makefile for building the cpu Idle example.
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

APP_NAME = pm_cpuidle_test_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform starterware_pm_hal starterware_pm_lib

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform starterware_pm_hal starterware_pm_lib

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_a15host += main_a15host.c
SRCS_m4 += main_m4.c
SRCS_c66x += main_c66x.c

# a15host
ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../../lnk_a15.cmd
endif

# m4
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../../lnk_m4.cmd
endif

# dsp
ifeq ($(CORE),c66x)
 LNKCMD_FILE = ../../lnk_dsp.cmd
endif

LNKFLAGS_LOCAL_a15host += --entry Entry

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

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
