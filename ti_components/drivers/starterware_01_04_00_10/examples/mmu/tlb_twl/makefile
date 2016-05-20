# Makefile for device starterware hal mailbox app

APP_NAME = mmu_tlb_twl_app

SRCDIR = src
INCDIR = inc

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = starterware_hal sys_config

# List all the components required by the application
COMP_LIST_COMMON = starterware_hal sys_config

# Common source files and CFLAGS across all platforms and cores
SRCS_c674x = main_dsp.c
SRCS_c66x  = main_dsp.c

SRCS_arp32_1 = main_arp32.c

CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

ifeq ($(CORE),c674x)
 LNKCMD_FILE = ../../lnk_dsp.cmd
endif

ifeq ($(CORE),c66x)
 LNKCMD_FILE = ../../lnk_dsp.cmd
endif

# arp32_1
ifeq ($(CORE),arp32_1)
 LNKCMD_FILE = ../../lnk_arp32.cmd
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
