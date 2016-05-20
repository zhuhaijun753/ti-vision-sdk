#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


#include Rules.make
# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu
# Default CORE
# Supported values: dsp, eve
CORE ?= dsp
TARGET_PLATFORM ?= dsp
ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

SOURCE_DIR := drivers\src
CRED_SRC_DIR := drivers\devices\$(TARGET_SOC)\cred\src\$(CORE)1
CRED_INC_DIR := drivers\devices\$(TARGET_SOC)\cred\inc\$(CORE)1

CFILES +=$(SOURCE_DIR)\dma_funcs.c
CFILES +=$(SOURCE_DIR)\dma_resource_allocator.c
CFILES +=$(SOURCE_DIR)\edma3lld_support.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils_autoincrement.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils_autoincrement_1d.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils_memcpy.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils_scatterGather.c
CFILES +=$(SOURCE_DIR)\edma_utils\edma_utils_state.c

OUTFILE = $(DMAUTILS_LIB)

include rules.mk

CFLAGS += -I $(BASE_ADDRESS_DIR) 
CFLAGS += -I .\drivers\inc
CFLAGS += -I .\inc
CFLAGS += -I $(CRED_INC_DIR)
CFLAGS += -I .\inc\edma_utils
CFLAGS += -I .\inc\edma_csl
CFLAGS += -I $(EDMA3_LLD_ROOT)\packages\ti\sdo\edma3\rm
CFLAGS += -I $(EDMA3_LLD_ROOT)\packages
ifneq ($(TARGET_PLATFORM) , PC)
CFLAGS += -D USE_EDMA3LLD
endif
##############################################################

$(OUTFILE) : libfile
