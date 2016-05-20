#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
DEST_ROOT = $(bsp_PATH)/binary

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
UTILS_INSTALL_DIR = $(xdc_PATH)

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/bin/
else
  # else, assume it is linux
  PATH_SEPARATOR = :
  UTILSPATH = /bin/
endif

# BIOS
bios_INCLUDE = $(bios_PATH)/packages
export bios_INCLUDE

# XDC
xdc_INCLUDE = $(xdc_PATH)/packages
export xdc_INCLUDE

# BSP drivers
bsp_INCLUDE = $(bsp_PATH)/include
export bsp_INCLUDE

# BSP Examples
bsp_examples_INCLUDE = $(bsp_PATH)/examples
export bsp_examples_INCLUDE

# EDMA
edma_INCLUDE = $(edma3_lld_PATH)/packages
export edma_INCLUDE
include $(edma3_lld_PATH)/packages/component.mk

# Starterware
starterware_INCLUDE = $(starterware_PATH)/include

include $(bsp_PATH)/build/makerules/component.mk
include $(starterware_PATH)/build/makerules/component.mk
export starterware_INCLUDE

# Package Name
PACKAGE_NAME = $(bsp_RELPATH)
export PACKAGE_NAME

#
# Tools paths
#

# Cortex-A8
CODEGEN_PATH_A8 =

# DSP
CODEGEN_PATH_C674 = $(CODEGEN_PATH_DSP)


# Commands commonly used within the make files
RM = $(UTILSPATH)rm
RMDIR = $(UTILSPATH)rm -rf
MKDIR = $(UTILSPATH)mkdir
ECHO = @$(UTILSPATH)echo

#emake provides detailed info for build analysis.
EMAKE = emake --emake-emulation=gmake --emake-gen-subbuild-db=1 --emake-annodetail=waiting

ifeq ($(OS),Windows_NT)
  MAKE = gmake
#  MAKE =  $(EMAKE)
else
  MAKE = make
endif
EGREP = $(UTILSPATH)egrep
CP = $(UTILSPATH)cp
ifeq ($(OS),Windows_NT)
  CHMOD = $(UTILSPATH)echo
else
  CHMOD = $(UTILSPATH)chmod
endif

ifeq ($(OS),Windows_NT)
  TOUCH=$(xdc_PATH)/bin/touch
else
  TOUCH=touch
endif

#
# XDC specific ENV variables
#
# XDC Config.bld file (required for configuro); Derives from top-level bsp_PATH
ifeq ($(SOCFAMILY),tda2xx)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    ifeq ($(PLATFORM),tda2xx-interposer)
      CONFIG_BLD_XDC_m4     = $(bsp_PATH)/examples/config_tda2xx_interposer.bld
    else
      CONFIG_BLD_XDC_m4     = $(bsp_PATH)/examples/config_tda2xx.bld
    endif
    ifeq ($(SOC),tda2ex)
      CONFIG_BLD_XDC_m4     = $(bsp_PATH)/examples/config_tda2ex.bld
    endif
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(bsp_PATH)/examples/config_tda2xx_66.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_a15),)
    CONFIG_BLD_XDC_a15 = $(bsp_PATH)/examples/config_tda2xx_a15.bld
  endif
endif

ifeq ($(SOCFAMILY),tda3xx)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    ifeq ($(PLATFORM),tda3xx-zebu)
      CONFIG_BLD_XDC_m4   = $(bsp_PATH)/examples/config_tda3xx_zebu.bld
    else
      CONFIG_BLD_XDC_m4   = $(bsp_PATH)/examples/config_tda3xx.bld
    endif
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(bsp_PATH)/examples/config_tda3xx_66.bld
  endif
endif

ifeq ($(PLATFORM),omap5430-evm)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    CONFIG_BLD_XDC_m4     = $(bsp_PATH)/examples/config_omap5430.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_m3),)
    CONFIG_BLD_XDC_m3     = $(bsp_PATH)/examples/config_omap5430.bld
  endif
endif

ifeq ($(PLATFORM),ti814x-evm)
  ifeq ($(CONFIG_BLD_XDC_m3),)
    CONFIG_BLD_XDC_m3     = $(bsp_PATH)/examples/config_ti814x_m3.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_674),)
    CONFIG_BLD_XDC_674     = $(bsp_PATH)/examples/config_ti814x_674.bld
  endif
endif

ifeq ($(PLATFORM),ti8149-evm)
  ifeq ($(CONFIG_BLD_XDC_m3),)
    CONFIG_BLD_XDC_m3     = $(bsp_PATH)/examples/config_ti8149_m3.bld
  endif
endif

ifeq ($(PLATFORM),ti811x-evm)
  ifeq ($(CONFIG_BLD_XDC_m3),)
    CONFIG_BLD_XDC_m3     = $(bsp_PATH)/examples/config_ti811x_m3.bld
  endif
endif

XDCROOT = $(xdc_PATH)
XDCTOOLS = $(xdc_PATH)
export XDCROOT
export XDCTOOLS

CGTOOLS = $(CODEGEN_PATH_M4)
export CGTOOLS

CGTOOLS_DSP = $(CODEGEN_PATH_C674)
export CGTOOLS_DSP

CODESOURCERYCGTOOLS = $(CODEGEN_PATH_A8)
export CODESOURCERYCGTOOLS

CGTOOLS_A15 = $(CODEGEN_PATH_A15)
export CGTOOLS_A15

STRIP470 = $(CODEGEN_PATH_M4)/bin/strip470 -p
STRIP6x = $(CODEGEN_PATH_C674)/bin/strip6x -p
STRIP_ALL_ARM = $(CODEGEN_PREFIX)strip -s
STRIP_DEBUG_ARM = $(CODEGEN_PREFIX)strip --strip-debug

PATH += $(PATH_SEPARATOR)$(xdc_PATH)$(PATH_SEPARATOR)$(CODEGEN_PATH_M4)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_C674)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_A15)/bin$(PATH_SEPARATOR)
export PATH

# Nothing beyond this point
