vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/std.h -Dxdc_target_name__=M4

CCOPTS = --endian=little -mv7M4 --float_support=vfplib --abi=eabi -q -ms --opt_for_speed=2  --program_level_compile -o3 -g --optimize_with_debug  -Dti_sysbios_family_arm_ducati_GateSmp_enableStats__D=FALSE -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE -Dti_sysbios_hal_Core_numCores__D=2 -Dti_sysbios_family_arm_m3_Hwi_enableException__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_disablePriority__D=16U -Dti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__D=0U -Dti_sysbios_family_arm_ducati_Core_initStackFlag__D=TRUE

XDC_ROOT  = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/

BUILD_DEFS = 

BIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages"

SYSBIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages"

IPC_INC    = -I"/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages"

UTILS_INC    = -I"/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages"

CC = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armcl -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/include
ASM = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armcl -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/include
AR = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armar rq

DEL = rm -f
CP = cp -f
MKDIR = mkdir -p

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asmem4 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(UTILS_INC) $<
endef


all: utils.aem4


UTILS.obj: utils/UTILS.c utils/NameServerRemoteNull.c utils/MultiProc.c utils/List.c makefile
	@-$(call RM, $@)
	@echo clem4 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(SYSBIOS_INC) $(BIOS_INC) \
	$(IPC_INC) $(UTILS_INC) \
	$(IPC_ROOT)utils/UTILS.c \
	$(IPC_ROOT)utils/NameServerRemoteNull.c \
	$(IPC_ROOT)utils/MultiProc.c \
	$(IPC_ROOT)utils/List.c \

utils.aem4: UTILS.obj 
	@-$(call RM, $@)
	@echo arem4 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, utils.aem4)
	@-$(call RM, UTILS.obj)
