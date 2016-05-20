vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/std.h -Dxdc_target_name__=ARP32

CCOPTS = --mem_model:data=far_aggregates --silicon_version=v210 -q -en_func_subsections  --program_level_compile -o3 -g  --symdebug:none --asm_define".asmfunc= " --asm_define".endasmfunc= " 

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/

BUILD_DEFS =  -Dxdc_runtime_Assert_DISABLE_ALL -Dxdc_runtime_Log_DISABLE_ALL -Dti_sdo_ipc_MessageQ_traceFlag__D=FALSE

INCS = -I/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages -I/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages

CC = /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/bin/cl-arp32 -c --gen_func_subsections $(CCOPTS) --output_file=$@ -I /datalocal1/ti_components/cg_tools/linux/arp32_1_0_6/include
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
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(INCS) $<
endef


all: /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/ipc.aearp32


Ipc.obj: ti/sdo/ipc/GateMP.c ti/sdo/ipc/ListMP.c ti/sdo/ipc/SharedRegion.c ti/sdo/ipc/MessageQ.c ti/sdo/ipc/Ipc.c ti/sdo/ipc/Notify.c ti/ipc/namesrv/NameServerRemoteRpmsg.c ti/ipc/remoteproc/Resource.c ti/sdo/ipc/gates/GatePeterson.c ti/sdo/ipc/gates/GatePetersonN.c ti/sdo/ipc/gates/GateMPSupportNull.c ti/sdo/ipc/heaps/HeapBufMP.c ti/sdo/ipc/heaps/HeapMemMP.c ti/sdo/ipc/heaps/HeapMultiBufMP.c ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.c ti/sdo/ipc/notifyDrivers/NotifySetupNull.c ti/sdo/ipc/notifyDrivers/NotifyDriverShm.c ti/sdo/ipc/nsremote/NameServerRemoteNotify.c ti/sdo/ipc/nsremote/NameServerMessageQ.c ti/sdo/ipc/transports/TransportShm.c ti/sdo/ipc/transports/TransportShmCircSetup.c ti/sdo/ipc/transports/TransportShmNotifySetup.c ti/sdo/ipc/transports/TransportShmCirc.c ti/sdo/ipc/transports/TransportShmNotify.c ti/sdo/ipc/transports/TransportShmSetup.c ti/sdo/ipc/transports/TransportNullSetup.c ti/sdo/ipc/gates/GateHWSpinlock.c ti/sdo/ipc/family/arctic/NotifySetup.c ti/sdo/ipc/family/arctic/NotifyCircSetup.c ti/sdo/ipc/family/arctic/InterruptArp32.c ti/sdo/ipc/family/c6a8149/NotifySetup.c ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c ti/sdo/ipc/family/c6a8149/InterruptEve.c ti/sdo/ipc/family/vayu/InterruptArp32.c ti/sdo/ipc/family/vayu/NotifyDriverMbx.c ti/sdo/ipc/family/vayu/NotifySetup.c ti/sdo/ipc/family/tda3xx/InterruptArp32.c ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c ti/sdo/ipc/family/tda3xx/NotifySetup.c makefile
	@-$(call RM, $@)
	@echo clearp32 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(INCS) \
	$(IPC_ROOT)ti/sdo/ipc/GateMP.c \
	$(IPC_ROOT)ti/sdo/ipc/ListMP.c \
	$(IPC_ROOT)ti/sdo/ipc/SharedRegion.c \
	$(IPC_ROOT)ti/sdo/ipc/MessageQ.c \
	$(IPC_ROOT)ti/sdo/ipc/Ipc.c \
	$(IPC_ROOT)ti/sdo/ipc/Notify.c \
	$(IPC_ROOT)ti/ipc/namesrv/NameServerRemoteRpmsg.c \
	$(IPC_ROOT)ti/ipc/remoteproc/Resource.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GatePeterson.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GatePetersonN.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateMPSupportNull.c \
	$(IPC_ROOT)ti/sdo/ipc/heaps/HeapBufMP.c \
	$(IPC_ROOT)ti/sdo/ipc/heaps/HeapMemMP.c \
	$(IPC_ROOT)ti/sdo/ipc/heaps/HeapMultiBufMP.c \
	$(IPC_ROOT)ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.c \
	$(IPC_ROOT)ti/sdo/ipc/notifyDrivers/NotifySetupNull.c \
	$(IPC_ROOT)ti/sdo/ipc/notifyDrivers/NotifyDriverShm.c \
	$(IPC_ROOT)ti/sdo/ipc/nsremote/NameServerRemoteNotify.c \
	$(IPC_ROOT)ti/sdo/ipc/nsremote/NameServerMessageQ.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShm.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmCircSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmNotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmCirc.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmNotify.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportNullSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateHWSpinlock.c \
	$(IPC_ROOT)ti/sdo/ipc/family/arctic/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/arctic/NotifyCircSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/arctic/InterruptArp32.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c6a8149/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c6a8149/InterruptEve.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/InterruptArp32.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/InterruptArp32.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifySetup.c

ipc.aearp32: Ipc.obj 
	@-$(call RM, $@)
	@echo arearp32 $^ ...
	@$(AR) $@ $^

/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/ipc.aearp32: ipc.aearp32
	@echo cp ipc.aearp32
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/ipc.aearp32")
	@$(CP) ipc.aearp32 "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/ipc.aearp32"

clean:
	@-$(call RM, ipc.aearp32)
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/ipc.aearp32")
	@-$(call RM, Ipc.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/),)
    $(shell $(MKDIR) /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/nonInstrumented/)
endif
endif
