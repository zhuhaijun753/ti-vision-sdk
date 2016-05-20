
MODULE_NAME = bsp_platforms

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc bsp starterware starterware_common starterware_hal sys_config starterware_pm_lib starterware_pm_hal

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = bsp_common bsp_osal

MODULE_SRC_BASE_PATH := $(bsp_PATH)/src/platforms

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_platform.c
SRCS_tda2xx = bsp_platformTda2xx.c
SRCS_tda3xx = bsp_platformTda3xx.c
SRCS_ti814x = bsp_platformTI814x.c
SRCS_ti8149 = bsp_platformTI814x.c
SRCS_ti811x = bsp_platformTI814x.c
SRCS_omap5430 = bsp_platformOmap5x.c
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
