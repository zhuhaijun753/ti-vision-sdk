
MODULE_NAME = bsp_boards

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware starterware_common starterware_hal bsp

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = bsp_common bsp_osal bsp_devices bsp_platforms starterware_common

MODULE_SRC_BASE_PATH := $(bsp_PATH)/src/boards

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_board.c bsp_boardTda2xx.c bsp_boardTda2ex.c bsp_boardTda3xx.c bsp_boardTI814x.c bsp_boardOmap5430.c
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(BSP_CFLAGS)

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
