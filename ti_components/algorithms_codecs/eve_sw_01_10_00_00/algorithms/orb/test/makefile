#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "../../../starterware"


EVEKERNELDB=     "..\..\..\kernels"
EVEAPPS = "..\..\..\apps"
EVEALGORITHMS = "..\..\..\algorithms"

##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src
SUBDIRS+= ..\..\..\common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\elf_out\test_orb.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ..\..\..\common
CFLAGS+= -I $(EVEALGFRAMEWORK)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_utils
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_csl

CFLAGS+= -I $(EVEKERNELDB)\inc

CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I $(EVEALGORITHMS)\orb\algo\inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
LDFLAGS+= -l "$(EVEAPPS)\fast9_corner_detect\algo\lib\$(TARGET_BUILD)\libeveFast9CornerDetect.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)\rbrief\algo\lib\$(TARGET_BUILD)\libeveRbrief.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)\imagePyramid_u8\algo\lib\$(TARGET_BUILD)\libeveImagePyramid_u8.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)\harris_best_feature_to_front\algo\lib\$(TARGET_BUILD)\libeveHarrisBestFeatureToFront.eve.lib"
LDFLAGS+= -l "$(EVEAPPS)\fast9_best_feature_to_front\algo\lib\$(TARGET_BUILD)\libeveFAST9BestFeatureToFront.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\orb\algo\lib\$(TARGET_BUILD)\libeveorb.eve.lib"
LDFLAGS+= -l "$(EVEALGFRAMEWORK)\lib\$(TARGET_BUILD)\libevealgframework.eve.lib"
LDFLAGS+= -l "$(EVEALGFRAMEWORK)\lib\$(TARGET_BUILD)\libeveextmem.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)\lib\$(TARGET_BUILD)\libevekernels.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)\lib\$(TARGET_BUILD)\libevenatckernels.eve.lib"

LDFLAGS+= -l ".\linker.cmd"
##############################################################


##############################################################
OUTDIR =  ".\elf_out"

$(OUTFILE) : outfile
##############################################################

