# Makefile for device starterware hal mailbox app

APP_NAME = sbl_multicore_mbx_2

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal utils_platform

COMP_LIST_a15host = sys_config
COMP_LIST_m4 = sys_config

# Common source files and CFLAGS across all platforms and cores

SRCS_m4 = main_ipu2_cpu0.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# a15host
ifeq ($(CORE),m4)
 LNKCMD_FILE = lnk_ipu2_cpu0.cmd
endif


LNKFLAGS_LOCAL_a15host += --entry main

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
