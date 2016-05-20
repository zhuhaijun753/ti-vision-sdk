/*
 * Copyright (c) 2014-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQueueNTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== Power.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Intrinsics.h>

#include "PowerCC2650.h"

/* driverlib header files */
#include <inc/hw_types.h>
#include <inc/hw_prcm.h>
#include <inc/hw_nvic.h>
#include <inc/hw_aon_wuc.h>
#include <inc/hw_aon_rtc.h>
#include <inc/hw_memmap.h>
#include <inc/hw_ccfg.h>
#include <inc/hw_rfc_pwr.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/pwr_ctrl.h>
#include <driverlib/prcm.h>
#include <driverlib/aon_wuc.h>
#include <driverlib/aon_ioc.h>
#include <driverlib/aon_rtc.h>
#include <driverlib/aon_event.h>
#include <driverlib/aux_wuc.h>
#include <driverlib/osc.h>
#include <driverlib/cpu.h>
#include <driverlib/vims.h>
#include <driverlib/rfc.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/driverlib_release.h>
#include <driverlib/setup.h>
#include <driverlib/ccfgread.h>

#include "package/internal/Power.xdc.h"

/*
 *  Resource database records.  Each record contains:
 *    { flags, flags2 , driverlibID}
 *
 *  flags  = type : parent1
 *  flags2 = parent2
 */
const ti_sysbios_family_arm_cc26xx_Power_ResourceRecord
    ti_sysbios_family_arm_cc26xx_Power_db[RESOURCE_END] =
{
/*  type       parent1      parent2      driverlibID
    ----      ----------   --------- ------------------- */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_TIMER0 },/* PERIPH_GPT0 */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_TIMER1 },/* PERIPH_GPT1 */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_TIMER2 },/* PERIPH_GPT2 */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_TIMER3 },/* PERIPH_GPT3 */
 { PERIPH  | DOMAIN_SERIAL, NOPARENT, PRCM_PERIPH_SSI0 },  /* PERIPH_SSI0 */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_SSI1 },  /* PERIPH_SSI1 */
 { PERIPH  | DOMAIN_SERIAL, NOPARENT, PRCM_PERIPH_UART0 }, /* PERIPH_UART0 */
 { PERIPH  | DOMAIN_SERIAL, NOPARENT, PRCM_PERIPH_I2C0 },  /* PERIPH_I2C0 */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_TRNG },  /* PERIPH_TRNG */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_GPIO },  /* PERIPH_GPIO */
 { PERIPH  | DOMAIN_PERIPH, DOMAIN_SYSBUS, PRCM_PERIPH_UDMA }, /* PERIPH_UDMA */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_CRYPTO },/* PERIPH_CRYPTO */
 { PERIPH  | DOMAIN_PERIPH, NOPARENT, PRCM_PERIPH_I2S },   /* PERIPH_I2S */
 { SPECIAL | DOMAIN_RFCORE, NOPARENT, 0 },                 /* PERIPH_RFCORE */
 { SPECIAL | NOPARENT,      NOPARENT, 1 },                 /* XOSC_HF */
 { DOMAIN  | NOPARENT,      NOPARENT, PRCM_DOMAIN_PERIPH },/* DOMAIN_PERIPH */
 { DOMAIN  | NOPARENT,      NOPARENT, PRCM_DOMAIN_SERIAL },/* DOMAIN_SERIAL */
 { DOMAIN  | NOPARENT,      NOPARENT, PRCM_DOMAIN_RFCORE },/* DOMAIN_RFCORE */
 { SPECIAL | NOPARENT,      NOPARENT, 2 }                  /* DOMAIN_SYSBUS */
};

/* resource reference count array */
volatile UInt8 ti_sysbios_family_arm_cc26xx_Power_refCount[RESOURCE_END] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* constraint counts array */
/* careful: bitmask values index to this array, be sure they are contiguous */
volatile UInt8 ti_sysbios_family_arm_cc26xx_Power_constraintCounts[
    ti_sysbios_family_arm_cc26xx_Power_NUMCONSTRAINTS] =
    { 0, 0, 0, 0, 0 };


/* * * * * * * * * * * * * * * * * APIs * * * * * * * * * * * * * * * * * */

/*
 *  ======== Power_getClockHandle ========
 */
Clock_Handle Power_getClockHandle()
{
    return (Power_Module_State_clockObj());
}

/*
 *  ======== Power_getConstraintInfo ========
 *  Get a bitmask indicating the constraints that have been registered with
 *  Power.
 */
