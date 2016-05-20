# Makefile for device starterware hal mailbox app
APP_NAME = i2c_eeprom_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sys_config starterware_hal i2c_lib uartConsole utils_platform

# List all the components required by the application
COMP_LIST_COMMON  =  uartConsole i2c_lib sys_config starterware_hal  utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(TAKEUSERINPUT), yes)
    CFLAGS_LOCAL_COMMON += -DTAKE_USER_INPUT=1
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c

ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../../lnk_a15.cmd
endif
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../../lnk_m4.cmd
endif

#Added linker command file to support gcc
ifeq ($(CORE),a8host)
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../../lnk_gcc_a8.cmd
endif
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
