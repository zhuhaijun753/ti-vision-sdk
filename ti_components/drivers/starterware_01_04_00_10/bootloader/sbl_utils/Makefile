# Filename: Makefile
#
# This file is the makefile for building SBL Utils.
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

MODULE_NAME = sbl_utils

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole utils_platform \
                              qspi_flashlib fat_lib fat_lib_edma starterware_boards  \
                              starterware_pm_hal starterware_examples_utility \
                              sbl_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += sbl_utils_common.c
SRCS_tda3xx += sbl_utils_tda3xx.c sbl_utils_tda3xx_ddr_config.c

PACKAGE_SRCS_COMMON = .

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

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
