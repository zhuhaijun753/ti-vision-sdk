#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK = "..\..\..\algframework"
EVESTARTERWARE  = "..\..\..\starterware"

EVEKERNELDB     = "..\..\..\kernels"
EVEALGORITHMS   = "..\..\..\apps"
EVE_COMMON_DIR  = "..\..\..\common"

ALGINCPATH = $(EVEALGORITHMS)\morphology\algo\inc
ALGLIBPATH = $(EVEALGORITHMS)\morphology\algo\lib\$(TARGET_BUILD)
##############################################################


##############################################################
#SUBDIRS = .\src
SUBDIRS= ..\..\..\common

CFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += .\src\morphology_tb.c
CFILES += .\src\report_utils.c
CFILES += .\src\morphology_config.c

CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES  = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE =.\elf_out\test_eveMorphology.eve.out
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(EVE_COMMON_DIR)
CFLAGS+= -I $(EVEALGFRAMEWORK)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_utils
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_csl

CFLAGS+= -I $(EVEKERNELDB)\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_grayscale_morphology_flat\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_dilate_cross\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_dilate_mask\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_dilate_square\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_erode_cross\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_erode_mask\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_erode_square\inc
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_vec_bin_image_morph_diff\inc

CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)

##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
LDFLAGS+= -l "$(ALGLIBPATH)\libeveMorphology.eve.lib"
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

