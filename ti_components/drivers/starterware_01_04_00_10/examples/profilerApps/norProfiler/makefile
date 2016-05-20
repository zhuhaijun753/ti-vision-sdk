APP_NAME = norProfiler

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sys_config uartConsole starterware_hal utils_platform

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform

# Common source files and CFLAGS across all platforms and cores

SRCS_COMMON += main.c nor.c util.c debug.c
SRCS_a8host +=
ASMS_a8host +=

# Common source files and CFLAGS across all platforms and cores

#LNKCMD_FILE = lnk_a8.cmd

ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../../lnk_a15.cmd
endif
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m4.cmd
endif
ifeq ($(CORE),a8host)
 #Added linker command file to support gcc
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../../lnk_gcc_a8.cmd
endif
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

LNKFLAGS_LOCAL_a15host += --entry Entry

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
