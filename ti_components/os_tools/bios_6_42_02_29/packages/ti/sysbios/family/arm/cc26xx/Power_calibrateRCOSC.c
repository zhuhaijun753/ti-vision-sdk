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
 *  ======== Power_calibrateRCOSC.c ========
 */

#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/arm/cc26xx/Power.h>
#include <ti/sysbios/family/arm/cc26xx/PowerCC2650.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/hal/Hwi.h>

#include <driverlib/ddi.h>
#include <driverlib/ioc.h>
#include <driverlib/osc.h>
#include <driverlib/gpio.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/aux_wuc.h>
#include <inc/hw_aux_evctl.h>
#include <inc/hw_aux_smph.h>
#include <inc/hw_aux_wuc.h>
#include <inc/hw_aux_tdc.h>
#include <inc/hw_ddi_0_osc.h>
#include <inc/hw_ddi.h>
#include <inc/hw_ccfg.h>

#include "package/internal/Power.xdc.h"

#define AUX_TDC_SEMAPHORE_NUMBER        1  /* semaphore 1 protects TDC */
#define NUM_RCOSC_LF_PERIODS_TO_MEASURE 32 /* x RCOSC_LF periods vs XOSC_HF */
#define NUM_RCOSC_HF_PERIODS_TO_MEASURE 1  /* x RCOSC_HF periods vs XOSC_HF */
#define ACLK_REF_SRC_RCOSC_HF           0  /* Use RCOSC_HF for ACLK REF */
#define ACLK_REF_SRC_RCOSC_LF           2  /* Use RCOSC_LF for ACLK REF */

#define SCLK_LF_OPTION_RCOSC_LF         3  /* defined in cc26_ccfg.xls */

#define DDI_0_OSC_O_CTL1_LOCAL                   0x00000004     /* offset */
#define DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_M 0x007C0000     /* mask */
#define DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_S    18          /* shift */
#define DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_EN_LOCAL_M 0x00020000  /* mask */
#define DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_EN_LOCAL_S 17          /* shift */

/* AUX ISR states */
#define WAIT_SMPH       0   /* just took SMPH, start RCOSC_LF */
#define CAL_RCOSC_LF    1   /* just finished RCOSC_LF, start first RCOSC_HF */
#define CAL_RCOSC_HF1   2   /* just finished 1st RCOSC_HF, start 2nd */
#define CAL_RCOSC_HF2   3   /* just finished 2nd RCOSC_HF, decide best */

/* calibration steps */
#define STEP_TDC_INIT_1    1
#define STEP_TDC_INIT_2    2
#define STEP_CAL_LF_1      3
#define STEP_CAL_LF_2      4
#define STEP_CAL_LF_3      5
#define STEP_CAL_HF1_1     6
#define STEP_CAL_HF1_2     7
#define STEP_CAL_HF1_3     8
#define STEP_CAL_HF2_1     9
#define STEP_CAL_HF2_2     10
#define STEP_CLEANUP_1     11
#define STEP_CLEANUP_2     12

/* macros */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define INSTRUMENT 0

#if INSTRUMENT
volatile UInt gotSEM = 0;
volatile UInt calLFi = 0;
volatile UInt calHF1i = 0;
volatile UInt calHF2i = 0;
volatile Bool doneCal = FALSE;
UInt tdcResult_LF = 0;
UInt tdcResult_HF1 = 0;
UInt tdcResult_HF2 = 0;
UInt numISRs = 0;
UInt calClocks = 0;
#endif

/*
 *  ======== initiateCalibration ========
 *  Initiate calibration of RCOSC_LF and RCOSCHF
 */
