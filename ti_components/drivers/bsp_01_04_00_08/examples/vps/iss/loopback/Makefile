
APP_NAME = bsp_examples_loopbackiss

SRCDIR = src awb_alg
INCDIR = . inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware bsp bsp_examples

# List all the components required by the application
COMP_LIST_m4vpss = bsp_common bsp_osal bsp_boards bsp_devices bsp_fvid2 bsp_i2c bsp_platforms bsp_vps bsp_examples_utility awblib
COMP_LIST_COMMON = starterware_common starterware_vpslib starterware_hal i2c_lib sys_config awblib starterware_pm_lib starterware_pm_hal

# XDC CFG File
XDC_CFG_FILE_m4vpss = loopback.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_m4vpss = Loopback_m2mIsp.c Loopback_m2mWdr.c Loopback_simcop.c Loopback_capt.c Loopback_display.c Loopback_main.c\
            IDH_createImage.c IDH_freeImage.c IDH_remapFromLUT.c \
            SDF_computeHistogram.c WB_clipCorrectionParams.c \
            WB_computeGainOffsetValues.c WB_computeLUT.c \
            WB_estimateIlluminant.c WB_estimateWbParams.c WB_wbAdjustment.c \

CFLAGS_LOCAL_m4vpss = $(BSP_CFLAGS)

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
