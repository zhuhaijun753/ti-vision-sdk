# Filename: makefile_tda3xx.mk
#
# This file is the makefile for building SBL for tda3xx.
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

ifeq ($(OPPMODE),)
APP_NAME = sbl_$(BOOTMODE)
else ifeq ($(OPPMODE),opp_nom)
APP_NAME = sbl_$(BOOTMODE)
else
APP_NAME = sbl_$(BOOTMODE)_$(OPPMODE)
endif

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = uartConsole sys_config starterware_hal utils_platform sbl_lib sbl_utils starterware_pm_hal

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform sbl_lib sbl_utils starterware_pm_hal

CFLAGS_LOCAL_COMMON += $(STARTERWARE_CFLAGS)

ifeq ($(BOOTMODE),qspi)
    COMP_LIST_COMMON += qspi_flashlib
    INCLUDE_EXTERNAL_INTERFACES += qspi_flashlib
endif

ifeq ($(BOOTMODE),qspi_sd)
    COMP_LIST_COMMON += qspi_flashlib fat_lib fat_lib_edma starterware_examples_utility starterware_boards starterware_devices i2c_lib starterware_common starterware_osal
    INCLUDE_EXTERNAL_INTERFACES += qspi_flashlib fat_lib fat_lib_edma starterware_examples_utility starterware_boards starterware_devices i2c_lib starterware_common starterware_osal
endif

#-----------------------------------------------------------------------------#
# Common compile flags                                                        #
#-----------------------------------------------------------------------------#

# Common source files and CFLAGS across all platforms and cores

SRCS_m4 += sbl_tda3xx_priv.c sbl_tda3xx_main.c

ifeq ($(BOOTMODE),nor)
SRCS_ASM_m4 += sbl_m4_init_nor.asm
endif

SRCS_ASM_m4 += sbl_m4_init.asm

#Flags for SBL opp_nom, opp_od and opp_high
ifeq ($(OPPMODE),)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_low)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=0
else ifeq ($(OPPMODE),opp_nom)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_od)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=2
else ifeq ($(OPPMODE),opp_high)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=3
endif

ifeq ($(SOCFAMILY),tda3xx)
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi qspi_sd))
    LNKCMD_FILE = ../lnk_tda3xx_m4.cmd
    LNKFLAGS_LOCAL_m4 += -e sbl_start --diag_suppress=10063 --retain SblIPU1Core1Init
endif
ifeq ($(BOOTMODE),nor)
    LNKCMD_FILE = ../lnk_tda3xx_m4_nor.cmd
    LNKFLAGS_LOCAL_m4 += -e sbl_nor_start --diag_suppress=10063 --retain SblIPU1Core1Init
endif
endif



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
