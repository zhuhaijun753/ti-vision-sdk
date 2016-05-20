# Makefile for device starterware hal mailbox app
APP_NAME = sensor_config_app

SRCDIR = src
INCDIR = . inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sys_config starterware_hal i2c_lib uartConsole utils_platform starterware_examples_utility

# List all the components required by the application
COMP_LIST_COMMON  =  uartConsole i2c_lib sys_config starterware_hal utils_platform starterware_examples_utility starterware_boards starterware_devices starterware_osal starterware_common
COMP_LIST_a15host =  starterware_pm_hal
COMP_LIST_m4  =  starterware_pm_hal

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = sensorconfig.c

#SRCS_dsp = main_dsp.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),a8host)
#Added linker command file to support gcc
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../lnk_gcc_a8.cmd
endif
endif
ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif
ifeq ($(CORE),m3vpss)
 LNKCMD_FILE = ../lnk_m3vpss.cmd
endif
ifeq ($(CORE),c674x)
 LNKCMD_FILE = ../lnk_dsp.cmd
endif
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m4.cmd
endif

LNKFLAGS_LOCAL_a15host += --entry Entry

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
