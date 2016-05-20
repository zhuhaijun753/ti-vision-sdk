# Makefile for device starterware hal mcaspTransmit app

APP_NAME = mcasp_sinetone_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = i2c_lib uartConsole starterware_hal sys_config utils_platform

# List all the components required by the application
COMP_LIST_COMMON  = i2c_lib uartConsole starterware_hal sys_config utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

SRCS_COMMON  = mcasp_transmit_tda2xx.c

# Core specific configurations for vayu
ifeq ($(CORE),a15host)
    LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),c66x)
 LNKCMD_FILE = ../../lnk_dsp.cmd
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
