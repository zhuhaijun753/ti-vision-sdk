/**
 *  \file  main_arp32.c
 *
 *  \brief ARP32 CPU Idle Example Application
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "arp32.h"
#include "soc.h"
#include "hw_eve_control.h"
#include "hw_edma_tc.h"
#include "hw_eve1_prm.h"
#include "hw_eve1_cm_core_aon.h"
#if defined (TDA2XX_FAMILY_BUILD)
#include "hw_eve2_prm.h"
#include "hw_eve2_cm_core_aon.h"
#include "hw_eve3_prm.h"
#include "hw_eve3_cm_core_aon.h"
#include "hw_eve4_prm.h"
#include "hw_eve4_cm_core_aon.h"
#endif
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "inth.h"
#include "intctl.h"
#include "irq_xbar.h"
#include "timer.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"
#include "pmlib_cpuidle.h"
#include "pmhal_cm.h"
#include "pmhal_pdm.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TIMER_INITIAL_COUNT             (uint32_t) (0xFFF00000U)
#define TIMER_RLD_COUNT                 (uint32_t) (0xFFF00000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TimerPRCMConfigure(void);
static void TimerIntcInit(void);
static void TimerIntcDeInit(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);
static void TimerRun(void);
static void TimerStop(void);
static void CpuIdleTest(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t gCntValue     = 10;
static volatile uint32_t gXbarInst     = 1;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void CpuIdleTest(void)
{
    pmErrCode_t status;
    uint32_t    i;
    uint32_t    coreId = _get_cpunum();

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */
    TimerPRCMConfigure();
    TimerRun();
    /* Wait to make sure VCOP is Idle */
    while (HW_RD_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_STAT,
                         EVE_STAT_VCOP_STAT) != 0U)
    {; }

    /* Program Force Standby for the EDMA TCs */
    HW_WR_REG32(SOC_EVE_EDMA_TC0_BASE + EDMA_TC_SYSCONFIG, 0x0);
    HW_WR_REG32(SOC_EVE_EDMA_TC1_BASE + EDMA_TC_SYSCONFIG, 0x0);

    /* Wait to make sure EDMA TC0 is Idle */
    while (HW_RD_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_STAT,
                         EVE_STAT_TC0_STAT) != 0U)
    {; }

    /* Wait to make sure EDMA TC1 is Idle */
    while (HW_RD_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_STAT,
                         EVE_STAT_TC1_STAT) != 0U)
    {; }

    if (0U == coreId)
    {
        /* Request EVE PD to be ON and CD to be clock gated */
        status = (pmErrCode_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE1,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                                  PM_TIMEOUT_NOWAIT);

        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_EVE1,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }
    #if defined (TDA2XX_FAMILY_BUILD)
    if (1U == coreId)
    {
        /* Request EVE PD to be ON and CD to be clock gated */
        status = (pmErrCode_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE2,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                                  PM_TIMEOUT_NOWAIT);

        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_EVE2,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }
    if (2U == coreId)
    {
        /* Request EVE PD to be ON and CD to be clock gated */
        status = (pmErrCode_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE3,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                                  PM_TIMEOUT_NOWAIT);

        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_EVE3,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }
    if (3U == coreId)
    {
        /* Request EVE PD to be ON and CD to be clock gated */
        status = (pmErrCode_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE4,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                                  PM_TIMEOUT_NOWAIT);

        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_EVE4,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }
    #endif
    for (i = 0; i < 10; i++)
    {
        status = PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_ON_ACTIVE);
        if (status == PM_SUCCESS)
        {
            UARTPuts("\nEnter Targeted Power State successfully", -1);
        }
        else
        {
            UARTPuts("\nEnter Targeted Power State failed", -1);
            break;
        }
    }
    TimerStop();
    UARTPuts("\nTest Completed!!", -1);
}