Bool Power_initiateCalibration()
{
    UInt hwiKey;
    Bool busy = FALSE;
    Bool status;
    Bool gotSem;

    if ((Power_module->calLF != TRUE) && (Power_calibrateRCOSC_HF != TRUE)) {
        return (FALSE);
    }

    /* make sure calibration is not already in progress */
    hwiKey = Hwi_disable();

    if (Power_module->busyCal == FALSE) {
        Power_module->busyCal = TRUE;
    }
    else {
        busy = TRUE;
    }

    Hwi_restore(hwiKey);

    if (busy == TRUE) {
        return (FALSE);
    }

#if INSTRUMENT
    gotSEM = 0;
    calLFi = 0;
    calHF1i = 0;
    calHF2i = 0;
    doneCal = FALSE;
#endif

    /* set contraint to prohibit standby during calibration sequence */
    Power_setConstraint(Power_SB_DISALLOW);

    /* set dependency to keep XOSC_HF active during calibration sequence */
    Power_setDependency(XOSC_HF);

    /* initiate acquisition of semaphore protecting TDC */
    gotSem = Power_getTdcSemaphore();

    /* if didn't acquire semaphore, must wait for autotake ISR */
    if (gotSem == FALSE) {
        Power_module->hwiState = WAIT_SMPH;
        status = FALSE;  /* FALSE: don't do anything else until acquire SMPH */
    }

    /* else, semaphore acquired, OK to proceed with first measurement */
    else {
#if INSTRUMENT
        gotSEM = 1;
#endif
        status = TRUE;   /* TRUE: OK to start first measurement */
    }

    return (status);
}

/*
 *  ======== Power_auxISR ========
 *  ISR for the AUX combo interrupt event.  Implements Hwi state machine to
 *  step through the RCOSC calibration steps.
 */
Void ti_sysbios_family_arm_cc26xx_Power_auxISR(UArg arg)
{
    UInt32 tdcResult;

#if INSTRUMENT
    numISRs++;
#endif

    /* read the interrupt source */
    UInt32 auxEvent = HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_EVTOMCUFLAGS);

    /* disable interrupts (clearing them does not clear the source (bug)) */
    HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_COMBEVTOMCUMASK) &= ~auxEvent;

    /* clear the interrupt source */
    HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_EVTOMCUFLAGSCLR) = auxEvent;

    /* ****** state = WAIT_SMPH: arrive here if just took the SMPH ****** */
    if (Power_module->hwiState == WAIT_SMPH) {
#if INSTRUMENT
        gotSEM = 1;
#endif
    }

    /* **** state = CAL_RCOSC_LF: here when just finished LF counting **** */
    else if (Power_module->hwiState == CAL_RCOSC_LF) {

        tdcResult = HWREG(AUX_TDCIF_BASE + AUX_TDC_O_RESULT);

#if INSTRUMENT
        tdcResult_LF = tdcResult;
#endif
        /* update the RTC SUBSECINC register based on LF measurement result */
        Power_updateSubSecInc(tdcResult);
#if INSTRUMENT
        calLFi = 1;
#endif
        /* if doing HF calibration initiate it now */
        if (Power_calibrateRCOSC_HF) {
            Power_module->calStep = STEP_CAL_LF_3;  /* next: trigger LF */
        }

        /* else, start cleanup */
        else {
            Power_module->calStep = STEP_CLEANUP_1; /* next: cleanup */
        }
    }

    /* ****** state = CAL_RCOSC_HF1: here when just finished 1st RCOSC_HF */
    else if (Power_module->hwiState == CAL_RCOSC_HF1) {

        tdcResult = HWREG(AUX_TDCIF_BASE + AUX_TDC_O_RESULT);

#if INSTRUMENT
        tdcResult_HF1 = tdcResult;
        calHF1i = 1;
#endif
        /* if HF setting perfect, nothing more to do, calibration is done */
        if (tdcResult == 1536) {
            Power_module->calStep = STEP_CLEANUP_1;  /* next: cleanup */
        }

        /* else, tweak trims, initiate another HF measurement */
        else {

            /* use first HF measurement to setup new trim values */
            Power_calibrateRcoscHf1(tdcResult);

            Power_module->calStep = STEP_CAL_HF1_3;  /* next: HF meas. #2 */
        }
    }

    /* ****** state = just finished second RCOSC_HF measurement ****** */
    else if (Power_module->hwiState == CAL_RCOSC_HF2) {

        tdcResult = HWREG(AUX_TDCIF_BASE + AUX_TDC_O_RESULT);

#if INSTRUMENT
        tdcResult_HF2 = tdcResult;
#endif
        /* look for improvement on #2, else revert to previous trim values */
        Power_calibrateRcoscHf2(tdcResult);

        Power_module->calStep = STEP_CLEANUP_1;    /* next: cleanup */
    }

    /* do the next calibration step... */
    Power_doCalibrate();
}

