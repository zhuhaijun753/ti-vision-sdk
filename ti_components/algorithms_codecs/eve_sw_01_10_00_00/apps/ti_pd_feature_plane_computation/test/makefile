#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "../../../starterware"


EVEKERNELDB=     "..\..\..\kernels"
EVEALGORITHMS = "..\..\..\apps"


ALGINCPATH= $(EVEALGORITHMS)\ti_pd_feature_plane_computation\algo\inc
ALGLIBPATH= $(EVEALGORITHMS)\ti_pd_feature_plane_computation\algo\lib\$(TARGET_BUILD)
##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src
SUBDIRS+= ..\..\..\common

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES += ../../../common/configparser.c
CFILES += ../../../common/ti_mem_manager.c
CFILES += ../../../common/boot_arp32.asm
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\elf_out\test_eveFeaturePlaneComputation.eve.out
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

CFLAGS+= -I $(ALGINCPATH)
CFLAGS+= -I $(EVEKERNELDB)
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
CFLAGS += -I ../../yuv_padding/algo/inc
CFLAGS+= -I $(EVEKERNELDB)\imgsiglib\vcop_yuv_scalar\inc
CFLAGS += -I ../../yuv_scalar/algo/inc
CFLAGS += -I ../../filter_2d/algo/inc

##############################################################


##############################################################
LDFLAGS+= -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
LDFLAGS+= -l "$(ALGLIBPATH)\libeveFeaturePlaneComputation.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\yuv_padding\algo\lib\$(TARGET_BUILD)\libeveYUVPAdding.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\yuv_scalar\algo\lib\$(TARGET_BUILD)\libeveYUVScalar.eve.lib"
LDFLAGS+= -l "$(EVEALGORITHMS)\filter_2d\algo\lib\$(TARGET_BUILD)\libeveFilter2D.eve.lib"
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

