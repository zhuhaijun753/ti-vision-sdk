# Makefile for device starterware hal mailbox app

APP_NAME = uart_test

SRCDIR = src ../common/src
INCDIR = inc ../common/inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config utils_platform starterware_boards starterware_common starterware_pm_hal

# List all the components required by the application
COMP_LIST_COMMON = starterware_hal sys_config utils_platform starterware_boards starterware_pm_hal

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c uartConfig.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),a15host)
	LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),m4)
	LNKCMD_FILE = ../../lnk_m4.cmd
endif

LNKFLAGS_LOCAL_a15host += --entry Entry

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