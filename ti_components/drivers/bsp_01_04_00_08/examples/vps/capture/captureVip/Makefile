
APP_NAME = bsp_examples_captureVip

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware bsp bsp_examples starterware_hal

# List all the components required by the application
COMP_LIST_m4vpss = bsp_common bsp_osal bsp_boards bsp_devices bsp_fvid2 bsp_i2c bsp_platforms bsp_vps bsp_examples_utility
COMP_LIST_m3vpss = bsp_common bsp_osal bsp_boards bsp_devices bsp_fvid2 bsp_i2c bsp_platforms bsp_vps bsp_examples_utility
COMP_LIST_COMMON = starterware_common starterware_vpslib starterware_hal i2c_lib sys_config

# XDC CFG File
XDC_CFG_FILE_m4vpss = captureVip.cfg
XDC_CFG_FILE_m3vpss = captureVipM3.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_m4vpss = CaptureVip_main.c
CFLAGS_LOCAL_m4vpss = $(BSP_CFLAGS)
SRCS_m3vpss = CaptureVip_main.c
CFLAGS_LOCAL_m3vpss = $(BSP_CFLAGS)

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
