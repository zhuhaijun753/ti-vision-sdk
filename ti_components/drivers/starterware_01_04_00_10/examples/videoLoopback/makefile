# Makefile for device starterware hal mailbox app

APP_NAME = videoLoopback

SRCDIR = src
INCDIR = inc $(starterware_PATH)/vpslib $(starterware_PATH)/vpslib/vpslib \
         $(starterware_PATH)/vpslib/devices $(starterware_PATH)/vpslib/common \
         $(starterware_PATH)/include $(starterware_PATH)/ti814xDsslib/inc \
         $(starterware_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sys_config starterware_hal i2c_lib utils_platform starterware_examples_utility uartConsole starterware_pm_lib starterware_pm_hal

# List all the components required by the application
COMP_LIST_COMMON = i2c_lib sys_config starterware_vpslib  starterware_hal starterware_common utils_platform starterware_osal starterware_boards starterware_examples_utility starterware_devices uartConsole starterware_pm_hal starterware_pm_lib

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = app_frameBufMgmt.c \
              app_videoLoopbackConfigure.c \
              main.c \
              app_sensor_lcd_config.c
CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m3vpss_192kHeap.cmd
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
