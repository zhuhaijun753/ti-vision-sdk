#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "../../../starterware"


EVEKERNELDB=     "..\..\..\kernels"
EVEALGORITHMS = "..\..\..\apps"

##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= ..\..\..\common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= .\src\pyramid_lk_sof_tb.c
CFILES+= .\src\report_utils.c
CFILES+= .\src\pyramid_lk_sof_config.c

CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\elf_out\test_evepyramidLKSOF.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I inc
CFLAGS+= -I ..\algo\inc
CFLAGS+= -I ..\..\..\common
CFLAGS+= -I $(EVEALGFRAMEWORK)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_utils
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_csl

CFLAGS+= -I $(EVEKERNELDB)\inc

CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I $(EVEALGORITHMS)\pyramid_lk_tracker\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\harrisCornerDetection32\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\imagePyramid_u8\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\yuv_padding\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\fast9_best_feature_to_front\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\fast9_corner_detect\algo\inc
CFLAGS+= -I $(EVEALGORITHMS)\bin_image_to_list\algo\inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
LDFLAGS+= -l "$(EVEALGORITHMS)\pyramid_lk_tracker\algo\lib\$(TARGET_BUILD)\libevePyramidLKTracker.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\fast9_corner_detect\algo\lib\$(TARGET_BUILD)\libeveFast9CornerDetect.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\fast9_best_feature_to_front\algo\lib\$(TARGET_BUILD)\libeveFAST9BestFeatureToFront.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\harrisCornerDetection32\algo\lib\$(TARGET_BUILD)\libeveHarrisCornerDetection32.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\imagePyramid_u8\algo\lib\$(TARGET_BUILD)\libeveImagePyramid_u8.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\yuv_padding\algo\lib\$(TARGET_BUILD)\libeveYUVPAdding.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\bin_image_to_list\algo\lib\$(TARGET_BUILD)\libeveBinImageToList.eve.lib"
LDFLAGS+= -l "$(EVEALGFRAMEWORK)\lib\$(TARGET_BUILD)\libevealgframework.eve.lib"
LDFLAGS+= -l "$(EVEALGFRAMEWORK)\lib\$(TARGET_BUILD)\libeveextmem.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)\lib\$(TARGET_BUILD)\libevekernels.eve.lib"
LDFLAGS+= -l "$(EVEKERNELDB)\lib\$(TARGET_BUILD)\libevenatckernels.eve.lib"
LDFLAGS+= -l "..\..\..\algorithms\pyramid_lk_sof\algo\lib\$(TARGET_BUILD)\libevesof.eve.lib"

LDFLAGS+= -l ".\linker.cmd"
##############################################################


##############################################################
OUTDIR =  ".\elf_out"

$(OUTFILE) : outfile
##############################################################

