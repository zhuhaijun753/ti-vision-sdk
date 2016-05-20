
MODULE_NAME = bsp_vps

SRCDIR = src captdrv captdrv/src vpedrv vpedrv/src dispdrv dispdrv/src m2mdrv/src

INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware starterware_hal starterware_common starterware_vpslib bsp

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = bsp_common bsp_osal bsp_fvid2 bsp_platforms bsp_vpslib

MODULE_SRC_BASE_PATH := $(bsp_PATH)/src/vps

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON =
SRCS_tda2xx =
SRCS_ti814x =
PACKAGE_SRCS_COMMON = Makefile vpsdrv_control.h
CFLAGS_LOCAL_COMMON = $(BSP_CFLAGS)

ifneq ($(PACKAGE_SELECT),vps-hal-only)
SRCS_COMMON += vpsdrv_init.c vpsdrv_control.c
PACKAGE_SRCS_COMMON += src
  ifeq ($(PACKAGE_VIP),yes)
    capt_drv = yes
  endif
  ifeq ($(PACKAGE_ISS),yes)
    ifneq ($(PACKAGE_VIP),yes)
        capt_drv = yes
    endif
  endif
  ifeq ($(capt_drv),yes)
    include $(MODULE_SRC_BASE_PATH)/captdrv/SRC_FILES_captdrv.MK
  endif
  ifeq ($(PACKAGE_VPE),yes)
    include $(MODULE_SRC_BASE_PATH)/vpedrv/SRC_FILES_vpedrv.MK
  endif
  ifeq ($(PACKAGE_DSS),yes)
    include $(MODULE_SRC_BASE_PATH)/dispdrv/SRC_FILES_dispdrv.MK
  endif
  ifeq ($(PACKAGE_M2M),yes)
    include $(MODULE_SRC_BASE_PATH)/m2mdrv/SRC_FILES_m2mdrv.MK
  endif
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
