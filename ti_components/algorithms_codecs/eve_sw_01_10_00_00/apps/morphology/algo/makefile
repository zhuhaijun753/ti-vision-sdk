
##############################################################
EVEALGFRAMEWORK = "..\..\..\algframework"
EVESTARTERWARE  = "..\..\..\starterware"

EVEKERNELDB     = "..\..\..\kernels"
EVE_COMMON_DIR  = "..\..\..\common"
##############################################################


##############################################################
SUBDIRS = .\inc
SUBDIRS+= .\src

CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
HFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

ifneq ($(TARGET_PLATFORM) , PC)
CFILES := $(filter-out %grayscale_morphology_host.c,$(CFILES))
HFILES := $(filter-out %grayscale_morphology_host.h,$(HFILES))
endif

OUTFILE=.\lib\$(TARGET_BUILD)\libeveMorphology.eve.lib
##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I .\inc
CFLAGS+= -I $(EVEALGFRAMEWORK)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_csl
CFLAGS+= -I $(EVESTARTERWARE)\inc\edma_utils

CFLAGS+= -I $(EVEKERNELDB)\inc
CFLAGS+= -I $(EVEKERNELDB)\common
CFLAGS+= -I $(EVEKERNELDB)\vlib\vcop_grayscale_morphology_flat\inc

CFLAGS+= -I $(EVE_COMMON_DIR)
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LIBDIR =  ".\lib\$(TARGET_BUILD)"
OUTDIR =  ".\elf_out"

$(OUTFILE) : libfile
##############################################################

