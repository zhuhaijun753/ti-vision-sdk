
MODULE_NAME = bsp_devices

SRCDIR = src tvp5158/src tvp7002/src sii9127/src mt9v022/src ov1063x/src \
         lcdCtrl/src tlc59108/src aic31/src ar0132/src sii9022a/src ioexp/src \
         ar0132rccc/src pga450/src adv7611/src ov10640/src ar0140/src \
         imx224/src ds90uh925/src ds90uh926/src

INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware starterware_common bsp

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = bsp_common bsp_osal bsp_boards bsp_fvid2 bsp_i2c bsp_platforms starterware_hal

MODULE_SRC_BASE_PATH := $(bsp_PATH)/src/devices

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_device.c bsp_deviceI2c.c
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(BSP_CFLAGS)

include $(MODULE_SRC_BASE_PATH)/tvp5158/SRC_FILES_tvp5158.MK
include $(MODULE_SRC_BASE_PATH)/tvp7002/SRC_FILES_tvp7002.MK
include $(MODULE_SRC_BASE_PATH)/sii9127/SRC_FILES_sii9127.MK
include $(MODULE_SRC_BASE_PATH)/mt9v022/SRC_FILES_mt9v022.MK
include $(MODULE_SRC_BASE_PATH)/ov1063x/SRC_FILES_ov1063x.MK
include $(MODULE_SRC_BASE_PATH)/lcdCtrl/SRC_FILES_lcdCtrl.MK
include $(MODULE_SRC_BASE_PATH)/tlc59108/SRC_FILES_tlc59108.MK
include $(MODULE_SRC_BASE_PATH)/aic31/SRC_FILES_aic31.MK
include $(MODULE_SRC_BASE_PATH)/ar0132/SRC_FILES_ar0132.MK
include $(MODULE_SRC_BASE_PATH)/ar0140/SRC_FILES_ar0140.MK
include $(MODULE_SRC_BASE_PATH)/ar0132rccc/SRC_FILES_ar0132rccc.MK
include $(MODULE_SRC_BASE_PATH)/sii9022a/SRC_FILES_sii9022a.MK
include $(MODULE_SRC_BASE_PATH)/ds90uh925/SRC_FILES_ds90uh925.MK
include $(MODULE_SRC_BASE_PATH)/ds90uh926/SRC_FILES_ds90uh926.MK
include $(MODULE_SRC_BASE_PATH)/ioexp/SRC_FILES_ioexp.MK
include $(MODULE_SRC_BASE_PATH)/pga450/SRC_FILES_pga450.MK
include $(MODULE_SRC_BASE_PATH)/adv7611/SRC_FILES_adv7611.MK
include $(MODULE_SRC_BASE_PATH)/ov10640/SRC_FILES_ov10640.MK
include $(MODULE_SRC_BASE_PATH)/imx224/SRC_FILES_imx224.MK

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