/*
 *  ======== Power_doCalibrate ========
 */
Void Power_doCalibrate(Void)
{
    switch (Power_module->calStep) {

        case STEP_TDC_INIT_1:

            /* turn on clock to TDC module */
            AUXWUCClockEnable(AUX_WUC_TDCIF_CLOCK);

            /* set saturation config to 2^24 */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_SATCFG) =
                AUX_TDC_SATCFG_LIMIT_ROVF;

            /* set start and stop trigger sources and polarity */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_TRIGSRC) =
                (AUX_TDC_TRIGSRC_STOP_SRC_ACLK_REF |
                 AUX_TDC_TRIGSRC_STOP_POL_HIGH) |
                (AUX_TDC_TRIGSRC_START_SRC_ACLK_REF |
                 AUX_TDC_TRIGSRC_START_POL_HIGH);

            /* set TDC_SRC clock to be XOSC_HF/2 = 24 MHz */
            DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL0,
                DDI_0_OSC_CTL0_ACLK_TDC_SRC_SEL_M,
                DDI_0_OSC_CTL0_ACLK_TDC_SRC_SEL_S, 2);

            /* set AUX_WUC:TDCCLKCTL.REQ... */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_TDCCLKCTL) = AUX_WUC_TDCCLKCTL_REQ;

            /* set next state */
            Power_module->calStep = STEP_TDC_INIT_2;

            /* start Clock object to delay while wait for ACK */
            Clock_start(Power_module->calClockHandle);

            break;

        case STEP_TDC_INIT_2:

            /* Enable trig count */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_TRIGCNTCFG) =
                AUX_TDC_TRIGCNTCFG_EN;

            /* if LF calibration enabled start LF measurement */
            if (Power_module->calLF) {

               /* clear UPD_REQ, new sub-second increment is NOT available */
                HWREG(AUX_WUC_BASE + AUX_WUC_O_RTCSUBSECINCCTL) = 0;

                /* set next Swi state */
                Power_module->calStep = STEP_CAL_LF_1;
            }

            /* else, start first HF measurement */
            else {
                /* set next Swi state */
                Power_module->calStep = STEP_CAL_HF1_1;
            }

            /* abort TDC */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_CTL) = AUX_TDC_CTL_CMD_ABORT;

            /* clear AUX_WUC:REFCLKCTL.REQ... */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) = 0;

            /* if not ready, start Clock object to delay while wait for ACK */
            if (HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) &
                AUX_WUC_REFCLKCTL_ACK) {

                /* start Clock object to delay while wait for ACK */
                Clock_start(Power_module->calClockHandle);

                break;
            }

            /* else, if ready now, fall thru to next step ... */


        case STEP_CAL_LF_1:
        case STEP_CAL_HF1_1:
        case STEP_CAL_HF2_1:

            if (Power_module->calStep == STEP_CAL_LF_1) {

                /* set the ACLK reference clock */
                DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL0,
                           DDI_0_OSC_CTL0_ACLK_REF_SRC_SEL_M,
                           DDI_0_OSC_CTL0_ACLK_REF_SRC_SEL_S,
                           ACLK_REF_SRC_RCOSC_LF);

                /* set next Swi state */
                Power_module->calStep = STEP_CAL_LF_2;
            }
            else {

                /* set the ACLK reference clock */
                DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL0,
                       DDI_0_OSC_CTL0_ACLK_REF_SRC_SEL_M,
                       DDI_0_OSC_CTL0_ACLK_REF_SRC_SEL_S,
                       ACLK_REF_SRC_RCOSC_HF);

                /* set next Swi state */
                if (Power_module->calStep == STEP_CAL_HF1_1) {
                    Power_module->calStep = STEP_CAL_HF1_2;
                }
                else {
                    Power_module->calStep = STEP_CAL_HF2_2;
                }
            }

            /* set AUX_WUC:REFCLKCTL.REQ */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) = AUX_WUC_REFCLKCTL_REQ;

            /* start Clock object to delay while wait for ACK */
            Clock_start(Power_module->calClockHandle);

            break;

        case STEP_CAL_LF_2:
        case STEP_CAL_HF1_2:
        case STEP_CAL_HF2_2:

            if (Power_module->calStep == STEP_CAL_LF_2) {

                /* Set number of periods of ACLK to count */
                HWREG(AUX_TDCIF_BASE + AUX_TDC_O_TRIGCNTLOAD) =
                    NUM_RCOSC_LF_PERIODS_TO_MEASURE;

                /* set next Hwi state before triggering TDC */
                Power_module->hwiState = CAL_RCOSC_LF;
            }
            else {

                /* Set number of periods of ACLK to count */
                HWREG(AUX_TDCIF_BASE + AUX_TDC_O_TRIGCNTLOAD) =
                    NUM_RCOSC_HF_PERIODS_TO_MEASURE;

                /* set next Hwi state before triggering TDC */
                if (Power_module->calStep == STEP_CAL_HF2_2) {
                    Power_module->hwiState = CAL_RCOSC_HF2;
                }
                else {
                    Power_module->hwiState = CAL_RCOSC_HF1;
                }
            }

            /* Reset/clear result of TDC */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_CTL) = AUX_TDC_CTL_CMD_CLR_RESULT;

            /* Clear possible pending interrupt source */
            HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_EVTOMCUFLAGSCLR) =
                AUX_EVCTL_EVTOMCUFLAGSCLR_TDC_DONE;

            /* Enable TDC done interrupt as part of AUX_COMBINED interrupt */
            HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_COMBEVTOMCUMASK) =
                AUX_EVCTL_COMBEVTOMCUMASK_TDC_DONE;

            /* Run TDC (start synchronously) */
            HWREG(AUX_TDCIF_BASE + AUX_TDC_O_CTL) =
                AUX_TDC_CTL_CMD_RUN_SYNC_START;

            break;

        case STEP_CAL_LF_3:
        case STEP_CAL_HF1_3:

            /* set next Swi state */
            if (Power_module->calStep == STEP_CAL_LF_3) {
                Power_module->calStep = STEP_CAL_HF1_1;
            }
            else {
                Power_module->calStep = STEP_CAL_HF2_1;
            }

            /* clear AUX_WUC:REFCLKCTL.REQ... */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) = 0;

            /* start Clock object to delay while wait for ACK */
            Clock_start(Power_module->calClockHandle);

            break;

        case STEP_CLEANUP_1:

            /* disable TDC counter clock source */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_TDCCLKCTL) = 0;

            /* set next state */
            Power_module->calStep = STEP_CLEANUP_2;

            /* start Clock object to delay while wait for ACK */
            Clock_start(Power_module->calClockHandle);

            break;

        case STEP_CLEANUP_2:

            /* release the TDC clock request */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_TDCCLKCTL) = 0;

            /* relese the TDC reference clock request */
            HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) = 0;

            /* release AUX semaphore */
            HWREG(AUX_SMPH_BASE + AUX_SMPH_O_SMPH1) = 1;

            /* release the standby constraint and XOSC_HF dependency */
            Power_releaseDependency(XOSC_HF);
            Power_releaseConstraint(Power_SB_DISALLOW);

            /* set next state */
            Power_module->calStep = STEP_TDC_INIT_1;