UInt32 Power_getConstraintInfo(Void)
{
    return (Power_module->constraintsMask);
}

/*
 *  ======== Power_getDependencyCount ========
 *  Get the count of dependencies that are currently declared upon a resource.
 */
UInt32 Power_getDependencyCount(Power_Resource resourceID)
{
    return (Power_module->resourceCounts[resourceID]);
}

/*
 *  ======== Power_getTicksUntilWakeup ========
 *  Get the number of system ticks until the next scheduled wakeup event
 */
UInt32 Power_getTicksUntilWakeup(Void)
{
    return (Clock_getTicksUntilInterrupt());
}

/*
 *  ======== Power_getTransitionLatency ========
 *  Get the transition latency for a sleep state.  The latency is reported
 *  in units of Clock ticks.
 */
UInt32 Power_getTransitionLatency(Power_SleepState sleepState,
    Power_LatencyType type)
{
    UInt32 latency = 0;

    if (type == Power_RESUME) {
        if (sleepState == Power_STANDBY) {
            latency = Power_resumeTicksSTANDBY;
        }
    }
    else {
        if (sleepState == Power_STANDBY) {
            latency = Power_totalTicksSTANDBY;
        }
    }

    return (latency);
}

/*
 *  ======== Power_getTransitionState ========
 *  Get the current sleep transition state.
 */
Power_TransitionState Power_getTransitionState(Void)
{
    return (Power_module->state);
}

/*
 *  ======== Power_getXoscStartupTime ========
 *  Get the estimated crystal oscillator startup time
 */
UInt32 Power_getXoscStartupTime(UInt32 timeUntilWakeupInMs)
{
    return (OSCHF_GetStartupTime(timeUntilWakeupInMs));
}

/*
 *  ======== Power_injectCalibration ========
 *  Explicitly trigger RCOSC calibration
 */
Void Power_injectCalibration(Void)
{
    if (Power_calibrateRCOSC) {
        if (Power_initiateCalibration()) {
            /* here if AUX SMPH was available, start calibration now ... */
            Power_doCalibrate();
         }
     }
}

/*
 *  ======== Power_isStableXOSC_HF ========
 *  Check if XOSC_HF has stabilized.
 */
Bool Power_isStableXOSC_HF(Void)
{
    Bool ready = TRUE;
    UInt key;

    key = Hwi_disable();

    /* only query if HF source is ready if there is a pending change */
    if (Power_module->xoscPending) {
        ready = OSCHfSourceReady();
    }

    Hwi_restore(key);

    return (ready);
}

/*
 *  ======== Power_releaseConstraint ========
 *  Release a previously declared constraint.
 */
Void Power_releaseConstraint(Power_Constraint constraint)
{
    UInt key;
    UInt8 count;

    key = Hwi_disable();

    count = Power_module->constraintCounts[Intrinsics_maxbit(constraint)];

    Assert_isTrue(count != 0, Power_A_tooManyCallsReleaseConstraint);

    count = count - 1;

    Power_module->constraintCounts[Intrinsics_maxbit(constraint)] = count;

    if (count == 0) {
        Power_module->constraintsMask &= ~constraint;
    }

    Hwi_restore(key);
}

/*
 *  ======== Power_releaseDependency ========
 *  Release a previously declared dependency.
 */
Void Power_releaseDependency(Power_Resource resourceID)
{
    UInt8 parent;
    UInt8 count;
    UInt32 id;
    UInt key;

    /* disable interrupts */
    key = Hwi_disable();

    /* read and decrement the reference count */
    count = Power_module->resourceCounts[resourceID];

    Assert_isTrue(count != 0, Power_A_tooManyCallsReleaseDependency);

    count = count - 1;

    Power_module->resourceCounts[resourceID] = count;

    /* if this was the last dependency being released.., */
    if (count == 0) {

        /* deactivate this resource ... */
        id = Power_module->resourceDB[resourceID].driverlibID;

        /* is resource a peripheral?... */
        if (Power_module->resourceDB[resourceID].flags
            & PERIPH) {
            PRCMPeripheralRunDisable(id);
            PRCMPeripheralSleepDisable(id);
            PRCMPeripheralDeepSleepDisable(id);
            PRCMLoadSet();
            while(!PRCMLoadGet())
                {};
        }

        /* else, does resource require a special handler?... */
        else if (Power_module->resourceDB[resourceID].flags
            & SPECIAL) {

            /* call the special handler */
            Power_module->resourceHandlers[id](DISABLE);
        }

        /* else resource is a power domain */
        else {
            PRCMPowerDomainOff(id);
            while (PRCMPowerDomainStatus(id) != PRCM_DOMAIN_POWER_OFF) {};
        }

        /* propagate release up the dependency tree ... */

        /* check for a first parent */
        parent = Power_module->resourceDB[resourceID].flags
          & PARENTMASK;

        /* if 1st parent, make recursive call to release that dependency */
        if (parent != NOPARENT) {
            Power_releaseDependency(parent);
        }

        /* check for a second parent */
        parent = Power_module->resourceDB[resourceID].flags2
          & PARENTMASK;

        /* if 2nd parent, make recursive call to release that dependency */
        if (parent != NOPARENT) {
            Power_releaseDependency(parent);
        }
    }

    /* re-enable interrupts */
    Hwi_restore(key);
}

