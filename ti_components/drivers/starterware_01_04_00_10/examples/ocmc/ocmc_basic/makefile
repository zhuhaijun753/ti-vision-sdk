# Makefile for device starterware hal mailbox app

APP_NAME = ocmc_app

SRCDIR = src ../common/src
INCDIR = inc ../common/inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform starterware_boards starterware_pm_hal

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform starterware_boards
COMP_LIST_m4 = starterware_pm_hal

# Common source files and CFLAGS across all platforms and cores
SRCS_a15host = main.c
SRCS_c66x = main.c
SRCS_m4 = main_m4.c ocmc_common.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),c66x)
 LNKCMD_FILE = ../../lnk_dsp.cmd
endif

ifeq ($(CORE),m4)
 LNKCMD_FILE = ../../lnk_m4.cmd
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