#if INSTRUMENT
            doneCal = TRUE;
            calHF2i = 1;
#endif
            Power_module->busyCal = FALSE;
            break;
    }
}

/*
 *  ======== Power_RCOSC_clockFunc ========
 */
Void ti_sysbios_family_arm_cc26xx_Power_RCOSC_clockFunc(UArg arg)
{
#if INSTRUMENT
    calClocks++;
#endif

    switch (Power_module->calStep) {

        case STEP_TDC_INIT_2:
            /* finish wait for AUX_WUC:TDCCLKCTL.ACK to be set ... */
            while(!(HWREG(AUX_WUC_BASE + AUX_WUC_O_TDCCLKCTL) &
                AUX_WUC_TDCCLKCTL_ACK));
            break;

        case STEP_CAL_LF_1:
        case STEP_CAL_HF1_1:
        case STEP_CAL_HF2_1:
            /* finish wait for AUX_WUC:REFCLKCTL.ACK to be cleared ... */
            while(HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) &
                AUX_WUC_REFCLKCTL_ACK);
            break;

        case STEP_CAL_LF_2:
        case STEP_CAL_HF1_2:
        case STEP_CAL_HF2_2:
            /* finish wait for AUX_WUC:REFCLKCTL.ACK to be set ... */
            while(!(HWREG(AUX_WUC_BASE + AUX_WUC_O_REFCLKCTL) &
                AUX_WUC_REFCLKCTL_ACK));
            break;

        case STEP_CLEANUP_2:
            /* finish wait for AUX_WUC:TDCCLKCTL.ACK to be cleared ... */
            while ((HWREG(AUX_WUC_BASE + AUX_WUC_O_TDCCLKCTL) &
                AUX_WUC_TDCCLKCTL_ACK));
            break;
    }

    Power_doCalibrate();
}