/*
 *  ======== Power_registerNotify ========
 *  Register a function to be called on a specific power event.
 *
 */
Power_Status Power_registerNotify(Power_NotifyObj * pNotifyObj,
    UInt32 eventTypes, Fxn notifyFxn, UArg clientArg, UArg arg)
{
    /* check for NULL pointers  */
    if ((pNotifyObj == NULL) || (notifyFxn == NULL)) {
        return (Power_EINVALIDPOINTER);
    }

    /* fill in notify object elements */
    pNotifyObj->eventTypes = eventTypes;
    pNotifyObj->notifyFxn = notifyFxn;
    pNotifyObj->clientArg = clientArg;

    /* place notify object on event notification queue */
    Queue_put(Power_Module_State_notifyQ(), (Queue_Elem*) pNotifyObj);

    return (Power_SOK);
}

/*
 *  ======== Power_setDependency ========
 *  Declare a dependency upon a resource.
 */
Bool Power_setDependency(Power_Resource resourceID)
{
    UInt8 parent;
    UInt8 count;
    UInt32 id;
    UInt key;

    /* disable interrupts */
    key = Hwi_disable();

    /* read and increment reference count */
    count = Power_module->resourceCounts[resourceID]++;

    /* if resource was NOT activated previously ... */
    if (count == 0) {

        /* propagate set up the dependency tree ... */

        /* check for a first parent */
        parent = Power_module->resourceDB[resourceID].flags
          & PARENTMASK;

        /* if first parent, make recursive call to set that dependency */
        if (parent != NOPARENT) {
            Power_setDependency(parent);
        }

        /* check for a second parent */
        parent = Power_module->resourceDB[resourceID].flags2
          & PARENTMASK;

        /* if second parent, make recursive call to set that dependency */
        if (parent != NOPARENT) {
            Power_setDependency(parent);
        }

        /* now activate this resource ... */
        id = Power_module->resourceDB[resourceID].driverlibID;

        /* is resource a peripheral?... */
        if (Power_module->resourceDB[resourceID].flags & PERIPH) {
            PRCMPeripheralRunEnable(id);
            PRCMPeripheralSleepEnable(id);
            PRCMPeripheralDeepSleepEnable(id);
            PRCMLoadSet();
            while(!PRCMLoadGet()){};
        }

        /* else, does resource require a special handler?... */
        else if (Power_module->resourceDB[resourceID].flags
            & SPECIAL) {

            /* call the special handler */
            Power_module->resourceHandlers[id](ENABLE);
        }

        /* else resource is a power domain */
        else {
            PRCMPowerDomainOn(id);
            while (PRCMPowerDomainStatus(id) != PRCM_DOMAIN_POWER_ON)
                {};
        }
    }

    /* re-enable interrupts */
    Hwi_restore(key);

    /* return the resource's activation status */
    return (Power_isDependencyActive(resourceID));
}

/*
 *  ======== Power_setConstraint ========
 *  Declare an operational constraint.
 */
Void Power_setConstraint(Power_Constraint constraint)
{
    UInt key;

    key = Hwi_disable();
    Power_module->constraintsMask |= constraint;
    Power_module->constraintCounts[Intrinsics_maxbit(constraint)]++;
    Hwi_restore(key);
}

/*
 *  ======== Power_shutdown ========
 */
