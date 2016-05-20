#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=eve
TARGET_NAME:=edma_eve_double_buffering_alias_view

include ../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

CFLAGS += -I../inc
CFLAGS += -I$(STARTERWARE_DIR)/inc/edma_utils
CFLAGS += -I$(STARTERWARE_DIR)/inc/edma_csl

LOCAL_SRC = main.c CurrentLuma0.c $(COMMON_DIR)/$(TARGET_SOC)/boot_arp32.asm
KERNEL_SRC = vcop_copy_data_per_8_kernel.k

# 'target' rules
all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean kernel_functions local_functions
	$(LN) -cr $(wildcard $(OBJ_DIR)/*.obj) -l"$(CORE_LIB)" -l"$(LIB)" -l"$(LINKER_CMD)" -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)"

kernel_functions : $(KERNEL_SRC)
	$(CC) $(CFLAGS) -kh --vc $(KERNEL_SRC) --obj_directory "$(OBJ_DIR)"

clean :
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map ./*.h ./*_kernel.c

