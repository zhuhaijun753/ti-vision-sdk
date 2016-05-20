vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/std.h -Dxdc_target_name__=ARP32

CCOPTS = --mem_model:data=far_aggregates --silicon_version=v210 -q -en_func_subsections  --program_level_compile -o3 -g  --symdebug:none --asm_define".asmfunc= " --asm_define".endasmfunc= " 

XDC_ROOT  = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/

BUILD_DEFS =  -Dxdc_runtime_Assert_DISABLE_ALL -Dxdc_runtime_Log_DISABLE_ALL

BIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages"

SYSBIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages"

IPC_INC    = -I"/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages"

UTILS_INC    = -I"/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages"

CC = /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/bin/cl-arp32 -c --gen_func_subsections $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/include
ASM = /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/bin/cl-arp32 -c --gen_func_subsections $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/include
AR = /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/bin/ar-arp32 rq

DEL = rm -f
CP = cp -f
MKDIR = mkdir -p

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asmearp32 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(UTILS_INC) $<
endef


all: /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/utils.aearp32


UTILS.obj: utils/UTILS.c utils/MultiProc.c utils/List.c utils/NameServerRemoteNull.c utils/NameServer.c makefile
	@-$(call RM, $@)
	@echo clearp32 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(SYSBIOS_INC) $(BIOS_INC) \
	$(IPC_INC) $(UTILS_INC) \
	$(IPC_ROOT)utils/UTILS.c \
	$(IPC_ROOT)utils/MultiProc.c \
	$(IPC_ROOT)utils/List.c \
	$(IPC_ROOT)utils/NameServerRemoteNull.c \
	$(IPC_ROOT)utils/NameServer.c \

utils.aearp32: UTILS.obj 
	@-$(call RM, $@)
	@echo arearp32 $^ ...
	@$(AR) $@ $^

/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/utils.aearp32: utils.aearp32
	@echo cp utils.aearp32
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/utils.aearp32")
	@$(CP) utils.aearp32 "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/utils.aearp32"

clean:
	@-$(call RM, utils.aearp32)
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/utils.aearp32")
	@-$(call RM, UTILS.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/),)
    $(shell $(MKDIR) /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/lib/utils/nonInstrumented/)
endif
endif
