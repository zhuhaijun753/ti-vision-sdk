#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************

OUTFILE = "..\..\lib\$(TARGET_BUILD)\libeveextmem.eve.lib"

##############################################################
SUBDIRS = .

CFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES += $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))

HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))
##############################################################



##############################################################
ifndef EVE_SW_ROOT
$(error You must define EVE_SW_ROOT!)
endif 
include $(EVE_SW_ROOT)\makerules\makerules_eve.mk

#used inside makerules, but okay to define it afterwards
CFLAGS+= -I ..\..\inc
##############################################################

LIBDIR=..\..\lib

##############################################################
$(OUTFILE) : libdirectory libfile
##############################################################

libdirectory:
	(cd $(LIBDIR)) || (mkdir $(LIBDIR))
