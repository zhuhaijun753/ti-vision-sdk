# Makefile for device starterware hal mcaspTransmit app

APP_NAME = mcaspTransmit_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config utils_platform

# List all the components required by the application
COMP_LIST_a8host = starterware_hal sys_config utils_platform
COMP_LIST_m3vpss  = starterware_hal sys_config utils_platform
COMP_LIST_m3video  = starterware_hal sys_config utils_platform
COMP_LIST_a15host  = starterware_hal sys_config utils_platform
COMP_LIST_m4  = starterware_hal sys_config utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(SOCFAMILY),ti814x)
SRCS_$(SOCFAMILY)  = mcaspTransmit.c
endif

ifeq ($(SOCFAMILY),tda2xx)
SRCS_$(SOCFAMILY) =  mcaspTransmit_tdaxx.c
endif

ifeq ($(SOCFAMILY),tda3xx)
SRCS_$(SOCFAMILY) =  mcaspTransmit_tdaxx.c
endif

# Core specific configurations

ifeq ($(CORE),a8host)

#Added linker command file to support gcc
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../../lnk_gcc_a8.cmd
endif
endif

ifeq ($(CORE),m3vpss)
 LNKCMD_FILE = ../../lnk_m3vpss.cmd
 endif

ifeq ($(CORE),m3video)
 LNKCMD_FILE = ../../lnk_m3vpss.cmd
 endif

# Core specific configurations for vayu

ifeq ($(CORE),a15host)
    LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),m4)
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