/*
 *  ======== Power_getTdcSemaphore ========
 *  Get TDC semaphore (number 1)
 */
Bool Power_getTdcSemaphore()
{
    UInt own;

    /* try to acquire SMPH */
    own = HWREG(AUX_SMPH_BASE + AUX_SMPH_O_SMPH1);

    /* if acquired SMPH: done */
    if (own != 0) {
        return (TRUE);
    }

    /*
     * else, did not acquire the semaphore, enable SMPH_AUTOTAKE_DONE event
     * (don't OR, write entire register, no other interrupts can be enabled!)
     */
    HWREG(AUX_EVCTL_BASE + AUX_EVCTL_O_COMBEVTOMCUMASK) =
        AUX_EVCTL_COMBEVTOMCUMASK_SMPH_AUTOTAKE_DONE;

    /* start AUTOTAKE of semaphore for TDC access */
    HWREG(AUX_SMPH_BASE + AUX_SMPH_O_AUTOTAKE) = AUX_TDC_SEMAPHORE_NUMBER;

    return (FALSE);
}

/*
 *  ======== Power_updateSubSecInc ========
 *  Update the SUBSECINC register based on measured RCOSC_LF frequency
 */
Void Power_updateSubSecInc(UInt32 tdcResult)
{
    UInt32 newSubSecInc;
    UInt32 oldSubSecInc;
    UInt32 subSecInc;

    /*
     * Calculate the new SUBSECINC
     * Here's the formula: AON_RTC:SUBSECINC = (45813 * NR) / 256
     */
    newSubSecInc = (45813 * tdcResult) / 256;

    /* Apply filter, but not for first calibration */
    if (Power_module->firstLF) {
        /* Don't apply filter first time, to converge faster */
        subSecInc = newSubSecInc;
        /* No longer first measurement */
        Power_module->firstLF = FALSE;
    }
    else {
        /* Read old SUBSECINC value */
        oldSubSecInc = HWREG(AON_RTC_BASE + AON_RTC_O_SUBSECINC) & 0x00FFFFFF;
        /* Apply filter, 0.5 times old value, 0.5 times new value */
        subSecInc = (oldSubSecInc * 1 + newSubSecInc * 1) / 2;
    }

    /* Update SUBSECINC values */
    HWREG(AUX_WUC_BASE + AUX_WUC_O_RTCSUBSECINC0) = subSecInc;
    HWREG(AUX_WUC_BASE + AUX_WUC_O_RTCSUBSECINC1) = subSecInc >> 16;

    /* update to use new values */
    HWREG(AUX_WUC_BASE + AUX_WUC_O_RTCSUBSECINCCTL) =
        AUX_WUC_RTCSUBSECINCCTL_UPD_REQ;
}

/*
 *  ======== Power_calibrateRcoscHf1 ========
 *  Calibrate RCOSC_HF agains XOSC_HF: compute and setup new trims
 */
