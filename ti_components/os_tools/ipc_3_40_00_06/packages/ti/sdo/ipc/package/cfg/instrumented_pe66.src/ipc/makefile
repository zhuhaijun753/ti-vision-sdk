vpath % /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

CCOPTS = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -o3   --symdebug:none --asm_define".asmfunc= " --asm_define".endasmfunc= " 

IPC_ROOT = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/

BUILD_DEFS =  -Dti_sdo_ipc_MessageQ_traceFlag__D=TRUE

INCS = -I/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages -I/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages

CC = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/cl6x -c $(CCOPTS) --output_file=$@ -I /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/include
ASM = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/cl6x -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/include
AR = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/ar6x rq

DEL = rm -f
CP = cp -f
MKDIR = mkdir -p

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(INCS) $<
endef


all: /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/ipc.ae66


Ipc.obj: ti/sdo/ipc/GateMP.c ti/sdo/ipc/ListMP.c ti/sdo/ipc/SharedRegion.c ti/sdo/ipc/MessageQ.c ti/sdo/ipc/Ipc.c ti/sdo/ipc/Notify.c ti/ipc/namesrv/NameServerRemoteRpmsg.c ti/ipc/remoteproc/Resource.c ti/sdo/ipc/gates/GatePeterson.c ti/sdo/ipc/gates/GatePetersonN.c ti/sdo/ipc/gates/GateMPSupportNull.c ti/sdo/ipc/heaps/HeapBufMP.c ti/sdo/ipc/heaps/HeapMemMP.c ti/sdo/ipc/heaps/HeapMultiBufMP.c ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.c ti/sdo/ipc/notifyDrivers/NotifySetupNull.c ti/sdo/ipc/notifyDrivers/NotifyDriverShm.c ti/sdo/ipc/nsremote/NameServerRemoteNotify.c ti/sdo/ipc/nsremote/NameServerMessageQ.c ti/sdo/ipc/transports/TransportShm.c ti/sdo/ipc/transports/TransportShmCircSetup.c ti/sdo/ipc/transports/TransportShmNotifySetup.c ti/sdo/ipc/transports/TransportShmCirc.c ti/sdo/ipc/transports/TransportShmNotify.c ti/sdo/ipc/transports/TransportShmSetup.c ti/sdo/ipc/transports/TransportNullSetup.c ti/sdo/ipc/family/c647x/Interrupt.c ti/sdo/ipc/family/c647x/NotifyCircSetup.c ti/sdo/ipc/family/c647x/MultiProcSetup.c ti/sdo/ipc/family/c647x/NotifySetup.c ti/sdo/ipc/gates/GateHWSem.c ti/sdo/ipc/gates/GateHWSpinlock.c ti/sdo/ipc/family/tci663x/Interrupt.c ti/sdo/ipc/family/tci663x/MultiProcSetup.c ti/sdo/ipc/family/tci663x/NotifyCircSetup.c ti/sdo/ipc/family/tci663x/NotifySetup.c ti/sdo/ipc/family/vayu/InterruptDsp.c ti/sdo/ipc/family/vayu/NotifyDriverMbx.c ti/sdo/ipc/family/vayu/NotifySetup.c ti/sdo/ipc/family/tda3xx/InterruptDsp.c ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c ti/sdo/ipc/family/tda3xx/NotifySetup.c ti/ipc/family/tci6614/Interrupt.c ti/ipc/family/tci6614/VirtQueue.c ti/ipc/family/tci6614/NotifySetup.c ti/ipc/family/tci6638/Interrupt.c ti/ipc/family/tci6638/VirtQueue.c ti/ipc/family/tci6638/NotifyCircSetup.c ti/ipc/family/vayu/VirtQueue.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
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
	$(IPC_ROOT)ti/sdo/ipc/family/c647x/Interrupt.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c647x/NotifyCircSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c647x/MultiProcSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/c647x/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateHWSem.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateHWSpinlock.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tci663x/Interrupt.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tci663x/MultiProcSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tci663x/NotifyCircSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tci663x/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/InterruptDsp.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/vayu/NotifySetup.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/InterruptDsp.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c \
	$(IPC_ROOT)ti/sdo/ipc/family/tda3xx/NotifySetup.c \
	$(IPC_ROOT)ti/ipc/family/tci6614/Interrupt.c \
	$(IPC_ROOT)ti/ipc/family/tci6614/VirtQueue.c \
	$(IPC_ROOT)ti/ipc/family/tci6614/NotifySetup.c \
	$(IPC_ROOT)ti/ipc/family/tci6638/Interrupt.c \
	$(IPC_ROOT)ti/ipc/family/tci6638/VirtQueue.c \
	$(IPC_ROOT)ti/ipc/family/tci6638/NotifyCircSetup.c \
	$(IPC_ROOT)ti/ipc/family/vayu/VirtQueue.c

ipc.ae66: Ipc.obj 
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^

/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/ipc.ae66: ipc.ae66
	@echo cp ipc.ae66
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/ipc.ae66")
	@$(CP) ipc.ae66 "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/ipc.ae66"

clean:
	@-$(call RM, ipc.ae66)
	@-$(call RM, "/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/ipc.ae66")
	@-$(call RM, Ipc.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/),)
    $(shell $(MKDIR) /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/ipc/lib/ipc/instrumented/)
endif
endif
