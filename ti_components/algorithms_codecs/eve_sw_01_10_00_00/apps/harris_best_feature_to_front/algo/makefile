
##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "..\..\..\starterware"

EVEKERNELDB=     "..\..\..\kernels"
EVE_COMMON_DIR= "..\..\..\common"
EVEKERNELCOMMON=     "..\..\..\kernels\common"

##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\lib\$(TARGET_BUILD)\libeveHarrisBestFeatureToFront.eve.lib
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

CFLAGS+= -I $(EVE_COMMON_DIR)
CFLAGS+= -I $(EVEKERNELCOMMON)
CFLAGS += -I../../../kernels/vlib/vcop_multipoint_harrisScore_u16/bam_helper
CFLAGS += -I../../../kernels/vlib/blockSortU32/bam_helper
CFLAGS += -I../../../kernels/vlib/vcop_prune_big_list/bam_helper
CFLAGS += -I../../../kernels/vlib/vcop_extract_bit_field_u32/bam_helper
CFLAGS += -I../../../kernels/vlib/blockSortU32/inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LIBDIR =  ".\lib\$(TARGET_BUILD)"
OUTDIR =  ".\elf_out"

$(OUTFILE) : libfile
##############################################################

