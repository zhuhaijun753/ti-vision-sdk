MODULE_NAME = sys_config

ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/platform.mk

#Accomodating Changes for introducing multiple Tool Chains
ifneq ($(TOOLCHAIN_$(ISA)), )
SRCDIR= $(ARCH) $(SOCFAMILY)_common $(ARCH)/$(SOCFAMILY)/$(TOOLCHAIN_$(ISA))
else
SRCDIR = $(ARCH) $(ARCH)/$(SOCFAMILY) $(SOCFAMILY)_common
endif
INCDIR =

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal

#MODULE_SRC_BASE_PATH := $(bsp_PATH)/utils/platform/ti814x/a8

# Common source files and CFLAGS across all platforms and cores
# SRCS_COMMON += interrupt.c cpu.c cp15.c
# SRCS_a8host += intvec.c
# SRCS_ASM_COMMON += exceptionhandler.asm
# SRCS_ASM_a8host += performance_unit.asm

# Get the file list from filelist.mk file in ARCH and ARCH/PLATFORM folders

#Accomodating Changes for introducing multiple Tool Chains

ifneq ($(TOOLCHAIN_$(ISA)), )
include $(starterware_PATH)/system_config/$(ARCH)/$(SOCFAMILY)/$(TOOLCHAIN_$(ISA))/filelist.mk
else
ifeq ($(CORE),$(filter $(CORE), a15host a15_0))
include $(starterware_PATH)/system_config/$(ARCH)/$(SOCFAMILY)/filelist.mk
else
include $(starterware_PATH)/system_config/$(ARCH)/filelist.mk
endif
endif

include $(starterware_PATH)/system_config/$(SOCFAMILY)_common/filelist.mk

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

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
