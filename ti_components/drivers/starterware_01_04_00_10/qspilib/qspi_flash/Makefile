# Makefile for device starterware hal mailbox app

MODULE_NAME = qspi_flashlib

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal utils_platform

# Common source files and CFLAGS across all platforms and cores
SRCS_a8host +=
ASMS_a8host +=

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = qspi_flash.c qspi_cmd_init.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

LNKCMD_FILE =

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
