
##############################################################
EVEALGFRAMEWORK=      "..\..\..\algframework"
EVESTARTERWARE=    "..\..\..\starterware"

EVEKERNELDB=     "..\..\..\kernels"
EVE_COMMON_DIR= "..\..\..\common"
EVEAPPS = "..\..\..\apps"
##############################################################


##############################################################
SUBDIRS= .\inc
SUBDIRS+= .\src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OUTFILE=.\lib\$(TARGET_BUILD)\libeveorb.eve.lib
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
CFLAGS+= -I $(EVEAPPS)\fast9_corner_detect\algo\inc
CFLAGS+= -I $(EVEAPPS)\rbrief\algo\inc
CFLAGS+= -I $(EVEAPPS)\imagePyramid_u8\algo\inc
CFLAGS+= -I $(EVEAPPS)\harris_best_feature_to_front\algo\inc
CFLAGS+= -I $(EVEAPPS)\fast9_best_feature_to_front\algo\inc
CFLAGS+= -I $(XDAIS_PACKAGES_DIR)
##############################################################


##############################################################
LIBDIR =  ".\lib\$(TARGET_BUILD)"
OUTDIR =  ".\elf_out"

$(OUTFILE) : libfile
##############################################################

