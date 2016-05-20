#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=eve
TARGET_NAME:=edma_circ1d_eve

include ../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

CFLAGS += -I../inc
CFLAGS += -I$(STARTERWARE_DIR)/inc/edma_csl
CFLAGS += --gen_func_subsections
LOCAL_SRC = main.c eve_dma_test_data.c $(COMMON_DIR)/$(TARGET_SOC)/boot_arp32.asm

# 'target' rules
all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean local_functions
	$(LN) -cr $(wildcard $(OBJ_DIR)/*.obj) -l"$(CORE_LIB)" -l"$(LIB)" -l"$(LINKER_CMD)" -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)"


clean :
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map ./*.h ./*_kernel.c

