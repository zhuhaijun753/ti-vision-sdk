
##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "..\..\..\starterware"

EVEKERNELDB=     "..\..\..\kernels"
EVE_COMMON_DIR= "..\..\..\common"
##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src
SUBDIRS+= .\src\bam_helper

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\lib\$(TARGET_BUILD)\libeveBinImageToList.eve.lib
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
CFLAGS += -I ../../../kernels/imgsiglib/vcop_binary_masking/bam_helper
CFLAGS += -I ../../../kernels/imgsiglib/vcop_bin_image_to_list/bam_helper
CFLAGS += -I ../../../kernels/imgsiglib/vcop_select_list_elements/bam_helper
CFLAGS += -I src/bam_helper
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LIBDIR =  ".\lib\$(TARGET_BUILD)"
OUTDIR =  ".\elf_out"

$(OUTFILE) : libfile
##############################################################

