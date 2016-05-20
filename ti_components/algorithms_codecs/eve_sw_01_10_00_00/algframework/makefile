#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

OUTFILE = "lib\$(TARGET_BUILD)\libevealgframework.eve.lib"

##############################################################
EVESTARTERWARE= ..\starterware
##############################################################

##############################################################
SUBDIRS:=.\src\bam
SUBDIRS+=.\src\bam_dma_nodes
SUBDIRS+=.\src
SUBDIRS+=.\src\osal

CFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
HFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

##############################################################


##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I $(EVESTARTERWARE)
CFLAGS+= -I $(EVESTARTERWARE)/inc
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_utils
CFLAGS+= -I $(EVESTARTERWARE)/inc/edma_csl
CFLAGS+= -I $(BASE_ADDRESS_DIR)
CFLAGS+= -I .\inc
##############################################################


##############################################################
$(OUTFILE) : libfile libeveextmem
##############################################################

libeveextmem:
	gmake -C .\src\extmem -f makefile
	
clean: libeveextmemclean

libeveextmemclean:
	gmake -C .\src\extmem -f makefile clean
