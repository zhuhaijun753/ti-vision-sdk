# Makefile for device starterware hal mailbox app

APP_NAME = mmcsd_fileIO_app

SRCDIR = src
INCDIR = inc

INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform fat_lib fat_lib_edma starterware_examples_utility

# List all the components required by the application
COMP_LIST_COMMON = uartConsole utils_platform fat_lib fat_lib_edma sys_config \
                   starterware_hal starterware_examples_utility starterware_boards \
                   starterware_devices i2c_lib starterware_common starterware_osal starterware_pm_hal

# include starterware_pm_hal only for Tda2xx EVM build
ifeq ($(PLATFORM),$(filter $(PLATFORM), tda2xx-evm dra7xx-evm tda2ex-evm tda2xx dra7xx tda2ex))
INCLUDE_EXTERNAL_INTERFACES += starterware_pm_hal
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif

ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m4.cmd
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
