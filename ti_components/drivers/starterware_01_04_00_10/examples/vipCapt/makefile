# Makefile for device starterware hal mailbox app

APP_NAME = vipCapt

SRCDIR = src
INCDIR = inc $(starterware_PATH)/vpslib $(starterware_PATH)/vpslib/vpslib \
         $(starterware_PATH)/vpslib/devices \
         $(starterware_PATH)/include $(starterware_PATH)/ti814xDsslib/inc \
         $(starterware_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config i2c_lib utils_platform starterware_examples_utility uartConsole

# List all the components required by the application
COMP_LIST_COMMON = starterware_vpslib sys_config starterware_common starterware_osal starterware_hal i2c_lib utils_platform starterware_boards starterware_examples_utility starterware_devices uartConsole

ifneq ($(SOCFAMILY),ti814x)
    COMP_LIST_COMMON += starterware_pm_hal
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = app_frameBufMgmt.c \
              app_vipConfigure.c \
              app_clk_prcm.c \
              main.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# a15host
ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif
ifeq ($(CORE),a8host)
#Added linker command file to support gcc
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../lnk_gcc_a8.cmd
endif
endif
ifeq ($(CORE),m3vpss)
 LNKCMD_FILE = ../lnk_m3vpss_192kHeap.cmd
endif
ifeq ($(CORE),m3video)
 LNKCMD_FILE = ../lnk_m3video.cmd
endif
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m3vpss_192kHeap.cmd
endif
ifeq ($(CORE),m4vpss)
 LNKCMD_FILE = ../lnk_m3vpss_192kHeap.cmd
endif
ifeq ($(CORE),m4video)
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
