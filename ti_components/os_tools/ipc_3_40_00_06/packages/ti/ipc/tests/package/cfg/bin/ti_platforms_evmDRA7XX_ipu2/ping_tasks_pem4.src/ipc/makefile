vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/std.h -Dxdc_target_name__=M4

CCOPTS = --endian=little -mv7M4 --float_support=vfplib --abi=eabi -q -ms --opt_for_speed=2  --program_level_compile -o3 -g --optimize_with_debug  --gcc

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/

BUILD_DEFS =  -Dti_sdo_ipc_MessageQ_traceFlag__D=FALSE -DIpcMgr_USEDEH -DIpcMgr_IPU -DSMP -DVAYU -DRPMSG_NS_2_0 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_videoProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_hostProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_vpssProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_dspProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_ducatiCtrlBaseAddr__D=1073745920 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_mailboxBaseAddr__D=1208778752

INCS = -I/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages -I/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages

CC = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armcl -c $(CCOPTS) --output_file=$@ -I /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/include
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
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(INCS) $<
endef


all: ipc.aem4


Ipc.obj: ti/sdo/utils/NameServerRemoteNull.c ti/sdo/utils/MultiProc.c ti/sdo/utils/List.c ti/sdo/ipc/family/vayu/NotifySetup.c ti/sdo/ipc/family/vayu/InterruptIpu.c ti/ipc/remoteproc/Resource.c ti/ipc/ipcmgr/IpcMgr.c ti/ipc/family/vayu/VirtQueue.c ti/ipc/rpmsg/NameMap.c ti/ipc/rpmsg/RPMessage.c makefile
	@-$(call RM, $@)
	@echo clem4 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(INCS) \
	$(IPC_ROOT)ti/sdo/utils/NameServerRemoteNull.c \
	$(IPC_ROOT)ti/sdo/utils/MultiProc.c \
	$(IPC_ROOT)ti/sdo/utils/List.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/InterruptIpu.c \
	$(IPC_ROOT)ti/ipc/remoteproc/Resource.c \
	$(IPC_ROOT)ti/ipc/ipcmgr/IpcMgr.c \
	$(IPC_ROOT)ti/ipc/family/vayu/VirtQueue.c \
	$(IPC_ROOT)ti/ipc/rpmsg/NameMap.c \
	$(IPC_ROOT)ti/ipc/rpmsg/RPMessage.c

ipc.aem4: Ipc.obj 
	@-$(call RM, $@)
	@echo arem4 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, ipc.aem4)
	@-$(call RM, Ipc.obj)
