
XOPTS = -I"/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/" -Dxdc_target_types__=/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/std.h -Dxdc_target_name__=M4

vpath % /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/sysbios/
vpath %.c /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

CCOPTS    = --endian=little -mv7M4 --float_support=vfplib --abi=eabi -q -ms --opt_for_speed=2  --program_level_compile -o3 -g --optimize_with_debug  -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE -Dti_sysbios_family_arm_ducati_GateDualCore_enableStats__D=FALSE -Dti_sysbios_hal_Core_numCores__D=2 -Dti_sysbios_family_arm_m3_Hwi_enableException__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_disablePriority__D=16U -Dti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__D=0U -Dti_sysbios_family_arm_ducati_Core_initStackFlag__D=TRUE

XDC_ROOT  = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/

BIOS_ROOT = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/sysbios/

BIOS_DEFS =  -Dti_sysbios_BIOS_swiEnabled__D=TRUE -Dti_sysbios_BIOS_taskEnabled__D=TRUE -Dti_sysbios_BIOS_clockEnabled__D=TRUE -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=TRUE -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS -Dti_sysbios_BIOS_smpEnabled__D=FALSE -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_knl_Swi_numPriorities__D=16 -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=FALSE -Dti_sysbios_knl_Task_numPriorities__D=16 -Dti_sysbios_knl_Task_checkStackFlag__D=TRUE -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_USER -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC -Dti_sysbios_hal_Core_delegate_getId=ti_sysbios_family_arm_ducati_Core_getId__E -Dti_sysbios_hal_Core_delegate_interruptCore=ti_sysbios_family_arm_ducati_Core_interruptCore__E -Dti_sysbios_hal_Core_delegate_lock=ti_sysbios_family_arm_ducati_Core_lock__E -Dti_sysbios_hal_Core_delegate_unlock=ti_sysbios_family_arm_ducati_Core_unlock__E -Dti_sysbios_hal_Core_numCores__D=2 -Dti_sysbios_family_arm_ducati_Core_numCores__D=2 -Dti_sysbios_utils_Load_taskEnabled__D=TRUE -Dti_sysbios_utils_Load_swiEnabled__D=FALSE -Dti_sysbios_utils_Load_hwiEnabled__D=FALSE -Dti_sysbios_family_arm_m3_Hwi_dispatcherSwiSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherTaskSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherAutoNestingSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherIrpTrackingSupport__D=TRUE -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE -Dti_sysbios_knl_Semaphore_supportsPriority__D=TRUE

BIOS_INC  = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/"

TARGET_INC = -I"/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/"

INCS = $(BIOS_INC) $(TARGET_INC)  

CC = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armcl -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/include
ASM = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armcl -c $(CCOPTS) -I /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/include
AR = /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5/bin/armar rq

DEL = rm -f
CP = cp -f

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asmem4 $< ...
	@$(ASM) $(BIOS_DEFS) $(XOPTS) $(INCS) $<
endef

all: sysbios.aem4

m3_Hwi_asm.obj: family/arm/m3/Hwi_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=m3_Hwi_asm.obj

m3_Hwi_asm_switch.obj: family/arm/m3/Hwi_asm_switch.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=m3_Hwi_asm_switch.obj

m3_IntrinsicsSupport_asm.obj: family/arm/m3/IntrinsicsSupport_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=m3_IntrinsicsSupport_asm.obj

m3_TaskSupport_asm.obj: family/arm/m3/TaskSupport_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=m3_TaskSupport_asm.obj

dmtimer_Timer_asm.obj: timers/dmtimer/Timer_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=dmtimer_Timer_asm.obj

ducati_Core_asm.obj: family/arm/ducati/Core_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=ducati_Core_asm.obj

ducati_CTM_asm.obj: family/arm/ducati/CTM_asm.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) --output_file=ducati_CTM_asm.obj


