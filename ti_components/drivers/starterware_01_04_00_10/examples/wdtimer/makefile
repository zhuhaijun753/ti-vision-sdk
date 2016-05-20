# Makefile for device starterware hal mailbox app

APP_NAME = wdtimer_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform

# List all the components required by the application

COMP_LIST_COMMON = sys_config uartConsole starterware_hal utils_platform

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif

ifeq ($(CORE),a8host)
#Added linker command file to support gcc
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../lnk_gcc_a8.cmd
endif
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
