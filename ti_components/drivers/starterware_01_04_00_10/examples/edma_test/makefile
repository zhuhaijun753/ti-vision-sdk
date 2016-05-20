# Makefile for device starterware hal mailbox app

APP_NAME = edma_test_app

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal uartConsole sys_config utils_platform

# List all the components required by the application
COMP_LIST_COMMON = uartConsole starterware_hal sys_config utils_platform

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = main.c dma_test.c dma_chain.c dma_link.c qdma_test.c qdma_link.c dma_polled.c dma_ping_pong_test.c

# a15host
ifeq ($(CORE),a15host)
 LNKCMD_FILE = ../lnk_a15.cmd
endif
ifeq ($(CORE),m4)
 LNKCMD_FILE = ../lnk_m4.cmd
endif
ifeq ($(CORE),c66x)
 LNKCMD_FILE = ../lnk_dsp.cmd
endif

#Added linker command file to support gcc
ifeq ($(CORE),a8host)
ifeq ($(TOOLCHAIN_a8),cgt)
 LNKCMD_FILE = ../lnk_a8.cmd
endif
ifeq ($(TOOLCHAIN_a8),gcc)
 LNKCMD_FILE = ../lnk_gcc_a8.cmd
endif
endif

ifeq ($(CORE),m3vpss)
 LNKCMD_FILE = ../lnk_m3vpss.cmd
endif
ifeq ($(CORE),m3video)
 LNKCMD_FILE = ../lnk_m3video.cmd
endif
ifeq ($(CORE),c674x)
 LNKCMD_FILE = ../lnk_dsp.cmd
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