Power_Status Power_shutdown(UArg arg)
{
    Power_Status status;
    UInt32 constraints;
    UInt hwiKey;

    /* make sure shutdown request doesn't violate a constraint */
    constraints = Power_getConstraintInfo();
    if ((constraints & (Power_SD_DISALLOW)) != 0) {
        return (Power_ECHANGE_NOT_ALLOWED);
    }

    /* next make sure Power is not still busy with a previous transition */
    hwiKey = Hwi_disable();

    if (Power_module->state == Power_ACTIVE) {
        /* set new transition state to entering shutdown */
        Power_module->state = Power_SHUTDOWN;
    }
    else {
        Hwi_restore(hwiKey);
        return (Power_EBUSY);
    }

    /* signal all clients registered for pre-shutdown notification */
    status = Power_notify(Power_ENTERING_SHUTDOWN);

    /* check for any error */
    if (status != Power_SOK) {
        Power_module->state = Power_ACTIVE;
        Hwi_restore(hwiKey);
        return (status);
    }

    /* now proceed with shutdown sequence ... */

    /* 1. Switch HF, MF, and LF clocks to source from RCOSC_HF */
    OSCInterfaceEnable();
    if(OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_RCOSC_HF) {
        OSCClockSourceSet(OSC_SRC_CLK_HF | OSC_SRC_CLK_MF,
            OSC_RCOSC_HF);
        while(!OSCHfSourceReady());
        OSCHfSourceSwitch();
    }
    OSCInterfaceDisable();

    /* 2. Make sure DMA and CRYTO clocks are off in deep-sleep */
    PRCMPeripheralDeepSleepDisable(PRCM_PERIPH_CRYPTO);
    PRCMPeripheralDeepSleepDisable(PRCM_PERIPH_UDMA);
    PRCMLoadSet();
    while(!PRCMLoadGet())
        {};

    /* 3. Power OFF AUX and disconnect from bus */
    AUXWUCPowerCtrl(AUX_WUC_POWER_OFF);

    /* 4. Remove AUX force ON */
    HWREG(AON_WUC_BASE + AON_WUC_O_AUXCTL) &=
        ~AON_WUC_AUXCTL_AUX_FORCE_ON;

    /*
     * 5. Reset AON event source IDs to avoid pending events powering
     * on MCU/AUX
     */
    HWREG(AON_EVENT_BASE + AON_EVENT_O_MCUWUSEL) = 0x3F3F3F3F;
    HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) = 0x003F3F3F;

    /* sync AON */
    SysCtrlAonSync();

    /*
     * 6. Enable shutdown - this latches the IOs, so configuration of
     * IOCFGx registers must be done prior to this
     */
    AONWUCShutDownEnable();

    /* 7. Sync AON */
    SysCtrlAonSync();

    /* 8. Wait until AUX powered off */
    while (AONWUCPowerStatusGet() & AONWUC_AUX_POWER_ON);

    /* 9. Request to power off MCU when go to deep sleep */
    PRCMMcuPowerOff();

    /*
     * 10. Turn off power domains inside MCU VD (BUS, FL_BUS, RFC,
     * CPU)
     */
    PRCMPowerDomainOff(PRCM_DOMAIN_RFCORE | PRCM_DOMAIN_SERIAL |
        PRCM_DOMAIN_PERIPH | PRCM_DOMAIN_CPU | PRCM_DOMAIN_VIMS);

    /* 11. Deep sleep to activate shutdown */
    PRCMDeepSleep();

    /* NOTE: if shutdown succeeded, should never get here */

    /* return failure status */
    Power_module->state = Power_ACTIVE;
    Hwi_restore(hwiKey);
    return (Power_EFAIL);
}

/*
 *  ======== Power_sleep ========
 */
