# Makefile for device starterware hal mailbox app

APP_NAME = ecc_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_a15host += main.c
SRCS_m4 += main.c
SRCS_c66x += main_c66x.c

ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m4.cmd
endif

# a15host
ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif

# dsp
ifeq ($(CORE),c66x)
 LNKCMD_FILE = ./lnk_dsp.cmd
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
