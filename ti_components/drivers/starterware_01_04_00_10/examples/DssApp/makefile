# Makefile for device starterware hal mailbox app

APP_NAME = DssApp

SRCDIR = src
INCDIR = inc $(starterware_PATH)/vpslib $(starterware_PATH)/vpslib/vpslib \
         $(starterware_PATH)/vpslib/devices $(starterware_PATH)/vpslib/common \
         $(starterware_PATH)/include $(starterware_PATH)/include/hw

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config starterware_examples_utility uartConsole starterware_pm_lib starterware_pm_hal

# List all the components required by the application
COMP_LIST_COMMON = starterware_vpslib sys_config starterware_common starterware_osal starterware_boards starterware_examples_utility starterware_devices utils_platform uartConsole starterware_pm_hal starterware_pm_lib

# include i2c_lib only for EVM build
ifeq ($(PLATFORM),$(filter $(PLATFORM), tda2xx-evm dra7xx-evm tda2ex-evm tda3xx-evm tda2xx dra7xx tda2ex tda3xx tda3xx-sim))
INCLUDE_EXTERNAL_INTERFACES += i2c_lib
COMP_LIST_COMMON += starterware_hal i2c_lib
endif


# Common source files and CFLAGS across all platforms and cores
SRCS_m4 = app_dctrlConfigure.c \
		  app_dssConfigure.c \
		  app_dss.c \
		  main.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)


ifeq ($(CORE),m4)
 LNKCMD_FILE = lnk_m4.cmd
endif

#LNKFLAGS_LOCAL_a15host += --entry Entry

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
