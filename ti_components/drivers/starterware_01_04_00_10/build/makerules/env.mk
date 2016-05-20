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

# Directory where all internal software packages are located; typically
#  those that are checked into version controlled repository.
starterware_PATH = $(ROOTDIR)

# Directory where all external (imported) software packages are located; typically
#  those that are NOT checked into version controlled repository. In this case,
#  compiler tool chains etc.
EXTERNAL_SW_ROOT = C:

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
DEST_ROOT = $(starterware_PATH)/binary

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
ifeq ($(UTILS_INSTALL_DIR),)
  UTILS_INSTALL_DIR = $(EXTERNAL_SW_ROOT)/ti/ccsv5/utils/cygwin
endif

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/
else
  # else, assume it is linux
  PATH_SEPARATOR = :
endif

#
# Tools paths
#

# Cortex-M3
ifeq ($(CODEGEN_PATH_M3),)
  CODEGEN_PATH_M3 = $(EXTERNAL_SW_ROOT)/ti/ti-cgt-arm_5.2.5
endif
# Cortex-M4
ifeq ($(CODEGEN_PATH_M4),)
  CODEGEN_PATH_M4 = $(EXTERNAL_SW_ROOT)/ti/ti-cgt-arm_5.2.5
endif
# Cortex-A
ifeq ($(CODEGEN_PATH_A8),)
  CODEGEN_PATH_A8 = $(EXTERNAL_SW_ROOT)/ti/ti-cgt-arm_5.2.5
endif

# For Linaro GCC Cortex-A8
ifeq ($(CODEGEN_PATH_GCC_A8),)
  CODEGEN_PATH_GCC_A8 = $(EXTERNAL_SW_ROOT)/tools/gcc-arm-none-eabi-4_7-2013q3
endif
# DSP
ifeq ($(CODEGEN_PATH_DSP),)
  CODEGEN_PATH_DSP = $(EXTERNAL_SW_ROOT)/ti/C6000_7.4.2
endif
# EVE
ifeq ($(CODEGEN_PATH_EVE),)
  CODEGEN_PATH_EVE = $(EXTERNAL_SW_ROOT)/ti/arp32_1.0.7
endif
#Cortex A15
# For Code Sourcery
#CODEGEN_PATH_A15 = $(EXTERNAL_SW_ROOT)/CodeSourcery/Sourcery_CodeBench_Lite_for_ARM_EABI
# For RVCT
#CODEGEN_PATH_A15 = $(EXTERNAL_SW_ROOT)/ARM_Compiler_5
#For Linaro
ifeq ($(CODEGEN_PATH_A15),)
  CODEGEN_PATH_A15 = $(EXTERNAL_SW_ROOT)/tools/gcc-arm-none-eabi-4_7-2013q3
endif

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


PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_M3)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_A15)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_A8)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_DSP)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_EVE)/bin
export PATH

# Nothing beyond this point