Power_Status Power_sleep(Power_SleepState sleepState, UArg arg0, UArg arg1)
{
    Power_Status status = Power_SOK;
    UInt xosc_hf_active = FALSE;
    Power_Event postEventLate;
    UInt32 poweredDomains = 0;
    Power_Event preEvent;
    Power_Event postEvent;
    UInt32 constraints;
    Bool retainCache = FALSE;
    UInt32 modeVIMS;
    UInt taskKey;
    UInt swiKey;

    /* first validate the sleep code */
    if (sleepState != Power_STANDBY) {
        status = Power_EFAIL;
    }

    if (status == Power_SOK) {

        if (Power_module->state == Power_ACTIVE) {

            /* set transition state to entering sleep */
            Power_module->state = Power_ENTERING_SLEEP;
        }
        else {
            status = Power_EBUSY;
        }

        if (status == Power_SOK) {

            /* setup sleep vars */
            preEvent = Power_ENTERING_STANDBY;
            postEvent = Power_AWAKE_STANDBY;
            postEventLate = Power_AWAKE_STANDBY_LATE;

            /* disable Task scheduling; allow Swis and Hwis for notifications */
            taskKey = Task_disable();

            /* signal all clients registered for pre-sleep notification */
            status = Power_notify(preEvent);

            /* check for any error */
            if (status != Power_SOK) {
                Power_module->state = Power_ACTIVE;
                Task_restore(taskKey);          /* re-enable scheduler */
                return (status);
            }

            /* now disable Swi scheduling */
            swiKey = Swi_disable();

            /* 1. Freeze the IOs on the boundary between MCU and AON */
            AONIOCFreezeEnable();

            /* 2. If XOSC_HF is active, force it off */
            if(OSCClockSourceGet(OSC_SRC_CLK_HF) == OSC_XOSC_HF) {
                xosc_hf_active = TRUE;
                Power_XOSC_HF(DISABLE);
            }

            /* 3. Allow AUX to power down */
            AONWUCAuxWakeupEvent(AONWUC_AUX_ALLOW_SLEEP);

            /* 4. Make sure writes take effect */
            SysCtrlAonSync();

            /* now proceed to transition to Power_STANDBY ... */

            /* 5. Query and save domain states before powering them off */
            if (Power_getDependencyCount(DOMAIN_RFCORE)) {
                poweredDomains |= PRCM_DOMAIN_RFCORE;
            }
            if (Power_getDependencyCount(DOMAIN_SERIAL)){
                poweredDomains |= PRCM_DOMAIN_SERIAL;
            }
            if (Power_getDependencyCount(DOMAIN_PERIPH)) {
                poweredDomains |= PRCM_DOMAIN_PERIPH;
            }

            /* 6. Gate running deep sleep clocks for Crypto and DMA */
            if (Power_getDependencyCount(PERIPH_CRYPTO)) {
                PRCMPeripheralDeepSleepDisable(
                    Power_module->resourceDB[PERIPH_CRYPTO].driverlibID);
            }
            if (Power_getDependencyCount(PERIPH_UDMA)) {
                PRCMPeripheralDeepSleepDisable(
                    Power_module->resourceDB[PERIPH_UDMA].driverlibID);
            }
            /* 7. Make sure clock settings take effect */
            PRCMLoadSet();

            /* 8. Request power off of domains in the MCU voltage domain */
            PRCMPowerDomainOff(poweredDomains | PRCM_DOMAIN_CPU);

            /* 9. Request uLDO during standby */
            PRCMMcuUldoConfigure(true);

            /* Query constraints to determine if cache should be retained */
            constraints = Power_getConstraintInfo();
            if ((constraints & Power_SB_VIMS_CACHE_RETAIN) != 0) {
                retainCache = TRUE;
            }

            /* 10. If don't want VIMS retention in standby, disable it now... */
            if (retainCache == FALSE) {

                /* 10.1 Get the current VIMS mode */
                do {
                    modeVIMS = VIMSModeGet(VIMS_BASE);
                } while (modeVIMS == VIMS_MODE_CHANGING);

                /* 10.2 If in a cache mode, turn VIMS off */
                if ((modeVIMS == VIMS_MODE_ENABLED) ||
                    (modeVIMS == VIMS_MODE_SPLIT)) {

                    /* 10.3 Now turn off the VIMS */
                    VIMSModeSet(VIMS_BASE, VIMS_MODE_OFF);
                }

                /* 10.4 Now disable retention */
                PRCMCacheRetentionDisable();
            }

            /* 11. Setup recharge parameters */
            SysCtrlSetRechargeBeforePowerDown(XoscInHighPowerMode);

            /* 12. Make sure all writes have taken effect */
            SysCtrlAonSync();

            /* 13. Invoke deep sleep to go to STANDBY */
            PRCMDeepSleep();

            /* 14. If didn't retain VIMS in standby, re-enable retention now */
            if (retainCache == FALSE) {

                /* 14.1 If previously in a cache mode, restore the mode now */
                if ((modeVIMS == VIMS_MODE_ENABLED) ||
                    (modeVIMS == VIMS_MODE_SPLIT)) {
                    VIMSModeSet(VIMS_BASE, modeVIMS);
                }

                /* 14.2 Re-enable retention */
                PRCMCacheRetentionEnable();
            }

            /* 15. Start forcing on power to AUX */
            AONWUCAuxWakeupEvent(AONWUC_AUX_WAKEUP);

            /* 16. Start re-powering power domains */
            PRCMPowerDomainOn(poweredDomains);

            /* 17. Restore deep sleep clocks of Crypto and DMA */
            if (Power_getDependencyCount(PERIPH_CRYPTO)) {
                PRCMPeripheralDeepSleepEnable(
                    Power_module->resourceDB[PERIPH_CRYPTO].driverlibID);
            }
            if (Power_getDependencyCount(PERIPH_UDMA)) {
                PRCMPeripheralDeepSleepEnable(
                    Power_module->resourceDB[PERIPH_UDMA].driverlibID);
            }

            /* 18. Make sure clock settings take effect */
            PRCMLoadSet();

            /* 19. Release request for uLDO */
            PRCMMcuUldoConfigure(false);

            /* 20. Set transition state to EXITING_SLEEP */
            Power_module->state = Power_EXITING_SLEEP;

            /* 21. Wait until all power domains are back on */
            while (PRCMPowerDomainStatus(poweredDomains) !=
                PRCM_DOMAIN_POWER_ON){};

            /*
             * 22. Signal clients registered for early post-sleep notification;
             * this should be used to initialize any timing critical or IO
             * dependent hardware
             */
            status = Power_notify(postEvent);

            /* 23. Disable IO freeze and ensure RTC shadow value is updated */
            AONIOCFreezeDisable();
            SysCtrlAonSync();

            /* 24. Wait for AUX to power up */
            while(!(AONWUCPowerStatusGet() & AONWUC_AUX_POWER_ON)) {};

            /* 25. If XOSC_HF was forced off above, initiate switch back */
            if (xosc_hf_active == TRUE) {
                Power_XOSC_HF(ENABLE);
            }

            /* 26. Re-enable interrupts */
            CPUcpsie();

            /*
             * 27. Signal all clients registered for late post-sleep
             * notification
             */
            status = Power_notify(postEventLate);

            /*
             * 28. Now clear the transition state before re-enabling
             * scheduler
             */
            Power_module->state = Power_ACTIVE;

            /* 29. Re-enable Swi scheduling */
            Swi_restore(swiKey);

            /* 30. Adjust recharge parameters */
            SysCtrlAdjustRechargeAfterPowerDown();

            /* re-enable Task scheduling */
            Task_restore(taskKey);
        }
    }

    return (status);
}

