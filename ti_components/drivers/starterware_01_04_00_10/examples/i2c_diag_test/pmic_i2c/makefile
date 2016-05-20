# Makefile for device starterware to test pmic
APP_NAME = pmic_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files

INCLUDE_EXTERNAL_INTERFACES = sys_config starterware_hal i2c_lib uartConsole utils_platform
COMP_LIST_COMMON  =  uartConsole i2c_lib sys_config starterware_hal  utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# Common source files and CFLAGS across all platforms and cores

ifeq ($(CORE),a15host)
 SRCS_a15host = main.c
 LNKCMD_FILE = ../../lnk_a15.cmd
endif

ifeq ($(CORE),m4)
    SRCS_m4  = main.c
    LNKCMD_FILE = ../../lnk_m4.cmd
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
