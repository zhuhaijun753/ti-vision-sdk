vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/std.h -Dxdc_target_name__=M4

CCOPTS = --endian=little -mv7M4 --float_support=vfplib --abi=eabi -q -ms --opt_for_speed=2  --program_level_compile -o3   --symdebug:none --asm_define".asmfunc= " --asm_define".endasmfunc= " 

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/

BUILD_DEFS =  -Dti_sdo_ipc_MessageQ_traceFlag__D=TRUE

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


all: /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/ipc.aem4


Ipc.obj: ti/sdo/ipc/GateMP.c ti/sdo/ipc/ListMP.c ti/sdo/ipc/SharedRegion.c ti/sdo/ipc/MessageQ.c ti/sdo/ipc/Ipc.c ti/sdo/ipc/Notify.c ti/ipc/namesrv/NameServerRemoteRpmsg.c ti/ipc/remoteproc/Resource.c ti/sdo/ipc/gates/GatePeterson.c ti/sdo/ipc/gates/GatePetersonN.c ti/sdo/ipc/gates/GateMPSupportNull.c ti/sdo/ipc/heaps/HeapBufMP.c ti/sdo/ipc/heaps/HeapMemMP.c ti/sdo/ipc/heaps/HeapMultiBufMP.c ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.c ti/sdo/ipc/notifyDrivers/NotifySetupNull.c ti/sdo/ipc/notifyDrivers/NotifyDriverShm.c ti/sdo/ipc/nsremote/NameServerRemoteNotify.c ti/sdo/ipc/nsremote/NameServerMessageQ.c ti/sdo/ipc/transports/TransportShm.c ti/sdo/ipc/transports/TransportShmCircSetup.c ti/sdo/ipc/transports/TransportShmNotifySetup.c ti/sdo/ipc/transports/TransportShmCirc.c ti/sdo/ipc/transports/TransportShmNotify.c ti/sdo/ipc/transports/TransportShmSetup.c ti/sdo/ipc/transports/TransportNullSetup.c ti/sdo/ipc/gates/GateHWSpinlock.c ti/sdo/ipc/family/vayu/InterruptIpu.c ti/sdo/ipc/family/vayu/NotifyDriverMbx.c ti/sdo/ipc/family/vayu/NotifySetup.c ti/sdo/ipc/family/tda3xx/InterruptIpu.c ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c ti/sdo/ipc/family/tda3xx/NotifySetup.c ti/ipc/family/vayu/VirtQueue.c makefile
	@-$(call RM, $@)
	@echo clem4 $< ...
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
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/InterruptIpu.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/InterruptIpu.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifySetup.c \
	$(IPC_ROOT)ti/ipc/family/vayu/VirtQueue.c

ipc.aem4: Ipc.obj 
	@-$(call RM, $@)
	@echo arem4 $^ ...
	@$(AR) $@ $^

/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/ipc.aem4: ipc.aem4
	@echo cp ipc.aem4
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/ipc.aem4")
	@$(CP) ipc.aem4 "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/ipc.aem4"

clean:
	@-$(call RM, ipc.aem4)
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/ipc.aem4")
	@-$(call RM, Ipc.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/),)
    $(shell $(MKDIR) /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/smpipc/instrumented/)
endif
endif
