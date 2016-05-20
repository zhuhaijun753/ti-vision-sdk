
MODULE_NAME = starterware_vpslib

ifeq ($(PLATFORM),ti814x)
    ifeq ($(PACKAGE_SELECT),vps-vpe-only)
      $(error Error: Invalid build option. vpslib cannot be built for PACKAGE_SELCT vps-vpe-only for ti814x)
    endif
    ifeq ($(PACKAGE_SELECT),vps-dss-only)
      $(error Error: Invalid build option. vpslib cannot be built for PACKAGE_SELCT vps-dss-only for ti814x)
    endif
endif

SRCDIR = drv common common/src hal hal/src hal/src/wdrldc                      \
         captcore captcore/src                                                 \
         vpecore vpecore/src                                                   \
         dispcore dispcore/src                                                 \
         isscore isscore/src

INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES =

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = starterware_hal starterware_common

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

#TODO: Fix this for packaging
PACKAGE_SRCS_COMMON = Makefile

MODULE_SRC_BASE_PATH := $(starterware_PATH)/vpslib
include $(MODULE_SRC_BASE_PATH)/hal/SRC_FILES_hal.MK

ifeq ($(STARTERWARE_BUILD_ENV), yes)

    SRCS_tda2xx += vps_initDrv.c
    SRCS_tda3xx += vps_initDrv.c
    ifeq ($(PACKAGE_VIP),yes)
        SRCS_tda2xx += vps_vipDrv.c
        SRCS_tda3xx += vps_vipDrv.c
    endif
    ifeq ($(PACKAGE_DSS),yes)
        SRCS_tda2xx += vps_dctrlDrv.c vps_dssDrv.c
        SRCS_tda3xx += vps_dctrlDrv.c vps_dssDrv.c
    endif

    ifeq ($(PACKAGE_VIP),yes)
        SRCS_ti814x += vps_vipDrv.c vps_initDrv.c
    endif

endif

ifneq ($(PACKAGE_SELECT),vps-hal-only)
  include $(MODULE_SRC_BASE_PATH)/common/SRC_FILES_common.MK
  ifeq ($(PACKAGE_VIP),yes)
    include $(MODULE_SRC_BASE_PATH)/captcore/SRC_FILES_captcore.MK
  endif
  ifeq ($(PACKAGE_VPE),yes)
    include $(MODULE_SRC_BASE_PATH)/vpecore/SRC_FILES_vpecore.MK
  endif
  ifeq ($(PACKAGE_DSS),yes)
    include $(MODULE_SRC_BASE_PATH)/dispcore/SRC_FILES_dispcore.MK
  endif
  ifeq ($(PACKAGE_ISS_DEF), yes)
    include $(MODULE_SRC_BASE_PATH)/isscore/SRC_FILES_isscore.MK
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
