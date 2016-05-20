# Makefile for Audio Platform

MODULE_NAME = bsp_audio

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc edma starterware starterware_hal bsp

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = bsp_common bsp_osal bsp_devices

MODULE_SRC_BASE_PATH := $(bsp_PATH)/src/audio

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = bsp_audio.c

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(BSP_CFLAGS)

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
