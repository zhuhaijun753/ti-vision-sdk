
MODULE_NAME = starterware_osal

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXERNAL_INTERFACES =

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = starterware_hal utils_platform

MODULE_SRC_BASE_PATH := $(starterware_PATH)/utils/osal

# Common source files and CFLAGS across all platforms and cores
ifeq ($(STARTERWARE_BUILD_ENV), yes)
SRCS_COMMON = osal.c osal_cache.c
endif
SRCS_COMMON = osal.c osal_cache.c
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