BIOS.obj: BIOS.c knl/Clock.c knl/Idle.c knl/Intrinsics.c knl/Queue.c knl/Semaphore.c knl/Swi.c knl/Swi_andn.c knl/Task.c gates/GateHwi.c gates/GateSwi.c gates/GateMutexPri.c gates/GateMutex.c syncs/SyncSem.c hal/Cache.c hal/Core.c hal/Hwi.c hal/Hwi_stack.c hal/Hwi_startup.c hal/Timer.c heaps/HeapBuf.c heaps/HeapMem.c xdcruntime/GateThreadSupport.c family/arm/m3/Hwi.c family/arm/m3/TaskSupport.c timers/dmtimer/Timer.c family/shared/vayu/IntXbar.c family/shared/vayu/TimerSupport.c family/arm/ducati/Core.c family/arm/ducati/GateDualCore.c family/arm/ducati/Timer.c family/arm/ducati/TimestampProvider.c family/arm/ducati/Wugen.c hal/unicache/Cache.c hal/ammu/AMMU.c makefile
	@-$(call RM, $@)
	@echo clem4 $< ...
	@$(CC) $(BIOS_DEFS) $(XOPTS) $(INCS) \
	$(BIOS_ROOT)BIOS.c \
	$(BIOS_ROOT)knl/Clock.c \
	$(BIOS_ROOT)knl/Idle.c \
	$(BIOS_ROOT)knl/Intrinsics.c \
	$(BIOS_ROOT)knl/Queue.c \
	$(BIOS_ROOT)knl/Semaphore.c \
	$(BIOS_ROOT)knl/Swi.c \
	$(BIOS_ROOT)knl/Swi_andn.c \
	$(BIOS_ROOT)knl/Task.c \
	$(BIOS_ROOT)gates/GateHwi.c \
	$(BIOS_ROOT)gates/GateSwi.c \
	$(BIOS_ROOT)gates/GateMutexPri.c \
	$(BIOS_ROOT)gates/GateMutex.c \
	$(BIOS_ROOT)syncs/SyncSem.c \
	$(BIOS_ROOT)hal/Cache.c \
	$(BIOS_ROOT)hal/Core.c \
	$(BIOS_ROOT)hal/Hwi.c \
	$(BIOS_ROOT)hal/Hwi_stack.c \
	$(BIOS_ROOT)hal/Hwi_startup.c \
	$(BIOS_ROOT)hal/Timer.c \
	$(BIOS_ROOT)heaps/HeapBuf.c \
	$(BIOS_ROOT)heaps/HeapMem.c \
	$(BIOS_ROOT)xdcruntime/GateThreadSupport.c \
	$(BIOS_ROOT)family/arm/m3/Hwi.c \
	$(BIOS_ROOT)family/arm/m3/TaskSupport.c \
	$(BIOS_ROOT)timers/dmtimer/Timer.c \
	$(BIOS_ROOT)family/shared/vayu/IntXbar.c \
	$(BIOS_ROOT)family/shared/vayu/TimerSupport.c \
	$(BIOS_ROOT)family/arm/ducati/Core.c \
	$(BIOS_ROOT)family/arm/ducati/GateDualCore.c \
	$(BIOS_ROOT)family/arm/ducati/Timer.c \
	$(BIOS_ROOT)family/arm/ducati/TimestampProvider.c \
	$(BIOS_ROOT)family/arm/ducati/Wugen.c \
	$(BIOS_ROOT)hal/unicache/Cache.c \
	$(BIOS_ROOT)hal/ammu/AMMU.c \

sysbios.aem4: BIOS.obj m3_Hwi_asm.obj m3_Hwi_asm_switch.obj m3_IntrinsicsSupport_asm.obj m3_TaskSupport_asm.obj dmtimer_Timer_asm.obj ducati_Core_asm.obj ducati_CTM_asm.obj
	@-$(call RM, $@)
	@echo arem4 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, sysbios.aem4)
	@-$(call RM, BIOS.obj)
	@-$(call RM, m3_Hwi_asm.obj)
	@-$(call RM, m3_Hwi_asm_switch.obj)
	@-$(call RM, m3_IntrinsicsSupport_asm.obj)
	@-$(call RM, m3_TaskSupport_asm.obj)
	@-$(call RM, dmtimer_Timer_asm.obj)
	@-$(call RM, ducati_Core_asm.obj)
	@-$(call RM, ducati_CTM_asm.obj)