Void Power_calibrateRcoscHf1(Int32 tdcResult)
{
    /* read current trims */
    Power_module->nCtrimCurr =
        (DDI32RegRead(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_RCOSCHFCTL) &
        DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_M) >>
        DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_S;

    Power_module->nCtrimFractCurr =
        (DDI32RegRead(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL1_LOCAL)
        & DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_M) >>
        DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_S;

    /*
     * Find RCOSC_HF-XOSC_HF frequency offset with current trim settings
     *   Positive value => RCOSC_HF runs slow, CTRIM(FRACT) should be increased
     *   Negative value => RCOSC_HF runs fast, CTRIM(FRACT) should be decreased
     * Resolution: 31.25 kHz; CTRIMFRACT resolution ~30 kHz
     */
    Power_module->nDeltaFreqCurr = (Int32) tdcResult - 1536;

    /*
     * Calculate change to CTRIMFRACT with safe assumptions of gain,
     * apply delta to current CTRIMFRACT and convert to valid CTRIM/CTRIMFRACT
     */
    Power_module->nCtrimFractNew = Power_module->nCtrimFractCurr +
        Power_scaleRndInf(Power_module->nDeltaFreqCurr);
    Power_module->nCtrimNew = Power_module->nCtrimCurr;

    /* One step of CTRIM is about 500 kHz, so limit to one CTRIM step */
    if (Power_module->nCtrimFractNew < 2)
    {
        /* Below sweet spot of current CTRIM => decrease CTRIM */
        Power_module->nCtrimNew = MAX(-0x40, Power_module->nCtrimNew - 1);
        Power_module->nCtrimFractNew = MAX(0, Power_module->nCtrimFractNew+16);
    }
    else if (Power_module->nCtrimFractNew > 29)
    {
        /* Above sweet spot of current CTRIM => increase CTRIM */
        Power_module->nCtrimNew = MIN(0x3F, Power_module->nCtrimNew + 1);
        Power_module->nCtrimFractNew = MIN(31, Power_module->nCtrimFractNew-16);
    }
    else
    {
        /* We're within sweet spot of current CTRIM => no change */
    }

    /* Find RCOSC_HF vs XOSC_HF frequency offset with new trim settings */
    DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_RCOSCHFCTL,
                           DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_M,
                           DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_S,
                           Power_module->nCtrimNew);

    /* Enable RCOSCHFCTRIMFRACT_EN */
    DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL1_LOCAL,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_EN_LOCAL_M,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_EN_LOCAL_S,
                           1);

    /* Modify CTRIM_FRACT */
    DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL1_LOCAL,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_M,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_S,
                           Power_module->nCtrimFractNew);
}

/*
 *  ======== Power_calibrateRcoscHf2 ========
 *  Calibrate RCOSC_HF agains XOSC_HF: determine better result, set new trims
 */
Void Power_calibrateRcoscHf2(Int32 tdcResult)
{
    Int32 nDeltaFreqNew;

    /* Calculate new delta freq */
    nDeltaFreqNew = (Int32) tdcResult - 1536;

    /* Determine whether the new settings are better or worse */
    if (Power_abs(nDeltaFreqNew) <= Power_abs(Power_module->nDeltaFreqCurr))
    {
        /* new settings are better or same, keep them in registers */
    }
    else
    {
        /*
         * Current setting were better, check whether we are getting fooled
         * by non-monotonicity in CTRIM
         */
        Power_module->nCtrimFractNew += Power_scaleRndInf(nDeltaFreqNew);
        if (Power_module->nCtrimCurr != Power_module->nCtrimNew &&
            Power_abs(Power_module->nCtrimFractCurr - 16) >
            Power_abs(Power_module->nCtrimFractNew - 16)) {

            /*
             * New settings updated based on frequency measurements are more
             * centered in its CTRIM than the current settings in its
             * CTRIM -> use updated new settings
             */
            DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL1_LOCAL,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_M,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_S,
                           Power_module->nCtrimFractNew);
        }
        else {
            /* New settings updated based on frequency measurements are less
             * centered in its CTRIM than the current settings in its CTRIM,
             * or they are both in the same CTRIM -> revert to old settings
             */
            DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_RCOSCHFCTL,
                           DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_M,
                           DDI_0_OSC_RCOSCHFCTL_RCOSCHF_CTRIM_S,
                           Power_module->nCtrimCurr);
            DDI16BitfieldWrite(AUX_DDI0_OSC_BASE, DDI_0_OSC_O_CTL1_LOCAL,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_M,
                           DDI_0_OSC_CTL1_RCOSCHFCTRIMFRACT_LOCAL_S,
                           Power_module->nCtrimFractCurr);
        }
    }
}

/*
 *  ======== Power_abs ========
 *  Absolute value
 */
Int Power_abs(Int i)
{
    /* compute absolute value of int argument */
    return (i < 0 ? -i : i);
}

/*
 *  ======== Power_scaleRndInf ========
 */
Int32 Power_scaleRndInf(Int32 x)
{
    return (2*x + ((x<0) ? -2 : 2))/3;
}