int main(void)
{
#if defined (TDA3XX_FAMILY_BUILD)
    PlatformUART3SetPinMux();
#else
    PlatformUART1SetPinMux();
#endif
    UARTStdioInit();
    UARTPuts("\nPM CPUIdle Test App", -1);
    /* Function to Test CPU Idle */
    CpuIdleTest();

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void TimerRun(void)
{
    /* Register Timer4 interrupts on to INTC */
    TimerIntcInit();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Enable the Timer4 wakeup event */
    TIMERWakeEnable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

    /* Set the Timer4 to Smart-idle mode */
    TIMERIdleModeConfigure(SOC_TIMER4_BASE, TIMER_SMART_IDLE);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
}

static void TimerStop(void)
{
    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    /* Disable the Timer4 wakeup event */
    TIMERWakeDisable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

    /* Unregister Timer4 interrupts */
    TimerIntcDeInit();
}

/*
 * Do the necessary Timer configurations on to INTC.
 */
static void TimerIntcInit(void)
{
    irq_xbar_ret_type_t status = invalid_mpu_id;
    uint8_t  connectionStatus  = 0;
    uint32_t coreId = _get_cpunum();
    cpu_id_t cpuId  = CPU_EVE1;
    #if defined (TDA2XX_FAMILY_BUILD)
    if (1U == coreId)
    {
        cpuId = CPU_EVE2;
    }
    if (2U == coreId)
    {
        cpuId = CPU_EVE3;
    }
    if (3U == coreId)
    {
        cpuId = CPU_EVE4;
    }
    #endif
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Connect the Xbar with interrupt source */
    status = IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, cpuId,
                            gXbarInst, TIMER4_IRQ);

    if (status == irq_xbar_success)
    {
        /* Check if xbar is indeed connected correctly */
        IRQXBARIsConnected(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, cpuId,
                           gXbarInst, TIMER4_IRQ, &connectionStatus);
        if (connectionStatus == 1)
        {
            UARTPuts("\nXBar is successfully connected to inst:", -1);
            UARTPutNum(gXbarInst);
        }
        else
        {
            UARTPuts("\nWrong XBar Connection", -1);
        }
    }
    else
    {
        UARTPuts("\nXBar not able to connect", -1);
    }

    /* Enable the interrupt */
    EVE_INTH_InterruptSetup(EVE_EVT_INT0,
                            (uint32_t) TimerIsr,
                            INTH_DEFAULT_INTERRUPT_KIND,
                            INTH_INT8);

    /* Actually set Enable bit in the interrupt controller */
    EVE_INTH_InterruptEnable(EVE_EVT_INT0);
    UARTPuts("\nInterrupt enable done", -1);
}

/*
 * Disable the interrupt configurations on INTC.
 */
static void TimerIntcDeInit(void)
{
    uint32_t coreId = _get_cpunum();
    cpu_id_t cpuId  = CPU_EVE1;
    #if defined (TDA2XX_FAMILY_BUILD)
    if (1U == coreId)
    {
        cpuId = CPU_EVE2;
    }
    if (2U == coreId)
    {
        cpuId = CPU_EVE3;
    }
    if (3U == coreId)
    {
        cpuId = CPU_EVE4;
    }
    #endif
    /* Restore the initial state of gCntValue */
    gCntValue = 10;

    /* Disconnect the XBar */
    IRQXBARDisconnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, cpuId,
                      gXbarInst);

    /* Disable the timer interrupt */
    EVE_INTH_InterruptDisable(EVE_EVT_INT0);
    UARTPuts("\nInterrupt disable done", -1);
}

/*
 * Setup the timer for one-shot and compare mode.
 */
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_FREE);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER4_BASE, (uint32_t) TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    TIMERReloadSet(SOC_TIMER4_BASE, (uint32_t) TIMER_RLD_COUNT);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE,
                       (uint32_t) TIMER_AUTORLD_NOCMP_ENABLE);
}

/*
 * Timer interrupt service routine. This will send a character to serial
 * console.
 */
static void TimerIsr(void *handle)
{
    int32_t time = 0;
    time = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
    UARTPuts("\nTime Taken to Wakeup:", -1);
    UARTPutNum(time - (int32_t) TIMER_RLD_COUNT);
    /* Disable the Timer interrupts */
    TIMERIntDisable(SOC_TIMER4_BASE,
                    (uint32_t) TIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    TIMERIntStatusClear(SOC_TIMER4_BASE,
                        (uint32_t) TIMER_INT_OVF_IT_FLAG);

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, (uint32_t) TIMER_INT_OVF_EN_FLAG);
    UARTPuts("\nISR done", -1);
}

/*
 * Timer4 PRCM configuration. This will explicitly enable the Timer4 module.
 */
static void TimerPRCMConfigure(void)
{
    /* PMHAL is not supported on EVE. Enabling Timer clocks using direct
     * register writes.
     */
    HW_WR_FIELD32((SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL),
                  CM_L4PER_TIMER4_CLKCTRL_MODULEMODE,
                  0x2);
}

