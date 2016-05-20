
XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

vpath % /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/sysbios/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

CCOPTS    = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -g  -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE -Dti_sysbios_family_c64p_Exception_enableExternalMPC__D=FALSE -Dti_sysbios_family_c64p_Exception_enablePrint__D=TRUE -Dti_sysbios_hal_Core_numCores__D=1

XDC_ROOT  = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

BIOS_ROOT = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/sysbios/

BIOS_DEFS =  -Dti_sysbios_BIOS_swiEnabled__D=TRUE -Dti_sysbios_BIOS_taskEnabled__D=TRUE -Dti_sysbios_BIOS_clockEnabled__D=TRUE -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=TRUE -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Swi_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Task_DISABLE_ALL_HOOKS -Dti_sysbios_BIOS_smpEnabled__D=FALSE -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_knl_Swi_numPriorities__D=16 -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=FALSE -Dti_sysbios_knl_Task_numPriorities__D=16 -Dti_sysbios_knl_Task_checkStackFlag__D=TRUE -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_USER -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC -Dti_sysbios_hal_Core_delegate_getId=ti_sysbios_hal_CoreNull_getId__E -Dti_sysbios_hal_Core_delegate_interruptCore=ti_sysbios_hal_CoreNull_interruptCore__E -Dti_sysbios_hal_Core_delegate_lock=ti_sysbios_hal_CoreNull_lock__E -Dti_sysbios_hal_Core_delegate_unlock=ti_sysbios_hal_CoreNull_unlock__E -Dti_sysbios_hal_Core_numCores__D=1 -Dti_sysbios_hal_CoreNull_numCores__D=1 -Dti_sysbios_utils_Load_taskEnabled__D=TRUE -Dti_sysbios_utils_Load_swiEnabled__D=FALSE -Dti_sysbios_utils_Load_hwiEnabled__D=FALSE -Dti_sysbios_family_c64p_Hwi_dispatcherSwiSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherTaskSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherAutoNestingSupport__D=TRUE -Dti_sysbios_family_c64p_Hwi_dispatcherIrpTrackingSupport__D=TRUE -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE -Dti_sysbios_knl_Semaphore_supportsPriority__D=TRUE

BIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/"

TARGET_INC = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/"

INCS = $(BIOS_INC) $(TARGET_INC)  

CC = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/cl6x -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/include
ASM = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/cl6x -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/include
AR = /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2/bin/ar6x rq

DEL = rm -f
CP = cp -f

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BIOS_DEFS) $(XOPTS) $(INCS) $<
endef

all: sysbios.ae66

c64p_Exception_asm.obj: family/c64p/Exception_asm.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Exception_asm.obj

c64p_Hwi_asm.obj: family/c64p/Hwi_asm.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_asm.obj

c64p_Hwi_asm_switch.obj: family/c64p/Hwi_asm_switch.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_asm_switch.obj

c64p_Hwi_disp_always.obj: family/c64p/Hwi_disp_always.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c64p_Hwi_disp_always.obj

dmtimer_Timer_asm.obj: timers/dmtimer/Timer_asm.s64P makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=dmtimer_Timer_asm.obj

c62_TaskSupport_asm.obj: family/c62/TaskSupport_asm.s62 makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=c62_TaskSupport_asm.obj


BIOS.obj: BIOS.c family/c64p/EventCombiner.c family/c64p/Exception.c family/c64p/Hwi.c family/c64p/Hwi_startup.c family/c64p/TimestampProvider.c knl/Clock.c knl/Idle.c knl/Intrinsics.c knl/Queue.c knl/Semaphore.c knl/Swi.c knl/Swi_andn.c knl/Task.c heaps/HeapBuf.c heaps/HeapMem.c gates/GateHwi.c gates/GateAll.c gates/GateSwi.c gates/GateMutexPri.c gates/GateMutex.c syncs/SyncSem.c family/c66/Cache.c hal/Cache.c hal/Core.c hal/CoreNull.c hal/Hwi.c hal/Hwi_stack.c hal/Hwi_startup.c timers/dmtimer/Timer.c family/shared/vayu/IntXbar.c family/shared/vayu/TimerSupport.c xdcruntime/GateThreadSupport.c family/c62/TaskSupport.c family/c62/IntrinsicsSupport.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BIOS_DEFS) $(XOPTS) $(INCS) \
	$(BIOS_ROOT)BIOS.c \
	$(BIOS_ROOT)family/c64p/EventCombiner.c \
	$(BIOS_ROOT)family/c64p/Exception.c \
	$(BIOS_ROOT)family/c64p/Hwi.c \
	$(BIOS_ROOT)family/c64p/Hwi_startup.c \
	$(BIOS_ROOT)family/c64p/TimestampProvider.c \
	$(BIOS_ROOT)knl/Clock.c \
	$(BIOS_ROOT)knl/Idle.c \
	$(BIOS_ROOT)knl/Intrinsics.c \
	$(BIOS_ROOT)knl/Queue.c \
	$(BIOS_ROOT)knl/Semaphore.c \
	$(BIOS_ROOT)knl/Swi.c \
	$(BIOS_ROOT)knl/Swi_andn.c \
	$(BIOS_ROOT)knl/Task.c \
	$(BIOS_ROOT)heaps/HeapBuf.c \
	$(BIOS_ROOT)heaps/HeapMem.c \
	$(BIOS_ROOT)gates/GateHwi.c \
	$(BIOS_ROOT)gates/GateAll.c \
	$(BIOS_ROOT)gates/GateSwi.c \
	$(BIOS_ROOT)gates/GateMutexPri.c \
	$(BIOS_ROOT)gates/GateMutex.c \
	$(BIOS_ROOT)syncs/SyncSem.c \
	$(BIOS_ROOT)family/c66/Cache.c \
	$(BIOS_ROOT)hal/Cache.c \
	$(BIOS_ROOT)hal/Core.c \
	$(BIOS_ROOT)hal/CoreNull.c \
	$(BIOS_ROOT)hal/Hwi.c \
	$(BIOS_ROOT)hal/Hwi_stack.c \
	$(BIOS_ROOT)hal/Hwi_startup.c \
	$(BIOS_ROOT)timers/dmtimer/Timer.c \
	$(BIOS_ROOT)family/shared/vayu/IntXbar.c \
	$(BIOS_ROOT)family/shared/vayu/TimerSupport.c \
	$(BIOS_ROOT)xdcruntime/GateThreadSupport.c \
	$(BIOS_ROOT)family/c62/TaskSupport.c \
	$(BIOS_ROOT)family/c62/IntrinsicsSupport.c \

sysbios.ae66: BIOS.obj c64p_Exception_asm.obj c64p_Hwi_asm.obj c64p_Hwi_asm_switch.obj c64p_Hwi_disp_always.obj dmtimer_Timer_asm.obj c62_TaskSupport_asm.obj
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, sysbios.ae66)
	@-$(call RM, BIOS.obj)
	@-$(call RM, c64p_Exception_asm.obj)
	@-$(call RM, c64p_Hwi_asm.obj)
	@-$(call RM, c64p_Hwi_asm_switch.obj)
	@-$(call RM, c64p_Hwi_disp_always.obj)
	@-$(call RM, dmtimer_Timer_asm.obj)
	@-$(call RM, c62_TaskSupport_asm.obj)
