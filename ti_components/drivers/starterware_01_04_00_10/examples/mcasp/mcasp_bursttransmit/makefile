# Makefile for device starterware hal mcaspBurstTransmit app

APP_NAME = mcaspBurstTransmit_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config utils_platform

# List all the components required by the application

COMP_LIST_a15host  = starterware_hal sys_config utils_platform
COMP_LIST_m4  = starterware_hal sys_config utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# Core specific configurations

ifeq ($(CORE),a15host)
    SRCS_a15host  = mcaspBurstTransmit_tda2xx.c
    LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),m4)
    SRCS_m4  = mcaspBurstTransmit_tda2xx.c
    LNKCMD_FILE = ../../lnk_m4.cmd
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
