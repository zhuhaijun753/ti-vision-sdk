#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
ifeq ($(wildcard $(EDMA3_LLD_ROOT)),)
$(error You must define EDMA3_LLD_ROOT!)
endif

##############################################################
DMAUTILS=    "..\..\..\dmautils"
DSP_COMMON_DIR= "..\..\common"
DSP_MODULES = "..\..\ti_object_detection"

##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src
SUBDIRS+= ..\..\common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\out\test_object_detection_algo.out
##############################################################

##############################################################
include ..\..\makerules_dsp.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ..\inc
CFLAGS+= -I ..\tracker\inc
CFLAGS+= -I $(XDAIS_PATH)\packages
CFLAGS+= -I $(DSP_COMMON_DIR)
CFLAGS+= -I $(DMAUTILS)\inc
CFLAGS+= -I $(DMAUTILS)\inc\edma_utils
CFLAGS+= -I $(DMAUTILS)\inc\edma_csl
CFLAGS+= -I $(EDMA3_LLD_ROOT)\packages\ti\sdo\edma3\rm
CFLAGS+= -I $(EDMA3_LLD_ROOT)\packages
CFLAGS+= -I $(MATHLIB_INSTALL_DIR)\packages
CFLAGS+= -I $(MATHLIB_INSTALL_DIR)\packages\ti\mathlib

CFLAGS+= -I $(DSP_MODULES)\ti_object_detection\algo\inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
DMAUTILS_LIB  := $(DMAUTILS)\libs\pc_dmautils.lib
else
DMAUTILS_LIB  := $(DMAUTILS)\libs\dsp_dmautils.lib
endif

LDFLAGS += -l $(DMAUTILS_LIB)

ifneq ($(TARGET_PLATFORM) , PC)
  LDFLAGS+= -cr -x
  LDFLAGS+= -l "$(EDMA3_LLD_ROOT)\packages\ti\sdo\edma3\rm\lib\tda3xx-evm\66\$(TARGET_BUILD)\edma3_lld_rm.ae66"
endif

LDFLAGS+= -l $(DSP_TOOLS)\lib\rts6600_elf.lib
ifeq ($(TARGET_PLATFORM) , PC)
else
LDFLAGS+= -l $(MATHLIB_INSTALL_DIR)\packages\ti\mathlib\lib\mathlib.lib
endif
LDFLAGS+= -l "$(DSP_MODULES)\lib\object_detection_algo.lib"
LDFLAGS+= -l ".\linker.cmd"

##############################################################


##############################################################
OUTDIR =  ".\out"

$(OUTFILE) : outfile
##############################################################

