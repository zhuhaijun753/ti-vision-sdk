
APP_NAME = bsp_examples_i2cUtility

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc starterware starterware_hal bsp bsp_examples

# List all the components required by the application
COMP_LIST_COMMON = starterware_common starterware_hal i2c_lib sys_config \
                   bsp_common bsp_osal bsp_boards bsp_devices bsp_fvid2 bsp_i2c bsp_platforms bsp_examples_utility

# XDC CFG File
XDC_CFG_FILE_m4vpss = i2cUtility.cfg
XDC_CFG_FILE_m4video = i2cUtility.cfg
XDC_CFG_FILE_m3vpss = i2cUtilityM3.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = Bsp_i2cUtilityMain.c Bsp_i2cRdWrUtil.c
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