/*
 *  ======== Power_switchXOSC_HF ========
 *  Switch to enable XOSC_HF.
 */
Void Power_switchXOSC_HF(Void)
{
    UInt key;

    key = Hwi_disable();

    /* only switch source if there is a pending change */
    if (Power_module->xoscPending == TRUE) {
        OSCHF_AttemptToSwitchToXosc();
        Power_module->xoscPending = FALSE;
    }

    Hwi_restore(key);
}

/*
 *  ======== Power_unregisterNotify ========
 *  Unregister for a power notification.
 *
 */
Void Power_unregisterNotify(Power_NotifyObj * pNotifyObj)
{
    UInt key;

    /* remove notify object from its event queue */
    key = Hwi_disable();
    Queue_remove((Queue_Elem *)pNotifyObj);
    Hwi_restore(key);
}


/* * * * * * * * * * * internal and support functions * * * * * * * * * * */

/*
 *  ======== Power_Module_startup ========
 */
Int ti_sysbios_family_arm_cc26xx_Power_Module_startup(Int status)
{
    UInt32 ccfgLfClkSrc;

    DRIVERLIB_ASSERT_CURR_RELEASE();

    /* check if should calibrate RCOSC_LF */
    if (Power_calibrateRCOSC_LF) {

        /* read the LF clock source from CCFG */
        ccfgLfClkSrc = CCFGRead_SCLK_LF_OPTION();

        /* verify RCOSC_LF is the LF clock source */
        if (ccfgLfClkSrc == SCLK_LF_OPTION_RCOSC_LF) {
            Power_module->calLF = true;
        }
    }

    /* if VIMS RAM is configured as GPRAM: set retention constraint */
    if (!CCFGRead_DIS_GPRAM()) {
        Power_setConstraint(Power_SB_VIMS_CACHE_RETAIN);
    }

    /* set standby disallow constraint pending LF clock quailifier disabling */
    Power_setConstraint(Power_SB_DISALLOW);

    return (Startup_DONE);
}

/*
 *  ======== Power_defaultClockFunc ========
 *  Clock function used by power policy to schedule early wakeups.
 */
Void Power_defaultClockFunc(UArg arg)
{
}

/*
 *  ======== Power_defaultNotifyTrapFunc ========
 */
Void Power_defaultNotifyTrapFunc()
{
    while (1) {};
}

/*
 *  ======== Power_doWFI ========
 */
Void Power_doWFI()
{
    __asm(" wfi");
}

/*
 *  ======== Power_LF_clockFunc ========
 *  Clock function used for delayed disable of LF clock qualifiers.
 */
Void Power_LF_clockFunc(UArg arg)
{
    UInt32 sourceLF;

     /* query LF clock source */
    sourceLF = OSCClockSourceGet(OSC_SRC_CLK_LF);

    /* is LF source either RCOSC_LF or XOSC_LF yet? */
    if ((sourceLF == OSC_RCOSC_LF) || (sourceLF == OSC_XOSC_LF)) {

        /* yes, disable the LF clock qualifiers */
        DDI16BitfieldWrite(
            AUX_DDI0_OSC_BASE,
            DDI_0_OSC_O_CTL0,
            DDI_0_OSC_CTL0_BYPASS_XOSC_LF_CLK_QUAL_M|
                DDI_0_OSC_CTL0_BYPASS_RCOSC_LF_CLK_QUAL_M,
            DDI_0_OSC_CTL0_BYPASS_RCOSC_LF_CLK_QUAL_S,
            0x3
        );

        /* now finish by releasing the standby disallow constraint */
        Power_releaseConstraint(Power_SB_DISALLOW);
    }

    /* not yet, LF still derived from HF, restart clock to check back later */
    else {
        /* retrigger LF Clock to fire in 100 msec */
        Clock_setTimeout(
            ti_sysbios_family_arm_cc26xx_Power_Module_State_lfClockObj(),
            (100000 / Clock_tickPeriod));
        Clock_start(
            ti_sysbios_family_arm_cc26xx_Power_Module_State_lfClockObj());
    }
}
/*
 *  ======== Power_notify ========
 *  Send notifications to registered clients.
 *  Note: Task scheduling is disabled when this function is called.
 */
Power_Status Power_notify(Power_Event eventType)
{
    Power_Status returnStatus = Power_SOK;
    Power_NotifyResponse notifyStatus;
    Queue_Handle notifyQ;

    notifyQ = Power_Module_State_notifyQ();

    /* if notification queue is not empty, service the queue */
    if (!Queue_empty(notifyQ)) {

       /* service the notification queue... */
       notifyStatus = Power_serviceNotifyQ(eventType);

       /* if notifications did not complete successfully ... */
        if (notifyStatus != Power_NOTIFYDONE) {

            /* call the configured notify trap function */
            (*(Power_FuncPtr)Power_notifyTrapFunc)();

            returnStatus = Power_EFAIL;
        }
    }

    return (returnStatus);
}

/*
 *  ======== Power_serviceNotifyQ ========
 */
Power_NotifyResponse Power_serviceNotifyQ(Power_Event eventType)
{
    Power_NotifyResponse returnStatus = Power_NOTIFYDONE;
    Power_NotifyResponse clientStatus;
    Queue_Handle notifyQ;
    Queue_Elem * elem;
    Fxn notifyFxn;
    UArg clientArg;

    notifyQ = Power_Module_State_notifyQ();

    /* point to first client notify object */
    elem = Queue_head(notifyQ);

    /* walk the queue and notify each registered client of the event */
    do {
        if (((Power_NotifyObj *)elem)->eventTypes & eventType) {

            /* pull params from notify object */
            notifyFxn = ((Power_NotifyObj *)elem)->notifyFxn;
            clientArg = ((Power_NotifyObj *)elem)->clientArg;

            /* call the client's notification function */
            clientStatus = (Power_NotifyResponse) (*(Fxn)notifyFxn)(
                eventType, clientArg);

            /* if client declared error stop all further notifications */
            if (clientStatus == Power_NOTIFYERROR) {
                return (Power_NOTIFYERROR);
            }
        }

        /* get next element in the notification queue */
        elem = Queue_next(elem);

    } while (elem != (Queue_Elem *) notifyQ);

    return (returnStatus);
}

/*
 *  ======== Power_RFCORECLKS ========
 *  Special dependency function for controlling RF core clocks.
 */
UInt Power_RFCORECLKS (UInt action)
{
    if (action == ENABLE) {
        RFCClockEnable();
    }
    else {
        RFCClockDisable();
    }
    return (0);
}

/*
 *  ======== Power_XOSC_HF_clockFunc ========
 *  Clock function used for delayed switching to XOSC_HF.
 */
Void Power_XOSC_HF_clockFunc(UArg arg0)
{
    Bool readyToCal;
    UInt32 timeout;
    UInt key;

    key = ti_sysbios_hal_Hwi_disable();

    /* if pending switch has already been made, just send out notifications */
    if (Power_module->xoscPending == FALSE) {

        /* initiate RCOSC calibration */
        if (Power_calibrateRCOSC) {
            readyToCal = Power_initiateCalibration();
        }

        /* notify clients that were waiting for a switch notification */
        Power_notify(Power_XOSC_HF_SWITCHED);

        /* if ready to start first cal measurment, do it now */
        if (Power_calibrateRCOSC) {
            if (readyToCal == TRUE) {
                Power_doCalibrate();
            }
        }
    }

    /* else, if HF ready to switch, do it now ... */
    else if (OSCHF_AttemptToSwitchToXosc()) {

        Power_module->xoscPending = FALSE;

        /* initiate RCOSC calibration */
        if (Power_calibrateRCOSC) {
            readyToCal = Power_initiateCalibration();
        }

        /* now notify clients that were waiting for a switch notification */
        Power_notify(Power_XOSC_HF_SWITCHED);

        /* if ready to start first cal measurment, do it now */
        if (Power_calibrateRCOSC) {
            if (readyToCal == TRUE) {
                Power_doCalibrate();
            }
        }
    }

    /* else, wait some more, then see if can switch ... */
    else {
        /* calculate wait timeout in units of ticks */
        timeout = Power_retryWaitXOSC_HF / ti_sysbios_knl_Clock_tickPeriod;
        if (timeout == 0) {
            timeout = 1;   /* wait at least 1 tick */
        }

        /* re-start Clock object with retry timeout */
        ti_sysbios_knl_Clock_setTimeout(
            ti_sysbios_family_arm_cc26xx_Power_Module_State_xoscClockObj(),
            timeout);
        ti_sysbios_knl_Clock_start(
            ti_sysbios_family_arm_cc26xx_Power_Module_State_xoscClockObj());
    }

    ti_sysbios_hal_Hwi_restore(key);
}

/*
 *  ======== Power_XOSC_HF ========
 */
UInt Power_XOSC_HF (UInt action)
{
    UInt32 timeout;

    if (action == ENABLE) {
        if (OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_XOSC_HF) {
            OSCHF_TurnOnXosc();

            Power_module->xoscPending = TRUE;

            /* calculate wait timeout in units of ticks */
            timeout = Power_initialWaitXOSC_HF /
                ti_sysbios_knl_Clock_tickPeriod;
            if (timeout == 0) {
                timeout = 1;   /* wait at least 1 tick */
            }

            /* start Clock object with initial timeout */
            ti_sysbios_knl_Clock_stop(
                ti_sysbios_family_arm_cc26xx_Power_Module_State_xoscClockObj());
            ti_sysbios_knl_Clock_setTimeout(
                ti_sysbios_family_arm_cc26xx_Power_Module_State_xoscClockObj(),
                timeout);
            ti_sysbios_knl_Clock_start(
                ti_sysbios_family_arm_cc26xx_Power_Module_State_xoscClockObj());
        }
    }

    /* when release XOSC_HF, auto switch to RCOSC_HF */
    else {
        OSCHF_SwitchToRcOscTurnOffXosc();
    }
    return (0);
}

/*
 *  ======== Power_isDependencyActive ========
 */
Bool Power_isDependencyActive (Power_Resource resourceID)
{
    Bool status = TRUE;

    /* check if the special XOSC_HF resource ...*/
    if(resourceID == XOSC_HF) {

        /* check to see if XOSC_HF is the active source */
        if(OSCClockSourceGet(OSC_SRC_CLK_HF) != OSC_XOSC_HF) {
            status = FALSE;
        }
    }

    /* else, all other resources ... */
    else {

       /* resource is active if dependency count != 0 */
        if(Power_module->resourceCounts[resourceID] == 0) {
            status = FALSE;
        }
    }

    return (status);
}

/*
 *  ======== Power_NOP (UInt action) ========
 */
UInt Power_NOP (UInt action)
{
    return (0);
}

Fxn ti_sysbios_family_arm_cc26xx_Power_resourceHandlers[3] =
{
    (Fxn) Power_RFCORECLKS,
    (Fxn) Power_XOSC_HF,
    (Fxn) Power_NOP
};
